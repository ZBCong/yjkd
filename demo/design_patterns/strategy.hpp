#pragma once
#include "design_patterns_def.h"

// ����ģʽ: 

interface IStrategy
{
    virtual ~IStrategy() {};
    virtual void AlgrithmInterface() = 0;
};

class CConcreteStrategy : public IStrategy
{
public:
    virtual void AlgrithmInterface() {};
};


/**
 * �������Strategyģʽ�Ĺؼ�,
 * Ҳ��Strategyģʽ��Templateģʽ�ĸ�����������.
 * Strategyͨ������ϡ���ʽʵ���㷨,
 * ��Templateģʽ���ȡ���Ǽ̳еķ�ʽ,
 * ������ģʽ������Ҳ�Ǽ̳к��������ʵ�ֽӿ����õķ�ʽ������
 **/
class CContext
{
public:
    CContext(IStrategy* strategy) : m_strategy(strategy) {}
    ~CContext() { if (m_strategy) delete m_strategy; }

    void DoAction() { m_strategy->AlgrithmInterface(); }

private:
    IStrategy* m_strategy;
};

class CStrategyClient
{
public:
    static void main()
    {
        /**
         * Strategyģʽ��Templateģʽʵ����ʵ��һ������ӿڵ����ַ�ʽ���̳к����֮�������
         * Ҫʵ��һ������ӿڣ��̳���һ�ַ�ʽ�����ǽ�����ӿ������ڻ����У��������ʵ�ַ��ھ��������С�
         * ��ϣ�ί�У�������һ�ַ�ʽ�����ǽ��ӿڵ�ʵ�ַ��ڱ���϶����У�������ӿڷ���������С�
         * �����ַ�ʽ������ȱ��
         **/
        IStrategy* pStrategy = new CConcreteStrategy();
        CContext*  pContext  = new CContext(pStrategy);
        pContext->DoAction();

        delete pContext;
    }
};
