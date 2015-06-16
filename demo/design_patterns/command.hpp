#pragma once

// ����ģʽ: ����ģʽ�Ƕ�����ķ�װ.����ģʽ�ѷ�����������κ�ִ����������ηָ,ί�ɸ���ͬ�Ķ���.
// ������ͦ�����С����,��˵������ģʽ��:
//   �������������칬֮ǰ������.��ʱ�������̫�׽���������������:
//   "���Ǿ���(ˮ����)����,����������:'��������̫�׽���,������а�ʥּ,
//   �½������ϴ�,������¼.'".�����ϵͳ�Ŀͻ��ˣ�̫�׽���������ķ�����,
//   ����������Ľ�����,ʥּ��������.��۵���һ���������Ҫ��������Ͻ籨��.
//   ���ֻ�ܷ�������,�������������������ﵽ��������.̫�׽��Ǹ���ʥּ����,
//   ������������ôִ��ʥּ.��ʱִ��ʥּ���������Լ�����.
//   ����Ȼ,�����������ʹ������칬��



// ��������ִ�в����Ľӿ�
interface ICommand
{
    virtual ~ICommand() {};
    virtual void Execute()=0;
};

// ֪�����ʵʩ��ִ��һ����������صĲ������κ��඼������Ϊһ�������ߡ�
class CReceiver
{
public:
    void Action() {};
};

// ��һ�������߶������һ������,���ý�������Ӧ�Ĳ���,��ʵ��Execute
class CConcreteCommand : public ICommand
{
public:
    CConcreteCommand(CReceiver* pReceiver) { m_recv = pReceiver; }
    virtual void Execute() { m_recv->Action(); }

private:
    CReceiver* m_recv;
};

// Ҫ�������ִ���������
class CInvoker
{
public:
    CInvoker(ICommand* pCommand) { m_cmd = pCommand; }
    void Invoke() { m_cmd->Execute(); }

private:
    ICommand* m_cmd;
};

class CCommandClient
{
public:
    static void main()
    {
        CReceiver* pRev = new CReceiver();              // ����յĽ�ɫ
        ICommand*  pCmd = new CConcreteCommand(pRev);   // ̫�׽��ǵĽ�ɫ
        CInvoker*  pInv = new CInvoker(pCmd);           // ��ʴ�۵Ľ�ɫ
        pInv->Invoke();

        delete pInv;
        delete pCmd;
        delete pRev;
    }
};
