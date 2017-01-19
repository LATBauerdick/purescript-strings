///////////////////////////////////////////////////////////////////////////////
//
// Module      :  Regex.cc
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

  static constexpr auto kBaseRegexOpts =
    std::regex_constants::ECMAScript | std::regex_constants::collate;

  static auto OptionsFromRecord(const any& rec) ->
      std::regex_constants::syntax_option_type {
    auto opts = kBaseRegexOpts;    
    if (map::get(symbol(ignoreCase), rec)) {
      opts |= std::regex_constants::icase;
    }
    if (record::get(symbol(multiline), rec)) {
      throw runtime_error("Regex 'multiline' option not supported");
    }
    if (record::get(symbol(sticky), rec)) {
      throw runtime_error("Regex 'sticky' option not supported");
    }
    if (record::get(symbol(unicode), rec)) {
      throw runtime_error("Regex 'unicode' option not supported");
    }
    return opts;
  }

  static inline auto MatchFlagsFromRecord(const any& rec) ->
      std::regex_constants::match_flag_type {
    return record::get(symbol(global), rec) ?
        std::regex_constants::match_flag_type::match_default
      : std::regex_constants::match_flag_type::format_first_only;
  }

  struct Regex {
    const string str;
    const std::regex regex;
    const any flagsRecord;

    Regex(const string& s, const any& f)
      : str(s),
        regex(s, OptionsFromRecord(f)),
        flagsRecord(f) {}
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
      return right(make_managed<Regex>(s1, data::get<1>(parseFlags(s2))));
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
    return cast<Regex>(r).flagsRecord;
  }

  // foreign import test :: Regex -> String -> Boolean
  //
  auto test(const any& r, const string& s) -> bool {
    return std::regex_search(s, cast<Regex>(r).regex);
  }

  // foreign import _match
  //   :: (forall r. r -> Maybe r)
  //   -> (forall r. Maybe r)
  //   -> Regex
  //   -> String
  //   -> Maybe (Array (Maybe String))
  //
  auto $_match(const any& just,
               const any& nothing,
               const any& r,
               const string& s) -> any {
    const auto& rx = cast<Regex>(r);
    const auto mflags = MatchFlagsFromRecord(rx.flagsRecord);
    std::smatch m;
    if (std::regex_match(s, m, rx.regex, mflags)) {
      any::array list;
      for (auto i = 0; i < m.size(); i++) {
        const auto& match = m[i];
        list.emplace_back(match.length() ? just(match.str()) : nothing);
      }
      return just(list);
    } else {
      return nothing;
    }
  }

  // foreign import replace :: Regex -> String -> String -> String
  //
  auto replace(const any& r, const string& s1, const string& s2) -> string {
    const auto& rx = cast<Regex>(r);
    const auto mflags = MatchFlagsFromRecord(rx.flagsRecord);
    return std::regex_replace(s2, rx.regex, s1, mflags);
  }

  // foreign import replace' :: Regex -> (String -> Array String -> String) -> String -> String
  //
  auto replace$prime(const any& r, const any& f, const string& s2) -> string {
    const auto& rx = cast<Regex>(r);
    const auto mflags = MatchFlagsFromRecord(rx.flagsRecord);
    std::smatch m;
    if (std::regex_search(s2, m, rx.regex, mflags)) {
      const string match = m[0].str();
      any::array submatches;
      for (auto i = 1; i < m.size(); i++) {
        submatches.emplace_back(m[i].str());
      }
      return std::regex_replace(s2,
                                rx.regex,
                                static_cast<const string&>(f(match)(submatches)),
                                mflags);
    } else {
      return s2;
    }
  }

  // foreign import _search
  //   :: (forall r. r -> Maybe r)
  //   -> (forall r. Maybe r)
  //   -> Regex
  //   -> String
  //   -> Maybe Int
  //
  auto $_search(const any& just,
                const any& nothing,
                const any& r,
                const string& s) -> any {
    std::smatch m;
    return std::regex_search(s, m, cast<Regex>(r).regex) ? just(m.position()) : nothing;
  }

  // foreign import split :: Regex -> String -> Array String
  //
  auto split(const any& r, const string& s) -> any::array {
    const auto& rx = cast<Regex>(r);
    const auto mflags = MatchFlagsFromRecord(rx.flagsRecord);
    if (std::regex_search(s, rx.regex, mflags)) {
      const auto ss = std::regex_replace(s, rx.regex, "\0\f\0", mflags);
      return Data_String::split("\0\f\0", ss);
    } else {
      return any::array{{ s }};
    }
  }

}

