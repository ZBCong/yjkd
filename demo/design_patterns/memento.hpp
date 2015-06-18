#pragma once

// 备忘录模式: 在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态.
// 这样以后就可将该对象恢复到原先保存的状态,如果使用一些公有接口让其它对象来得到对象的状态.
// 便会暴露对象的实现细节.
// -------------------------
// memento模式的几个角色:
// 1) 备忘录（Memento）角色：备忘录角色存储“Originator”的内部状态。
//    “Originator”根据需要决定备忘录角色存储“Originator”的哪些内部状态。
//    为了防止“Originator”以外的其他对象访问备忘录。
//    备忘录实际上有两个接口，“Caretaker”只能看到备忘录提供的窄接口.
//    对于备忘录角色中存放的属性是不可见的。“Originator”则能够看到一个宽接口.能够得到自己放入备忘录角色中属性。
// 2) 备忘发起（Originator）角色：“备忘发起角色”创建一个备忘录，用以记录当前时刻它的内部状态。在需要时使用备忘录恢复内部状态。
// 3) 备忘录管理者（Caretaker）角色：负责保存好备忘录。不能对备忘录的内容进行操作或检查。


// 用于记录一些备忘信息,只有发出记录的人,才可以访问他的成员
class CMemento
{
private:
    CMemento(const int nScore, const int nLevel) : m_nScore(nScore), m_nLevel(nLevel) {}

    friend class CGamePlayer;

private:
    const int m_nScore; // 分数
    const int m_nLevel; // 等级
};

class CGamePlayer
{
public:
    CGamePlayer() : m_nScore(0), m_nLevel(0) {}
    void Set(int nScore, int nLevel)
    {
        m_nScore = nScore;
        m_nLevel = nLevel;
    }

    CMemento* CreateMemento() { return new CMemento(m_nScore, m_nLevel); }
    void RestoreFromMemento(const CMemento* pMemento)
    {
        if (pMemento)
        {
            Set(pMemento->m_nScore, pMemento->m_nLevel);
        }
    }

private:
    int m_nScore;
    int m_nLevel;
};

// 管理者只能简单的存储memento,而不能对其进行任何操作
class Caretaker
{
public:
    Caretaker() : m_pMemento(NULL) {}
    ~Caretaker() {if (m_pMemento) delete m_pMemento; }

    void SetMemento(CMemento* pMemento) { m_pMemento = pMemento; }
    CMemento* GetMemento() { return m_pMemento; }

private:
    CMemento* m_pMemento;
};

class CMementoClient
{
public:
    static void main()
    {
        // 玩家初始状态
        CGamePlayer player;
        player.Set(10, 20);

        // 创建记忆点,交给管理员
        CMemento* pMemento = player.CreateMemento();
        Caretaker caretaker;
        caretaker.SetMemento(pMemento);

        // 玩家状态变更
        player.Set(100, 200);

        // 恢复玩家状态
        player.RestoreFromMemento(caretaker.GetMemento());
    }
};
