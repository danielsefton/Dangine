/*
	Copyright (c) 2011, Stefan Reinalter

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

	3. This notice may not be removed or altered from any source
	distribution.
*/

#include "Platform/StableHeaders.h"

#include "Util/Helper/Assert.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
Assert::Assert(const char* file, int line, const char* format, ...)
	: m_file(file)
	, m_line(line)
{
	va_list argptr;
	va_start(argptr, format);

	// TODO: log here

	va_end(argptr);
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, bool var)
{
	Dispatch(m_file, m_line, "Variable %s = %s (bool)", name, var ? "true" : "false");
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, char var)
{
	Dispatch(m_file, m_line, "Variable %s = %d (char)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, signed char var)
{
	Dispatch(m_file, m_line, "Variable %s = %d (signed char)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, unsigned char var)
{
	Dispatch(m_file, m_line, "Variable %s = %u (unsigned char)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, short var)
{
	Dispatch(m_file, m_line, "Variable %s = %d (short)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, unsigned short var)
{
	Dispatch(m_file, m_line, "Variable %s = %u (unsigned short)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, int var)
{
	Dispatch(m_file, m_line, "Variable %s = %d (int)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, unsigned int var)
{
	Dispatch(m_file, m_line, "Variable %s = %u (unsigned int)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, long var)
{
	Dispatch(m_file, m_line, "Variable %s = %ld (long)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, unsigned long var)
{
	Dispatch(m_file, m_line, "Variable %s = %lu (unsigned long)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, long long var)
{
	Dispatch(m_file, m_line, "Variable %s = %lld (long long)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, unsigned long long var)
{
	Dispatch(m_file, m_line, "Variable %s = %llu (unsigned long long)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, float var)
{
	Dispatch(m_file, m_line, "Variable %s = %f (float)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, double var)
{
	Dispatch(m_file, m_line, "Variable %s = %f (double)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, const char* const var)
{
	Dispatch(m_file, m_line, "Variable %s = \"%s\" (const char*)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
Assert& Assert::Variable(const char* const name, const void* const var)
{
	Dispatch(m_file, m_line, "Variable %s = 0x%X (pointer)", name, var);
	return *this;
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------