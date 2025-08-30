#define BOOST_TEST_MODULE test_ip_filter

#include "lib.h"
#include "lib_sfinae.h"

#include <boost/test/unit_test.hpp>

using namespace otus;

BOOST_AUTO_TEST_SUITE(test_ip_filter)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(2 > 0);
}

BOOST_AUTO_TEST_CASE(test_valid_sum)
{
    BOOST_CHECK(1 + 1 == 2);
}

BOOST_AUTO_TEST_CASE(test_sfinae_1)
{
    std::string ip_int8_tStr = otus::print_ip(int8_t{-1}); // 255
    BOOST_CHECK(ip_int8_tStr == "255");
}

BOOST_AUTO_TEST_CASE(test_sfinae_2)
{
    std::string ip_int8_tStr = otus::print_ip(int16_t{0}); // 0.0
    BOOST_CHECK(ip_int8_tStr == "0.0");
}

BOOST_AUTO_TEST_CASE(test_sfinae_3)
{
    std::string ip_int8_tStr = otus::print_ip(int32_t{2130706433}); // 127.0.0.1
    BOOST_CHECK(ip_int8_tStr == "127.0.0.1");
}

BOOST_AUTO_TEST_CASE(test_sfinae_4)
{
    std::string ip_int8_tStr = otus::print_ip(int64_t{8875824491850138409}); // 123.45.67.89.101.112.131.41
    BOOST_CHECK(ip_int8_tStr == "123.45.67.89.101.112.131.41");
}

BOOST_AUTO_TEST_CASE(test_sfinae_5)
{
    std::string ip_int8_tStr = otus::print_ip(std::string{"Hello, World !"}); // Hello, World!
    BOOST_CHECK(ip_int8_tStr == "Hello, World !");
}

BOOST_AUTO_TEST_CASE(test_sfinae_6)
{
    std::string ip_int8_tStr = otus::print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
    BOOST_CHECK(ip_int8_tStr == "100.200.300.400");
}

BOOST_AUTO_TEST_CASE(test_sfinae_7)
{
    std::string ip_int8_tStr = otus::print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
    BOOST_CHECK(ip_int8_tStr == "400.300.200.100");
}

BOOST_AUTO_TEST_CASE(test_sfinae_8)
{
    std::string ip_int8_tStr = otus::print_ip(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0
    BOOST_CHECK(ip_int8_tStr == "123.456.789.0");
}
BOOST_AUTO_TEST_SUITE_END()