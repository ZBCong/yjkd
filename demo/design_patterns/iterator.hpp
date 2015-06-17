#pragma once

// 迭代器模式: 提供一种方法顺序访问一个聚合对象中各个元素，而又不需暴露该对象的内部表示.
// STL中用迭代器分离容器与算法

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

// 这个容器实现特别简单,不能扩容,不能太长,不能...嗯,什么都不能.
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

// 算法并不需要知道容器的实现实现细节,仅通过迭代器接口,即可操作容器.
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
