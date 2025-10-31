constexpr int Z = 1000001;
int _trie[Z][26];  // _trie[node][c] = index of child node via character 'a'+c
int _pre_cnt[Z];   //_pre_cnt[node] = number of strings passing through this node
int _cnt[Z];	   // total nodes used so far (root is 0)
int _tot;		   // total nodes used so far (root is 0)

struct Trie {
	Trie() {
		_tot = 0;
		new_node();
	}

	inline int new_node() {
		int x = _tot++;
		memset(_trie[x], 0, sizeof(_trie[x]));
		_cnt[x] = _pre_cnt[x] = 0;
		return x;
	}

	inline void add(string& s, int f = 1, int ptr = 0) {
		for (auto& c : s) {
			int& p = _trie[ptr][c - 'a'];
			if (!p) p = new_node();
			ptr = p;
			_pre_cnt[ptr] += f;	 // increment (or decrement) prefix count
		}
		_cnt[ptr] += f;	 // mark an exact‐end here
	}

	inline int count(string& s, int ptr = 0) {
		for (auto& c : s) {
			if (_pre_cnt[_trie[ptr][c - 'a']]) {
				ptr = _trie[ptr][c - 'a'];
				continue;
			}
			return 0;
		}
		return _cnt[ptr];
	}

	inline int pref_count(string& s, int ptr = 0) {
		for (auto& c : s) {
			if (_pre_cnt[_trie[ptr][c - 'a']])
				ptr = _trie[ptr][c - 'a'];
			else
				return 0;
		}
		return _pre_cnt[ptr];
	}

	inline array<int, 2> lcp(string& s, int ptr = 0) {
		array<int, 2> res{};
		for (auto& c : s) {
			int& p = _trie[ptr][c - 'a'];
			if (!p) break;
			ptr = p;
			++res[0];  // length of matched prefix
		}
		res[1] = _pre_cnt[ptr];	 // how many strings have that prefix
		return res;
	}

	inline ll query(string& s, int ptr = 0, ll res = 0) {
		for (auto& c : s) {
			int& p = _trie[ptr][c - 'a'];
			if (!p) break;	// prefix ends here
			ptr = p;
			res += _pre_cnt[ptr];  // accumulate how many words pass here
		}
		return res;	 // sum over all prefixes of s that exist
	}

	inline void remove(string& s, int f = -1) { add(s, f); }
};