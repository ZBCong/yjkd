#pragma once
#include "design_patterns_def.h"

// �н���ģʽ: ��һ���н��������װһϵ�еĶ��󽻻���
// �н���ʹ��������Ҫ��ʽ���໥���ã��Ӷ�ʹ�������ɢ�����ҿ��Զ����ظı�����֮��Ľ�����

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
         * ÿ��Colleague ά��һ�� Mediator.
         * ��Ҫ����ͨ��ʱ��ÿ�������Colleagueֱ����ConcreteMediator����Ϣ.
         * ������Ϣ�����������ConcreteMediator������.
         *
         *  ConcreteColleague����ά���Ը��Ե����ã���������Ҳ��֪�������Ĵ��ڡ�
         * �ŵ�: ����Colleague��������ϡ�
         * ȱ��: ����Mediator�����˼��л�,���ǾͰ�Colleague֮��Ľ��������Ա�Ϊ���н��ߵĸ�����.
         *        Ҳ�����н��߻��ı��κ�һ�� Colleague ������.
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
