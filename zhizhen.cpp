#include <iostream>

using namespace std;

int main ()
{
   char  var[5] ={ 'i','p'};   // 实际变量的声明
   char  var1[5] ={ 'a','b'};
   char  *ip[5];        // 指针变量的声明

   ip[0] = &var[0];       // 在指针变量中存储 var 的地址
   ip[1] = &var1[0];
   ip[3] = &var[0];
   cout << "Value of var variable: ";
   cout << var << endl;

   cout<<&var<<endl;
   // 输出在指针变量中存储的地址
   cout << "Address stored in ip variable: ";
   cout << ip << endl;
   cout << "Address stored in ip variable: ";
   cout << ip+2 << endl;
   // 访问指针中地址的值
   cout << "Value of *ip variable: ";
   cout << *(ip+2) << endl;

   return 0;
}
