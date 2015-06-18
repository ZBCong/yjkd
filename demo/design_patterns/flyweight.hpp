#pragma once
#include <vector>

// 享元模式: 运用共享技术有效地支持大量细粒度的对象
// 1) Flyweight模式中，最重要的是将对象分解成intrinsic和extrinsic两部分。
// 2) 内部状态：在享元对象内部并且不会随环境改变而改变的共享部分，可以称为是享元对象的内部状态
// 3) 外部状态：而随环境改变而改变的，取决于应用环境，或是实时数据，这些不可以共享的东西就是外部状态了。
// 4) 内部状态和外部状态之间的区别：
// 在Flyweight模式应用中，通常修改的是外部状态属性，而内部状态属性一般都是用于参考或计算时引用。
//  Flyweight执行时所需的状态必定是内部的或外部的。内部状态存储于ConcreteFlyweight对象之中；
//  而外部状态则由Client对象存储或计算。当用户调用Flyweight对象的操作时，将该状态传递给它。

class IFlyweight
{
public:
    virtual void Operation(const int nExtrinsic) = 0;
    int GetIntrinsic() { return m_nIntrinsic; }
    virtual ~IFlyweight() {}

protected:
    IFlyweight(int nIntrinsic) : m_nIntrinsic(nIntrinsic) {}

private:
    int m_nIntrinsic;
};

class CConcreteFlyweight : public IFlyweight
{
public:
    virtual void Operation(const int nExtrinsic) {}
    CConcreteFlyweight(int nIntrinsic) : IFlyweight(nIntrinsic) {}
};

class UnsharedConcreteFlyweight : public IFlyweight
{
public:
    virtual void Operation(const int nExtrinsic) {}
    UnsharedConcreteFlyweight(int nIntrinsic) : IFlyweight(nIntrinsic) {}
};

class CFlyweightFactory
{
public:
    ~CFlyweightFactory()
    {
        for(std::vector<IFlyweight*>::iterator it = m_vecFlyweightPool.begin();
            it != m_vecFlyweightPool.end();
            ++it)
        {
            if (*it)
            {
                delete (*it);
            }
        }
        m_vecFlyweightPool.clear();
    }

    IFlyweight* GetFlyweight(int nIntrinsic)
    {
        for(std::vector<IFlyweight*>::iterator it = m_vecFlyweightPool.begin();
            it != m_vecFlyweightPool.end();
            ++it)
        {
            if (*it)
            {
                if((*it)->GetIntrinsic() == nIntrinsic)
                {
                    return *it;
                }
            }
        }

        IFlyweight* pFlyWeight = new CConcreteFlyweight(nIntrinsic);
        m_vecFlyweightPool.push_back(pFlyWeight);

        return pFlyWeight;
    }

    size_t GetFlyweightCount()
    {
        return m_vecFlyweightPool.size();
    }

private:
    std::vector<IFlyweight*> m_vecFlyweightPool;
};

class CFlyWeightClient
{
public:
    static void main()
    {
        CFlyweightFactory* pFac = new CFlyweightFactory();
        IFlyweight* pFly1 = pFac->GetFlyweight(20);
        IFlyweight* pFly2 = pFac->GetFlyweight(30);
        IFlyweight* pFly3 = pFac->GetFlyweight(20);
        pFly1->Operation(222);
        size_t nCnt = pFac->GetFlyweightCount();
        ASSERT_EQ(nCnt, 2);
    }
};
