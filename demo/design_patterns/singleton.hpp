#pragma once
#include "utils\singleton.h"

// 保证一个类,只有一个实例存在

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

