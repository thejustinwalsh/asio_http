# C++ Embeddable HTTP Server
Asio + http-parser from Joyent = fun.


# Introduction
You can create your own high performance HTTP based services in seconds. This library uses `http-parser` library from Joyent which is based on the `nginx` http parser and powers `nodejs`.

Uses stand-alone [ASIO](http://think-async.com/Asio) library and C++11 without the requirement of boost like the original implementation.

# Building
CMake files need to be updated. Considering using [Conan](https://conan.io) package manager.

# License
The MIT License (MIT)
Copyright (c) 2016 thejustinwalsh LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
