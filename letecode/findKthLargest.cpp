/*
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
*/
#include "vectorPrint.h"
#include <queue>
#if 1
class Solution {
public:
    int quickselect(vector<int> &nums,int l,int r,int k){
        cout<<l<<" "<<r<<endl;
        if(l==r) return nums[k];
        int partition=nums[l],i=l-1,j=r+1;
        while(i<j){
            do i++; while (nums[i]<partition);
            do j--; while (nums[j]>partition);
            if(i<j) swap(nums[i],nums[j]);
            cout<<"i:"<<i<<" "<<"j:"<<j<<endl;
        }
        //vectorcoutAuto(nums);
        
        if(k<=j) return quickselect(nums,l,j,k);
        else return quickselect(nums,j+1,r,k);
    }
    int findKthLargest(vector<int>& nums, int k) {
        int n=nums.size();
        return quickselect(nums,0,n-1,n-k);
    }
};
#endif
#if 0
class Solution {
public:
    void maxHeapify(vector<int>& a,int i,int heapSize){
        int l=i*2+1,r=i*2+2,largest=i;
        if(l<heapSize&&a[l]>a[largest]) largest=l;
        if(r<heapSize&&a[r]>a[largest]) largest=r;
        if(largest!=i){
            swap(a[i],a[largest]);
            maxHeapify(a,largest,heapSize);
        }
    }
    void buildMaxHeap(vector<int>& a,int heapSize){
        for(int i=heapSize/2;i>=0;--i) maxHeapify(a,i,heapSize);
    }
    int findKthLargest(vector<int> &nums, int k) {
        int heapSize=nums.size();
        buildMaxHeap(nums,heapSize);
        for(int i=nums.size()-1;i>=nums.size()-k+1;--i){
            swap(nums[0],nums[i]);
            --heapSize;
            maxHeapify(nums,0,heapSize);
        }
        return nums[0];
    }
};
#endif
#if 0
class Solution 
{
public:
    int findKthLargest(vector<int>& nums, int k) 
    {
        priority_queue<int, vector<int>, less<int>> maxHeap;
        for (int x : nums)
            maxHeap.push(x);
        for (int _ = 0; _ < k - 1; _ ++)
            maxHeap.pop();
        return maxHeap.top();
    }
};
#endif
int main()
{
    Solution abc;
    vector<int> nums = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k = 4;
    int result;
    result = abc.findKthLargest(nums, k);
    return 0;
}