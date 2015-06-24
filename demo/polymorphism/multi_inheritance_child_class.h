#pragma once

namespace micc
{
class B1
{
public:
    virtual int f1() { return 1; }
    virtual int f2() { return 2; }
    virtual int f3() { return 3; }
};

class B2
{
public:
    virtual int f1() { return 10; }
    virtual int f2() { return 20; }
    virtual int f3() { return 30; }
};

class B3
{
public:
    virtual int f1() { return 100; }
    virtual int f2() { return 200; }
    virtual int f3() { return 300; }
};

class D1 : public B1, public B2, public B3
{
public:
    virtual int d1() { return 1000; }
};

class D2 : public B1, public B2, public B3
{
public:
    virtual int f2() { return 666; }
};

} // end of namespace micc



class CMultiInheritanceChildClass
{
public:
    static void main()
    {
        _test1();
        _test2();
    }

private:
    static void _test1()
    {
        using namespace micc;

        D1 d;
        int* pAddrOfD = (int*)(&d); // 取对象的首地址

        int* pAddrOfVtblInB1  = (int*)(*pAddrOfD);
        int* pAddrOfVtblInB2  = (int*)*(pAddrOfD + 1);
        int* pAddrOfVtblInB3  = (int*)*(pAddrOfD + 2);

        typedef int (*PFun)();

        // 调用基类B1的函数
        PFun pB1F1 = (PFun)(*pAddrOfVtblInB1);
        PFun pB1F2 = (PFun)*(pAddrOfVtblInB1 + 1);
        PFun pB1F3 = (PFun)*(pAddrOfVtblInB1 + 2);
        ASSERT_EQ(1, pB1F1()); // B1::f1()
        ASSERT_EQ(2, pB1F2()); // B1::f2()
        ASSERT_EQ(3, pB1F3()); // B1::f3()

        // 调用自身d1函数
        PFun pD1D1 = (PFun)*(pAddrOfVtblInB1 + 3);
        ASSERT_EQ(1000, pD1D1()); // D1::d1()

        // 调用基类B2的函数
        PFun pB2F1 = (PFun)(*pAddrOfVtblInB2);
        PFun pB2F2 = (PFun)*(pAddrOfVtblInB2 + 1);
        PFun pB2F3 = (PFun)*(pAddrOfVtblInB2 + 2);
        ASSERT_EQ(10, pB2F1()); // B2::f1()
        ASSERT_EQ(20, pB2F2()); // B2::f2()
        ASSERT_EQ(30, pB2F3()); // B2::f3()

        // 调用基类B3的函数
        PFun pB3F1 = (PFun)(*pAddrOfVtblInB3);
        PFun pB3F2 = (PFun)*(pAddrOfVtblInB3 + 1);
        PFun pB3F3 = (PFun)*(pAddrOfVtblInB3 + 2);
        ASSERT_EQ(100, pB3F1()); // B1::f1()
        ASSERT_EQ(200, pB3F2()); // B1::f2()
        ASSERT_EQ(300, pB3F3()); // B1::f3()
    }

    static void _test2()
    {
        using namespace micc;

        D2 d;
        int* pAddrOfD = (int*)(&d); // 取对象的首地址

        int* pAddrOfVtblInB1  = (int*)(*pAddrOfD);
        int* pAddrOfVtblInB2  = (int*)*(pAddrOfD + 1);
        int* pAddrOfVtblInB3  = (int*)*(pAddrOfD + 2);

        typedef int (*PFun)();

        // 调用基类B1的函数
        PFun pB1F1 = (PFun)(*pAddrOfVtblInB1);
        PFun pB1F2 = (PFun)*(pAddrOfVtblInB1 + 1);
        PFun pB1F3 = (PFun)*(pAddrOfVtblInB1 + 2);
        ASSERT_EQ(1, pB1F1()); // B1::f1()
        ASSERT_EQ(666, pB1F2()); // D2::f2()
        ASSERT_EQ(3, pB1F3()); // B1::f3()

        // 调用基类B2的函数
        PFun pB2F1 = (PFun)(*pAddrOfVtblInB2);
        PFun pB2F2 = (PFun)*(pAddrOfVtblInB2 + 1);
        PFun pB2F3 = (PFun)*(pAddrOfVtblInB2 + 2);
        ASSERT_EQ(10, pB2F1()); // B2::f1()
        ASSERT_EQ(666, pB2F2()); // D2::f2()
        ASSERT_EQ(30, pB2F3()); // B2::f3()

        // 调用基类B3的函数
        PFun pB3F1 = (PFun)(*pAddrOfVtblInB3);
        PFun pB3F2 = (PFun)*(pAddrOfVtblInB3 + 1);
        PFun pB3F3 = (PFun)*(pAddrOfVtblInB3 + 2);
        ASSERT_EQ(100, pB3F1()); // B1::f1()
        ASSERT_EQ(666, pB3F2()); // D2::f2()
        ASSERT_EQ(300, pB3F3()); // B1::f3()
    }
};
