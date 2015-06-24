#include "stdafx.h"
#include "empty_class.h"
#include "virtual_base_class.h"
#pragma warning(disable:4312)

/**
 * ǳ����vs2005��32λ����Ķ�̬ʵ��ԭ��
 **/

TEST(POLYMORPHISM, EMPTY_CLASS)
{
    ASSERT_EQ(1, sizeof(CEmptyClassWithoutVirtualFunc)); // �����СΪ1
    ASSERT_EQ(4, sizeof(CEmptyClassWithVirtualFunc));    // �����СΪ4
}

TEST(POLYMORPHISM, BASE_VIRTUAL_CLASS)
{
    CBase b;
    int* pAddrOfB = (int*)(&b); // ȡ����ĵ�ַ
    int* pContentOfB = (int*)(*pAddrOfB); // ȡ����ĵ�ַ��ָ�������
    int* pAddrOfFirstVitualFuncInB = pContentOfB; // �����ַ��ָ������,ʵ��Ϊ�麯�������׵�ַ

    typedef int (*PFun)();

    PFun pFun1 = (PFun)(*pAddrOfFirstVitualFuncInB); // ȡ�麯�������׵�ַ��ָ����,ȡ��һ���麯����ַ
    ASSERT_EQ(10, pFun1()); // ���õ�һ���麯��CBase::f1()

    PFun pFun2 = (PFun)*(pAddrOfFirstVitualFuncInB+1); // �麯�����׵�ַ��1,�õ���һ���麯����ַ
    ASSERT_EQ(20, pFun2()); // ���õ�һ���麯��CBase::f2()

    PFun pFun3 = (PFun)*(pAddrOfFirstVitualFuncInB+2); // �麯�����׵�ַ��2,�õ�����һ���麯����ַ
    ASSERT_EQ(30, pFun3()); // ���õ�һ���麯��CBase::f3()
}