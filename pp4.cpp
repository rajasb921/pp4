#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "graph.h"

int main(){

    std::string filename;

    std::cout << "Hello!\n";
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    Graph<std::string,std::string> G(filename);

    std::cout << "Thank you. Your graph is ready.\n"
    "------------\n"
    "What would you like to do?\n"
    "------------\n"

    "1. Find edges incident on a vertex\n"
    "2. Find a path in the graph\n"
    "3. Insert an edge\n"
    "4. Erase a vertex\n"
    "5. Quit program\n";

    int choice = 0;
    while (choice != 5){
        
        std::cout << "Input: ";
        std::cin >> choice;
        switch (choice){
            case 1:
                std::cout << "case 1\n";
                break;
            case 2:
                std::cout << "case 2\n";
                break;
            case 3:
                std::cout << "case 3\n";
                break;
            case 4:
                std::cout << "case 4\n";
                break;
            case 5:
                std::cout << "case 5\n";
                break;
            default:
                std::cout << "Invalid input. Try again.\n";
                break;


        }
    }

    std::cout << G.numVertices() <<" Vertices:\n";
    for (size_t i=0; i<G.vertices().size(); i++){
        std::cout << *(G.vertices()[i]) << "\n";
    }

    std::cout << G.numEdges() <<" Edges:\n";
    for (size_t i=0; i<G.edges().size(); i++){
        std::cout << *(G.edges()[i]) << "\n";
    }

    Graph<std::string, float> graph1("input.txt");

    std::cout << "\nIN MAIN: ALL VERTICIES IN Graph::vertex_list:\n";
    for (size_t i = 0; i < graph1.numVertices(); ++i){
        std::cout << *(graph1.vertices()[i]) << std::endl;
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