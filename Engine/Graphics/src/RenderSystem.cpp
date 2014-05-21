//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Graphics/RenderSystem.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
RenderSystem::RenderSystem()
{
}
//------------------------------------------------------------------------------
RenderSystem::~RenderSystem()
{
	shutdown();
}
//------------------------------------------------------------------------------
bool RenderSystem::initialise(void* pHandle)
{
	shutdown();
	return Base::initialise(pHandle);
}
//------------------------------------------------------------------------------
void RenderSystem::shutdown()
{
	Base::shutdown();
}
//------------------------------------------------------------------------------
bool RenderSystem::beginScene(uint buffers)
{
	return Base::beginScene(buffers);
}
//------------------------------------------------------------------------------
bool RenderSystem::endScene()
{
	return Base::endScene();
}
//------------------------------------------------------------------------------
bool RenderSystem::clearScene(uint buffers)
{
	return Base::clearScene(buffers);
}
//------------------------------------------------------------------------------
bool RenderSystem::present()
{
	return Base::present();
}
//------------------------------------------------------------------------------
void RenderSystem::setClearColor(float red, float green, float blue, float alpha)
{
	Base::setClearColor(red, green, blue, alpha);
}
//------------------------------------------------------------------------------
bool RenderSystem::setWorldMatrix(const vmMatrix4& m)
{
	return Base::setWorldMatrix(m);
}
//------------------------------------------------------------------------------
bool RenderSystem::setViewMatrix(const vmMatrix4& m)
{
	return Base::setViewMatrix(m);
}
//------------------------------------------------------------------------------
bool RenderSystem::setProjectionMatrix(const vmMatrix4& m)
{
	return Base::setProjectionMatrix(m);
}
//------------------------------------------------------------------------------
bool RenderSystem::setAmbientLight(float red, float green, float blue)
{
	return Base::setAmbientLight(red, green, blue);
}
//------------------------------------------------------------------------------
bool RenderSystem::setShadingType(ShadeOptions so)
{
	return Base::setShadingType(so);
}
//------------------------------------------------------------------------------
bool RenderSystem::setLightingEnabled(bool enabled)
{
	return Base::setLightingEnabled(enabled);
}
//------------------------------------------------------------------------------
bool RenderSystem::setLight(size_t index, Light* light)
{
	return Base::setLight(index, light);
}
//------------------------------------------------------------------------------
bool RenderSystem::setLightEnabled(size_t index, bool enabled)
{
	return Base::setLightEnabled(index, enabled);
}
//------------------------------------------------------------------------------
bool RenderSystem::setBlending(SceneBlendFactor sourceFactor, SceneBlendFactor destFactor, SceneBlendOperation op)
{
	return Base::setBlending(sourceFactor, destFactor, op);
}
//------------------------------------------------------------------------------
bool RenderSystem::setBlendingSeparate(SceneBlendFactor sourceFactor, 
	SceneBlendFactor destFactor, SceneBlendFactor sourceFactorAlpha, 
	SceneBlendFactor destFactorAlpha, SceneBlendOperation op, 
	SceneBlendOperation alphaOp)
{
	return Base::setBlendingSeparate(sourceFactor, destFactor, sourceFactorAlpha, 
		destFactorAlpha, op, alphaOp);
}
//------------------------------------------------------------------------------
bool RenderSystem::setAlpha(CompareFunction func, unsigned char value)
{
	return Base::setAlpha(func, value);
}
//------------------------------------------------------------------------------
bool RenderSystem::setDepthEnabled(bool enabled)
{
	return Base::setDepthEnabled(enabled);
}
//------------------------------------------------------------------------------
bool RenderSystem::setDepthWriteEnabled(bool enabled)
{
	return Base::setDepthWriteEnabled(enabled);
}
//------------------------------------------------------------------------------
bool RenderSystem::setCullingMode(CullingMode mode)
{
	return Base::setCullingMode(mode);
}
//------------------------------------------------------------------------------
bool RenderSystem::setPolygonMode(PolygonMode level)
{
	return Base::setPolygonMode(level);
}
//------------------------------------------------------------------------------
bool RenderSystem::setStencilEnabled(bool enabled)
{
	return Base::setStencilEnabled(enabled);
}
//------------------------------------------------------------------------------
bool RenderSystem::setStencilParams(CompareFunction func, uint32 refValue, 
	uint32 mask, StencilOperation stencilFailOp, StencilOperation depthFailOp, 
	StencilOperation passOp, bool twoSidedOperation)
{
	return Base::setStencilParams(func, refValue, mask, stencilFailOp, 
		depthFailOp, passOp, twoSidedOperation);
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------