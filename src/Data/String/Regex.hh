///////////////////////////////////////////////////////////////////////////////
//
// Module      :  Regex.hh
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
#ifndef Data_String_Regex_FFI_HH
#define Data_String_Regex_FFI_HH

#include "PureScript/PureScript.hh"

namespace Data_String_Regex {
  using namespace PureScript;

  // foreign import showRegex' :: Regex -> String
  //
  auto showRegex$prime(const any&) -> string;

  // foreign import regex'
  //   :: (String -> Either String Regex)
  //   -> (Regex -> Either String Regex)
  //   -> String
  //   -> String
  //   -> Either String Regex
  //
  auto regex$prime(const any&, const any&, const string&, const string&) -> any;

  // foreign import source :: Regex -> String
  //
  auto source(const any&) -> string;

  // foreign import flags' :: Regex -> RegexFlagsRec
  //
  auto flags$prime(const any&) -> any;

  // foreign import test :: Regex -> String -> Boolean
  //
  auto test(const any&, const string&) -> bool;

  // foreign import _match
  //   :: (forall r. r -> Maybe r)
  //   -> (forall r. Maybe r)
  //   -> Regex
  //   -> String
  //   -> Maybe (Array (Maybe String))
  //
  auto $_match(const any&, const any&, const any&, const string&) -> any;

  // foreign import replace :: Regex -> String -> String -> String
  //
  auto replace(const any&, const string&, const string&) -> string;

  // foreign import replace' :: Regex -> (String -> Array String -> String) -> String -> String
  //
  auto replace$prime(const any&, const any&, const string&) -> string;

  // foreign import _search
  //   :: (forall r. r -> Maybe r)
  //   -> (forall r. Maybe r)
  //   -> Regex
  //   -> String
  //   -> Maybe Int
  //
  auto $_search(const any&, const any&, const any&, const string&) -> any;

  // foreign import split :: Regex -> String -> Array String
  //
  auto split(const any&, const string&) -> any::array;

}

#endif // Data_String_Regex_FFI_HH
