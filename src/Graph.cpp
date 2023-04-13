// By: Gonçalo Leão

#include "Graph.h"


std::unordered_map<string , Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

unordered_set<Vertex*> Graph::getExtremes() const{
    unordered_set<Vertex*> testExtremes;

    /* EXAMPLE 2.2
    testExtremes.insert(findVertex("V1"));
    testExtremes.insert(findVertex("V5"));
    testExtremes.insert(findVertex("V6"));
    */

    /* EXAMPLE 2.3
    testExtremes.insert(findVertex("V1"));
    testExtremes.insert(findVertex("V5"));
    */

    /* EXAMPLE 4.1/4.2
    testExtremes.insert(findVertex("V12"));
    testExtremes.insert(findVertex("V8"));
    testExtremes.insert(findVertex("V7"));
    testExtremes.insert(findVertex("V2"));
    testExtremes.insert(findVertex("V6"));
    testExtremes.insert(findVertex("V4"));
    */

    return testExtremes;
}

unordered_set<Vertex*> Graph::getExtremesMunicipalities() const{
    unordered_set<Vertex*> test;
    test.insert(findVertex("V1"));
    test.insert(findVertex("V3"));
    test.insert(findVertex("V4"));
    test.insert(findVertex("V5"));
    test.insert(findVertex("V12"));
    test.insert(findVertex("V13"));
    test.insert(findVertex("V11"));
    test.insert(findVertex("V6"));

    return test;
}

unordered_set<Vertex*> Graph::getExtremesDistricts() const{
    return extremesDistricts;
}

int Graph::getRegion() const {
    return this->region;
}

void Graph::setRegion(enum region r) {
    this->region = r;
}


/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(const string &id) const {
    auto lowerId = id;
    transform(lowerId.begin(), lowerId.end(), lowerId.begin(), ::tolower);
    auto v = vertexSet.find(lowerId);
    if (v == vertexSet.end()) return nullptr;
    else return v->second;
}

void Graph::insertExtreme(Vertex *v) {
    extremes.insert(v);
}

void Graph::insertExtremeMunicipality(Vertex *v) {
    extremesMunicipalities.insert(v);
}

void Graph::insertExtremeDistrict(Vertex *v) {
    extremesDistricts.insert(v);
}



int Graph::findBottleneck(Vertex* src) const {
    int cap = numeric_limits<int>::max();
    int tmp;
    auto v = src;
    auto e = v->getPath();

    while (e != nullptr) {
        tmp = e->getOrig() == v ? e->getFlow() : e->getCapacity() - e->getFlow() - e->getReverse()->getFlow();

        if (tmp < cap)
            cap = tmp;

        v = e->getOrig() == v ? e->getDest() : e->getOrig();

        e = v->getPath();
    }

    return cap;
}

void Graph::augmentFlow(Vertex* dest, int flow) const {
    auto v = dest;
    auto e = v->getPath();

    while (e != nullptr) {
        e->getOrig() == v ? e->setFlow(e->getFlow() - flow) : e->setFlow(e->getFlow() + flow);

        v = e->getOrig() == v ? e->getDest() : e->getOrig();

        e = v->getPath();
    }
}

bool Graph::findPath(Vertex* origin , Vertex* dest) const {
    resetNodes();

    queue<Vertex*> q;
    origin->setVisited(true);
    q.push(origin);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto e : v->getAdj()) {
            auto w = e->getDest();

            if (v->getComponent() != 0 && w->getComponent() != v->getComponent())
                continue;

            bool isNotFull = e->getCapacity() > e->getFlow() + e->getReverse()->getFlow();

            if (!w->isVisited() && isNotFull && !e->getDisabled()) {
                if (w == dest) {
                    w->setPath(e);
                    return true;
                }

                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }

        for (auto e : v->getIncoming()) {
            auto w = e->getOrig();
            if (!w->isVisited() && e->getFlow() > 0 && !e->getDisabled()) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }

    return false;
}


