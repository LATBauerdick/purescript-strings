///////////////////////////////////////////////////////////////////////////////
//
// Module      :  String.cc
// Copyright   :  (c) Andy Arvanitis 2016
// License     :  MIT
//
// Maintainer  :  Andy Arvanitis <andy.arvanitis@gmail.com>
// Stability   :  experimental
// Portability :
//
// String FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#include <algorithm>
#include <locale>
#include <codecvt>
#include <regex>
#include "String.hh"
#include "Data.Char/Char.hh"

namespace Data_String {

  static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;

  static constexpr auto kRegexOpts =
    std::regex_constants::ECMAScript | std::regex_constants::collate;

  // foreign import _charAt
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Int
  //   -> String
  //   -> Maybe Char
  //
  auto _charAt(const any& just,
               const any& nothing,
               const int i,
               const string& s) -> any {
    if (i < 0 or i >= s.size()) {
      return nothing;
    } else {
      return just(UChar_At(i, s));
    }
  }

  // foreign import singleton :: Char -> String
  //
  auto singleton(char32_t c) -> string {
    return utf32conv.to_bytes(c);
  }

  // foreign import _charCodeAt
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Int
  //   -> String
  //   -> Maybe Int
  //
  auto _charCodeAt(const any& just,
                   const any& nothing,
                   const int i,
                   const string& s) -> any {
    if (i < 0 or i >= s.size()) {
      return nothing;
    } else {
      return just(Data_Char::toCharCode(UChar_At(i, s)));
    }
  }

  // foreign import _toChar
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> String
  //   -> Maybe Char
  //
  auto _toChar(const any& just,
               const any& nothing,
               const string& s) -> any {
    const auto utf32 = utf32conv.from_bytes(s);
    return utf32.size() == 1 ? just(utf32.front()) : nothing;
  }

  // foreign import fromCharArray :: Array Char -> String
  //
  auto fromCharArray(const any::array& xs) -> string {
    std::u32string utf32;
    for (auto it = xs.cbegin(), end = xs.cend(); it != end; it++) {
      utf32.push_back(*it);
    }
    return utf32conv.to_bytes(utf32);
  }

  // foreign import _indexOf
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Pattern
  //   -> String
  //   -> Maybe Int
  //
  auto _indexOf(const any& just,
                const any& nothing,
                const string& x,
                const string& s) -> any {
    const auto i = s.find(x);
    assert(i == string::npos || i <= std::numeric_limits<int>::max());
    return i == string::npos ? nothing : just(static_cast<int>(i));
  }

  // foreign import _indexOf'
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Pattern
  //   -> Int
  //   -> String
  //   -> Maybe Int
  //
  auto _indexOf$prime(const any& just,
                      const any& nothing,
                      const string& x,
                      const int startAt,
                      const string& s) -> any {
    if (startAt < 0) {
      return nothing;
    }
    const auto i = s.find(x, startAt);
    assert(i == string::npos || i <= std::numeric_limits<int>::max());
    return i == string::npos ? nothing : just(static_cast<int>(i));    
  }

  // foreign import _lastIndexOf
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Pattern
  //   -> String
  //   -> Maybe Int
  //
  auto _lastIndexOf(const any& just,
                    const any& nothing,
                    const string& x,
                    const string& s) -> any {    
    const auto i = s.rfind(x);
    assert(i == string::npos || i <= std::numeric_limits<int>::max());
    return i == string::npos ? nothing : just(static_cast<int>(i));
  }

  // foreign import _lastIndexOf'
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Pattern
  //   -> Int
  //   -> String
  //   -> Maybe Int
  //
  auto _lastIndexOf$prime(const any& just,
                          const any& nothing,
                          const string& x,
                          const int startAt,
                          const string& s) -> any {
    if (startAt < 0 || startAt > s.size()) {
      return nothing;
    }
    const auto i = s.rfind(x, startAt);
    assert(i == string::npos || i <= std::numeric_limits<int>::max());
    return i == string::npos ? nothing : just(static_cast<int>(i));
  }

  // foreign import length :: String -> Int
  //
  auto length(const string& s) -> int {
    const auto sz = s.size();
    assert(sz <= std::numeric_limits<int>::max());
    return static_cast<int>(sz);
  }

