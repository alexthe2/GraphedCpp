#pragma once
#include "Comparable.h"

class GraphEdge : Comparable
{
public:
	GraphEdge() = default;
	
	virtual auto calculateValue() const -> int;
	auto equals(const Comparable& copy) const -> bool override;
};

