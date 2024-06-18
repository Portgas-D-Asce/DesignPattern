#include <iostream>
#include <memory>
#include <future>
using namespace std;

class Singleton {
public:
    // 析构函数设置为私有, 这里需要声明友元
    friend class default_delete<Singleton>;
    // 获取实例接口
    static Singleton& get_instance() {
        // 懒汉模式一次性初始化, static 注意下
        static once_flag flag;
        call_once(flag, [&]() {
            // make_unique 需要声明友元
            cout << "only called once" << endl;
            _instance = unique_ptr<Singleton>(new Singleton());
        });
        return *_instance;
    }
private:
    // 防止产生多个实例对象
    Singleton() = default;
    // 防止意外析构
    ~Singleton() = default;
    Singleton(const Singleton&) = default;
    Singleton& operator=(const Singleton&) = default;
private:
    // 声明为私有防止直接访问
    // 声明为只能指针, 防止内存泄露
    static unique_ptr<Singleton> _instance;
};

unique_ptr<Singleton> Singleton::_instance = nullptr;

int main() {
    Singleton& ins1 = Singleton::get_instance();

    future<Singleton &> fut = async(Singleton::get_instance);
    Singleton& ins2 = fut.get();
    return 0;
}