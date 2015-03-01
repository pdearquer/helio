/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Texts formatting tests
 * Tests the Storage.Structure.Text.Format class.
 */
class FormatTest :
      public virtual Test
{
public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   FormatTest(TestFramework *framework);

   
   /**
    * Tests the Boolean conversions.
    */
   void boolean();
   
   /**
    * Tests the binary integers conversions.
    */
   void binary();
   
   /**
    * Tests the Integer conversions.
    */
   void integer();

   /**
    * Tests the Float conversions.
    */
   void floatClass();

   /**
    * Tests the Character conversions.
    */
   void character();

   /**
    * Tests the Pointer conversions.
    */
   void pointer();
};

