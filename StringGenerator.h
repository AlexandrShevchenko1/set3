#ifndef STRING_GENERATOR_H
#define STRING_GENERATOR_H

#include <vector>
#include <string>
#include <random>
class CompareCounter {
public:
    long long count = 0;

    bool operator()(const std::string& a, const std::string& b) {
        ++count;
        return a < b;
    }
};

class StringGenerator {
public:
    StringGenerator();
    std::vector<std::string> generateUnsortedStrings(int numStrings);
    std::vector<std::string> generateSortedStrings(int numStrings);
    std::vector<std::string> generateAlmostSortedStrings(int numStrings);

private:
    std::string generateRandomString(int minLength, int maxLength);
    std::string allowedChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";
    std::mt19937 gen;
};

#endif // STRING_GENERATOR_H
