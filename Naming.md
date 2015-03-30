# Naming and commenting convention #

The naming and commenting conventions of Helio are quite close to the standard Java style, being familiar with it will help you.

In general, choose the shortest name possible but long enough to describe properly what you are naming. Start by writing the comments that describe the class, method or attribute, because that will give you the clue for the name, usually from the first words of your description.

Be consistent with the names. Use the same word to name the same thing. For example, there are many ways of naming the number of elements of a container: size, length, count, numElements... but Helio uses count (and length for strings and size for arrays), so either use this name or rename all the occurrences.

Do not spare words in your comments but neither put unnecessary wording, be direct and concise. The comments about the software design (classes, methods and attributes) must go in the headers (`*.h`). These are for the users, so explain well enough for everyone else to use your code without having to dig into it. The comments about implementation details are for developers and go in the code (`*.cpp`), write them only if necessary and wherever it is clearer.

## Packages ##

Helio namespaces are called packages like in Java and follow the same directories structure. Each package has a folder with its name and all the classes within this namespace are contained on that directory. Therefore the directories structure follows the internal software structure.

The names of the packages are written in UpperCamelCase, meaning that the words are concatenated without spaces or underscores in between and written using lower-case characters except for the first character which is a capital letter as a way to separate words. Acronyms are written as any other word, in lower-case except for the first letter (e.g. Xml, Url, Utf). These are examples of correct names:

```
Error
Xml
Storage
FileSystem
Escapings
```

Try to find a name of one single word for your package. This is not compulsory but will help making the code clearer. In addition, if you need two or more words to specify what your package does, consider rethinking the design of your code.

## Classes ##

Classes' names should also be written in UpperCamelCase. Remember to write the comment that precede the class before naming it. Create one and only one class per file and name the file with the class's name.

The comments must start with a single sentence's description, this is the same text that needs to be in the `Package.xml` file. The next lines explain in more detail what the class does, write as many paragraphs as you need. Then add any extra explanations, clarifications or examples that you consider. Finally write the tags or patterns that the class follows.

```
/** Temporary character string.
 * Character sequence based on Text::Buffer that allows text manipulation
 * on an static object (using operators).
 *
 * This class is intended for one unique purpose; String creation. It
 * implements an extensive addition operator to allow a behaviour like this:
 *   String text = "name = " + name + ", age = " + age;
 *
 * Static object.
 */
class StringBuffer : 
      public virtual Buffer
{
```

Note that in order to create a new class you will have to add a few lines in the `Package.xml` file of its package. Read the [Builder page](Builder.md) to learn more.

## Methods ##

Methods or class functions (either static or not) are named in lowerCamelCase, which is like UpperCamelCase but with the first letter of the first word lower-case. Here are some examples:

```
equals
toString
enqueueFront
canEncode
convertToUtf8
```

The method's parameters follow the same rules as the temporal variables explained below.

When defining a method, start with the prototype and think carefully the parameters. Then write the comment that describes what it does (normally starting with a verb in third person) and finally name the method itself. Write always a comment of the method, constructor or destructor explaining what it does and, if relevant, how. If it does nothing, put that.

These are three examples from the Buffer class:

```
/**
 * Creates an empty buffer of the default capacity.
 */
Buffer();

/**
 * Returns a piece of the buffer.
 * @param start The index of the first character included.
 * @param length Number of characters to pick up.
 *    If length is 0, returns all the string until the end of the buffer.
 *    If length is negative, returns all the string until the end minus the given length.
 */
Buffer *sub(_int start, _int length) const;

/**
 * Adds some characters from another buffer to the end of this.
 */
void add(const Buffer *b);
```

Note that the `@param` tag wasn't necessary in the last example and therefore wasn't included. Be practical with common sense.

## Attributes ##

The attributes or properties of a class are also named in lowerCamelCase, although they use to be adjectives or nouns, while methods use to be verbs. However the private or protected attributes must start with an underscore.

```
private:
protected:
_elements
_count
_minDigits

public:
key
dayOfMonth
```

Once more, write the comment first and name the attribute afterwards. Write always a comment explaining the attribute.

```
/**
 * Minimum number of digits (padding with 0s).
 * In decimal numbers this is only for the integer part.
 */
_int _minDigits;

/**
 * Array of UTF-32 (target endianess) characters.
 */
__char *_data;
```

## Temporal variables ##

Temporal or internal variables are variables of limited scope, normally within a method, for example the method's parameters. Name them in lower-case and separate the words with underscores. Examples are:

```
actual_len
mult_limit
node_start
next_position
```

Use variables with names that someone else could understand. It is ok to use names like `i` or `num` in small scopes, but if the method is long or complex choose better your names.

## Constants ##

The constants must be written using upper-case on all the letters and separating the words with underscores. For example:

```
MIN_CAPACITY
LOAD_FACTOR
POINTER_START
EPSILON
```

Do not use macros to define constants, use static attributes. There are special rules for them, read [the types documentation](Types.md) to learn more.

## Macros ##

Avoid the macros as must as you can, but for those tasks which cannot be accomplished by other means (unlike constants...), follow the same naming rules as for constants, i.e. upper-case letters with underscores as separators. For example:

```
MAKE_ERROR
RE_THROW_ERROR
PRINTLN
ASSERT_EQ
```

If the macro you are defining do something (is not just a constant), use the function-like syntax, even if it has no parameter:

```
#define INCORRECT_MACRO   doSomething()
#define CORRECT_MACRO()   doSomething()
```

This way, the developer will not be doing things without knowing it.

A special case are the macros which begin with `__HELIO`, these are Helio internals.

## Summary ##

This table is a quick reference to recall the convention, not a substitute to reading this page. I know it is boring (because it is also boring to write) but trust me, it will pay off.

| **Type** | **Convention** | **Example** |
|:---------|:---------------|:------------|
| Package (Namespace) | UpperCamelCase | `FileSystem` |
| Classes | UpperCamelCase | `BufferReader` |
| Methods | lowerCamelCase | `lastIndexOf` |
| Public attributes | lowerCamelCase | `dayOfMonth` |
| Private or protected attributes | Underscore followed by lowerCamelCase | `_minDigits` |
| Temporal or internal variables | lower-case with underscore as word separator | `actual_len` |
| Constants | Upper-case with underscore as word separator | `INITIAL_CAPACITY` |
| Macros | Upper-case with underscore as word separator | `MAKE_ERROR` |