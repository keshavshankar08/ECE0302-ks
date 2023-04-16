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
    //check if connected to self
    if(start == end){
        return false;
    }

    //get start and end pos in list
    int startPos, endPos; 
    startPos = endPos = -1;
    for(int i = 0; i < list.size(); i++){
        if(list.at(i).data == start){
            startPos = i;
        }
        if(list.at(i).data == end){
            endPos = i;
        }
    }

    //check if already exists in list
    std::__wrap_iter<int *> foundStart = find(list.at(startPos).adjacencies.begin(), list.at(startPos).adjacencies.end(), start);
    std::__wrap_iter<int *> foundEnd = find(list.at(endPos).adjacencies.begin(), list.at(endPos).adjacencies.end(), end);
    if(!(foundStart == list.at(endPos).adjacencies.end()) || !(foundEnd == list.at(startPos).adjacencies.end())){
        return false;
    }

    //temp for adding
    Node<LabelType> tempNode;

    //if start not yet in list, make and connect
    if(startPos == -1){
        tempNode.data = start;
        list.push_back(tempNode);
        startPos = list.size() - 1;
    }

    //if end not yet in list, make and connect
    if(endPos == -1){
        tempNode.data = endPos;
        list.push_back(tempNode);
        endPos = list.size() - 1;
    }

    //update adjacenies
    list.at(startPos).adjacencies.push_back(end);
    list.at(endPos).adjacencies.push_back(start);

    return true;
}   

template <typename LabelType> 
bool AdjacencyListGraph<LabelType>::remove(LabelType start, LabelType end) {
    //check if connected to self
    if(start == end){
        return false;
    }

    //get start and end pos in list
    int startPos, endPos; 
    startPos = endPos = -1;
    for(int i = 0; i < list.size(); i++){
        if(list.at(i).data == start){
            startPos = i;
        }
        if(list.at(i).data == end){
            endPos = i;
        }
    }

    //if start/end in list not found
    if(startPos == -1 || endPos == -1){
        return false;
    }

    //check adjacencies of start for end
    bool removalFound = false;
    for(int i = 0; i < list.at(endPos).adjacencies.size(); i++){
        if(start == list.at(endPos).adjacencies.at(i)){
            list.at(endPos).adjacencies.erase(list.at(endPos).adjacencies.begin() + i);
            removalFound = true;
            break;
        }
    }
    for(int i = 0; i < list.at(startPos).adjacencies.size(); i++){
        if(start == list.at(startPos).adjacencies.at(i)){
            list.at(startPos).adjacencies.erase(list.at(startPos).adjacencies.begin() + i);
            removalFound = true;
            break;
        }
    }

    //check if removed properly
    if(removalFound == false){
        return false;
    }

    //removing when no adjacencies
    if(list.at(startPos).adjacencies.size() == 0){
        list.erase(list.begin() + startPos);
    }
    if(list.at(endPos).adjacencies.size() == 0){
        list.erase(list.begin() + endPos);
    }

    return true;
}


//-----BONUS-----
template <typename LabelType> 
void AdjacencyListGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&)) {}

//-----BONUS-----
template <typename LabelType> 
void AdjacencyListGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&)) {}