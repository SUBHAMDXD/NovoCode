#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

// Represents a folder in the file system Trie.
struct TrieNode {
    // Maps subfolder names to their corresponding Trie nodes.
    // std::map keeps children sorted, which is crucial for consistent serialization.
    std::map<std::string, TrieNode*> children;
    
    // Flag to mark the folder for deletion.
    bool is_deleted = false;
};

class Solution {
public:
    /**
     * @brief Deletes folders with duplicate subfolder structures.
     * @param paths A 2D vector where each inner vector is a path to a folder.
     * @return A 2D vector of the remaining paths after deletion.
     */
    std::vector<std::vector<std::string>> deleteDuplicateFolder(std::vector<std::vector<std::string>>& paths) {
        
        // 1. Build the Trie from the input paths.
        TrieNode* root = new TrieNode();
        for (const auto& path : paths) {
            TrieNode* curr = root;
            for (const auto& folder_name : path) {
                if (curr->children.find(folder_name) == curr->children.end()) {
                    curr->children[folder_name] = new TrieNode();
                }
                curr = curr->children[folder_name];
            }
        }

        // 2. Serialize subtrees and collect them in a map to find duplicates.
        std::map<std::string, std::vector<TrieNode*>> structures;
        serializeAndCollect(root, structures);

        // 3. Mark all nodes that correspond to a duplicated structure.
        for (auto const& [key, nodes] : structures) {
            if (nodes.size() > 1) {
                for (TrieNode* node : nodes) {
                    node->is_deleted = true;
                }
            }
        }

        // 4. Collect the final paths of non-deleted folders.
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> current_path;
        collectPaths(root, current_path, result);
        
        // Note: In a production environment, you would deallocate the Trie memory.
        
        return result;
    }

private:
    /**
     * @brief Performs a post-order traversal to create a serialized key for each subtree.
     * @param node The current node in the Trie.
     * @param structures A map to store serialized keys and the nodes they correspond to.
     * @return The serialized key for the subtree rooted at `node`.
     */
    std::string serializeAndCollect(TrieNode* node, std::map<std::string, std::vector<TrieNode*>>& structures) {
        // A leaf node (empty folder) has an empty structure.
        if (node->children.empty()) {
            return ""; 
        }

        std::string key = "";
        // Generate the key from children's names and their structures.
        for (auto const& [name, child] : node->children) {
            key += "(" + name + serializeAndCollect(child, structures) + ")";
        }

        // A non-empty key means this is a non-empty folder structure.
        // We only consider non-empty folders for duplication.
        structures[key].push_back(node);

        return key;
    }

    /**
     * @brief Performs a pre-order traversal to collect the paths of non-deleted folders.
     * @param node The current node in the Trie.
     * @param current_path The path leading up to the current node.
     * @param result The final list of valid paths.
     */
    void collectPaths(TrieNode* node, std::vector<std::string>& current_path, std::vector<std::vector<std::string>>& result) {
        // Explore each child of the current node.
        for (auto const& [name, child] : node->children) {
            // If the child folder is NOT marked for deletion, process it.
            if (!child->is_deleted) {
                // Add the folder to the current path.
                current_path.push_back(name);
                
                // This path is valid, so add it to the results.
                result.push_back(current_path);
                
                // Recursively explore its subfolders.
                collectPaths(child, current_path, result);
                
                // Backtrack: remove the folder from the path to explore siblings.
                current_path.pop_back();
            }
        }
    }
};