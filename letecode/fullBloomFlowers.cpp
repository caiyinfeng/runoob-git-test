/*
给你一个下标从 0 开始的二维整数数组 flowers ，其中 flowers[i] = [starti, endi] 表示第 i 朵花的 花期 从 starti 到 endi （都 包含）。
同时给你一个下标从 0 开始大小为 n 的整数数组 people ，people[i] 是第 i 个人来看花的时间。
请你返回一个大小为 n 的整数数组 answer ，其中 answer[i]是第 i 个人到达时在花期内花的 数目 。
*/
#include "vectorPrint.h"
#include <algorithm>
#include <map>
#include <numeric>
#if 1
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        map<int,int> diff;
        for(auto &f:flowers){
            diff[f[0]]++;
            diff[f[1]+1]--;
        }
        int n=people.size();
        vector<int> id(n);
        iota(id.begin(),id.end(),0);
        sort(id.begin(),id.end(),[&](int i,int j){return people[i]<people[j];});
        auto it=diff.begin();
        int sum=0;
        for(int i:id){
            while(it!=diff.end()&&it->first<=people[i])
                sum+=it++->second;
            people[i]=sum;
        }
        return people;
    }
};
#endif
#if 0
class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        int n=flowers.size();
        vector<int> starts(n),ends(n);
        for(int i=0;i<n;i++){
            starts[i]=flowers[i][0];
            ends[i]=flowers[i][1];
        }
        sort(starts.begin(),starts.end());
        sort(ends.begin(),ends.end());
        for(int &p:people){
            p=(upper_bound(starts.begin(),starts.end(),p)-starts.begin())-
              (lower_bound(ends.begin(),ends.end(),p)-ends.begin());
        }
        return people;
    }
};
#endif
int main(){
    vector<vector<int>> flowers={{1,6},{3,7},{9,12},{4,13}};
    vector<int> people={2,3,7,11};
    vector<int> result;
    Solution abc;
    result=abc.fullBloomFlowers(flowers,people);
    return 0;
}