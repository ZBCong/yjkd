#pragma once

#ifndef interface
#define interface struct
#endif // interface

// ����ģʽ,���󴴽���ģʽ.ʹ����Ĵ��������ӳٵ�����

interface ILightBase
{
    virtual void TurnOn()  = 0;
    virtual void TurnOff() = 0;
};

class CBulbLight : public ILightBase
{
public:
    virtual void TurnOn()  {}
    virtual void TurnOff() {}
};

class CTubeLight : public ILightBase
{
public:
    virtual void TurnOn()  {}
    virtual void TurnOff() {}
};

interface ICreatorBase
{
    virtual ILightBase* Create() = 0;
};

class CBulbCreator : public ICreatorBase
{
public:
    virtual ILightBase* Create() { return new CBulbLight(); }
};

class TubeCreator : public ICreatorBase
{
public:
    virtual ILightBase* Create() { return new CTubeLight(); }
};

class CFactoryMethodClient
{
public:
    static void main()
    {
        ICreatorBase* pBulbCreator = new CBulbCreator();
        ICreatorBase* pTubeCreator = new TubeCreator();

        ILightBase* pBulbLight = pBulbCreator->Create();
        ILightBase* pTubeLight = pTubeCreator->Create();

        pBulbLight->TurnOn();
        pBulbLight->TurnOff();

        pTubeLight->TurnOn();
        pTubeLight->TurnOff();

        delete pBulbCreator;
        delete pTubeCreator;
        delete pBulbLight;
        delete pTubeLight;
    }
};