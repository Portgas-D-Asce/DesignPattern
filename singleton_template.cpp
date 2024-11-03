#include <iostream>
#include <memory>
using namespace std;


template<typename T>
class Singleton {
public:
    static T& get() {
        std::once_flag flag;
        std::call_once(flag, [&]() {
            _instance = std::unique_ptr<T>(new T());
            _instance->init();
        });
        return *_instance;
    }

    static void destroy() {
        static std::once_flag flag;
        std::call_once(flag, [&]() { _instance.reset(nullptr); });
    }
private:
    static std::unique_ptr<T> _instance;
};

template<typename T>
std::unique_ptr<T> Singleton<T>::_instance = nullptr;


class Instance {
public:
    void func() {
        std::cout << "do something" << std::endl;
    }

    friend class default_delete<Instance>;
    friend class Singleton<Instance>;
    // 如果内部需要使用以下某个函数，将其设置为 private default
    Instance(const Instance&) = delete;
    Instance(Instance&&) = delete;
    Instance& operator=(const Instance&) = delete;
    Instance& operator=(const Instance&&) = delete;
private:
    Instance() {
        // load messages from config and init single instance
    }
    void init() {

    }
    ~Instance() = default;
};

int main() {
    Instance& ins = Singleton<Instance>::get();

    ins.func();

    Singleton<Instance>::destroy();

    return 0;
}
