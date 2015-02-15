/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Texts formating tests
 * Tests the Storage.Strucutre.Text.Format class.
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
    * Tests the Boolean convertions.
    */
   void boolean();
   
   /**
    * Tests the binary integers convertions.
    */
   void binary();
   
   /**
    * Tests the Integer convertions.
    */
   void integer();

   /**
    * Tests the Float convertions.
    */
   void floatClass();

   /**
    * Tests the Character convertions.
    */
   void character();

   /**
    * Tests the Pointer convertions.
    */
   void pointer();
};

