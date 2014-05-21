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

#ifndef DANGINE_ASSERT_H
#define DANGINE_ASSERT_H

/// concatenates tokens, even when the tokens are macros themselves
#define DG_PP_JOIN_HELPER_HELPER(_0, _1)		_0##_1
#define DG_PP_JOIN_HELPER(_0, _1)				DG_PP_JOIN_HELPER_HELPER(_0, _1)
#define DG_PP_JOIN_IMPL(_0, _1)					DG_PP_JOIN_HELPER(_0, _1)

#define DG_PP_JOIN_2(_0, _1)																	DG_PP_JOIN_IMPL(_0, _1)
#define DG_PP_JOIN_3(_0, _1, _2)																DG_PP_JOIN_2(DG_PP_JOIN_2(_0, _1), _2)
#define DG_PP_JOIN_4(_0, _1, _2, _3)															DG_PP_JOIN_2(DG_PP_JOIN_3(_0, _1, _2), _3)
#define DG_PP_JOIN_5(_0, _1, _2, _3, _4)														DG_PP_JOIN_2(DG_PP_JOIN_4(_0, _1, _2, _3), _4)
#define DG_PP_JOIN_6(_0, _1, _2, _3, _4, _5)													DG_PP_JOIN_2(DG_PP_JOIN_5(_0, _1, _2, _3, _4), _5)
#define DG_PP_JOIN_7(_0, _1, _2, _3, _4, _5, _6)												DG_PP_JOIN_2(DG_PP_JOIN_6(_0, _1, _2, _3, _4, _5), _6)
#define DG_PP_JOIN_8(_0, _1, _2, _3, _4, _5, _6, _7)											DG_PP_JOIN_2(DG_PP_JOIN_7(_0, _1, _2, _3, _4, _5, _6), _7)
#define DG_PP_JOIN_9(_0, _1, _2, _3, _4, _5, _6, _7, _8)										DG_PP_JOIN_2(DG_PP_JOIN_8(_0, _1, _2, _3, _4, _5, _6, _7), _8)
#define DG_PP_JOIN_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9)									DG_PP_JOIN_2(DG_PP_JOIN_9(_0, _1, _2, _3, _4, _5, _6, _7, _8), _9)
#define DG_PP_JOIN_11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)								DG_PP_JOIN_2(DG_PP_JOIN_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _10)
#define DG_PP_JOIN_12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11)							DG_PP_JOIN_2(DG_PP_JOIN_11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _11)
#define DG_PP_JOIN_13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12)					DG_PP_JOIN_2(DG_PP_JOIN_12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _12)
#define DG_PP_JOIN_14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13)				DG_PP_JOIN_2(DG_PP_JOIN_13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _13)
#define DG_PP_JOIN_15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14)			DG_PP_JOIN_2(DG_PP_JOIN_14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _14)
#define DG_PP_JOIN_16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)		DG_PP_JOIN_2(DG_PP_JOIN_15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _15)


/// chooses a value based on a condition
#define DG_PP_IF_0(t, f)			f
#define DG_PP_IF_1(t, f)			t
#define DG_PP_IF(cond, t, f)		DG_PP_JOIN_2(DG_PP_IF_, DG_PP_TO_BOOL(cond))(t, f)


/// converts a condition into a boolean 0 (=false) or 1 (=true)
#define DG_PP_TO_BOOL_0 0
#define DG_PP_TO_BOOL_1 1
#define DG_PP_TO_BOOL_2 1
#define DG_PP_TO_BOOL_3 1
#define DG_PP_TO_BOOL_4 1
#define DG_PP_TO_BOOL_5 1
#define DG_PP_TO_BOOL_6 1
#define DG_PP_TO_BOOL_7 1
#define DG_PP_TO_BOOL_8 1
#define DG_PP_TO_BOOL_9 1
#define DG_PP_TO_BOOL_10 1
#define DG_PP_TO_BOOL_11 1
#define DG_PP_TO_BOOL_12 1
#define DG_PP_TO_BOOL_13 1
#define DG_PP_TO_BOOL_14 1
#define DG_PP_TO_BOOL_15 1
#define DG_PP_TO_BOOL_16 1

#define DG_PP_TO_BOOL(x)		DG_PP_JOIN_2(DG_PP_TO_BOOL_, x)


