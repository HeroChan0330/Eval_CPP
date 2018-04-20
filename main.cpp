#include <iostream>
#include "stack.cpp"
#include "stdio.h"
#include "string.h"

using namespace std;

//��ȡ���ŵ����ȼ�
int GetPriority(char op){
    switch(op){
    case '(':
        return 0;
        break;
    case '+':
        return 1;
        break;
    case '/':
        return 2;
        break;
    }
    return 0;
}
double SingleCompute(double a,double b,char op){
    if(op=='+'){
        return a+b;
    }
    else if(op=='/'){
        return 1/(1/a+1/b);
    }
}


double ResistanceCompute(char*str){//���������
    Stack<char> opStack;
    Stack<double> numStack;
    while(*str){
        if((*str)=='('){
            opStack.Push(*str);
            str++;
        }
        else if((*str)=='+'||(*str)=='/'){//���������ջ
            if(GetPriority(*str)>GetPriority(opStack.Peek()))
                opStack.Push(*str);//ֱ����ջ
            else{//��ǰ������ȼ���ʽ����������ջ
                do{
                    double v=numStack.Pop();
                    v=SingleCompute(numStack.Pop(),v,opStack.Pop());
                    numStack.Push(v);
                }while(GetPriority(*str)<=GetPriority(opStack.Peek()));
                opStack.Push(*str);
            }
            str++;
        }
        else if((*str)==')'){//�����ų�ջ
            do{//һֱ��ֱ���õ�������
                double v=numStack.Pop();
                v=SingleCompute(numStack.Pop(),v,opStack.Pop());
                numStack.Push(v);
            }while(opStack.Peek()!='(');
            opStack.Pop();
            str++;
        }
        else{//��ȡdouble
            int i=0;
            while((str[i]>=48&&str[i]<=57)||str[i]=='.'){
                i++;
            }
            double num;
            sscanf(str,"%lf",&num);
            numStack.Push(num);
            //printf("%lf\n",num);
            str+=i;//��ָ���Ƶ�����ĩβ
        }
    }
    return numStack.Pop();
}

int main(int args,char*argv[])
{
    if(args>1){
        char expression[50]={0};
        expression[0]='(';
        snprintf(expression+1,48,"%s)",argv[1]);
        double result=ResistanceCompute(expression);
        printf("%s=%lf\n\n",expression,result);
    }
    else{
        while(1){
            char expression[50]={0};
            expression[0]='(';
            scanf("%s",expression+1);
            expression[strlen(expression)]=')';
            //�Ա��ʽ���и�ʽ��
            double result=ResistanceCompute(expression);
            printf("%s=%lf\n\n",expression,result);
        }
    }
    return 0;
}
