#pragma once

#ifndef interface
#define interface
#endif // interface

// ���󹤳�


// ʾ��:
// ��ƻ����,�ɱ���ͱ����2��������

interface IWatchBand
{};

interface IWatchCore
{
    virtual void Bind(IWatchBand* a) = 0;
};

interface IWatchFactory
{
    virtual IWatchBand* CreateWatchBand() = 0;
    virtual IWatchCore* CreateWatchCore() = 0;
};

// ƻ�����һ����Ʒver1.0
class CAppleWatchBandVer_1_0 : public IWatchBand {};
class CAppleWatchCoreVer_1_0 : public IWatchCore { virtual void Bind(IWatchBand* a) {} };

// ƻ����ڶ�����Ʒver2.0
class CAppleWatchBandVer_2_0 : public IWatchBand {};
class CAppleWatchCoreVer_2_0 : public IWatchCore { virtual void Bind(IWatchBand* a) {} };

// ����ƻ����1.0��Ĺ���
class CFactoryOfAppleWatchVer_1_0 : public IWatchFactory
{
public:
    virtual IWatchBand* CreateWatchBand() { return new CAppleWatchBandVer_1_0(); }
    virtual IWatchCore* CreateWatchCore() { return new CAppleWatchCoreVer_1_0(); }
};

// ����ƻ����2.0��Ĺ���
class CFactoryOfAppleWatchVer_2_0 : public IWatchFactory
{
    virtual IWatchBand* CreateWatchBand() { return new CAppleWatchBandVer_2_0(); }
    virtual IWatchCore* CreateWatchCore() { return new CAppleWatchCoreVer_2_0(); }
};

// ͨ����������,���벻ͬ�Ĺ���,������ͬ�汾�Ĳ�Ʒ
class CCommonWorkFlow
{
private:
    IWatchBand* pWatchBand;
    IWatchCore* pWatchCore;

public:
    CCommonWorkFlow(IWatchFactory* factory)
    {
        pWatchBand = factory->CreateWatchBand();
        pWatchCore = factory->CreateWatchCore();
    }

    ~CCommonWorkFlow()
    {
        if (pWatchBand) delete pWatchBand;
        if (pWatchCore) delete pWatchCore;
    }

    void Run()
    {
        pWatchCore->Bind(pWatchBand);
    }
};

class CAbstractFactoryClient
{
public:
    static void main()
    {
        IWatchFactory* pFactory1 = new CFactoryOfAppleWatchVer_1_0();
        CCommonWorkFlow*   pEnv1     = new CCommonWorkFlow(pFactory1);
        pEnv1->Run();

        IWatchFactory* pFactory2 = new CFactoryOfAppleWatchVer_2_0();
        CCommonWorkFlow*   pEnv2     = new CCommonWorkFlow(pFactory2);
        pEnv2->Run();

        delete pEnv1;
        delete pEnv2;
        delete pFactory1;
        delete pFactory2;
    }
};
