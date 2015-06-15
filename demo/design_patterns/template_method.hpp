#pragma once

// 模板方法模式
// 抽象模板,定义并实现了一个模板方法.
// 这个模板方法一般是一个具体方法,它给出了一个顶层逻辑的骨架
// 而逻辑的组成步骤在相应的抽象操作中,推迟到之类实现.
// 顶层逻辑也有可能调用一些具体方法.

class AbstractClass
{
public:
    void TemplateMethod()
    {
        this->PrimitiveOperation1();
        this->PrimitiveOperation2();
    }

    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;
};

class ConcreteClassA : public AbstractClass
{
public:
    virtual void PrimitiveOperation1() {}
    virtual void PrimitiveOperation2() {}
};

class ConcreteClassB : public AbstractClass
{
public:
    virtual void PrimitiveOperation1() {}
    virtual void PrimitiveOperation2() {}
};

class CTemplateMethodClient
{
public:
    static void main()
    {
        //ConcreteClassA与ConcreteClassB可相互替换
        AbstractClass* pAbstract = new ConcreteClassA();
        pAbstract->TemplateMethod();
        delete pAbstract;

        pAbstract = new ConcreteClassB();
        pAbstract->TemplateMethod();
        delete pAbstract;
    }
};
