#pragma once
#include "design_patterns_def.h"

// 装饰者模式: 动态地给一个对象添加一些额外的职责，就增加功能来说，Decorator模式比生成子类更为灵活。

interface ITarget
{
    virtual ~ITarget() {}
    virtual void Operation() = 0;
};

class CDecoratorOnlyOne : public ITarget
{
public:
    CDecoratorOnlyOne(ITarget* pTarget) : m_pTarget(pTarget) {}
    ~CDecoratorOnlyOne() { if (m_pTarget) delete m_pTarget; }

    virtual void Operation()
    {
        m_pTarget->Operation();
        AddBehavor();
    }

    void AddBehavor() {}

private:
    ITarget* m_pTarget;
};

class CTarget : public ITarget
{
public:
    virtual void Operation() {}
};

class IDecorator : public ITarget
{
public:
    IDecorator(ITarget* pTarget) : m_pTarget(pTarget) {}
    virtual ~IDecorator() { if (m_pTarget) delete m_pTarget; }

protected:
    ITarget* m_pTarget;
};

class CConcreteDecoratorA : public IDecorator
{
public:
    CConcreteDecoratorA(ITarget* pTarget) : IDecorator(pTarget) {}
    virtual void Operation()
    {
        m_pTarget->Operation();
        AddBehavorA(); // 附加职责A
    }
    void AddBehavorA() {}
};

class CConcreteDecoratorB : public IDecorator
{
public:
    CConcreteDecoratorB(ITarget* pTarget) : IDecorator(pTarget) {}
    virtual void Operation()
    {
        m_pTarget->Operation();
        AddBehavorB(); // 附加职责B
    }

    void AddBehavorB() {}
};

class CConcreteDecoratorC : public IDecorator
{
public:
    CConcreteDecoratorC(ITarget* pTarget) : IDecorator(pTarget) {}
    virtual void Operation()
    {
        m_pTarget->Operation();
        AddBehavorC(); // 附加职责C
    }
    void AddBehavorC() {}
};

class CConcreteDecoratorD : public IDecorator
{
public:
    CConcreteDecoratorD(ITarget* pTarget) : IDecorator(pTarget) {}
    virtual void Operation()
    {
        m_pTarget->Operation();
        AddBehavorD(); // 附加职责D
    }

    void AddBehavorD() {}
};

class CDecoratorClient
{
public:
    static void main()
    {
        ITarget* pTarget1 = new CTarget();                   // 被装饰的目标对象
        IDecorator* pDecorator = NULL;
        IDecorator* pDecoratorA = new CConcreteDecoratorA(pTarget1);            //给装饰对象附加职责A
        IDecorator* pDecoratorB = new CConcreteDecoratorB(pDecoratorA);            //给装饰对象附加职责B
        IDecorator* pDecoratorC = new CConcreteDecoratorC(pDecoratorB);            //给装饰对象附加职责C
        IDecorator* pDecoratorD = new CConcreteDecoratorD(pDecoratorC);            //给装饰对象附加职责D
        pDecoratorD->Operation();
        delete pDecoratorD;

        //只添加一种修饰
        ITarget* pTarget2 = new CTarget();
        CDecoratorOnlyOne* pDecoratorOnlyOne = new CDecoratorOnlyOne(pTarget2);
        pDecoratorOnlyOne->Operation();
        delete pDecoratorOnlyOne;
    }
};
