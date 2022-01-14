#pragma once

#include <memory>

#include "date.h"
#include "token.h"

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
    Date date_;
    Comparison comparison_;
public:
    DateComparisonNode(const Comparison& comparison, const Date& date);
    bool Evaluate(const Date& date, const string& event) const override;
};

class EventComparisonNode : public Node {
    string event_;
    Comparison comparison_;
public:
    EventComparisonNode(const Comparison& comparison, string  event);
    bool Evaluate(const Date& date, const string& event) const override;
};

class LogicalOperationNode : public Node {
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    LogicalOperation op;
public:
    LogicalOperationNode(const LogicalOperation& operation, shared_ptr<Node> left, shared_ptr<Node> right);
    bool Evaluate(const Date& date, const string& event) const override;
};