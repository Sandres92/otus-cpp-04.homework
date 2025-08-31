#pragma once

#include <utility>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

/**
 * @brief Sfinae functions
 *
 * This .h file contains some functions, to
 * create ip string by Int, std::vector, std::string, std::tuple, with
 * some rules
 *
 */

namespace otus
{
    /**
     * @brief EnableIf struct, which help detect conditional and discard false conditional
     *
     * @param <in> Conditional. Conditional of EnableIf
     * @param <in> typename T. Contains type
     *
     *
     */
    template <bool conditional, typename T>
    struct EnableIf;

    /**
     * @brief EnableIf struct, which help detect conditional and discard false conditional
     *
     * @param <in> Conditional. Conditional of EnableIf
     * @param <in> typename T. Contains type
     *
     *
     */
    template <typename T>
    struct EnableIf<true, T>
    {
        using type = T;
    };

    /**
     * @brief IsSame struct, help detect two input T is same
     *
     * @param <in> typename T. First input type
     * @param <in> typename U. Second input type
     *
     *
     */
    template <typename T, typename U>
    struct IsSame
    {
        static constexpr bool value = false;
    };

    template <typename T>
    struct IsSame<T, T>
    {
        static constexpr bool value = true;
    };

    /**
     * @brief AllSame struct, help detect all input types is same
     *
     * @param <in> typename T. First input type
     * @param <in> typename... U. Other types is same
     *
     *
     */
    template <typename T, typename... U>
    struct AllSame
    {
        static constexpr bool value = false;
    };
    template <typename T>
    struct AllSame<T>
    {
        static constexpr bool value = true;
    };

    template <typename T, typename U, typename... Us>
    struct AllSame<T, U, Us...>
    {
        static constexpr bool value = IsSame<T, U>::value && AllSame<T, Us...>::value;
    };

    // template <typename T, typename U, typename... Us>
    // struct IsSame<T, U, Us...>
    //{
    //     static constexpr bool value = IsSame<T, U> && IsSame<T, Us...>::value;
    // };

    /**
     * @brief IsInt varidble detect integer numbers
     *
     *
     */
    namespace Number
    {
        template <typename NoInteger>
        inline constexpr bool IsInt = false;
        // template <>
        // inline constexpr bool IsInt<int> = true;
        template <>
        inline constexpr bool IsInt<int8_t> = true;
        template <>
        inline constexpr bool IsInt<int16_t> = true;
        template <>
        inline constexpr bool IsInt<int32_t> = true;
        template <>
        inline constexpr bool IsInt<int64_t> = true;
    }

    /**
     * @brief HasToString detect input type can be convert to std::string
     *
     * @param <in> typename T. Type, which check.
     *
     * @return bool value, if type T can be convert
     *
     */
    template <typename T>
    struct HasToString
    {
    private:
        static int convert(...);
        template <typename U>
        static decltype(std::to_string(std::declval<U>())) convert(const U &);

    public:
        static constexpr bool value =
            !IsSame<int, decltype(convert(std::declval<T>()))>::value;
    };

    /**
     * @brief print_ip for integer numbers
     *
     * @param <in> typename T. Type, which check.
     *
     *  @details In input Type ckeck T is Integer, and also check, if this type
     * can be convert to sting. If yes, function can be retutn std::string
     *
     *
     * @return std::string. Ip as string
     *
     */
    template <typename T>
    typename EnableIf<Number::IsInt<T> &&
                          HasToString<T>::value,
                      std::string>::type
    print_ip(T val)
    {
        // std::cout << "Int =" << val << "\n";
        std::string result{};
        auto size = sizeof(T);
        result.reserve((size * 3) + (size - 1));

        for (int i = size - 1; i >= 0; --i)
        {
            unsigned char byte = val >> 8 * i;
            int number = static_cast<int>(byte);

            result += std::to_string(number) + ".";
        }

        result.pop_back();

        return result;
    }

