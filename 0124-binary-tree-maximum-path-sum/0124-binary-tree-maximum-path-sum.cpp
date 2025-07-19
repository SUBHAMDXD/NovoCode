class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        dfs(root, maxSum);
        return maxSum;
    }

private:
    int dfs(TreeNode* node, int& maxSum) {
        if (!node) return 0;
        
        int left = max(0, dfs(node->left, maxSum));
        int right = max(0, dfs(node->right, maxSum));
        
        maxSum = max(maxSum, node->val + left + right);
        
        return node->val + max(left, right);
    }
};