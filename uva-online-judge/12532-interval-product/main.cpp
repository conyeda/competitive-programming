#include<bits/stdc++.h>
using namespace std;

typedef long long 			ll;
typedef pair<int, int> 		ii;
typedef vector<ii> 			vii;
typedef vector<int> 		vi;
#define INF 1000000000

class SegmentTree {         // the segment tree is stored like a heap array
private: vi st, A;            // recall that vi is: typedef vector<int> vi;
  int n;
  int left (int p) { return p << 1; }     // same as binary heap operations
  int right(int p) { return (p << 1) + 1; }

  void build(int p, int L, int R) {                           // O(n log n)
    if (L == R)                            // as L == R, either one is fine
      st[p] = A[L];                                         // store the index
    else {                                // recursively compute the values
      build(left(p) , L              , (L + R) / 2);
      build(right(p), (L + R) / 2 + 1, R          );
      int p1 = st[left(p)], p2 = st[right(p)];
      st[p] = p1 * p2;
  } }

  int rmq(int p, int L, int R, int i, int j) {                  // O(log n)
    if (i >  R || j <  L) return -2; // current segment outside query range
    if (L >= i && R <= j) return st[p];               // inside query range

     // compute the min position in the left and right part of the interval
    int p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
    int p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

    if (p1 == -2) return p2;   // if we try to access segment outside query
    if (p2 == -2) return p1;                               // same as above
    return p1 * p2; }          // as as in build routine

  int update_range(int p, int L, int R, int i, int j, int new_value) {
    // if the current interval does not intersect 
    // the update interval, return this st node value!
    if (i > R || j < L)
      return st[p];

    // if the current interval is included in the update range,
    // update that st[node]
    if (L == R) {
      A[L] = new_value; // update the underlying array
      return st[p] = new_value; // this index
    }

    // compute the minimum pition in the 
    // left and right part of the interval
    int p1, p2;
    p1 = update_range(left(p) , L              , (L + R) / 2, i, j, new_value);
    p2 = update_range(right(p), (L + R) / 2 + 1, R          , i, j, new_value);

    // return the pition where the overall minimum is
    return st[p] = p1 * p2;
  }

public:
  SegmentTree(const vi &_A) {
    A = _A; n = (int)A.size();              // copy content for local usage
    st.assign(4 * n, 0);            // create large enough vector of zeroes
    build(1, 0, n - 1);                                  // recursive build
  }

  int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }   // overloading

  int update_range(int i, int j, int new_value) {
    return update_range(1, 0, n - 1, i, j, new_value); }
};

int N, K;

void solve()
{
	int i = 1, j = 1;
	int x = 0;
	char ch;
	string res = "";
	vi v;
	
	while (N--)
	{
		cin >> x;
		if (x != 0)
		{
			v.push_back((x > 0 ? 1 : -1));
		}
		else
		{
			v.push_back(0);
		}
	}
	
	SegmentTree st(v);
	
	while (K--)
	{
		cin >> ch >> i >> j;
		i--;
		
		if (ch == 'C')
		{
			if (j != 0)
			{
				j = j > 0 ? 1 : - 1;
			}
			st.update_range(i, i, j);
		}
		else
		{
			j--;
			x = st.rmq(i, j);
			
			if (x == 0)
			{
				res += '0';
			}
			else
			{
				res += (x > 0) ? "+" : "-";
			}
		}
	}
	
	cout << res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("my-output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    #endif
    
    while (cin >> N >> K)
    {
        solve();
        cout << "\n";
    }

    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
    return 0;
}
