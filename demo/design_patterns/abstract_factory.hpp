#pragma once

#ifndef interface
#define interface
#endif // interface

// 抽象工厂


// 示例:
// 大苹果表,由表带和表核心2个大件组成

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

// 苹果表第一代产品ver1.0
class CAppleWatchBandVer_1_0 : public IWatchBand {};
class CAppleWatchCoreVer_1_0 : public IWatchCore { virtual void Bind(IWatchBand* a) {} };

// 苹果表第二代产品ver2.0
class CAppleWatchBandVer_2_0 : public IWatchBand {};
class CAppleWatchCoreVer_2_0 : public IWatchCore { virtual void Bind(IWatchBand* a) {} };

// 生产苹果表1.0版的工厂
class CFactoryOfAppleWatchVer_1_0 : public IWatchFactory
{
public:
    virtual IWatchBand* CreateWatchBand() { return new CAppleWatchBandVer_1_0(); }
    virtual IWatchCore* CreateWatchCore() { return new CAppleWatchCoreVer_1_0(); }
};

// 生产苹果表2.0版的工厂
class CFactoryOfAppleWatchVer_2_0 : public IWatchFactory
{
    virtual IWatchBand* CreateWatchBand() { return new CAppleWatchBandVer_2_0(); }
    virtual IWatchCore* CreateWatchCore() { return new CAppleWatchCoreVer_2_0(); }
};

// 通用生产流程,接入不同的工厂,生产不同版本的产品
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
