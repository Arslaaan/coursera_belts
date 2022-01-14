#include "node.h"

#include <utility>

DateComparisonNode::DateComparisonNode(const Comparison &comparison, const Date &date)
        : date_(date), comparison_(comparison) {};

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &operation, shared_ptr<Node> l,
                                           shared_ptr<Node> r)
        : op(operation), left(std::move(l)), right(std::move(r)) {};

EventComparisonNode::EventComparisonNode(const Comparison &comparison, string event)
        : comparison_(comparison), event_(std::move(event)) {};

bool DateComparisonNode::Evaluate(const Date &date, const string &event) const {
    switch (comparison_) {
        case Comparison::Less:
            return date < date_;
        case Comparison::LessOrEqual:
            return date < date_ || date == date_;
        case Comparison::Greater:
            return date > date_;
        case Comparison::GreaterOrEqual:
            return date > date_ || date == date_;
        case Comparison::Equal:
            return date == date_;
        case Comparison::NotEqual:
            return !(date == date_);
        default:
            throw logic_error("Unknown comparison");
    }
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) const {
    if (op == LogicalOperation::And) {
        return left->Evaluate(date, event) && right->Evaluate(date, event);
    } else {
        return left->Evaluate(date, event) || right->Evaluate(date, event);
    }
}

bool EmptyNode::Evaluate(const Date &date, const string &event) const {
    return true;
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const {
    switch (comparison_) {
        case Comparison::Less:
            return event < event_;
        case Comparison::LessOrEqual:
            return event < event_ || event == event_;
        case Comparison::Greater:
            return event > event_;
        case Comparison::GreaterOrEqual:
            return event > event_ || event == event_;
        case Comparison::Equal:
            return event == event_;
        case Comparison::NotEqual:
            return !(event == event_);
        default:
            throw logic_error("Unknown comparison");
    }
}