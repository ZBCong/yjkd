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
        int* pAddrOfB = (int*)(&b); // 取对象的首地址

        int* pAddrOfFirstVitualFuncInB = (int*)(*pAddrOfB); // 对象首地址    -> 虚函数表
        int* pMember1 = (int*)(pAddrOfB + 1);               // 对象首地址加1 -> 成员1
        int* pMember2 = (int*)(pAddrOfB + 2);               // 对象首地址加2 -> 成员2

        ASSERT_EQ(100, *pMember1);
        ASSERT_EQ(200, *pMember2);

        typedef int (*PFun)();

        PFun pFun1 = (PFun)(*pAddrOfFirstVitualFuncInB);        // 取虚函数表的首地址所指内容,取第一个虚函数地址
        ASSERT_EQ(10, pFun1());                                 // 调用第一个虚函数CBase::f1()
        PFun pFun2 = (PFun)*(pAddrOfFirstVitualFuncInB + 1);    // 虚函数表首地址加1,得到下一个虚函数地址
        ASSERT_EQ(20, pFun2());                                 // 调用第一个虚函数CBase::f2()
        PFun pFun3 = (PFun)*(pAddrOfFirstVitualFuncInB + 2);    // 虚函数表首地址加2,得到下下一个虚函数地址
        ASSERT_EQ(30, pFun3());                                 // 调用第一个虚函数CBase::f3()
    }
};
