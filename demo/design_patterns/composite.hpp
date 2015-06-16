#pragma once

// ���ģʽ:

#include <list>
#include <algorithm>

// �����ӿ�
interface IComponent
{
    virtual ~IComponent() {}
    virtual void Operation() = 0;
    virtual void Add(IComponent* pChild) {}
    virtual void Remove(IComponent* pChild) {}
    virtual IComponent* GetChild(int nIndex) { return NULL; }
};

// Ҷ�ڵ�,û���ӽڵ�
class CLeaf : public IComponent
{
public:
    virtual void Operation() {}
};

// ���ڴ洢�ӽڵ�
class CComposite : public IComponent
{
    typedef std::list<IComponent*> _ComonentListType;

private:
    _ComonentListType m_components;

public:
    ~CComposite()
    {
        for (_ComonentListType::iterator it = m_components.begin(); it != m_components.end(); ++it)
        {
            delete (*it);
        }
    }

    virtual void Operation()
    {
        for (_ComonentListType::iterator it = m_components.begin(); it != m_components.end(); ++it)
        {
            (*it)->Operation();
        }
    }

    virtual void Add(IComponent* pChild)
    {
        m_components.push_back(pChild);
    }

    virtual void Remove(IComponent* pChild)
    {
        _ComonentListType::iterator it = std::find(m_components.begin(), m_components.end(), pChild);
        if (m_components.end() != it)
        {
            delete (*it);
            m_components.erase(it);
        }
    }

    virtual IComponent* GetChild(int nIndex)
    {
        int i = 0;
        _ComonentListType::iterator it;
        for (it=m_components.begin(); it!=m_components.end(); ++it)
        {
            if (i == nIndex)
            {
                return *it;
            }
            i++;
        }

        return NULL;
    }
};

class CCompositeClient
{
public:
    static void main()
    {
        CLeaf* pLeaf1 = new CLeaf();
        CLeaf* pLeaf2 = new CLeaf();

        CComposite* pComposite = new CComposite();
        pComposite->Add(pLeaf1);
        pComposite->Add(pLeaf2);
        pComposite->Operation();
        pComposite->Remove(pLeaf1);
        pComposite->GetChild(0)->Operation();

        delete pComposite;
    }
};
