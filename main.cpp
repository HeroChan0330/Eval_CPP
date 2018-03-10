#include <iostream>
#include "stack.cpp"
#include "stdio.h"
#include "string.h"

using namespace std;


//Dijkstra双栈计算器
double Compute(char*str){//计算的表达式需要用左右括号包围 且每2个操作数要用括号包围
    Stack<char> opStack;
    Stack<double> numStack;
    while(*str){
        if((*str)=='(');//左括号不处理
        else if((*str)=='+'||(*str)=='-'||(*str)=='*'||(*str)=='/'){//四则运算符号入栈
            opStack.Push(*str);
        }
        else if((*str)==')'){//右括号出栈
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
        else{//获取double
            int i=0;
            while((str[i]>=48&&str[i]<=57)||str[i]=='.'){
                i++;
            }
            double num;
            sscanf(str,"%lf",&num);
            numStack.Push(num);
            printf("%lf\n",num);
            str+=i-1;//将指针移到数字末尾
        }
        str++;
    }
    return numStack.Pop();
}



//获取符号的优先级
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
//对2个操作数进行四则运算
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
//优化的Dijkstra双栈计算器 http://blog.csdn.net/xieyihua1994/article/details/51644720

double Compute2(char*str){//计算的表达式需要用左右括号包围 且每2个操作数要用括号包围
    Stack<char> opStack;
    Stack<double> numStack;
    while(*str){
        if((*str)=='('){
            opStack.Push(*str);
            str++;
        }
        else if((*str)=='+'||(*str)=='-'||(*str)=='*'||(*str)=='/'){//四则运算符号入栈
            if(GetPriority(*str)>GetPriority(opStack.Peek()))
                opStack.Push(*str);//直接入栈
            else{//把前面高优先级的式子算完再入栈
                do{
                    double v=numStack.Pop();
                    v=SingleCompute(numStack.Pop(),v,opStack.Pop());
                    numStack.Push(v);
                }while(GetPriority(*str)<=GetPriority(opStack.Peek()));
                opStack.Push(*str);
            }
            str++;
        }
        else if((*str)==')'){//右括号出栈
            do{//一直算直到得到左括号
                double v=numStack.Pop();
                v=SingleCompute(numStack.Pop(),v,opStack.Pop());
                numStack.Push(v);
            }while(opStack.Peek()!='(');
            opStack.Pop();
            str++;
        }
        else{//获取double
            int i=0;
            while((str[i]>=48&&str[i]<=57)||str[i]=='.'){
                i++;
            }
            double num;
            sscanf(str,"%lf",&num);
            numStack.Push(num);
            //printf("%lf\n",num);
            str+=i;//将指针移到数字末尾
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
            //对表达式进行格式化
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
