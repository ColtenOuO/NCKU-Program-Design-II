#include <bits/stdc++.h>
 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long
 
using namespace std;
 
using namespace __gnu_pbds;
 
typedef tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
 
class ouo{
		public:
					int employee_id,age,gender,salary;
};
bool cmp(ouo &a,ouo &b)
{
		if( a.salary == b.salary )
				{
							if( a.age == b.age )
										{
														if( a.gender == b.gender )
																		{
																							return a.employee_id < b.employee_id;
																										}
																	
																	return ( a.gender == 'f' );
																			}
									
									return a.age < b.age;
										}
			
			return a.salary < b.salary;
}
signed main(int argv,char* argc[])
{
		ios_base::sync_with_stdio(false);
			cin.tie(0);
				
				freopen(argc[1],"r",stdin);
					
					vector<ouo> v;
						
						string s;
							while( cin >> s )
									{
												for(int i=0;i<s.size();i++) if( s[i] == ',' ) s[i] = ' ';
														stringstream ss;
																ss << s;
																		
																		ouo pb;
																				
																				for(int i=0;i<4;i++)
																							{
																											char a;
																														int b;
																																	
																																	if( i == 2 ) ss >> a;
																																				else ss >> b;
																																							
																																							if( i == 0 ) pb.employee_id = b;
																																										else if( i == 1 ) pb.age = b;
																																													else if( i == 2 ) pb.gender = a;
																																																else pb.salary = b;
																																																		}
																						
																						v.emplace_back(pb);
																							}
								
								sort(v.begin(),v.end(),cmp);
									
									for(int i=0;i<v.size();i++)
											{
														if( i != 0 && v[i].salary != v[i-1].salary ) cout << "\n" , cout << v[i].salary;
														        else if( i == 0 ) cout << v[i].salary;
																	cout << "," << v[i].employee_id;
																		}

									    cout << "\n";
									    	
									    	return 0;
}
