#include <bits/stdc++.h>
#define int long long

using namespace std;

int cnt = 0;
unordered_map<string,unordered_set<int> > x;
map<pair<int,string>,int> word;
unordered_map<int,int> total;

signed main(int argc,char* argv[])
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream cin_corpus(argv[1]);
    ifstream cin_query(argv[2]);

    string s;
    while( getline(cin_corpus,s) )
    {
        int idx = 0;
        cnt++;
        for(int i=0;i<s.size();i++)
        {
            if( s[i] >= '0' && s[i] <= '9' ) idx *= 10 , idx += ( s[i] - '0' );
            else break;
        }
        
        string tmp = "";
        vector<string> v;

        for(int i=to_string(num).size();i<s.size();i++)
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
        unordered_map<int,double> ans;
        while( ss >> tmp )
        {
            for(int i=0;i<tmp.size();i++) if( tmp[i] >= 'A' && tmp[i] <= 'Z' ) tmp[i] += ( 'a' - 'A' );
            if( x.count(tmp) != 0 )
            {
                double idf = log10( (double)cnt / x[tmp].size() );

                for( auto i : x[tmp] )
                {
                    double num = (double)word[make_pair(i,tmp)] / total[i];
                    ans[i] += num * idf;
                }
            }
        }

        vector<pair<double,int>> answer;
        for( auto i : ans ) if( i.second != 0 ) answer.push_back(make_pair(i.second*-1,i.first));
        sort(ans.begin(),ans.end());
        
        int k = stoi(argv[3]);
        for(int i=0;i<answer.size();i++)
        {
            if( i == k ) break;
            cout << answer[i].second << "\n";
        }
        
        int less = k - answer.size();
        while(less--) cout << -1 << "\n";
    }

    return 0;
}
