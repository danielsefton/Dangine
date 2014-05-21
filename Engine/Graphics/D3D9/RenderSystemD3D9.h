//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef RENDERSYSTEMD3D9_H
#define RENDERSYSTEMD3D9_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class RenderSystemD3D9
{
public:
	RenderSystemD3D9();
	~RenderSystemD3D9();

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

	inline IDirect3DDevice9* getD3D9Device() { return mD3DDevice; }

private:
	IDirect3D9* mD3D;
	IDirect3DDevice9* mD3DDevice;
	Real mClearColour[4];
	D3DXMATRIX mDxViewMat, mDxProjMat, mDxWorldMat;

}; // class RenderSystemD3D9
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // RENDERSYSTEMD3D9_H