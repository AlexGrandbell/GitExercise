#include <iostream>
#include <vector>
#include "func.h"

using namespace std;
 
//最长公共子序列，但是不仅要长度，还要输出这个序列的具体内容是什么
string longestCommonSubsequence(string text1, string text2) {
    int m = text1.size();
    int n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));//dp[i][j]表示text1[0...i-1]和text2[0...j-1]的最长公共子序列长度
    vector<vector<int>> path(m + 1, vector<int>(n + 1, 0));//1表示左上，2表示上，3表示左
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            //如果当前字符相等，那么当前的最长公共子序列长度就是前一个字符的最长公共子序列长度+1
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                path[i][j] = 1;
            } else {
                //如果当前字符不相等，那么当前的最长公共子序列长度就是前一个字符的最长公共子序列长度
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    path[i][j] = 2;
                } else {
                    dp[i][j] = dp[i][j - 1];
                    path[i][j] = 3;
                }
            }
        }
    }
    string res = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (path[i][j] == 1) {
            res = text1[i - 1] + res;
            i--;
            j--;
        } else if (path[i][j] == 2) {
            i--;
        } else {
            j--;
        }
    }
    return res;
}

int main() {
    string text1,text2;
    cin >> text1 >> text2;
    string res = longestCommonSubsequence(text1, text2);
    //获得了LCS后，还需要将原来两个字符串中剩余的字符拼接到该字符串后面，并且整个字符串不能有重复字符
    int i = 0, j = 0;
    for (int k = 0; k < res.size(); k++) {
        while (text1[i] != res[k]) {
            cout << text1[i++];
        }
        while (text2[j] != res[k]) {
            cout << text2[j++];
        }
        cout << res[k];
        i++;
        j++;
    }
    while (i < text1.size()) {
        cout << text1[i++];
    }
    while (j < text2.size()) {
        cout << text2[j++];
    }
    return 0;
}
