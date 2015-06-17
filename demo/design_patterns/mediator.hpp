#pragma once
#include "design_patterns_def.h"

// 中介者模式: 用一个中介对象来封装一系列的对象交互。
// 中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。

class IColleague;

interface IMediator
{
    virtual ~IMediator() {}
    virtual void SendMsg(int, IColleague*) = 0;
};

class IColleague
{
public:
    IColleague(IMediator* pMediator) : m_pMediator(pMediator) {}
    virtual ~IColleague() {}

    virtual void SendMsg(int) = 0;
    virtual void GetMsg(int) = 0;

protected:
    IMediator* m_pMediator;
};

class CColleagueA : public IColleague
{
public:
    CColleagueA(IMediator* pMediator) : IColleague(pMediator) {}
    virtual void SendMsg(int msg) { m_pMediator->SendMsg(msg, this); }
    virtual void GetMsg(int) {}
};

class CColleagueB : public IColleague
{
public:
    CColleagueB(IMediator* pMediator) : IColleague(pMediator) {}
    virtual void SendMsg(int msg) { m_pMediator->SendMsg(msg, this); }
    virtual void GetMsg(int) {}
};

class ConcreteMediator : public IMediator
{
public:
    void SetColleagueA(IColleague* p) { m_ColleageA = p; }
    void SetColleagueB(IColleague* p) { m_ColleageB = p; }
    virtual void SendMsg(int msg, IColleague* p)
    {
        if(p == m_ColleageA)
        {
            m_ColleageB->GetMsg(msg);
        }
        else if(p == m_ColleageB)
        {
            m_ColleageA->GetMsg(msg);
        }
    }

private:
    IColleague* m_ColleageA;
    IColleague* m_ColleageB;
};

class CMediatorClient
{
public:
    static void main()
    {
        /**
         * 每个Colleague 维护一个 Mediator.
         * 当要进行通信时，每个具体的Colleague直接向ConcreteMediator发信息.
         * 至于信息发到哪里，则由ConcreteMediator来决定.
         *
         *  ConcreteColleague不必维护对各自的引用，甚至它们也不知道各个的存在。
         * 优点: 各个Colleague减少了耦合。
         * 缺点: 由于Mediator控制了集中化,于是就把Colleague之间的交互复杂性变为了中介者的复杂性.
         *        也就是中介者会变的比任何一个 Colleague 都复杂.
         **/

        ConcreteMediator* pMediator = new ConcreteMediator();

        IColleague* p1 = new CColleagueA(pMediator);
        IColleague* p2 = new CColleagueB(pMediator);

        pMediator->SetColleagueA(p1);
        pMediator->SetColleagueB(p2);

        p1->SendMsg(1);
        p2->SendMsg(2);

        delete p1;
        delete p2;
        delete pMediator;
    }
};
