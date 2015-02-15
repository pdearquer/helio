/*
 * Copyright 2015 Pablo de Arquer
 * Licensed under the GPLv3 or higher (http://www.gnu.org/licenses)
 */

/** Root suite of all tests
 * Main suite that contains all the tests.
 * Its name is ignored.
 *
 * If you need to add any suite to the root, do it in the constructor
 * of this class.
 */
class RootSuite :
      public virtual TestSuite
{
public:
   /**
    * Build the tests tree.
    */
   RootSuite(TestFramework *framework);
};

