#include "StringGenerator.h"
#include <algorithm>

StringGenerator::StringGenerator() {
    std::random_device rd;
    gen = std::mt19937(rd());
}

std::string StringGenerator::generateRandomString(int minLength, int maxLength) {
    std::uniform_int_distribution<> lengthDist(minLength, maxLength);
    int length = lengthDist(gen);
    std::uniform_int_distribution<> charDist(0, allowedChars.size() - 1); // NOLINT
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += allowedChars[charDist(gen)];
    }
    return result;
}

std::vector<std::string> StringGenerator::generateUnsortedStrings(int numStrings) {
    std::vector<std::string> strings;
    for (int i = 0; i < numStrings; ++i) {
        strings.push_back(generateRandomString(10, 200));
    }
    return strings;
}

std::vector<std::string> StringGenerator::generateSortedStrings(int numStrings) {
    auto strings = generateUnsortedStrings(numStrings);
    std::sort(strings.begin(), strings.end(), std::greater<std::string>()); // NOLINT
    return strings;
}

std::vector<std::string> StringGenerator::generateAlmostSortedStrings(int numStrings) {
    std::vector<std::string> strings = generateSortedStrings(numStrings);
    auto swapCnt = (size_t) (numStrings * 0.1);
    std::uniform_int_distribution<size_t> index_dist(0, numStrings - 1);
    for (size_t i = 0; i < swapCnt; ++i) {
        std::swap(strings[index_dist(gen)], strings[index_dist(gen)]);
    }
    return strings;
}
