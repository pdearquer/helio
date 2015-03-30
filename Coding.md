# Programming Style #

Helio is programmed in C++, but this is a very flexible language which allows many ways of coding, some of them prone to errors. This guide restricts the use of some C++ features and introduce others (typical of Java or Ada) in an attempt to define a robust and uniform programming style which helps developers to deliver a high standard software and read easier other's source.

Please read carefully and understanding the rules described in this documents:

  * [Naming and commenting conventions](Naming.md)
  * [Types, limits and operations](Types.md)
  * [How to handle errors](Errors.md)

Also read the [specific documentation of the modules](Modules.md) that you want to use, specially the [Collections](Collections.md).

## General rules ##

These are general stuff that I could not classify.

You will notice that certain patterns that are discouraged here are used often in the code. They serve just as a way to fulfill some C++ lacks. Some examples are the static class String, the error handling with macros or the containers implemented as templates.

### Order of a class ###

The order of listing of the parts of a class is:

  1. Static attributes
  1. Attributes or properties
  1. Static methods
  1. Constructors
  1. Destructor
  1. Methods

Avoid the use of macros, but if necessary define them after the class.

### Accessibility ###

Make all the attributes protected by default, so they are not accessible from outside but your class is easily extensible (I am always assuming an open source environment). Make an attribute private if it requires a particular handling and you consider that it is better to abstract that from the children classes.

Some classes are just a group of attributes, with no function by themselves. These are called structures and must have all their attributes public. It is the user's responsibility to maintain the consistency of the data. An example of this is shown in `Storage::Structure::MapEntry`.

Make your methods public unless they are intended for internal use only, in which case declare them protected. Use private methods for things that you consider dangerous to use even for child classes. Note that this is an open source project and the users can (and should) read the code when inheriting from your class.

Never make your method virtual if it is called from a constructor or destructor and, in the same way, never call a virtual method from a constructor or destructor. The call could happen in an incomplete class (not yet created or never created because of an exception in a constructor). If this is not the case, try to make your methods virtual, this again will make your classes more extensible.

### Multiple inheritance ###

Always inherit virtually and from at least one Helio class:
```
class Integer : 
      public virtual Cloneable, public virtual Orderable<Integer>,
      public virtual Hashable<Integer>, public virtual Number
{
```
If you don't need any, use Object:
```
class Buffer : 
      public virtual Object
{
```

And never use the constructor's initialization list:
```
StringBuffer::StringBuffer(const StringBuffer &other)
      : Buffer(&other)   // INCORRECT: THIS LINE BRINGS MANY PROBLEMS
{
}
```
Use only the default constructor of the parent (by not specifying any) and initialize your class using methods.
```
StringBuffer::StringBuffer(const StringBuffer &other)
{
   add(other);
}
```
This way you will use multiple inheritance safely.

### Templates ###

Do not overuse the templates or generic. They are very handy for things like containers, but they can lead to a complex and confuse syntax. So if you can avoid them in a sensible way, do it.

If you need to create a template, create a new class marked as `onlyheader` in the `Package.xml` file (see next section), that will exclude the .cpp from the compilation. Then include the .cpp file in the `Templates.h` file on the root.

Access all the attributes and methods of the template with the `this->` prefix (it is required to inherit) and check that the generic types you accept fulfil your needs, the `__CHECK_BASE` macro will help you with this. For example:

```
template<class T>
class Set : 
      public virtual Container<T>
{
   __CHECK_BASE(T, Comparable<T>);
```

### Static objects ###

Static objects are those that you use allocating statically, rather than with `new` and `delete`. Avoid this kind of classes as much as possible, they hide the memory management and lead to bad patterns as PIMPL (which means duplication and implementing a smart pointer each time). In some cases however, its use is justified (like for the String class).

A static class must inherit from StaticObject and be declared as friend of it, this prevents other classes to inherit from yours (similar to `final` in Java). Do not forget to implement the copy and assign constructors and consider carefully the operators you make and their prototypes (read [Types and Operations](Types.md) for more details).

### Creating a new class or package ###

If you need to add a new class to the project, you will have to create an entry in the `Package.xml` file of the same folder (package) of your class and run the builder again to include it into the compilation.

If you want to create a new package you'll have to create a new directory with a `Package.xml` file on it.

See the [Builder documentation](Builder.md) to learn more.