#pragma once
#include "design_patterns_def.h"

// 策略模式: 

interface IStrategy
{
    virtual ~IStrategy() {};
    virtual void AlgrithmInterface() = 0;
};

class CConcreteStrategy : public IStrategy
{
public:
    virtual void AlgrithmInterface() {};
};


/**
 * 这个类是Strategy模式的关键,
 * 也是Strategy模式和Template模式的根本区别所在.
 * Strategy通过“组合”方式实现算法,
 * 而Template模式则采取的是继承的方式,
 * 这两个模式的区别也是继承和组合两种实现接口重用的方式的区别
 **/
class CContext
{
public:
    CContext(IStrategy* strategy) : m_strategy(strategy) {}
    ~CContext() { if (m_strategy) delete m_strategy; }

    void DoAction() { m_strategy->AlgrithmInterface(); }

private:
    IStrategy* m_strategy;
};

class CStrategyClient
{
public:
    static void main()
    {
        /**
         * Strategy模式和Template模式实际是实现一个抽象接口的两种方式：继承和组合之间的区别。
         * 要实现一个抽象接口，继承是一种方式：我们将抽象接口声明在基类中，将具体的实现放在具体子类中。
         * 组合（委托）是另外一种方式：我们将接口的实现放在被组合对象中，将抽象接口放在组合类中。
         * 这两种方式各有优缺点
         **/
        IStrategy* pStrategy = new CConcreteStrategy();
        CContext*  pContext  = new CContext(pStrategy);
        pContext->DoAction();

        delete pContext;
    }
};
