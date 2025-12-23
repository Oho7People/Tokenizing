#ifndef TOKENIZE_CPP
#define TOKENIZE_CPP

#include "tokenize.hpp"
#include <unordered_set>
#include <unordered_map>
#include <cctype>


static const std::unordered_map<char, Token> kSpecialSymbols{
    {'+', PlusToken{}},     {'-', MinusToken{}},          {'*', MultiplyToken{}},      {'/', DivideToken{}},
    {'%', ResidualToken{}}, {'(', OpeningBracketToken{}}, {')', ClosingBracketToken{}}};

static const std::unordered_map<std::string_view, Token> kSpecialNames{
    {"sqr", SqrToken{}}, {"max", MaxToken{}}, {"min", MinToken{}}, {"abs", AbsToken{}}};

static bool IsAlpha(char symbol) {
  return std::isalpha(static_cast<unsigned char>(symbol));
}

static bool IsSpace(char symbol) {
  return std::isspace(static_cast<unsigned char>(symbol));
}

static bool IsDigit(char symbol) {
  return std::isdigit(static_cast<unsigned char>(symbol));
}

template <class Predicate>
std::string_view GetConsecutive(std::string_view str, size_t pos, Predicate pred) {
  auto begin = str.begin() + pos;
  auto end = std::ranges::find_if_not(begin, str.end(), pred);
  return str.substr(pos, end - begin);
}

int ToNumber(std::string_view str) {
  return std::stoi(static_cast<std::string>(str));
}

std::vector<Token> Tokenize(std::string_view input) {
  std::vector<Token> tokens;
  size_t pos = 0;
  while (pos < input.size()) {
    if (IsSpace(input[pos])) {
      ++pos;
    } else if (IsDigit(input[pos])) {
      const auto word = GetConsecutive(input, pos, IsDigit);
      tokens.emplace_back(NumberToken{ToNumber(word)});
      pos += word.size();
    } else if (IsAlpha(input[pos])) {
      const auto word = GetConsecutive(input, pos, IsAlpha);
      if (kSpecialNames.contains(word)) {
        tokens.push_back(kSpecialNames.at(word));
      } else {
        tokens.emplace_back(UnknownToken{std::string(word)});
      }
      pos += word.size();
    } else if (kSpecialSymbols.contains(input[pos])) {
      tokens.push_back(kSpecialSymbols.at(input[pos]));
      ++pos;
    } else {
      tokens.emplace_back(UnknownToken{std::string(1, input[pos])});
      ++pos;
    }
  }
  return tokens;
}

#endif