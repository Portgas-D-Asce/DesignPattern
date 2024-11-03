#include <iostream>
using namespace std;

class Test {
public:
    static Test& get_instance() {
        static Test test;
        return test;
    }

    void func() {
        cout << "test" << endl;
    }
private:
    Test() = default;
    ~Test() = default;
};

int main() {
    auto& test = Test::get_instance();
    test.func();
    return 0;
}