#include <iostream>
using namespace std;

// 产品 A 接口
class IProductA {
public:
    virtual ~IProductA() = default;
    virtual void func() = 0;
};

// 产品 A1（Factory1 生产）
class ProductA1 : public IProductA {
public:
    void func() override {
        cout << "ProductA1" << endl;
    }
};

// 产品 A2 （Factory2 生产）
class ProductA2 : public IProductA {
public:
    void func() override {
        cout << "ProductA2" << endl;
    }
};

// 产品 B 接口
class IProductB {
public:
    virtual ~IProductB() = default;
    virtual void func() = 0;
};

// 产品 B1（Factory1 生产）
class ProductB1 : public IProductB {
public:
    void func() override {
        cout << "ProductB1" << endl;
    }
};

// 产品 B2（Factory2 生产）
class ProductB2 : public IProductB {
public:
    void func() override {
        cout << "ProductB2" << endl;
    }
};

// 抽象工厂接口
class IFactory {
public:
    virtual ~IFactory() = default;
    virtual IProductA* create_a() = 0;
    virtual IProductB* create_b() = 0;
};

// 工厂 1
class Factory1 : public IFactory {
public:
    IProductA* create_a() override {
        return new ProductA1();
    }

    IProductB* create_b() override {
        return new ProductB1();
    }
};

// 工厂 2
class Factory2 : public IFactory {
public:
    IProductA* create_a() override {
        return new ProductA2();
    }

    IProductB* create_b() override {
        return new ProductB2();
    }
};

void test(IFactory* f) {
    // 生产一个 A 类产品
    IProductA* a = f->create_a();
    a->func();

    // 生产一个 B 类产品
    IProductB* b = f->create_b();
    b->func();
}


int main() {
    IFactory* f1 = new Factory1();
    // 生产 Factory1 的 A 产品和 B 产品
    test(f1);

    cout << endl;

    // 生产 Factory2 的 A 产品和 B 产品
    IFactory* f2 = new Factory2();
    test(f2);
    return 0;
}