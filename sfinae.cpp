#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <list>

#include <tuple>

#include "lib.h"
#include "lib_sfinae.h"

using namespace std;

int main()
{
    std::string str = "123";

    // int8_t x_8 = -1;
    // int16_t x_16 = 0;
    // int32_t x_32 = 2130706433;
    // int64_t x_64 = 8875824491850138409;

    int a = 1;
    otus::print_ip(a);

    int8_t x_8 = -1;
    otus::print_ip(x_8);

    int16_t x_16 = 0;
    otus::print_ip(x_16);

    int32_t x_32 = 2130706433;
    otus::print_ip(x_32);

    int64_t x_64 = 8875824491850138409;
    otus::print_ip(x_64);

    std::vector v{1, 2, 3};
    otus::print_ip(v);

    std::vector l{4, 6, 6};
    otus::print_ip(l);

    std::string s = "Hello world!";
    otus::print_ip(s);

    // float f = 1.0f;
    // otus::print_ip(f);

    std::tuple<int, int> t{1, 1};
    otus::print_ip(t);

    std::cout << "HasFoo has foo(): " << otus::HasFunction<std::vector<int>>::value << std::endl; // true
    std::cout << "HasFoo has foo(): " << otus::HasFunction<int>::value << std::endl;              // true

    return 0;
}

int main_int64_t()

{
    std::string str;

    int64_t x = 8875824491850138409;
    unsigned char bytes[sizeof(x)];
    std::copy(&x,
              &x + sizeof(x),
              bytes);

    for (int i = 0; i != sizeof(x); ++i)
    {
        std::cout << static_cast<int>(bytes[i]) << " ";
    }

    return 0;
}

int main_int32_t()
{
    int32_t x = 2130706433;
    unsigned char bytes[sizeof(x)];
    std::copy(static_cast<const unsigned char *>(static_cast<const void *>(&x)),
              static_cast<const unsigned char *>(static_cast<const void *>(&x)) + sizeof(x),
              bytes);

    for (int i = 0; i != sizeof(x); ++i)
    {
        std::cout << static_cast<int>(bytes[i]) << " ";
    }

    return 0;
}

int main_int_16()
{
    int16_t x = 0;
    unsigned char bytes[sizeof(x)];
    std::copy(static_cast<const unsigned char *>(static_cast<const void *>(&x)),
              static_cast<const unsigned char *>(static_cast<const void *>(&x)) + sizeof(x),
              bytes);

    for (int i = 0; i != sizeof(x); ++i)
    {
        std::cout << static_cast<int>(bytes[i]) << " ";
    }

    return 0;
}

int main_int_8()
{
    int8_t x = -1;
    unsigned char bytes[sizeof(x)];
    std::copy(static_cast<const char *>(static_cast<const void *>(&x)),
              static_cast<const char *>(static_cast<const void *>(&x)) + sizeof x,
              bytes);

    for (int i = 0; i != sizeof(x); ++i)
    {
        std::cout << static_cast<int>(bytes[i]) << " ";
    }

    return 0;
}