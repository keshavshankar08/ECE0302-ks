#include "adjacency_matrix_graph.hpp"


//Im mentally done and did not have the will to continue.



template <typename LabelType>
AdjacencyMatrixGraph<LabelType>::AdjacencyMatrixGraph() {}

template <typename LabelType> 
int AdjacencyMatrixGraph<LabelType>::getNumVertices() const {
    return verticies.size();
}

template <typename LabelType> 
int AdjacencyMatrixGraph<LabelType>::getNumEdges() const {
    int count = 0;
    for(int i = 0; i < edges.size(); i++){
        for(int j = 0; j < edges.at(i).size(); j++){
            if(edges.at(i).at(j) == true){
                count++;
            }
        }
    }

    return count;
}

template <typename LabelType> 
bool AdjacencyMatrixGraph<LabelType>::add(LabelType start, LabelType end) {
    return true;
}   

template <typename LabelType> 
bool AdjacencyMatrixGraph<LabelType>::remove(LabelType start, LabelType end) {
    return true;
}

template <typename LabelType> 
void AdjacencyMatrixGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

template <typename LabelType> 
void AdjacencyMatrixGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}