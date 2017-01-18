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
// Char FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#include <locale>
#include "Char.hh"

namespace Data_Char {

  // foreign import toLower :: Char -> Char
  //
  auto toLower(char32_t c) -> char32_t {
    // Note: does not convert unicode characters
    return std::tolower(c);
  }

  // foreign import toUpper :: Char -> Char
  //
  auto toUpper(char32_t c) -> char32_t {
    // Note: does not convert unicode characters
    return std::toupper(c);
  }

}
