/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Format numbers into text and vice versa.
 * Format numbers (and some other primitive types) into text and
 * analyse text back to extract numbers.
 * This class also stored the convertion configuration.
 *
 * For normal formating you can make use of the default formatter:
 *    String my_str_var = Format::def()->toString(my_int_var);
 *
 * TODO: Implement native types?
 */
class Format : 
      public virtual Object
{
protected:
   /**
    * Default formater.
    */
   static Format *_default;


   /**
    * Default base.
    */
   _int _base;
   
   /**
    * Digits array.
    */
   StringBuffer _digits;
   
   /**
    * Say if ignore case in digit recorgition.
    */
   _bool _igncase;
   
   /**
    * Minimum number of digits (padding with 0s).
    * In decimal numbers this is only the integer part.
    */
   _int _minDigits;      
   
   /**
    * Say if print plus sign in positive values.
    */
   _bool _sign;
   
   /**
    * Number of decimal digits.
    */
   _int _precision;
   

public:
   /**
    * Create a formater with the default configuration.
    */
   Format();
   
   /**
    * Copy constructor.
    */
   Format(Format *fmt);
   
   
   /**
    * Returns a reference to the default formater.
    */
   static Format *def();
   
   
   /**
    * Parse a string to extract a boolean.
    */
   virtual _bool toBool(const String &str);
   
   /**
    * Parse a boolean from a window starting at the given pointer.

    * If successful, the pointer will point to the last character processed.
    */
   virtual _bool toBool(Window *win, WindowPointer &p);
   
   /**
    * Parse a boolean in a region of a window.
    */
   virtual _bool toBool(Window *win, const WindowPointer &from, const WindowPointer &to);
   

   /**
    * Parse a string to extract a integer number.
    */
   virtual _int toInt(const String &str);
   
   /**
    * Parse a integer from a window starting at the given pointer.
    * If successful, the pointer will point to the last character processed.
    */
   virtual _int toInt(Window *win, WindowPointer &p);
   
   /**
    * Parse a integer in a region of a window.
    */
   virtual _int toInt(Window *win, const WindowPointer &from, const WindowPointer &to);
   
   
   /**
    * Parse a string to extract a bynary number.
    */
   virtual __uint64 toUInt64(const String &str);
   
   /**
    * Parse a bynary number from a window starting at the given pointer.
    * If successful, the pointer will point to the last character processed.
    */
   virtual __uint64 toUInt64(Window *win, WindowPointer &p);
   
   /**
    * Parse a bynary number in a region of a window.
    */
   virtual __uint64 toUInt64(Window *win, const WindowPointer &from, const WindowPointer &to);
   

   /**
    * Parse a string to extract a signed bynary number.
    */
   virtual __sint64 toSInt64(const String &str);
   
   /**
    * Parse a signed bynary number from a window starting at the given pointer.
    * If successful, the pointer will point to the last character processed.
    */
   virtual __sint64 toSInt64(Window *win, WindowPointer &p);
   
   /**
    * Parse a signed bynary number in a region of a window.
    */
   virtual __sint64 toSInt64(Window *win, const WindowPointer &from, const WindowPointer &to);

   
   /**
    * Parse a string to extract a floating point number.
    */
   virtual _float toFloat(const String &str);
   
   /**
    * Parse a float from a window starting at the given pointer.
    * If successful, the pointer will point to the last character processed.
    */
   virtual _float toFloat(Window *win, WindowPointer &p);
   
   /**
    * Parse a float in a region of a window.
    */
   virtual _float toFloat(Window *win, const WindowPointer &from, const WindowPointer &to);
   
   
   /**
    * Parse a string to extract a single character.
    */
   virtual Character toChar(const String &str);


   /**
    * Parse a string to extract a pointer.
    */
   virtual _pointer toPointer(const String &str);
   
   /**
    * Parse a pointer from a window starting at the given pointer.
    * If successful, the pointer will point to the last character processed.
    */
   virtual _pointer toPointer(Window *win, WindowPointer &p);
   
   /**
    * Parse a pointer in a region of a window.
    */
   virtual _pointer toPointer(Window *win, const WindowPointer &from, const WindowPointer &to);


#if 0
   /**
    * Parse a string to extract a date.
    */
   Date toDate(const String &str);
#endif


   /**
    * Format a boolean.
    */
   virtual String toString(_bool b);
   
   /**
    * Format a boolean.
    */
   virtual Buffer *toBuffer(_bool b);


   /**
    * Format a number.
    */
   virtual String toString(_int num);
   
   /**
    * Format a number in a specific base.
    */
   virtual String toString(_int num, _int base);
   
   /**
    * Format a number.
    */
   virtual Buffer *toBuffer(_int num);
   
   /**
    * Format a number in a specific base.
    */
   virtual Buffer *toBuffer(_int num, _int base);
   
   
   /**
    * Format a binary number.
    */
   virtual String toString(__uint64 num);
   
   /**
    * Format a binary number in a specific base.
    */
   virtual String toString(__uint64 num, _int base);
   
   /**
    * Format a binary number.
    */
   virtual Buffer *toBuffer(__uint64 num);
   
   /**
    * Format a binary number in a specific base.
    */
   virtual Buffer *toBuffer(__uint64 num, _int base);
   
   
   /**
    * Format a signed binary number.
    */
   virtual String toString(__sint64 num);
   
   /**
    * Format a signed binary number in a specific base.
    */
   virtual String toString(__sint64 num, _int base);
   
   /**
    * Format a signed binary number.
    */
   virtual Buffer *toBuffer(__sint64 num);
   
   /**
    * Format a signed binary number in a specific base.
    */
   virtual Buffer *toBuffer(__sint64 num, _int base);
   
   
   /**
    * Format a floating point number.
    */
   virtual String toString(_float num);
   
   /**
    * Format a floating point number.
    */
   virtual Buffer *toBuffer(_float num);
   
   /**
    * Format a character.
    */
   virtual String toString(_char c);
   
   /**
    * Format a character.
    */
   virtual Buffer *toBuffer(_char c);
   
   
   /**
    * Format a pointer.
    */
   virtual String toString(_pointer p);
   
   /**
    * Format a pointer.
    */
   virtual Buffer *toBuffer(_pointer p);
   
   
   /**
    * Format a date.
    */
   virtual String toString(const Date &date);
   
   
   /**
    * C style print formated function.
    * Only valid compiler primitive arguments.
    */
   static String printf(String fmt, ...);
   
   
   /**
    * Get the default base.
    */
   _int base();
   
   /**
    * Set the default base.
    */
   _int base(_int b);
   
   /**
    * Get the digits array.
    */
   String digits();

   /**
    * Set the digits array.
    */
   String digits(String dig);

   /**
    * Say if ignore case in digit recorgition.
    */
   _bool igncase();

   /**
    * Say if ignore case in digit recorgition.
    */
   _bool igncase(_bool ignore);
   
   /**
    * Minimum number of digits (padding with 0s).
    */
   _int minDigits();

   /**
    * Minimum number of digits (padding with 0s).
    */
   _int minDigits(_int min);
   
   /**
    * Say if print plus sign in positive values.
    */
   _bool sign();
   
   /**
    * Say if print plus sign in positive values.
    */
   _bool sign(_bool plus);
   
   /**
    * Get the number of decimal digits.
    */
   _int precision();

   /**
    * Set the number of decimal digits.
    */
   _int precision(_int pre);
};

