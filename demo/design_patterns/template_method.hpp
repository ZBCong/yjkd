#pragma once

// ģ�巽��ģʽ
// ����ģ��,���岢ʵ����һ��ģ�巽��.
// ���ģ�巽��һ����һ�����巽��,��������һ�������߼��ĹǼ�
// ���߼�����ɲ�������Ӧ�ĳ��������,�Ƴٵ�֮��ʵ��.
// �����߼�Ҳ�п��ܵ���һЩ���巽��.

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
        //ConcreteClassA��ConcreteClassB���໥�滻
        AbstractClass* pAbstract = new ConcreteClassA();
        pAbstract->TemplateMethod();
        delete pAbstract;

        pAbstract = new ConcreteClassB();
        pAbstract->TemplateMethod();
        delete pAbstract;
    }
};
