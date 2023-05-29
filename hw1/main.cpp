#include <bits/stdc++.h>

#define int long long

using namespace std;

signed main(int argc,char* argv[])
{
		ios_base::sync_with_stdio(false);
			cin.tie(0);
				
				int n = stoll(argv[1]) , ans = 0;
					
					for(int i=0;i<=n;i++)
							{
										cout << "(" << i << "," << n - i << ")\n";
												
												ans = max(ans,i*(n-i)); 
													}
						
						cout << ans << "\n";
							
							return 0;
}


