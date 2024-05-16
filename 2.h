#ifndef STANDARD_SORTER_H
#define STANDARD_SORTER_H

#include <vector>
#include <string>

class AdvancedSorting {
public:
    int charComparisons = 0;
    int performQuickSort(std::vector<std::string>& data);
    int performMergeSort(std::vector<std::string>& data);

private:
    void executeQuickSort(std::vector<std::string>& data, int low, int high);
    void executeMergeSort(std::vector<std::string>& data, size_t start, size_t end);
    void combine(std::vector<std::string>& data, size_t start, size_t end, size_t middle);
    int determinePivot(std::vector<std::string>& data, int low, int high);
    int compare(const std::string& a, const std::string& b);
};

#endif // STANDARD_SORTER_H
