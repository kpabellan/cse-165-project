#include <GL/glut.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "Main.h"

float piece_x = 1.0f;
float piece_y = 1.0f;
int blockType = 1; // 1 = I, 2 = J, 3 = L, 4 = O, 5 = S, 6 = T, 7 = Z
int pieceOrientation = 0; // 0 = original orientation, 1 = 90 degree rotation, 2 = 180 degree rotation, 3 = 270 degree rotation
int gameBoard[20][10]; // [row][column]
Shape shape = Shape::I;

using namespace std::this_thread; // Sleep_for, sleep_until
using namespace std::chrono; // Nanoseconds, system_clock, seconds

// Define window dimensions
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 1200;
const int SPAWN_INTERVAL_MS = 500;

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0); // This clears all filters/colors and sets the background to black
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 10, 0, 20, -1, 1); // Specifies the size of the projection on the computer screen. 
  glMatrixMode(GL_MODELVIEW);
}

// Draws a square at the specified location with the specified size
void drawBlock(float x, float y, float size) {
  // Draw the square
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + size, y);
  glVertex2f(x + size, y + size);
  glVertex2f(x, y + size);
  glEnd();

  // Draw the gridlines
  glColor3f(1.0, 1.0, 1.0); // Set the color to white for the gridlines
  glBegin(GL_LINE_LOOP);
  glVertex2f(x, y);
  glVertex2f(x + size, y);
  glVertex2f(x + size, y + size);
  glVertex2f(x, y + size);
  glEnd();
}

// Draws a tetromino at the specified location with the specified size
void drawTetromino(float x, float y, float size, Shape shape, int orientation) {
  Tetris tetris(shape);
  const auto & tetromino = tetris.tetrominoes[orientation];

  for (int row = 0; row < tetromino.size(); row++) {
    for (int col = 0; col < tetromino[row].size(); col++) {
      if (tetromino[row][col]) {
        glColor3f(tetris.color[0], tetris.color[1], tetris.color[2]);
        drawBlock(x + col * size, y + row * size, size);
      }
    }
  }
}

// Spawns a new block at the top of the board
void spawnTetromino() {
  srand(time(0));
  blockType = rand() % 7 + 1;
  if (blockType == 1) {
    shape = Shape::I;
  } else if (blockType == 2) {
    shape = Shape::J;
  } else if (blockType == 3) {
    shape = Shape::L;
  } else if (blockType == 4) {
    shape = Shape::O;
  } else if (blockType == 5) {
    shape = Shape::S;
  } else if (blockType == 6) {
    shape = Shape::T;
  } else if (blockType == 7) {
    shape = Shape::Z;
  }
  piece_x = 3.0f;
  piece_y = 17.0f;
}

// Checks if the block can move to the specified location
bool validMove(float x, float y, int pieceOrientation, int newOrientation, int dx, int dy, Shape shape) {
  Tetris tetris(shape);
  const auto & tetromino = tetris.tetrominoes[newOrientation];

  for (int row = 0; row < tetromino.size(); row++) {
    for (int col = 0; col < tetromino[row].size(); col++) {
      if (tetromino[row][col]) {
        float newX = x + col + dx;
        float newY = y + row + dy;

        if (newX < 0 || newX > 9 || newY < 0 || newY > 19) {
          return false; // Out of bounds
        }

        if (gameBoard[static_cast < int > (newY)][static_cast < int > (newX)]) {
          return false; // Collision with other block on the board
        }
      }
    }
  }
  return true;
}

void clearRows() {
  for (int row = 0; row < 20; row++) {
    bool rowCompleted = true;
    for (int col = 0; col < 10; col++) {
      if (gameBoard[row][col] == 0) {
        rowCompleted = false;
        break;
      }
    }

    if (rowCompleted) {
      // Shift all the rows above the completed row down by one
      for (int j = row; j < 19; j++) {
        for (int col = 0; col < 10; col++) {
          gameBoard[j][col] = gameBoard[j + 1][col];
        }
      }

      // Clear the top row
      for (int col = 0; col < 10; col++) {
        gameBoard[19][col] = 0;
      }

      // Check the same row again in case multiple rows have been completed
      --row;
    }
  }
}

