//
//  main.cpp
//  计算器3
//
//  Created by 董依萌 on 2017/4/17.
//  Copyright © 2017年 董依萌. All rights reserved.
//

#include <iostream>
#include <string>
#define Stack_Size 100
using namespace std;
class stack{                    //数字的栈
private:
    int *elem;                    //地址  头指针 记录长度
    int top;
    int stacksize;//栈数组长度
public:
    stack()
    {
        elem=new int[Stack_Size];    //栈的第一个元素存的 0 数字从1位置开始存
        top=1;
        elem[0]=0;
        stacksize=Stack_Size;
    }
    bool empty() {              //检查栈是否为空
        if (top == -1)
            return true;
        return false;
    }
    bool full() {            //检查栈是否为空
        if (top == stacksize)
            return true;
        return false;
    }
    bool gettop (int &x) {     //取栈顶元素
        if (!empty()) {
            x=elem[--top];
            //cout<<" g"<<x;
            return true;
        }
        return false;
    }
    bool instack(int &x){    //元素入栈
        if(!full()){
            elem[top++]=x;
            //cout<<" i"<<x;
            return true;
        }
        return false;
    }
    ~stack(){
        delete []elem;
        top=-1;
        stacksize=0;
        cout<<"\t\tthe end"<<endl;
    }
};
class stackk:public stack{    // 存放 符号的栈
private:
    char *elem;
    int top;
    int stacksize;//栈数组长度
public:
    stackk()
    {
        elem=new char[Stack_Size];  //0位置是“#”，在下面的 fuhao()函数里它返回0
        top=1;                      // fuhao()函数用来判断优先级
        elem[0]='#';
        stacksize=Stack_Size;
    }
    bool empty(){
        if (top == 0)
            return true;
        return false;
    }
    char gettop (char &x) {
        if (!empty()) {
            x=elem[--top];
            //cout<<" g"<<x;
            return x;
        }
        return false;
    }
    bool instack(char &x){
        if(!full()){
            elem[top++]=x;
           // cout<<" i"<<x;
            return true;
        }
        return false;
    }
    ~stackk(){
        delete []elem;
        top=-1;
        stacksize=0;
        cout<<"\t\tthe end"<<endl;
    }
    
};
int fuhao(char c){          // 符号的ascii码和优先级不一致 所以用这个函数返回
    switch(c){               // 数值 代表优先级
        case'#':return 0;
        case')':return 1;
        case'=':return 2;
        case'+':return 3;
        case'-':return 4;
        case'*':return 5;
        case'/':return 6;
        case'(':return 7;
    }
    return 0;
}
int jisuan(int x,int y,int s){    // 传递需要计算的两个数和符号对应的数字 用来返回
    if(s==3)                     //相应的计算结果
        return x+y;
    else if(s==4)
        return x-y;
    else if(s==5)
        return x*y;
    else if(s==6)
        return x/y;
    return 0;
}
int main() {
    int i,j,sum=0;
    int x,y;
    char s;
    stack s1;         // 存放数字的栈的对象
    stackk s2;        // 存放字符的栈的对象
    string st;        // 获得输入的表达式的字符串
    cin>>st;
    for(i=0;st[i]!='\0';i++){
        if(st[i]>='0'&&st[i]<='9'){    //如果是数字就写入数字栈
            j=st[i]-'0';
            s1.instack(j);
            while(st[++i]>='0'&&st[i]<='9'){ //判断下一个如果还是数字就把上一个
                j=st[i]-'0';              //取出乘10加上现在的写入数字栈
                s1.gettop(x);
                x=x*10+j;
                s1.instack(x);
            }
            i--;
        }
        else{                   //对字符进行的操作
                while(fuhao(s2.gettop(s))>=fuhao(st[i])){ //判断当前字符之前是否还有优先级比它高的再计算
                    if(fuhao(s)==7&&fuhao(st[i])!=1){
                        s2.instack(s);
                        s2.instack(st[i]);
                        break;
                    }
                    else if(fuhao(s)==7&&fuhao(st[i])==1){
                        break;
                    }
                    else if(fuhao(s)>=fuhao(st[i])){
                        s1.gettop(x);
                        s1.gettop(y);
                        sum=jisuan(y,x,fuhao(s));
                        s1.instack(sum);
                        //s2.instack(st[i]);
                    }
                }
                if(fuhao(s)<fuhao(st[i])){
                    s2.instack(s);
                    s2.instack(st[i]);
                }
            }
    }
    s1.gettop(sum);
    cout<<sum<<endl;
    return 0;
}
