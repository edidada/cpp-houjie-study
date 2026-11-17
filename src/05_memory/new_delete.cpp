// 侯捷《C++ 内存管理机制》的 C++17 重写。
// 考察：new 表达式的三步分解、类专属 operator new/delete、placement new。
#include <cstddef>
#include <iostream>
#include <new>

class Widget {
public:
    Widget() { std::cout << "  Widget::Widget()  this=" << this << "\n"; }
    ~Widget() { std::cout << "  Widget::~Widget() this=" << this << "\n"; }

    static void* operator new(std::size_t n) {
        std::cout << "  1) Widget::operator new(" << n << ")\n";
        return ::operator new(n);
    }

    static void operator delete(void* p, std::size_t n) noexcept {
        std::cout << "  Widget::operator delete(" << n << ")\n";
        ::operator delete(p);
    }

private:
    int data_[4];
};

int main() {
    std::cout << "sizeof(Widget)=" << sizeof(Widget) << "\n";

    std::cout << "-- new Widget --\n";
    // ① 调用 operator new 分配  ② void* 转型  ③ 调用构造函数
    Widget* w = new Widget;

    std::cout << "-- delete w --\n";
    // ① 调用析构函数  ② 调用 operator delete 释放
    delete w;

    std::cout << "-- placement new --\n";
    // 用 ::new 强制走全局 placement new：只构造，不分配内存
    alignas(Widget) unsigned char buf[sizeof(Widget)];
    Widget* p = ::new (buf) Widget();
    p->~Widget();

    return 0;
}
