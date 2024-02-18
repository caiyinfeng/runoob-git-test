/*
定义 str = [s, n] 表示 str 由 n 个字符串 s 连接构成。

    例如，str == ["abc", 3] =="abcabcabc" 。

如果可以从 s2 中删除某些字符使其变为 s1，则称字符串 s1 可以从字符串 s2 获得。

    例如，根据定义，s1 = "abc" 可以从 s2 = "abdbec" 获得，仅需要删除加粗且用斜体标识的字符。

现在给你两个字符串 s1 和 s2 和两个整数 n1 和 n2 。由此构造得到两个字符串，其中 str1 = [s1, n1]、str2 = [s2, n2] 。

请你找出一个最大整数 m ，以满足 str = [str2, m] 可以从 str1 获得。
*/
#include <iostream>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        if(n1==0||n2==0) return 0;
        int s1cnt=0,index=0,s2cnt=0;
                // recall 是我们用来找循环节的变量，它是一个哈希映射
        // 我们如何找循环节？假设我们遍历了 s1cnt 个 s1，此时匹配到了第 s2cnt 个 s2 中的第 index 个字符
        // 如果我们之前遍历了 s1cnt' 个 s1 时，匹配到的是第 s2cnt' 个 s2 中同样的第 index 个字符，那么就有循环节了
        // 我们用 (s1cnt', s2cnt', index) 和 (s1cnt, s2cnt, index) 表示两次包含相同 index 的匹配结果
        // 那么哈希映射中的键就是 index，值就是 (s1cnt', s2cnt') 这个二元组
        // 循环节就是；
        //    - 前 s1cnt' 个 s1 包含了 s2cnt' 个 s2
        //    - 以后的每 (s1cnt - s1cnt') 个 s1 包含了 (s2cnt - s2cnt') 个 s2
        // 那么还会剩下 (n1 - s1cnt') % (s1cnt - s1cnt') 个 s1, 我们对这些与 s2 进行暴力匹配
        // 注意 s2 要从第 index 个字符开始匹配
        unordered_map<int,pair<int,int>> recall;
        pair<int,int> pre_loop,in_loop;
        while(true){
            ++s1cnt;
            for(char ch:s1){
                if(ch==s2[index]){
                    index+=1;
                    if(index==s2.size()){
                        ++s2cnt;
                        index=0;
                    }
                }
            }
            if(s1cnt==n1) return s2cnt/n2;// 还没有找到循环节，所有的 s1 就用完了
            // 出现了之前的 index，表示找到了循环节
            if(recall.count(index)){
                auto [s1cnt_prime,s2cnt_prime]=recall[index];
                pre_loop={s1cnt_prime,s2cnt_prime};// 前 s1cnt' 个 s1 包含了 s2cnt' 个 s2
                in_loop={s1cnt-s1cnt_prime,s2cnt-s2cnt_prime};// 以后的每 (s1cnt - s1cnt') 个 s1 包含了 (s2cnt - s2cnt') 个 s2
                break;
            }else recall[index]={s1cnt,s2cnt};
        }
        // ans 存储的是 S1 包含的 s2 的数量，考虑的之前的 pre_loop 和 in_loop
        int ans=pre_loop.second+(n1-pre_loop.first)/in_loop.first*in_loop.second;
        int rest=(n1-pre_loop.first)%in_loop.first;
        for(int i=0;i<rest;++i){
            for(char ch:s1){
                if(ch==s2[index]){
                    ++index;
                    if(index==s2.size()){
                        ans++;
                        index=0;
                    }
                }
            }
        }
        return ans/n2;
    }
};
int main() {
    Solution sol;

    // Test Case 1: Basic test case
    string s1 = "acb", s2 = "ab";
    int n1 = 4, n2 = 2;
    cout << "Test Case 1: " << sol.getMaxRepetitions(s1, n1, s2, n2) << " (Expected: 2)" << endl;

    // Test Case 2: Larger strings
    string s3 = "abc", s4 = "ab";
    int n3 = 5, n4 = 2;
    cout << "Test Case 2: " << sol.getMaxRepetitions(s3, n3, s4, n4) << " (Expected: 2)" << endl;

    // Test Case 3: Empty strings
    string s5 = "", s6 = "ab";
    int n5 = 3, n6 = 1;
    cout << "Test Case 3: " << sol.getMaxRepetitions(s5, n5, s6, n6) << " (Expected: 0)" << endl;

    // Test Case 4: One of the repetition counts is zero
    string s7 = "abc", s8 = "ab";
    int n7 = 3, n8 = 0;
    cout << "Test Case 4: " << sol.getMaxRepetitions(s7, n7, s8, n8) << " (Expected: 0)" << endl;

    return 0;
}
