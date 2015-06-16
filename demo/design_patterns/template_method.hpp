#pragma once

// ģ�巽��ģʽ
// ����ģ��,���岢ʵ����һ��ģ�巽��.
// ���ģ�巽��һ����һ�����巽��,��������һ�������߼��ĹǼ�
// ���߼�����ɲ�������Ӧ�ĳ��������,�Ƴٵ�֮��ʵ��.
// �����߼�Ҳ�п��ܵ���һЩ���巽��.

interface IAbstractClass
{
    virtual ~IAbstractClass() {}
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;

    void TemplateMethod()
    {
        this->PrimitiveOperation1();
        this->PrimitiveOperation2();
    }
};

class ConcreteClassA : public IAbstractClass
{
public:
    virtual void PrimitiveOperation1() {}
    virtual void PrimitiveOperation2() {}
};

class ConcreteClassB : public IAbstractClass
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
        IAbstractClass* pAbstract = new ConcreteClassA();
        pAbstract->TemplateMethod();
        delete pAbstract;

        pAbstract = new ConcreteClassB();
        pAbstract->TemplateMethod();
        delete pAbstract;
    }
};
