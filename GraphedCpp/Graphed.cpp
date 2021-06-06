#include "Graphed.h"
#include "Utils.h"

#include <algorithm>

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex> && CheckType<Edge, GraphEdge>
Graphed<Vertex, Edge>::Graphed(bool auto_clean) {
	this->adjacency_list_ = std::map<Vertex*, std::vector<AdjacencyConnection>>();
	this->auto_clean_ = auto_clean;
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex> && CheckType<Edge, GraphEdge>
Graphed<Vertex, Edge>::~Graphed() {
    
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex> && CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::insertEdge(Vertex* from, Vertex* to, Edge* edge) -> void {
	const auto elem = this->adjacency_list_.find(from);

	if (elem == this->adjacency_list_.end()) {
		this->adjacency_list_.insert(std::pair<Vertex*, std::vector<AdjacencyConnection>>(from, std::vector<AdjacencyConnection>(1, AdjacencyConnection(to, edge))));
	} else {
		elem->second.emplace_back(AdjacencyConnection(to, edge));
	}
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex> && CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::insertBiEdge(Vertex* vertex1, Vertex* vertex2, Edge* value) -> void {
	this->insertEdge(vertex1, vertex2, value);
	this->insertEdge(vertex2, vertex1, value);
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex> && CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::insertVertex(Vertex* vertex) -> void {
	const auto elem = this->adjacency_list_.find(vertex);

	if(elem == this->adjacency_list_.end()) {
		this->adjacency_list_.insert(std::pair<Vertex*, std::vector<AdjacencyConnection>>(vertex, std::vector<AdjacencyConnection>()));
	}
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex>&& CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::removeVertex(Vertex* vertex) -> bool {
	const auto elem = this->adjacency_list_.find(vertex);

	if (elem == this->adjacency_list_.end()) {
		return false;
	}

	// TODO: It's missing
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex>&& CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::removeVertex(Vertex* vertex, bool auto_clean_override) -> bool {
    
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex>&& CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::removeEdge(Vertex* from, Vertex* to, Edge* value) -> bool {
	const auto elem = this->adjacency_list_.find(from);

	if(elem == this->adjacency_list_.end()) {
		return false;
	}
	
	IGNORE(remove(elem->second.begin(), elem->second.end(), AdjacencyConnection(to, value)));
	return true;
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex> && CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::removeEdge(Vertex* from, Vertex* to, Edge* value, bool auto_clean_override) -> bool {}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex>&& CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::changeEdge(Vertex* from, Vertex* to, Edge *old_value, Edge *new_value) -> bool {
	return changeEdge(from, to, old_value, new_value, this->auto_clean_);
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex> && CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::changeEdge(Vertex* from, Vertex* to, Edge* old_value, Edge* new_value,
                         const bool auto_clean_override) -> bool {
	const auto elem = this->adjacency_list_.find(from);

	if (elem == this->adjacency_list_.end()) {
		return false;
	}

	const auto old_element = *(std::find(elem->second.begin(), elem->second.end(), old_value));

	std::replace(elem->second.begin(), elem->second.end(),
		AdjacencyConnection(to, old_value), AdjacencyConnection(to, new_value));

	if(auto_clean_override) {
		delete old_element.first;
		delete old_element.second;
	}

	return true;
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex> && CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::getAllEdges(Vertex* from, Vertex* to) -> std::vector<Edge*> {
	const auto elem = this->adjacency_list_.find(from);
	auto edges = std::vector<Edge>();
	
	if(elem != this->adjacency_list_.end()) {
		for(const auto& entry : elem->second) {
			edges.emplace_back(entry.second);
		}
	}

	return edges;
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex>&& CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::getAllConnectingNodes(Vertex* from) -> std::vector<Vertex*> {
	const auto elem = this->adjacency_list_.find(from);
	auto edges = std::vector<Vertex>();

	if (elem != this->adjacency_list_.end()) {
		for (const auto& entry : elem->second) {
			edges.emplace_back(entry.first);
		}
	}

	return edges;
}

template <typename Vertex, typename Edge>
requires CheckType<Vertex, GraphVertex>&& CheckType<Edge, GraphEdge>
auto Graphed<Vertex, Edge>::constructMatrix() -> std::vector<std::vector<int>> {
	auto lut = std::map<Vertex*, int>();
	auto i = 0;
	for (const auto& entry : this->adjacency_list_) {
		lut.emplace(entry.first, i++);
	}

	auto matrix = std::vector<std::vector<int>>(i, std::vector<int>(i, -1));
	for (const auto& entry : this->adjacency_list_) {
		for (const auto& to : entry.second) {
			matrix.at(lut.at(entry.first)).at(lut.at(to.first)) = to.second->calculateValue();
		}
	}

	return matrix;
}
