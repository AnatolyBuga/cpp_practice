#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <chrono>
using namespace std;

// Parses eg "1Y3M" into (1, 3)
std::pair<int, int> extractNumbers(const std::string& input) {
    // Alternatively, could also work with stream
    int beforeY = 0;
    int beforeM = 0;
    
    size_t indexY = input.find('Y');
    size_t indexM = input.find('M');

    if (indexY != std::string::npos) {
        beforeY = std::stoi(input.substr(0, indexY));
    }

    if (indexM != std::string::npos) {
        beforeM = std::stoi(input.substr(indexY + 1, indexM - indexY - 1));
    }

    return std::make_pair(beforeY, beforeM);
}


// Parses label into date
// Takes care of parsing error
std::tm parseDateString(const std::string& dateString) {
    std::tm timeInfo = {};
    std::istringstream ss(dateString);

    // Parse the month and year from the string
    ss >> std::get_time(&timeInfo, "%b%Y");
    if (ss.fail()) {
        // If the first attempt fails, retry with a different format for the year
        ss.clear();
        ss.seekg(0);
        ss >> std::get_time(&timeInfo, "%b%y");
    }

    if (ss.fail()) {
        throw std::invalid_argument("Invalid date string format, expected %b%Y or %b%y");
    }

    return timeInfo;
}

int calculateMonthsDifference(std::tm date_next, std::tm date_prev) {
    auto time1 = std::chrono::system_clock::from_time_t(std::mktime(&date_next));
    auto time2 = std::chrono::system_clock::from_time_t(std::mktime(&date_prev));

    auto duration = std::chrono::duration_cast<std::chrono::months>(time1 - time2);
    
    return duration.count();
}

// Assuming Months are the lowest level of granularity
// this function returns number of months between the valuation date and label
// TODO this function assumes today() to compare eg Mar2025 vs 15M. as of 1/1/22 15M<Mar2025,
// but as of Feb 2024 => 15M>Mar2025
int label_to_months(string label) {
    if (label.back() == 'M') {
        std::pair<int, int> years_months = extractNumbers(label);
        return years_months.first*12 + years_months.second;
    }
    else
    {
        const std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const std::tm currentDate = *std::localtime(&now);
        auto dt = parseDateString(label); 
        return calculateMonthsDifference(dt, currentDate);
    }
}

struct Tenor {
    public:
        string _label;

        Tenor(string label = "3M")
        {
            _label = label;
        }

        // must satisfy strict weak ordering
        // https://stackoverflow.com/questions/979759/how-to-define-operator-on-an-n-tuple-that-satisfies-a-strict-weak-ordering
        bool operator<(Tenor const& obj) const
        {    
            auto m_self = label_to_months(_label);    
            auto m_obj =   label_to_months(obj._label);  
            return m_self < m_obj;
        }
};

void tenor_operator_ordered() {
    auto t1 = Tenor {"1M"};
    auto t2 = Tenor {"2M"};
    auto t3 = Tenor {"1Y6M"};
    auto t4 = Tenor {"Mar2025"};
    auto t5 = Tenor {"Jan2026"};

    //populate the map
    map<Tenor, int> mp;
    mp[t4] = 12;
    mp[t5] = 22;
    mp[t1] = 1; 
    mp[t3] = 18; 
    mp[t2] = 2;

    // Printing Test objects in sorted order 
    for (auto x : mp) 
        cout << x.first._label << " " << x.second << endl; 

}