#pragma once

/**
 * 理解桥接模式，重点需要理解如何将抽象化(Abstraction)与实现化(Implementation)脱耦，使得二者可以独立地变化。
 * 抽象化：抽象化就是忽略一些信息，把不同的实体当作同样的实体对待。
 *          在面向对象中，将对象的共同性质抽取出来形成类的过程即为抽象化的过程。
 * 实现化：针对抽象化给出的具体实现，就是实现化，抽象化与实现化是一对互逆的概念.
 *          实现化产生的对象比抽象化更具体，是对抽象化事物的进一步具体化的产物。
 * 脱耦：脱耦就是将抽象化和实现化之间的耦合解脱开，或者说是将它们之间的强关联改换成弱关联,
 *          将两个角色之间的继承关系改为关联关系。桥接模式中的所谓脱耦,
 *          就是指在一个软件系统的抽象化和实现化之间使用关联关系（组合或者聚合关系）而不是继承关系,
 *          从而使两者可以相对独立地变化，这就是桥接模式的用意.
 * 
 * 这个模式理解起来,确实有点乱啊.这个模式是应对软件的多维度的变化,下面的例子,变化维度有2个.
 * 一是手机品牌,一是软件. 手机品牌在不断变化, 同样, 软件也在不断变化.
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
         * 将抽象部分与它的实现部分分离，使得它们可以独立地变化
         * 1、抽象与实现分离(IPhoneCommonInterface和ISoftwareCommonInterface,手机品牌和软件分离)
         * 2、抽象部分可以变化(手机品牌可以不断变化)
         * 3、实现部分也可以变化(软件可以不断变化)
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
