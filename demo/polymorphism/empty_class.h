#pragma once


class CEmptyClassWithoutVirtualFunc
{
public:
    void f() {}
};

class CEmptyClassWithVirtualFunc
{
public:
    virtual void vf1() {}
    virtual void vf2() {}
    virtual void vf3() {}
    virtual void vf4() = 0;
    void f() {}
};


class CEmptyClassClient
{
public:
    static void main()
    {
        ASSERT_EQ(1, sizeof(CEmptyClassWithoutVirtualFunc)); // �����СΪ1
        ASSERT_EQ(4, sizeof(CEmptyClassWithVirtualFunc));    // �����СΪ4
    }
};