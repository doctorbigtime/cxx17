#include <string>

struct Thing { Thing(int i) : i(i) {} int i; };

Thing make_thing(int i) { return Thing{i}; }

extern void other_fun(Thing&);

void foo(int i) {
    auto my_thing = make_thing(i);
    other_fun(my_thing);
}

