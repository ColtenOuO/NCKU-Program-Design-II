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
#include<bits/stdc++.h>

using namespace std;

map<int,int> people;

struct ouo{
	int id;
	string s;
	string timer;
};

bool leap(int year)
{
	if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return 1;
            else
                return 0;
        }
        else
            return 1;
    }
    else
        return 0;
}
bool cmp(const ouo &a,const ouo &b)
{
	if( a.id == b.id )
	{
		return a.timer < b.timer;	
	}
	
	return a.id < b.id;	
}
struct cmp2
{
	bool operator()( pair<pair<int,int>,pair<string,string>> &a , pair<pair<int,int>,pair<string,string>> &b )
	{
		if( a.first.first == b.first.first && a.first.second == b.first.second ) return a.second.first < b.second.first;
		else if( a.first.first == b.first.first ) return a.first.second > b.first.second;
		else return a.first.first < b.first.first;
	}
};
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
				u = "";
			}
			else u += s[i];
		}
	}
	
	sort(v.begin(),v.end(),cmp);
	
	int head_idx = 0,c = 0;
	priority_queue<pair<pair<int,int>,pair<string,string>>,vector<pair<pair<int,int>,pair<string,string>>>,cmp2> pq;
	
	for(int i=0;i<v.size();i++)
	{
		if( i == 0 ) c = 1;
		else
		{
			if( v[i].id == v[i-1].id && v[i].timer == v[i-1].timer ) continue;
			else
			{
				if( v[i].id != v[i-1].id )
				{
					pq.push( { { c , v[i-1].id } , { v[head_idx].timer , v[i-1].timer } } );
					c = 1;
					head_idx = i;
				}
				else
				{
					bool consecutive = false;
					string yy1 = v[i-1].timer.substr(0,4);
					string yy2 = v[i].timer.substr(0,4);
					string mm1 = v[i-1].timer.substr(4,2);
					string mm2 = v[i].timer.substr(4,2);
					string dd1 = v[i-1].timer.substr(6,2);
					string dd2 = v[i].timer.substr(6,2);
					
					if( yy1 != yy2 && mm1 == "12" && mm2 == "1" && dd1 == "31" && dd2 == "1" ) consecutive = 1;
					else if( yy1 == yy2 && stoi(mm2) - stoi(mm1) == 1 && stoi(dd2) == 1 )
					{
						bool check = false;
						if( mm1 == "1" || mm1 == "3" || mm1 == "5" || mm1 == "7" || mm1 == "8" || mm1 == "10" || mm1 == "12" )
						{
							if( dd1 == "31" ) check = true;
						}
						else if( mm1 == "2" && dd1 == "29" ) check = true;
						else if( mm1 == "2" && dd1 == "28" && leap(stoi(yy1)) == true ) check = true;
						else if( dd1 == "30" ) check = true;
						
						if( check == true ) consecutive = 1;
					}
					else if( yy1 == yy2 && mm1 == mm2 && stoi(dd2) - stoi(dd1) == 1 ) consecutive = 1;
					
					if( yy1 == yy2 && dd1 == dd2 ) continue;
					else if( consecutive == 1 ) c++;
					else
					{
						pq.push( { { c , v[i-1].id } , { v[head_idx].timer , v[i-1].timer } } );
						c = 1;
						head_idx = i;
					}
				}
			}
			
			if( i == v.size() - 1 ) pq.push( { { c , v[i].id } , { v[head_idx].timer , v[i].timer } } );
		}
	}
	
	int cnt = 0;
	
	while( pq.size() != 0 && cnt != 3 )
	{	
		auto ans = pq.top();
		pq.pop();
		
		if( people[ans.first.second] == 1 ) continue;
		else
		{
			people[ans.first.second] = 1;
			cnt++;
			
			cout << ans.first.second << "," << ans.first.first << "," << ans.second.first.substr(0,8) << "," << ans.second.second.substr(0,8) << "\n";
		}
	}
	
	return 0;
}
