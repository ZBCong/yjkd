#pragma once

#include "design_patterns_def.h"

// ����ģʽ: �ڿͻ������Ŀ�����֮������һ���м�㣬�ô������������Ŀ�������һ��

interface IMath
{
    virtual ~IMath() {}
    virtual int Add(int a, int b) = 0;
    virtual int Sub(int a, int b) = 0;
};

class CMathImpl : public IMath
{
public:
    virtual int Add( int a, int b ) { return a + b; }
    virtual int Sub( int a, int b ) { return a - b; }
};

class CMathProxy : public IMath
{
public:
    CMathProxy()  { m_pImpl = new CMathImpl(); }
    ~CMathProxy() { if (m_pImpl) delete m_pImpl; }

    virtual int Add( int a, int b )
    {
        // do something before impl
        return m_pImpl->Add(a, b);
        // do something after impl
    }

    virtual int Sub( int a, int b )
    {
        // do something before impl
        return m_pImpl->Sub(a, b);
        // do something after impl
    }

private:
    IMath* m_pImpl;
};

class CProxyClient
{
public:
    static void main()
    {
        IMath* p = new CMathProxy();
        p->Add(1, 2);
        p->Sub(3, 2);

        delete p;
    }
};
