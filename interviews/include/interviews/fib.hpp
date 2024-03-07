#include <iostream>
#include <vector>

void anagrams_playground();
void new_playground();

int fib_n(const int n) {
    if (n<=1) return n;

    int fib_n_minus_2 = 0;
    int fib_n_minus_1 = 1;
    int fib_n = 0;
    
    for(int i = 2; i < n; ++i) {
        fib_n = fib_n_minus_1 + fib_n_minus_2;
        fib_n_minus_2 = fib_n_minus_1;
        fib_n_minus_1 = fib_n;
    };

    return fib_n;

}

std::vector<int> fib_seq(int n) {
    std::vector<int> res;
    if (n>=1) res.push_back(0);
    if(n>=2) res.push_back(1);

    for (int i = 2; i<n; ++i) {
        int fib_n = res[res.size() - 1] + res[res.size() - 2];
        res.push_back(fib_n);
    };
    return res;
}

void run_fin() {
    int n = 10;
    int res = fib_n(n);
    std::cout << "Fibanace " << n << " : " << res << std::endl;

    std::vector<int> fibo = fib_seq(n);
    for (auto f: fibo) {
        std::cout << f << " ";
    };
}