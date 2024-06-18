#include <iostream>
using namespace std;

class Element1;
class Element2;

// 访问者接口
class IVisitor {
public:
    virtual void visit_element1(Element1& ele1) = 0;
    virtual void visit_element2(Element2& ele2) = 0;
    virtual ~IVisitor() = default;
};

// 元素接口
class IElement {
public:
    virtual void accept(IVisitor& vis) = 0;
    virtual ~IElement() = default;
};

// 元素 1
class Element1 : public IElement {
public:
    void accept(IVisitor& vis) override {
        vis.visit_element1(*this);
    }
};

// 元素 2
class Element2 : public IElement {
public:
    void accept(IVisitor& vis) override {
        vis.visit_element2(*this);
    }
};

// 为 IElement 添加 func1 接口
class Visitor1 : public IVisitor {
    void visit_element1(Element1& ele1) override {
        cout << "Element1 func1" << endl;
    }

    void visit_element2(Element2& ele2) override {
        cout << "Element2 func1" << endl;
    }
};

// 为 IElement 添加 func2 接口
class Visitor2 : public IVisitor {
    void visit_element1(Element1& ele1) override {
        cout << "Element1 func2" << endl;
    }

    void visit_element2(Element2& ele2) override {
        cout << "Element2 func2" << endl;
    }
};


int main() {
    Visitor1 vis1;
    Visitor2 vis2;

    // IElement 看着没有 func1、func2 接口
    // 但通过访问者模式为其 “添加” 了这两个接口
    IElement* ele1 = new Element1();
    ele1->accept(vis1);
    ele1->accept(vis2);

    cout << endl;

    IElement* ele2 = new Element2();
    ele2->accept(vis1);
    ele2->accept(vis2);

    return 0;
}