/// Returns 1 if the arguments to the variadic macro are separated by a comma, 0 otherwise.
#define DG_PP_HAS_COMMA(...)							DG_PP_HAS_COMMA_EVAL(DG_PP_HAS_COMMA_ARGS(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0))
#define DG_PP_HAS_COMMA_EVAL(...)						__VA_ARGS__
#define DG_PP_HAS_COMMA_ARGS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) _16


/// Returns 1 if the argument list to the variadic macro is empty, 0 otherwise.
#define DG_PP_IS_EMPTY(...)														\
	DG_PP_HAS_COMMA																\
	(																			\
		DG_PP_JOIN_5															\
		(																		\
			DG_PP_IS_EMPTY_CASE_,												\
			DG_PP_HAS_COMMA(__VA_ARGS__),										\
			DG_PP_HAS_COMMA(DG_PP_IS_EMPTY_BRACKET_TEST __VA_ARGS__),			\
			DG_PP_HAS_COMMA(__VA_ARGS__ (~)),									\
			DG_PP_HAS_COMMA(DG_PP_IS_EMPTY_BRACKET_TEST __VA_ARGS__ (~))		\
		)																		\
	)

#define DG_PP_IS_EMPTY_CASE_0001			,
#define DG_PP_IS_EMPTY_BRACKET_TEST(...)	,


// DG_PP_VA_NUM_ARGS() is a very nifty macro to retrieve the number of arguments handed to a variable-argument macro.
// unfortunately, VS 2010 still has this preprocessor bug which treats a __VA_ARGS__ argument as being one single parameter:
// https://connect.microsoft.com/VisualStudio/feedback/details/521844/variadic-macro-treating-va-args-as-a-single-parameter-for-other-macros#details
#if _MSC_VER >= 1400
#	define DG_PP_VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...)	N
#	define DG_PP_VA_NUM_ARGS_REVERSE_SEQUENCE			16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
#	define DG_PP_VA_NUM_ARGS_LEFT (
#	define DG_PP_VA_NUM_ARGS_RIGHT )
#	define DG_PP_VA_NUM_ARGS(...)						DG_PP_VA_NUM_ARGS_HELPER DG_PP_VA_NUM_ARGS_LEFT __VA_ARGS__, DG_PP_VA_NUM_ARGS_REVERSE_SEQUENCE DG_PP_VA_NUM_ARGS_RIGHT
#else
#	define DG_PP_VA_NUM_ARGS(...)						DG_PP_VA_NUM_ARGS_HELPER(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#	define DG_PP_VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...)	N
#endif

// DG_PP_NUM_ARGS correctly handles the case of 0 arguments
#define DG_PP_NUM_ARGS(...)								DG_PP_IF(DG_PP_IS_EMPTY(__VA_ARGS__), 0, DG_PP_VA_NUM_ARGS(__VA_ARGS__))


// DG_PP_PASS_ARGS passes __VA_ARGS__ as multiple parameters to another macro, working around the following bug:
// https://connect.microsoft.com/VisualStudio/feedback/details/521844/variadic-macro-treating-va-args-as-a-single-parameter-for-other-macros#details
#if _MSC_VER >= 1400
#	define DG_PP_PASS_ARGS_LEFT (
#	define DG_PP_PASS_ARGS_RIGHT )
#	define DG_PP_PASS_ARGS(...)							DG_PP_PASS_ARGS_LEFT __VA_ARGS__ DG_PP_PASS_ARGS_RIGHT
#else
#	define DG_PP_PASS_ARGS(...)							(__VA_ARGS__)
#endif


