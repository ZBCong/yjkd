#pragma once

// ���ģʽ:ʹӦ�ó���ֻ�ܿ�����۶���,�����ῴ�������ϸ�ڶ���
// ����Ӧ�ó���ĸ��Ӷ�,��������˳���Ŀ�ά����.
// ����һ��ʽ����ĸо�.�Ѹ��ӵ��߼���������,�ṩһ���򵥵Ķ���ӿ�
// ��װ��ϵͳ


// �ǳ����ӵ�ģ��1
class CVeryComplexModule1
{
public:
    void ComplexMethod1() {}
    void ComplexMethod2() {}
    void ComplexMethod3() {}
};

class CVeryComplexModule2
{
public:
    void ComplexMethod1() {}
    void ComplexMethod2() {}
    void ComplexMethod3() {}
};

// facade
class CFacade
{
public:
    static void SimpleDoSomething() // ��������һ���ӿ�, ʵ��һϵ�и��ӵĲ���
    {
        CVeryComplexModule1 c1;
        CVeryComplexModule2 c2;
        c1.ComplexMethod3();
        c2.ComplexMethod2();
    }
};

// client
class CFacadeClient
{
public:
    static void main()
    {
        CFacade::SimpleDoSomething(); // һ��ʽ����,����Ҫ֪���ڲ�����ʵ��ϸ��
    }
};
