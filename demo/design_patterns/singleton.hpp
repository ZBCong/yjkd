#pragma once
#include "utils\singleton.h"

// 保证一个类,只有一个实例存在
// singleton有2种常用玩法.
// 1. 懒汉式,在使用这个对象实例的时候,才去创建对象
// 2. 饿汉式,在全局初始化的时候,就已经开始创建对象实例.
// 二者区别在于单例对象的初始化时间不同


// 懒汉式
class CLazyMan
{
    SINGLETON_DECLARE(CLazyMan, Instance);
private:
    CLazyMan()  {};
    ~CLazyMan() {};

public:
    void DoSomething() {}
};

// 饿汉式
class CHungryMan
{
    SINGLETON_TEMPLATE_DECLARE(CHungryMan);
private:
    CHungryMan()  {}
    ~CHungryMan() {}

public:
    void DoSomething() {}
};

class CSingletonClient
{
public:
    static void main()
    {
        CLazyMan::Instance().DoSomething();
        y::Singleton<CHungryMan>::instance().DoSomething();
    }
};