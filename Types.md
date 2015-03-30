# Types and Operations #

Helio defines 4 kinds of basic types:
  * **Native:** These are the types that the compiler provides, e.g. `int`, `float`...
  * **Static:** Classes on `Storage::Structure::Data` which implement the basic types as\*objects, e.g. `Integer`, `Float`...
  * **Internal:** Native types used internally by the Static types to store the values, e.g. `__int`, `__float`...
  * **Standard:** Types selected to be use throughout Helio. Use only these in your code. The user can decide which types wants at compiler time depending on the application: testing, safety, speed... By default the static types are recommended because they provide the best safety and testing environment (for example they limit the operators).

All these definitions are done in `Types.h` and any change requires a full rebuild.

## Standard types ##

Unless you are implementing a new type, you should use always these types. They are:

### `_bool` ###

It can be only `true` or `false`. Do not use other definition (like `0` and `1`) and do not assign them from integer:

```
_bool result = index;         // INCORRECT
_bool result = (index != 0);  // Correct
```

Booleans can be used as conditions for statements like `if` or `while`, e.g.:

```
if(enabled)
{
```

### `_char` ###

This type contains a simple character, but never assign it from a string or a number:

```
_char separator = "a";  // INCORRECT
_char separator = 0x61; // INCORRECT
_char separator = 'a';  // Correct
```

Characters are characters not numbers. Do not use them as numbers, except for comparisons and assume UTF-32 encoding:

```
_char c = 'a' + 2;        // INCORRECT
if(c >= 'A' && c <= 'Z')  // Correct
{
```

Note that it is possible to build Helio setting `_char` as 8, 16 or 32 bits. If the user types a character that cannot be represented with the current precision, an Exception will be thrown.

### `_int` ###

`Integer::MAX` and `Integer::MIN`

### `_float` ###

`Float::MAX`, `Float::MIN` and `Float::EPSILON`.

### `_pointer` ###

`null`

### `String` ###

## Constants ##

## Functions ##

## Binary types ##

The binary types are native types non-dependent of the compiler or architecture...
`_uint8`