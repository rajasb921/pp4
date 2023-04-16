#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "graph.h"

int main(){

    Graph<std::string,std::string> g = Graph<std::string,std::string>();
    
    // Vertices
    Vertex<std::string,std::string> A("A");
    Vertex<std::string,std::string> B("B");
    Vertex<std::string,std::string> C("C");
    Vertex<std::string,std::string> D("D");
    Vertex<std::string,std::string> E("E");

    // Add vertices
    g.insertVertex(A);
    g.insertVertex(B);
    g.insertVertex(C);
    g.insertVertex(D);
    g.insertVertex(E);

    // Edges
    Edge<std::string,std::string> ab("ab");
    Edge<std::string,std::string> bc("bc");
    Edge<std::string,std::string> be("be");
    Edge<std::string,std::string> ce("ce");
    Edge<std::string,std::string> ed("ed");
    Edge<std::string,std::string> cd("cd");

    // Add edges
    g.insertEdge(A,B,ab);
    g.insertEdge(B,C,bc);
    g.insertEdge(B,E,be);
    g.insertEdge(C,E,ce);
    g.insertEdge(E,D,ed);
    g.insertEdge(C,D,cd);

    std::cout << g.numVertices() <<" Vertices:\n";
    for (int i=0; i<g.vertices().size(); i++){
        std::cout << *(g.vertices()[i]) << "\n";
    }

    std::cout << g.numEdges() <<" Edges:\n";
    for (int i=0; i<g.edges().size(); i++){
        std::cout << *(g.edges()[i]) << "\n";
    }
    return EXIT_SUCCESS;
}

/*
    // Define types
    typedef std::vector<Edge<std::string,std::string>*> el;
    typedef std::vector<Vertex<std::string,std::string>*> vl;

    // Vertices
    Vertex<std::string,std::string> A("A");
    Vertex<std::string,std::string> B("B");
    Vertex<std::string,std::string> C("C");
    Vertex<std::string,std::string> D("D");
    Vertex<std::string,std::string> E("E");

    // Edges
    Edge<std::string,std::string> ab("ab",{&A,&B});
    Edge<std::string,std::string> bc("bc",{&B,&C});
    Edge<std::string,std::string> be("be",{&B,&E});
    Edge<std::string,std::string> ce("ce",{&C,&E});
    Edge<std::string,std::string> ed("ed",{&E,&D});
    Edge<std::string,std::string> cd("cd",{&C,&D});
    
    // Connecting vertices and edges
    A.addEdge(ab);
    B.addEdge(bc);
    B.addEdge(be);
    C.addEdge(bc);
    C.addEdge(ce);
    C.addEdge(cd);
    D.addEdge(cd);
    D.addEdge(ed);
    E.addEdge(ed);
    E.addEdge(ce);
    E.addEdge(be);


    // Output
    std::cout << *ab << "\n";
    std::cout << *ab.opposite(A) << "\n";
    std::cout << ab.isAdjacentTo(bc) << "\n";
    std::cout << ab.isIncidentOn(C) << "\n";
*/