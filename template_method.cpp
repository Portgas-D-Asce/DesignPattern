#include <iostream>
using namespace std;

class ITemplate {
public:
    virtual ~ITemplate() = default;
    virtual void func1() = 0;

    void func2() {
        cout << "func2" << endl;
    }

    void func3() {
        cout << "func3" << endl;
    }

    virtual void func4() = 0;

    // Template Method 具有稳定的结构
    void run() {
        func1();
        func2();
        func3();
        func4();
    }
};

class Template1 : public ITemplate {
    void func1() override {
        cout << "Template1::func1" << endl;
    }

    void func4() override {
        cout << "Template1::func4" << endl;
    }
};

class Template2 : public ITemplate {
    void func1() override {
        cout << "Template2::func1" << endl;
    }

    void func4() override {
        cout << "Template2::func4" << endl;
    }
};


int main() {
    ITemplate* temp1 = new Template1();
    temp1->run();

    cout << endl;

    ITemplate* temp2 = new Template2();
    temp2->run();

    return 0;
}