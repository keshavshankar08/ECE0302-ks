#include "adjacency_list_graph.hpp"

template <typename LabelType>
AdjacencyListGraph<LabelType>::AdjacencyListGraph() {}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumVertices() const {
    return list.size();
}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumEdges() const {
    //count var
    int count = 0;

    //loop through list and add adjacenies(edges) per node
    for(Node<LabelType> tempNode : list){
        count += tempNode.adjacencies.size();
    }

    //fix right count then left same count
    count /= 2;

    return count;
}
        
template <typename LabelType> 
bool AdjacencyListGraph<LabelType>::add(LabelType start, LabelType end) {
    
}   

template <typename LabelType> 
bool AdjacencyListGraph<LabelType>::remove(LabelType start, LabelType end) {}

template <typename LabelType> 
void AdjacencyListGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

template <typename LabelType> 
void AdjacencyListGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}