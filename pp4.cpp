#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "graph.h"

int main(){
    
    // File input
    std::cout << "\nHello!\n\n";
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;
    Graph<std::string,std::string> g(filename);
    
    // Main function loop
    bool flag = true;
    while(flag){
        std::cout << "--------------------------\nWhat would you like to do?\n--------------------------\n";
        std::cout << "1. Find edges incident on a vertex\n2. Find a path in the graph\n3. Insert an edge\n4. Erase a vertex\n\n";
        int option = 0;
        while (option < 1 || option > 4){
            std::cout << "Enter option number (1-4): ";
            std::cin >> option;
            if (option == 1){
                std::string label;
                std::cout << "Enter label of vertex you would like to explore: ";
                while (label.size() == 0){
                    std::getline(std::cin,label);
                };
                g.printDetails(label);
            }else if (option == 2){
                
                // Create v1
                std::string label1;
                Vertex<std::string,std::string>* v1 = new Vertex<std::string,std::string>;
                std::cout << "Enter label of the beginning vertex: ";
                while (label1.size() == 0){
                    std::getline(std::cin,label1);
                }
                for (int i=0; i<g.numVertices(); i++){
                    if (*(*g.vertices()[i]) == label1){
                        v1 = g.vertices()[i];
                        break;
                    }
                }

                // Create v2
                std::string label2;
                Vertex<std::string,std::string>* v2 = new Vertex<std::string,std::string>;
                std::cout << "Enter label of the end vertex: ";
                while (label2.size() == 0){
                    std::getline(std::cin,label2);
                };
                for (int i=0; i<g.numVertices(); i++){
                    if (*(*g.vertices()[i]) == label2){
                        v2 = g.vertices()[i];
                        break;
                    }
                }

                // Find path 
                std::vector<Vertex<std::string,std::string>*> path = g.findPath(v1,v2);

                // Print path
                for (int i=0; i<path.size()-1; i++){
                    std::cout << *(*path[i]) << " to ";
                }
                std::cout << (*(*path[path.size()-1])) << "\n";

            }else if (option == 3){

                // Create edge
                Edge<std::string,std::string>* e = new Edge<std::string,std::string>;
                std::string edgeLabel;
                std::cout << "Enter label of the edge you would like to add: ";
                while (edgeLabel.size() == 0){
                    std::getline(std::cin,edgeLabel);
                };
                e->setEdge(edgeLabel);

                // Create vertex 1
                Vertex<std::string,std::string>* v1 = new Vertex<std::string,std::string>;
                std::string v1Label;
                std::cout << "Enter label of the first vertex: ";
                while (v1Label.size() == 0){
                    std::getline(std::cin,v1Label);
                };
                v1->setVertex(v1Label);

                // Create vertex 2
                Vertex<std::string,std::string>* v2 = new Vertex<std::string,std::string>;
                std::string v2Label;
                std::cout << "Enter label of the second vertex: ";
                while (v2Label.size() == 0){
                    std::getline(std::cin,v2Label);
                };
                v2->setVertex(v2Label);

                // Insert edge
                g.insertEdge(v1,v2,e);
                
            }else if (option == 4){

                // Create vertex
                Vertex<std::string,std::string>* v = new Vertex<std::string,std::string>;
                std::string label;
                std::cout << "Enter label of the vertex you would like to delete: ";
                while (label.size() == 0){
                    std::getline(std::cin,label);
                };
                v->setVertex(label);

                // Erase vertex
                g.eraseVertex(v);

            }else{
                std::cout << "Invalid option\n";
            }
        }
        
   
        char check;
        while (check != 'y' || check != 'n'){
            std::cout << "Would you like to continue? (y/n): ";
            std::cin >> check;
            if (check == 'n'){
                flag = false;
                break;
            }else{
                break;
            }
        }

        
    }
    
    return EXIT_SUCCESS;
}
