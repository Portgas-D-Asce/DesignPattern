#include <iostream>
#include <string>
using namespace std;

/* 命令
 * 命令支持构造、执行 和 回退等接口，执行结果只有成功/失败
 * 命令类型一旦固定，命令的参数格式也就固定了
 * */

class ICommand {
public:
    virtual bool exec() = 0;
    virtual bool undo() = 0;
};


class ACommand : public ICommand {
private:
    int _a;
    int _b;
public:
    // 执行命令所需要的参数，都在构造函数中传入
    ACommand(int a, int b) : _a(a), _b(b) {}

    // 执行命令时，不需传入额外的参数（传入额外参数如何解释？）
    bool exec() override {
        // 执行命令
        int res = _a + _b;

        // 命令执行结果的处理也作为接收方
        std::cout << res << std::endl;

        // 返回命令执行结果
        return true;
    }
    bool undo() override {
        _a + _b;
        return true;
    }
};


class BCommand : public ICommand {
private:
    int _a;
    int _b;
public:
    BCommand(int a, int b) : _a(a), _b(b) {}

    bool exec() override {
        _a + _b;
        return true;
    }
    bool undo() override {
        _a + _b;
        return true;
    }
};


/* 执行者
 * 执行者负责命令的构造、执行、回退等操作
 * 执行者不关心命令的返回结果，只关心命令是否执行成功，命令执行完了，结果也就处理好了
 * */

int main() {
    string type = "add";
    // 定义抽象命令
    std::shared_ptr<ICommand> cmd = nullptr;
    if(type == "add") {
        cmd = std::make_shared<ACommand>(1, 2);
    } else {
        cmd = std::make_shared<BCommand>(1, 2);
    }
    // 抽象命令其好处在于，不用每种情况都重复调用执行命令
    cmd->exec();
    cmd->undo();
    return 0;
}


