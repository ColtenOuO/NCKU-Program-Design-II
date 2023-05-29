#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <bits/stdc++.h>

#define int long long

using namespace std;

vector<int> KMP(string str, string substr) {
    int pos, now;
    vector<int> ff(substr.size()), ans;
    ff[0] = pos = -1;
    //build fail function
    for (int i = 1; i < substr.size(); i++) {
        while (pos != -1 && substr[pos+1] != substr[i]) pos = ff[pos];
        if (substr[pos+1] == substr[i]) pos++;
        ff[i] = pos;
    }
    now = -1;
    for (int i = 0; i < str.size(); i++) {
        while (now != -1 && substr[now+1] != str[i]) now = ff[now]; 
        if (substr[now+1] == str[i]) now++;
        if (now+1 == substr.size()) {
            ans.emplace_back(i-substr.size()+2);//match index
            now = ff[now];
        }
    }
    return ans;
}
signed main(int argc,char* argv[])
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	freopen(argv[1],"r",stdin);
	vector<pair<int,string>> v;
	
	char c;
	int id;
	string s;
	while( cin >> id >> c >> c )
	{
		getline(cin,s);
		s.pop_back();

		for(int i=0;i<s.size();i++) if( s[i] >= 'A' && s[i] <= 'Z' ) s[i] += ( 'a' - 'A' );
		
		string s2 = "";
		for(int i=0;i<s.size();i++)
		{
			if( s[i] == ' ' ) s2 += s[i];
			else if( s[i] >= 'a' && s[i] <= 'z' ) s2 += s[i];
		}
		
		v.push_back(make_pair(id,s2));
	}
	
	sort(v.begin(),v.end());
	
	cin.clear();
	vector<int>answer;
	freopen(argv[2],"r",stdin);

	while( getline(cin,s) )
	{
		answer.clear();
		for(int i=0;i<s.size();i++) if( s[i] >= 'A' && s[i] <= 'Z' ) s[i] += ( 'a' - 'A' );
		
		stringstream ss;
		ss << s;
		string u;
		
		vector<string> query;
		while( ss >> u ) query.push_back(u);
		
		for(int i=0;i<v.size();i++)
		{
			int ok = 0 , pos = -1;
			for(int k=0;k<query.size();k++)
			{
				vector<int> u = KMP(v[i].second,query[k]);			
				auto it = u.begin();
				while( it != u.end() )
				{
					int index = it - u.begin();
					
					bool apple = 1,banana = 1;
					
					if( u[index] - 1 + query[k].size() >= v[i].second.size() ) banana = 1;
					else if( v[i].second[ u[index] - 1 + query[k].size() ] >= 'a' && v[i].second[ u[index] - 1 + query[k].size() ] <= 'z' ) banana = 0;
					
					if( v[i].second[ u[index] - 2 ] >= 'a' && v[i].second[ u[index] - 2 ] <= 'z' ) apple = 0;
					
					if( ( u[index] == 1 && banana == 1 ) || ( apple == 1 && banana == 1 ) )
					{
						ok++ , pos = u[index];
						break;
					}
					else it++;
				}
			}
			if( ok == query.size() ) answer.push_back(v[i].first);
		}
		
		if( answer.size() == 0 ) cout << -1 << "\n";
		else
		{
			sort(answer.begin(),answer.end());
			for(int i=0;i<answer.size();i++)
			{
				cout << answer[i];
				if( i != answer.size() - 1 ) cout << " ";
			}
			cout << "\n";
		}
	}
	
	return 0;
}