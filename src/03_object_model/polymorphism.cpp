// 侯捷《C++ 面向对象高级编程（下）· 对象模型》的 C++17 重写。
// 考察：虚函数、动态绑定、vptr 带来的 sizeof 变化、基类虚析构。
#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;                  // 基类析构必须是 virtual
    virtual double area() const { return 0.0; }
    virtual const char* name() const { return "Shape"; }
};

class Circle : public Shape {
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159265358979323846 * r_ * r_; }
    const char* name() const override { return "Circle"; }

private:
    double r_;
};

class Rect : public Shape {
public:
    Rect(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    const char* name() const override { return "Rect"; }

private:
    double w_;
    double h_;
};

int main() {
    // 静态类型都是 Shape，实际调用由 vptr → vtbl 决定（动态绑定）
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Circle>(1.0));
    shapes.emplace_back(std::make_unique<Rect>(2.0, 3.0));

    std::cout << "sizeof(Shape)=" << sizeof(Shape)
              << "（含一个 vptr 指针）\n";
    for (const auto& s : shapes) {
        std::cout << s->name() << " area=" << s->area() << "\n";
    }

    const Shape& ref = *shapes[0];             // 引用同样触发动态绑定
    std::cout << "静态类型 Shape& → 实际调用 " << ref.name() << "\n";

    const bool ok = shapes[0]->area() > 3.14 && shapes[1]->area() == 6.0;
    return ok ? 0 : 1;
}
