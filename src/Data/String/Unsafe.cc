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
// String Unsafe FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#include <locale>
#include <codecvt>
#include "Unsafe.hh"
#include "Data.Char/Char.hh"

namespace Data_String_Unsafe {

  static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;

  // foreign import charCodeAt :: Int -> String -> Int
  //
  auto charCodeAt(const int i, const string& s) -> int {
    if (i >= 0 && i < s.size()) return Data_Char::toCharCode(UChar_At(i, s));
    throw runtime_error("Data.String.Unsafe.charCodeAt: Invalid index.");
  }

  // foreign import charAt :: Int -> String -> Char
  //
  auto charAt(const int i, const string& s) -> char32_t {
    if (i >= 0 && i < s.size()) return UChar_At(i, s);
    throw runtime_error("Data.String.Unsafe.charAt: Invalid index.");
  }

  // foreign import char :: String -> Char
  //
  auto char$(const string& s) -> char32_t {
    const auto utf32 = utf32conv.from_bytes(s);
    if (utf32.size() == 1) return utf32.front();
    throw runtime_error("Data.String.Unsafe.char: Expected string of length 1.");
  }

  // Unsafe helper function
  //
  auto UChar_At(const int i, const string& s) -> char32_t {
    return utf32conv.from_bytes(s.c_str() + i).front();
  }

}