bool Graph::findDistrictPath(Vertex* origin , Vertex* dest ) const {
    resetNodes();

    queue<Vertex*> q;
    origin->setVisited(true);
    q.push(origin);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto e : v->getAdj()) {
            auto w = e->getDest();
            if(w->getDistrict() != v->getDistrict()){
                continue;
            }
            if (!w->isVisited() && e->getCapacity() > e->getFlow() + e->getReverse()->getFlow()) {
                if (w == dest) {
                    w->setPath(e);
                    return true;
                }

                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }

        for (auto e : v->getIncoming()) {
            auto w = e->getOrig();
            if(w->getDistrict() != v->getDistrict()){
                continue;
            }
            if (!w->isVisited() && e->getFlow() > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }

    return false;
}


bool Graph::findMunPath(Vertex* origin , Vertex* dest ) const {
    resetNodes();

    queue<Vertex*> q;
    origin->setVisited(true);
    q.push(origin);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        for (auto e : v->getAdj()) {
            auto w = e->getDest();
            if(w->getMunicipality() != v->getMunicipality()){
                continue;
            }
            if (!w->isVisited() && e->getCapacity() > e->getFlow() + e->getReverse()->getFlow()) {
                if (w == dest) {
                    w->setPath(e);
                    return true;
                }

                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }

        for (auto e : v->getIncoming()) {
            auto w = e->getOrig();

            if(w->getMunicipality() != v->getMunicipality()){
                continue;
            }
            if (!w->isVisited() && e->getFlow() > 0) {
                w->setVisited(true);
                w->setPath(e);
                q.push(w);
            }
        }
    }

    return false;
}

void Graph::districtMaxFlow(const string &origin, const string &dest) const {
    resetNodes();
    resetFlow();

    auto s = findVertex(origin);
    auto t = findVertex(dest);

    while (findDistrictPath(s, t)){
        int flow = findBottleneck(t);
        augmentFlow(t, flow);
    }
}

void Graph::munMaxFlow(const string &origin, const string &dest) const {
    resetNodes();
    resetFlow();

    auto s = findVertex(origin);
    auto t = findVertex(dest);

    while (findMunPath(s, t)){
        int flow = findBottleneck(t);
        augmentFlow(t, flow);
    }
}

void Graph::maxFlow(const string &origin, const string &dest) const {
    resetNodes();
    resetFlow();

    auto s = findVertex(origin);
    auto t = findVertex(dest);

    while (findPath(s, t)){
        int flow = findBottleneck(t);
        augmentFlow(t, flow);
    }
}


void Graph::minCostMaxFlow(Vertex *origin, Vertex *dest) const {
    resetNodes();
    resetFlow();

    while (findCheapestPath(origin, dest)){
        int flow = findBottleneck(dest);
        augmentFlow(dest, flow);
    }
}

// No need to check for negative cycles in the Bellman-Ford
bool Graph::findCheapestPath(Vertex *origin, Vertex *dest) const {
    resetNodes();
    bool relaxedAnEdge;

    origin->setPrice(0);

    for (int i = 0; i < getVertexSet().size(); i++) {
        relaxedAnEdge = false;

        for (const auto& v: getVertexSet()) {
            Vertex *orig = v.second;

            for (Edge *e: orig->getAdj()) {
                Vertex *adjNode = e->getDest();
                Edge *reverse = e->getReverse();

                if (orig->getComponent() != 0 && adjNode->getComponent() != orig->getComponent())
                    continue;

                bool relaxEdge = adjNode->getPrice() > orig->getPrice() + e->getService();
                bool isNotFull = e->getCapacity() > e->getFlow() + reverse->getFlow();

                if (relaxEdge && isNotFull) {
                    adjNode->setPrice(orig->getPrice() + e->getService());
                    adjNode->setPath(e);
                    relaxedAnEdge = true;
                }
            }

            for (Edge *e: orig->getIncoming()) {
                Vertex *adjNode = e->getOrig();

                bool relaxEdge = adjNode->getPrice() > orig->getPrice() - e->getService();

                if (e->getFlow() > 0 && relaxEdge) {
                    adjNode->setPrice(orig->getPrice() - e->getService());
                    adjNode->setPath(e);
                    relaxedAnEdge = true;
                }
            }
        }

        if (!relaxedAnEdge)
            break;
    }

    return dest->getPath() != nullptr;
}

bool Graph::addVertex(const string &id) {
    if (findVertex(id) != nullptr)
        return false;
    string lowerid = id;
    transform(lowerid.begin(), lowerid.end(), lowerid.begin(), ::tolower);
    vertexSet.insert({lowerid, new Vertex(id)});
    return true;
}

bool Graph::addVertex(Vertex *v) {
    if (findVertex(v->getId()) != nullptr)
        return false;

    auto lowerId = v->getId();
    transform(lowerId.begin(), lowerId.end(), lowerId.begin(), ::tolower);
    vertexSet.insert({lowerId, v});
    return true;
}

bool Graph::removeVertex(const std::string &id) {
    if (findVertex(id) == nullptr) return false;
    auto v = findVertex(id);
    v->removeOutgoingEdges();
    auto lowerId = v->getId();
    transform(lowerId.begin(), lowerId.end(), lowerId.begin(), ::tolower);
    vertexSet.erase(lowerId);
    return true;
}

bool Graph::removeVertex(Vertex *v) {
    if (findVertex(v->getId()) == nullptr) return false;
    v->removeOutgoingEdges();
    auto lowerId = v->getId();
    transform(lowerId.begin(), lowerId.end(), lowerId.begin(), ::tolower);
    vertexSet.erase(lowerId);
    return true;
}

bool Graph::addBidirectionalEdge(const string &sourc, const string &dest, double c, enum service s) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, c);
    auto e2 = v2->addEdge(v1, c);
    e1->setReverse(e2);
    e2->setReverse(e1);
    e1->setService(s);
    e2->setService(s);
    return true;
}

