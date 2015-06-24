#pragma once

class CChildWithoutOverride : public CBase
{
public:
    CChildWithoutOverride() : m_c1(1000), m_c2(2000) {}

    virtual int c1() { return 111; }
    virtual int c2() { return 222; }
    virtual int c3() { return 333; }

private:
    int m_c1;
    int m_c2;
};

class CChildClassClient
{
public:
    static void main()
    {
        CChildWithoutOverride c;
        int* pAddrOfC = (int*)(&c); // ȡ������׵�ַ

        int* pAddrOfFirstVitualFuncInBase = (int*)(*pAddrOfC);  // �����׵�ַ    -> �麯����
        int* pBaseMember1  = (int*)(pAddrOfC + 1);              // �����׵�ַ��1 -> �����Ա1
        int* pBaseMember2  = (int*)(pAddrOfC + 2);              // �����׵�ַ��2 -> �����Ա2
        int* pChildMember1 = (int*)(pAddrOfC + 3);              // �����׵�ַ��1 -> �����Ա1
        int* pChildMember2 = (int*)(pAddrOfC + 4);              // �����׵�ַ��2 -> �����Ա2

        ASSERT_EQ(100, *pBaseMember1);
        ASSERT_EQ(200, *pBaseMember2);
        ASSERT_EQ(1000, *pChildMember1);
        ASSERT_EQ(2000, *pChildMember2);

        typedef int (*PFun)();

        // ���û���ĺ���
        PFun pBaseF1 = (PFun)(*pAddrOfFirstVitualFuncInBase);     // ȡ�麯������׵�ַ��ָ����,ȡ��һ���麯����ַ
        ASSERT_EQ(10, pBaseF1());                                 // ���õ�һ���麯��CBase::f1()
        PFun pBaseF2 = (PFun)*(pAddrOfFirstVitualFuncInBase + 1); // �麯�����׵�ַ��1,�õ���һ���麯����ַ
        ASSERT_EQ(20, pBaseF2());                                 // ���õ�һ���麯��CBase::f2()
        PFun pBaseF3 = (PFun)*(pAddrOfFirstVitualFuncInBase + 2); // �麯�����׵�ַ��2,�õ�����һ���麯����ַ
        ASSERT_EQ(30, pBaseF3());                                 // ���õ�һ���麯��CBase::f3()

        // ��������������麯��
        PFun pChildC1 = (PFun)*(pAddrOfFirstVitualFuncInBase+3);   // �麯�����׵�ַ��2,�õ�����һ���麯����ַ
        ASSERT_EQ(111, pChildC1());                                 // ���õ�һ���麯��CBase::f3()
        PFun pChildC2 = (PFun)*(pAddrOfFirstVitualFuncInBase+4);   // �麯�����׵�ַ��2,�õ�����һ���麯����ַ
        ASSERT_EQ(222, pChildC2());                                 // ���õ�һ���麯��CBase::f3()
        PFun pChildC3 = (PFun)*(pAddrOfFirstVitualFuncInBase+5);   // �麯�����׵�ַ��2,�õ�����һ���麯����ַ
        ASSERT_EQ(333, pChildC3());                                 // ���õ�һ���麯��CBase::f3()
    }
};
