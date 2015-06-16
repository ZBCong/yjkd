#pragma once

#include "design_patterns_def.h"

// 适配器模式:将一个类的接口转换成客户希望的另外一个接口

// 目标抽象接口
interface Target  
{
    virtual ~Target() {}
    virtual void method1() = 0;
};

// 被适配者
class Adaptee
{
public:
    void method2()
    {
    }
};

// 配接器
class Adapter : public Target
{  
private:
    Adaptee* m_pAdaptee;

public:
    Adapter(Adaptee* pAdaptee) : m_pAdaptee(pAdaptee)
    {}
    ~Adapter() { if (m_pAdaptee) delete m_pAdaptee; }

    void method1()
    { m_pAdaptee->method2(); }
};

class CAdapterClient
{
public:
    static void main()
    {
        Target* pTarget = new Adapter(new Adaptee());
        pTarget->method1();

        delete pTarget;
    }
};
