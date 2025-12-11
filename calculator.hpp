#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "parser.hpp"
#include "tokenize.hpp"
#include "expressions.hpp"

int CalculateExpression(std::string_view input);

#endif // CALCULATOR_HPP