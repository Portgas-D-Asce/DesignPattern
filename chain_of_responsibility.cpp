#include <iostream>
#include <string>
using namespace std;

class IHandler {
private:
    // 下一个处理人
    IHandler* _next;
public:
    explicit IHandler(IHandler* next) : _next(next) {}
    virtual ~IHandler() = default;

    // 判断是否由自己处理
    virtual bool pred(const string& event) = 0;

    // 处理请求
    virtual void deal(const string& event) = 0;

    // 如果该由自己处理, 则直接处理请求
    // 如果不该由自己处理, 转发给下一位处理人
    void process(const string& event) {
        if(pred(event)) {
            deal(event);
        } else {
            _next->process(event);
        }
    }
};

// 第一个处理人
class Handler1 : public IHandler {
public:
    explicit Handler1(IHandler* next) : IHandler(next) {}

    bool pred(const string& event) override {
        return event.empty();
    }

    void deal(const string& event) override {
        cout << "event is empty" << endl;
    }
};

// 第二个处理人
class Handler2 : public IHandler {
public:
    explicit Handler2(IHandler* next) : IHandler(next) {}

    bool pred(const string& event) override {
        return event.size() <= 5;
    }

    void deal(const string& event) override {
        cout << event << ": small event" << endl;
    }
};

// 默认处理人
class Handler3 : public IHandler {
public:
    explicit Handler3() : IHandler(nullptr) {}

    bool pred(const string& event) override {
        return true;
    }

    void deal(const string& event) override {
        cout << event << ": big event" << endl;
    }
};

int main() {
    // 构建职责链
    Handler3 handler3{};
    Handler2 handler2(&handler3);
    Handler1 handler1(&handler2);

    string event1;
    handler1.process(event1);

    string event2 = "abc";
    handler1.process(event2);

    string event3 = "abcdefgh";
    handler1.process(event3);

    return 0;
}