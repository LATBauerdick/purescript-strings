///////////////////////////////////////////////////////////////////////////////
//
// Module      :  String.hh
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
#ifndef Data_String_FFI_HH
#define Data_String_FFI_HH

#include "PureScript/PureScript.hh"

namespace Data_String {
  using namespace PureScript;

  // foreign import _charAt
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Int
  //   -> String
  //   -> Maybe Char
  //
  auto _charAt(const any&, const any&, const int, const string&) -> any;

  // foreign import singleton :: Char -> String
  //
  auto singleton(char32_t) -> string;

  // foreign import _charCodeAt
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Int
  //   -> String
  //   -> Maybe Int
  //
  auto _charCodeAt(const any&, const any&, const int, const string&) -> any;

  // foreign import _toChar
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> String
  //   -> Maybe Char
  //
  auto _toChar(const any&, const any&, const string&) -> any;

  // foreign import fromCharArray :: Array Char -> String
  //
  auto fromCharArray(const any::array&) -> string;

  // foreign import _indexOf
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Pattern
  //   -> String
  //   -> Maybe Int
  //
  auto _indexOf(const any&, const any&, const string&, const string&) -> any;

  // foreign import _indexOf'
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Pattern
  //   -> Int
  //   -> String
  //   -> Maybe Int
  //
  auto _indexOf$prime(const any&, const any&, const string&, const int, const string&) -> any;

  // foreign import _lastIndexOf
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Pattern
  //   -> String
  //   -> Maybe Int
  //
  auto _lastIndexOf(const any&, const any&, const string&, const string&) -> any;

  // foreign import _lastIndexOf'
  //   :: (forall a. a -> Maybe a)
  //   -> (forall a. Maybe a)
  //   -> Pattern
  //   -> Int
  //   -> String
  //   -> Maybe Int
  //
  auto _lastIndexOf$prime(const any&, const any&, const string&, const int, const string&) -> any;

  // foreign import length :: String -> Int
  //
  auto length(const string&) -> int;

  // foreign import _localeCompare
  //   :: Ordering
  //   -> Ordering
  //   -> Ordering
  //   -> String
  //   -> String
  //   -> Ordering
  //
  auto _localeCompare(const any&, const any&, const any&, const string&, const string&) -> any;

  // foreign import replace :: Pattern -> Replacement -> String -> String
  //
  auto replace(const string&, const string&, const string&) -> string;

  // foreign import replaceAll :: Pattern -> Replacement -> String -> String
  //
  auto replaceAll(const string&, const string&, const string&) -> string;

  // foreign import take :: Int -> String -> String
  //
  auto take(const int, const string&) -> string;

  // foreign import drop :: Int -> String -> String
  //
  auto drop(const int, const string&) -> string;

  // foreign import count :: (Char -> Boolean) -> String -> Int
  //
  auto count(const any&, const string&) -> int;

  // foreign import split :: Pattern -> String -> Array String
  //
  auto split(const string&, string) -> any::array;

  // foreign import _splitAt :: (forall a. a -> Maybe a)
  //                         -> (forall a. Maybe a)
  //                         -> Int
  //                         -> String
  //                         -> Maybe (Array String)
  //
  auto _splitAt(const any&, const any&, const int, const string&) -> any;

  // foreign import toCharArray :: String -> Array Char
  //
  auto toCharArray(const string&) -> any::array;

  // foreign import toLower :: String -> String
  //
  auto toLower(const string&) -> string;

  // foreign import toUpper :: String -> String
  //
  auto toUpper(const string&) -> string;

  // foreign import trim :: String -> String
  //
  auto trim(const string&) -> string;

  // foreign import joinWith :: String -> Array String -> String
  //
  auto joinWith(const string&, const any::array&) -> string;

}

#endif // Data_String_FFI_HH
