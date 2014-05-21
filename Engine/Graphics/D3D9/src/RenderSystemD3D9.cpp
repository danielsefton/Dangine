//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Graphics/D3D9/RenderSystemD3D9.h"
#include "Graphics/D3D9/MappingsD3D9.h"
#include "Components/Light.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
RenderSystemD3D9::RenderSystemD3D9()
	: mD3D(NULL)
	, mD3DDevice(NULL)
{
	mClearColour[0] = mClearColour[1] = mClearColour[2] = mClearColour[3] = 0.5f;
}
//------------------------------------------------------------------------------
RenderSystemD3D9::~RenderSystemD3D9()
{
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::initialise(void* pHandle)
{
	if ((mD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	D3DDISPLAYMODE d3ddm;
	mD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.BackBufferWidth = 1024;
	d3dpp.BackBufferHeight = 768;
	d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	/*d3dpp.Windowed			   = FALSE;
	d3dpp.SwapEffect			 = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferWidth		= 1024;
	d3dpp.BackBufferHeight	   = 768;
	d3dpp.BackBufferFormat	   = D3DFMT_X8R8G8B8;
	d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;*/

	if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, (HWND)pHandle, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
void RenderSystemD3D9::shutdown()
{
	if (mD3DDevice != NULL)
		mD3DDevice->Release();
	mD3DDevice = NULL;

	if (mD3D != NULL)
		mD3D->Release();
	mD3D = NULL;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::beginScene(uint buffers)
{
	if (mD3DDevice == NULL)
		return false;

	clearScene(buffers);

	if (FAILED(mD3DDevice->BeginScene()))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::endScene()
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->EndScene()))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::clearScene(uint buffers)
{
	if (mD3DDevice == NULL)
		return false;

	DWORD flags = 0;
	if (buffers & FBT_COLOUR)
	{
		flags |= D3DCLEAR_TARGET;
	}
	if (buffers & FBT_DEPTH)
	{
		flags |= D3DCLEAR_ZBUFFER;
	}
	if (buffers & FBT_STENCIL)
	{
		flags |= D3DCLEAR_STENCIL;
	}

	if (FAILED(mD3DDevice->Clear(0, NULL, flags, D3DCOLOR_COLORVALUE(
		mClearColour[0], mClearColour[1], mClearColour[2], mClearColour[3]), 1.0f, 0)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::present()
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->Present(NULL, NULL, NULL, NULL)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
void RenderSystemD3D9::setClearColor(float red, float green, float blue, float alpha)
{
	mClearColour[0] = red;
	mClearColour[1] = green;
	mClearColour[2] = blue;
	mClearColour[3] = alpha;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setWorldMatrix(const vmMatrix4& m)
{
	if (mD3DDevice == NULL)
		return false;

	mDxWorldMat = MappingsD3D9::makeD3DXMatrix(m);

	if (FAILED(mD3DDevice->SetTransform(D3DTS_WORLD, &mDxWorldMat)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setViewMatrix(const vmMatrix4& m)
{
	if (mD3DDevice == NULL)
		return false;

	mDxViewMat = MappingsD3D9::makeD3DXMatrix(m);

	if (FAILED(mD3DDevice->SetTransform(D3DTS_VIEW, &mDxViewMat)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setProjectionMatrix(const vmMatrix4& m)
{
	if (mD3DDevice == NULL)
		return false;

	mDxProjMat = MappingsD3D9::makeD3DXMatrix(m);

	if (FAILED(mD3DDevice->SetTransform(D3DTS_PROJECTION, &mDxProjMat)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setAmbientLight(float red, float green, float blue)
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(red, green, blue, 1.0f))))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setShadingType(ShadeOptions so)
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_SHADEMODE, MappingsD3D9::get(so))))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setLightingEnabled(bool enabled)
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_LIGHTING, enabled)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setLight(size_t index, Light* light)
{
	if (mD3DDevice == NULL)
		return false;

	D3DLIGHT9 l;
	ZeroMemory(&l, sizeof(l));

	// Map values to D3DLIGHT9
	switch (light->lightType)
	{
		case LT_POINT:
			l.Type = D3DLIGHT_POINT;
			break;
		case LT_DIRECTIONAL:
			l.Type = D3DLIGHT_DIRECTIONAL;
			break;
		case LT_SPOTLIGHT:
			l.Type = D3DLIGHT_SPOT;
			l.Theta = light->theta;
			l.Phi = light->phi;
			l.Falloff = light->falloff;
			break;
	}
	l.Ambient		= MappingsD3D9::makeD3DColorValue(light->ambient);
	l.Diffuse		= MappingsD3D9::makeD3DColorValue(light->diffuse);
	l.Specular		= MappingsD3D9::makeD3DColorValue(light->specular);
	l.Position		= MappingsD3D9::makeD3DXVector3(light->position);
	l.Direction		= MappingsD3D9::makeD3DXVector3(light->direction);
	l.Range			= light->range;
	l.Attenuation0	= light->attenuation0;
	l.Attenuation1	= light->attenuation1;
	l.Attenuation2	= light->attenuation2;

	if (FAILED(mD3DDevice->SetLight(static_cast<DWORD>(index), &l)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setLightEnabled(size_t index, bool enabled)
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->LightEnable(static_cast<DWORD>(index), enabled)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setBlending(SceneBlendFactor sourceFactor, 
	SceneBlendFactor destFactor, SceneBlendOperation op)
{
	if (mD3DDevice == NULL)
		return false;

	if (sourceFactor == SBF_ONE && destFactor == SBF_ZERO)
	{
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE)))
			return false;
	}
	else
	{
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE)))
			return false;
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, FALSE)))
			return false;
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_SRCBLEND, MappingsD3D9::get(sourceFactor))))
			return false;
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_DESTBLEND, MappingsD3D9::get(destFactor))))
			return false;
	}

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_BLENDOP, MappingsD3D9::get(op))))
		return false;
	if (FAILED(mD3DDevice->SetRenderState(D3DRS_BLENDOPALPHA, MappingsD3D9::get(op))))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setBlendingSeparate(SceneBlendFactor sourceFactor, 
	SceneBlendFactor destFactor, SceneBlendFactor sourceFactorAlpha, 
	SceneBlendFactor destFactorAlpha, SceneBlendOperation op, 
	SceneBlendOperation alphaOp)
{
	if (mD3DDevice == NULL)
		return false;

	if (sourceFactor == SBF_ONE && destFactor == SBF_ZERO && 
		sourceFactorAlpha == SBF_ONE && destFactorAlpha == SBF_ZERO)
	{
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE)))
			return false;
	}
	else
	{
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE)))
			return false;
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE)))
			return false;
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_SRCBLEND, MappingsD3D9::get(sourceFactor))))
			return false;
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_DESTBLEND, MappingsD3D9::get(destFactor))))
			return false;
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_SRCBLENDALPHA, MappingsD3D9::get(sourceFactorAlpha))))
			return false;
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_DESTBLENDALPHA, MappingsD3D9::get(destFactorAlpha))))
			return false;
	}

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_BLENDOP, MappingsD3D9::get(op))))
		return false;
	if (FAILED(mD3DDevice->SetRenderState(D3DRS_BLENDOPALPHA, MappingsD3D9::get(alphaOp))))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setAlpha(CompareFunction func, unsigned char value)
{
	if (mD3DDevice == NULL)
		return false;

	if (func != CMPF_ALWAYS_PASS)
	{
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,  TRUE)))
			return false;
	}
	else
	{
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,  FALSE)))
			return false;
	}

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, MappingsD3D9::get(func))))
		return false;
	if (FAILED(mD3DDevice->SetRenderState(D3DRS_ALPHAREF, value)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setDepthEnabled(bool enabled)
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_ZENABLE, enabled)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setDepthWriteEnabled(bool enabled)
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, enabled)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setCullingMode(CullingMode mode)
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_CULLMODE, MappingsD3D9::get(mode, false))))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setPolygonMode(PolygonMode level)
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_FILLMODE, MappingsD3D9::get(level))))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setStencilEnabled(bool enabled)
{
	if (mD3DDevice == NULL)
		return false;

	if (FAILED(mD3DDevice->SetRenderState(D3DRS_STENCILENABLE, enabled)))
		return false;

	return true;
}
//------------------------------------------------------------------------------
bool RenderSystemD3D9::setStencilParams(CompareFunction func, uint32 refValue, 
	uint32 mask, StencilOperation stencilFailOp, StencilOperation depthFailOp, 
	StencilOperation passOp, bool twoSidedOperation)
{
	if (mD3DDevice == NULL)
		return false;

	// 2-sided operation
	if (twoSidedOperation)
	{
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, TRUE)))
			return false;

		// Set alternative versions of ops
		// fail op
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_CCW_STENCILFAIL, MappingsD3D9::get(stencilFailOp, false))))
			return false;

		// depth fail op
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_CCW_STENCILZFAIL, MappingsD3D9::get(depthFailOp, false))))
			return false;

		// pass op
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_CCW_STENCILPASS, MappingsD3D9::get(passOp, false))))
			return false;
	}
	else
	{
		if (FAILED(mD3DDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE, FALSE)))
			return false;
	}

	// func
	if (FAILED(mD3DDevice->SetRenderState(D3DRS_STENCILFUNC, MappingsD3D9::get(func))))
		return false;

	// reference value
	if (FAILED(mD3DDevice->SetRenderState(D3DRS_STENCILREF, refValue)))
		return false;

	// mask
	if (FAILED(mD3DDevice->SetRenderState(D3DRS_STENCILMASK, mask)))
		return false;

	// fail op
	if (FAILED(mD3DDevice->SetRenderState(D3DRS_STENCILFAIL, MappingsD3D9::get(stencilFailOp, false))))
		return false;

	// depth fail op
	if (FAILED(mD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, MappingsD3D9::get(depthFailOp, false))))
		return false;

	// pass op
	if (FAILED(mD3DDevice->SetRenderState(D3DRS_STENCILPASS, MappingsD3D9::get(passOp, false))))
		return false;

	return true;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------