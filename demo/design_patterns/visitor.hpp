#pragma once
#include "design_patterns_def.h"
#include <list>

// ������ģʽ:
// �͹۲��ߵ������ǣ����۲���Ҫִ��һ��������Ȼ����������֪ͨ���۲��ߡ�������ģʽ���ɷ��������������Ķ�����
// ��������ߣ�Visitor����ɫ��������һ�����߶�����ʲ������γ����еľ���Ԫ�ؽ�ɫ����ʵ�ֵĽӿڡ�
// ��������ߣ�ConcreteVisitor����ɫ��ʵ�ֳ�������߽�ɫ�������Ľӿڣ�Ҳ���ǳ���������������ĸ������ʲ�����
// ����ڵ㣨Element����ɫ������һ�����ܲ���������һ�������߶�����Ϊһ��������
// ����ڵ㣨ConcreteElement����ɫ��ʵ���˳���Ԫ�����涨�Ľ��ܲ�����
// �ṹ����ObjectStructure����ɫ�������µ�һЩ���Σ����Ա����ṹ�е�����Ԫ��
// ȱ��:
// 1�������µĽڵ����ú����ѡ�ÿ����һ���µĽڵ㶼��ζ��Ҫ�ڳ�������߽�ɫ������һ���µĳ��������
//    ����ÿһ���������������������Ӧ�ľ��������
// 2���ƻ���װ��������ģʽҪ������߶�����ʲ�����ÿһ���ڵ����Ĳ�������������һ�������нڵ�����Ҫ��
//    ���Ǳ��뱩¶һЩ�Լ��Ĳ������ڲ�״̬����Ȼ�������ߵķ��ʾͱ��û�����塣
//    ���ڷ����߶����Լ�����۷��ʲ��������״̬���Ӷ�ʹ��Щ״̬���ٴ洢�ڽڵ�����У���Ҳ���ƻ���װ�ġ�

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
