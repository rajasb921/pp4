#ifndef VERTEX_H
#define VERTEX_H
#include <cstdlib>
#include <vector>
#include "edge.h"
      
// Vertex Object
template <typename Tvertex, typename Tedge>
class Vertex{
    private:
        Tvertex v;
        typedef std::vector<Edge<Tvertex,Tedge>> EdgeList;    // Define type vector of edges
        EdgeList edges;
    public:
        Vertex(Tvertex _v , EdgeList _edges){    // Constructor
            v = _v;
            edges = _v;
        }

        Tedge operator*(){                      // Dereference
            return v;
        }

        EdgeList incidentEdges(){               // Return incident edges
            return edges; 
        }

        bool isAdjacentTo(Vertex _v){            // Return true if vertex is adjacent to given vertex 'v'
            
            if (v = _v){
                return false;        // Vertex is NOT adjacent to itself
            }
            
            for(int i=0; i<edges.size(); i++){
                // Choose edge 'e'
                Edge<Tvertex,Tedge> e = edges[i];

                // Iterate through end vertices of 'e' , return true after finding 'v'
                for (int j=0; j<e.endVertices().size(); j++){
                    if(e.endVertices()[j] == _v){
                        return true;
                    }
                }
            }
            
            return false;
        }
};

#endif