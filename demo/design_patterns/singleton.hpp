#pragma once
#include "utils\singleton.h"

// ��֤һ����,ֻ��һ��ʵ������
// singleton��2�ֳ����淨.
// 1. ����ʽ,��ʹ���������ʵ����ʱ��,��ȥ��������
// 2. ����ʽ,��ȫ�ֳ�ʼ����ʱ��,���Ѿ���ʼ��������ʵ��.
// �����������ڵ�������ĳ�ʼ��ʱ�䲻ͬ


// ����ʽ
class CLazyMan
{
    SINGLETON_DECLARE(CLazyMan, Instance);
private:
    CLazyMan()  {};
    ~CLazyMan() {};

public:
    void DoSomething() {}
};

// ����ʽ
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