void Graph::resetFlow() const {
    for (const auto& v: getVertexSet()) {
        for (auto e: v.second->getAdj()) {
            e->setFlow(0);
        }
        for (auto e: v.second->getIncoming()) {
            e->setFlow(0);
        }
    }
}

void Graph::resetNodes() const {
    for (auto v: getVertexSet()) {
        v.second->setVisited(false);
        v.second->setPath(nullptr);
        v.second->setPrice(100000); // Can't be the maximum value of an integer as it would overflow when using the Bellman-Ford algorithm
        v.second->setInQueue(false);

        for (Edge *e: v.second->getAdj()) {
            e->setVisited(false);
        }
    }
}

int Graph::getMaxFlow(Vertex *v1, Vertex *v2) {
    maxFlow(v1->getId(), v2->getId());
    int flow = 0;
    for (auto e: v2->getIncoming()) flow += e->getFlow();
    return flow;
}

int Graph::getMunMaxFlow(Vertex *v1, Vertex *v2) {
    munMaxFlow(v1->getId(), v2->getId());
    int flow = 0;
    for (auto e: v2->getIncoming()) flow += e->getFlow();
    return flow;
}

int Graph::getDistrictMaxFlow(Vertex *v1, Vertex *v2) {
    districtMaxFlow(v1->getId(), v2->getId());
    int flow = 0;
    for (auto e: v2->getIncoming()) flow += e->getFlow();
    return flow;
}

Graph::~Graph() {
}

int Graph::computeCost(Vertex *origin) const {
    int totalCost = 0;
    queue<Vertex *> q;
    resetNodes();

    origin->setVisited(true);
    q.push(origin);
    Vertex *currNode;

    while (!q.empty()) {
        currNode = q.front();

        for (Edge *e: currNode->getAdj()) {
            Vertex *destNode = e->getDest();

            if (e->getFlow() > 0 && !e->getVisited()) {
                if (!destNode->isVisited()) {
                    q.push(destNode);
                    destNode->setVisited(true);
                }
                totalCost += e->getFlow() * e->getService();
                e->setVisited(true);
            }
        }

        q.pop();
    }

    return totalCost;
}

vector<Edge *> Graph::fetchUsedEdges(vector<Vertex *> result_vector) {
    vector<Edge *> allEdges;

    queue<Vertex *> q;
    for (auto e : result_vector) {
        q.push(e);
    }
    auto origin = q.front();
    resetNodes();

    origin->setVisited(true);
    q.push(origin);
    Vertex *currNode;

    while (!q.empty()) {
        currNode = q.front();

        for (Edge *e: currNode->getAdj()) {
            Vertex *destNode = e->getDest();

            if (e->getFlow() > 0 && !e->getVisited()) {
                if (!destNode->isVisited()) {
                    q.push(destNode);
                    destNode->setVisited(true);
                }
                allEdges.push_back(e);
                e->setVisited(true);
            }
        }

        q.pop();
    }

    return allEdges;
}

int Graph::getVertexFlow(Vertex *v) const {
    int totalFlow = 0;
    for (Edge *e: v->getIncoming()) {
        totalFlow += e->getFlow();
    }

    return totalFlow;
}

Vertex *Graph::addSuperSource(Vertex* dest) {
    string superNode = "Super Node";

    addVertex(superNode);

    for (auto e: getExtremes()){
        if (e != dest) addBidirectionalEdge(superNode, e->getId(), 9999, STANDARD);
    }

    findVertex(superNode)->setComponent(0);

    return findVertex(superNode);
}

void Graph::removeSuperSource(Vertex* superSource) {
    for (Vertex *extreme: extremes) {
        extreme->removeEdge(superSource->getId());
    }

    removeVertex(superSource->getId());
}

void Graph::connectedComponentsDfs(Vertex *src, int i) {
    src->setVisited(true);
    src->setComponent(i);

    for (Edge *e: src->getAdj()) {
        Vertex *dest = e->getDest();

        if (!dest->isVisited()) {
            connectedComponentsDfs(dest, i);
        }
    }
}

void Graph::setConnectedComponents() {
    resetNodes();
    int i = 1;

    for (const auto& v: vertexSet) {
        Vertex *vertex = v.second;

        if (!vertex->isVisited()) {
            connectedComponentsDfs(vertex, i);
            i++;
        }
    }
}
