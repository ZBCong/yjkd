#pragma once

// 责任链模式
// 1. Put a "next" pointer in the base class
// 2. The "chain" method in the base class always delegates to the next object
// 3. If the derived classes cannot handle, they delegate to the base class

class CHandlerBase
{
public:
    CHandlerBase() : m_pNext(0) {}
    virtual ~CHandlerBase()     {}

    void Append(CHandlerBase *p)
    {
        if (m_pNext)
        {
            m_pNext->Append(p);
        }
        else
        {
            m_pNext = p;
        }
    }

    // 2. The "chain" method in the base class always delegates to the next obj
    virtual void Handle(int i)
    {
        if (m_pNext)
        {
            m_pNext->Handle(i);
        }
    }

private:
    CHandlerBase *m_pNext; // 1. "next" pointer in the base class
};

class CHandler1 : public CHandlerBase
{
public:
    virtual void Handle(int i)
    {
        if (i>=0 && i<=2)
        {
            // handle
        }
        else
        {
            CHandlerBase::Handle(i); // 3. Delegate to the base class
        }
    }
};

class CHandler2 : public CHandlerBase
{
public:
    virtual void Handle(int i)
    {
        if (i>=3 && i<=6)
        {
            // handle
        }
        else
        {
            CHandlerBase::Handle(i);
        }
    }
};

class CHandler3 : public CHandlerBase
{
public:
    virtual void Handle(int i)
    {
        // handle all
    }
};

class CChainOfResponsibilityClient
{
public:
    static void main()
    {
        CHandler1 h1; // 处理[1,2]
        CHandler2 h2; // 处理[3,6]
        CHandler3 h3; // 处理其它情况

        h1.Append(&h2);
        h1.Append(&h3);

        for (int i=1; i < 10; i++)
        {
            h1.Handle(i);
        }
    }
};
