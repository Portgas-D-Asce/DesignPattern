#include <iostream>
#include <memory>
using namespace std;


template<typename T>
class Singleton {
public:
    template<typename... Args>
    static T& get_instance(Args&&... args) {
        std::call_once(_init_flag, [&]() {
            // 这块还有完美转发的必要么，lambda 表达式已经引用了？？？？？？？
            _instance = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        });
        return *_instance;
    }

    static void destroy() {
        static std::once_flag flag;
        std::call_once(flag, [&]() {
            _instance.reset(nullptr);
        });
    }
private:
    static std::unique_ptr<T> _instance;
    // 使用不同的参数构造单例，会导致多个局部静态变量，进而导致多例, 故取消局部静态变量
    static std::once_flag _init_flag;
};

template<typename T>
std::unique_ptr<T> Singleton<T>::_instance = nullptr;

template<typename T>
std::once_flag Singleton<T>::_init_flag = {};


class RealClass {
public:
    friend class default_delete<RealClass>;
    friend class Singleton<RealClass>;
    void func() {
        std::cout << "do something" << std::endl;
    }
private:
    RealClass() {
        // load messages from config and init single instance
    }
    ~RealClass() = default;
    RealClass(const RealClass&) = default;
    RealClass& operator=(const RealClass&) = default;
};


int main() {
    RealClass& ins = Singleton<RealClass>::get_instance();
    ins.func();
    return 0;
}