void timer(int value) {
  int newOrientation = pieceOrientation;
  if (validMove(piece_x, piece_y, pieceOrientation, newOrientation, 0, -1, shape)) {
    piece_y -= 1.0f;
  } else {
    Tetris tetris(shape);
    const auto & tetromino = tetris.tetrominoes[pieceOrientation];

    for (int row = 0; row < tetromino.size(); row++) {
      for (int col = 0; col < tetromino[row].size(); col++) {
        if (tetromino[row][col]) {
          int boardRow = static_cast < int > (piece_y) + row;
          int boardCol = static_cast < int > (piece_x) + col;
          gameBoard[boardRow][boardCol] = blockType;
        }
      }
    }

    // Check if game is over
    for (int col = 0; col < 10; col++) {
      if (gameBoard[19][col] != 0) {
        exit(0);
      }
    }

    clearRows();

    spawnTetromino();
  }

  glutPostRedisplay();
  glutTimerFunc(SPAWN_INTERVAL_MS, timer, 0);
}

// Draws the board so that the user can see the blocks that have already fallen
void drawBoard(float size) {
  for (int row = 0; row < 20; row++) {
    for (int col = 0; col < 10; col++) {
      Tetris tetris(Shape::I); // Initialize the Tetris object with a default shape
      if (gameBoard[row][col]) {
        if (gameBoard[row][col] == 1) {
          tetris = Tetris(Shape::I);
        } else if (gameBoard[row][col] == 2) {
          tetris = Tetris(Shape::J);
        } else if (gameBoard[row][col] == 3) {
          tetris = Tetris(Shape::L);
        } else if (gameBoard[row][col] == 4) {
          tetris = Tetris(Shape::O);
        } else if (gameBoard[row][col] == 5) {
          tetris = Tetris(Shape::S);
        } else if (gameBoard[row][col] == 6) {
          tetris = Tetris(Shape::T);
        } else if (gameBoard[row][col] == 7) {
          tetris = Tetris(Shape::Z);
        } else {
          // No block in this cell, draw nothing
          continue;
        }
        glColor3f(tetris.color[0], tetris.color[1], tetris.color[2]);
        drawBlock(col * size, row * size, size);
      }
    }
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen before drawing the new tetromino position
  glColor3f(1.0, 1.0, 1.0); // White color for the grid lines

  // Draw grid lines
  glLineWidth(1.0);
  glBegin(GL_LINES);

  // Vertical lines
  for (int i = 0; i <= 10; i++) {
    glVertex2f(i, 0);
    glVertex2f(i, 20);
  }

  //Horizontal lines
  for (int i = 0; i <= 20; i++) {
    glVertex2f(0, i);
    glVertex2f(10, i);
  }
  glEnd();

  // Draw the board (blocks that have already fallen)
  drawBoard(1.0f);

  // Draw the current tetromino
  drawTetromino(piece_x, piece_y, 1.0f, shape, pieceOrientation);

  glutSwapBuffers();
}

void handleInput(int key, int x, int y) {
  int newOrientation = pieceOrientation;

  switch (key) {
  case GLUT_KEY_UP:
    newOrientation = (pieceOrientation + 1) % 4;
    if (validMove(piece_x, piece_y, pieceOrientation, newOrientation, 0, 0, shape)) {
      pieceOrientation = newOrientation;
    }
    glutPostRedisplay(); // Updates the displaying image when an action has occurred
    break;

  case GLUT_KEY_RIGHT:
    if (validMove(piece_x, piece_y, pieceOrientation, newOrientation, 1, 0, shape)) {
      piece_x += 1.0f;
    }
    glutPostRedisplay();
    break;

  case GLUT_KEY_LEFT:
    if (validMove(piece_x, piece_y, pieceOrientation, newOrientation, -1, 0, shape)) {
      piece_x -= 1.0f;
    }
    glutPostRedisplay();
    break;

  case GLUT_KEY_DOWN:
    if (validMove(piece_x, piece_y, pieceOrientation, newOrientation, 0, -1, shape)) {
      piece_y -= 1.0f;
    }
    glutPostRedisplay();
    break;
  }
}

int main(int argc, char ** argv) {
  glutInit( & argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(300, 100);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("TETRIS");
  init();
  spawnTetromino();
  glutDisplayFunc(display);
  glutSpecialFunc(handleInput);
  glutTimerFunc(1000, timer, 0);
  glutMainLoop();
  return 0;
}
