#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

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

        void setVertex(Tvertex _v){               // Setter for vertex
            v = _v;
        }

        void addEdge(Edge<Tvertex,Tedge>* &e){         // Add edge
            edges.push_back(e);
        }

        EdgeList incidentEdges(){               // Return incident edges
            return edges; 
        }

        bool isAdjacentTo(Vertex<Tvertex,Tedge>* &_v){            // Return true if vertex is adjacent to given vertex 'v'
            
            if (v == *(*_v)){
                return false;        // Vertex is NOT adjacent to itself
            }
            
            for(int i=0; i<edges.size(); i++){
                // Choose edge 'e'
                Edge<Tvertex,Tedge>* e = new Edge<Tvertex,Tedge>;
                e = edges[i];

                // Iterate through end vertices of 'e' , return true after finding 'v'
                for (int j=0; j<e->endVertices().size(); j++){
                    Vertex<Tvertex,Tedge>* u = new Edge<Tvertex,Tedge>;
                    u = e->endVertices()[j];
                    if(*(*u) == *(*_v)){
                        return true;
                    }
                }
            }
            
            return false;
        }

        void eraseEdge(Edge<Tvertex,Tedge>* e){
            for (int i=0; i<edges.size(); i++){
                if (*(*edges[i]) == *(*e)){
                    edges.erase(edges.begin() + i);
                    break;
                }
            }
            return;
        }
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

        void setEdge(Tedge _e){               // Setter for Edge
            e = _e;
        }

        void addVertex(Vertex<Tvertex,Tedge>* &v){          // Add vertex
            if (vertices.size() == 2){
                std::cout << "Edge already connected to 2 vertices\n";
                return;
            }

            vertices.push_back(v);
            return;
        }

        VertexList endVertices(){       // Return end vertices
            return vertices;
        }

        Vertex<Tvertex,Tedge>* opposite(Vertex<Tvertex,Tedge>* &_v){       // Return vertex opposite to vertex given 'v'
            
            for (int i=0; i<vertices.size(); i++){
                if (*(*vertices[i]) != *(*_v)){
                    return vertices[i];
                    break;
                }
            }

            return nullptr;
        }

        bool isAdjacentTo(Edge<Tvertex,Tedge>* &f){         // Return true if edge is adjacent to given edge 'e'
            if (*(*f) == e){
                return false;    // Edge is NOT adjacent to itself
            }
            
            for (int i=0; i<vertices.size(); i++){
                // Choose vertex 'v'
                Vertex<Tvertex,Tedge>* v = new Vertex<Tvertex,Tedge>;
                v = vertices[i];

                // Iterate through all edges of 'v', return true after finding 'f'
                for (int j=0; j<v->incidentEdges().size(); j++){
                    Edge<Tvertex,Tedge>* tempEdge = new Edge<Tvertex,Tedge>;
                    tempEdge = v->incidentEdges()[j];
                    if (*(*tempEdge) == *(*f)){
                        return true;
                    }
                }
            }

            return false;
        }


        bool isIncidentOn(Vertex<Tvertex,Tedge>* &v){        // Return true if edge is incident on vertex 'v'
            for (int i=0; i<vertices.size(); i++){
                if (*(vertices[i]) == *(*v)){
                    return true;
                }
            }

            return false;
        }
};

// Graph Object
/*
    - Contains number of vertices currently in graph
    - Contains vector storing all vertex objects
    - Contains vector storing all edge objects
*/
template <typename Tvertex, typename Tedge>
class Graph{
    private:
        // Number of vertices in the graph
        int n_Vertices = 0;

        // Number of vertices in the graph
        int n_Edges = 0;
        
        // List of all vertices in the graph
        typedef std::vector<Vertex<Tvertex,Tedge>*> VertexList;
        VertexList vertex_list;

