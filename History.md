# History and motivation #

Several years ago, I decided to start making an Operating System. I had some ideas and a lot of curiosity about the internals of the computers...

## Pre-Helio era ##

My first try was to learn assembler and write a 16 bits basic system. I thought that the assembler would make my system faster, but in fact it just made it harder to maintain. It became pretty obvious after a few hundreds of lines.

My next idea was to use C. I made another system that used the first one as a boot loader and drew some graphics (using a BIOS call and the framebuffer). I was aiming for some kind of Graphical User Interface but I found out that I spent most of the time dealing with lists and other structures.

## The beginnings of Helio ##

An Object Oriented language looked more suitable and I didn't want to fall in the same mistake of making a system too focused on one specific architecture. I liked the idea of an independent assembler so I went for Java. I called this system `Helio`.

Java is a nice language, but it hadn't a way to compile to a real architecture so I wrote a byte code (.class) to i386 assembler (GNU gas) converter. I used some interrupt calls to fulfil the VM needs and a minimal Java runtime classes and native functions.

I also created an architecture simulator. That was easy in Java, but I soon realised that the managed memory (garbage collector) is of no good in large projects. In addition it makes an OS non-deterministic and unable to manage one of the most precious resources; the memory.

## Helio Boot ##

I also suspected that a modern processor is more complex than what I thought, so I grabbed the old C attempt and remade it as `Helio Boot`. The intention of this system was simply to learn.

It ended up being a bootable floppy disk that jumps to protected mode and brings up a small console. The few commands it has, merely boast about the system features: multitasking, CPU info, PCI, SATA, PS2, BIOS calls (jumping back to real mode for an instant), graphics...

## Helio 2 ##

But at that time, it was apparent that a bunch of drivers won't make an Operating System. In fact the Java experiment shown that the components' interface (API) is far more important than a particular implementation. Besides, most of the job of working with devices, memory pages or filesystems is about dealing with structures (lists, trees...).

So I started from scratch once again. I am glad that this is only a hobby and not a business, otherwise I would have struggled... This time I called it `Helio 2`, and put on it all the lessons I had learnt.

I chose C++, which is a really good language, supports OOP and gives you full control over the memory, but I suffered from its flexibility and ended up sticking to a strict [Programming Style](Coding.md) to avoid nasty problems.

Eventually I found out that in order to get a good scalability and performance, the structures or containers must be chosen carefully based on the use you give to them. So I restarted making this module, which broke most of the rest...

## Helio Public ##

After 15 years of doing and undoing experiments, I decided to publish my work. I gathered the parts working from `Helio 2` and created `Helio Public`, which is the version available in this repository. I'll keep working on it and adding more modules from `Helio 2` as it supports them.

Making an Operating System is a massive task that never ends and my spare time is very limited, so I decided to release it and share my experiences in case someone could benefit from them.

Feel free to use, modify, fork or redistribute any part of it, but please drop me a line, it is always pleasant to know that someone else is using your work.