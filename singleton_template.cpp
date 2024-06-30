#include <iostream>
#include <memory>
using namespace std;

template<typename T>
class Singleton {
public:
    static T& get_instance() {
        static std::once_flag flag;
        std::call_once(flag, [&]() {
            // construct single instance from config file
            _instance = std::unique_ptr<T>(new T());
        });
        return *_instance;
    }
private:
    static std::unique_ptr<T> _instance;
};

template<typename T>
std::unique_ptr<T> Singleton<T>::_instance = nullptr;

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
