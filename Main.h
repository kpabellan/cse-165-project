#ifndef MAIN_H
#define MAIN_H

#include <iostream>

using namespace std;

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
    void move(int first, int second);
    void rotate();

  
};

class GameBoard {

  private:
    int width;
    int height;
    int* blocks;
    int score;
  public:
    // Constructor
    GameBoard();

    // Getters and setters
    int getWidth();
    int getHeight();
    int getBlock(int x, int y);
    int getScore();
    void setBlock(int x, int y, int type);
    void setScore(int score);

    // Methods
    bool isGameOver();
    void clearRows();

};

class Player {
  private:
    int score;
    int level;
    Block currentBlock;
    Block nextBlock;
  public:
    // Constructor
    Player();

    // Getters and setters
    int getScore();
    int getLevel();
    Block getCurrentBlock();
    Block getNextBlock();
    void setScore(int score);
    void setLevel(int level);
    void setCurrentBlock(Block block);
    void setNextBlock(Block block);

    // Methods
    void moveCurrentBlock(int dx, int dy);
    void rotateCurrentBlock();
    void dropCurrentBlock();
    void updateScore(int rowsCleared);


};

#endif
