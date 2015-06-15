#pragma once

// 外观模式:使应用程序只能看到外观对象,而不会看到具体的细节对象
// 降低应用程序的复杂度,并且提高了程序的可维护性.
// 有种一键式体验的感觉.把复杂的逻辑隐藏起来,提供一个简单的对外接口
// 封装子系统


// 非常复杂的模块1
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
    static void SimpleDoSomething() // 仅调用这一个接口, 实现一系列复杂的操作
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
        CFacade::SimpleDoSomething(); // 一键式操作,不需要知道内部具体实现细节
    }
};
