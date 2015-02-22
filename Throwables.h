/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/* Throwables: Error descriptors
 * Do not use directly, use the ERROR macros instead.
 * This file should be generated automatically */

/* Exceptions: Recoverable errors */

class Exception : public virtual Component::Error::Throwable
{
protected:
   Exception() { }
   
public:
   class NotSupported;
   class InvalidClass;
   class Format;
   class Structure;
   class Device;
   class Test;
};

class Exception::NotSupported : public virtual Exception
{
public:
   NotSupported(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Operation not supported.", child, source, line, date);
   }
};

class Exception::InvalidClass : public virtual Exception
{
public:
   InvalidClass(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The object does not belong to the expected class.", child, source, line, date);
   }
};

class Exception::Format : public virtual Exception
{
protected:
   Format() { }
   
public:
   Format(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Invalid format found.", child, source, line, date);
   }
   
   class Overflow;
   class InvalidCharacter;
   class DateLimit;
   class InvalidBase;
   class InvalidDigits;
   class IllegalSequence;
   class UnexpectedEnd;
   class InvalidByte;
   class EmptyBuffer;
};

class Exception::Format::Overflow : public virtual Exception::Format
{
public:
   Overflow(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The number exceed the limits.", child, source, line, date);
   }
};

class Exception::Format::InvalidCharacter : public virtual Exception::Format
{
public:
   InvalidCharacter(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Character code is not valid.", child, source, line, date);
   }
};

class Exception::Format::DateLimit : public virtual Exception::Format
{
public:
   DateLimit(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Date out of the limits of precision.", child, source, line, date);
   }
};

class Exception::Format::InvalidBase : public virtual Exception::Format
{
public:
   InvalidBase(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Invalid base for current digits.", child, source, line, date);
   }
};

class Exception::Format::InvalidDigits : public virtual Exception::Format
{
public:
   InvalidDigits(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Invalid set of digits.", child, source, line, date);
   }
};

class Exception::Format::IllegalSequence : public virtual Exception::Format
{
public:
   IllegalSequence(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Illegal sequence of characters found.", child, source, line, date);
   }
};

class Exception::Format::UnexpectedEnd : public virtual Exception::Format
{
public:
   UnexpectedEnd(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Unexpected end of data.", child, source, line, date);
   }
};

class Exception::Format::InvalidByte : public virtual Exception::Format
{
public:
   InvalidByte(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Incorrect sequence of bytes found.", child, source, line, date);
   }
};

class Exception::Format::EmptyBuffer : public virtual Exception::Format
{
public:
   EmptyBuffer(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Empty buffers cannot be processed.", child, source, line, date);
   }
};

class Exception::Structure : public virtual Exception
{
protected:
   Structure() { }
   
public:
   class KeyNotFound;
   class ValueNotFound;
   class EscapingNotSupported;
   class EncodingNotSupported;
};

class Exception::Structure::KeyNotFound : public virtual Exception::Structure
{
public:
   KeyNotFound(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The given key was not found is the container.", child, source, line, date);
   }
};

class Exception::Structure::ValueNotFound : public virtual Exception::Structure
{
public:
   ValueNotFound(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The given value was not found is the container.", child, source, line, date);
   }
};

class Exception::Structure::EscapingNotSupported : public virtual Exception::Structure
{
public:
   EscapingNotSupported(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Escaping not supported.", child, source, line, date);
   }
};

class Exception::Structure::EncodingNotSupported : public virtual Exception::Structure
{
public:
   EncodingNotSupported(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Encoding not supported.", child, source, line, date);
   }
};

class Exception::Device : public virtual Exception
{
protected:
   Device() { }
   
public:
   class NoDefault;
};

class Exception::Device::NoDefault : public virtual Exception::Device
{
public:
   NoDefault(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("No default device available of this type.", child, source, line, date);
   }
};

class Exception::Test : public virtual Exception
{
protected:
   Test() { }
   
public:
   class UnknownException;
   class IllegalFilter;
   class TestException;
   class MemoryLeak;
};

