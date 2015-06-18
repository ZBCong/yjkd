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
    CDoor theDoor(new CDoorClosed); // ��ʼ��һ���ѹرյ���
    theDoor.Open();  // ���ÿ��Ų���,���ű���
    theDoor.Open();  // �ٴε��ÿ��Ų���,���ŵ�״̬���ı�,����Ϊ��
    theDoor.Close(); // �ٵ��ù��Ų���,���ű��ر�
    theDoor.Close(); // �ٴε��ù��Ų���,���ŵ�״̬���ı�,����Ϊ�ر�
    theDoor.Open();  // ���ÿ��Ų���,�ű���
}
