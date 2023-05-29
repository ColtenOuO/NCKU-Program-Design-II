#include<iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
class str_token{
    public:
        std::unordered_map<std::string,std::set<int>> mp;
        void adding_token(const std::string s,const std::int32_t id) { mp[s].insert(id); };
        str_token(std::unordered_map<std::string,std::set<std::int32_t> > init_mp); // Constructor
};

void string_token_parsing(const std::string s,str_token &data,std::int32_t id);
