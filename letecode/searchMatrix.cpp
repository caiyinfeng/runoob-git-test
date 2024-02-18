/*
给你一个满足下述两条属性的 m x n 整数矩阵：

每行中的整数从左到右按非递减顺序排列。
每行的第一个整数大于前一行的最后一个整数。
给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。
*/
#include "vectorPrint.h"
#include <algorithm>
#if 1
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        auto row=upper_bound(matrix.begin(),matrix.end(),target,[](const int b,const vector<int>& a){
            cout<<"b<a[0]"<<endl;
            return b<a[0];
        });
        if(row==matrix.begin())
        {
            return false;
        }
        for(vector<int>::iterator it = row->begin(); it!=row->end(); it++)
        {
            cout<<*it<<endl;
        }
        --row;
        for(vector<int>::iterator it = row->begin(); it!=row->end(); it++)
        {
            cout<<*it<<endl;
        }
        return binary_search(row->begin(),row->end(),target);
    }
};
#endif
#if 0
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(),n=matrix[0].size();
        int low=0,high=m*n-1;
        while(low<=high)
        {
            int mid=(high+low)>>1;
            int x=matrix[mid/n][mid%n];
            if(x<target)
            {
                low=mid+1;
            }else if(x>target){
                high=mid-1;
            }else{
                return true;
            }
        }
        return false;
    }
};
#endif
int main()
{
    vector<vector<int>> ab={{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    int target=11;
    Solution abc;
    bool result;
    result=abc.searchMatrix(ab,target);
    cout<<result<<endl;
    return 0;
}