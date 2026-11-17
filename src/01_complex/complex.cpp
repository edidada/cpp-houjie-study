// 侯捷《C++ 面向对象高级编程（上）》Complex 例子的 C++17 重写。
// 考察：初始化列表、const 正确性、+= 返回引用、+ 按值返回临时对象。
#include <iostream>

class Complex {
public:
    Complex(double r = 0.0, double i = 0.0) : re_(r), im_(i) {}

    double real() const { return re_; }
    double imag() const { return im_; }

    // 成员函数：修改自身，返回引用以支持 a += b += c 的链式写法
    Complex& operator+=(const Complex& rhs) {
        re_ += rhs.re_;
        im_ += rhs.im_;
        return *this;
    }

private:
    double re_;
    double im_;
};

// 非成员 operator+：结果是一个新对象，必须按值返回（绝不能返回引用）
inline Complex operator+(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.real() + rhs.real(), lhs.imag() + rhs.imag());
}

inline std::ostream& operator<<(std::ostream& os, const Complex& c) {
    return os << "(" << c.real() << "," << c.imag() << ")";
}

int main() {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);

    const Complex sum = c1 + c2;       // 产生临时对象，再拷贝/移动到 sum
    std::cout << "c1=" << c1 << " c2=" << c2 << " c1+c2=" << sum << "\n";

    Complex c3;
    c3 += c1 += c2;                    // 返回引用才支持链式
    std::cout << "after chained +=: c1=" << c1 << " c3=" << c3 << "\n";

    const bool ok = sum.real() == 4.0 && sum.imag() == 6.0 &&
                    c3.real() == 4.0 && c3.imag() == 6.0;
    return ok ? 0 : 1;
}
