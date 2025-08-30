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

    template <typename X, typename Y>
    struct Equal
    {
        static constexpr bool value = false;
    };

    template <typename X>
    struct Equal<X, X>
    {
        static constexpr bool value = true;
    };

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
    typename EnableIf<HasFunction<T>::value && !IsSame<T, std::string>::value, void>::type
    print_ip(T val)
    {
        std::cout << "Vector/List size " << val.size() << "\n";
    }

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
    typename EnableIf<Number::IsInt<T>, void>::type
    // typename EnableIf<std::is_integral<T>(), void>::type
    print_ip(T val)
    {
        std::cout << "Int =" << val << "\n";
    }

    template <typename T>
    typename EnableIf<IsSame<T, std::string>::value, void>::type
    print_ip(T val)
    {
        std::cout << "std::string =" << val << "\n";
    }

    // template <typename T>
    // struct has_begin
    //{
    // private:
    //     // Перегрузка с многоточием для случая, когда begin() не существует
    //     static int check(...);
    //
    //    // Специализация для случая, когда begin() существует
    //    template <typename U>
    //    static decltype(std::declval<U>().begin()) check(const U &);
    //
    // public:
    //    // Проверяем, что check() возвращает не int (это значит, что begin() существует)
    //    static constexpr bool value = !std::is_same<int, decltype(check(std::declval<T>()))>::value;
    //};

    namespace Tuple
    {
        template <typename NoIntegerTuple>
        inline constexpr bool IsTuple = false;

        template <typename U>
        inline constexpr bool IsTuple<std::tuple<U>> = true;

        template <typename... U>
        inline constexpr bool IsTuple<std::tuple<U...>> = true;
    };

    // template <typename T>
    // typename EnableIf<Tuple::IsTuple<T>, void>::type
    // print_ip(const T &val)
    //{
    //     std::cout << "tuple =" << std::get<0>(val) << " , " << std::get<1>(val) << "\n";
    // }

    template <typename T, typename... U>
    typename EnableIf<AllSame<T, U...>::value, void>::type
    // void
    print_ip(const std::tuple<T, U...> &val)
    {
        std::cout << "tuple =" << std::get<0>(val) << " , " << std::get<1>(val) << "\n";
    }
}