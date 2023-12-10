#include <fstream>
#include <iostream>
#include <string>

#include "day01.h"

namespace input
{
const std::string kRootFolder = "../adventOfCode/input/";
const std::string kFileExtension = ".txt";
} // namespace input

int main() {
  using namespace input;

  // Edit here the input file
  const std::string filename = kRootFolder + "day01/example_2" + kFileExtension;
  
  std::ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    std::cerr << "Error opening the file '" << filename << "'\n";
    return 1;
  }

  // Edit here the code to execute
  day01::run(inputFile);

  inputFile.close();
  return 0;
}
