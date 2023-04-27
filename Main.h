#ifndef MAIN_H
#define MAIN_H

#include <iostream>


using namespace std;
const int gridSize = 10;

enum BlockType {
    I_BLOCK,
    J_BLOCK,
    L_BLOCK,
    O_BLOCK,
    S_BLOCK,
    T_BLOCK,
    Z_BLOCK
};

 int BLOCK_SIZES[7] = {
    4,  // I_BLOCK
    3,  // J_BLOCK
    3,  // L_BLOCK
    2,  // O_BLOCK
    3,  // S_BLOCK
    3,  // T_BLOCK
    3   // Z_BLOCK
};



class GameBoard {

  
  private:
  static const int blockSize = 20;// each block has the same size we are using 20 as a place holder 
    static const int width = 20;
    static const int height = 20;
    BlockType blocks[width][height];
    int score;
    int level;
    int numRowsCleared; 

  public:    

    // Constructor
   // Constructor
    GameBoard() : score(0), level(0), numRowsCleared(0) {
        // Initialize all blocks to NULL
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                blocks[x][y] == NULL;
            }
        }
    }  
    // Getters and setters
    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    BlockType getBlock(int x, int y){
        return blocks[x][y];
    }

    int getScore(){
        return score;
    }

    int getLevel(){
        return level;
    }
    int getNumRowsCleared() {
        return numRowsCleared;
    }
    void setBlock(int x, int y, BlockType type);

    void setScore(int s){
        score = s;
    }
    void setLevel(int l){
        level = l;
    }
    void setNumRowsCleared(int nrc){
        numRowsCleared = nrc;
    }

    // Methods
    bool isGameOver() const {
        // Check if top row is filled with blocks
        for (int x = 0; x < width; ++x) {
            if (!isBlockEmpty(x, 0)) {
                return true; // Game is over
            }
        }
        return false; // Game is not over
    }

    bool isBlockEmpty(int x, int y) const {
        // Check if block is out of bounds or cell is empty
        if (x < 0 || x >= width|| y < 0 || y >= height) {
            return true; // Block is out of bounds
        } else {
            return (blocks[x][y] == NULL);
        }
    }

    bool isRowComplete(int y) const {
        // Check if all cells in row are occupied by blocks
        for (int x = 0; x < width; ++x) {
            if (blocks[x][y] == NULL) {
                return false; // Row is not complete
            }
        }
        return true; // Row is complete
    }

 void clearRow(int y) {
    // Clear all cells in the row
    for (int x = 0; x < width; ++x) {
        blocks[x][y] == NULL;
    }
}

void clearRows() {
    // Check each row for completion and clear completed rows
    for (int y = 0; y < height; ++y) {
        if (isRowComplete(y)) {
            clearRow(y);
        }
    }
}

    void placeBlock( Block& block) {
        // Check if block can be placed at current position
        for (int x = 0; x < blockSize; ++x) {
            for (int y = 0; y < blockSize; ++y) {
                if (block.isCellOccupied(x, y)) {
                    int boardX = block.getX() + x;
                    int boardY = block.getY() + y;
                    if (!isBlockEmpty(boardX, boardY)) {
                        // Block cannot be placed at current position
                        // End the game or move the block to a different position
                        return;
                    }
                }
            }
        }

        // Place the block on the game board
        for (int x = 0; x < blockSize; ++x) {
            for (int y = 0; y < blockSize; ++y) {
                if (block.isCellOccupied(x, y)) {
                    int boardX = block.getX() + x;
                    int boardY = block.getY() + y;
                    blocks[boardX][boardY] == block.getType() ;
                }
            }
        }

        
    }
};

