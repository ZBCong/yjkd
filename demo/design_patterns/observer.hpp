#pragma once

// �۲���ģʽ: ģʽ������һ��һ�Զ��������ϵ,�ö���۲��߶���ͬʱ����ĳһ���������.
// ������������״̬�Ϸ����仯ʱ,��֪ͨ���й۲��߶���,ʹ�����ܹ��Զ������Լ�.

#include <list>

interface IBeObserver;

// �۲��߽ӿ�
interface IObserver
{
public:
    virtual ~IObserver() {};
    virtual void Update(IBeObserver*) = 0;
};

// ���۲��߽ӿ�
interface IBeObserver
{
    virtual ~IBeObserver() {}
    virtual void Notify()
    {
        for(std::list<IObserver*>::iterator it = m_lst.begin(); it != m_lst.end(); it++)
        {
            if (*it)
            {
                (*it)->Update(this);
            }
        }
    }

    virtual void Attach(IObserver* pObserver)
    {
        if (pObserver)
        {
            m_lst.push_back(pObserver);
        }
    }

    virtual void Detach(IObserver* pObserver)
    {
        std::list<IObserver*>::iterator iter;
        iter = find(m_lst.begin(), m_lst.end(), pObserver);
        if(iter != m_lst.end())
        {
            m_lst.erase(iter);
        }
    }

    virtual int  GetState() { return m_state; }
    virtual void SetState(int state) { m_state = state; }

private:
    int m_state;
    std::list<IObserver*> m_lst; // �۲����б�
};

class CBeObserver : public IBeObserver {};

class ConcreteObserverA : public IObserver
{
public:
    virtual void Update(IBeObserver* pSubject) { m_state = pSubject->GetState(); }

private:
    int m_state;
};

class ConcreteObserverB : public IObserver
{
public:
    virtual void Update(IBeObserver* pSubject) { m_state = pSubject->GetState(); }

private:
    int m_state;
};

class CObserverClient
{
public:
    static void main()
    {
        IObserver* pObserver1 = new ConcreteObserverA();
        IObserver* pObserver2 = new ConcreteObserverB();
        IObserver* pObserver3 = new ConcreteObserverA();

        IBeObserver* pBeObserver = new CBeObserver();
        pBeObserver->Attach(pObserver1);
        pBeObserver->Attach(pObserver2);
        pBeObserver->Attach(pObserver3);

        pBeObserver->SetState(22);
        pBeObserver->Notify();

        pBeObserver->SetState(33);
        pBeObserver->Detach(pObserver3);
        pBeObserver->Notify();

        delete pBeObserver;
        delete pObserver1;
        delete pObserver2;
        delete pObserver3;
    }
};