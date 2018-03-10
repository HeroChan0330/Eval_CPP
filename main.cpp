#include <iostream>
#include "stack.cpp"
#include "stdio.h"
#include "string.h"

using namespace std;


//Dijkstra˫ջ������
double Compute(char*str){//����ı��ʽ��Ҫ���������Ű�Χ ��ÿ2��������Ҫ�����Ű�Χ
    Stack<char> opStack;
    Stack<double> numStack;
    while(*str){
        if((*str)=='(');//�����Ų�����
        else if((*str)=='+'||(*str)=='-'||(*str)=='*'||(*str)=='/'){//�������������ջ
            opStack.Push(*str);
        }
        else if((*str)==')'){//�����ų�ջ
            double v=numStack.Pop();
            char op=opStack.Pop();
            switch(op){
                case '+':
                    v=numStack.Pop()+v;
                    break;
                case '-':
                    v=numStack.Pop()-v;
                    break;
                case '*':
                    v=numStack.Pop()*v;
                    break;
                case '/':
                    v=numStack.Pop()/v;
                    break;
            }
            numStack.Push(v);
        }
        else{//��ȡdouble
            int i=0;
            while((str[i]>=48&&str[i]<=57)||str[i]=='.'){
                i++;
            }
            double num;
            sscanf(str,"%lf",&num);
            numStack.Push(num);
            printf("%lf\n",num);
            str+=i-1;//��ָ���Ƶ�����ĩβ
        }
        str++;
    }
    return numStack.Pop();
}



//��ȡ���ŵ����ȼ�
int GetPriority(char op){
    switch(op){
    case '(':
        return 0;
        break;
    case '+':case '-':
        return 1;
        break;
    case '*':case '/':
        return 2;
        break;
    }
    return 0;
}
//��2��������������������
double SingleCompute(double a,double b,char op){
    switch(op){
    case '+':
        return a+b;
        break;
    case '-':
        return a-b;
        break;
    case '*':
        return a*b;
        break;
    case '/':
        return a/b;
        break;
    }
}
//�Ż���Dijkstra˫ջ������ http://blog.csdn.net/xieyihua1994/article/details/51644720

double Compute2(char*str){//����ı��ʽ��Ҫ���������Ű�Χ ��ÿ2��������Ҫ�����Ű�Χ
    Stack<char> opStack;
    Stack<double> numStack;
    while(*str){
        if((*str)=='('){
            opStack.Push(*str);
            str++;
        }
        else if((*str)=='+'||(*str)=='-'||(*str)=='*'||(*str)=='/'){//�������������ջ
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
        double result=Compute2(expression);
        printf("%s=%lf\n\n",expression,result);
    }
    else{
        while(1){
            char expression[50]={0};
            expression[0]='(';
            scanf("%s",expression+1);
            expression[strlen(expression)]=')';
            //�Ա��ʽ���и�ʽ��
            double result=Compute2(expression);
            printf("%s=%lf\n\n",expression,result);
        }
    }
    /*
    char*str="(1.76+98.25)";
    printf("result:%lf\n",Compute(str));
    */


    return 0;
}
