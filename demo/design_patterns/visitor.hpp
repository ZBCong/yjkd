#pragma once
#include "design_patterns_def.h"
#include <list>

// 访问者模式:
// 和观察者的区别是，被观察者要执行一个动作，然后主动发送通知给观察者。访问者模式是由访问者主动发出的动作。
// 抽象访问者（Visitor）角色：声明了一个或者多个访问操作，形成所有的具体元素角色必须实现的接口。
// 具体访问者（ConcreteVisitor）角色：实现抽象访问者角色所声明的接口，也就是抽象访问者所声明的各个访问操作。
// 抽象节点（Element）角色：声明一个接受操作，接受一个访问者对象作为一个参量。
// 具体节点（ConcreteElement）角色：实现了抽象元素所规定的接受操作。
// 结构对象（ObjectStructure）角色：有如下的一些责任，可以遍历结构中的所有元素
// 缺点:
// 1，增加新的节点类变得很困难。每增加一个新的节点都意味着要在抽象访问者角色中增加一个新的抽象操作，
//    并在每一个具体访问者类中增加相应的具体操作。
// 2，破坏封装。访问者模式要求访问者对象访问并调用每一个节点对象的操作，这隐含了一个对所有节点对象的要求：
//    它们必须暴露一些自己的操作和内部状态。不然，访问者的访问就变得没有意义。
//    由于访问者对象自己会积累访问操作所需的状态，从而使这些状态不再存储在节点对象中，这也是破坏封装的。

class CEmployee;
class CBoss;

interface IVisitor
{
public:
    virtual void Visit(const CEmployee& employee) = 0;
    virtual void Visit(const CBoss& boss) = 0;
    virtual ~IVisitor() {}
};

interface IElement
{
public:
    virtual void Accept(IVisitor *visitor) = 0;
    virtual ~IElement() {}
};

class CEmployee : public IElement
{
public :
    CEmployee( int nId, int nSalary, int nVactionDays )
        : m_nId(nId)
        , m_nSalary(nSalary)
        , m_nVacationDays(nVactionDays)
    {}

    void Accept(IVisitor *pVisitor)
    {
        if (pVisitor)
        {
            pVisitor->Visit(*this);
        }
    }

    int GetSalary() const       { return m_nSalary; }
    int GetVacationDays() const { return m_nVacationDays; }

private:
    int m_nId;
    int m_nSalary;
    int m_nVacationDays;
};

class CBoss : public IElement
{
public :
    CBoss(int nId, int nSalary, int nVactionDays)
        : m_nId(nId)
        , m_nSalary(nSalary)
        , m_nVacationDays(nVactionDays)
    {}

    virtual void Accept( IVisitor *pVisitor)
    {
        if (pVisitor)
        {
            pVisitor->Visit(*this);
        }
    }

    int GetSalary() const       { return m_nSalary; }
    int GetVacationDays() const { return m_nVacationDays; }

private:
    int m_nId;
    int m_nSalary;
    int m_nVacationDays;
};

class CSalaryVisitor : public IVisitor
{
public:
    CSalaryVisitor() : m_nSalarySum(0) {}
    virtual void Visit(const CEmployee& employee) { m_nSalarySum += employee.GetSalary(); }
    virtual void Visit(const CBoss& boss)         { m_nSalarySum += boss.GetSalary(); }
    int GetSalarySum() const                      { return m_nSalarySum; }

private:
    int m_nSalarySum;
};

class CVacationVisitor : public IVisitor
{
public:
    CVacationVisitor() : m_nVacationSum(0) {}
    virtual void Visit(const CEmployee& employee) { m_nVacationSum += employee.GetVacationDays(); }
    virtual void Visit(const CBoss& boss)         { m_nVacationSum += boss.GetVacationDays(); }
    int GetVacationSum() const                    { return m_nVacationSum; }

private:
    int m_nVacationSum;
};

class CEmployeeMgr
{
public:
    ~CEmployeeMgr()
    {
        for (std::list<CEmployee*>::iterator it = m_employees.begin(); it != m_employees.end(); ++it)
        {
            if (*it)
            {
                delete (*it);
            }
        }
        m_employees.clear();
    }

    void Accept(IVisitor *pVisitor)
    {
        for (std::list<CEmployee*>::iterator it = m_employees.begin(); it != m_employees.end(); ++it)
        {
            if (*it)
            {
                (*it)->Accept(pVisitor);
            }
        }
    }

    void Attach(CEmployee *employee) { m_employees.push_back(employee); }
    void Detach(CEmployee *employee) { m_employees.remove(employee); }

private :
    std::list< CEmployee*> m_employees;
};

class CVisitorClient
{
public:
    static void main()
    {
        CEmployeeMgr *pMgr = new CEmployeeMgr();
        pMgr->Attach( new CEmployee( 1001, 2500, 14 ) );
        pMgr->Attach( new CEmployee( 1002, 3500, 16 ) );
        pMgr->Attach( new CEmployee( 1003, 4500, 21 ) );

        CSalaryVisitor   pVisitor1;
        CVacationVisitor pVisitor2;

        pMgr->Accept(&pVisitor1);
        pMgr->Accept(&pVisitor2);

        int nSumSalary   = pVisitor1.GetSalarySum();
        int nSumVacation = pVisitor2.GetVacationSum();

        ASSERT_EQ(nSumSalary,   10500);
        ASSERT_EQ(nSumVacation, 51);
    }
};
