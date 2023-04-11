class Solution {
public:
    string removeStars(string s) {
        string ans;
        int n = s.size(), count = 0;
        for(int i=n-1; i>=0; i--)
        {
            if(count && s[i]!='*'){
                count--;
                continue;
            }
            if(s[i]!='*')
                ans.push_back(s[i]);
            else
            {
                int j = i;
                while(j<n && s[j]=='*')
                    count++,j--;
                i = j + 1; 
            }

        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
/*
"leet**cod*e"
          ^
"e*doc**teel"
    ^
Res = eocel
ans = lecoe

Algo : 
- Reverse the string
- if char : string == *
    keep a count of star and skip the upcomming chars
- else
    add to res
*/