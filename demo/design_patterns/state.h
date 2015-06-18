#pragma once
#include "design_patterns_def.h"

// ״̬ģʽ: ����һ�����������ڲ�״̬�ı�ʱ�ı�����Ϊ���Ӷ�ʹ���������ƺ��޸����ࡣ

class CDoor;

interface IDoorState
{
    virtual void Open(CDoor* door) = 0;
    virtual void Close(CDoor* door) = 0;
    virtual ~IDoorState() {}
};

class CDoorOpened : public IDoorState
{
public:
    virtual void Open(CDoor* door);
    virtual void Close(CDoor* door);
};

class CDoorClosed : public IDoorState
{
public:
    virtual void Open(CDoor* door);
    virtual void Close(CDoor* door);
};

class CDoor
{
public:
    CDoor(IDoorState* pDoorState);
    ~CDoor();

    void SetState(IDoorState* pDoorState);
    void Open();
    void Close();

private:
    void _ReleaseCurrentState();
    void _SetState(IDoorState* pDoorState);

private:
    IDoorState* m_pDoorState;
};

class CStateClient
{
public:
    static void main();
};
