//------------------------------------------------------------------------------
// Created by Daniel Sefton
//------------------------------------------------------------------------------

#include "Platform/StableHeaders.h"

#include "Util/Math/AxisAlignedBox.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
AxisAlignedBox::AxisAlignedBox()
{
	for (uint i = 0; i < 3; i++)
		mMinimum[i] = mSize[i] = 0.0f;
}
//------------------------------------------------------------------------------
AxisAlignedBox::AxisAlignedBox(const vmVector3& min, const vmVector3& max)
{
	setMinimumAndMaximum(min, max);
}
//------------------------------------------------------------------------------
AxisAlignedBox::~AxisAlignedBox()
{
}
//------------------------------------------------------------------------------
void AxisAlignedBox::setMinimumAndMaximum(const vmVector3& min, const vmVector3& max)
{
	setMinimumAndSize(min, max - min);
}
//------------------------------------------------------------------------------
void AxisAlignedBox::setMinimumAndSize(const vmVector3& min, const vmVector3& size)
{
	bool cond = (size.getX() >= 0.0f) || (size.getY() >= 0.0f) || (size.getZ() >= 0.0f);
	DG_ASSERT(cond, "Size is not positive.")(cond);

	mMinimum[0] = min.getX();
	mMinimum[1] = min.getY();
	mMinimum[2] = min.getZ();

	mSize[0] = size.getX();
	mSize[1] = size.getY();
	mSize[2] = size.getZ();
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------