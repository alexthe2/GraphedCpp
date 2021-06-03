#pragma once
class Comparable {
public:
	virtual ~Comparable() = default;
	virtual auto equals(const Comparable& copy) const -> bool = 0;

	friend bool operator== (const Comparable& c1, const Comparable& c2);
	friend bool operator!= (const Comparable& c1, const Comparable& c2);
};