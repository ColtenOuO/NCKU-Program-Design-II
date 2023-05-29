#pragma GCC optimize(3)
#pragma GCC target("avx")
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

#include <bits/stdc++.h>
#include <unordered_map>
#include "parser.h"

#define int long long

using namespace std;

unordered_map<string,unordered_set<int>> data2;
unordered_map<string,set<int32_t>> init_mp;

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

bool cmp(pair<double,int> &a,pair<double,int> &b)
{
    if( a.first == b.first ) return a.second < b.second;
    return a.first > b.first;
}
signed main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream corpus(argv[1]);
    ifstream query(argv[2]);
    string s;
    char u;
    int idx,cnt = 0;
    str_token new_data(init_mp);
    while( corpus >> idx >> u >> u ) // read 'id',',','"'
    {
        getline(corpus,s);
        string_token_parsing(s,new_data,idx);
        cnt++;
    }

    //cin.clear();
   // freopen(argv[2],"r",stdin);
    unordered_map<int,double,custom_hash> answer;
    string input;
    while( getline(query,input) )
    {
        //answer.clear();
        stringstream ss;
        ss << input;
        string query;
        
        while( ss >> query )
        {
            string u;
            for(int i=0;i<query.size();i++)
            {
                if( query[i] >= 'A' && query[i] <= 'Z' ) query[i] += ( 'a' - 'A' );
            }

            int total = 0;

            int sz = new_data.mp[query].size();

            for( auto i : new_data.mp[query] )
            {
                answer[i] += log10((double)cnt / sz );
            }
        }

        vector<pair<double,int>> v;
        for( auto i : answer ) v.push_back(make_pair(i.second,i.first)) , answer[i.first] = 0.0;
        sort(v.begin(),v.end(),cmp);

      //  for(int i=0;i<2;i++) cout << v[i].second << " " << v[i].first << "\n";

        int k = stoi(argv[3]);
        for(int i=0;i<k;i++)
        {
            if( i >= v.size() ) cout << -1;
            else if( v[i].first <= 0 ) cout << -1;
            else
            {
                int ouo = v[i].second;  
                cout << v[i].second;                
            }

            if( i != k - 1 ) cout << " ";
            else cout << "\n";
        }
    }
}