class Exception::Test::UnknownException : public virtual Exception::Test
{
public:
   UnknownException(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Catched unknown exception.", child, source, line, date);
   }
};

class Exception::Test::IllegalFilter : public virtual Exception::Test
{
public:
   IllegalFilter(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Illegal test filtering pattern.", child, source, line, date);
   }
};

class Exception::Test::TestException : public virtual Exception::Test
{
public:
   TestException(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("This exception is just for test purposes.", child, source, line, date);
   }
};

class Exception::Test::MemoryLeak : public virtual Exception::Test
{
public:
   MemoryLeak(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Object not deallocated from memory.", child, source, line, date);
   }
};


/* Errors: Unrecoverable errors */

class Error : public virtual Component::Error::Throwable
{
protected:
   Error() { }
   
public:
   class UserInterrupt;
   class TimeOut;
   class NotImplemented;
   class NullObject;
   class Internal;
   class IllegalClass;
   class Arithmetic;
   class Structure;
   class Text;
   class Test;
};

class Error::UserInterrupt : public virtual Error
{
public:
   UserInterrupt(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Execution interrupted by the user.", child, source, line, date);
   }
};

class Error::TimeOut : public virtual Error
{
public:
   TimeOut(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The execution has timed out.", child, source, line, date);
   }
};

class Error::NotImplemented : public virtual Error
{
public:
   NotImplemented(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Feature not implemented.", child, source, line, date);
   }
};

class Error::NullObject : public virtual Error
{
public:
   NullObject(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Unexpected null object.", child, source, line, date);
   }
};

class Error::Internal : public virtual Error
{
public:
   Internal(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Internal error occured.", child, source, line, date);
   }
};

class Error::IllegalClass : public virtual Error
{
public:
   IllegalClass(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The pointer given is not a legal Object.", child, source, line, date);
   }
};

class Error::Arithmetic : public virtual Error
{
protected:
   Arithmetic() { }
   
public:
   class Overflow;
   class DivisionByCero;
   class ModuloByCero;
};

class Error::Arithmetic::Overflow : public virtual Error::Arithmetic
{
public:
   Overflow(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Last arithmetic operation has overflown.", child, source, line, date);
   }
};

class Error::Arithmetic::DivisionByCero : public virtual Error::Arithmetic
{
public:
   DivisionByCero(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Trying to calculate a division by cero.", child, source, line, date);
   }
};

class Error::Arithmetic::ModuloByCero : public virtual Error::Arithmetic
{
public:
   ModuloByCero(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Trying to calculate a modulo by cero.", child, source, line, date);
   }
};

class Error::Structure : public virtual Error
{
protected:
   Structure() { }
   
public:
   class IllegalCapacity;
   class OutOfBounds;
   class Empty;
   class IterationEnded;
   class IteratorInvalidated;
   class InvalidLength;
   class LoopsNotAllowed;
   class InvalidContainer;
};

class Error::Structure::IllegalCapacity : public virtual Error::Structure
{
public:
   IllegalCapacity(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The capacity must be higher than cero.", child, source, line, date);
   }
};

class Error::Structure::OutOfBounds : public virtual Error::Structure
{
public:
   OutOfBounds(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Index or interval out of bounds.", child, source, line, date);
   }
};

class Error::Structure::Empty : public virtual Error::Structure
{
public:
   Empty(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Operation invalid because the container is empty.", child, source, line, date);
   }
};

class Error::Structure::IterationEnded : public virtual Error::Structure
{
public:
   IterationEnded(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("There are no more elements to iterate.", child, source, line, date);
   }
};

class Error::Structure::IteratorInvalidated : public virtual Error::Structure
{
public:
   IteratorInvalidated(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The container has been modified and that invalidates this iterator.", child, source, line, date);
   }
};

class Error::Structure::InvalidLength : public virtual Error::Structure
{
public:
   InvalidLength(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Trying to set a negative or too long length.", child, source, line, date);
   }
};

class Error::Structure::LoopsNotAllowed : public virtual Error::Structure
{
public:
   LoopsNotAllowed(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("This node container does not allow loops.", child, source, line, date);
   }
};

