#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    string tmp;
    vector<string> res;
    vector<string> board={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    void DFS(int pos,string digits){
        if(pos==digits.size()){
            //if(tmp.size()==digits.size())
            //{
                res.push_back(tmp);
                cout << tmp.size() << endl;
            //}
            return;
        }
        int num=digits[pos]-'0';
        for(int i=0;i<board[num].size();i++){
            tmp.push_back(board[num][i]);
            DFS(pos+1,digits);
            //cout << tmp << endl;
            
            tmp.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        if(digits.size()==0) return res;
        DFS(0,digits);
        return res;
    }
};

int main()
{
    string abc="559";
    Solution aa;
    vector<string> a;
    a=aa.letterCombinations(abc);
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << endl;
    }
    return 0;
}