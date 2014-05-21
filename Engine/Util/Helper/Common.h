/*
-----------------------------------------------------------------------------
This source file is part of OGRE
	(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2012 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef COMMON_H
#define COMMON_H

#include "Platform/Prerequisites.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
/**
 * Enumerator which specifies the network mode.
 */
enum NetworkMode
{
	NM_CLIENT = 0,
	NM_SERVER = 1
};
//------------------------------------------------------------------------------
enum LightTypes
{
	LT_POINT = 0, 
	LT_DIRECTIONAL = 1, 
	LT_SPOTLIGHT = 2
};
//------------------------------------------------------------------------------
	/** Comparison functions used for the depth/stencil buffer operations and 
		others. */
	enum CompareFunction
	{
		CMPF_ALWAYS_FAIL,
		CMPF_ALWAYS_PASS,
		CMPF_LESS,
		CMPF_LESS_EQUAL,
		CMPF_EQUAL,
		CMPF_NOT_EQUAL,
		CMPF_GREATER_EQUAL,
		CMPF_GREATER
	};

	/** High-level filtering options providing shortcuts to settings the
		minification, magnification and mip filters. */
	enum TextureFilterOptions
	{
		/// Equal to: min=FO_POINT, mag=FO_POINT, mip=FO_NONE
		TFO_NONE,
		/// Equal to: min=FO_LINEAR, mag=FO_LINEAR, mip=FO_POINT
		TFO_BILINEAR,
		/// Equal to: min=FO_LINEAR, mag=FO_LINEAR, mip=FO_LINEAR
		TFO_TRILINEAR,
		/// Equal to: min=FO_ANISOTROPIC, max=FO_ANISOTROPIC, mip=FO_LINEAR
		TFO_ANISOTROPIC
	};

	enum FilterType
	{
		/// The filter used when shrinking a texture
		FT_MIN,
		/// The filter used when magnifying a texture
		FT_MAG,
		/// The filter used when determining the mipmap
		FT_MIP
	};
	/** Filtering options for textures / mipmaps. */
	enum FilterOptions
	{
		/// No filtering, used for FILT_MIP to turn off mipmapping
		FO_NONE,
		/// Use the closest pixel
		FO_POINT,
		/// Average of a 2x2 pixel area, denotes bilinear for MIN and MAG, trilinear for MIP
		FO_LINEAR,
		/// Similar to FO_LINEAR, but compensates for the angle of the texture plane
		FO_ANISOTROPIC
	};

	/** Light shading modes. */
	enum ShadeOptions
	{
		SO_FLAT,
		SO_GOURAUD,
		SO_PHONG
	};

	/** Fog modes. */
	enum FogMode
	{
		/// No fog. Duh.
		FOG_NONE,
		/// Fog density increases  exponentially from the camera (fog = 1/e^(distance * density))
		FOG_EXP,
		/// Fog density increases at the square of FOG_EXP, i.e. even quicker (fog = 1/e^(distance * density)^2)
		FOG_EXP2,
		/// Fog density increases linearly between the start and end distances
		FOG_LINEAR
	};

	/** Hardware culling modes based on vertex winding.
		This setting applies to how the hardware API culls triangles it is sent. */
	enum CullingMode
	{
		/// Hardware never culls triangles and renders everything it receives.
		CULL_NONE = 1,
		/// Hardware culls triangles whose vertices are listed clockwise in the view (default).
		CULL_CLOCKWISE = 2,
		/// Hardware culls triangles whose vertices are listed anticlockwise in the view.
		CULL_ANTICLOCKWISE = 3
	};

	/** Manual culling modes based on vertex normals.
		This setting applies to how the software culls triangles before sending them to the 
		hardware API. This culling mode is used by scene managers which choose to implement it -
		normally those which deal with large amounts of fixed world geometry which is often 
		planar (software culling movable variable geometry is expensive). */
	enum ManualCullingMode
	{
		/// No culling so everything is sent to the hardware.
		MANUAL_CULL_NONE = 1,
		/// Cull triangles whose normal is pointing away from the camera (default).
		MANUAL_CULL_BACK = 2,
		/// Cull triangles whose normal is pointing towards the camera.
		MANUAL_CULL_FRONT = 3
	};

	/** Enumerates the wave types usable with the Ogre engine. */
	enum WaveformType
	{
		/// Standard sine wave which smoothly changes from low to high and back again.
		WFT_SINE,
		/// An angular wave with a constant increase / decrease speed with pointed peaks.
		WFT_TRIANGLE,
		/// Half of the time is spent at the min, half at the max with instant transition between.
		WFT_SQUARE,
		/// Gradual steady increase from min to max over the period with an instant return to min at the end.
		WFT_SAWTOOTH,
		/// Gradual steady decrease from max to min over the period, with an instant return to max at the end.
		WFT_INVERSE_SAWTOOTH,
		/// Pulse Width Modulation. Works like WFT_SQUARE, except the high to low transition is controlled by duty cycle. 
		/// With a duty cycle of 50% (0.5) will give the same output as WFT_SQUARE.
		WFT_PWM
	};

	/** The polygon mode to use when rasterising. */
	enum PolygonMode
	{
		/// Only points are rendered.
		PM_POINTS = 1,
		/// Wireframe models are rendered.
		PM_WIREFRAME = 2,
		/// Solid polygons are rendered.
		PM_SOLID = 3
	};

	/** An enumeration of broad shadow techniques */
	enum ShadowTechnique
	{
		/** No shadows */
		SHADOWTYPE_NONE = 0x00,
		/** Mask for additive shadows (not for direct use, use  SHADOWTYPE_ enum instead)
		*/
		SHADOWDETAILTYPE_ADDITIVE = 0x01,
		/** Mask for modulative shadows (not for direct use, use  SHADOWTYPE_ enum instead)
		*/
		SHADOWDETAILTYPE_MODULATIVE = 0x02,
		/** Mask for integrated shadows (not for direct use, use SHADOWTYPE_ enum instead)
		*/
		SHADOWDETAILTYPE_INTEGRATED = 0x04,
		/** Mask for stencil shadows (not for direct use, use  SHADOWTYPE_ enum instead)
		*/
		SHADOWDETAILTYPE_STENCIL = 0x10,
		/** Mask for texture shadows (not for direct use, use  SHADOWTYPE_ enum instead)
		*/
		SHADOWDETAILTYPE_TEXTURE = 0x20,
		
		/** Stencil shadow technique which renders all shadow volumes as
			a modulation after all the non-transparent areas have been 
			rendered. This technique is considerably less fillrate intensive 
			than the additive stencil shadow approach when there are multiple
			lights, but is not an accurate model. 
		*/
		SHADOWTYPE_STENCIL_MODULATIVE = 0x12,
		/** Stencil shadow technique which renders each light as a separate
			additive pass to the scene. This technique can be very fillrate
			intensive because it requires at least 2 passes of the entire
			scene, more if there are multiple lights. However, it is a more
			accurate model than the modulative stencil approach and this is
			especially apparent when using coloured lights or bump mapping.
		*/
		SHADOWTYPE_STENCIL_ADDITIVE = 0x11,
		/** Texture-based shadow technique which involves a monochrome render-to-texture
			of the shadow caster and a projection of that texture onto the 
			shadow receivers as a modulative pass. 
		*/
		SHADOWTYPE_TEXTURE_MODULATIVE = 0x22,
		
		/** Texture-based shadow technique which involves a render-to-texture
			of the shadow caster and a projection of that texture onto the 
			shadow receivers, built up per light as additive passes. 
			This technique can be very fillrate intensive because it requires numLights + 2 
			passes of the entire scene. However, it is a more accurate model than the 
			modulative approach and this is especially apparent when using coloured lights 
			or bump mapping.
		*/
		SHADOWTYPE_TEXTURE_ADDITIVE = 0x21,

		/** Texture-based shadow technique which involves a render-to-texture
		of the shadow caster and a projection of that texture on to the shadow
		receivers, with the usage of those shadow textures completely controlled
		by the materials of the receivers.
		This technique is easily the most flexible of all techniques because 
		the material author is in complete control over how the shadows are
		combined with regular rendering. It can perform shadows as accurately
		as SHADOWTYPE_TEXTURE_ADDITIVE but more efficiently because it requires
		less passes. However it also requires more expertise to use, and 
		in almost all cases, shader capable hardware to really use to the full.
		@note The 'additive' part of this mode means that the colour of
		the rendered shadow texture is by default plain black. It does
		not mean it does the adding on your receivers automatically though, how you
		use that result is up to you.
		*/
		SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED = 0x25,
		/** Texture-based shadow technique which involves a render-to-texture
			of the shadow caster and a projection of that texture on to the shadow
			receivers, with the usage of those shadow textures completely controlled
			by the materials of the receivers.
			This technique is easily the most flexible of all techniques because 
			the material author is in complete control over how the shadows are
			combined with regular rendering. It can perform shadows as accurately
			as SHADOWTYPE_TEXTURE_ADDITIVE but more efficiently because it requires
			less passes. However it also requires more expertise to use, and 
			in almost all cases, shader capable hardware to really use to the full.
			@note The 'modulative' part of this mode means that the colour of
			the rendered shadow texture is by default the 'shadow colour'. It does
			not mean it modulates on your receivers automatically though, how you
			use that result is up to you.
		*/
		SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED = 0x26
	};

	/** An enumeration describing which material properties should track the vertex colours */
	typedef int TrackVertexColourType;
	enum TrackVertexColourEnum {
		TVC_NONE		= 0x0,
		TVC_AMBIENT	 = 0x1,		
		TVC_DIFFUSE	 = 0x2,
		TVC_SPECULAR	= 0x4,
		TVC_EMISSIVE	= 0x8
	};

	/** Sort mode for billboard-set and particle-system */
	enum SortMode
	{
		/** Sort by direction of the camera */
		SM_DIRECTION,
		/** Sort by distance from the camera */
		SM_DISTANCE
	};

	/** Defines the frame buffer types. */
	enum FrameBufferType {
		FBT_COLOUR  = 0x1,
		FBT_DEPTH   = 0x2,
		FBT_STENCIL = 0x4
	};
