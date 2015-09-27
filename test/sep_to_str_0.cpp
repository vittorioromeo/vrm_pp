#include "./utils/test_utils.hpp"
#include <string>
#include <vrm/pp/sep_to_str.hpp>

int main()
{
    std::string s(VRM_PP_SEP_TOSTR(", ", 1, 2, 3));
    TEST_ASSERT(s == "1, 2, 3");
 
    return 0;
}