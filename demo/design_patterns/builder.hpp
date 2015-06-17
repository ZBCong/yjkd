#pragma once
#include "design_patterns_def.h"

// Builderģʽ: 

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

//����Builder���࣬���岻ͬ���ֵĴ����ӿ�
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

// ConcreteBuilder1��ConcreteBuilder2��Builder�����������࣬����ʵ�����ֲ�ͬ�Ľ���ϸ��
// ʹ��Builder������Ʒ,������Ʒ�Ĺ��̶�һ��,���ǲ�ͬ��builder�в�ͬ��ʵ��
// �����ͬ��ʵ��ͨ����ͬ��Builder��������ʵ��,����һ��Builder��ָ��,ͨ�������ʵ�ֶ�̬����
class CDirector
{
public:
    CDirector(IBuilder* pBuilder) : m_pBuilder(pBuilder) {}
    ~CDirector() { if (m_pBuilder) delete m_pBuilder; }

    // Construct��������һ�������������������,��ͬ�Ĳ���֮���װ�䷽ʽ����һ�µ�,
    // ���ȹ���PartA�����PartB,ֻ�Ǹ��ݲ�ͬ�Ĺ����߻��в�ͬ�ı�ʾ 
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