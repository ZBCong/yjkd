#pragma once
#include "design_patterns_def.h"

// װ����ģʽ: ��̬�ظ�һ���������һЩ�����ְ�𣬾����ӹ�����˵��Decoratorģʽ�����������Ϊ��

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
        AddBehavorA(); // ����ְ��A
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
        AddBehavorB(); // ����ְ��B
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
        AddBehavorC(); // ����ְ��C
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
        AddBehavorD(); // ����ְ��D
    }

    void AddBehavorD() {}
};

class CDecoratorClient
{
public:
    static void main()
    {
        ITarget* pTarget1 = new CTarget();                   // ��װ�ε�Ŀ�����
        IDecorator* pDecorator = NULL;
        IDecorator* pDecoratorA = new CConcreteDecoratorA(pTarget1);            //��װ�ζ��󸽼�ְ��A
        IDecorator* pDecoratorB = new CConcreteDecoratorB(pDecoratorA);            //��װ�ζ��󸽼�ְ��B
        IDecorator* pDecoratorC = new CConcreteDecoratorC(pDecoratorB);            //��װ�ζ��󸽼�ְ��C
        IDecorator* pDecoratorD = new CConcreteDecoratorD(pDecoratorC);            //��װ�ζ��󸽼�ְ��D
        pDecoratorD->Operation();
        delete pDecoratorD;

        //ֻ���һ������
        ITarget* pTarget2 = new CTarget();
        CDecoratorOnlyOne* pDecoratorOnlyOne = new CDecoratorOnlyOne(pTarget2);
        pDecoratorOnlyOne->Operation();
        delete pDecoratorOnlyOne;
    }
};
