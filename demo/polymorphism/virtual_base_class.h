#pragma once

class CBase
{
public:
    virtual int f1() { return 10; }
    virtual int f2() { return 20; }
    virtual int f3() { return 30; }

    CBase() : m_1(100), m_2(200) {}

private:
    int m_1;
    int m_2;
};

class CVirtualBaseClassClient
{
public:
    static void main()
    {
        CBase b;
        int* pAddrOfB = (int*)(&b); // ȡ������׵�ַ

        int* pAddrOfFirstVitualFuncInB = (int*)(*pAddrOfB); // �����׵�ַ    -> �麯����
        int* pMember1 = (int*)(pAddrOfB + 1);               // �����׵�ַ��1 -> ��Ա1
        int* pMember2 = (int*)(pAddrOfB + 2);               // �����׵�ַ��2 -> ��Ա2

        ASSERT_EQ(100, *pMember1);
        ASSERT_EQ(200, *pMember2);

        typedef int (*PFun)();

        PFun pFun1 = (PFun)(*pAddrOfFirstVitualFuncInB);        // ȡ�麯������׵�ַ��ָ����,ȡ��һ���麯����ַ
        ASSERT_EQ(10, pFun1());                                 // ���õ�һ���麯��CBase::f1()
        PFun pFun2 = (PFun)*(pAddrOfFirstVitualFuncInB + 1);    // �麯�����׵�ַ��1,�õ���һ���麯����ַ
        ASSERT_EQ(20, pFun2());                                 // ���õ�һ���麯��CBase::f2()
        PFun pFun3 = (PFun)*(pAddrOfFirstVitualFuncInB + 2);    // �麯�����׵�ַ��2,�õ�����һ���麯����ַ
        ASSERT_EQ(30, pFun3());                                 // ���õ�һ���麯��CBase::f3()
    }
};
