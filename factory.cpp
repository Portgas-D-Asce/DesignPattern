#include <iostream>
using namespace std;

// 产品接口
class IProduct {
public:
    virtual ~IProduct() = default;
    virtual void func() = 0;
};

// 工厂接口
class IFactory {
public:
    virtual ~IFactory() = default;
    virtual IProduct* create() = 0;
};

// 产品 1
class Product1 : public IProduct {
public:
    void func() override {
        cout << "Product1" << endl;
    }
};

// 产品 1 工厂
class FactoryProduct1 : public IFactory {
public:
    IProduct* create() override {
        return new Product1();
    }
};

// 产品 2
class Product2 : public IProduct {
public:
    void func() override {
        cout << "Product2" << endl;
    }
};

// 产品 2 工厂
class FactoryProduct2 : public IFactory {
public:
    IProduct* create() override {
        return new Product2();
    }
};

// test 模块摆脱 new Product1()、new Product2() 固定类型依赖
// 直接传进来指定产品，不也可摆脱固定类型依赖，为什么还要工厂？
// test 模块要的不是某个产品，要的是创建产品的方法
void test(IFactory* factory) {
    IProduct* pro1 = factory->create();
    pro1->func();

    IProduct* pro2 = factory->create();
    pro2->func();
}


int main() {
    IFactory* factory1 = new FactoryProduct1();
    test(factory1);

    cout << endl;

    IFactory* factory2 = new FactoryProduct2();
    test(factory2);
    return 0;
}