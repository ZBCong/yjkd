#pragma once
#include "utils\singleton.h"

// ��֤һ����,ֻ��һ��ʵ������

class CSingletonTest
{
    SINGLETON_DECLARE(CSingletonTest, Instance);
private:
    CSingletonTest()  {};
    ~CSingletonTest() {};

public:
    void DoSomething()
    {
    }
};

