#pragma once

/**
 * ����Ž�ģʽ���ص���Ҫ�����ν�����(Abstraction)��ʵ�ֻ�(Implementation)���ʹ�ö��߿��Զ����ر仯��
 * ���󻯣����󻯾��Ǻ���һЩ��Ϣ���Ѳ�ͬ��ʵ�嵱��ͬ����ʵ��Դ���
 *          ����������У�������Ĺ�ͬ���ʳ�ȡ�����γ���Ĺ��̼�Ϊ���󻯵Ĺ��̡�
 * ʵ�ֻ�����Գ��󻯸����ľ���ʵ�֣�����ʵ�ֻ���������ʵ�ֻ���һ�Ի���ĸ���.
 *          ʵ�ֻ������Ķ���ȳ��󻯸����壬�ǶԳ�������Ľ�һ�����廯�Ĳ��
 * ���������ǽ����󻯺�ʵ�ֻ�֮�����Ͻ��ѿ�������˵�ǽ�����֮���ǿ�����Ļ���������,
 *          ��������ɫ֮��ļ̳й�ϵ��Ϊ������ϵ���Ž�ģʽ�е���ν����,
 *          ����ָ��һ�����ϵͳ�ĳ��󻯺�ʵ�ֻ�֮��ʹ�ù�����ϵ����ϻ��߾ۺϹ�ϵ�������Ǽ̳й�ϵ,
 *          �Ӷ�ʹ���߿�����Զ����ر仯��������Ž�ģʽ������.
 * 
 * ���ģʽ�������,ȷʵ�е��Ұ�.���ģʽ��Ӧ������Ķ�ά�ȵı仯,���������,�仯ά����2��.
 * һ���ֻ�Ʒ��,һ�����. �ֻ�Ʒ���ڲ��ϱ仯, ͬ��, ���Ҳ�ڲ��ϱ仯.
 **/

interface ISoftwareCommonInterface
{
    virtual ~ISoftwareCommonInterface() {};
    virtual void Run() = 0;
};

interface IPhoneCommonInterface
{
    virtual ~IPhoneCommonInterface() {};
    virtual void RunAllSoftWare() = 0;
    virtual void AddSoftware(ISoftwareCommonInterface*) = 0;
};

class CSamsung : public IPhoneCommonInterface
{
public:
    ~CSamsung()
    {
        for (std::vector<ISoftwareCommonInterface*>::const_iterator it = m_vecSoftware.begin(); it != m_vecSoftware.end(); ++it)
        {
            if (*it)
            {
                delete (*it);
            }
        }
    }

    virtual void RunAllSoftWare()
    {
        for (std::vector<ISoftwareCommonInterface*>::const_iterator it = m_vecSoftware.begin(); it != m_vecSoftware.end(); ++it)
        {
            if (*it)
            {
                (*it)->Run();
            }
        }
    }

    virtual void AddSoftware( ISoftwareCommonInterface* pImpl )
    {
        m_vecSoftware.push_back(pImpl);
    }

private:
    std::vector<ISoftwareCommonInterface*> m_vecSoftware;
};

class CIphone : public IPhoneCommonInterface
{
public:
    ~CIphone()
    {
        for (std::vector<ISoftwareCommonInterface*>::const_iterator it = m_vecSoftware.begin(); it != m_vecSoftware.end(); ++it)
        {
            if (*it)
            {
                delete (*it);
            }
        }
    }

    virtual void RunAllSoftWare()
    {
        for (std::vector<ISoftwareCommonInterface*>::const_iterator it = m_vecSoftware.begin(); it != m_vecSoftware.end(); ++it)
        {
            if (*it)
            {
                (*it)->Run();
            }
        }
    }

    virtual void AddSoftware( ISoftwareCommonInterface* pImpl )
    {
        m_vecSoftware.push_back(pImpl);
    }

private:
    std::vector<ISoftwareCommonInterface*> m_vecSoftware;
};

class CMusicPlayer : public ISoftwareCommonInterface
{
public:
    void Run() {};
};

class CAngryBirds : public ISoftwareCommonInterface
{
public:
    void Run() {}
};

class CBridgeClient
{
public:
    static void main()
    {
        /**
         * �����󲿷�������ʵ�ֲ��ַ��룬ʹ�����ǿ��Զ����ر仯
         * 1��������ʵ�ַ���(IPhoneCommonInterface��ISoftwareCommonInterface,�ֻ�Ʒ�ƺ��������)
         * 2�����󲿷ֿ��Ա仯(�ֻ�Ʒ�ƿ��Բ��ϱ仯)
         * 3��ʵ�ֲ���Ҳ���Ա仯(������Բ��ϱ仯)
         **/

        ISoftwareCommonInterface* pMusicPlayer1 = new CMusicPlayer();
        ISoftwareCommonInterface* pAngryBirds1  = new CAngryBirds();
        IPhoneCommonInterface*    pSamsung      = new CSamsung();
        pSamsung->AddSoftware(pMusicPlayer1);
        pSamsung->AddSoftware(pAngryBirds1);
        pSamsung->RunAllSoftWare();

        ISoftwareCommonInterface* pMusicPlayer2 = new CMusicPlayer();
        ISoftwareCommonInterface* pAngryBirds2  = new CAngryBirds();
        IPhoneCommonInterface*    pIphone       = new CIphone();
        pIphone->AddSoftware(pMusicPlayer2);
        pIphone->AddSoftware(pAngryBirds2);
        pIphone->RunAllSoftWare();

        delete pSamsung;
        delete pIphone;
    }
};
