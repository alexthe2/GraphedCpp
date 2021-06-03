#include "Graphed.h"

#include <algorithm>


#include "Utils.h"

Graphed::Graphed() {
	this->adjacency_list_ = std::map<GraphVertex, std::vector<AdjacencyConnection>>();
}

auto Graphed::insertEdge(GraphVertex from, GraphVertex to, GraphEdge edge) -> void {
	const auto elem = this->adjacency_list_.find(from);

	if (elem == this->adjacency_list_.end()) {
		this->adjacency_list_.insert(std::pair<GraphVertex, std::vector<AdjacencyConnection>>(from, std::vector<AdjacencyConnection>(1, AdjacencyConnection(to, edge))));
	} else {
		elem->second.emplace_back(AdjacencyConnection(to, edge));
	}
}

auto Graphed::insertBiEdge(GraphVertex vertex1, GraphVertex vertex2, GraphEdge value) -> void {
	this->insertEdge(vertex1, vertex2, value);
	this->insertEdge(vertex2, vertex1, value);
}

auto Graphed::removeEdge(GraphVertex from, GraphVertex to, GraphEdge value) -> bool {
	const auto elem = this->adjacency_list_.find(from);

	if(elem == this->adjacency_list_.end()) {
		return false;
	}
	
	IGNORE(remove(elem->second.begin(), elem->second.end(), AdjacencyConnection(to,value)));
	return true;
}

auto Graphed::changeEdge(GraphVertex from, GraphVertex to, GraphEdge oldValue, GraphEdge newValue) -> bool {
	const auto elem = this->adjacency_list_.find(from);

	if (elem == this->adjacency_list_.end()) {
		return false;
	}

	std::replace(elem->second.begin(), elem->second.end(), AdjacencyConnection(to, oldValue), AdjacencyConnection(to, newValue));
	return true;
}

auto Graphed::getAllEdges(GraphVertex from, GraphVertex to) -> std::vector<GraphEdge> {
	const auto elem = this->adjacency_list_.find(from);
	auto edges = std::vector<GraphEdge>();
	
	if(elem != this->adjacency_list_.end()) {
		for(const auto& entry : elem->second) {
			edges.emplace_back(entry.second);
		}
	}

	return edges;
}

auto Graphed::getAllConnectingNodes(GraphVertex from) -> std::vector<GraphVertex> {
	const auto elem = this->adjacency_list_.find(from);
	auto edges = std::vector<GraphVertex>();

	if (elem != this->adjacency_list_.end()) {
		for (const auto& entry : elem->second) {
			edges.emplace_back(entry.first);
		}
	}

	return edges;
}

auto Graphed::constructMatrix() -> std::vector<std::vector<int>> {
	auto lut = std::map<GraphVertex, int>();
	auto i = 0;
	for (const auto& entry : this->adjacency_list_) {
		lut.emplace(entry.first, i++);
	}

	auto matrix = std::vector<std::vector<int>>(i, std::vector<int>(i, -1));
	for (const auto& entry : this->adjacency_list_) {
		for (const auto& to : entry.second) {
			matrix.at(lut.at(entry.first)).at(lut.at(to.first)) = to.second.calculateValue();
		}
	}

	return matrix;
}
