// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class Edge;

#define INF std::numeric_limits<int>::max()

/************************* Vertex  **************************/

class Vertex {
public:

    /**
     * Constructor for the Vertex class;
     * @param id - the id of the vertex;
     */
    Vertex(string id);

    /**
     * Constructor for the Vertex class;
     * @param id - the id of the vertex;
     * @param district - the district of the vertex;
     * @param municipality - the municipality of the vertex;
     * @param mainLine - the main line of the vertex;
     * @param townships - the townships of the vertex;
     */
    Vertex(string id, string district, string municipality, string mainLine,
           list<string> townships);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    /**
     * Returns the id of the vertex;
     */
    string getId() const;

    /**
     * Returns a vector containing all the adjacent edges of the vertex;
     */
    vector<Edge *> getAdj() const;

    /**
     * Returns the line of the vertex;
     */
    string getLine() const;

    /**
     * Returns the district of the vertex;
     */
    string getDistrict() const;

    /**
     * Returns the municipality of the vertex;
     */
    string getMunicipality() const;

    /**
     * Checks if the vertex is visited;
     * @return true - if the vertex is visited;
     *         false - if the vertex is not visited;
     */
    bool isVisited() const;

    /**
     * Checks if the vertex is being processed;
     * @return true - if the vertex is being processed;
     *         false - if the vertex is not being processed;
     */
    bool isProcessing() const;

    /**
     * Retrieves the price of the vertex;
     * @return the price of the vertex;
     */
    int getPrice() const;

    /**
     * Retrieves the flow of the vertex;
     * @return the flow of the vertex;
     */
    int getFlow() const;

    /**
     * Checks if the vertex is in the queue;
     * @return true - if the vertex is in the queue;
     *         false - if the vertex is not in the queue;
     */
    int getMaxFlow() const;

    /**
     * Gets the attribute inQueue;
     * @return the vertex's inQueue;
     */
    bool getInQueue() const;

    /**
     * Retrieves the path of the vertex;
     * @return the edge path of the vertex;
     */
    Edge *getPath() const;

    /**
     * Retrieves the incoming edges of the vertex;
     * @return a vector containing all the incoming edges of the vertex;
     */
    vector<Edge *> getIncoming() const;


    /**
     * Sets the visited attribute of the vertex;
     * @param visited - true if the vertex is visited, false if otherwise;
     */
    void setVisited(bool visited);

    /**
     * Sets the processing attribute of the vertex;
     * @param processing - true if the vertex is being processed, false if otherwise;
     */
    void setProcesssing(bool processing);

    /**
     * Sets the price attribute of the vertex;
     * @param price - the price of the vertex;
     */
    void setPrice(int price);

    /**
     * Sets the flow attribute of the vertex;
     * @param flow - the flow of the vertex;
     */
    void setFlow(int flow);

    /**
     * Sets the inQueue attribute of the vertex;
     * @param inQueue - true if the vertex is in the queue, false if otherwise;
     */
    void setInQueue(bool inQueue);
    void setMaxFlow(int maxFlow);

    /**
     * Sets the path attribute of the vertex;
     * @param path - the edge path of the vertex;
     */
    void setPath(Edge *path);

    /**
     * Adds an edge from the vertex (this) to the destination vertex, with a given weight;
     * @param dest - the destination vertex;
     * @param w - the weight of the edge;
     * @return the edge created;
     */
    Edge * addEdge(Vertex *dest, double w);

    /**
     * Auxiliary function to remove an outgoing edge (with a given destination (d))
     * from a vertex (this).
     * Returns true if successful, and false if such edge does not exist.
     */
    bool removeEdge(string destID);

    /**
     * Removes all the outgoing edges of the vertex from the adjacency vector;
     * Time Complexity: O(E), where E is the number of edges;
     */
    void removeOutgoingEdges();
    bool operator==(const Vertex& v);

    /**
     * Gets the attribute disabledFlow;
     * @return the vertex's disabled flow;
     */
    int getDisabledFlow() const;

    /**
     * Sets the attribute disabledFlow;
     * @param disabledFlow - the amount to set;
     */
    void setDisabledFlow(int disabledFlow);

