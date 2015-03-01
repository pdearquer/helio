/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** String tests
 * Tests the Storage.Structure.Data.String class.
 */
class StringTest :
      public virtual Test
{
public:
   /**
    * Add all the test cases.
    * @param framework Test framework reference
    */
   StringTest(TestFramework *framework);


   /**
    * Basic String tests.
    */
   void string();

   /**
    * Basic StringBuffer tests.
    */
   void stringBuffer();

   /**
    * Addition operator tests.
    */
   void addition();

   /**
    * Edition of StringBuffers
    */
   void stringBufferEdit();
};

