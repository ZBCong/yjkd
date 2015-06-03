#pragma once

#define SINGLETON_DECLARE(theClass) friend class y::Singleton<theClass>

namespace y
{

template<class T>
class Singleton
{
    typedef Singleton<T> _Myt;

public:
    static T& Instance()
    {
        static T obj;
        m_oc.do_nothing();
        return obj;
    }

private:
    struct _obj_creator
    {
        _obj_creator() 
        {
            _Myt::Instance(); 
        }
        inline void do_nothing() const {}
    };

private:
    static _obj_creator m_oc;
};

template<typename T> typename Singleton<T>::_obj_creator Singleton<T>::m_oc;

}
