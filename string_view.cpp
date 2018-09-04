#include <vector>
#include <string>
#include <string_view>
#include <cassert>

#if OLD_AND_BUSTED

std::vector<std::string> split(std::string const& v)
{
    std::vector<std::string> ret;
    std::string tmp = v;
    auto pos = tmp.find(" ");
    while(pos != std::string::npos)
    {
        ret.push_back(tmp.substr(0, pos));
        tmp = tmp.substr(pos+1);
        pos = tmp.find(" ");
    }
    return ret;
}

#else

std::vector<std::string_view> split(std::string const& v)
{
    std::vector<std::string_view> ret;
    size_t pos, off = 0;
    do
    {
        pos = v.find(" ", off);
        if(pos == std::string::npos) {
            ret.emplace_back(v.c_str()+off, v.size()-off);
        }
        else {
            ret.emplace_back(v.c_str()+off, pos-off);
        }
        off = pos+1;
    } while(pos != std::string::npos);
    return ret;
}

#endif

auto main(int argc, char** argv) -> int
{
    std::string x = "foo bar baz qux";
    auto v = split(x);
    assert(v.size() == 4);
    return 0;
}
