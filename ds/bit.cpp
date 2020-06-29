#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> OST;

const int N = 100001;

OST bit[N];

void insert(int x, int y) {
	for(int i = x; i < N; i += i & -i)
		bit[i].insert(make_pair(y, x));
}

void remove(int x, int y) {
	for(int i = x; i < N; i += i & -i)
		bit[i].erase(make_pair(y, x));
}

int query(int x, int y) { int ans = 0;
	for(int i = x; i > 0; i -= i & -i)
		ans += bit[i].order_of_key(mp(y+1, 0));
	return ans;
}


////////////////////////////////////////////////////////////


// This is equivalent to calculating lower_bound on prefix sums array
// LOGN = log(N)

int bit[N]; // BIT array

int bit_search(int v) {
	int sum = 0, pos = 0;
	for(int i = LOGN; i >= 0; i--) {
		if(pos + (1 << i) < N && sum + bit[pos + (1 << i)] < v) {
			sum += bit[pos + (1 << i)];
			pos += (1 << i);
		}
	}
	return pos + 1; // +1 because 'pos' will have position of largest value less than 'v'
}
