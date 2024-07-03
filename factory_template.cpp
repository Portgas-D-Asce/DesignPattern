#include <iostream>

template<typename Product>
class Factory {
public:
    template<typename... Args>
    static Product create(Args&&... args) {
        return Product(std::forward<Args>(args)...);
    }
};

class Product1 {
private:
    int _x, _y;
public:
    Product1(int x, int y) : _x(x), _y(y) {}
    void func() const {
        std::cout << "Product1: " << _x << ", " << _y << std::endl;
    }
};

class Product2 {
private:
    int _x, _y;
public:
    Product2(int x, int y) : _x(x), _y(y) {}
    void func() const {
        std::cout << "Product2: " << _x << ", " << _y << std::endl;
    }
};

// test 模块摆脱固定产品依赖
template<typename Product>
void test() {
    Product nw = Factory<Product>::create(1, 1);
    nw.func();
}

int main() {
    test<Product1>();

    test<Product2>();

    return 0;
}
