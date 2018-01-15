# Short Vector Optimisation #

This repository contains the effects of an effort to implement a drop-in replacement of `std::vector` employing 'small content optimisation'. That is, store the first few items in a static array, and only after crossing some threshold switch to dynamic storage.

The implementation is not finished, as at some point I abandoned the project. All the work was not in vane, however, as I learned a lot during the process.

## Motivation ##

Some time ago I worked on an application which at some point during runtime processed and moved around a huge number of small arrays of values. The number of items in each array was in principle arbitrary and depending on the input data, so the arrays were represented by `std::vector`s. However, most of the time, especially in case of one enormous input project, the arrays were really short -- over 95% of them were 8 items or shorter.

Even though profiling the application did not show `std::vector` processing as explicit bottlenecks, I nevertheless wanted to experiment and see whether using short-content-optimised vectors could improve the runtime performance. I hoped for drastically reducing the number of memory allocations (and possibly fragmentation) and accessing the data in more cache-friendly way.

## Alternatives ##

When I started the project I was not aware that the excellent [boost](http://www.boost.org) libraries contain `boost::container::small_vector`, which does exactly what I wanted. At some point I did notice its existence and gave it a try, only to find out that at the time the implementation was incomplete and very buggy. I do not know what the state is now, but I expect the situation improved.

## Plan ##

I did not have a clear plan of which steps to take. But I did know that I wanted to start with a simple and working implementation missing most or all valid optimisations and improve the code in small increments with aid of tests. Otherwise, I would get bogged down with all the details and get flooded with bugs.

My first thought was to dig up my own project where I implemented (just for fun and education purposes) the STL's `std::vector` from scratch and extend the implementation using TDD methodology.

## Unit tests ##

I spent some time looking for comprehensive unit test suite for library implementation of `std::vector` in hope of reusing it for my version, only to find out that apparently none such beast exists. The library shipped with GCC (or rather G++) had mostly ad-hoc tests covering some defects. I did not check other library implementations, though.

Due to lack of tests I decided not to reuse my old `vector` implementation. Instead, I created a thin wrapper delegating all the calls to underlying `std::vector` and wrote unit tests for that. At least I was writing tests for code proven in countless battles on many architectures and systems and I could be sure that if a test failed or crashed, it was due to the testing code and not the tested code. One loose end less to chase.

The unit test suite I created is not as comprehensive as I would hope for. It lacks checks for algorithmic complexity guaranties or for number of allocations, but was still a major effort to write.

## Implementation ##

This implementation covers almost the whole `std::vector` interface. The notable exceptions are the lack of `Alloc` template argument and lack of `swap` member function. I removed the latter once I realized it cannot be implemented as standard-mandated constant-time operation while the contained items are in static array. It should be put back, nonetheless.

## To do ##

As I mentioned above, this project is not finished. At some point I stopped working on the original application and was too busy to invest the time to finish this project without a clear motivation.

There are many things that should be done to declare this work *complete* or *production-grade*.

At least the following come to my mind:
* add `allocator` template argument (defaulting to `std::vector::allocator_type`)
* ensure proper alignment of the static array
* reduce the memory footprint by cleverly putting most private variables into a `union`
* use assignment instead of copy-constructors in appropriate places
* make vectors of different static size related types
* extend the unit test suite to cover allocations and algorithmic complexity guaranties
* update the implementation to the C++11 standard

## License ##

This project is released under **MIT/X11** license, so feel free to do anything you like with it.

