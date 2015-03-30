# Building Helio #

Helio comes with its own [building tool](Builder.md), but building the builder in first instance is a recursive dilemma. The `PreBuild` folder solves this problem.

If your development environment and platform are GNU/Linux and AMD64 (x64), try to run `PreBuild/builder.x64`.

```
$ PreBuild/builder.x64
[Helio ready]
Helio Builder 0.1

Invalid arguments.
use: builder build [root]
```

If it works successfully go to the next section, but if not jump to PreBuild.

## Builder ##

Build Helio with the builder is very easy, just select the target "test" and call "make" to construct it:

```
$ PreBuild/builder.x64 test
[Helio ready]
Helio Builder 0.1

Entering root... OK
Loading source descriptors... OK
Loading build "test" descriptor... OK
Compiling build... OK
Generating compilation... OK

Build ready. Run "make" to start compilation.
$ make
Compiling Storage/Structure/Data/Object.cpp...
Compiling Storage/Structure/Data/Number.cpp...
...
Compiling Test/Storage/Structure/Suite.cpp...
Linking test...
Successfully build
$
```

If everything goes well you should get the result in `Build/test`. Try it out with:

```
$ Build/test --verbose
[Helio Public 0.0.1 dev ready]
[Helio Test framework]
Warning: Memory check not available.
Starting run over 40 tests.
SelfTest.simpleAsserts: Starting...
...
Storage.Structure.LinkedListTest.basic: finished OK in 0 millis
Testing finished with result: OK
$
```

The [Test](Test.md) page explains the command in detail.

## PreBuild ##

The `PreBuild` folder contains scripts to save and restore the construction files of the builder. However, the builder is currently not ready, so the target is the [testing command](Test.md).

Extract the files, build and run it with these lines:

```
$ PreBuild/unpack
Build files unpacked from: PreBuild/build.tgz
Run "make" to start compilation
$ make
Compiling Storage/Structure/Data/Object.cpp...
Compiling Storage/Structure/Data/Number.cpp...
...
Compiling Test/Storage/Structure/Suite.cpp...
Linking test...
Successfully build
$ Build/test --verbose
[Helio Public 0.0.1 dev ready]
[Helio Test framework]
Warning: Memory check not available.
Starting run over 40 tests.
SelfTest.simpleAsserts: Starting...
...
Storage.Structure.LinkedListTest.basic: finished OK in 0 millis
Testing finished with result: OK
$
```

Now is your turn to mess around :)


## Versions ##

In case you have problems, these are the versions I run in my computer:

```
$ g++ --version
g++ (Debian 4.7.2-5) 4.7.2
Copyright (C) 2012 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ make --version
GNU Make 3.81
Copyright (C) 2006  Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.

This program built for x86_64-pc-linux-gnu
$ uname -a
Linux sion 3.2.0-4-amd64 #1 SMP Debian 3.2.65-1+deb7u1 x86_64 GNU/Linux
```

I don't think the version of make is too important, but you are better off getting a modern G++ because Helio uses the `-std=c++11` flag.