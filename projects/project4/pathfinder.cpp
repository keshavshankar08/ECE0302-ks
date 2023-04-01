#include <cstdlib>
#include <iostream>
#include "lib/image.h"
#include "list.hpp"
#include "queue.hpp"
#include "vector"
#include <algorithm>
#include <chrono>

//structure for current state node (holds coordinates of node)
struct currState{
  int x, y;
};

//-----main-----
int main(int argc, char *argv[])
{
  // get input/output file names from command line arguments
  if (argc != 3) {
    std::cout << "Usage: pathfinder "
              << "<first_input_filename> <second_output_filename>\n"
              << std::endl;
    return EXIT_FAILURE;
  }
  std::string input_file = argv[1];
  std::string output_file = argv[2];
  // Read input image from file
  Image<Pixel> image = readFromFile(input_file);
  int imageHeight = image.height();
  int imageWidth = image.width();

  //----------FINDING START POSITION----------
  //Variables for position
  int startX, startY, numStarts = 0;//y is rows, x is cols
  //Find the start position
  for(int row = 0; row < image.height(); row++){
    for(int col = 0; col < image.width(); col++){
      //set start cords if pixel red
      if(image(row,col) == RED){
        startX = col;
        startY = row;
        numStarts++;
      }
      //check for more than one start or non red, black, white pixels
      if(numStarts > 1 || (image(row,col) != BLACK && image(row,col) != WHITE && image(row,col) != RED)){
        return EXIT_FAILURE;
      }
    }
  }
  //check start point exists
  if(numStarts == 0){
    return EXIT_FAILURE;
  }

  //----------BREADTH FIRST SEARCH----------
  Queue<currState, List<currState> > frontier;//var for unexplored nodes
  bool exploredArr[imageHeight][imageWidth];//var for explored nodes
  for(int m = 0; m < imageHeight; m++){
    for(int n = 0; n < imageWidth; n++){
      exploredArr[m][n] = false;
    }
  }

  //add the starting position to queue
  currState startingPos;
  startingPos.x = startX;//x is col, y is row
  startingPos.y = startY;
  frontier.enqueue(startingPos);
  
  //while queue isnt empty
  while(frontier.isEmpty() == false){
    //get current node from frontier
    currState curNode = frontier.peekFront();
    frontier.dequeue();

    //checking if goal reached on left side
    if((curNode.x == 0) || (curNode.x == image.width() - 1) || (curNode.y == 0) || (curNode.y == image.height() - 1)){
      if(exploredArr[curNode.y][curNode.x + 1]){
        image(curNode.y, curNode.x) = GREEN;
        break;
      }
    }
    
    //if not at goal yet and not at edge, keep searching
    //temp vars for surrounding nodes
    currState up, right, down, left;

    //auto start = std::chrono::high_resolution_clock::now();
    //get surrounding squares coordinates
    up.x = curNode.x;
    up.y = curNode.y - 1;
    down.x = curNode.x;
    down.y = curNode.y + 1;
    left.x = curNode.x - 1;
    left.y = curNode.y;
    right.x = curNode.x + 1;
    right.y = curNode.y;
    //auto end = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    //std::cout << duration.count() << std::endl;

    //check up for unexplored node
    if((image(up.y, up.x) == WHITE) && !exploredArr[up.y][up.x]){
      frontier.enqueue(up);
    }

    //check down for unexplored node
    if(image(down.y, down.x) == WHITE && !exploredArr[down.y][down.x]){
      frontier.enqueue(down);
    }

    //check left for unexplored node
    if(image(left.y, left.x) == WHITE && !exploredArr[left.y][left.x]){
      frontier.enqueue(left);
    }

    //check right for unexplored node
    if(image(right.y, right.x) == WHITE && !exploredArr[right.y][right.x]){
      frontier.enqueue(right);
    }
    

    //make frontier node explored and remove it from the queue
    exploredArr[curNode.y][curNode.x] = true;
  }

  // Write solution image to file
  writeToFile(image, output_file);

  //frontier empty and no exits found
  return EXIT_SUCCESS;
}