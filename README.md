# detector
A header-only C++ library for checking the host os/compiler in a modern way.


## Getting started
The library is header-only, so you just need to clone it from Github and `#include` it. That's all. No dependency. No `#include`s (it doesn't even depend on the standard library).


## Example

``` c++
#include <iostream>
    
void print_os()
{
    if constexpr(is_windows_v)
    {
        std::cout << "windows";
    }
    else if constexpr (is_linux_v)
    {
        std::cout << "linux";
    }
    else if constexpr (is_macos_v)
    {
        std::cout << "macos";
    }
}

int main()
{
    print_os();
}
```

There are other os-es checks supported. If you want to contribute, please create a(n) issue/pull request.
