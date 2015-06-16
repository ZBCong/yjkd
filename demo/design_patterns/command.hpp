#pragma once

// 命令模式: 命令模式是对命令的封装.命令模式把发出命令的责任和执行命令的责任分割开,委派给不同的对象.
// 看到则挺不错的小故事,来说明命令模式的:
//   在美猴王大闹天宫之前就有了.那时玉帝命令太白金星召美猴王上天:
//   "金星径入(水帘洞)当中,面南立定道:'我是西方太白金星,奉玉帝招安圣旨,
//   下界请你上大,拜受仙录.'".玉帝是系统的客户端，太白金星是命令的发出者,
//   猴王是命令的接收者,圣旨就是命令.玉帝的这一道命令就是要求猴王到上界报到.
//   玉帝只管发出命令,而不管命令是怎样传达到美猴王的.太白金星负责将圣旨传到,
//   可是美猴王怎么执行圣旨.何时执行圣旨是美猴王自己的事.
//   果不然,不久美猴王就大闹了天宫。



// 用来声明执行操作的接口
interface ICommand
{
    virtual ~ICommand() {};
    virtual void Execute()=0;
};

// 知道如何实施与执行一个与请求相关的操作，任何类都可能作为一个接收者。
class CReceiver
{
public:
    void Action() {};
};

// 将一个接收者对象绑定于一个操作,调用接收者相应的操作,以实现Execute
class CConcreteCommand : public ICommand
{
public:
    CConcreteCommand(CReceiver* pReceiver) { m_recv = pReceiver; }
    virtual void Execute() { m_recv->Action(); }

private:
    CReceiver* m_recv;
};

// 要求该命令执行这个请求
class CInvoker
{
public:
    CInvoker(ICommand* pCommand) { m_cmd = pCommand; }
    void Invoke() { m_cmd->Execute(); }

private:
    ICommand* m_cmd;
};

class CCommandClient
{
public:
    static void main()
    {
        CReceiver* pRev = new CReceiver();              // 孙悟空的角色
        ICommand*  pCmd = new CConcreteCommand(pRev);   // 太白金星的角色
        CInvoker*  pInv = new CInvoker(pCmd);           // 玉皇大帝的角色
        pInv->Invoke();

        delete pInv;
        delete pCmd;
        delete pRev;
    }
};