class Block:GameBoard {
    private:
    int x;
    int y;
    BlockType type;
  public:
    // Constructor
    Block(int a, int b, BlockType blockType){
        x = a;
        y = b;
        type = blockType;
    }
   int  getBlockSize(BlockType a){
       if (a == I_BLOCK){
           return BLOCK_SIZES[0];
       }
       if (a == J_BLOCK){
           return BLOCK_SIZES[1];
       }
       if (a == L_BLOCK){
           return BLOCK_SIZES[2];
       }
       if (a == O_BLOCK){
           return BLOCK_SIZES[3];
       }
       if (a == S_BLOCK){
           return BLOCK_SIZES[4];
       }
       if (a == T_BLOCK){
           return BLOCK_SIZES[5];
       }
       if (a == Z_BLOCK){
           return BLOCK_SIZES[6];
       }
    }
    // Getters and setters
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }

    int getType(){
        return type;
    }

    void setX(int a){
        x = a;
    }
    void setY(int b){
        y = b;
    }
  


    // Methods
    void move(int a, int b){
        x=a;
        y=b;
    }

    void rotateClockwise(){
        x += 1;
        y -= 1;
    }
    void rotateCounterClockwise(){
        x -= 1;
        y += 1;
    }

    bool isCellOccupied(int a, int b)  {
    // Calculate the coordinates of the cell within the block's shape
    int cellX = a - x;
    int cellY = b - y;

    // Check if the cell is within the bounds of the block's shape
    if (cellX < 0 || cellX >= getBlockSize(type)|| cellY < 0 || cellY >= getBlockSize(type)) {
        return false;
    }

    // Check if the cell is occupied by a block piece
    return (getBlock(a, b)!= NULL);
}

 bool checkCollision(GameBoard& gameBoard, int x, int y)  {
    // Check if block is out of bounds
    if (x < 0 || x >= gameBoard.getWidth() || y < 0 || y >= gameBoard.getHeight()) {
        return true;
    }

    // Check if block overlaps with other blocks on the game board
    for (int i = 0; i < getBlockSize(type); ++i) {
        for (int j = 0; j < getBlockSize(type); ++j) {
            if (isCellOccupied(i, j)) {
                int boardX = x + i;
                int boardY = y + j;
                if (boardX < 0 || boardX >= gameBoard.getWidth() || boardY < 0 || boardY >= gameBoard.getHeight()) {
                    // Block is out of bounds
                    return true;
                }
                if (gameBoard.isCellOccupied(boardX, boardY)) {
                    // Block overlaps with another block on the game board
                    return true;
                }
            }
        }
    }

    return false;
}
  
};

class Player  {
  private:
    int score;
    int level;
    int numRowsCleared;
    Block currentBlock;
    Block nextBlock;
    int timeToMove;
  public:
    // Constructor
    Player(GameBoard& gameBoard);

  // Getters and setters
    int getScore() {
        return score;
    }

    int getLevel() {
        return level;
    }

    int getNumRowsCleared() {
        return numRowsCleared;
    }

    Block getCurrentBlock() {
        return currentBlock;
    }

    Block getNextBlock() {
        return nextBlock;
    }
    int getTimeToMove() {
        return timeToMove;
    }

    void setScore(int s){
        score = s;
    }

    void setLevel(int l){
        level = l;
    }
    void setNumRowsCleared(int nrc){
        numRowsCleared = nrc;
    }
    void setCurrentBlock( Block& block){
        currentBlock = block;
    }
    void setNextBlock( Block& block){
        nextBlock = block;
    }

    void setTimeToMove(int t2m){
        timeToMove = t2m;
    }

   // Methods
    bool canMoveCurrentBlock(int dx, int dy)  {
    // Check if the current block is within the boundaries of the grid
    if (currentBlock.getX() + dx < 0 || currentBlock.getX() + dx >= gridSize ||
        currentBlock.getY() + dy < 0 || currentBlock.getY() + dy >= gridSize) {
        return false;
    }
    
    // Check if the destination cell is empty
      return (currentBlock.isCellOccupied(dx,dy));



}   
bool canRotateCurrentBlockClockwise()  {
    // Check if the current block can be rotated clockwise without colliding with anything
    Block rotated = currentBlock;
    rotated.rotateClockwise();
    return !checkCollision(rotated);
}

bool canRotateCurrentBlockCounterClockwise()  {
    // Check if the current block can be rotated counterclockwise without colliding with anything
    Block rotated = currentBlock;
    rotated.rotateCounterClockwise();
    return !checkCollision(rotated);
}

void moveCurrentBlock(int dx, int dy) {
    // Move the current block by the given displacement (dx, dy) if possible
        currentX = currentBlock.getX();
        currentY = currentBlock.getY();
    if (!checkCollision(currentBlock, currentX + dx, currentY + dy)) {
        currentX += dx;
        currentY += dy;
    }
}

void rotateCurrentBlockClockwise() {
    // Rotate the current block clockwise if possible
    
    if (canRotateCurrentBlockClockwise()) {
        currentBlock.rotateClockwise();
    }
}

void rotateCurrentBlockCounterClockwise() {
    // Rotate the current block counterclockwise if possible
    if (canRotateCurrentBlockCounterClockwise()) {
        currentBlock.rotateCounterClockwise();
    }
}

void dropCurrentBlock() {
    // Drop the current block as far as possible
         currentX = currentBlock.getX();
        currentY = currentBlock.getY();
    while (!checkCollision(currentBlock, currentX,currentY + 1)) {
        currentY++;
    }
}

void updateScore(int numRowsCleared) {
    // Update the score based on the number of rows cleared
    if (numRowsCleared > 0) {
        score += pow(2, numRowsCleared) * 100;
    }
}


};

#endif


