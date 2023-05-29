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

vector<pair<str_token,int>> data2;
unordered_map<string,int32_t> init_mp;

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
    while( corpus >> idx >> u >> u ) // read 'id',',','"'
    {
        getline(corpus,s);

        str_token new_data(init_mp);

        string_token_parsing(s,new_data);
        data2.push_back(make_pair(new_data,idx));
        cnt++;
    }

    //cin.clear();
   // freopen(argv[2],"r",stdin);
     map<int,double> answer;
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

            for( auto i : data2 )
            {
                if( i.first.mp[query] != 0 ) total++;
            }

       //     cout << query << " " << total << "\n";

            for( auto i : data2 )
            {
                if( i.first.mp[query] != 0 ) answer[i.second] += log10((double)cnt / (double)total);
            }
        }

        vector<pair<double,int>> v;
        for( auto i : answer ) v.push_back(make_pair(i.second,i.first)) , answer[i.first] = 0;
        sort(v.begin(),v.end(),cmp);

     //   for(int i=0;i<2;i++) cout << v[i].second << " " << v[i].first << "\n";

        int k = stoi(argv[3]);
        for(int i=0;i<k;i++)
        {
            if( v[i].first == 0 ) cout << -1;
            else
            {
                int ouo = v[i].second;  
                cout << ouo;                
            }

            if( i != k - 1 ) cout << " ";
            else cout << "\n";
        }
    }
}
