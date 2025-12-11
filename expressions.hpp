#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <memory>

class IExpression {
 public:
  virtual int Calculate() const = 0;
  virtual ~IExpression() = default;
};

class Constant : public IExpression {
  int value_;

 public:
  explicit Constant(int value) : value_(value) {
  }

  int Calculate() const override {
    return value_;
  }
};

class IUnaryOperation : public IExpression {
  std::unique_ptr<IExpression> operand_;

 public:
  explicit IUnaryOperation(std::unique_ptr<IExpression> operand) : operand_(std::move(operand)) {
  }

  int Calculate() const override {
    return Operation(operand_->Calculate());
  }

  virtual int Operation(int operand) const = 0;
};

class IBinaryOperation : public IExpression {
  std::unique_ptr<IExpression> left_;
  std::unique_ptr<IExpression> right_;

 public:
  IBinaryOperation(std::unique_ptr<IExpression> left, std::unique_ptr<IExpression> right)
      : left_(std::move(left)), right_(std::move(right)) {
  }

  int Calculate() const override {
    return Operation(left_->Calculate(), right_->Calculate());
  }

  virtual int Operation(int left, int right) const = 0;
};

class Sum : public IBinaryOperation {
 public:
  int Operation(int left, int right) const override {
    return left + right;
  }

  using IBinaryOperation::IBinaryOperation;
};

class Subtract : public IBinaryOperation {
 public:
  int Operation(int left, int right) const override {
    return left - right;
  }

  using IBinaryOperation::IBinaryOperation;
};

class AbsoluteValue : public IUnaryOperation {
 public:
  int Operation(int operand) const override {
    return operand < 0 ? -operand : operand;
  }
  using IUnaryOperation::IUnaryOperation;
};

class Minus : public IUnaryOperation {
 public:
  int Operation(int operand) const override {
    return -operand;
  }
  using IUnaryOperation::IUnaryOperation;
};

class Plus : public IUnaryOperation {
 public:
  int Operation(int operand) const override {
    return operand;
  }
  using IUnaryOperation::IUnaryOperation;
};

class Multiply : public IBinaryOperation {
 public:
  int Operation(int left, int right) const override {
    return left * right;
  }
  using IBinaryOperation::IBinaryOperation;
};

class Divide : public IBinaryOperation {
 public:
  int Operation(int left, int right) const override {
    return left / right;
  }
  using IBinaryOperation::IBinaryOperation;
};

class Residual : public IBinaryOperation {
 public:
  int Operation(int left, int right) const override {
    return left % right;
  }
  using IBinaryOperation::IBinaryOperation;
};

class Square : public IUnaryOperation {
 public:
  int Operation(int operand) const override {
    return operand * operand;
  }
  using IUnaryOperation::IUnaryOperation;
};

class Maximum : public IBinaryOperation {
 public:
  int Operation(int left, int right) const override {
    return left > right ? left : right;
  }
  using IBinaryOperation::IBinaryOperation;
};

class Minimum : public IBinaryOperation {
 public:
  int Operation(int left, int right) const override {
    return left < right ? left : right;
  }
  using IBinaryOperation::IBinaryOperation;
};

#endif  // EXPRESSIONS_HPP