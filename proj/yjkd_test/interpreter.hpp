#pragma once
#include <map>
#include <string>
#include <stack>
#include "..\..\demo\design_patterns\design_patterns_def.h"

// 解释器模式
// 1) AbstractExpression（抽象表达式）：声明一个抽象的解释操作，这个接口为抽象语法树中所有的节点所共享。
// 2) TerminalExpression（终结符表达式）：例如A◎B这个表达式中的A,B即是终止符。
//    实现抽象表达式中所要求的接口，主要是一个interpreter()方法。文法中每一个终结符都有一个具体终结表达式与之相对应。
// 3) NonterminalExpression（非终结符表达式）：上式中的◎符号即为非终止符。
// 4) Context：需要被解释的东西
// 缺点: 解释器模式为文法中的每一条规则至少定义了一个类，因此包含许多规则的文法可能难以管理和维护。
//       建议当文法非常复杂时，使用其他的技术如语法分析程序或编译器生成器来处理。
// 满足“业务规则频繁变化，且类似的模式不断重复出现，并且容易抽象为语法规则的问题”适合使用Interpreter模式。


// 代码示例:输入一个模型公式（加减四则运算），然后输入模型中的参数，运算出结果。
// 如输入公式: "a+b-c"
// 再分别输入a,b,c的值,计算公式的结果

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
