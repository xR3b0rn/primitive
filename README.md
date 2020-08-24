# primitive
C++ primitive data type wrapper
# Features
* Comparsion chaining
* STL support for `std::ostream`, `std::istream`, `std::hash`
* Member casting functions such as `to_s`, `to_ws`, `cast<T>`, ...
* Types are more restrictive than primitives in ISO C++, i.e. `i64_t var = ui64_t(0)` will error
# Usage
```C++
#include "primitive.h"

using namespace primitive;
using namespace primitive::literals;

template <class T>
struct Point
{
    T x, y;
};
template <class T>
struct Size
{
    T width, height;
};

int main()
{
    Size<i64_t> window{640_i64, 480_i64};
    Point<i64_t> pixel{100_i64, 100_i64};
    // Check if point is inbetween the window, if so, print the points location
    if (0_i64 < pixel.x < window.width && 0_i64 < pixel.y < window.height)
    {
        auto x = pixel.x.to<d_t>().to_s();
        auto y = pixel.y.to<d_t>().to_s();
        std::cout << "pixel.x=" << x << " pixel.y=" << y << std::endl;
    }
}
```
# Installation
Just copy the header into your project.
