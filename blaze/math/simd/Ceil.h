//=================================================================================================
/*!
//  \file blaze/math/simd/Ceil.h
//  \brief Header file for the SIMD ceil functionality
//
//  Copyright (C) 2013 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_SIMD_CEIL_H_
#define _BLAZE_MATH_SIMD_CEIL_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/simd/BasicTypes.h>
#include <blaze/system/Inline.h>
#include <blaze/system/Vectorization.h>


namespace blaze {

//=================================================================================================
//
//  INTRINSIC CEIL FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\fn simd_float_t ceil( simd_float_t )
// \brief Computes the largest integer value not less than the given value for a vector of single
//        precision floating point values.
// \ingroup simd
//
// \param a The vector of single precision floating point values.
// \return The resulting vector.
*/
#if BLAZE_MIC_MODE && ( defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC) )
BLAZE_ALWAYS_INLINE simd_float_t ceil( const simd_float_t& a ) noexcept
{
   return _mm512_ceil_ps( a.value );
}
#elif BLAZE_AVX_MODE
BLAZE_ALWAYS_INLINE simd_float_t ceil( const simd_float_t& a ) noexcept
{
   return _mm256_ceil_ps( a.value );
}
#elif BLAZE_SSE4_MODE
BLAZE_ALWAYS_INLINE simd_float_t ceil( const simd_float_t& a ) noexcept
{
   return _mm_ceil_ps( a.value );
}
#endif
//*************************************************************************************************


//*************************************************************************************************
/*!\fn simd_double_t ceil( simd_double_t )
// \brief Computes the largest integer value not less than the given value for a vector of double
//        precision floating point values.
// \ingroup simd
//
// \param a The vector of double precision floating point values.
// \return The resulting vector.
*/
#if BLAZE_MIC_MODE && ( defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC) )
BLAZE_ALWAYS_INLINE simd_double_t ceil( const simd_double_t& a ) noexcept
{
   return _mm512_ceil_pd( a.value );
}
#elif BLAZE_AVX_MODE
BLAZE_ALWAYS_INLINE simd_double_t ceil( const simd_double_t& a ) noexcept
{
   return _mm256_ceil_pd( a.value );
}
#elif BLAZE_SSE4_MODE
BLAZE_ALWAYS_INLINE simd_double_t ceil( const simd_double_t& a ) noexcept
{
   return _mm_ceil_pd( a.value );
}
#endif
//*************************************************************************************************

} // namespace blaze

#endif