        // List of all edges in the graph
        typedef std::vector<Edge<Tvertex,Tedge>*> EdgeList;
        EdgeList edge_list;
    public:
        Graph(){};       // Default constructor
        Graph(std::string filename){        // Create graph from file
            
            // Opening file
            std::ifstream myFile;
            myFile.open(filename);
            if (!myFile){
                std::cout << "File not found! Terminating!\n\n";
                return;
            }

            // Variables
            std::string vertex_u;
            std::string vertex_v;
            std::string edge_e;
            
            std::string line;

           
            std::getline(myFile,line);   // Skip first line
            while (std::getline(myFile,line)){
                std::istringstream tab_string(line);

                // Extract vertices, edge
                std::getline(tab_string,vertex_u,'\t');
                Vertex<std::string,std::string>* u = new Vertex<std::string,std::string>;
                u->setVertex(vertex_u);
                
                std::getline(tab_string,vertex_v,'\t');
                Vertex<std::string,std::string>* v = new Vertex<std::string,std::string>;
                v->setVertex(vertex_v);
                
                
                std::getline(tab_string,edge_e,'\t');
                Edge<std::string,std::string>* e = new Edge<std::string,std::string>;
                e->setEdge(edge_e);
                
                u = insertVertex(u);
                v = insertVertex(v);
                e = insertEdge(v,u,e);
               
                //std::cout << "Vertex 1: " << *(*u) << " Size: " << u->incidentEdges().size() << "\n";
                //std::cout << "Vertex 2: " << *(*v) << " Size: " << v->incidentEdges().size() << "\n";
                //std::cout << "\n\n";
            }

            std::cout << "\nThank you. Your graph is ready\n\n";
            myFile.close();

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

        Vertex<Tvertex,Tedge>* insertVertex(Vertex<Tvertex,Tedge>* &v){       // Add Vertex to graph
            // Check if vertex already exists
            for (int i=0; i<vertex_list.size(); i++){
                if (*(*v) == *(*vertex_list[i])){
                    //std::cout << "Vertex insert failed: Vertex already exists\n";
                    return vertex_list[i];
                }
            }
            vertex_list.push_back(v);
            n_Vertices++;
           //std::cout << "Vertex successfully added\n";
            return v;
        }

        Edge<Tvertex,Tedge>* insertEdge(Vertex<Tvertex,Tedge>* &v, Vertex<Tvertex,Tedge>* &u, Edge<Tvertex,Tedge>* &x){    // Add edge to graoh
            // Check if edge already exists
            for (int i=0; i<edge_list.size(); i++){
                if (*(*x) == *(*edge_list[i])){
                    std::cout << "Edge insert failed: Edge already exists\n";
                    return edge_list[i];
                }
            }

            // Check if v1 exists
            bool vertex1 = false;
            for (int i=0; i<vertex_list.size(); i++){
                if (*(*v) == *(*vertex_list[i])){
                    vertex1 = true;
                    break;
                }
            }

            // Check if v2 exists
            bool vertex2 = false;
            for (int j=0; j<vertex_list.size(); j++){
                if (*(*u) == *(*vertex_list[j])){
                    vertex2 = true;
                    break;
                }
            }

            // Add edge
            if (vertex1 && vertex2){
                x->addVertex(v);
                x->addVertex(u);
                v->addEdge(x);
                u->addEdge(x);
                edge_list.push_back(x);
                n_Edges++;
                //std::cout << "Edge insert successful\n";
                return x;
            }else{
                std::cout << "Edge insert failed: Vertices do not exist\n";
            }

            return nullptr;
        }

        void eraseVertex(Vertex<Tvertex,Tedge>* &v){
            // Check if vertex exists
            Vertex<std::string,std::string>* tempv1 = new Vertex<std::string,std::string>;
            bool found = false;
            for (int i=0; i<numVertices(); i++){
                if (*(*vertex_list[i]) == *(*v)){
                    found = true;
                    tempv1= vertex_list[i];
                    break;
                }
            }
            if (found == false){
                std::cout << "Vertex does not exist\n";
                return;
            }

            // Disconnect edges from end vertices, and remove them
            for (int i=0; i<tempv1->incidentEdges().size(); i++){
                // Edge to be removed
                Edge<std::string,std::string>* tempEdge = new Edge<std::string,std::string>;
                tempEdge = tempv1->incidentEdges()[i];

                // Opposite vertex
                Vertex<std::string,std::string>* tempv2= new Vertex<std::string,std::string>;
                tempv2 = tempEdge->opposite(tempv1);

                // Erase edge from opposite vertex
                tempv2->eraseEdge(tempEdge);

                // Erase edge from current vertex
                tempv1->eraseEdge(tempEdge);

                // Erase edge from graph
                for (int j=0 ; j<edge_list.size(); j++){
                    if (*(*edge_list[j]) == *(*tempEdge)){
                        edge_list.erase(edge_list.begin() + j);
                        delete tempEdge;
                        n_Edges--;
                        break;
                    }
                }
                
            }


            // Remove vertex
            for (int i=0 ; i<vertex_list.size(); i++){
                if (*(*vertex_list[i]) == *(*v)){
                    vertex_list.erase(vertex_list.begin() + i);
                    n_Vertices--;
                    break;
                }
            }

            delete v;
        }

        
        void printDetails(Tvertex data){
            Vertex<Tvertex,Tedge>* v =  new Vertex<Tvertex,Tedge>;
            int i;
            for (i=0; i<vertex_list.size(); i++){
                if (*(*vertex_list[i]) == data){
                    v = vertex_list[i];
                    break;
                }
            }

            if (i==vertex_list.size()){
                std::cout << "Vertex not found!\n";
                return;
            }

            for (int j=0; j<v->incidentEdges().size(); j++){
                Edge<Tvertex,Tedge>* newEdge = new Edge<Tvertex,Tedge>;
                newEdge = v->incidentEdges()[j];
                if (*(*(newEdge->endVertices()[0])) == data){
                    std::cout << data << " to " << *(*(newEdge->endVertices()[1])) << " is " << *(*newEdge) << "\n";
                }else{
                    std::cout << data << " to " << *(*(newEdge->endVertices()[0])) << " is " << *(*newEdge) << "\n";
                }
            }
            std::cout << "\n";
            return;
        }

        bool DFS(Vertex<Tvertex,Tedge>* &v, Vertex<Tvertex,Tedge>* &goal, std::vector<Vertex<Tvertex,Tedge>*> &visited, std::vector<Vertex<Tvertex,Tedge>*> &path){
        visited.push_back(v);

            if (*(*v) == *(*goal)){
                path.push_back(v);
                return true;
            }

            for (int i=0; i<v->incidentEdges().size(); i++){
                Edge<Tvertex,Tedge>* e = new Edge<Tvertex,Tedge>;
                e = v->incidentEdges()[i];

                Vertex<Tvertex,Tedge>* u = new Vertex<Tvertex,Tedge>;
                u = e->opposite(v);

                if(std::find(visited.begin(), visited.end(), u) == visited.end()){
                    if(DFS(u, goal, visited, path)){
                        path.push_back(v);
                        return true;
                    }
                }
            }

            return false;
        }

        std::vector<Vertex<Tvertex,Tedge>*> findPath(Vertex<Tvertex,Tedge>* &start, Vertex<Tvertex,Tedge>* &goal){
            std::vector<Vertex<Tvertex,Tedge>*> visited;
            std::vector<Vertex<Tvertex,Tedge>*> path;

             DFS(start, goal, visited, path);

            if(path.empty()){
                std::cout << "No path found" << std::endl;
                return {};
            }

            std::reverse(path.begin(), path.end());
            return path;
        }
        

};

#endif
