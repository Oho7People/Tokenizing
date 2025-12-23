#ifndef TOKENIZE_HPP
#define TOKENIZE_HPP

#include <vector>
#include <string_view>
#include <string>
#include <any>
#include <cstddef>
#include <variant>

struct PlusToken {};

struct MinusToken {};

struct MultiplyToken {};

struct DivideToken {};

struct ResidualToken {};

struct OpeningBracketToken {};

struct ClosingBracketToken {};

struct SqrToken {};

struct MaxToken {};

struct MinToken {};

struct AbsToken {};

struct NumberToken {
  int value;
};

struct UnknownToken {
  std::string value;
};

inline bool operator==(PlusToken, PlusToken) {
  return true;
}

inline bool operator==(NumberToken lhs, NumberToken rhs) {
  return lhs.value == rhs.value;
}
inline bool operator==(AbsToken, AbsToken) {
  return true;
}
inline bool operator==(MinToken, MinToken) {
  return true;
}
inline bool operator==(MaxToken, MaxToken) {
  return true;
}
inline bool operator==(SqrToken, SqrToken) {
  return true;
}
inline bool operator==(ClosingBracketToken, ClosingBracketToken) {
  return true;
}
inline bool operator==(OpeningBracketToken, OpeningBracketToken) {
  return true;
}
inline bool operator==(ResidualToken, ResidualToken) {
  return true;
}
inline bool operator==(DivideToken, DivideToken) {
  return true;
}
inline bool operator==(MinusToken, MinusToken) {
  return true;
}
inline bool operator==(MultiplyToken, MultiplyToken) {
  return true;
}
inline bool operator==(UnknownToken lhs, UnknownToken rhs) {
  return lhs.value == rhs.value;
}

using Token = std::variant<PlusToken, MinusToken, MultiplyToken, DivideToken, ResidualToken, OpeningBracketToken,
                            ClosingBracketToken, SqrToken, MaxToken, MinToken, AbsToken, NumberToken, UnknownToken>;

std::vector<Token> Tokenize(std::string_view input);

int ToNumber(std::string_view str);

#endif