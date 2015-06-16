#pragma once

#include "design_patterns_def.h"

// Prototypeģʽ�ṩ��һ��ͨ���Ѵ��ڶ�������¶��󴴽��Ľӿڣ�Clone��
//  Clone()ʵ�ֺ;����������أ���C++��ͨ���������캯��ʵ��
// ����:
// ��ԭ��ʵ��ָ��������������࣬����ͨ��������Щԭ�ʹ����µĶ���
// Prototypeԭ�ͻ��࣬����Clone�ӿں���
interface IPrototype
{
public:
    virtual ~IPrototype() {};
    virtual IPrototype* Clone() const = 0;
};

class ConcretePrototype1 : public IPrototype
{
public:
    ConcretePrototype1()  {}
    ~ConcretePrototype1() {}
    ConcretePrototype1(const ConcretePrototype1&) {}
    virtual IPrototype* Clone() const { return new ConcretePrototype1(*this); }
};

class ConcretePrototype2:public IPrototype
{
public:
    ConcretePrototype2()  {}
    ~ConcretePrototype2() {}
    ConcretePrototype2(const ConcretePrototype2&) {}
    virtual IPrototype* Clone() const { return new ConcretePrototype2(*this); }
};

class CPrototypeClient
{
public:
    static void main()
    {
        IPrototype* p1 = new ConcretePrototype1();
        IPrototype* p2 = p1->Clone();

        IPrototype* p3 = new ConcretePrototype2();
        IPrototype* p4 = p3->Clone();

        delete p1;
        delete p2;
        delete p3;
        delete p4;
    }
};
