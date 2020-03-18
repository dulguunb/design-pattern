#include <iostream>
#include <stack>
#include <boost/algorithm/string.hpp>
#include <vector>
using namespace std;

class String{
    string s;
    public:
    String(const string &cs) : s {cs}
    {
    }
    String to_lower() const {
        string ss {s};
        boost::to_lower(ss);
        return {ss}; // inference
    }
    vector<string> split(const string &delimeter=" ") const{
        vector <string> result;
        boost::split(result,s,boost::is_any_of(delimeter),boost::token_compress_on);
        return result;
    }
};

int main(){
    String s {"Hello World"};
    auto parts = s.to_lower().split();
    for(const auto& parts : parts ){
        cout << parts << endl;
    }
    return 0;
}