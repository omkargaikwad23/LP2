#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        //2D array to store all results
        vector<vector<string>>result;
        //temp array of strings ["....", "....", "....", "...."]
        vector<string> temp(n, string(n, '.')); 
        //record column of queens previous rows
        int dp[n];
        Helper(result, temp, dp, 0, n);
        return result;
    }
    
    void Helper(vector<vector<string>>&result, 
                vector<string>&temp, 
                int dp[], int row, int n){
        
        if(row==n){
            result.push_back(temp);
            return;
        }
        for(int col = 0; col<n; col++){
            if(valid(dp, row, col, n)){
                dp[row] = col;
                temp[row][col] = 'Q';
                Helper(result, temp, dp, row+1, n);
                temp[row][col] = '.';
            }
        }
    }
    
    
    bool valid(int dp[], int row, int col, int n){
        for(int i=0; i<row; i++){
            if(dp[i]==col || abs(row-i)==abs(dp[i]-col)){
                return false;
            }
        }
        return true;
    }
};

int main(){
    
}