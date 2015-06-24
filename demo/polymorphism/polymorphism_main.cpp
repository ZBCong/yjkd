#include "stdafx.h"
#include "empty_class.h"
#include "virtual_base_class.h"
#pragma warning(disable:4312)

/**
 * 浅析下vs2005下32位程序的多态实现原理
 **/

TEST(POLYMORPHISM, EMPTY_CLASS)
{
    ASSERT_EQ(1, sizeof(CEmptyClassWithoutVirtualFunc)); // 空类大小为1
    ASSERT_EQ(4, sizeof(CEmptyClassWithVirtualFunc));    // 虚类大小为4
}

TEST(POLYMORPHISM, BASE_VIRTUAL_CLASS)
{
    CBase b;
    int* pAddrOfB = (int*)(&b); // 取对象的首地址

    int* pAddrOfFirstVitualFuncInB = (int*)(*pAddrOfB); // 对象首地址    -> 虚函数表
    int* pMember1 = (int*)(pAddrOfB+1);                 // 对象首地址加1 -> 成员1
    int* pMember2 = (int*)(pAddrOfB+2);                 // 对象首地址加2 -> 成员2

    ASSERT_EQ(100, *pMember1);
    ASSERT_EQ(200, *pMember2);

    typedef int (*PFun)();

    PFun pFun1 = (PFun)(*pAddrOfFirstVitualFuncInB);    // 取虚函数表的首地址所指内容,取第一个虚函数地址
    ASSERT_EQ(10, pFun1());                             // 调用第一个虚函数CBase::f1()

    PFun pFun2 = (PFun)*(pAddrOfFirstVitualFuncInB+1);  // 虚函数表首地址加1,得到下一个虚函数地址
    ASSERT_EQ(20, pFun2());                             // 调用第一个虚函数CBase::f2()

    PFun pFun3 = (PFun)*(pAddrOfFirstVitualFuncInB+2);  // 虚函数表首地址加2,得到下下一个虚函数地址
    ASSERT_EQ(30, pFun3());                             // 调用第一个虚函数CBase::f3()
}
