#include <iostream>
using namespace std;

// 组件接口
class ISubject {
public:
    virtual void func() = 0;
    virtual ~ISubject() = default;
};

// 组件 1 实现
class Subject1 : public ISubject {
public:
    void func() override {
        cout << "Subject1" << endl;
    }
};

// 组件 2 实现
class Subject2 : public ISubject {
public:
    void func() override {
        cout << "Subject2" << endl;
    }
};

// 装饰器接口
// 之所以要继承 ISubject, 是为了继承要装饰的接口
// 包含 ISubject* 是为了执行真正的逻辑
class IDecorator : public ISubject {
protected:
    // 要被装饰的组件
    ISubject* _sub;
public:
    explicit IDecorator(ISubject* sub) : _sub(sub) {}
};

class Decorator1 : public IDecorator {
public:
    explicit Decorator1(ISubject* sub) : IDecorator(sub) {}

    void func() override {
        // 装饰行为
        cout << "Decorator1" << endl;
        // 真正行为
        _sub->func();
    }
};

class Decorator2 : public IDecorator {
public:
    explicit Decorator2(ISubject* sub) : IDecorator(sub) {}

    void func() override {
        // 装饰行为
        cout << "Decorator2" << endl;
        // 真正行为
        _sub->func();
    }
};


int main() {
    Subject2 sub1;
    // 装饰器 1 装饰组件 1
    Decorator1 dec1(&sub1);
    dec1.func();

    cout << endl;

    // 神奇的是，可以多次装饰
    // 装饰器 1 + 装饰器 1 装饰组件 1
    Decorator1 dec11(&dec1);
    dec11.func();

    cout << endl;

    // 装饰器 2 + 装饰器 1 装饰组件 1
    Decorator2 dec2(&dec1);
    dec2.func();
    return 0;
}