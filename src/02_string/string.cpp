// 侯捷《C++ 面向对象高级编程（上）》String 例子的 C++17 重写。
// 考察：Big Three（拷贝构造 / 拷贝赋值 / 析构）、深拷贝、自赋值检查。
#include <cstring>
#include <iostream>

class String {
public:
    explicit String(const char* s = nullptr) {
        len_ = s ? std::strlen(s) : 0;
        data_ = new char[len_ + 1];
        if (s) {
            std::memcpy(data_, s, len_ + 1);
        } else {
            data_[0] = '\0';
        }
    }

    // 1) 拷贝构造：深拷贝，不能只复制指针
    String(const String& other) : len_(other.len_) {
        data_ = new char[len_ + 1];
        std::memcpy(data_, other.data_, len_ + 1);
    }

    // 2) 拷贝赋值：自赋值检查 + 先分配成功再释放旧资源
    String& operator=(const String& other) {
        if (this == &other) return *this;
        char* tmp = new char[other.len_ + 1];
        std::memcpy(tmp, other.data_, other.len_ + 1);
        delete[] data_;
        data_ = tmp;
        len_ = other.len_;
        return *this;
    }

    // 3) 析构
    ~String() { delete[] data_; }

    const char* c_str() const { return data_; }
    std::size_t size() const { return len_; }

private:
    char* data_;
    std::size_t len_;
};

inline std::ostream& operator<<(std::ostream& os, const String& s) {
    return os << s.c_str();
}

int main() {
    String a("hello");
    String b(a);          // 深拷贝
    String c;
    c = a;                // 拷贝赋值
    c = c;                // 自赋值：不加检查会 delete 掉自己的 data_

    std::cout << "a=" << a << " b=" << b << " c=" << c << "\n";
    std::cout << "sizeof(String)=" << sizeof(String)
              << "（对象本身只存指针与长度，字符在堆上）\n";

    const bool ok = std::strcmp(b.c_str(), "hello") == 0 &&
                    std::strcmp(c.c_str(), "hello") == 0 &&
                    b.c_str() != a.c_str();   // 验证不是浅拷贝
    return ok ? 0 : 1;
}
