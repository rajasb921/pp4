#ifndef GRPAH_H
#define GRAPH_H
#include <vector>
#include <cstdlib>

// Edge definition?
template <typename Tvertex, typename Tedge>
class Edge;

// Vertex Object
/*
    - Contains data of vertex (Tvertex)
    - Contains vector of pointers to incident edge objects
*/
template <typename Tvertex, typename Tedge>
class Vertex{
    private:
        Tvertex v;
        typedef std::vector<Edge<Tvertex,Tedge>*> EdgeList;    // Vector containing pointers to edge objects
        EdgeList edges;
    public:
        Vertex(){};
        Vertex(Tvertex _v , EdgeList _edges = {}){    // Constructor
            v = _v;
            edges = _edges;
        }

        Tvertex operator*(){                      // Dereference
            return v;
        }

        void addEdge(Edge<Tvertex,Tedge> e){         // Add edge
            edges.push_back(&e);
            return;
        }

        void removeEdge(Edge<Tvertex, Tedge> e){
            edges.pop(  )
        }

        EdgeList incidentEdges(){               // Return incident edges
            return edges; 
        }

        bool isAdjacentTo(Vertex<Tvertex,Tedge> _v){            // Return true if vertex is adjacent to given vertex 'v'
            
            if (v == *_v){
                return false;        // Vertex is NOT adjacent to itself
            }
            
            for(size_t i=0; i < edges.size(); i++){
                // Choose edge 'e'
                Edge<Tvertex,Tedge> *e;
                e = edges[i];
                // Iterate through end vertices of 'e' , return true after finding 'v'
                for (size_t j = 0; j < e->endVertices().size(); j++){
                    Vertex<Tvertex,Tedge> *u;
                    u = e->endVertices()[j];
                    if(*(*u) == *_v){
                        return true;
                    }
                }
            }
            
            return false;
        }

        /*
        // Disconnects edge from given vertex, but DOES NOT DELETE IT 
        //helpful for case where edge should still exist, but remove it
        //from Vertex::edges --- might not be necessary 
        void disconnectEdge(Edge<Tvertex, Tedge> e){
            //loop through incident edges to find a match
            for (size_t i = 0; i < this->incidentEdges().size(); ++i){
                if (*e == *this->incidentEdges()[i]){
                    edges.erase(edges.begin() + i);
                }
            }
        }
        */
};

// Edge object
/*
    - Contains data of edge (Tedge)
    - Contains vector of pointers to end vertices
*/
template <typename Tvertex, typename Tedge>
class Edge{
    private:
        Tedge e;
        typedef std::vector<Vertex<Tvertex,Tedge>*> VertexList;    //  Vector containing pointers to vertices
        VertexList vertices;
    public:
        Edge(){};
        Edge(Tedge _e, VertexList _vertices = {}){            // Constructor
            e = _e;
            vertices = _vertices;
        }

        Tedge operator*(){          // Dereference
            return e;
        }
        
        void addVertex(Vertex<Tvertex,Tedge> v){          // Add vertex
            if (vertices.size() == 2){
                std::cout << "Edge already connected to 2 vertices\n";
                return;
            }

            vertices.push_back(&v);
            return;
        }

        VertexList endVertices(){       // Return end vertices
            return vertices;
        }

        Vertex<Tvertex,Tedge> opposite(Vertex<Tvertex,Tedge> _v){       // Return vertex opposite to vertex given 'v'
            
            Vertex<Tvertex,Tedge> oppositeVertex;
            for (size_t i = 0; i < vertices.size(); i++){
                if (*(*vertices[i]) != *_v){
                    oppositeVertex = *vertices[i];
                    break;
                }
            }

            return oppositeVertex;
        }

        bool isAdjacentTo(Edge<Tvertex,Tedge> f){         // Return true if edge is adjacent to given edge 'f'
            if (*f == e){
                return false;    // Edge is NOT adjacent to itself
            }
            
            for (size_t i = 0; i < vertices.size(); i++){
                // Choose vertex 'v'
                Vertex<Tvertex,Tedge> *v;
                v = vertices[i];

                for (size_t j = 0; j < v->incidentEdges().size(); j++){
                    Edge<Tvertex,Tedge> *tempEdge;
                    tempEdge = v->incidentEdges()[j];
                    if (*(*tempEdge) == *f){
                        return true;
                    }
                }
            }

            return false;
        }


