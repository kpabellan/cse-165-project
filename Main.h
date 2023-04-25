#ifndef MAIN_H
#define MAIN_H

#include <iostream>

using namespace std;

enum BlockType {
  I_BLOCK,
  J_BLOCK,
  L_BLOCK,
  O_BLOCK,
  S_BLOCK,
  T_BLOCK,
  Z_BLOCK
};

class Block {
    private:
    int x;
    int y;
    int type;
  public:
    // Constructor
    Block(int a, int b, int blockType);

    // Getters and setters
    int getX();
    int getY();
    int getType();
    void setX(int a);
    void setY(int b);

    // Methods
    void move(int x, int y);
    void rotateClockwise();
    void rotateCounterClockwise();

  
};

class GameBoard {

  
    
  public:
    // Constants
    static const int WIDTH = 10;
    static const int HEIGHT = 20;

    // Constructor
    GameBoard();

     public:
    // Constants
    static const int WIDTH = 10;
    static const int HEIGHT = 20;

    // Constructor
    GameBoard();

    // Getters and setters
    int getWidth() const;
    int getHeight() const;
    BlockType getBlock(int x, int y) const;
    int getScore() const;
    int getLevel() const;
    int getNumRowsCleared() const;
    void setBlock(int x, int y, BlockType type);
    void setScore(int score);
    void setLevel(int level);
    void setNumRowsCleared(int numRowsCleared);

    // Methods
    bool isGameOver() const;
    bool isBlockEmpty(int x, int y) const;
    bool isRowComplete(int y) const;
    void clearRow(int y);
    void clearRows();
    void placeBlock(const Block& block);
    private:
    BlockType blocks_[WIDTH][HEIGHT];
    int score;
    int level;
    int numRowsCleared;

  

};

class Player {
  private:
    int score;
    int level;
    int numRowsCleared;
    Block currentBlock;
    Block nextBlock;
    int timeToMove;
  public:
    // Constructor
    Player();

  // Getters and setters
    int getScore() const;
    int getLevel() const;
    int getNumRowsCleared() const;
    Block getCurrentBlock() const;
    Block getNextBlock() const;
    int getTimeToMove() const;
    void setScore(int score);
    void setLevel(int level);
    void setNumRowsCleared(int numRowsCleared);
    void setCurrentBlock(const Block& block);
    void setNextBlock(const Block& block);
    void setTimeToMove(int timeToMove);

   // Methods
    bool canMoveCurrentBlock(int dx, int dy) const;
    bool canRotateCurrentBlockClockwise() const;
    bool canRotateCurrentBlockCounterClockwise() const;
    void moveCurrentBlock(int dx, int dy);
    void rotateCurrentBlockClockwise();
    void rotateCurrentBlockCounterClockwise();
    void dropCurrentBlock();
    void updateScore(int numRowsCleared);


};

#endif
