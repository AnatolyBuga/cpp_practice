// warm up
#include <vector>
#include <iostream>
#include <algorithm>

float max_profit(const std::vector<float>& prices ) {
    float max_profit = 0;
    float min_so_far = prices[0];

    for (int i = 1; i<prices.size(); ++i){
    //for (auto p: prices) {
        float p = prices[i];
        if (p<min_so_far) {
            min_so_far = p ;
        } else {
            max_profit = std::max(max_profit, p - min_so_far );
        }
    }
    return max_profit;
}

void run_max_profit(){
    std::vector<float> nums = {-1, -2, 3, 1, 10};
    std::cout << max_profit(nums) << std::endl;
}