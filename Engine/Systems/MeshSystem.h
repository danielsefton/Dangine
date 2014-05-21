//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef MESHSYSTEM_H
#define MESHSYSTEM_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/System.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class MeshSystem : public System
{
public:
	MeshSystem(ComponentType type);
	~MeshSystem();

	std::vector<Real> getVertices(Entity& rEntity);
	std::vector<short> getIndices(Entity& rEntity);
	AxisAlignedBox getBoundingBox(Entity& rEntity) const;
	Real getBoundingRadius(Entity& rEntity) const;

	inline void setRenderSystem(RenderSystem* pRenderSystem)
	{
		mRenderSystem = pRenderSystem;
	}
	inline void setCamera(Camera* pCamera)
	{
		mCamera = pCamera;
	}
	inline void setLight(Light* pLight)
	{
		mLight = pLight;
	}

	static const ComponentType type = COMPONENTTYPE_MESH;

private:
	void _initialise(Entity& rEntity);
	void _destroy(Entity& rEntity);
	void _process(Entity& rEntity);

	RenderSystem* mRenderSystem;
	Camera* mCamera;
	Light* mLight;

}; // class MeshSystem
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // MESHSYSTEM_H