#include "parser.hpp"

std::unique_ptr<IExpression> ParseFactor(const std::vector<Token>& tokens, size_t& pos) {
  if (pos >= tokens.size()) {
    throw WrongExpressionError("not enough tokens");
  }
  const auto& token = tokens[pos];
  ++pos;
  if (std::holds_alternative<NumberToken>(token)) {
    return std::make_unique<Constant>(std::get<NumberToken>(token).value);
  }
  if (std::holds_alternative<PlusToken>(token)) {
    auto arg = ParseFactor(tokens, pos);
    return std::make_unique<Plus>(std::move(arg));
  }
  if (std::holds_alternative<MinusToken>(token)) {
    auto arg = ParseFactor(tokens, pos);
    return std::make_unique<Minus>(std::move(arg));
  }
  if (std::holds_alternative<OpeningBracketToken>(token)) {
    auto sub_expression = ParseExpression(tokens, pos);
    if (pos >= tokens.size() || !std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
      throw WrongExpressionError("no matching ) for (");
    }
    ++pos;
    return sub_expression;
  }

  if (std::holds_alternative<AbsToken>(token)) {
    auto op = ParseFactor(tokens, pos);
    return std::make_unique<AbsoluteValue>(std::move(op));
  }
  if (std::holds_alternative<SqrToken>(token)) {
    auto op = ParseFactor(tokens, pos);
    return std::make_unique<Square>(std::move(op));
  }
  if (std::holds_alternative<MaxToken>(token)) {
    auto op_left = ParseFactor(tokens, pos);
    auto op_right = ParseFactor(tokens, pos);
    return std::make_unique<Maximum>(std::move(op_left), std::move(op_right));
  }
  if (std::holds_alternative<MinToken>(token)) {
    auto op_left = ParseFactor(tokens, pos);
    auto op_right = ParseFactor(tokens, pos);
    return std::make_unique<Minimum>(std::move(op_left), std::move(op_right));
  }
  if (std::holds_alternative<UnknownToken>(token)) {
    throw UnknownSymbolError(std::get<UnknownToken>(token).value);
  }
  throw WrongExpressionError("unexpected expression");
}

std::unique_ptr<IExpression> ParseTerm(const std::vector<Token>& tokens, size_t& pos) {
  auto expression = ParseFactor(tokens, pos);
  while (pos < tokens.size()) {
    const auto& token = tokens[pos];
    if (std::holds_alternative<MultiplyToken>(token)) {
      ++pos;
      auto multiplied = ParseFactor(tokens, pos);
      expression = std::make_unique<Multiply>(std::move(expression), std::move(multiplied));
    } else if (std::holds_alternative<DivideToken>(token)) {
      ++pos;
      auto divided = ParseFactor(tokens, pos);
      expression = std::make_unique<Divide>(std::move(expression), std::move(divided));
    } else if (std::holds_alternative<ResidualToken>(token)) {
      ++pos;
      auto residualed = ParseFactor(tokens, pos);
      expression = std::make_unique<Residual>(std::move(expression), std::move(residualed));
    } else {
      break;
    }
  }
  return expression;
}

std::unique_ptr<IExpression> ParseExpression(const std::vector<Token>& tokens, size_t& pos) {
  auto expression = ParseTerm(tokens, pos);
  while (pos < tokens.size()) {
    const auto& token = tokens[pos];
    if (std::holds_alternative<PlusToken>(token)) {
      ++pos;
      auto addendum = ParseTerm(tokens, pos);
      expression = std::make_unique<Sum>(std::move(expression), std::move(addendum));
    } else if (std::holds_alternative<MinusToken>(token)) {
      ++pos;
      auto deductible = ParseTerm(tokens, pos);
      expression = std::make_unique<Subtract>(std::move(expression), std::move(deductible));
    } else if (std::holds_alternative<UnknownToken>(token)) {
      throw UnknownSymbolError(std::get<UnknownToken>(token).value);
    } else {
      break;
    }
  }
  return expression;
}
