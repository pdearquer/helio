/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Buffer of bytes
 * Binary array of bytes.
 * Similar to Vector<byte> but including byte level operations.
 */
class Buffer : 
      public virtual Object
{
   friend class Storage::Structure::Data::String;
   friend class Storage::Structure::Text::Buffer;
#ifdef __HELIO_LOADER_SIMULATION
   friend class Loader::Simulation;
#endif
#ifdef __HELIO_COMPONENT_CONSOLE
   friend class Component::Console;
#endif

protected:
   /**
    * Array of data.
    */
   _byte *_data;
   
   /**
    * Buffer size.
    */
   _int _length;
   
   /**
    * Buffer capacity.
    */
   _int _capacity;
   
   
public:
   /**
    * Create an empty buffer with default capacity.
    */
   Buffer();
   
   /**
    * Create an empty buffer with the given initial capacity.
    */
   Buffer(_int cap);
   
   /**
    * Create a buffer with initial data (copied).
    */
   Buffer(const _byte *data, _int len);
   
   /**
    * Create a buffer with initial data (copied) and sets the capacity.
    */
   Buffer(const _byte *data, _int len, _int cap);
   
   /**
    * Make a buffer copy.
    */
   Buffer(const Buffer *other);
   
   /**
    * Release the buffer.
    */
   ~Buffer();
   
   
   /**
    * Gets a byte from the buffer.
    */
   _byte get(_int index) const;
   
   /**
    * Gets a uint16 from the buffer using Big Endian.
    */
   _uint16 getUInt16BE(_int index) const;
   
   /**
    * Gets a uint16 from the buffer using Little Endian.
    */
   _uint16 getUInt16LE(_int index) const;
   
   /**
    * Gets a uint16 from the buffer using target endianness.
    */
   _uint16 getUInt16(_int index) const;
   
   
   /**
    * Gets a uint32 from the buffer using Big Endian.
    */
   _uint32 getUInt32BE(_int index) const;
   
   /**
    * Gets a uint32 from the buffer using Little Endian.
    */
   _uint32 getUInt32LE(_int index) const;
   
   /**
    * Gets a uint32 from the buffer using target endianness.
    */
   _uint32 getUInt32(_int index) const;
   
   
   
   /**
    * Sets a byte to the buffer.
    * In index is higher than length a exception is thrown.
    */
   void set(_int index, _byte value);
   
   /**
    * Sets some bytes to the buffer.
    * In index is higher than length a exception is thrown.
    */
   void set(_int index, _byte *b, _int count);
   
   /**
    * Sets some bytes to the buffer from other buffer.
    * In index is higher than length a exception is thrown.
    */
   void set(_int index, Buffer *b);
   
   /**
    * Gets or sets a byte in the buffer.
    */
   _byte &operator [](const _int index);
   
   
   /**
    * Adds a byte to the end of buffer.
    */
   void add(_byte b);   
   
   /**
    * Adds some bytes to the end of buffer.
    */
   void add(_byte *b, _int count);
   
   /**
    * Adds some bytes to the end of buffer from other buffer.
    */
   void add(Buffer *b);
   
   /**
    * Adds some bytes to the end of buffer from other buffer.
    * Start reading from the given position (always add to the end).
    */
   void add(Buffer *b, _int count, _int start);
   
   /**
    * Adds some bytes to the buffer from other buffer.
    * The difference with set() is that this method ensures the capacity. 
    */
   void add(_int start, Buffer *b);
   
   /**
    * Adds some bytes to the buffer from other buffer.
    * Start is the start of this buffer where place bytes.
    * The difference with set() is that this method ensures the capacity. 
    */
   void add(_int start, Buffer *b, _int count);
   
   /**
    * Adds some bytes to the buffer from other buffer.
    * Start is the start of this buffer where place bytes.
    * Start2 is the start of b where get bytes.
    * The difference with set() is that this method ensures the capacity. 
    */
   void add(_int start, Buffer *b, _int count, _int start2);
   
   
   /**
    * Adds a uint16 to the end of buffer using Big Endian.
    */
   void addUInt16BE(_uint16 v);
   
   /**
    * Adds a uint16 to the end of buffer using Little Endian.
    */
   void addUInt16LE(_uint16 v);
   
   /**
    * Adds a uint16 to the end of buffer using target endianness.
    */
   void addUInt16(_uint16 v);
   
   /**
    * Adds a uint32 to the end of buffer using Big Endian.
    */
   void addUInt32BE(_uint32 v);
   
   /**
    * Adds a uint32 to the end of buffer using Little Endian.
    */
   void addUInt32LE(_uint32 v);
   
   /**
    * Adds a uint32 to the end of buffer using target endianness.
    */
   void addUInt32(_uint32 v);
   
   
   /**
    * Returns the number of bytes stored.
    */
   _int length() const;
   _int count() const;
   
   /**
    * Sets the number of bytes stored.
    * Remove the remaining or fill with zeros if higher.
    */
   _int length(_int len);
   _int count(_int len);
   
   /**
    * Gets current capacity.
    */
   _int capacity() const;
   
   /**
    * Sets the capacity.
    */
   _int capacity(_int cap);
   
   
   /**
    * Returns a pieze of the buffer.
    */
   Buffer *sub(_int len) const;
   
   /**
    * Returns a pieze of the buffer.
    */
   Buffer *sub(_int start, _int len) const;
   
   
   /**
    * Says if the buffer cointains no byte.
    */
   _bool empty() const;   
   
   /**
    * Removes all bytes (do no reduce capacity).
    */
   void clear();
   
   /**
    * Moves the buffer a number of bytes (positive ahead and negative backwards)
    */
   void move(_int count);
   
   /**
    * Discards some bytes in the buffer shortening the length.
    * If count is negative a hole of abs(count) zero bytes is made at index.
    */
   void erase(_int index, _int count);
   
   
   /**
    * Inserts a byte in the buffer shifting the tail.
    * It can discard a given number of bytes from the index
    * (eg if discard is 1 this method equals to set).
    */
   void insert(_int index, _byte b, _int discard = 0);
   
   /**
    * Inserts a buffer in the buffer shifting the tail.
    * It can discard a given number of bytes from the index
    * (eg if discard is the buffer length this method equals to set).
    */
   void insert(_int index, Buffer *b, _int discard = 0);
   
   
   /**
    * Finds a byte and replace all occurrences with other.
    * A negative start value means from the end (-1 means last character).
    */
   void replace(_byte find, _byte other, _int start = 0);
     
   /**
    * Finds a buffer and replace all occurrences with other.
    * A negative start value means from the end (-1 means last character).
    */
   void replace(Buffer *find, Buffer *other, _int start = 0);
   
   
   /**
    * Returns the raw data buffer. Use with care!
    */
   _byte *data();
   
   /**
    * Returns the raw data buffer as constant.
    */
   const _byte *data() const;

         
   /**
    * Compares itself with another buffer.
    */
   virtual _bool equals(Buffer *other) const;
   using Object::equals;
  
   /**
    * Generate a human readable string representing the buffer.
    */
   virtual String toString() const;
     
   /**
    * Ensure a minimum capacity in bytes.
    */
   void ensureCap(_int min);
  
    
protected:    
   /**
    * Copy a number of bytes of memory.
    */
   static void *memcpy(void *dst, const void *org, _int n);
   
   /**
    * Sets a number of bytes of memory with the given value.
    */
   static void *memset(void *buf, _byte val, _int n);
      
   /**
    * Compare a number of bytes in memory.
    */
   static _int memcmp(const void *buf1, const void *buf2, _int n);
   
   /**
    * Count the number of bytes until the first null.
    */
   static _int strlen(const void *buf);
   
   /**
    * Compare two raw strings.
    */
   static _int strcmp(const void *buf1, const void *buf2); 
};

