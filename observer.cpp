#include <iostream>
#include <set>
using namespace std;

class ISubject;

// 观察者
class IObserver {
public:
    virtual ~IObserver() = default;
    // 被观察者的通知消息到来
    virtual void update(ISubject* sub) = 0;
};

// 被观察者
class ISubject {
private:
    set<IObserver*> _obs;
public:
    virtual ~ISubject() = default;

    // 添加观察者
    void add(IObserver* ob) {
        _obs.insert(ob);
    }

    // 移除观察者
    void rm(IObserver* ob) {
        _obs.erase(ob);
    }

    // 通知所有观察者
    void notify() {
        for(IObserver* ob : _obs) {
            ob->update(this);
        }
    }
};

class Observer1 : public IObserver {
public:
    void update(ISubject* sub) override {
        cout << "Observer1 receive change from Subject" << endl;
    }
};

class Observer2 : public IObserver {
public:
    void update(ISubject* sub) override {
        cout << "Observer2 receive change from Subject" << endl;
    }
};

class Subject1 : public ISubject {
public:
    void change() {
        notify();
    }
};

class Subject2 : public ISubject {
public:
    void change() {
        notify();
    }
};

int main() {
    Observer1 ob1;
    Observer2 ob2;
    Subject1 sub1;
    // 添加观察者 1
    sub1.add(&ob1);
    // 添加观察者 2
    sub1.add(&ob2);
    // 被观察者状态发生变化
    sub1.change();
    return 0;
}