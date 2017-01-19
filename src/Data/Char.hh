///////////////////////////////////////////////////////////////////////////////
//
// Module      :  Char.hh
// Copyright   :  (c) Andy Arvanitis 2016
// License     :  MIT
//
// Maintainer  :  Andy Arvanitis <andy.arvanitis@gmail.com>
// Stability   :  experimental
// Portability :
//
// Char FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#ifndef Data_Char_FFI_HH
#define Data_Char_FFI_HH

#include "PureScript/PureScript.hh"

namespace Data_Char {
  using namespace PureScript;

  // foreign import toCharCode :: Char -> Int
  //
  inline auto toCharCode(char32_t c) -> int {
    assert(c <= std::numeric_limits<int>::max());
    return static_cast<int>(c);
  }

  // foreign import fromCharCode :: Int -> Char
  //
  inline auto fromCharCode(int i) -> char32_t {
    assert(i >= 0 && i < 0x10FFFF); // valid unicode code point range
    return static_cast<char32_t>(i);
  }

  // foreign import toLower :: Char -> Char
  //
  auto toLower(char32_t) -> char32_t;

  // foreign import toUpper :: Char -> Char
  //
  auto toUpper(char32_t) -> char32_t;

}

#endif // Data_Char_FFI_HH
