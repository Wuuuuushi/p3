#ifndef ___PROJECT_3_CONVERT_HPP
#define ___PROJECT_3_CONVERT_HPP

#include <istream>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include "Wordset.hpp"
#include <set>

namespace shindler::ics46::project3 {

bool isValidLetter(std::string str, std::string start);

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
[[nodiscard]] std::vector<std::string> convert(const std::string& start,
                                               const std::string& end,
                                               const BaseWordSet<H1, H2, EvictThreshold>& words) {
    // TODO: Implement this. The stub is only to allow the code to remove
    //       (you can remove it).
    std::vector<std::string> path{};
    std::unordered_map<std::string, std::string> seenStrings{};
    std::queue<std::string> queueOfWords{};

    queueOfWords.push(start);
    while(!queueOfWords.empty())
    {
        for (size_t i{0}; i < words.capacity(); i++)
        {
            if (words.HashTable1[i] != "")
            {
                if (words.HashTable1[i].length() == start.length())
                {
                    if (isValidLetter(words.HashTable1[i], queueOfWords.front()))
                    {
                        if (!seenStrings.contains(words.HashTable1[i]))
                        {
                            seenStrings[words.HashTable1[i]] = queueOfWords.front();
                            queueOfWords.push(words.HashTable1[i]);
                        }
                    }
                }
            }
            if (words.HashTable2[i] != "")
            {
                if (words.HashTable2[i].length() == start.length())
                {
                    if (isValidLetter(words.HashTable2[i], queueOfWords.front()))
                    {
                        if (!seenStrings.contains(words.HashTable2[i]))
                        {
                            seenStrings[words.HashTable2[i]] = queueOfWords.front();
                            queueOfWords.push(words.HashTable2[i]);
                        }
                    }
                }
            }
        }
        if (seenStrings.contains(end))
        {
            break;
        }
        queueOfWords.pop();
    }
    if (!seenStrings.contains(end))
    {
        return path;
    }
    std::string currentPath{end};
    path.push_back(currentPath);
    while (seenStrings[currentPath] != start)
    {
        currentPath = seenStrings[currentPath];
        path.push_back(currentPath);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

// You should not need to change this function
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void loadWordsIntoTable(std::istream& istream,
                        BaseWordSet<H1, H2, EvictThreshold>& words) {
    std::string word;

    while (istream >> word) {
        words.insert(word);
    }
}

}  // namespace shindler::ics46::project3

#endif
