#ifndef _SORT_HPP
#define _SORT_HPP

#include "linked_list.hpp"
#include <algorithm>

template<typename T> LinkedList<T> sort(LinkedList<T> list)
{	
	//create blank array with same size as linked list
	T listCopy[list.getLength()];

	//copy over elements from linked list to array
	for(int i = 0; i < list.getLength(); i++){
		listCopy[i] = list.getEntry(i);
	}

	//sort the array using quick sort algorithm
	int a, b, minPos; 
	int n = sizeof(listCopy)/sizeof(listCopy[0]); 

	//loop over array
    for(a = 0; a < n - 1; a++){
        minPos = a; 
		//loop over elements past current element
        for(b = a+1; b < n; b++){
			//set as min element if less than other elements
        	if(listCopy[b] < listCopy[minPos]){
				minPos = b;
			}
        }
		//swap the vars at the positions
        if(minPos != a){
			int temp = listCopy[minPos]; 
			listCopy[minPos] = listCopy[a]; 
			listCopy[a] = temp; 
		}
    }

	//convert the regular array back to linked list
	for(int i = 0; i < list.getLength(); i++){
		list.setEntry(i, listCopy[i]);
	}

	return list;
}

#endif
