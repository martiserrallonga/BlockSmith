#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace day01
{
// clang-format off
const std::map<int, std::string_view> stringNumbers {
  { 1, "one" },
  { 2, "two" },
  { 3, "three" },
  { 4, "four" },
  { 5, "five" },
  { 6, "six" },
  { 7, "seven" },
  { 8, "eight" },
  { 9, "nine" },
};
// clang-format on

using FIter = std::string_view::const_iterator;
using RIter = std::string_view::const_reverse_iterator;
using Iter = std::variant<FIter, RIter>;

//using StrIter = std::string_view::const_iterator;

template<typename Iter>
bool isStringNumber(Iter targetFirst, Iter targetLast, Iter wordFirst, Iter wordLast) {
  while (targetFirst != targetLast) {
    if (wordFirst == wordLast) return false;
    if (*targetFirst != *wordFirst) return false;
    ++targetFirst;
    ++wordFirst;
  }
  return true;
}

template<typename Iter>
std::optional<int> checkAllNumbers(Iter wordFirst, Iter wordLast) {
  if (*wordFirst >= '1' && *wordFirst <= '9') return *wordFirst - '0';
  for (const auto& [value, name]: stringNumbers) {

    bool forward = std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>();
    auto begin = forward ? name.cbegin() : name.crbegin();
    auto end = forward ? name.cend() : name.crend();

    if (isStringNumber(begin, end, wordFirst, wordLast)) {
      return value;
      break;
    }
  }
  return std::nullopt;
}

template<typename Iter>
std::optional<int> findNumber(Iter lineBegin, Iter lineEnd) {
  for (auto it = lineBegin; it != lineEnd; ++it) {
    auto query = checkAllNumbers(it, lineEnd);
    if (query.has_value()) {
      std::cout << query.value() << std::endl;
      return query.value();
    }
  }

  return std::nullopt;
}

int lineStrNumber(std::string_view line) {
  auto first = findNumber(line.cbegin(), line.cend());
  //auto last = findNumber(line.crbegin(), line.crend(), false);
  auto last = first;

  if (!first.has_value() || !last.has_value()) {
    std::cerr << "Error: Number not found:\n\t" << line << std::endl;
    return 0;
  } else {
    return 10 * first.value() + last.value();
  }
}

int lineNumber(std::string_view line) {
  auto isNumber = [](const char& c) {
    return c >= '0' && c <= '9';
  };

  auto first = std::ranges::find_if(line.cbegin(), line.cend(), isNumber);
  auto last = std::ranges::find_if(line.crbegin(), line.crend(), isNumber);

  std::string strNumber;
  if (first <= line.cend()) strNumber += *first;
  if (last <= line.crend()) strNumber += *last;

  return atoi(strNumber.c_str());
}

void run(std::ifstream& inputFile) {
  int result = 0;

  std::string line;
  while (std::getline(inputFile, line)) {
    result += lineStrNumber(line);
  }

  std::cout << result << std::endl;
}

} // namespace day01