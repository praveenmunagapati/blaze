//=================================================================================================
/*!
//  \file blaze/util/typetraits/MakeUnsigned.h
//  \brief Header file for the MakeUnsigned type trait
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

#ifndef _BLAZE_UTIL_TYPETRAITS_MAKEUNSIGNED_H_
#define _BLAZE_UTIL_TYPETRAITS_MAKEUNSIGNED_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <boost/type_traits/make_unsigned.hpp>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\brief Compile time type conversion into an unsigned integral type.
// \ingroup type_traits
//
// This type trait provides the feature to convert the given integral or enumeration type \a T to
// the corresponding unsigned integral data type with the same size and with the same cv-qualifiers.
// Note that in case \a T is bool or a non-integral data type, a compilation error is created.

   \code
   enum MyEnum { ... };
   
   blaze::MakeUnsigned<int>::Type                  // Results in 'unsigned int'
   blaze::MakeUnsigned<const unsigned int>::Type   // Results in 'const unsigned int'
   blaze::MakeUnsigned<const unsigned long>::Type  // Results in 'const unsigned long'
   blaze::MakeUnsigned<MyEnum>::Type               // Unsigned integer type with the same width as the enum
   blaze::MakeUnsigned<wchar_t>::Type              // Unsigned integer type with the same width as wchar_t
   \endcode
*/
template< typename T >
struct MakeUnsigned
{
 public:
   //**********************************************************************************************
   /*! \cond BLAZE_INTERNAL */
   typedef typename boost::make_unsigned<T>::type  Type;
   /*! \endcond */
   //**********************************************************************************************
};
//*************************************************************************************************

} // namespace blaze

#endif
