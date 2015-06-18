#pragma once
#include "design_patterns_def.h"

// 状态模式: 允许一个对象在其内部状态改变时改变其行为，从而使对象看起来似乎修改了类。

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
