#pragma once
#include "design_patterns_def.h"

// 解释器模式
// 1) AbstractExpression（抽象表达式）：声明一个抽象的解释操作，这个接口为抽象语法树中所有的节点所共享。
// 2) TerminalExpression（终结符表达式）：实现与文法中的终结符相关联的解释操作。
//    实现抽象表达式中所要求的接口，主要是一个interpreter()方法。文法中每一个终结符都有一个具体终结表达式与之相对应。
// 3) NonterminalExpression（非终结符表达式）：为文法中的非终结符实现解释操作。
// 4) Context：包含解释器之外的一些全局信息。
// 缺点: 解释器模式为文法中的每一条规则至少定义了一个类，因此包含许多规则的文法可能难以管理和维护。
//       建议当文法非常复杂时，使用其他的技术如语法分析程序或编译器生成器来处理。


// Context:此处为演奏内容类
class CPlayContext
{
public:
    void SetContext(const std::string& sContext) { m_sContext = sContext; }
    std::string GetContext() const { return m_sContext; }
    bool IsEmpty() const { return m_sContext.size() <= 0; }

private:
    std::string m_sContext;
};

// AbstractExpression: 此处为表达式接口
interface IExpression
{
    void Interpret(CPlayContext* context)
    {
        std::string s1 = context->GetContext();
        std::string buf;
        std::string s2;

        if(context->GetContext().length()==0)
        {
            return;
        }
        else
        {
            std::vector<std::string> vec;

            std::stringstream ss(context->GetContext());

            while(ss >> buf)
                vec.push_back(buf);

            std::string playKey=vec[0];
            std::string playValue=vec[1];
            Excute(playKey,playValue);

            vec.erase(vec.begin(),vec.begin()+2);
            std::vector<std::string>::iterator it;
            for(it=vec.begin();it!=vec.end();it++)
            {
                s2+=*it;
                if(it!=vec.end()-1)
                    s2+=" ";
            }

            context->SetContext(s2);
        }
    }
    virtual void Excute(std::string key,std::string value) = 0;
};

//ConcreteExpression，此处为音符类
class Note : public IExpression
{
public:
    void Excute(std::string key,std::string value)
    {
        std::string note;
        switch(key[0])
        {
        case 'C':
            note="1";
            break;
        case 'D':
            note="2";
            break;
        case 'E':
            note="3";
            break;
        case 'F':
            note="4";
            break;
        case 'G':
            note="5";
            break;
        case 'A':
            note="6";
            break;
        case 'B':
            note="7";
            break;
        }
        std::cout<<note<<" ";
    }
};

//ConcreteExpression，此处为音阶类
class Scale : public IExpression
{
public:
    void Excute(std::string key, std::string value)
    {
        std::string scale;
        switch(value[0])
        {
        case '1':
            scale="低音";
            break;
        case '2':
            scale="中音";
            break;
        case'3':
            scale="高音";
            break;
        }
        std::cout<<scale<<" ";
    }
};

class CInterpreterClient
{
public:
    static void main()
    {
        CPlayContext context;
        context.SetContext("O 2 E 0.5 G 0.5 A 3 E 0.5 G 0.5 D 3 E 0.5 G 0.5 A 0.5 O 3 C 1 O 2 A 0.5 G 1 C 0.5 E 0.5 D 3");

        IExpression* pExpression = NULL;

        while(!context.IsEmpty())
        {
            char c = context.GetContext()[0];
            switch(c)
            {
            case 'O':
                pExpression=new Scale();
                break;
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'A':
            case 'B':
            case 'P':
                pExpression=new Note();
                break;
            }

            pExpression->Interpret(&context);
            delete pExpression;
        }
    }
};