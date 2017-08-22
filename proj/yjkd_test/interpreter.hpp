#pragma once
#include <map>
#include <string>
#include <stack>
#include "..\..\demo\design_patterns\design_patterns_def.h"

// ������ģʽ
// 1) AbstractExpression��������ʽ��������һ������Ľ��Ͳ���������ӿ�Ϊ�����﷨�������еĽڵ�������
// 2) TerminalExpression���ս�����ʽ��������A��B������ʽ�е�A,B������ֹ����
//    ʵ�ֳ�����ʽ����Ҫ��Ľӿڣ���Ҫ��һ��interpreter()�������ķ���ÿһ���ս������һ�������ս���ʽ��֮���Ӧ��
// 3) NonterminalExpression�����ս�����ʽ������ʽ�еġ���ż�Ϊ����ֹ����
// 4) Context����Ҫ�����͵Ķ���
// ȱ��: ������ģʽΪ�ķ��е�ÿһ���������ٶ�����һ���࣬��˰�����������ķ��������Թ����ά����
//       ���鵱�ķ��ǳ�����ʱ��ʹ�������ļ������﷨��������������������������
// ���㡰ҵ�����Ƶ���仯�������Ƶ�ģʽ�����ظ����֣��������׳���Ϊ�﷨��������⡱�ʺ�ʹ��Interpreterģʽ��


// ����ʾ��:����һ��ģ�͹�ʽ���Ӽ��������㣩��Ȼ������ģ���еĲ���������������
// �����빫ʽ: "a+b-c"
// �ٷֱ�����a,b,c��ֵ,���㹫ʽ�Ľ��

namespace interpreter
{

// global definitions
typedef char                              MapKeyType;
typedef int                               MapValueType;
typedef std::map<MapKeyType,MapValueType> MapType;


interface IExpresstion
{
    virtual MapValueType Interpret(const MapType& m) = 0;
    virtual ~IExpresstion() {}
};

class SymbolExprData
{
public:
    SymbolExprData(IExpresstion* pLeftExpr, IExpresstion* pRightExpr)
        : m_pLeftExpr(pLeftExpr)
        , m_pRightExpr(pRightExpr)
    {}

    ~SymbolExprData()
    {
        if (m_pLeftExpr)  delete m_pLeftExpr;
        if (m_pRightExpr) delete m_pRightExpr;
    }

    MapValueType InterpretLeft(const MapType& m)
    {
        if (m_pLeftExpr)
        {
            return m_pLeftExpr->Interpret(m);
        }
        return -1;
    }

    MapValueType InterpretRight(const MapType& m)
    {
        if (m_pRightExpr)
        {
            return m_pRightExpr->Interpret(m);
        }
        return -1;
    }

private:
    IExpresstion* m_pLeftExpr;
    IExpresstion* m_pRightExpr;
};

class CValExpr : public IExpresstion
{
public:
    CValExpr(const MapKeyType& key) : m_key(key)
    {}

    virtual MapValueType Interpret(const MapType& m)
    {
        MapType::const_iterator it = m.find(m_key);
        if (it != m.end())
        {
            return it->second;
        }
        return MapValueType(0);
    }

private:
    MapKeyType m_key;
};

class CAddExpr : public IExpresstion
{
public:
    CAddExpr(IExpresstion* pLeftExpr, IExpresstion* pRightExpr) : m_data(pLeftExpr, pRightExpr)
    {}

    virtual MapValueType Interpret( const MapType& m )
    {
        return m_data.InterpretLeft(m) + m_data.InterpretRight(m);
    }

private:
    SymbolExprData m_data;
};

class CSubExpr : public IExpresstion
{
public:
    CSubExpr(IExpresstion* pLeftExpr, IExpresstion* pRightExpr) : m_data(pLeftExpr, pRightExpr)
    {}

    virtual MapValueType Interpret( const MapType& m )
    {
        return m_data.InterpretLeft(m) - m_data.InterpretRight(m);
    }

private:
    SymbolExprData m_data;
};

class Calculator
{
public:
    Calculator(const std::string& sExpr)
    {
        _Analysis(sExpr);
    }

    ~Calculator()
    {
        if (m_expr)
        {
            delete m_expr;
        }
    }

    MapValueType Do(const MapType& m)
    {
        if (m_expr)
        {
            return m_expr->Interpret(m);
        }
        return -1;
    }

private:
    void _Analysis(const std::string& sExpr)
    {
        std::stack<IExpresstion*> stackExpr;
        IExpresstion* pLeftExpr  = NULL;
        IExpresstion* pRightExpr = NULL;

        for (std::string::const_iterator it = sExpr.begin(); it != sExpr.end(); ++it)
        {
            switch (*it)
            {
            case '+':
                pLeftExpr = stackExpr.top();
                pRightExpr = new CValExpr(*(++it));
                stackExpr.push(new CAddExpr(pLeftExpr, pRightExpr));
                break;
            case '-':
                pLeftExpr = stackExpr.top();
                pRightExpr = new CValExpr(*(++it));
                stackExpr.push(new CSubExpr(pLeftExpr, pRightExpr));
                break;
            default:
                stackExpr.push(new CValExpr(*it));
                break;
            }
        }
        m_expr = stackExpr.top();
    }

private:
    IExpresstion* m_expr;
};

} // end of namespace interpreter

class CInterpreterClient
{
public:
    static void main()
    {
        using namespace interpreter;

        MapType m;
        m['a'] = 10;
        m['b'] = 20;
        m['c'] = 5;

        Calculator c("a+b-c");
        int n = c.Do(m);
        ASSERT_EQ(n, 25);
    }
};
