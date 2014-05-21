//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#ifndef AXISALIGNEDBOX_H
#define AXISALIGNEDBOX_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class AxisAlignedBox
{
public:
	AxisAlignedBox();
	AxisAlignedBox(const vmVector3& min, const vmVector3& max);
	~AxisAlignedBox();

	inline vmVector3 getMinimum() const
	{
		return vmVector3(mMinimum[0], mMinimum[1], mMinimum[2]);
	}
	inline vmVector3 getCenter() const
	{
		return vmVector3(
			(getMaximum().getX() + getMinimum().getX()) * 0.5f,
			(getMaximum().getY() + getMinimum().getY()) * 0.5f,
			(getMaximum().getZ() + getMinimum().getZ()) * 0.5f);
	}
	inline vmVector3 getSize() const
	{
		return vmVector3(mSize[0], mSize[1], mSize[2]);
	}
	inline vmVector3 getHalfSize() const
	{
		return getSize() * 0.5f;
	}
	inline vmVector3 getMaximum() const
	{
		return getMinimum() + getSize();
	}

	void setMinimumAndMaximum(const vmVector3& min, const vmVector3& max);
	void setMinimumAndSize(const vmVector3& min, const vmVector3& size);

private:
	Real mMinimum[3];
	Real mSize[3];

}; // class AxisAlignedBox
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // AXISALIGNEDBOX_H