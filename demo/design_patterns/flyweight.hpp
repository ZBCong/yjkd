#pragma once
#include <vector>

// ��Ԫģʽ: ���ù�������Ч��֧�ִ���ϸ���ȵĶ���
// 1) Flyweightģʽ�У�����Ҫ���ǽ�����ֽ��intrinsic��extrinsic�����֡�
// 2) �ڲ�״̬������Ԫ�����ڲ����Ҳ����滷���ı���ı�Ĺ����֣����Գ�Ϊ����Ԫ������ڲ�״̬
// 3) �ⲿ״̬�����滷���ı���ı�ģ�ȡ����Ӧ�û���������ʵʱ���ݣ���Щ�����Թ���Ķ��������ⲿ״̬�ˡ�
// 4) �ڲ�״̬���ⲿ״̬֮�������
// ��FlyweightģʽӦ���У�ͨ���޸ĵ����ⲿ״̬���ԣ����ڲ�״̬����һ�㶼�����ڲο������ʱ���á�
//  Flyweightִ��ʱ�����״̬�ض����ڲ��Ļ��ⲿ�ġ��ڲ�״̬�洢��ConcreteFlyweight����֮�У�
//  ���ⲿ״̬����Client����洢����㡣���û�����Flyweight����Ĳ���ʱ������״̬���ݸ�����

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
