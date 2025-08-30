#pragma once

#include <utility>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>

namespace otus
{
    template <bool conditional, typename T>
    struct EnableIf;

    template <typename T>
    struct EnableIf<true, T>
    {
        using type = T;
    };

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

            result += std::to_string(number);
            if (i != 0)
            {
                result += ".";
            }
        }

        std::cout << result << "\n";
        //  std::copy(&val,
        //            &val + sizeof(T),
        //            bytes);
        //
        //  for (int i = sizeof(T) - 1; i <= 0; --i)
        //{
        //     std::cout << static_cast<int>(bytes[i]) << " ";
        // }
        return result;
    }

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
            result += std::to_string(*it);
            if (it != val.end() - 1)
            {
                result += ".";
            }
        }

        std::cout << result << "\n";
        return result;
    }

    template <typename T>
    typename EnableIf<IsSame<T, std::string>::value, std::string>::type
    print_ip(const T &val)
    {
        std::cout << "std::string =" << val << "\n";
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

    template <typename T, typename... Rest>
    std::string TupleToString(const std::tuple<T, Rest...> &val)
    {
        std::string str = TupleToStringImpl(val);
        return str;
    }

    template <typename T, typename... U>
    typename EnableIf<AllSame<T, U...>::value &&
                          HasToString<T>::value,
                      std::string>::type
    print_ip(const std::tuple<T, U...> &val)
    {
        std::cout << "tuple =" << std::get<0>(val) << " , " << std::get<1>(val) << "\n";
        std::string result = TupleToString(val);
        std::cout << result << "\n";
        return result;
    }
}