//------------------------------------------------------------------------------
	/** Type of texture blend mode.
	*/
	enum LayerBlendType
	{
		LBT_COLOUR,
		LBT_ALPHA
	};

	/** List of valid texture blending operations, for use with TextureUnitState::setColourOperation.
		@remarks
			This list is a more limited list than LayerBlendOperationEx because it only
			includes operations that are supportable in both multipass and multitexture
			rendering and thus provides automatic fallback if multitexture hardware
			is lacking or insufficient.
	*/
	enum LayerBlendOperation {
		/// Replace all colour with texture with no adjustment
		LBO_REPLACE,
		/// Add colour components together.
		LBO_ADD,
		/// Multiply colour components together.
		LBO_MODULATE,
		/// Blend based on texture alpha
		LBO_ALPHA_BLEND

	};

	/** Expert list of valid texture blending operations, for use with TextureUnitState::setColourOperationEx
		and TextureUnitState::setAlphaOperation, and internally in the LayerBlendModeEx class. It's worth
		noting that these operations are for blending <i>between texture layers</i> and not between rendered objects
		and the existing scene. Because all of these modes are only supported in multitexture hardware it may be
		required to set up a fallback operation where this hardware is not available.
	*/
	enum LayerBlendOperationEx {
		/// use source1 without modification
		LBX_SOURCE1,
		/// use source2 without modification
		LBX_SOURCE2,
		/// multiply source1 and source2 together
		LBX_MODULATE,
		/// as LBX_MODULATE but brighten afterwards (x2)
		LBX_MODULATE_X2,
		/// as LBX_MODULATE but brighten more afterwards (x4)
		LBX_MODULATE_X4,
		/// add source1 and source2 together
		LBX_ADD,
		/// as LBX_ADD, but subtract 0.5 from the result
		LBX_ADD_SIGNED,
		/// as LBX_ADD, but subtract product from the sum
		LBX_ADD_SMOOTH,
		/// subtract source2 from source1
		LBX_SUBTRACT,
		/// use interpolated alpha value from vertices to scale source1, then add source2 scaled by (1-alpha)
		LBX_BLEND_DIFFUSE_ALPHA,
		/// as LBX_BLEND_DIFFUSE_ALPHA, but use alpha from texture
		LBX_BLEND_TEXTURE_ALPHA,
		/// as LBX_BLEND_DIFFUSE_ALPHA, but use current alpha from previous stages
		LBX_BLEND_CURRENT_ALPHA,
		/// as LBX_BLEND_DIFFUSE_ALPHA but use a constant manual blend value (0.0-1.0)
		LBX_BLEND_MANUAL,
		/// dot product of color1 and color2 
		LBX_DOTPRODUCT,
		/// use interpolated color values from vertices to scale source1, then add source2 scaled by (1-color)
		LBX_BLEND_DIFFUSE_COLOUR
	};

	/** List of valid sources of values for blending operations used
		in TextureUnitState::setColourOperation and TextureUnitState::setAlphaOperation,
		and internally in the LayerBlendModeEx class.
	*/
	enum LayerBlendSource
	{
		/// the colour as built up from previous stages
		LBS_CURRENT,
		/// the colour derived from the texture assigned to this layer
		LBS_TEXTURE,
		/// the interpolated diffuse colour from the vertices
		LBS_DIFFUSE,
		/// the interpolated specular colour from the vertices
		LBS_SPECULAR,
		/// a colour supplied manually as a separate argument
		LBS_MANUAL
	};

	/** Types of blending that you can specify between an object and the existing contents of the scene.
		@remarks
			As opposed to the LayerBlendType, which classifies blends between texture layers, these blending
			types blend between the output of the texture units and the pixels already in the viewport,
			allowing for object transparency, glows, etc.
		@par
			These types are provided to give quick and easy access to common effects. You can also use
			the more manual method of supplying source and destination blending factors.
			See Material::setSceneBlending for more details.
		@see
			Material::setSceneBlending
	*/
	enum SceneBlendType
	{
		/// Make the object transparent based on the final alpha values in the texture
		SBT_TRANSPARENT_ALPHA,
		/// Make the object transparent based on the colour values in the texture (brighter = more opaque)
		SBT_TRANSPARENT_COLOUR,
		/// Add the texture values to the existing scene content
		SBT_ADD,
		/// Multiply the 2 colours together
		SBT_MODULATE,
		/// The default blend mode where source replaces destination
		SBT_REPLACE
		// TODO : more
	};

	/** Blending factors for manually blending objects with the scene. If there isn't a predefined
		SceneBlendType that you like, then you can specify the blending factors directly to affect the
		combination of object and the existing scene. See Material::setSceneBlending for more details.
	*/
	enum SceneBlendFactor
	{
		SBF_ONE,
		SBF_ZERO,
		SBF_DEST_COLOUR,
		SBF_SOURCE_COLOUR,
		SBF_ONE_MINUS_DEST_COLOUR,
		SBF_ONE_MINUS_SOURCE_COLOUR,
		SBF_DEST_ALPHA,
		SBF_SOURCE_ALPHA,
		SBF_ONE_MINUS_DEST_ALPHA,
		SBF_ONE_MINUS_SOURCE_ALPHA

	};

	/** Blending operations controls how objects are blended into the scene. The default operation
		is add (+) but by changing this you can change how drawn objects are blended into the
		existing scene.
	*/
	enum SceneBlendOperation
	{
		SBO_ADD,
		SBO_SUBTRACT,
		SBO_REVERSE_SUBTRACT,
		SBO_MIN,
		SBO_MAX
	};
	/** @} */
	/** @} */
