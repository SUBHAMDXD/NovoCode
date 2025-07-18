#include <unordered_set>
using namespace std;

class FindElements {
private:
    unordered_set<int> values;
    void recover(TreeNode* node, int val) {
        if (node == nullptr) 
            return;
        node->val = val;
        values.insert(val);
        recover(node->left, 2 * val + 1);
        recover(node->right, 2 * val + 2);
    }
public:
    FindElements(TreeNode* root) {
        recover(root, 0);
    }
    
    bool find(int target) {
        return values.find(target) != values.end();
    }
};