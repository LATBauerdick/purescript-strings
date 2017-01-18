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
// String Regex FFI functions
//
///////////////////////////////////////////////////////////////////////////////
//
#include <iostream>
#include <locale>
#include <codecvt>
#include <regex>
#include "Regex.hh"

define_symbol(global);
define_symbol(ignoreCase);
define_symbol(multiline);
define_symbol(sticky);
define_symbol(unicode);

namespace Data_String_Regex {

  static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;

  static constexpr auto kRegexOpts =
    std::regex_constants::ECMAScript | std::regex_constants::collate;

  static auto Flags(const string& s) -> std::regex_constants::syntax_option_type {
    auto flags = kRegexOpts;
    if (s.find("i") != string::npos) {
      flags |= std::regex_constants::icase;
    }
    if (s.find("g") != string::npos) {
      std::cerr << "regex 'global' option not supported" << std::endl;
    }
    if (s.find("m") != string::npos) {
      std::cerr << "regex 'multiline' option not supported" << std::endl;
    }
    if (s.find("u") != string::npos) {
      std::cerr << "regex 'unicode' option not supported" << std::endl;
    }
    if (s.find("y") != string::npos) {
      std::cerr << "regex 'sticky' option not supported" << std::endl;
    }
    return flags;
  }

  struct Regex {
    const string str;
    const std::regex expr;
    Regex(const string& s,
          std::regex_constants::syntax_option_type o) : str(s), expr(s, o) {}
  };

  // foreign import showRegex' :: Regex -> String
  //
  auto showRegex$prime(const any& r) -> string {
    return cast<Regex>(r).str;
  }

  // foreign import regex'
  //   :: (String -> Either String Regex)
  //   -> (Regex -> Either String Regex)
  //   -> String
  //   -> String
  //   -> Either String Regex
  //
  auto regex$prime(const any& left,
                   const any& right,
                   const string& s1,
                   const string& s2) -> any {
    try {
      return right(make_managed<Regex>(s1, Flags(s2)));
    } catch (std::exception& e) {
      return left(e.what());
    }
  }

  // foreign import source :: Regex -> String
  //
  auto source(const any& r) -> string {
    return cast<Regex>(r).str;
  }

  // foreign import flags' :: Regex -> RegexFlagsRec
  //
  auto flags$prime(const any& r) -> any {
    const auto flags = cast<Regex>(r).expr.flags();
    return record::make(
      { symbol(global),     false },
      { symbol(ignoreCase), flags & std::regex_constants::icase },
      { symbol(multiline),  false },
      { symbol(sticky),     false },
      { symbol(unicode),    false }
    );
  }

  // foreign import test :: Regex -> String -> Boolean
  //
  auto test(const any&, const string&) -> bool {
    throw runtime_error("Incomplete implementation for Data_String_Regex::test");
  }

  // foreign import _match
  //   :: (forall r. r -> Maybe r)
  //   -> (forall r. Maybe r)
  //   -> Regex
  //   -> String
  //   -> Maybe (Array (Maybe String))
  //
  auto $_match(const any&, const any&, const any&, const string&) -> any {
    throw runtime_error("Incomplete implementation for Data_String_Regex::_match");
  }

  // foreign import replace :: Regex -> String -> String -> String
  //
  auto replace(const any&, const string&, const string&) -> string {
    throw runtime_error("Incomplete implementation for Data_String_Regex::replace");
  }

  // foreign import replace' :: Regex -> (String -> Array String -> String) -> String -> String
  //
  auto replace$prime(const any&, const any&, const string&) -> string {
    throw runtime_error("Incomplete implementation for Data_String_Regex::replace'");    
  }

  // foreign import _search
  //   :: (forall r. r -> Maybe r)
  //   -> (forall r. Maybe r)
  //   -> Regex
  //   -> String
  //   -> Maybe Int
  //
  auto $_search(const any&, const any&, const any&, const string&) -> string {
    throw runtime_error("Incomplete implementation for Data_String_Regex::_search");
  }

  // foreign import split :: Regex -> String -> Array String
  //
  auto split(const any&, const string&) -> any::array {
    throw runtime_error("Incomplete implementation for Data_String_Regex::split");
  }

}
