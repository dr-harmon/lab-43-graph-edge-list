#pragma once

#include <unordered_map>

template <typename VertexElement, typename EdgeElement>
class Graph {
public:

    class Vertex;
    class VertexItor;
    class Edge;
    class EdgeItor;

    typedef std::unordered_map<int,Vertex> VertexMap;
    typedef std::unordered_map<int,Edge> EdgeMap;

    class VertexList {
    public:
        VertexItor begin() const {
            return VertexItor(vertexMap.begin());
        }

        VertexItor end() const {
            return VertexItor(vertexMap.end());
        }

    private:
        const VertexMap vertexMap;
        friend Graph;

        VertexList(const VertexMap& _vertexMap) : vertexMap(_vertexMap) {}
    };

    class EdgeList {
    public:
        EdgeItor begin() const {
            return EdgeItor(edgeMap.begin());
        }

        EdgeItor end() const {
            return EdgeItor(edgeMap.end());
        }

    private:
        const EdgeMap edgeMap;
        friend Graph;

        EdgeList(const EdgeMap& _edgeMap) : edgeMap(_edgeMap) {}
    };

    class VertexItor {
    public:
        const Vertex& operator*() const {
            return it->second;
        }

        VertexItor& operator++() {
            ++it;
            return *this;
        }

        VertexItor operator++(int) {
            VertexItor temp = *this;
            ++it;
            return temp;
        }

        bool operator!=(const VertexItor& other) const {
            return it != other.it;
        }

    private:
        typename VertexMap::const_iterator it;
        friend VertexList;

        VertexItor(typename VertexMap::const_iterator _it) : it(_it) {}
    };

    class EdgeItor {
    public:
        const Edge& operator*() const {
            return it->second;
        }

        EdgeItor& operator++() {
            ++it;
            return *this;
        }

        EdgeItor operator++(int) {
            EdgeItor temp = *this;
            ++it;
            return temp;
        }

        bool operator!=(const EdgeItor& other) const {
            return it != other.it;
        }

    private:
        typename EdgeMap::const_iterator it;
        friend EdgeList;

        EdgeItor(typename EdgeMap::const_iterator _it) : it(_it) {}
    };

    class Vertex {
    public:
        bool isAdjacentTo(const Vertex& v) const {
            for (const auto& edgePair : g.edgeMap) {
                if ((id == edgePair.second.startVertex && v.id == edgePair.second.endVertex) ||
                    (id == edgePair.second.endVertex && v.id == edgePair.second.startVertex)) {
                    return true;
                }
            }
            return false;
        }

        EdgeList incidentEdges() const {
            EdgeMap incidentEdges;
            for (const auto& edgePair : g.edgeMap) {
                if (edgePair.second.isIncidentOn(*this)) {
                    incidentEdges.insert(edgePair);
                }
            }
            return EdgeList(incidentEdges);
        }

        const VertexElement& operator*() const {
            return element;
        }

    private:
        VertexElement element;
        int id;
        const Graph& g;
        friend Graph;

        Vertex(const VertexElement& _element, int _id, const Graph& _g) : element(_element), id(_id), g(_g) {}
    };

    class Edge {
    public:
        VertexList endVertices() const {
            VertexMap endV;
            endV.emplace(startVertex, g.vertexMap.at(startVertex));
            endV.emplace(endVertex, g.vertexMap.at(endVertex));
            return VertexList(endV);
        }

        const Vertex& opposite(const Vertex& v) const {
            return g.vertexMap.at(v.id == startVertex ? endVertex : startVertex);
        }

        bool isIncidentOn(const Vertex& v) const {
            return v.id == startVertex || v.id == endVertex;
        }

        const EdgeElement& operator*() const {
            return element;
        }

    private:
        EdgeElement element;
        int id;
        int startVertex, endVertex;
        const Graph& g;
        friend Graph;

        Edge(const EdgeElement& _element, int _id, int _startVertex, int _endVertex, const Graph& _g) :
            element(_element), id(_id), startVertex(_startVertex), endVertex(_endVertex), g(_g) {}
    };

    const Vertex& insertVertex(const VertexElement& element) {
        Vertex v(element, nextVertexID++, *this);
        vertexMap.emplace(v.id, v);
        return vertexMap.at(v.id);
    }

    const Edge& insertEdge(const Vertex& v, const Vertex& u, const EdgeElement& element) {
        if (vertexMap.count(v.id) == 0 || vertexMap.count(u.id) == 0) {
            throw std::runtime_error("Cannot add edge between unknown vector");
        }

        Edge e(element, nextEdgeID++, v.id, u.id, *this);
        edgeMap.emplace(e.id, e);
        return edgeMap.at(e.id);
    }

    void eraseVertex(const Vertex& v) {
        vertexMap.erase(v.id);
        auto it = edgeMap.begin();
        while (it != edgeMap.end()) {
            if (it->second.isIncidentOn(v)) {
                it = edgeMap.erase(it);
            } else {
                it++;
            }
        }
    }

    void eraseEdge(const Edge& e) {
        edgeMap.erase(e.id);
    }

    VertexList vertices() const {
        return VertexList(vertexMap);
    }

    EdgeList edges() const {
        return EdgeList(edgeMap);
    }

private:
    int nextVertexID = 1;
    int nextEdgeID = 1;
    VertexMap vertexMap;
    EdgeMap edgeMap;
};
