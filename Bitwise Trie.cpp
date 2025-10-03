#include <bits/stdc++.h>
using namespace std;
struct TrieNode {
	TrieNode* child[2];
	int cnt;  // number of values passing through this node
	TrieNode() {
		child[0] = child[1] = 0;
		cnt = 0;
	}
};
class BitwiseTrie {
public:
	const int B = 30;  // 62 for ll
	using T = int;	   // make long long
	BitwiseTrie() { root = new TrieNode(); }

	// void clr(TrieNode* rr) {
	//     if (rr == 0)return;
	//     clr(rr->child[0]);
	//     clr(rr->child[1]);
	//     delete rr;
	// }
	// ~BitwiseTrie() {clr(root);}

	void insert(T num) {
		TrieNode* cur = root;
		cur->cnt++;
		for (int b = B; b >= 0; --b) {
			int bit = (num >> b) & 1;
			if (!cur->child[bit]) cur->child[bit] = new TrieNode();
			cur = cur->child[bit];
			cur->cnt++;
		}
	}
	void remove(int num) {
		TrieNode* cur = root;
		for (int b = B; b >= 0; --b) {
			int bit = (num >> b) & 1;
			if (!cur->child[bit] || cur->child[bit]->cnt == 0) return;
			cur = cur->child[bit];
			cur->cnt--;
		}
	}
	T queryMaxXor(T num) const {
		TrieNode* cur = root;
		if (!cur || cur->cnt == 0) return 0;
		T xorVal = 0;
		for (int b = B; b >= 0; --b) {
			int bit = (num >> b) & 1;
			int want = bit ^ 1;
			if (cur->child[want] && cur->child[want]->cnt > 0) {
				xorVal |= (1LL << b);
				cur = cur->child[want];
			} else if (cur->child[bit] && cur->child[bit]->cnt > 0)
				cur = cur->child[bit];
			else
				break;
		}
		return xorVal;
	}

private:
	TrieNode* root;
};
