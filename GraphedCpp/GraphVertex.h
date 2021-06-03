#pragma once
class GraphVertex : Comparable {

public:
	auto equals(const Comparable& copy) const -> bool override;
};