#pragma once
#include <map>
#include <vector>

#include "GraphEdge.h"
#include "GraphVertex.h"

// ReSharper disable once CppInconsistentNaming
#define AdjacencyConnection std::pair<Vertex*, Edge*>  // NOLINT(cppcoreguidelines-macro-usage)

template <class Type, class BaseClass>
concept CheckType = std::is_base_of<BaseClass, Type>::value;

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex> && CheckType<Edge, GraphEdge>
class Graphed {
public:
	explicit Graphed(bool auto_clean=true);
	~Graphed();

	auto insertEdge(Vertex* from, Vertex* to, Edge* edge) -> void;
	auto insertBiEdge(Vertex* vertex1, Vertex* vertex2, Edge* value) -> void;

	auto insertVertex(Vertex* vertex) -> void;
	auto removeVertex(Vertex* vertex) -> bool;
	auto removeVertex(Vertex* vertex, bool auto_clean_override) -> bool;

	auto removeEdge(Vertex* from, Vertex* to, Edge* value) -> bool;
	auto removeEdge(Vertex* from, Vertex* to, Edge* value, bool auto_clean_override) -> bool;
	auto changeEdge(Vertex* from, Vertex* to, Edge* old_value, Edge* new_value) -> bool;
	auto changeEdge(Vertex* from, Vertex* to, Edge* old_value, Edge* new_value, bool auto_clean_override) -> bool;

	[[nodiscard]] auto getAllEdges(Vertex* from, Vertex* to) -> std::vector<Edge*>;
	[[nodiscard]] auto getAllConnectingNodes(Vertex* from)->std::vector<Vertex*>;
	
	[[nodiscard]] auto constructMatrix() -> std::vector<std::vector<int>>;

private:
	bool auto_clean_;
	std::map<Vertex*, std::vector<AdjacencyConnection>> adjacency_list_;
};


