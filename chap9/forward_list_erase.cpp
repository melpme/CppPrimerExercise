#include <iostream>
#include <forward_list>

int main()
{
    std::forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    auto pre = flst.before_begin();
    auto curr = flst.begin();
    while (curr != flst.end()) {
        if (*curr % 2) {
            curr = flst.erase_after(pre);
        } else {
            pre = curr;
            curr++;
        }
    }
}