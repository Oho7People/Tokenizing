#include "calculator.hpp"

int CalculateExpression(std::string_view input) {
  size_t pos = 0;
  const auto tokens = Tokenize(input);
  const auto expression = ParseExpression(tokens, pos);
  if (pos < tokens.size()) {
    throw WrongExpressionError("too many operands");
  }
  return expression->Calculate();
}