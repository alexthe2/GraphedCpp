#pragma once

class GraphEdge
{
public:
	GraphEdge() = default;
	~GraphEdge() = default;
	
	[[nodiscard]] virtual auto calculateValue() const -> int = 0;
	[[nodiscard]] virtual auto equals(GraphEdge* copy) const -> bool;
};

class NumericEdge final : public GraphEdge {
public:
	explicit NumericEdge(int value);

    [[nodiscard]] auto calculateValue() const -> int override;

private:
	int value_;
};


