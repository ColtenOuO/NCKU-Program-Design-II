#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("fma,sse,sse2,sse3,sse4")

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

string in[520005],out[520005];

int ans1[520005],ans2[520005],people[5200005];

set<int> st;

struct ouo{
	int id;
	string s;
	string timer;
};

bool cmp(const ouo &a,const ouo &b)
{
	return a.timer < b.timer;	
}
signed main(int argc,char *argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	//freopen(argv[1],"r",stdin);
	
    ifstream test(argv[1]);
    streambuf *cinbuf = std::cin.rdbuf(); // 儲存原始的 cin buffer
    cin.rdbuf(test.rdbuf()); // 用檔案的 buffer 替換 cin buffer

	char u;
	int id;
	string x,y,s;
	
	vector<ouo> v;
	
	while( cin >> s )
	{
		int idx = 0 , id;
		string x,y;
		string u;
		for(int i=0;i<s.size();i++)
		{
			if( s[i] == ',' || i == s.size() - 1 )
			{
				if( idx == 2 ) u += s[i];
				
				if(  idx == 0 ) id = stoi(u);
				else if( idx == 1 ) x = u;
				else y = u;

				idx++;
				if( idx == 3 ) v.push_back({id,x,y});
				if( people[id] == 0 ) st.insert(id);
				people[id] = 1;
				u = "";
			}
			else u += s[i];
		}
	}
	
	sort(v.begin(),v.end(),cmp);
	
	for(int i=0;i<v.size();i++)
	{
		string x = v[i].s;
		int id = v[i].id;
		string y = v[i].timer;		
		
		if( x.size() == 7 )
		{
			if( in[id].size() != 0 ) ans1[id]++;
			
			in[id] = y;
		}
		else
		{
			if( in[id].size() == 0 ) ans1[id]++;
			else
			{				
				if (in[id].substr(0, 8) != y.substr(0, 8)) {
                    ans1[id] += 2;
                    in[id] = "";
                    continue;
                }

				int now = stoi(in[id].substr(8));
                int h1 = now / 100, m1 = now % 100;

                int now2 = stoi(y.substr(8));
                int h2 = now2 / 100, m2 = now2 % 100;

				int total = 0 , check = 1;

				if( m1 <= m2 ) total = ( h2 - h1 ) * 60 + ( m2 - m1 );
				else total = ( h2 -  h1 ) * 60 - ( m1 - m2 );
				
				if( total > 8 * 60 ) ans2[id]++;
				
				in[id] = "";
			}
		}
	}

	for( auto i : st )
	{
		if( in[i].size() != 0 ) cout << i << "," << ans2[i] << "," << ans1[i] + 1 << "\n";
 		else cout << i << "," << ans2[i] << "," << ans1[i] << "\n";
	}
	
	
	return 0;
}
