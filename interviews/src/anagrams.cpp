#include <iostream>
#include <unordered_map>

bool areAnagrams(const std::string& str1, const std::string& str2) {
    // If lengths of strings are different, they cannot be anagrams
    if (str1.length() != str2.length()) {
        return false;
    }

    // Count occurrences of characters in str1
    // in C++ unordered_map operator[] if not found returns default
    std::unordered_map<char, int> charCount;
    for (char c : str1) {
        charCount[c]++;
    }

    // Decrement occurrences of characters in str2
    for (char c : str2) {
        // NOT FOUND?
        if (charCount.find(c) == charCount.end()) {
            // Character not found in str1, not an anagram
            return false;
        }
        charCount[c]--;
        if (charCount[c] < 0) {
            // More occurrences of character in str2 than in str1, not an anagram
            return false;
        }
    }

    // Check if all characters in str1 are consumed in str2
    for (const auto& pair : charCount) {
        if (pair.second != 0) {
            // Character count not zero, not an anagram
            return false;
        }
    }

    // All checks passed, str1 and str2 are anagrams
    return true;
}

void anagrams_playground() {
    std::string str1 = "listen";
    std::string str2 = "silent";
    if (areAnagrams(str1, str2)) {
        std::cout << "\"" << str1 << "\" and \"" << str2 << "\" are anagrams." << std::endl;
    } else {
        std::cout << "\"" << str1 << "\" and \"" << str2 << "\" are not anagrams." << std::endl;
    };
}