//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "Platform/Prerequisites.h"

#ifdef DANGINE_BUILD_RENDERSYSTEM_D3D9
#include "Graphics/D3D9/RenderSystemD3D9.h"
#elif DANGINE_BUILD_RENDERSYSTEM_GL
#include "Graphics/GL/RenderSystemGL.h"
#endif

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class RenderSystem : public DANGINE_RENDERSYSTEM_BASE
{
	typedef DANGINE_RENDERSYSTEM_BASE Base;

public:
	RenderSystem();
	~RenderSystem();

	bool initialise(void* pHandle);
	void shutdown();

	bool beginScene(uint buffers);
	bool endScene();
	bool clearScene(uint buffers);
	bool present();

	void setClearColor(float red, float green, float blue, float alpha);

	bool setWorldMatrix(const vmMatrix4& m);
	bool setViewMatrix(const vmMatrix4& m);
	bool setProjectionMatrix(const vmMatrix4& m);
	bool setAmbientLight(float red, float green, float blue);
	bool setShadingType(ShadeOptions so);
	bool setLightingEnabled(bool enabled);
	bool setLight(size_t index, Light* light);
	bool setLightEnabled(size_t index, bool enabled);
	bool setBlending(SceneBlendFactor sourceFactor, SceneBlendFactor destFactor, SceneBlendOperation op);
	bool setBlendingSeparate(SceneBlendFactor sourceFactor, SceneBlendFactor destFactor, 
		SceneBlendFactor sourceFactorAlpha, SceneBlendFactor destFactorAlpha, 
		SceneBlendOperation op, SceneBlendOperation alphaOp);
	bool setAlpha(CompareFunction func, unsigned char value);
	bool setDepthEnabled(bool enabled);
	bool setDepthWriteEnabled(bool enabled);
	bool setCullingMode(CullingMode mode);
	bool setPolygonMode(PolygonMode level);
	bool setStencilEnabled(bool enabled);
	bool setStencilParams(CompareFunction func, uint32 refValue, uint32 mask, 
		StencilOperation stencilFailOp, StencilOperation depthFailOp, 
		StencilOperation passOp, bool twoSidedOperation);

}; // class RenderSystem
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // RENDERSYSTEM_H