#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) {
  long minutes = seconds / 60;
  long hour = minutes / 60;
  long second = int(seconds % 60);
  long minute = int(minutes % 60);

  std::string str =
      std::string(std::to_string(hour) + ":" + std::to_string(minute) + ":" +
                  std::to_string(second));

  return str;
}