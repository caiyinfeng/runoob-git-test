#include <iostream>
#include <math.h>
using namespace std;

// 变量声明
int a, b;
int c;
float f;
#include <iostream>
using namespace std;
 
// 函数声明
int max(int num1, int num2);

 
// 函数返回两个数中较大的那个数
int max(int num1, int num2) 
{
   // 局部变量声明
   int result;
 
   if (num1 > num2)
      result = num1;
   else
      result = num2;
 
   return result; 
}

int add(int a,int b=1)
{
  int c;
  c=a+b;
  return c;
}


int main ()
{
  // 变量定义
#if 1
  int a=10;
  int b=11;
  cout<<a<<b<<endl;
  int c;
  int d;
  float f;
  int g;
 
  // 实际初始化
  a = 15;
  b = 20;
  cout<<a<<b<<endl;
  c = a + b;
 
  cout << c << endl ;

  f = 70.0/3.0;
  cout << f << endl ;
  f= f+0.33;
  g=fabs(f);
  cout << f << endl ;
  cout<<g<<endl;
#endif
#if 0
  for(int i=0 ;i<=10 ;i++)
  {
     cout<<i<<endl;
     printf("This loop will run forever.\n");
  }

#endif
  d=max(a,b);
  cout<<d<<endl;
  a=add(a,b);
  cout<<a<<b<<endl;
  a=add(a);
  cout<<a<<b<<endl;
  return 0;
}
