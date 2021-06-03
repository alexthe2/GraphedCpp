#pragma once
#include <map>
#include <vector>

#include "GraphEdge.h"
#include "GraphVertex.h"

// ReSharper disable once CppInconsistentNaming
#define AdjacencyConnection std::pair<GraphVertex, GraphEdge>

class Graphed {
public:
	Graphed();

	auto insertEdge(GraphVertex from, GraphVertex to, GraphEdge edge) -> void;
	auto insertBiEdge(GraphVertex vertex1, GraphVertex vertex2, GraphEdge value) -> void;
	
	auto removeEdge(GraphVertex from, GraphVertex to, GraphEdge value) -> bool;
	auto changeEdge(GraphVertex from, GraphVertex to, GraphEdge oldValue, GraphEdge newValue) -> bool;

	auto getAllEdges(GraphVertex from, GraphVertex to) -> std::vector<GraphEdge>;
	auto getAllConnectingNodes(GraphVertex from)->std::vector<GraphVertex>;
	
	auto constructMatrix() -> std::vector<std::vector<int>>;

private:
	std::map<GraphVertex, std::vector<AdjacencyConnection>> adjacency_list_;
};


