#include "Comparable.h"

auto Comparable::equals(const Comparable& copy) const -> bool {
	return true;
}

bool operator==(const Comparable& c1, const Comparable& c2) {
	return c1.equals(c2);
}

bool operator!=(const Comparable& c1, const Comparable& c2) {
	return !c1.equals(c2);
}

