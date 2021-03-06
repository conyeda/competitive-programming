#include<bits/stdc++.h>
using namespace std;

// Notice the number of spaces in the output. They have to be exactly these.

typedef long long         ll;
typedef pair<int, int>    ii;
typedef vector<ii>        vii;
typedef vector<int>       vi;
#define INF 1000000000;

int row[8], a, b, lineCounter;
bitset<30> rw, ld, rd; // row and diagonals

bool can_place(int r, int c)
{
  if (b == c && r != a)
  {
    return false;
  }
  
  return !rw[r] && !ld[r-c+7] && !rd[r+c];
}

void backtrack(int c)
{ 
  if (c == 8)
  {
    printf("%2d      %d", ++lineCounter, row[0] + 1);
    
    for (int i = 1; i < 8; i++)
    {
      printf(" %d", row[i] + 1);
    }
    
    printf("\n");
  }
  else
  {
    for (int r = 0; r < 8; r++)
    {
      if (can_place(r, c))
      {
        rw[r] = ld[r-c+7] = rd[r+c] = true;
        row[c] = r;
        backtrack(c + 1);
        rw[r] = ld[r-c+7] = rd[r+c] = false;
      }
    }
  }
}

void solve()
{ 
  cin >> a >> b;
  a--;
  b--;
  
  backtrack(0);
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

  int t = 1;
  cin >> t;

  while (t--)
  {
    memset(row, 0, sizeof row);
    lineCounter = 0;
    printf("SOLN       COLUMN\n");
    printf(" #      1 2 3 4 5 6 7 8\n\n");
    
    solve();
    
    if (t != 0)
    {
      printf("\n");
    }
  }

  cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
  return 0;
}
