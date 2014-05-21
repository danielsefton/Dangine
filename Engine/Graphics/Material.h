//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
struct Material
{
	Material()
		: ambient(vmVector4(0.5f, 0.5f, 0.5f, 1.f))
		, diffuse(vmVector4(0.7f, 0.7f, 0.7f, 1.f))
		, specular(vmVector4(1.f, 1.f, 1.f, 1.f))
		, emissive(vmVector4(0.f, 0.f, 0.f, 1.f))
		, shininess(1.0f)
		, textures(0)
	{
	}
	vmVector4 ambient;
	vmVector4 diffuse;
	vmVector4 specular;
	vmVector4 emissive;
	Real shininess;
	std::vector<String> textureFiles;
	LPDIRECT3DTEXTURE9* textures;
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // MATERIAL_H