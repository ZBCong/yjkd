#pragma once
#include "design_patterns_def.h"

// ������ģʽ
// 1) AbstractExpression��������ʽ��������һ������Ľ��Ͳ���������ӿ�Ϊ�����﷨�������еĽڵ�������
// 2) TerminalExpression���ս�����ʽ����ʵ�����ķ��е��ս��������Ľ��Ͳ�����
//    ʵ�ֳ�����ʽ����Ҫ��Ľӿڣ���Ҫ��һ��interpreter()�������ķ���ÿһ���ս������һ�������ս���ʽ��֮���Ӧ��
// 3) NonterminalExpression�����ս�����ʽ����Ϊ�ķ��еķ��ս��ʵ�ֽ��Ͳ�����
// 4) Context������������֮���һЩȫ����Ϣ��
// ȱ��: ������ģʽΪ�ķ��е�ÿһ���������ٶ�����һ���࣬��˰�����������ķ��������Թ����ά����
//       ���鵱�ķ��ǳ�����ʱ��ʹ�������ļ������﷨��������������������������


// Context:�˴�Ϊ����������
class CPlayContext
{
public:
    void SetContext(const std::string& sContext) { m_sContext = sContext; }
    std::string GetContext() const { return m_sContext; }
    bool IsEmpty() const { return m_sContext.size() <= 0; }

private:
    std::string m_sContext;
};

// AbstractExpression: �˴�Ϊ���ʽ�ӿ�
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

//ConcreteExpression���˴�Ϊ������
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

//ConcreteExpression���˴�Ϊ������
class Scale : public IExpression
{
public:
    void Excute(std::string key, std::string value)
    {
        std::string scale;
        switch(value[0])
        {
        case '1':
            scale="����";
            break;
        case '2':
            scale="����";
            break;
        case'3':
            scale="����";
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