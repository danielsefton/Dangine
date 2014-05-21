//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef LIGHT_H
#define LIGHT_H

#include "Platform/Prerequisites.h"

#include "Util/Entity/Component.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
struct Light : public Component
{
	static const ComponentType type = COMPONENTTYPE_LIGHT;

	Light(uint num)
		: num(num)
		, lightType(LT_POINT)
		, diffuse(vmVector4(1.0f, 1.0f, 1.0f, 1.0f))
		, specular(vmVector4(0.0f, 0.0f, 0.0f, 1.0f))
		, ambient(vmVector4(0.5f, 0.5f, 0.5f, 1.0f))
		, position(vmVector3(0.0f, 0.0f, 0.0f))
		, direction(vmVector3(0.0f, 0.0f, 1.0f))
		, range(100000.0f)
		, falloff(1.0f)
		, attenuation0(1.0f)
		, attenuation1(0.0f)
		, attenuation2(0.0f)
		, theta(0.5f)
		, phi(1.0f)
	{
	}

	uint num;
	LightTypes lightType;
	vmVector4 diffuse;
	vmVector4 specular;
	vmVector4 ambient;
	vmVector3 position;
	vmVector3 direction;
	Real range;
	Real falloff;
	Real attenuation0;
	Real attenuation1;
	Real attenuation2;
	Real theta;
	Real phi;
};
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // LIGHT_H