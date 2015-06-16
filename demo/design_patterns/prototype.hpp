#pragma once

#include "design_patterns_def.h"

// Prototype模式提供了一个通过已存在对象进行新对象创建的接口（Clone）
//  Clone()实现和具体的语言相关，在C++中通过拷贝构造函数实现
// 作用:
// 用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
// Prototype原型基类，定义Clone接口函数
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
