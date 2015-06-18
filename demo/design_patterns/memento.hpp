#pragma once

// ����¼ģʽ: �ڲ��ƻ���װ�Ե�ǰ���£�����һ��������ڲ�״̬�����ڸö���֮�Ᵽ�����״̬.
// �����Ժ�Ϳɽ��ö���ָ���ԭ�ȱ����״̬,���ʹ��һЩ���нӿ��������������õ������״̬.
// ��ᱩ¶�����ʵ��ϸ��.
// -------------------------
// mementoģʽ�ļ�����ɫ:
// 1) ����¼��Memento����ɫ������¼��ɫ�洢��Originator�����ڲ�״̬��
//    ��Originator��������Ҫ��������¼��ɫ�洢��Originator������Щ�ڲ�״̬��
//    Ϊ�˷�ֹ��Originator�����������������ʱ���¼��
//    ����¼ʵ�����������ӿڣ���Caretaker��ֻ�ܿ�������¼�ṩ��խ�ӿ�.
//    ���ڱ���¼��ɫ�д�ŵ������ǲ��ɼ��ġ���Originator�����ܹ�����һ����ӿ�.�ܹ��õ��Լ����뱸��¼��ɫ�����ԡ�
// 2) ��������Originator����ɫ�������������ɫ������һ������¼�����Լ�¼��ǰʱ�������ڲ�״̬������Ҫʱʹ�ñ���¼�ָ��ڲ�״̬��
// 3) ����¼�����ߣ�Caretaker����ɫ�����𱣴�ñ���¼�����ܶԱ���¼�����ݽ��в������顣


// ���ڼ�¼һЩ������Ϣ,ֻ�з�����¼����,�ſ��Է������ĳ�Ա
class CMemento
{
private:
    CMemento(const int nScore, const int nLevel) : m_nScore(nScore), m_nLevel(nLevel) {}

    friend class CGamePlayer;

private:
    const int m_nScore; // ����
    const int m_nLevel; // �ȼ�
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

// ������ֻ�ܼ򵥵Ĵ洢memento,�����ܶ�������κβ���
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
        // ��ҳ�ʼ״̬
        CGamePlayer player;
        player.Set(10, 20);

        // ���������,��������Ա
        CMemento* pMemento = player.CreateMemento();
        Caretaker caretaker;
        caretaker.SetMemento(pMemento);

        // ���״̬���
        player.Set(100, 200);

        // �ָ����״̬
        player.RestoreFromMemento(caretaker.GetMemento());
    }
};
