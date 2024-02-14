// union with enum is basically like an enum holding a value
#include <variant>
#include <iostream>
#include <cstdint>

enum class Type { ptr, num };
// p and i are placed into the same memory location
union Value {
    float* p;
    int i;
};
// Error prone, but it might be much faster!
// https://www.reddit.com/r/cpp/comments/kst2pu/with_stdvariant_you_choose_either_performance_or/
struct BadEntry {
    Type t; // called tag
    Value v; // use v.p if t==Type::ptr; use v.i if t==Type::num
};

void f(BadEntry* pe)
{
    if (pe->t == Type::num)
        std::cout << pe->v.i;
// ...
}

// BETTER TO USE VARIANT:
struct GoodEntry {
    std::variant<float*,int> v;
};

void f(GoodEntry* pe) {
    if (std::holds_alternative<int>(pe->v)){
        std::cout << std::get<int>(pe ->v) << std::endl;
    }
}

struct Quit {};
struct Move { int32_t x; int32_t y; };
struct Write { std::string s; };
struct ChangeColor { int32_t r; int32_t g; int32_t b; };
using Message = std::variant<Quit, Move, Write, ChangeColor>;

void f2(Message* pm) {
    // remember to deref
    // https://stackoverflow.com/questions/77989243/c-stdholds-alternative-with-custom-type-class/77989282
    if (std::holds_alternative<Move>(*pm)){
        std::cout << "Move's y: "<< std::get<Move>(*pm).y << std::endl;
    }
}

void union_playground() {
    GoodEntry e = GoodEntry {1};
    GoodEntry* pe = &e;
    f(pe);
    GoodEntry& x = *pe; // no copy

    

    auto q = Move{1,2};
    int* y = &q.x; // y is an address
    Message m = q;
    Message* pm = &m;
    f2(pm);

    Move* yy = &q;

    // int* z = yy->y; error! hence we cannot create int* using ->
    Move& ww = *yy; // no copy, see above
    int* z = &ww.y;

    std::cout << "Z: " << *z << std::endl; // deref here
}

