//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Systems/CameraSystem.h"
#include "Util/Entity/SystemManager.h"
#include "Util/Entity/World.h"
#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Graphics/RenderSystem.h"
#include "Graphics/D3D9/MappingsD3D9.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
CameraSystem::CameraSystem(ComponentType type)
	: System(type)
{
}
//------------------------------------------------------------------------------
CameraSystem::~CameraSystem()
{
	System::destroy();
}
//------------------------------------------------------------------------------
void CameraSystem::_initialise(Entity& rEntity)
{
	Camera* camera = rEntity.getComponent<Camera>();
	Transform* transform = rEntity.getComponent<Transform>();
	// TODO: Camera shouldn't really be storing the position.
	camera->position = transform->position;

	Real depth = camera->farRange - camera->nearRange;
	Real q = -camera->nearRange * camera->farRange / depth;
	Real qn = camera->farRange / depth;
	Real yScale = tan((D3DX_PI / 2) - (camera->fov / 2));
	Real xScale = yScale / camera->aspectRatio;

	vmMatrix4 matrixProj(
		vmVector4(xScale, 0.0f,   0.0f, 0.0f),
		vmVector4(0.0f,   yScale, 0.0f, 0.0f),
		vmVector4(0.0f,   0.0f,   qn,   q),
		vmVector4(0.0f,   0.0f,   1.0f, 0.0f));

	camera->projectionMatrix = matrixProj;
	mRenderSystem->setProjectionMatrix(camera->projectionMatrix);
}
//------------------------------------------------------------------------------
void CameraSystem::_destroy(Entity& rEntity)
{
	(void)rEntity;
	// Nothing to destroy
}
//------------------------------------------------------------------------------
void CameraSystem::_process(Entity& rEntity)
{
	Camera* camera = rEntity.getComponent<Camera>();
	Transform* transform = rEntity.getComponent<Transform>();
	// TODO: Camera shouldn't really be storing the position.
	camera->position = transform->position;

	D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);
	D3DXVECTOR3 look = D3DXVECTOR3(0, 0, 1);
	D3DXVECTOR3 right = D3DXVECTOR3(1, 0, 0);

	// Yaw is rotation around the y axis (up)
	D3DXMATRIX yawMatrix;
	D3DXMatrixRotationAxis(&yawMatrix, &up, camera->yaw);
	// To apply yaw we rotate the look & right vectors about the up vector (using our yaw matrix)
	D3DXVec3TransformCoord(&look, &look, &yawMatrix); 
	D3DXVec3TransformCoord(&right, &right, &yawMatrix); 

	// Pitch is rotation around the x axis (right)
	D3DXMATRIX pitchMatrix;
	D3DXMatrixRotationAxis(&pitchMatrix, &right, camera->pitch);
	// To apply pitch we rotate the look and up vectors about the right vector (using our pitch matrix)
	D3DXVec3TransformCoord(&look, &look, &pitchMatrix); 
	D3DXVec3TransformCoord(&up, &up, &pitchMatrix); 
		
	// Roll is rotation around the z axis (look)
	D3DXMATRIX rollMatrix;
	D3DXMatrixRotationAxis(&rollMatrix, &look, camera->roll);
	// To apply roll we rotate up and right about the look vector (using our roll matrix)
	D3DXVec3TransformCoord(&right, &right, &rollMatrix); 
	D3DXVec3TransformCoord(&up, &up, &rollMatrix); 

	// Build the view matrix from the transformed camera axis
	D3DXMATRIX matrixView;
	D3DXMatrixIdentity(&matrixView);

	matrixView._11 = right.x; matrixView._12 = up.x; matrixView._13 = look.x;
	matrixView._21 = right.y; matrixView._22 = up.y; matrixView._23 = look.y;
	matrixView._31 = right.z; matrixView._32 = up.z; matrixView._33 = look.z;
	
	D3DXVECTOR3 pos = D3DXVECTOR3(transform->position.getX(), transform->position.getY(), transform->position.getZ());
	matrixView._41 = - D3DXVec3Dot(&pos, &right); 
	matrixView._42 = - D3DXVec3Dot(&pos, &up);
	matrixView._43 = - D3DXVec3Dot(&pos, &look);

	// Set the camera values
	camera->right = vmVector3(right.x, right.y, right.z);
	camera->up = vmVector3(up.x, up.y, up.z);
	camera->look = vmVector3(look.x, look.y, look.z);

	camera->viewMatrix = MappingsD3D9::convertD3DXMatrix(matrixView);
	mRenderSystem->setViewMatrix(camera->viewMatrix);
}
//------------------------------------------------------------------------------
void CameraSystem::yaw(Entity& rEntity, Real amount)
{
	Camera* camera = rEntity.getComponent<Camera>();
	camera->yaw += amount;
	camera->yaw = _restrictAngleTo360Range(camera->yaw);
}
//------------------------------------------------------------------------------
void CameraSystem::pitch(Entity& rEntity, Real amount)
{
	Camera* camera = rEntity.getComponent<Camera>();
	camera->pitch += amount;
	camera->pitch = _restrictAngleTo360Range(camera->pitch);
}
//------------------------------------------------------------------------------
void CameraSystem::roll(Entity& rEntity, Real amount)
{
	Camera* camera = rEntity.getComponent<Camera>();
	camera->roll += amount;
	camera->roll = _restrictAngleTo360Range(camera->roll);
}
//------------------------------------------------------------------------------
void CameraSystem::moveForward(Entity& rEntity, Real amount)
{
	Camera* camera = rEntity.getComponent<Camera>();
	Transform* transform = rEntity.getComponent<Transform>();
	transform->position += camera->look * amount;
}
//------------------------------------------------------------------------------
void CameraSystem::moveRight(Entity& rEntity, Real amount)
{
	Camera* camera = rEntity.getComponent<Camera>();
	Transform* transform = rEntity.getComponent<Transform>();
	transform->position += camera->right * amount;
}
//------------------------------------------------------------------------------
void CameraSystem::moveUp(Entity& rEntity, Real amount)
{
	Camera* camera = rEntity.getComponent<Camera>();
	Transform* transform = rEntity.getComponent<Transform>();
	transform->position += camera->up * amount;
}
//------------------------------------------------------------------------------
Real CameraSystem::_restrictAngleTo360Range(Real angle) const
{
	while (angle > 2 * D3DX_PI)
		angle -= 2 * D3DX_PI;
	while (angle < 0)
		angle += 2 * D3DX_PI;
	return angle;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------