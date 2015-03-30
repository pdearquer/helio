# Modules #

Helio is divided into modules. A module is generally a package (or namespace) which has a function by its own, although modules can depend on others. There is no hard division among them, it is more of a functional organisation.

This is the list of modules:

## Test Framework ##
It has all the features that you would expect of a modern test framework: Test units, suites, timeout, memory cage (pending on the Memory module)... Read more on the [Test Framework](Test.md) page.

## Collections Framework ##
A set of generic [containers](Collections.md) which is currently under construction. It is a core module that is holding many others and so has become the highest priority now.

## Text Processing Unit ##
Tools to [process text](TextUnit.md) buffers and character flows based on a moving window. It is working but lacks limits.

## Builder ##
Helio has its own [building system](Builder.md) that allows configure the construction, selecting only the bits that you need. This module is currently pending on the XML.