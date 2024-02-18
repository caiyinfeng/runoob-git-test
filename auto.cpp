#include <iostream>
using namespace std;
int main()
{
    int arr[5] = {1,2,3,4,5};
    for (auto &a : arr)
    {
        a++;
        cout << a;
    }
    cout << endl;
    for (auto a : arr)
    {
        cout << a;
    }
    cout << endl;
    system("pause");
    return 0;
}