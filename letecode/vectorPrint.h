#include <iostream>
#include <vector>
using namespace std;
void vectorcoutAuto(vector<auto> &A)
{
    for (auto a : A)
    {
        cout << a << " ";
    }
    cout <<"vector<auto>"<< endl;
}
void PrintVecofVec2(vector<vector<auto>> &A)
{
    for (int i = 0; i < A.size(); i++)
    { // 行数
        for (int j = 0; j < A[i].size(); j++)
        { // A[i].size() 第i行的列数
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}