#include<map>
#include <unordered_map>
#include "parser.h"


void string_token_parsing(std::string s,str_token &data2)
{
    std::string tmp = "";
    for(int i=0;i<s.size();i++)
    {
        if( s[i] >= 'A' && s[i] <= 'Z' ) s[i] += ( 'a' - 'A' );
        else if( s[i] == ' ' ) if( tmp != "" ) data2.adding_token(tmp) , tmp = "";
        
        if( s[i] >= 'a' && s[i] <= 'z' ) tmp += s[i];
    }

    if( tmp != "" ) data2.adding_token(tmp);

    return;
}
str_token::str_token(std::unordered_map<std::string,std::int32_t> init_mp) : mp(init_mp) { } // Constructor