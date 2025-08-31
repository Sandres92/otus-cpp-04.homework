#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <list>

#include <tuple>

#include "lib.h"
#include "lib_sfinae.h"

using namespace std;

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */
int main()
{
    // int a = 1;
    // otus::print_ip(a);

    std::string s = otus::print_ip(int8_t{-1}); // 255
    std::cout << s << "\n";

    s = otus::print_ip(int16_t{0}); // 0.0
    std::cout << s << "\n";

    s = otus::print_ip(int32_t{2130706433}); // 127.0.0.1
    std::cout << s << "\n";

    s = otus::print_ip(int64_t{8875824491850138409}); // 123.45.67.89.101.112.131.41
    std::cout << s << "\n";

    s = otus::print_ip(std::string{"Hello, World !"}); // Hello, World!
    std::cout << s << "\n";

    s = otus::print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
    std::cout << s << "\n";

    s = otus::print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
    std::cout << s << "\n";

    s = otus::print_ip(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0
    std::cout << s << "\n";

    // std::cout << "HasFoo has foo(): " << otus::HasFunction<std::vector<int>>::value << std::endl; // true
    // std::cout << "HasFoo has foo(): " << otus::HasFunction<int>::value << std::endl;              // true

    return 0;
}
