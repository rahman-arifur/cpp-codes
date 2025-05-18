#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* child[2];
    TrieNode() {child[0] = child[1] = 0;}
};
class BitwiseTrie {
public:
    BitwiseTrie() {root = new TrieNode();}
    // void clr(TrieNode* rr) {
    //     if (rr == 0)return;
    //     clr(rr->child[0]);
    //     clr(rr->child[1]);
    //     delete rr;
    // }
    // ~BitwiseTrie() {clr(root);}
    // Insert number into trie
    void insert(int num) {
        TrieNode* cur = root;
        // from bit 31 (MSB) down to 0 (LSB)
        for (int b = 31; b >= 0; --b) {
            int bit = (num >> b) & 1;
            if (!cur->child[bit]) cur->child[bit] = new TrieNode();
            cur = cur->child[bit];
        }
    }
    int queryMinXor(int num) {
        TrieNode* cur = root;
        int xorVal = 0;
        for (int b = 31; b >= 0; --b) {
            int bit = (num >> b) & 1;
            // prefer to go to same bit to keep XOR 0 at this position
            if (cur->child[bit])cur = cur->child[bit];
            else {
                cur = cur->child[bit ^ 1];
                xorVal |= (1 << b);
            }
        }
        return xorVal;
    }
    int queryMaxXor(int num) {
        TrieNode* cur = root;
        int xorVal = 0;
        for (int b = 31; b >= 0; --b) {
            int bit = (num >> b) & 1;
            if (cur->child[bit ^ 1]) {
                cur = cur->child[bit ^ 1];
                xorVal |= (1 << b);
            } else cur = cur->child[bit];
        }
        return xorVal;
    }

private:
    TrieNode* root;
};

int findMinXORWithTrie(const vector<int>& nums) {
    if (nums.size() < 2) return 0;
    BitwiseTrie trie;
    trie.insert(nums[0]);
    int minXor = INT_MAX;
    for (size_t i = 1; i < nums.size(); ++i) {
        int curXor = trie.queryMinXor(nums[i]);
        minXor = min(minXor, curXor);
        trie.insert(nums[i]);
    }
    return minXor;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> nums = {9, 5, 3, 10};
    cout << "Minimum XOR is: " << findMinXORWithTrie(nums) << "\n";
    return 0;
}
