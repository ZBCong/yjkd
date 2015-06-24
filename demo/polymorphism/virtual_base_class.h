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