  // foreign import _localeCompare
  //   :: Ordering
  //   -> Ordering
  //   -> Ordering
  //   -> String
  //   -> String
  //   -> Ordering
  //
  auto _localeCompare(const any& lt,
                      const any& eq,
                      const any& gt,
                      const string& s1,
                      const string& s2) -> any {
    // TODO: more testing needed
    const auto& collate = std::use_facet<std::collate<char>>(std::locale());
    const auto result = collate.compare(s1.c_str(), s1.c_str() + s1.size(),
                                        s2.c_str(), s2.c_str() + s2.size());
    return result < 0 ? lt : result > 0 ? gt : eq;
  }

  // foreign import replace :: Pattern -> Replacement -> String -> String
  //
  auto replace(const string& s1, const string& s2, const string& s3) -> string {
    string s(s3);
    const auto found = s.find(s1);
    return found == string::npos ? s : s.replace(found, s1.size(), s2);
  }

  // foreign import replaceAll :: Pattern -> Replacement -> String -> String
  //
  auto replaceAll(const string& s1, const string& s2, const string& s3) -> string {
    string s(s3);
    for (string::size_type pos = 0, found = string::npos;
         (found = s.find(s1, pos)) != string::npos;
         pos += s2.size()) {
      s.replace(found, s1.size(), s2);
    }
    return s;
  }

  // foreign import take :: Int -> String -> String
  //
  auto take(const int n, const string& s) -> string {
    return s.substr(0, n < 0 ? 0 : n);
  }

  // foreign import drop :: Int -> String -> String
  //
  auto drop(const int n, const string& s) -> string {    
    return n <= 0 ? s : n >= s.size() ? "" : s.substr(n);
  }

  // foreign import count :: (Char -> Boolean) -> String -> Int
  //
  auto count(const any& p, const string& s) -> int {
    const auto utf32 = utf32conv.from_bytes(s);
    decltype(utf32)::size_type i = 0;
    while (i < utf32.size() && p(utf32[i])) {
      i++;
    }
    return i;
  }

  // foreign import split :: Pattern -> String -> Array String
  //
  auto split(const string& sep, string s) -> any::array {
    any::array result;
    if (not sep.empty()) {
      string::size_type n;
      while (n = s.find(sep), n != string::npos) {
        result.emplace_back(s.substr(0, n));
        s = s.substr(n + sep.size());
      }
      result.emplace_back(s.substr(0, n));
    } else {
      const auto utf32 = utf32conv.from_bytes(s);
      for (auto it = utf32.cbegin(), end = utf32.cend(); it != end; it++) {
        result.emplace_back(utf32conv.to_bytes(*it));
      }
    }
    return result;
  }

  // foreign import _splitAt :: (forall a. a -> Maybe a)
  //                         -> (forall a. Maybe a)
  //                         -> Int
  //                         -> String
  //                         -> Maybe (Array String)
  //
  auto _splitAt(const any& just,
                const any& nothing,
                const int i,
                const string& s) -> any {    
    return i >= 0 && i < s.size() ? just(any::array{s.substr(0, i), s.substr(i)})
                                  : nothing;
  }

  // foreign import toCharArray :: String -> Array Char
  //
  auto toCharArray(const string& s) -> any::array {
    any::array result;
    const auto utf32 = utf32conv.from_bytes(s);
    for (auto it = utf32.cbegin(), end = utf32.cend(); it != end; it++) {
      result.emplace_back(*it);
    }
    return result;
  }

  // foreign import toLower :: String -> String
  //
  auto toLower(const string& s) -> string {
    // Note: does not convert unicode characters
    string result;
    for (auto it = s.cbegin(), end = s.cend(); it != end; it++) {
      result.push_back(std::tolower(*it));
    }
    return result;
  }

  // foreign import toUpper :: String -> String
  //
  auto toUpper(const string& s) -> string {
    // Note: does not convert unicode characters
    string result;
    for (auto it = s.cbegin(), end = s.cend(); it != end; it++) {
      result.push_back(std::toupper(*it));
    }
    return result;    
  }

  // foreign import trim :: String -> String
  //
  auto trim(const string& s) -> string {
    static const auto expr = std::regex("^\\s+|\\s+$", kRegexOpts);
    return std::regex_replace(s, expr, "");
  }

  // foreign import joinWith :: String -> Array String -> String
  //
  auto joinWith(const string& s, const any::array& xs) -> string {
    const auto sz = xs.size();
    string result;
    if (sz > 0) {
      result = static_cast<const string&>(xs.front());
    }
    if (sz > 1) {
      for (auto it = xs.cbegin() + 1, end = xs.cend(); it != end; it++) {
        result.append(s);
        result.append(static_cast<const string&>(*it));
      }
    }
    return result;
  }

}
