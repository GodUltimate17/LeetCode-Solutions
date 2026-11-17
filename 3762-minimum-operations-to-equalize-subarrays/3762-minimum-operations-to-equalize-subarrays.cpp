class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();

        vector<int> a = nums;
        sort(a.begin(), a.end());

        a.erase(unique(a.begin(), a.end()), a.end());

        int m = a.size();

        vector<long long> ans;
        vector<int> rem(n);

        for (int i = 0; i < n; i++) {
            rem[i] = nums[i] % k;
        }

        vector<int> bad(n, 0);

        for (int i = 1; i < n; i++) {
            bad[i] = bad[i - 1] + (rem[i] != rem[i - 1]);
        }

        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // Process each query
        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            bool possible = true;

            for (int i = l + 1; i <= r; i++) {
                if (rem[i] != rem[l]) {
                    possible = false;
                    break;
                }
            }

            if (!possible) {
                ans.push_back(-1);
                continue;
            }

            vector<int> temp;

            for (int i = l; i <= r; i++) {
                temp.push_back(nums[i]);
            }

            sort(temp.begin(), temp.end());

            int median = temp[temp.size() / 2];

            long long operations = 0;

            for (int x : temp) {
                operations += abs(x - median) / k;
            }

            ans.push_back(operations);
        }

        return ans;
    }
};

// Synced seamlessly with LeetHub Pro
// Pro features: https://bit.ly/leethubpro | Free version: https://bit.ly/leethubv4
// Get it here: https://chromewebstore.google.com/detail/bcilpkkbokcopmabingnndookdogmbna