//------------------------------------------------------------------------------
	/// Enum describing the various actions which can be taken onthe stencil buffer
	enum StencilOperation
	{
		/// Leave the stencil buffer unchanged
		SOP_KEEP,
		/// Set the stencil value to zero
		SOP_ZERO,
		/// Set the stencil value to the reference value
		SOP_REPLACE,
		/// Increase the stencil value by 1, clamping at the maximum value
		SOP_INCREMENT,
		/// Decrease the stencil value by 1, clamping at 0
		SOP_DECREMENT,
		/// Increase the stencil value by 1, wrapping back to 0 when incrementing the maximum value
		SOP_INCREMENT_WRAP,
		/// Decrease the stencil value by 1, wrapping when decrementing 0
		SOP_DECREMENT_WRAP,
		/// Invert the bits of the stencil buffer
		SOP_INVERT
	};
//------------------------------------------------------------------------------
	enum PixelFormat
	{
		/// Unknown pixel format.
		PF_UNKNOWN = 0,
		/// 8-bit pixel format, all bits luminance.
		PF_L8 = 1,
		PF_BYTE_L = PF_L8,
		/// 16-bit pixel format, all bits luminance.
		PF_L16 = 2,
		PF_SHORT_L = PF_L16,
		/// 8-bit pixel format, all bits alpha.
		PF_A8 = 3,
		PF_BYTE_A = PF_A8,
		/// 8-bit pixel format, 4 bits alpha, 4 bits luminance.
		PF_A4L4 = 4,
		/// 2 byte pixel format, 1 byte luminance, 1 byte alpha
		PF_BYTE_LA = 5,
		/// 16-bit pixel format, 5 bits red, 6 bits green, 5 bits blue.
		PF_R5G6B5 = 6,
		/// 16-bit pixel format, 5 bits red, 6 bits green, 5 bits blue.
		PF_B5G6R5 = 7,
		/// 8-bit pixel format, 2 bits blue, 3 bits green, 3 bits red.
		PF_R3G3B2 = 31,
		/// 16-bit pixel format, 4 bits for alpha, red, green and blue.
		PF_A4R4G4B4 = 8,
		/// 16-bit pixel format, 5 bits for blue, green, red and 1 for alpha.
		PF_A1R5G5B5 = 9,
		/// 24-bit pixel format, 8 bits for red, green and blue.
		PF_R8G8B8 = 10,
		/// 24-bit pixel format, 8 bits for blue, green and red.
		PF_B8G8R8 = 11,
		/// 32-bit pixel format, 8 bits for alpha, red, green and blue.
		PF_A8R8G8B8 = 12,
		/// 32-bit pixel format, 8 bits for blue, green, red and alpha.
		PF_A8B8G8R8 = 13,
		/// 32-bit pixel format, 8 bits for blue, green, red and alpha.
		PF_B8G8R8A8 = 14,
		/// 32-bit pixel format, 8 bits for red, green, blue and alpha.
		PF_R8G8B8A8 = 28,
		/// 32-bit pixel format, 8 bits for red, 8 bits for green, 8 bits for blue
		/// like PF_A8R8G8B8, but alpha will get discarded
		PF_X8R8G8B8 = 26,
		/// 32-bit pixel format, 8 bits for blue, 8 bits for green, 8 bits for red
		/// like PF_A8B8G8R8, but alpha will get discarded
		PF_X8B8G8R8 = 27,
#if OGRE_ENDIAN == OGRE_ENDIAN_BIG
		/// 3 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue
		PF_BYTE_RGB = PF_R8G8B8,
		/// 3 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red
		PF_BYTE_BGR = PF_B8G8R8,
		/// 4 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red and one byte for alpha
		PF_BYTE_BGRA = PF_B8G8R8A8,
		/// 4 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue, and one byte for alpha
		PF_BYTE_RGBA = PF_R8G8B8A8,
#else
		/// 3 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue
		PF_BYTE_RGB = PF_B8G8R8,
		/// 3 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red
		PF_BYTE_BGR = PF_R8G8B8,
		/// 4 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red and one byte for alpha
		PF_BYTE_BGRA = PF_A8R8G8B8,
		/// 4 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue, and one byte for alpha
		PF_BYTE_RGBA = PF_A8B8G8R8,
#endif		
		/// 32-bit pixel format, 2 bits for alpha, 10 bits for red, green and blue.
		PF_A2R10G10B10 = 15,
		/// 32-bit pixel format, 10 bits for blue, green and red, 2 bits for alpha.
		PF_A2B10G10R10 = 16,
		/// DDS (DirectDraw Surface) DXT1 format
		PF_DXT1 = 17,
		/// DDS (DirectDraw Surface) DXT2 format
		PF_DXT2 = 18,
		/// DDS (DirectDraw Surface) DXT3 format
		PF_DXT3 = 19,
		/// DDS (DirectDraw Surface) DXT4 format
		PF_DXT4 = 20,
		/// DDS (DirectDraw Surface) DXT5 format
		PF_DXT5 = 21,
		// 16-bit pixel format, 16 bits (float) for red
		PF_FLOAT16_R = 32,
		// 48-bit pixel format, 16 bits (float) for red, 16 bits (float) for green, 16 bits (float) for blue
		PF_FLOAT16_RGB = 22,
		// 64-bit pixel format, 16 bits (float) for red, 16 bits (float) for green, 16 bits (float) for blue, 16 bits (float) for alpha
		PF_FLOAT16_RGBA = 23,
				// 32-bit pixel format, 32 bits (float) for red
		PF_FLOAT32_R = 33,
		// 96-bit pixel format, 32 bits (float) for red, 32 bits (float) for green, 32 bits (float) for blue
		PF_FLOAT32_RGB = 24,
		// 128-bit pixel format, 32 bits (float) for red, 32 bits (float) for green, 32 bits (float) for blue, 32 bits (float) for alpha
		PF_FLOAT32_RGBA = 25,
		// 32-bit, 2-channel s10e5 floating point pixel format, 16-bit green, 16-bit red
		PF_FLOAT16_GR = 35,
		// 64-bit, 2-channel floating point pixel format, 32-bit green, 32-bit red
		PF_FLOAT32_GR = 36,
		// Depth texture format
		PF_DEPTH = 29,
		// 64-bit pixel format, 16 bits for red, green, blue and alpha
		PF_SHORT_RGBA = 30,
		// 32-bit pixel format, 16-bit green, 16-bit red
		PF_SHORT_GR = 34,
		// 48-bit pixel format, 16 bits for red, green and blue
		PF_SHORT_RGB = 37,
		/// PVRTC (PowerVR) RGB 2 bpp
		PF_PVRTC_RGB2 = 38,
		/// PVRTC (PowerVR) RGBA 2 bpp
		PF_PVRTC_RGBA2 = 39,
		/// PVRTC (PowerVR) RGB 4 bpp
		PF_PVRTC_RGB4 = 40,
		/// PVRTC (PowerVR) RGBA 4 bpp
		PF_PVRTC_RGBA4 = 41,
		/// 8-bit pixel format, all bits red.
		PF_R8 = 42,
		/// 16-bit pixel format, 8 bits red, 8 bits green.
		PF_RG8 = 43,
				// Number of pixel formats currently defined
		PF_COUNT = 44
	};
		typedef std::vector<PixelFormat> PixelFormatList;

	/**
	 * Flags defining some on/off properties of pixel formats
	 */
	enum PixelFormatFlags {
		// This format has an alpha channel
		PFF_HASALPHA		= 0x00000001,	  
		// This format is compressed. This invalidates the values in elemBytes,
		// elemBits and the bit counts as these might not be fixed in a compressed format.
		PFF_COMPRESSED	= 0x00000002,
		// This is a floating point format
		PFF_FLOAT		   = 0x00000004,		 
		// This is a depth format (for depth textures)
		PFF_DEPTH		   = 0x00000008,
		// Format is in native endian. Generally true for the 16, 24 and 32 bits
		// formats which can be represented as machine integers.
		PFF_NATIVEENDIAN	= 0x00000010,
		// This is an intensity format instead of a RGB one. The luminance
		// replaces R,G and B. (but not A)
		PFF_LUMINANCE	   = 0x00000020
	};
	
	/** Pixel component format */
	enum PixelComponentType
	{
		PCT_BYTE = 0,	/// Byte per component (8 bit fixed 0.0..1.0)
		PCT_SHORT = 1,   /// Short per component (16 bit fixed 0.0..1.0))
		PCT_FLOAT16 = 2, /// 16 bit float per component
		PCT_FLOAT32 = 3, /// 32 bit float per component
		PCT_COUNT = 4	/// Number of pixel types
	};
//------------------------------------------------------------------------------
typedef std::map<String, String> NameValuePairList;
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // COMMON_H