    /**
     * Gets the attribute component
     * @return the connected component the vertex is in
     */
    int getComponent() const;

    /**
     * Sets the attribute component of the vertex
     * @param component - the connected component the vertex is in
     */
    void setComponent(int component);

protected:
    string id; /**< The id of the vertex */
    vector<Edge *> adj; /**< The adjacency vector of the vertex */

    // auxiliary fields
    bool visited = false; /**< Visited state of the vertex */  // used by DFS, BFS, Prim ...
    // used by Dijkstra
    bool processing = false;  /**< Processing state of the vertex */
    int price = 0; /**< Price of the vertex */
    int flow = 0; /**< Flow of the vertex */
    bool inQueue; /**< InQueue state of the vertex */
    int component;

protected:
    Edge *path = nullptr; /**< Edge path of the vertex */
    string name = id, district, municipality, main_line; /**< Name (id), district, municipality and main line of the vertex */
    list<string> townships; /**< Townships list of the vertex */
    int maxFlow; /**< Vertex's max flow */
    int disabledFlow; /**< Vertex's disabled flow */

    vector<Edge *> incoming; /**< Vector of incoming edges of the vertex */

    /**
     * Removes an edge from both its origin and destination vertices;
     * @param edge - the edge to be removed;
     */
    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/

enum service{STANDARD = 2, ALFA_PENDULAR = 4}; /**< Enum for the service of the edge */

class Edge {
public:
    /**
     * Constructs an edge with a given origin, destination and capacity;
     * @param orig - the origin vertex of the edge;
     * @param dest - the destination vertex of the edge;
     * @param c - the capacity of the edge;
     */
    Edge(Vertex *orig, Vertex *dest, double c);

    /**
     * Gets the destination vertex of the edge;
     * @return the destination vertex of the edge;
     */
    Vertex * getDest() const;

    /**
     * Gets the capacity of the edge;
     * @return the capacity of the edge;
     */
    int getCapacity() const;


    /**
     * Gets the origin vertex of the edge;
     * @return the origin vertex of the edge;
     */
    Vertex * getOrig() const;

    /**
     * Gets the reverse edge of the edge;
     * @return the reverse edge of the edge;
     */
    Edge *getReverse() const;

    /**
     * Gets the flow of the edge;
     * @return the flow of the edge;
     */
    int getFlow() const;

    /**
     * Gets the service of the edge;
     * @return the service of the edge;
     */
    int getService() const;

    /**
     * Checks if the edge is disabled;
     * @return true - if the edge is disabled;
     *         false - if the edge is not disabled;
     */
    bool getDisabled() const;

    /**
     * Checks if the edge is visited;
     * @return true - if the edge is visited;
     *         false - if the edge is not visited;
     */
    bool getVisited() const;


    /**
     * Sets the visited attribute of the edge;
     * @param visited - true if the edge is visited, false if otherwise;
     */
    void setVisited(bool visited);

    /**
     * Sets the reverse attribute of the edge;
     * @param reverse - the reverse edge of the edge;
     */
    void setReverse(Edge *reverse);

    /**
     * Sets the flow attribute of the edge;
     * @param flow - the flow of the edge;
     */
    void setFlow(int flow);

    /**
     * Sets the service attribute of the edge;
     * @param service - the service of the edge;
     */
    void setService(enum service s);

    /**
     * Sets the disabled attribute of the edge;
     * @param disabled - true if the edge is disabled, false if otherwise;
     */
    void setDisabled(bool disabled);
protected:
    Vertex * dest; /**< Destination vertex of the edge */
    double capacity; /**< Capacity, or weight, of the edge */

    // auxiliary fields
    bool selected = false; /**< Selected state of the edge */
    bool disabled = false; /**< Disabled state of the edge */
    bool visited = false; /**< Visited state of the edge */

    // used for bidirectional edges
    Vertex *orig; /**< Origin vertex of the edge */
    Edge *reverse = nullptr; /**< Reverse edge of the edge */

    int flow; /**< Flow of the edge */

    enum service service; /**< Service of the edge */

};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */