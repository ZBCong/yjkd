#pragma once

#include "design_patterns_def.h"

// ������ģʽ:��һ����Ľӿ�ת���ɿͻ�ϣ��������һ���ӿ�

// Ŀ�����ӿ�
interface Target  
{
    virtual ~Target() {}
    virtual void method1() = 0;
};

// ��������
class Adaptee
{
public:
    void method2()
    {
    }
};

// �����
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
