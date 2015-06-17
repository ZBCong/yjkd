#pragma once

// ������ģʽ: �ṩһ�ַ���˳�����һ���ۺ϶����и���Ԫ�أ����ֲ��豩¶�ö�����ڲ���ʾ.
// STL���õ����������������㷨

template<class ContainerType>
class CIterator
{
    typedef CIterator _Myt;
    typedef typename ContainerType::value_type  value_type;
    typedef typename ContainerType::pointer     pointer;

public:
    CIterator(pointer p) : m_p(p) {}

    _Myt& operator ++()
    {
        ++m_p;
        return *this;
    }

    bool operator !=(const _Myt& rhs) const { return (m_p != rhs.m_p); }
    value_type& operator *() { return *m_p; }

private:
    pointer m_p;
};

// �������ʵ���ر��,��������,����̫��,����...��,ʲô������.
class CContainter
{
    enum {_MAX_ARR_SIZE = 32};

public:
    typedef CIterator<CContainter>  iterator;
    typedef int         value_type;
    typedef int*        pointer;

    CContainter()
    {
        m_pArr  = new int[_MAX_ARR_SIZE];
        m_nSize = 0;
    }

    iterator begin() { return iterator(&m_pArr[0]); }
    iterator end()   { return iterator(&m_pArr[m_nSize]); }

    void push_back(const value_type& val)
    {
        m_pArr[m_nSize] = val;
        ++m_nSize;
    }

private:
    pointer m_pArr;
    int     m_nSize;
};

// �㷨������Ҫ֪��������ʵ��ʵ��ϸ��,��ͨ���������ӿ�,���ɲ�������.
template<class IteratorType, class T>
IteratorType Find(IteratorType first, IteratorType last, const T& val)
{
    for (; first != last; ++first)
    {
        if (*first == val)
        {
            break;
        }
    }
    return (first);
}

class CIteratorClient
{
public:
    static void main()
    {
        CContainter c;
        c.push_back(1);
        c.push_back(2);
        c.push_back(10);
        c.push_back(20);

        CContainter::iterator iter = Find(c.begin(), c.end(), 10);

        ASSERT_EQ(*iter, 10);
    }
};
