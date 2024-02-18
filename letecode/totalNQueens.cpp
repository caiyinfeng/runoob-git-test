#include <iostream>
using namespace std;
class Solution {
public:
    int totalNQueens(int n) {
        dfs(n, 0, 0, 0, 0);
        
        return this->res;
    }
    
    void dfs(int n, int row, int col, int ld, int rd) {
        if (row >= n) { res++; return; }
        
        // 将所有能放置 Q 的位置由 0 变成 1，以便进行后续的位遍历
        int bits = ~(col | ld | rd) & ((1 << n) - 1);
        cout<<"bits:"<<bits<<endl;
        while (bits > 0) {
            int pick = bits & -bits; // 注: x & -x
            cout<<"first "<<"pick:"<<pick<<" bits:"<<bits<<" col:"<<col<<" ld:"<<ld<<" rd:"<<rd<<endl;
            dfs(n, row + 1, col | pick, (ld | pick) << 1, (rd | pick) >> 1);
            bits &= bits - 1; // 注: x & (x - 1)
            cout<<"return "<<"pick:"<<pick<<" bits:"<<bits<<" col:"<<col<<" ld:"<<ld<<" rd:"<<rd<<endl;
        }
    }

private:
    int res = 0;
};
int main()
{
    int abc;
    Solution ab;
    abc=ab.totalNQueens(4);
}