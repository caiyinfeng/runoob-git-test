#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
 
int main ()
{
   int i,j;
 
   // 设置种子
   srand( (unsigned)time(NULL) );

   /* 生成 10 个随机数 */
   for( i = 0; i < 10; i++ )
   {
      // 生成实际的随机数
      j= 10+rand()%100;
      cout <<"随机数： " << j <<"rand()"<<rand()<<"rand()%100 "<<rand()%100<< endl;
   }

   return 0;
}
