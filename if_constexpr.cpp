#include <iostream>
#include <type_traits>

#if OLD_AND_BUSTED

template <typename T>
T get_value(T* t) { return *t; }

template <typename T>
T get_value(T t) { return t; }

#else // NEW_HOTNESS
template <typename T>
auto get_value(T t)
{
    if constexpr(std::is_pointer_v<T>)
        return *t;
    else return t;
}

#endif


struct Person {
    public:
    std::string getFirstName() const { return first_name; }
    std::string getLastName() const { return last_name; }
    int getAge() const { return age; }
    private:
    std::string first_name, last_name;
    int age;
};

#if OLD_AND_BUSTED

template <unsigned I>
auto get(Person const& p);

template <> auto get<0>(Person const& p) { return p.getFirstName(); }
template <> auto get<1>(Person const& p) { return p.getLastName(); }
template <> auto get<2>(Person const& p) { return p.getAge(); }

#else // NEW_HOTNESS

template <unsigned I>
auto get(Person const& p)
{
    if constexpr(I == 0) return p.getFirstName();
    if constexpr(I == 1) return p.getLastName();
    if constexpr(I == 2) return p.getAge();
}

#endif


template <typename T>
void print(T t)
{
    std::cout << get_value(t) << std::endl;
}

auto main(int argc, char** argv) -> int
{
    auto a = 666;
    auto *b = &a;

    print(a); // 666
    print(b); // 666

    return 0;
}

