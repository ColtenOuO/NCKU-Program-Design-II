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
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <chrono>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int cnt = 0;
unordered_map<string,unordered_set<int,custom_hash> > x;
map<pair<int,string>,int> word;
unordered_map<int,int,custom_hash> total;

signed main(int argc,char* argv[])
{
 //   ios_base::sync_with_stdio(false);
   // cin.tie(0);

    ifstream cin_corpus(argv[1]);
    ifstream cin_query(argv[2]);
    string s;
    while( getline(cin_corpus,s) )
    {
//	   cout << 1 << "\n";
        int idx = 0;
        cnt++;
        for(int i=0;i<s.size();i++)
        {
            if( s[i] >= '0' && s[i] <= '9' ) idx *= 10 , idx += ( s[i] - '0' );
            else break;
        }
        
        string tmp = "";
        vector<string> v;

        for(int i=to_string(idx).size();i<s.size();i++)
        {
            if( s[i] >= 'A' && s[i] <= 'Z' ) s[i] += ( 'a' - 'A');
            if( s[i] == ' ' )
            {
                if( tmp == "" ) continue;
                x[tmp].insert(idx);
                word[make_pair(idx,tmp)]++;
                total[idx]++;
                tmp = "";
            }
            else if( s[i] >= 'a' && s[i] <= 'z' ) tmp += s[i];
        }

        if( tmp != "" )
        {
            x[tmp].insert(idx) , word[make_pair(idx,tmp)]++ , total[idx]++;
        }
    }

    while( getline(cin_query,s) )
    {
        stringstream ss;
        ss << s;
        string tmp;
        unordered_map<int,double,custom_hash> ans;
        while( ss >> tmp )
        {
            for(int i=0;i<tmp.size();i++) if( tmp[i] >= 'A' && tmp[i] <= 'Z' ) tmp[i] += ( 'a' - 'A' );
            if( x.count(tmp) != 0 )
            {
                double idf = log10( (double)cnt / (int)x[tmp].size() );

                for( auto i : x[tmp] )
                {
                    double num = (double)word[make_pair(i,tmp)] / total[i];
                    ans[i] += num * idf;
                }
            }
        }

        vector<pair<double,int> > answer;
        for( auto i : ans ) if( i.second != 0 ) answer.push_back(make_pair(i.second*-1.0,i.first));
        sort(answer.begin(),answer.end());
        
        int k = stoi(argv[3]);
        
        int less = k - answer.size();
	if( less > 0 )
	{
	    while(less--) answer.push_back({48763LL,-1});
	}
        //while(less--) cout << -1 << "\n";
	//
	for(int i=0;i<answer.size();i++)
	{
		cout << answer[i].second;
		if( i == k  - 1 ) cout << "\n";
		else cout << " ";

		if( i == k - 1 ) break;
	}
	
    }

    return 0;
}
