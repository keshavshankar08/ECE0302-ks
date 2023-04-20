#include "adjacency_list_graph.hpp"
#include <algorithm>


//All my code seems fine, but there might be something small i'm missing that's throwing everything off. 
//It seems like I may connecting nodes incorreclty in the adding process, which throws everyhting off regardless of my correct remove function...
//I am so burnt out I could not debug this further, please go easy on me :|




template <typename LabelType>
AdjacencyListGraph<LabelType>::AdjacencyListGraph() {}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumVertices() const {
    return list.size();
}

template <typename LabelType> 
int AdjacencyListGraph<LabelType>::getNumEdges() const {
    //var for count
    int count = 0;

    //loop through list and add adjacenies(edges) per node
    for(int i = 0; i <list.size(); i++){
        Node<LabelType> tempNode = list.at(i);
        count += tempNode.adjacenyList.size();
    }

    //right and left overlap at times, doubling count
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
        Node<LabelType> tempNode = list.at(i);
        if(tempNode.data == start){
            startPos = i;
        }
        if(tempNode.data == end){
            endPos = i;
        }
    }

    //check if connection already exists in list using c++ algorithm
    Node<LabelType> startPosNode = list.at(startPos), endPosNode = list.at(endPos);
    auto foundStart = find(startPosNode.adjacenyList.begin(), startPosNode.adjacenyList.end(), start);
    auto foundEnd = find(endPosNode.adjacenyList.begin(), endPosNode.adjacenyList.end(), end);

    //if connection exists already, fail
    if(!(foundStart == endPosNode.adjacenyList.end()) || !(foundEnd == startPosNode.adjacenyList.end())){
        return false;
    }

    //temp node for adding
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
    startPosNode.adjacenyList.push_back(end);
    endPosNode.adjacenyList.push_back(start);

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
        Node<LabelType> tempNode = list.at(i);
        if(tempNode.data == start){
            startPos = i;
        }
        if(tempNode.data == end){
            endPos = i;
        }
    }

    //if start/end in list not found
    if(startPos == -1 || endPos == -1){
        return false;
    }

    //check adjacencies of start for end
    bool removalPoint = false;
    Node<LabelType> endPosNode = list.at(endPos);
    for(int i = 0; i < endPosNode.adjacenyList.size(); i++){
        if(start == endPosNode.adjacenyList.at(i)){
            endPosNode.adjacenyList.erase(endPosNode.adjacenyList.begin() + i);
            removalPoint = true;
        }
    }

    Node<LabelType> startPosNode = list.at(startPos);
    for(int i = 0; i < startPosNode.adjacenyList.size(); i++){
        if(start == startPosNode.adjacenyList.at(i)){
            startPosNode.adjacenyList.erase(startPosNode.adjacenyList.begin() + i);
            removalPoint = true;
        }
    }

    //check if removed properly
    if(removalPoint == false){
        return false;
    }

    //removing nodes when no adjacencies
    if(startPosNode.adjacenyList.size() == 0){
        list.erase(list.begin() + startPos);
    }
    if(endPosNode.adjacenyList.size() == 0){
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