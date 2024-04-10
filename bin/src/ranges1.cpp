// input_range, forward_range, bidirectional_range, random_access_range, and contiguous_range
// take_view, take_while_view
#include <ranges>
#include <iostream>
#include <vector>

// view doesn't own element
//range owns elements

void views(std::ranges::forward_range auto& r)
{
    std::ranges::filter_view v {r, [](int x) { return x%2; } }; // view (only) odd numbers from r
    std::cout << "odd numbers: "; 
    for (int x : v)
        std::cout << x << ' ';
    std::cout << std::endl;

    std::cout << "last three odd numbers: "; 
    std::ranges::reverse_view rv {v};
    for (int x: std::ranges::take_view{rv,3}) std::cout<<x<<' ';
    std::cout << std::endl;

    auto tripple = [](const auto& pair) {return std::get<0>(pair)%3;}; // index is not multiple of 4
    auto deenum = [](const auto& p) {return std::get<1>(p);};
    std::cout << "Index is not a multiple of 3, drop first one -> "; 
    auto filtered = v
        |std::views::enumerate
        |std::ranges::views::filter(tripple)
        |std::ranges::views::drop(1)
        |std::ranges::views::take(8)
        ;
    for (const auto& [index, value] : filtered) {
        std::cout << "Index: " << index << ", Value: " << value << "  ;";
    };
    std::cout << std::endl;
    std::cout << "Reversed, deenumed : "  << std::endl;
    for (int x: filtered|std::views::reverse|std::views::transform(deenum)) {
        std::cout << "Value: " << x << std::endl;
    }
}

struct Person {
    std::string name;
    int age;
    double height;
};

// auto average_temp(std::vector<Person> ppl) -> float {
    
//     if (ppl.size()==0) throw ;
//     double s = 0;
//     for (int x: std::ranges::views::elements<1>(ppl)) s+=x;

//     return s/ppl.size();
// }

auto ranges_playground() {
    std::vector<Person> people = {
        {"Alice", 30, 165.5},
        {"Bob", 25, 180.2},
        {"Charlie", 40, 170.0}
    };

    // Calculate the average age using views
    // double averageAge = std::ranges::views::transform(people, [](const Person& p) { return p.age; })
    //                     | std::views::transform_reduce([](int a, int b) { return a + b; }) 
    //                     / static_cast<double>(people.size());


    // Calculate the average age using views
    // Generate a range of numbers from 10 to 20 using std::views::iota
    auto range = std::views::iota(10, 34); // Note: 21 is exclusive, so the range is [10, 20]

    // Filter the range to keep only multiples of 3
    auto multiplesOf3 = range | std::views::filter([](int x) { return x % 3 == 0; });
    // Convert the range into a vector
    std::vector<int> multiplesVector(std::begin(multiplesOf3), std::end(multiplesOf3));

    views(range);

}