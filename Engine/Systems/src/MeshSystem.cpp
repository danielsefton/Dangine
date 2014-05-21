//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Systems/MeshSystem.h"
#include "Util/Entity/SystemManager.h"
#include "Util/Entity/World.h"
#include "Components/Mesh.h"
#include "Components/Transform.h"
#include "Graphics/RenderSystem.h"
#include "Graphics/D3D9/MappingsD3D9.h"
#include "Components/Camera.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
MeshSystem::MeshSystem(ComponentType type)
	: System(type)
	, mRenderSystem(0)
	, mCamera(0)
	, mLight(0)
{
}
//------------------------------------------------------------------------------
MeshSystem::~MeshSystem()
{
	System::destroy();
}
//------------------------------------------------------------------------------
void MeshSystem::_initialise(Entity& rEntity)
{
	Mesh* mesh = rEntity.getComponent<Mesh>();

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX(mesh->file.c_str(), D3DXMESH_SYSTEMMEM, mRenderSystem->getD3D9Device(), 
		NULL, NULL, NULL, NULL, &mesh->mesh)))
	{
		// If model is not in current folder, try parent folder
		if (FAILED(D3DXLoadMeshFromX(mesh->file.c_str(), D3DXMESH_SYSTEMMEM, mRenderSystem->getD3D9Device(), 
			NULL, NULL, NULL, NULL, &mesh->mesh)))
		{
			MessageBox(NULL, std::string("Could not find " + mesh->file).c_str(), "Meshes.exe", MB_OK);
			return; //E_FAIL;
		}
	}

	// Create textures
	for (size_t i = 0; i < mesh->materials.size(); ++i)
	{
		mesh->materials[i].textures = DG_NEW_ARRAY2(LPDIRECT3DTEXTURE9, mesh->materials.size(), systemManager->getWorld().getLinearArena());
		for (size_t j = 0; j < mesh->materials[i].textureFiles.size(); ++j)
		{
			String path = "..\\media\\" + mesh->materials[i].textureFiles[j];
			if (FAILED(D3DXCreateTextureFromFileA(mRenderSystem->getD3D9Device(), path.c_str(), &mesh->materials[i].textures[j])))
			{
				MessageBox(NULL, std::string("Could not find texture map " + path).c_str(), "Meshes.exe", MB_OK);
			}
		}
	}

	// Create effect
	ID3DXBuffer* pError = NULL;
	if (FAILED(D3DXCreateEffectFromFile(mRenderSystem->getD3D9Device(), mesh->effectFile.c_str(), 
		NULL, NULL, D3DXSHADER_DEBUG, NULL, &mesh->effect, &pError)))
	{ 
		if (pError != NULL) 
		{ 
			MessageBoxA(NULL, (char*)(pError->GetBufferPointer()), "Error", 0);
			pError->Release(); 
		}  
	}
}
//------------------------------------------------------------------------------
void MeshSystem::_destroy(Entity& rEntity)
{
	Mesh* mesh = rEntity.getComponent<Mesh>();

	for (size_t i = 0; i < mesh->materials.size(); ++i)
	{
		for (size_t j = 0; j < mesh->materials[i].textureFiles.size(); ++j)
		{
			// TODO: Crash here if mesh is not found
			if (mesh->materials[i].textures[j])
			{
				mesh->materials[i].textures[j]->Release();
				DG_DELETE_ARRAY(mesh->materials[i].textures[j], systemManager->getWorld().getLinearArena());
			}
		}
	}

	if (mesh->mesh != NULL)
		mesh->mesh->Release();

	if (mesh->effect != NULL)
		mesh->effect->Release();
}
//------------------------------------------------------------------------------
void MeshSystem::_process(Entity& rEntity)
{
	Mesh* mesh = rEntity.getComponent<Mesh>();
	Transform* transform = rEntity.getComponent<Transform>();

	D3DXMATRIX matWorld;
	// TODO: Remove. This is to support PhysX.
	if (transform->useMatrixTransform)
	{
		matWorld = transform->d3dMat;
		mRenderSystem->getD3D9Device()->SetTransform(D3DTS_WORLD, &matWorld);
	}
	else
	{
		D3DXMATRIX matRotate;
		D3DXMatrixRotationQuaternion(&matRotate, &MappingsD3D9::makeD3DXQuat(transform->orientation));
		D3DXMATRIX matScale;
		D3DXMatrixScaling(&matScale, transform->scale.getX(), transform->scale.getY(), transform->scale.getZ());
		D3DXMATRIX matTranslate;
		D3DXMatrixTranslation(&matTranslate, transform->position.getX(), transform->position.getY(), transform->position.getZ());
		matWorld = matRotate * matScale * matTranslate;
		mRenderSystem->getD3D9Device()->SetTransform(D3DTS_WORLD, &matWorld);
	}

	// TODO: Position isn't working
	/*vmMatrix4 matWorld(
		vmMatrix4::rotation(transform->orientation) * 
		vmMatrix4::scale(transform->scale) * 
		vmMatrix4::translation(transform->position));
	mRenderSystem->setWorldMatrix(matWorld);*/

	// TODO: Remove this if function.
	if (mesh->mesh != NULL && mesh->effect != NULL && mCamera != 0 && mLight != 0)
	{
		D3DXMATRIX dxMatWorld = matWorld;//MappingsD3D9::makeD3DXMatrix(matWorld);
		D3DXMATRIX dxMatView = MappingsD3D9::makeD3DXMatrix(mCamera->viewMatrix);
		D3DXMATRIX dxMatProj = MappingsD3D9::makeD3DXMatrix(mCamera->projectionMatrix);
		D3DXMATRIX dxMatViewProj = dxMatView * dxMatProj;
		D3DXMATRIX dxMatWorldView = dxMatWorld * dxMatView;
		D3DXMATRIX dxMatWorldViewProj = dxMatWorld * dxMatView * dxMatProj;

		mesh->effect->SetMatrix("world_matrix", &dxMatWorld);
		mesh->effect->SetMatrix("view_matrix", &dxMatView);
		mesh->effect->SetMatrix("projection_matrix", &dxMatProj);
		mesh->effect->SetMatrix("viewproj_matrix", &dxMatViewProj);
		mesh->effect->SetMatrix("worldview_matrix", &dxMatWorldView);
		mesh->effect->SetMatrix("worldviewproj_matrix", &dxMatWorldViewProj);

		UINT numPasses = 0;
		mesh->effect->Begin(&numPasses, 0);

		for (UINT pass = 0; pass < numPasses; ++pass)
		{
			mesh->effect->BeginPass(pass);

			for (size_t i = 0; i < mesh->materials.size(); ++i)
			{
				// Set the shader params
				D3DXVECTOR4 dxSurfaceAmbient = MappingsD3D9::makeD3DXVector4(mesh->materials[i].ambient);
				D3DXVECTOR4 dxSurfaceDiffuse = MappingsD3D9::makeD3DXVector4(mesh->materials[i].diffuse);
				D3DXVECTOR4 dxSurfaceSpecular = MappingsD3D9::makeD3DXVector4(mesh->materials[i].specular);
				D3DXVECTOR4 dxSurfaceEmissive = MappingsD3D9::makeD3DXVector4(mesh->materials[i].emissive);
				D3DXVECTOR4 dxLightAmbient = MappingsD3D9::makeD3DXVector4(mLight->ambient);
				D3DXVECTOR4 dxLightDiffuse = MappingsD3D9::makeD3DXVector4(mLight->diffuse);
				D3DXVECTOR4 dxLightSpecular = MappingsD3D9::makeD3DXVector4(mLight->specular);
				D3DXVECTOR4 dxLightPos = D3DXVECTOR4(MappingsD3D9::makeD3DXVector3(mLight->position), 0.0f);
				D3DXVECTOR4 dxLightDir = D3DXVECTOR4(MappingsD3D9::makeD3DXVector3(mLight->direction), 0.0f);
				D3DXVECTOR4 dxCameraPos = D3DXVECTOR4(MappingsD3D9::makeD3DXVector3(mCamera->position), 0.0f);

				mesh->effect->SetVector("surface_ambient_colour", &dxSurfaceAmbient);
				mesh->effect->SetVector("surface_diffuse_colour", &dxSurfaceDiffuse);
				mesh->effect->SetVector("surface_specular_colour", &dxSurfaceSpecular);
				mesh->effect->SetVector("surface_emissive_colour", &dxSurfaceEmissive);
				mesh->effect->SetFloat("surface_shininess", mesh->materials[i].shininess);

				mesh->effect->SetVector("ambient_light_colour", &dxLightAmbient);
				mesh->effect->SetVector("light_diffuse_colour", &dxLightDiffuse);
				mesh->effect->SetVector("light_specular_colour", &dxLightSpecular);
				mesh->effect->SetVector("light_position", &dxLightPos);
				mesh->effect->SetVector("light_direction", &dxLightDir);

				mesh->effect->SetVector("camera_position", &dxCameraPos);

				mesh->effect->SetFloat("time", systemManager->getWorld().getElapsed());

				for (size_t j = 0; j < mesh->materials[i].textureFiles.size(); ++j)
				{
					std::stringstream ss;
					ss << "g_texture" << j;
					mesh->effect->SetTexture(ss.str().c_str(), mesh->materials[i].textures[j]);
				}

				// Draw the mesh subset
				mesh->mesh->DrawSubset(i);
			}

			mesh->effect->EndPass();
		}

		mesh->effect->End();
	}
	// TODO: Remove this part - legacy support for fixed-function.
	else if (mesh->mesh != NULL)
	{
		// Meshes are divided into subsets, one for each material. Render them in a loop.
		for (DWORD i = 0; i < mesh->materials.size(); ++i)
		{
			D3DMATERIAL9 dxMat;
			ZeroMemory(&dxMat, sizeof(D3DMATERIAL9));
			dxMat.Ambient = MappingsD3D9::makeD3DColorValue(mesh->materials[i].ambient);
			dxMat.Diffuse = MappingsD3D9::makeD3DColorValue(mesh->materials[i].diffuse);
			dxMat.Specular = MappingsD3D9::makeD3DColorValue(mesh->materials[i].specular);
			dxMat.Emissive = MappingsD3D9::makeD3DColorValue(mesh->materials[i].emissive);
			dxMat.Power = mesh->materials[i].shininess;

			// Set the material and texture for this subset
			mRenderSystem->getD3D9Device()->SetMaterial(&dxMat);
			mRenderSystem->getD3D9Device()->SetTexture(0, mesh->materials[i].textures[0]);
			
			// Draw the mesh subset
			mesh->mesh->DrawSubset(i);
		}
	}
}
//------------------------------------------------------------------------------
std::vector<Real> MeshSystem::getVertices(Entity& rEntity)
{
	Mesh* mesh = rEntity.getComponent<Mesh>();

	// http://forum-archive.developer.nvidia.com/index.php?showtopic=1953
	std::vector<Real> vertices;
	DWORD stride =  D3DXGetFVFVertexSize(mesh->mesh->GetFVF());
	BYTE* vbptr = NULL;
	mesh->mesh->LockVertexBuffer(0, (LPVOID*)&vbptr);
	int ii = -1;
	for (size_t i = 0; i < mesh->mesh->GetNumVertices(); ++i)
	{
		ii++;
		D3DXVECTOR3* pos = (D3DXVECTOR3*)vbptr;
		vertices.push_back(pos->x);
		vertices.push_back(pos->y);
		vertices.push_back(pos->z);
		vbptr += stride;
	}
	mesh->mesh->UnlockVertexBuffer();
	return vertices;
}
//------------------------------------------------------------------------------
std::vector<short> MeshSystem::getIndices(Entity& rEntity)
{
	Mesh* mesh = rEntity.getComponent<Mesh>();

	//int b = mesh->mesh->GetOptions();
	//if (b & D3DXMESH_32BIT)
		//LOG(logINFO) << "32 bit";

	// http://forum-archive.developer.nvidia.com/index.php?showtopic=1953
	DWORD stride = sizeof(short);
	BYTE* ibptr = NULL;
	short* indices = NULL;
	std::vector<short> copy;
	mesh->mesh->LockIndexBuffer(0, (LPVOID*)&indices);
	for (size_t i = 0; i < mesh->mesh->GetNumFaces() * 3; ++i)
	{
		copy.push_back(indices[i]);
	}
	mesh->mesh->UnlockIndexBuffer();
	return copy;
}
//------------------------------------------------------------------------------
AxisAlignedBox MeshSystem::getBoundingBox(Entity& rEntity) const
{
	Mesh* mesh = rEntity.getComponent<Mesh>();

	DWORD* pData = NULL;
	D3DXVECTOR3 minBounds;
	D3DXVECTOR3 maxBounds;
	mesh->mesh->LockVertexBuffer(D3DLOCK_READONLY, (VOID**)&pData);   
	D3DXComputeBoundingBox((D3DXVECTOR3*)pData, mesh->mesh->GetNumVertices(), 
		D3DXGetFVFVertexSize(mesh->mesh->GetFVF()), &minBounds, &maxBounds);
	mesh->mesh->UnlockVertexBuffer();

	return AxisAlignedBox(MappingsD3D9::convertD3DXVector3(minBounds), 
		MappingsD3D9::convertD3DXVector3(maxBounds));
}
//------------------------------------------------------------------------------
Real MeshSystem::getBoundingRadius(Entity& rEntity) const
{
	Mesh* mesh = rEntity.getComponent<Mesh>();

	DWORD* pData = NULL;
	D3DXVECTOR3 center;
	FLOAT radius;
	mesh->mesh->LockVertexBuffer(D3DLOCK_READONLY, (VOID**)&pData);   
	D3DXComputeBoundingSphere((D3DXVECTOR3*)pData, mesh->mesh->GetNumVertices(), 
		D3DXGetFVFVertexSize(mesh->mesh->GetFVF()), &center, &radius);
	mesh->mesh->UnlockVertexBuffer();

	return radius;

	/*FLOAT radius;
	D3DXVECTOR3 center;
	LPDIRECT3DVERTEXBUFFER9 pVBuf;//pointer to vertex buffer
	if (SUCCEEDED(mesh->mesh->GetVertexBuffer(&pVBuf))) {//get the address
		D3DXVECTOR3* pVert;//pointer to first vertex in buffer
		if (SUCCEEDED(pVBuf->Lock(0,0,(void **) &pVert,D3DLOCK_READONLY))) {
			//compute bounding radius
			D3DXComputeBoundingSphere(
				  pVert,			
				  mesh->mesh->GetNumVertices(),		
				  mesh->mesh->GetNumBytesPerVertex(),	
				  &center,							
				  &radius					
			);
			//add the largest component of the center vect to the radius so the center can be 0 and the radius will encompas entire mesh
			radius+=std::max(std::max(abs(center.x),abs(center.y)),abs(center.z));
			pVBuf->Unlock();

			return radius;
		}else{
			MessageBox( NULL, "could not lock vertex buffer", "getBoundingSphere", MB_OK );
		}
	}else{
		MessageBox( NULL, "error getting vertex buffer address", "getBoundingSphere", MB_OK );
	}*/
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------