/// Expand any number of arguments into a list of operations called with those arguments
#define DG_PP_EXPAND_ARGS_0(op, empty)
#define DG_PP_EXPAND_ARGS_1(op, a1)																			op(a1, 0)
#define DG_PP_EXPAND_ARGS_2(op, a1, a2)																		op(a1, 0) op(a2, 1)
#define DG_PP_EXPAND_ARGS_3(op, a1, a2, a3)																	op(a1, 0) op(a2, 1) op(a3, 2)
#define DG_PP_EXPAND_ARGS_4(op, a1, a2, a3, a4)																op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3)
#define DG_PP_EXPAND_ARGS_5(op, a1, a2, a3, a4, a5)															op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4)
#define DG_PP_EXPAND_ARGS_6(op, a1, a2, a3, a4, a5, a6)														op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5)
#define DG_PP_EXPAND_ARGS_7(op, a1, a2, a3, a4, a5, a6, a7)													op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6)
#define DG_PP_EXPAND_ARGS_8(op, a1, a2, a3, a4, a5, a6, a7, a8)												op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7)
#define DG_PP_EXPAND_ARGS_9(op, a1, a2, a3, a4, a5, a6, a7, a8, a9)											op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8)
#define DG_PP_EXPAND_ARGS_10(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)									op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9)
#define DG_PP_EXPAND_ARGS_11(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11)								op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10)
#define DG_PP_EXPAND_ARGS_12(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12)							op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11)
#define DG_PP_EXPAND_ARGS_13(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13)					op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11) op(a13, 12)
#define DG_PP_EXPAND_ARGS_14(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14)				op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11) op(a13, 12) op(a14, 13)
#define DG_PP_EXPAND_ARGS_15(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15)			op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11) op(a13, 12) op(a14, 13) op(a15, 14)
#define DG_PP_EXPAND_ARGS_16(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16)		op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11) op(a13, 12) op(a14, 13) op(a15, 14) op(a16, 15)

#define DG_PP_EXPAND_ARGS(op, ...)		DG_PP_JOIN_2(DG_PP_EXPAND_ARGS_, DG_PP_NUM_ARGS(__VA_ARGS__)) DG_PP_PASS_ARGS(op, __VA_ARGS__)


/// Turns any legal C++ expression into nothing
#define DG_UNUSED_EXP_IMPL(symExpr, n)					, (void)sizeof((symExpr) == 0)
#define DG_UNUSED_EXP(...)								(void)sizeof(true) DG_PP_EXPAND_ARGS DG_PP_PASS_ARGS(DG_UNUSED_EXP_IMPL, __VA_ARGS__)

/// Breaks into the debugger (if it is attached)
#if !DG_MASTER
#	define DG_BREAKPOINT								((IsDebuggerPresent() != 0) ? __debugbreak() : DG_UNUSED_EXP(true))
#else
#	define DG_BREAKPOINT								DG_UNUSED_EXP(true)
#endif

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
class Assert
{
public:
	Assert(const char* file, int line, const char* format, ...);

	// integral types
	Assert& Variable(const char* const name, bool var);
	Assert& Variable(const char* const name, char var);
	Assert& Variable(const char* const name, signed char var);
	Assert& Variable(const char* const name, unsigned char var);
	Assert& Variable(const char* const name, short var);
	Assert& Variable(const char* const name, unsigned short var);
	Assert& Variable(const char* const name, int var);
	Assert& Variable(const char* const name, unsigned int var);
	Assert& Variable(const char* const name, long var);
	Assert& Variable(const char* const name, unsigned long var);
	Assert& Variable(const char* const name, long long var);
	Assert& Variable(const char* const name, unsigned long long var);
	Assert& Variable(const char* const name, float var);
	Assert& Variable(const char* const name, double var);

	// string literals / character arrays
	Assert& Variable(const char* const name, const char* const var);

	// generic pointers
	Assert& Variable(const char* const name, const void* const var);

private:
	const char* m_file;
	int m_line;
};
//------------------------------------------------------------------------------
namespace
{
	template <typename T>
	static void Dispatch(const char* file, int line, const char* format, const char* const name, const T value)
	{
		// TODO: log here
	}
}
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#define DG_ASSERT_ENABLED 1

#if DG_ASSERT_ENABLED
#	define DG_ASSERT_IMPL_VAR(variable, n)			.Variable(#variable, variable)
#	define DG_ASSERT_IMPL_VARS(...)					DG_PP_EXPAND_ARGS DG_PP_PASS_ARGS(DG_ASSERT_IMPL_VAR, __VA_ARGS__), DG_BREAKPOINT)
#	define DG_ASSERT(condition, format, ...)		(condition) ? DG_UNUSED_EXP(true) : (Dangine::Assert(__FILE__, __LINE__, "Assertion \"" #condition "\" failed. " format, __VA_ARGS__) DG_ASSERT_IMPL_VARS
#else
#	define DG_ASSERT(condition, format, ...)		DG_UNUSED_EXP(condition), DG_UNUSED_EXP(format), DG_UNUSED_EXP(__VA_ARGS__), DG_UNUSED_EXP
#endif


#endif // DANGINE_ASSERT_H

// Example usage:
// --------------

/*
int a = 5;
int b = 10;
DG_ASSERT(a < b, "A was not less than B, %s.", "sadly")(a, b);
*/