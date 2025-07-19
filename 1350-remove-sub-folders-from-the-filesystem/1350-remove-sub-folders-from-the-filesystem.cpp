class Solution {
public:
    vector<string> removeSubfolders(vector<string>& folder) {
        sort(folder.begin(), folder.end());
        
        vector<string> result;
        
        for (const string& f : folder) {
            if (result.empty() || !isSubfolder(result.back(), f)) {
                result.push_back(f);
            }
        }
        
        return result;
    }
    
private:
    bool isSubfolder(const string& parent, const string& child) {
        if (child.length() <= parent.length()) {
            return false;
        }
        
        if (child.substr(0, parent.length()) == parent && child[parent.length()] == '/') {
            return true;
        }
        
        return false;
    }
};
