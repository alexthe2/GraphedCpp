#pragma once
class GraphVertex {

public:
	virtual auto equals(GraphVertex* copy) const -> bool = 0;
};