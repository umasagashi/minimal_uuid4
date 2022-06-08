# minimal uuid4

## Introduction

*minimal uuid4* is a C++11 header only library for UUID4 generation.
This library has no dependencies other than C++11 and should work on most platforms.

**This library should not be used in any security-related code.**

## How to use

Copy `include/minimal_uuid4.h` to your project manually. Usage is as follows:

```c++
#include <iostream>

#include "minimal_uuid4.h"

int main() {
    minimal_uuid4::Generator gen;
    std::cout << gen.uuid4().hex() << std::endl;  // 89ecd845f4bb48368a7814e65d42570a
    std::cout << gen.uuid4().str() << std::endl;  // 437afb83-ef89-4851-b0e3-6d5adf000904
    return 0;
}
```

The above is all you can do with this library.
UUID version 1-3,5 are not supported.
This limitation is the reason why this library has no dependencies.

## License

MIT License

Note: For OSS projects, you do not need to copy the license file separately, as the header contains all the necessary
notices.
