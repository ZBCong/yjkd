#include "state.h"
#include <stdio.h>

void CDoorOpened::Open( CDoor* theDoor ) {}

void CDoorOpened::Close( CDoor* theDoor )
{
    if (theDoor)
    {
        theDoor->SetState(new CDoorClosed);
    }
}

void CDoorClosed::Open( CDoor* theDoor )
{
    if (theDoor)
    {
        theDoor->SetState(new CDoorOpened);
    }
}

void CDoorClosed::Close( CDoor* theDoor ) {}

CDoor::CDoor(IDoorState* pDoorState) : m_pDoorState(pDoorState) {}
CDoor::~CDoor() { _ReleaseCurrentState(); }

void CDoor::SetState( IDoorState* pDoorState )
{
    _ReleaseCurrentState();
    _SetState(pDoorState);
}

void CDoor::Open()
{
    m_pDoorState->Open(this);
}

void CDoor::Close()
{
    m_pDoorState->Close(this);
}

void CDoor::_ReleaseCurrentState()
{
    if (m_pDoorState)
    {
        delete m_pDoorState;
        m_pDoorState = NULL;
    }
}

void CDoor::_SetState( IDoorState* pDoorState )
{
    m_pDoorState = pDoorState;
}

void CStateClient::main()
{
    CDoor theDoor(new CDoorClosed); // 初始化一个已关闭的门
    theDoor.Open();  // 调用开门操作,则门被打开
    theDoor.Open();  // 再次调用开门操作,则门的状态不改变,依旧为打开
    theDoor.Close(); // 再调用关门操作,则门被关闭
    theDoor.Close(); // 再次调用关门操作,则门的状态不改变,依旧为关闭
    theDoor.Open();  // 调用开门操作,门被打开
}
