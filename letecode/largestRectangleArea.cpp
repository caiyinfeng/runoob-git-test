/*
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。
*/
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
#if 0
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n=heights.size();
        vector<int> left(n),right(n);
        stack<int> mono_stack;
        for(int i=0;i<n;i++)
        {
            while(!mono_stack.empty()&&heights[mono_stack.top()]>=heights[i]){
                mono_stack.pop();
            }
            left[i]=(mono_stack.empty()?-1:mono_stack.top());
            mono_stack.push(i);
        }
        mono_stack=stack<int>();
        for(int i=n-1;i>=0;i--)
        {
            while(!mono_stack.empty()&&heights[mono_stack.top()]>=heights[i]){
                mono_stack.pop();
            }
            right[i]=(mono_stack.empty()?n:mono_stack.top());
            mono_stack.push(i);
        }
        int ans=0;
        for(int i=0;i<n;i++){
            ans=max(ans,(right[i]-left[i]-1)*heights[i]);
        }
        return ans;
    }
};
#endif
#if 1
class Solution {
public:
#if 1
    int largestRectangleArea(vector<int>& heights) {
        int n=heights.size();
        stack<int> mono_stack;
        int ans=0;
        for(int i=0;i<n;i++)
        {
            while(!mono_stack.empty()&&heights[mono_stack.top()]>=heights[i]){
                int cur=mono_stack.top();
                mono_stack.pop();
                int pre=mono_stack.empty()?-1:mono_stack.top();
                ans=max(ans,heights[cur]*(i-pre-1));
            }
            mono_stack.push(i);
        }
        while (!mono_stack.empty())
        {
            int cur=mono_stack.top();
            mono_stack.pop();
            int pre=mono_stack.empty()?-1:mono_stack.top();
            ans=max(ans,heights[cur]*(n-pre-1));
        }
        return ans;
    }
#endif
};
#endif
int main(){
    vector<int> heights={6,7,5,2,4,5,9,3};
    Solution abc;
    int ans;
    ans=abc.largestRectangleArea(heights);
    cout<<ans<<endl;
    return 0;
}