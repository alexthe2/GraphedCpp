#include "GraphEdge.h"

auto GraphEdge::equals(Comparable* copy) const -> bool {
    return calculateValue() == (dynamic_cast<GraphEdge*>(copy))->calculateValue();
}

NumericEdge::NumericEdge(const int value) {
    this->value_ = value;
}

auto NumericEdge::calculateValue() const -> int {
    return value_;
}
