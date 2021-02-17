#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    Graph & removeEdge(const N &begin, const N &end);
    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges(void) const;
    unsigned numNodes(void) const;
    void print(std::ostream &os) const;
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }

template <class N>
class EdgeAlreadyExists
{
public:
    N info1, info2;
    EdgeAlreadyExists(N inf1, N inf2) {info1 = inf1; info2 = inf2;}
};
template <class N>
std::ostream & operator<<(std::ostream & out, const EdgeAlreadyExists<N> &e)
{ out << "Edge already exists: " << e.info1 << " , " << e.info2; return out; }

// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

template <class N>
class EdgeDoesNotExist {
public:
    N info1, info2;
    EdgeDoesNotExist(N inf1, N inf2) {
        info1 = inf1;
        info2 = inf2;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &e)
{ out << "Edge does not exist: " << e.info1 << " , " << e.info2; return out; }

template <class N, class E>
Graph<N,E>::Graph() {}

template <class N, class E>
Graph<N, E>::~Graph() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        delete *it;
    }
}

template <class N, class E>
unsigned Graph<N, E>::numEdges() const {
    int nEdges = 0;
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        nEdges += (*it)->edges.size();
    }
    return nEdges;
}

template <class N, class E>
unsigned Graph<N, E>::numNodes() const {
    return nodes.size();
}

template <class N, class E>
Graph<N, E> & Graph<N, E>::addNode(const N &inf) {
    for (auto it = nodes.begin(); it != nodes.end(); it++)  {
        if ((*it)->info == inf) {
            throw NodeAlreadyExists<N>(inf);
        }
    }
    Node<N,E> *no1 = new Node<N,E>(inf);
    nodes.push_back(no1);
    return *this;
}

template <class N, class E>
Graph<N, E> & Graph <N, E>::addEdge(const N &begin, const N &end, const E &val) {
    bool foundBegin = false;
    bool foundEnd = false;
    Node<N,E> *noBegin_apt = NULL;
    Node<N,E> *noEnd_apt = NULL;
    for (auto it = nodes.begin(); it != nodes.end(); it ++) {
        if ((*it)->info == begin) {
            foundBegin = true;
            noBegin_apt = *it;
            for (auto it1 = (*it)->edges.begin(); it1 != (*it)->edges.end(); it1++) {
                if (it1->destination->info == end) {
                    throw EdgeAlreadyExists<N> (begin, end);
                }
            }
            if (foundEnd == true) {
                break;
            }
        }
        else if ((*it)->info == end) {
            foundEnd = true;
            noEnd_apt = *it;
            if (foundBegin == true) {
                break;
            }
        }
    }
    if (!foundBegin) {
        throw NodeDoesNotExist<N>(begin);
    }
    if (!foundEnd) {
        throw NodeDoesNotExist<N>(end);
    }
    Edge<N,E> edge1(noEnd_apt, val);
    noBegin_apt->edges.push_back(edge1);

    return *this;
}

template <class N, class E>
E & Graph<N, E>::edgeValue(const N &begin, const N &end) {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if ((*it)->info == begin) {
            for (auto it1 = (*it)->edges.begin(); it1 != (*it)->edges.end(); it1++) {
                if (it1->destination->info == end) {
                    return it1->value;
                }
                throw EdgeDoesNotExist<N> (begin, end);
            }
        }
    }
    throw NodeDoesNotExist<N> (begin);
}

template <class N, class E>
Graph<N, E> & Graph<N, E>::removeEdge(const N &begin, const N &end) {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if ((*it)->info == begin) {
            for (auto it1 = (*it)->edges.begin(); it1 != (*it)->edges.end(); it1++) {
                if (it1->destination->info == end) {
                    (*it)->edges.erase(it1);
                    return *this;
                }
            }
            throw EdgeDoesNotExist<N> (begin, end);
        }
    }
    throw NodeDoesNotExist<N> (begin);
    return *this;
}

template <class N, class E>
void Graph<N, E>::print(std::ostream &os) const {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        os << "( " << (*it)->info;
        for (auto it1 = (*it)->edges.begin(); it1 != (*it)->edges.end(); it1++) {
            os << "[ " << it1->destination->info << " " << it1->value << "] ";
        }
        os << ") ";
    }
}

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g) {
    g.print(out);
    return out;
}