class Error::Structure::InvalidContainer : public virtual Error::Structure
{
public:
   InvalidContainer(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The element does not belong to the container provided.", child, source, line, date);
   }
};

class Error::Text : public virtual Error
{
protected:
   Text() { }
   
public:
   class NoBackward;
   class IncompatiblePointers;
   class InvalidPointer;
};

class Error::Text::NoBackward : public virtual Error::Text
{
public:
   NoBackward(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Window start and end pointers cannot go backwards.", child, source, line, date);
   }
};

class Error::Text::IncompatiblePointers : public virtual Error::Text
{
public:
   IncompatiblePointers(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Incompatible pointers mixed, they must work over the same window.", child, source, line, date);
   }
};

class Error::Text::InvalidPointer : public virtual Error::Text
{
public:
   InvalidPointer(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Window pointer not allocated.", child, source, line, date);
   }
};

class Error::Test : public virtual Error
{
protected:
   Test() { }
   
public:
   class Assertion;
   class Duplicated;
   class TestError;
};

class Error::Test::Assertion : public virtual Error::Test
{
public:
   Assertion(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Assertion condition failed.", child, source, line, date);
   }
};

class Error::Test::Duplicated : public virtual Error::Test
{
public:
   Duplicated(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Test name duplicated.", child, source, line, date);
   }
};

class Error::Test::TestError : public virtual Error::Test
{
public:
   TestError(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("This error is just for test purposes.", child, source, line, date);
   }
};


/* Faults: Critical errors */

class Fault : public virtual Component::Error::Throwable
{
protected:
   Fault() { }
   
public:
   class Code;
   class Memory;
};

class Fault::Code : public virtual Fault
{
protected:
   Code() { }
   
public:
   class InvalidAddress;
   class FloatingPoint;
   class IllegalInstruction;
};

class Fault::Code::InvalidAddress : public virtual Fault::Code
{
public:
   InvalidAddress(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Trying to access an invalid memory address.", child, source, line, date);
   }
};

class Fault::Code::FloatingPoint : public virtual Fault::Code
{
public:
   FloatingPoint(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Floating point exception.", child, source, line, date);
   }
};

class Fault::Code::IllegalInstruction : public virtual Fault::Code
{
public:
   IllegalInstruction(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Trying to execute an illegal instruction.", child, source, line, date);
   }
};

class Fault::Memory : public virtual Fault
{
protected:
   Memory() { }
   
public:
   class SafeAllocatorBroken;
   class OutOfMemory;
   class InvalidPointer;
   class AlignmentFail;
   class BigAllocation;
   class DoubleDeallocation;
   class MemoryCorrupt;
};

class Fault::Memory::SafeAllocatorBroken : public virtual Fault::Memory
{
public:
   SafeAllocatorBroken(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Exception thrown on safe allocator environment.", child, source, line, date);
   }
};

class Fault::Memory::OutOfMemory : public virtual Fault::Memory
{
public:
   OutOfMemory(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("No more memory available.", child, source, line, date);
   }
};

class Fault::Memory::InvalidPointer : public virtual Fault::Memory
{
public:
   InvalidPointer(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("The pointer provided is not valid in current memory allocator.", child, source, line, date);
   }
};

class Fault::Memory::AlignmentFail : public virtual Fault::Memory
{
public:
   AlignmentFail(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Fail to accomplish alignment constraints.", child, source, line, date);
   }
};

class Fault::Memory::BigAllocation : public virtual Fault::Memory
{
public:
   BigAllocation(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Trying to allocate an object too big.", child, source, line, date);
   }
};

class Fault::Memory::DoubleDeallocation : public virtual Fault::Memory
{
public:
   DoubleDeallocation(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Trying to deallocate an object already deallocated.", child, source, line, date);
   }
};

class Fault::Memory::MemoryCorrupt : public virtual Fault::Memory
{
public:
   MemoryCorrupt(Component::Error::Throwable *child, const String &source, _int line, const String &date)
   {
      init("Memory corruption detected.", child, source, line, date);
   }
};

