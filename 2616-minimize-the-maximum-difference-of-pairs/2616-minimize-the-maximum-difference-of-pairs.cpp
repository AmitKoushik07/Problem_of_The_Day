class Solution {
    using pair_int = pair<int, int>;
public:
    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> diffs;
        int high = 0;
        for (int i = 0; i < n-1; ++i) {
            int diff = abs(nums[i]-nums[i+1]);
            diffs.push_back(diff);
            high = max(high, diff);
        }
        int low = 0;               
        while (low < high) {
            int mid = (low+high)/2;
            if (valid(diffs, mid, p)) {
                high = mid;
            } else {
                low = mid+1;
            }
        }
        return low;
    }
    
    bool valid(vector<int>& diffs, int mid, int p) {
        int cnt = 0;
        bool used = false;
        for (auto d : diffs) {
            if (!used && d <= mid) {
                ++cnt;
                used = true;
            } else {
                used = false;
            }
        }
        return cnt >= p;
    }
};