#include <iostream>
using namespace std;

// 变化维度 1
class ILeft {
public:
    virtual void func() = 0;
    virtual ~ILeft() = default;
};

class Left1 : public ILeft {
public:
    void func() override {
        cout << "Left1" << endl;
    }
};

class Left2 : public ILeft {
public:
    void func() override {
        cout << "Left2" << endl;
    }
};

// 变化维度 2
class IRight {
public:
    virtual void func() = 0;
    virtual ~IRight() = default;
};

class Right1 : public IRight {
public:
    void func() override {
        cout << "Right1" << endl;
    }
};

class Right2 : public IRight {
public:
    void func() override {
        cout << "Right2" << endl;
    }
};

// 具有两个变换维度: Left 和 Right
// 当然也允许多个变化维度
class Bridge {
private:
    ILeft* _left;
    IRight* _right;
public:
    Bridge(ILeft* left, IRight* right) : _left(left), _right(right) {}

    void run() {
        _left->func();
        _right->func();
    }
};


int main() {
    Left1 left1;
    Right2 right2;
    // 运行时装配, 第一个变化维度使用 Left1, 第二个变化维度使用 Right2
    Bridge b(&left1, &right2);
    b.run();

    return 0;
}