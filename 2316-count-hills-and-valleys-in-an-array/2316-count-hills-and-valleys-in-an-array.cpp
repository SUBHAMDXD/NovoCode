class Solution {
public:
    int countHillValley(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) return 0;
        
 int count = 0;
        int i = 1;
        
        while (i < n - 1) {
            // Find the closest non-equal neighbor on the left
            int left = i - 1;
            while (left >= 0 && nums[left] == nums[i]) {
                left--;
            }
            
            // Find the closest non-equal neighbor on the right
            int right = i + 1;
            while (right < n && nums[right] == nums[i]) {
                right++;
            }
            
            // Check if we have valid neighbors on both sides
            if (left >= 0 && right < n) {
                // Check if it's a hill (both neighbors smaller)
                if (nums[left] < nums[i] && nums[right] < nums[i]) {
                    count++;
                }
                // Check if it's a valley (both neighbors larger)
                else if (nums[left] > nums[i] && nums[right] > nums[i]) {
                    count++;
                }
            }
            
            // Skip all equal elements to avoid double-counting
            while (i < n - 1 && nums[i] == nums[i + 1]) {
                i++;
            }
            i++;
        }
        
        return count;
    }
};
