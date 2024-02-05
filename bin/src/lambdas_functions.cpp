#include <iostream>
#include "lib.hpp"
using namespace std;

// constant expr - at compile time, but can be used by non const too
constexpr double trippo(double x) {return x*x*x;}; 
// at compile time ONLY
consteval double trippo2(double x) {return x*x*x;};

void lambdas_functions() {
    // value of constexpr is calculated at compile time by compiler
    constexpr double max1 = 0.01*trippo(3);

    // lambda. auto - compiler can identify the type
    auto lessThen3 = [](int x) { return x < 3; };
    if (lessThen3(max1)) { cout << "x is less than three! "<< endl; }
    /*
        [список_захвата](список_параметров) { тело_функции }
        [список_захвата](список_параметров) -> тип_возвращаемого_значения{ тело_функции }

        [] // без захвата переменных из внешней области видимости
        [=] // все переменные захватываются по значению
        [&] // все переменные захватываются по ссылке
        [x, y] // захват x и y по значению
        [&x, &y] // захват x и y по ссылке
        [in, &out] // захват in по значению, а out — по ссылке
        [=, &out1, &out2] // захват всех переменных по значению,
        // кроме out1 и out2, которые захватываются по ссылке
        [&, x, &y] // захват всех переменных по ссылке, кроме x,
        // которая захватывается по значению

    */
    using FPointer = int(*) (int myint);
    FPointer ptr = square;
    int res = ptr(10);
    cout << "res: " << res << endl;
}