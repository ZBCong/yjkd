#pragma once
#include "design_patterns_def.h"

// Builder模式: 

class CProduct
{
private:
    int m_a;
    int m_b;
    int m_c;

public:
    void setPartA(int a) { m_a = a; }
    void setPartB(int b) { m_b = b; }
    void setPartC(int c) { m_c = c; }
};

//抽象Builder基类，定义不同部分的创建接口
interface IBuilder
{
    virtual ~IBuilder() {};
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual void BuildPartC() = 0;
    virtual CProduct* GetProduct() = 0;
};

class ConcreteBuilder1 : public IBuilder
{
public:
    ConcreteBuilder1()  { m_pProduct = new CProduct(); }
    ~ConcreteBuilder1() { if (m_pProduct) delete m_pProduct; }

    virtual void BuildPartA() { m_pProduct->setPartA(10); }
    virtual void BuildPartB() { m_pProduct->setPartB(20); }
    virtual void BuildPartC() { m_pProduct->setPartC(30); }

    virtual CProduct* GetProduct() { return m_pProduct; }

private:
    CProduct* m_pProduct;
};

class ConcreteBuilder2:public IBuilder
{
public:
    ConcreteBuilder2()  { m_pProduct = new CProduct(); }
    ~ConcreteBuilder2() { if (m_pProduct) delete m_pProduct; }

    virtual void BuildPartA() { m_pProduct->setPartA(100); }
    virtual void BuildPartB() { m_pProduct->setPartB(200); }
    virtual void BuildPartC() { m_pProduct->setPartC(300); }
    virtual CProduct* GetProduct() { return m_pProduct; }

private:
    CProduct* m_pProduct;
};

// ConcreteBuilder1与ConcreteBuilder2是Builder的两个派生类，用于实现两种不同的建造细节
// 使用Builder构建产品,构建产品的过程都一致,但是不同的builder有不同的实现
// 这个不同的实现通过不同的Builder派生类来实现,存有一个Builder的指针,通过这个来实现多态调用
class CDirector
{
public:
    CDirector(IBuilder* pBuilder) : m_pBuilder(pBuilder) {}
    ~CDirector() { if (m_pBuilder) delete m_pBuilder; }

    // Construct函数定义一个对象的整个构建过程,不同的部分之间的装配方式都是一致的,
    // 首先构建PartA其次是PartB,只是根据不同的构建者会有不同的表示 
    void Construct()
    {
        m_pBuilder->BuildPartA();
        m_pBuilder->BuildPartB();
        m_pBuilder->BuildPartC();
    }

private:
    IBuilder* m_pBuilder;
};

class CBuilderClient
{
public:
    static void main()
    {
        CDirector* pDirector1 = new CDirector(new ConcreteBuilder1());
        pDirector1->Construct();

        CDirector* pDirector2 = new CDirector(new ConcreteBuilder2());
        pDirector2->Construct();

        delete pDirector1;
        delete pDirector2;
    }
};