#include "vectorPrint.h"
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.size()==0||grid.size()==0)
        {
            return 0;
        }
        int rows=grid.size(),columns=grid[0].size();
        auto dp=vector<int>(columns);
        dp[0]=grid[0][0];
        for(int j=1;j<columns;++j)
        {
            dp[j]=dp[j-1]+grid[0][j];
            cout<<"j: "<<j<<" dp[j]: "<<dp[j]<<endl;            
        }        
        for(int i=1;i<rows;i++)
        {
            dp[0]=dp[0]+grid[i][0];
            cout<<"dp[0]"<<dp[0]<<endl;
            for(int j=1;j<columns;++j)
            {
                dp[j]=min(dp[j],dp[j-1])+grid[i][j];
                cout<<"j: "<<j<<" dp[j]: "<<dp[j]<<endl;
            }
        }
        return dp[columns-1];
    }
};

int main()
{
    vector<vector<int>> ab={{1,3,1},{1,5,1},{4,2,1}};
    int a;
    Solution abc;
    a=abc.minPathSum(ab);
    cout<<a<<endl;
    return 0;
}