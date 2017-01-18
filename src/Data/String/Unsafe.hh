///////////////////////////////////////////////////////////////////////////////
//
// Module      :  Coerce.hh
// Copyright   :  (c) Andy Arvanitis 2016
// License     :  MIT
//
// Maintainer  :  Andy Arvanitis <andy.arvanitis@gmail.com>
// Stability   :  experimental
// Portability :
//
// String_Unsafe FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#ifndef Data_String_Unsafe_FFI_HH
#define Data_String_Unsafe_FFI_HH

#include "PureScript/PureScript.hh"

namespace Data_String_Unsafe {
  using namespace PureScript;

  // foreign import charCodeAt :: Int -> String -> Int
  //
  auto charCodeAt(const int, const string&) -> int;

  // foreign import charAt :: Int -> String -> Char
  //
  auto charAt(const int, const string&) -> char32_t;

  // foreign import char :: String -> Char
  //
  auto char$(const string&) -> char32_t;

  // Unsafe helper function
  //
  auto UChar_At(const int i, const string& s) -> char32_t;

}

#endif // Data_String_Unsafe_FFI_HH
