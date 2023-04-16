#ifndef EDGE_H
#define EDGE_H
#include <cstdlib>
#include <vector>
#include "vertex.h"

// Edge object
template <typename Tvertex, typename Tedge>
class Edge{
    private:
        Tedge e;
        typedef std::vector<Vertex<Tvertex,Tedge>> VertexList;    //  Define type vector of vertices
        VertexList vertices;
    public:
        Edge(Tedge _e, VertexList _vertices){            // Constructur
            e = _e;
            vertices = _vertices;
        }

        Tedge operator*(){          // Dereference
            return e;
        }

        VertexList endVertices(){       // Return end vertices
            return vertices;
        }

        Vertex opposite(Vertex<Tvertex,Tedge> v){       // Return vertex opposite to vertex given 'v'
            for (int i=0; i<vertices.size(); i++){
                if (vertices[i] != v){
                    return vertices[i];
                    break;
                }
            }
        }

        bool isAdjacentTo(Edge<Tvertex,Tedge> f){         // Return true if edge is adjacent to given edge 'e'
            if (f==e){
                return false;    // Edge is NOT adjacent to itself
            }
            
            for (int i=0; i<vertices.size(); i++){
                // Choose vertex 'v'
                Vertex<Tvertex,Tedge> v = vertices[i]; 

                // Iterate through all edges of 'v', return true after finding 'f'
                for (int j=0; j<v.incidentEdges().size(); j++){
                    if (v.incidentEdges()[j] == f){
                        return true;
                    }
                }
            }

            return false;
        }


        bool isIncidentOn(Vertex v){        // Return true if edge is incident on vertex 'v'
            for (int i=0; i<vertices.size(); i++){
                if (vertices[i] == v){
                    return true;
                }
            }

            return false;
        }
};

#endif