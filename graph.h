#ifndef GRPAH_H
#define GRAPH_H
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

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

        EdgeList incidentEdges(){               // Return incident edges
            return edges; 
        }

        bool isAdjacentTo(Vertex<Tvertex,Tedge> _v){            // Return true if vertex is adjacent to given vertex 'v'
            
            if (v == *_v){
                return false;        // Vertex is NOT adjacent to itself
            }
            
            for(int i=0; i<edges.size(); i++){
                // Choose edge 'e'
                Edge<Tvertex,Tedge> *e = new Edge<Tvertex,Tedge>;
                e = edges[i];
                // Iterate through end vertices of 'e' , return true after finding 'v'
                for (int j=0; j<e->endVertices().size(); j++){
                    Vertex<Tvertex,Tedge> *u = new Vertex<Tvertex,Tedge>;
                    u = e->endVertices()[j];
                    if(*(*u) == *_v){
                        return true;
                    }
                }
            }
            
            return false;
        }

        void set_v(Tvertex _v){
            v = _v;
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
            for (int i=0; i<vertices.size(); i++){
                if (*(*vertices[i]) != *_v){
                    oppositeVertex = *vertices[i];
                    break;
                }
            }

            return oppositeVertex;
        }

        bool isAdjacentTo(Edge<Tvertex,Tedge> f){         // Return true if edge is adjacent to given edge 'e'
            if (*f == e){
                return false;    // Edge is NOT adjacent to itself
            }
            
            for (int i=0; i<vertices.size(); i++){
                // Choose vertex 'v'
                Vertex<Tvertex,Tedge> *v = new Vertex<Tvertex,Tedge>; 
                v = vertices[i];

                // Iterate through all edges of 'v', return true after finding 'f'
                for (int j=0; j<v->incidentEdges().size(); j++){
                    Edge<Tvertex,Tedge> *tempEdge =  new Edge<Tvertex,Tedge>;
                    tempEdge = v->incidentEdges()[j];
                    if (*(*tempEdge) == *f){
                        return true;
                    }
                }
            }

            return false;
        }


        bool isIncidentOn(Vertex<Tvertex,Tedge> v){        // Return true if edge is incident on vertex 'v'
            for (int i=0; i<vertices.size(); i++){
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
        typedef std::vector<Vertex<Tvertex,Tedge>> VertexList;
        VertexList vertex_list;

        // List of all edges in the graph
        typedef std::vector<Edge<Tvertex,Tedge>> EdgeList;
        EdgeList edge_list;
    public:
        Graph(){};       // Default constructor
        Graph(std::string filename){        // Create graph from file

            void trim(std::string& str);
            
            std::ifstream iFile(filename);
            if(!iFile.is_open()) std::cout << "ERROR: File not read!\n";

            std::string line_buff, temp_buff, v1_buff, v2_buff, e_buff;

            Vertex<std::string, float> vertex;

            // ------ Line 1 -----------

            getline(iFile, line_buff); //first line of input.txt
            std::istringstream stream(line_buff);

            //Read in all values of first line
            while(getline(stream, temp_buff, ',')){
                trim(temp_buff);
                std::cout << "temp_buff:" << temp_buff << std::endl;
                vertex.set_v(temp_buff);
                this->insertVertex(vertex);
            }

            // -----Lines 2-n -------
            std::cout << "Rest of the lines" << std::endl;

            int i = 0;
            while(!iFile.eof()){
                getline(iFile, line_buff);
                std::istringstream stream(line_buff);

                //get v and e
                std::cout << "\n------ The 3 getline's (" << i << ")-----" << std::endl;
                getline(stream, v1_buff, '\t');
                getline(stream, v2_buff, '\t');
                getline(stream, e_buff, '\t');
                std::cout << "v1_buff=" << v1_buff << std::endl;
                std::cout << "v2_buff=" << v2_buff << std::endl;
                std::cout << "e_buff=" << e_buff << std::endl;


                //convert e_buff (string) to e_float (float)
                float e_float = std::stof(e_buff);
                std::cout << "e_float=" << e_float << std::endl;
                
                //make verticies 
                Vertex<std::string, float> v1(v1_buff);
                Vertex<std::string, float> v2(v2_buff);

                //make edge (first make "verticies")
                Edge<std::string, float> e(e_float);
                this->insertEdge(v1, v2, e);

                i++;
            }

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
            for (size_t i=0; i < vertex_list.size(); i++){
                if (*v == *vertex_list[i]){
                    std::cout << "Vertex insert failed: Vertex already exists\n";
                    return;
                }
            }
            std::cout << "insertVertex(): *v = " << *v << std::endl;
            vertex_list.push_back(v);
            n_Vertices++;
            std::cout << "Vertex successfully added\n";
        }

        void insertEdge(Vertex<Tvertex,Tedge> v, Vertex<Tvertex,Tedge> u, Edge<Tvertex,Tedge> x){    // Add edge to graoh
            // Check if edge already exists
            for (int i=0; i<edge_list.size(); i++){
                if (*x == *edge_list[i]){
                    std::cout << "Edge insert failed: Edge already exists\n";
                    return;
                }
            }

            std::cout << "\nInside insertEdge():\n";
            // Check if v1 exists
            bool vertex1 = false;
            for (int i=0; i<vertex_list.size(); i++){
                std::cout << "*v=" << *v << std::endl;
                std::cout << "*vertex_list (at i=" << i << ")=" << *vertex_list[i] << std::endl;
                if (*v == *vertex_list[i]){
                    vertex1 = true;
                    break;
                }
            }

            // Check if v2 exists
            bool vertex2 = false;
            for (int i=0; i<vertex_list.size(); i++){
                std::cout << "*u=" << *u << std::endl;
                std::cout << "*vertex_list (at i=" << i << ")=" << *vertex_list[i] << std::endl;
                if (*u == *vertex_list[i]){
                    vertex2 = true;
                    break;
                }
            }

            // Add edgeRun
            if (vertex1 && vertex2){
                x.addVertex(v);
                x.addVertex(u);
                v.addEdge(x);
                u.addEdge(x);
                edge_list.push_back(x);
                n_Edges++;
                std::cout << "Edge insert successful\n"; //Move/rename a branch, together with
                return;
            }else{
                std::cout << "Edge insert failed: Vertices do not exist\n";
            }

            return;
        }

        void eraseVertex(Vertex<Tvertex,Tedge> v){
            // Disconnect edges from end vertices, and remove them
            // Remove vertex
            // Deal with disconnected vertices?
        }

};

//trim leading and trailing whitespaces
void trim(std::string& str){
    size_t size = str.find_first_not_of(" \t");
    str.erase(0, size);

    size = str.find_last_not_of(" \t");
    if (std::string::npos != size)
    str.erase(size+1);
}


#endif