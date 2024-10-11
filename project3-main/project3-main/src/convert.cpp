#include "convert.hpp"

#include <vector>

#include "Wordset.hpp"

namespace shindler::ics46::project3 {
  bool isValidLetter(std::string str, std::string start)
  {
    size_t dif{0};
    for(size_t i{0}; i < str.length(); i++)
    {
      if (str[i] != start[i])
      {
        dif++;
      }
    }
    if (dif != 1)
    {
      return false;
    }
    return true;
  }

  
}  // namespace shindler::ics46::project3
