// 侯捷《STL 标准库与泛型编程》的 C++17 重写（简化版 iterator_traits）。
// 考察：类模板、偏特化、萃取（traits）、编译期类型计算。
#include <iostream>
#include <type_traits>

// 泛化版本：假设迭代器自己内嵌 value_type
template <typename Iter>
struct my_traits {
    using value_type = typename Iter::value_type;
};

// 偏特化版本：原生指针没有内嵌类型，需要单独萃取
template <typename T>
struct my_traits<T*> {
    using value_type = T;
};

// 算法只依赖 traits，不依赖迭代器的具体类型 —— 这就是 GP 的解耦
template <typename Iter>
typename my_traits<Iter>::value_type sum(Iter first, Iter last) {
    typename my_traits<Iter>::value_type acc{};
    for (; first != last; ++first) acc += *first;
    return acc;
}

// 一个带内嵌 value_type 的最简迭代器
struct SimpleIter {
    using value_type = int;
    int* p;
    int& operator*() const { return *p; }
    SimpleIter& operator++() {
        ++p;
        return *this;
    }
    bool operator!=(const SimpleIter& rhs) const { return p != rhs.p; }
};

int main() {
    int raw[] = {1, 2, 3, 4};

    const int a = sum(raw, raw + 4);                       // 走偏特化
    const int b = sum(SimpleIter{raw}, SimpleIter{raw + 4});  // 走泛化

    std::cout << "指针范围求和 = " << a << "\n";
    std::cout << "类迭代器求和 = " << b << "\n";

    static_assert(std::is_same_v<my_traits<int*>::value_type, int>);
    static_assert(std::is_same_v<my_traits<SimpleIter>::value_type, int>);

    return (a == 10 && b == 10) ? 0 : 1;
}