        bool isIncidentOn(Vertex<Tvertex,Tedge> v){        // Return true if edge is incident on vertex 'v'
            for (size_t i=0; i<vertices.size(); i++){
                if (*(*vertices[i]) == *v){
                    return true;
                }
            }

            return false;
        }
};

// Graph Object
/*
    - Contains number of vertices currently in graph
    - Contains number of edges currently in graph
    - Contains vector storing all vertex objects
    - Contains vector storing all edge objects
*/
template <typename Tvertex, typename Tedge>
class Graph{
    private:
        // Number of vertices in the graph
        int n_Vertices = 0;

        // Number of edges in the graph
        int n_Edges = 0;
        
        // List of all vertices in the graph
        typedef std::vector<Vertex<Tvertex,Tedge>> VertexList;
        VertexList vertex_list;

        // List of all edges in the graph
        typedef std::vector<Edge<Tvertex,Tedge>> EdgeList;
        EdgeList edge_list;

    public:
        Graph(){};       // Default constructor
        Graph(std::string filename){        // Create graph from file
            std::cout << "Not yet complete :(\n";
        }

        VertexList vertices(){            // Return vector of vertices
            return vertex_list;
        }

        int numVertices(){                // Return number of vertices
            return n_Vertices;
        }

        EdgeList edges(){                // Return vector of edges
            return edge_list;
        }

        int numEdges(){                  // Return number of edges
            return n_Edges;
        }

        void insertVertex(Vertex<Tvertex,Tedge> v){       // Add Vertex to graph
            // Check if vertex already exists
            for (size_t i=0; i<vertex_list.size(); i++){
                if (*v == *vertex_list[i]){
                    std::cout << "Vertex insert failed: Vertex already exists\n";
                    return;
                }
            }
            vertex_list.push_back(v);
            n_Vertices++;
            std::cout << "Vertex successfully added\n";
        }

        void insertEdge(Vertex<Tvertex,Tedge> v, Vertex<Tvertex,Tedge> u, Edge<Tvertex,Tedge> x){    // Add edge to graoh
            // Check if edge already exists
            for (size_t i=0; i<edge_list.size(); i++){
                if (*x == *edge_list[i]){
                    std::cout << "Edge insert failed: Edge already exists\n";
                    return;
                }
            }

            // Check if v1 exists
            bool vertex1 = false;
            for (size_t i=0; i<vertex_list.size(); i++){
                if (*v == *vertex_list[i]){
                    vertex1 = true;
                    break;
                }
            }

            // Check if v2 exists
            bool vertex2 = false;
            for (size_t i=0; i<vertex_list.size(); i++){
                if (*u == *vertex_list[i]){
                    vertex2 = true;
                    break;
                }
            }

            // Add edge
            if (vertex1 && vertex2){
                x.addVertex(v);
                x.addVertex(u);
                v.addEdge(x);
                u.addEdge(x);
                edge_list.push_back(x);
                n_Edges++;
                std::cout << "Edge insert successful\n";
                return;
            }else{
                std::cout << "Edge insert failed: Vertices do not exist\n";
            }

            return;
        }

        /*
        void eraseVertex(Vertex<Tvertex,Tedge> v){
            // Disconnect edges from end vertices, and remove them
            Vertex<Tvertex, Tedge>* v_ptr = nullptr; // to not loose track of selected vertex
            size_t v_index; // for deleting (erase()) the vertex from the vector

            //find if vertex v is in vertex_list
            for (size_t i = 0; i < vertex_list.size(); ++i){
                if (*vertex_list[i] == *v){
                    v_ptr = &vertex_list[i];
                    v_index = i;
                    break;
                }
            }

            if (v_ptr = nullptr){
                std::cout << "Vertex not found!" << std::endl;
                return;
            }

            // loop through incident edges of v, deleting them along the way
            for (size_t i = 0; i < (*v_ptr).incidentEdges().size(); ++i){
                Edge<Tvertex, Tedge>* e;
                while(!(*v_ptr).edges.empty()){
                    edges.pop_back();
                }

            }


            // Remove vertex
            // Deal with disconnected vertices? // use pointer to not lose track
        }
        */

};

#endif