    /**
     * @brief HasFunction struct help detect some function in type T
     *
     * @param <in> typename T. Type, which check.
     *
     *  @details In input Type ckeck such function, as begin, end and size, with
     * correct returned type. If all this function return char, then typename T not
     * std collection
     *
     * @return value true if typename T is std collection
     *
     */
    template <typename T>
    struct HasFunction
    {
    private:
        static char begin(...);
        template <typename U>
        static decltype(std::declval<U>().begin()) begin(const U &);

        static char end(...);
        template <typename U>
        static decltype(std::declval<U>().end()) end(const U &);

        static char size(...);
        template <typename U>
        static decltype(std::declval<U>().size()) size(const U &);

    public:
        static constexpr bool value =
            !IsSame<char, decltype(begin(std::declval<T>()))>::value &&
            !IsSame<char, decltype(end(std::declval<T>()))>::value &&
            !IsSame<char, decltype(size(std::declval<T>()))>::value;
    };

    /**
     * @brief print_ip for std collection
     *
     * @param <in> typename T. Type, which check.
     *
     *  @details In input Type ckeck T is has correct begin, end, size function also
     * check typename T is not string. For strin have other print_ip function
     *
     *
     * @return std::string. Ip as string
     *
     */
    template <typename T>
    typename EnableIf<HasFunction<T>::value &&
                          HasToString<decltype(*std::declval<T>().begin())>::value &&
                          !IsSame<T, std::string>::value,
                      std::string>::type
    print_ip(const T &val)
    {
        std::string result{};
        result.reserve((val.size() * 3) + (val.size() - 1));

        for (auto it = val.begin(); it != val.end(); ++it)
        {
            result += std::to_string(*it) + ".";
        }

        result.pop_back();

        return result;
    }

    /**
     * @brief print for std::string
     *
     * @param <in> typename T. Type, which check.
     *
     *  @details not convert to ip string, just return input std::string
     *
     * @return std::string
     *
     */
    template <typename T>
    typename EnableIf<IsSame<T, std::string>::value, std::string>::type
    print_ip(const T &val)
    {
        return val;
    }

    namespace Tuple
    {
        template <typename NoIntegerTuple>
        inline constexpr bool IsTuple = false;

        template <typename U>
        inline constexpr bool IsTuple<std::tuple<U>> = true;

        template <typename... U>
        inline constexpr bool IsTuple<std::tuple<U...>> = true;
    };

    // std::string TupleToStringImpl(const std::tuple<> &)
    //{
    //     return {};
    // }

    /**
     * @brief convert std::tuple, one value, to std::string
     *
     * @param <in> typename T. Type, which check.
     * @param <in> typename... Rest>. Other type.
     *
     * @details Convert typename T to string. And check typename... Rest is not las element
     * and call TupleToStringImpl recursivity
     *
     * @return std::tuple one element as std::string
     *
     */
    template <typename T, typename... Rest>
    std::string TupleToStringImpl(const std::tuple<T, Rest...> &val)
    {
        std::string str = std::to_string(std::get<0>(val));
        if constexpr (sizeof...(Rest) > 0)
        {
            str += "." + TupleToStringImpl(std::apply([](auto, auto... rest)
                                                      { return std::make_tuple(rest...); }, val));
        }
        return str;
    }

    /**
     * @brief convert all std::tuple, to std::string
     *
     * @param <in> typename T. Type, which check.
     * @param <in> typename... Rest>. Other type.
     *
     *
     * @return std::tuple -> std::string val1.val2.val3...
     *
     */
    template <typename T, typename... Rest>
    std::string TupleToString(const std::tuple<T, Rest...> &val)
    {
        std::string str = TupleToStringImpl(val);
        return str;
    }

    /**
     * @brief print_ip for std::tuple to ip sting
     *
     * @param <in> typename T. first type
     * @param <in> typename... U>. Other types of tuple
     *
     * @details In input Type T and ...U ckeck that all type is same, also for this
     * type chek Type T can be convert to std::string
     *
     *
     * @return std::string. Ip as string
     *
     */
    template <typename T, typename... U>
    typename EnableIf<AllSame<T, U...>::value &&
                          HasToString<T>::value,
                      std::string>::type
    print_ip(const std::tuple<T, U...> &val)
    {
        return TupleToString(val);
    }
}