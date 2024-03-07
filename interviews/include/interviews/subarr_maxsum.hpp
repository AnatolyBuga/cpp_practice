#include <iostream>
#include <vector>
#include <algorithm>

// int*& start_ptr, int*& end_ptr
std::vector<int> maxSubarr(const std::vector<int>& nums) {
    int max_sum = nums[0];
    int current_sum = nums[0]; // either prev element or sum of last X elems(as long as current sum is > 0)
    int start_index = 0, end_index = 0, temp_start_index = 0;

    for (int i = 1; i < nums.size(); ++i) {
        // This case only kicks in when CURR_SUM IS NEGATIVE
        // BECAUSE if the negative curr_sum is < max_sum then we  return curr_sum
        // say 100 < 99 + 100
        // -200 < 199 - 200
        // 2 > -1 + 2
        if (nums[i] > current_sum + nums[i]) {  // -1 
            // 2
            current_sum = nums[i]; // -100
            // 3
            temp_start_index = i; // 1
        } else {
            // 199
            // -1
            current_sum += nums[i]; 
        }

        // if 199 > 99
        // if 198 > 199 NO | -1 > 199 NO
        // if 2 > 199 NO
        if (current_sum > max_sum) { // -100 > -1 NO; 
            

            // 199 
            // 
            max_sum = current_sum; // 
            // 0
            // 
            start_index = temp_start_index; // 2
            // 1
            // 
            end_index = i; // 2
        }
    }

    // start_ptr = &nums[start_index];
    // end_ptr = &nums[end_index];

    std::vector<int> subarray(nums.begin() + start_index, nums.begin() + end_index + 1);
    return subarray;
}

void run_subarrmaxsum() {
    std::vector<int> nums = {-1, -100, -103};
    // int* start_ptr;
    // int* end_ptr;
    std::vector<int> res = maxSubarr(nums);

    for (const int i: res) {
        std::cout<< i << " ";
    } 

}