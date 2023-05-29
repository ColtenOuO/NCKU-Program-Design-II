#include<iostream>
#include <unordered_map>
#include <map>
class str_token{
    public:
        std::unordered_map<std::string,std::int32_t> mp;
        void adding_token(const std::string s) { mp[s]++; };
        str_token(std::unordered_map<std::string,std::int32_t> init_mp); // Constructor
};

void string_token_parsing(const std::string s,str_token &data);
