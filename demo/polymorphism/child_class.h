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
        int* pAddrOfC = (int*)(&c); // 取对象的首地址

        int* pAddrOfFirstVitualFuncInBase = (int*)(*pAddrOfC);  // 对象首地址    -> 虚函数表
        int* pBaseMember1  = (int*)(pAddrOfC + 1);              // 对象首地址加1 -> 父类成员1
        int* pBaseMember2  = (int*)(pAddrOfC + 2);              // 对象首地址加2 -> 父类成员2
        int* pChildMember1 = (int*)(pAddrOfC + 3);              // 对象首地址加1 -> 自身成员1
        int* pChildMember2 = (int*)(pAddrOfC + 4);              // 对象首地址加2 -> 自身成员2

        ASSERT_EQ(100, *pBaseMember1);
        ASSERT_EQ(200, *pBaseMember2);
        ASSERT_EQ(1000, *pChildMember1);
        ASSERT_EQ(2000, *pChildMember2);

        typedef int (*PFun)();

        // 调用基类的函数
        PFun pBaseF1 = (PFun)(*pAddrOfFirstVitualFuncInBase);     // 取虚函数表的首地址所指内容,取第一个虚函数地址
        ASSERT_EQ(10, pBaseF1());                                 // 调用第一个虚函数CBase::f1()
        PFun pBaseF2 = (PFun)*(pAddrOfFirstVitualFuncInBase + 1); // 虚函数表首地址加1,得到下一个虚函数地址
        ASSERT_EQ(20, pBaseF2());                                 // 调用第一个虚函数CBase::f2()
        PFun pBaseF3 = (PFun)*(pAddrOfFirstVitualFuncInBase + 2); // 虚函数表首地址加2,得到下下一个虚函数地址
        ASSERT_EQ(30, pBaseF3());                                 // 调用第一个虚函数CBase::f3()

        // 调用子类自身的虚函数
        PFun pChildC1 = (PFun)*(pAddrOfFirstVitualFuncInBase+3);   // 虚函数表首地址加2,得到下下一个虚函数地址
        ASSERT_EQ(111, pChildC1());                                 // 调用第一个虚函数CBase::f3()
        PFun pChildC2 = (PFun)*(pAddrOfFirstVitualFuncInBase+4);   // 虚函数表首地址加2,得到下下一个虚函数地址
        ASSERT_EQ(222, pChildC2());                                 // 调用第一个虚函数CBase::f3()
        PFun pChildC3 = (PFun)*(pAddrOfFirstVitualFuncInBase+5);   // 虚函数表首地址加2,得到下下一个虚函数地址
        ASSERT_EQ(333, pChildC3());                                 // 调用第一个虚函数CBase::f3()
    }
};
