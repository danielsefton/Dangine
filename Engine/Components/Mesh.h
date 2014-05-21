//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/Component.h"
#include "Graphics/Material.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
struct Mesh : public Component
{
	static const ComponentType type = COMPONENTTYPE_MESH;

	Mesh()
		: file("")
		, effectFile("")
		, mesh(0)
		, effect(0)
	{
	}

	// Mesh file
	std::string file;
	// Effect file
	std::string effectFile;
	// Materials
	std::vector<Material> materials;
	/// Our mesh object in system
	LPD3DXMESH mesh;
	/// Effect
	ID3DXEffect* effect;
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // MESH_H