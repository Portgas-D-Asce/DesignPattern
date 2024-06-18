#include <iostream>
#include <string>
#include <map>
using namespace std;

class Memento {
private:
    // 多状态
    int _stat1, _stat2;
public:
    Memento() = default;
    Memento(int stat1, int stat2) : _stat1(stat1), _stat2(stat2) {}

    int stat1() const {
        return _stat1;
    }

    int stat2() const {
        return _stat2;
    }
};

class Subject {
private:
    int _x, _y;
public:
    Subject(int x, int y) : _x(x), _y(y) {}

    Memento backup() const {
        return Memento(_x, _y);
    }

    void recover(const Memento& mem) {
        _x = mem.stat1();
        _y = mem.stat2();
    }

    void output() const {
        cout << "x: " << _x << ", y: " << _y << endl;
    }
};

class Manager {
private:
    // 多备份
    map<string, Memento> _memes;
public:
    void add(const string& key, const Memento& mem) {
        _memes[key] = mem;
    }

    Memento query(const string& key) {
        return _memes[key];
    }
};


int main() {
    Subject t(10, 20);
    Manager manager;
    // 创建 01 号备份
    manager.add("01", t.backup());
    t.output();

    // 修改对象
    t = Subject(30, 40);
    t.output();

    // 恢复 01 备份
    t.recover(manager.query("01"));
    t.output();

    return 0;
}