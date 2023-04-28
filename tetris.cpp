#include <GL/glut.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "Main.h"

float piece_x = 1.0f;
float piece_y = 1.0f;
int blockType = 0;
Tetris::Shape shape = Tetris::Shape::I;
int pieceOrientation = 0; // 0 = original orientation, 1 = 90 degree rotation, 2 = 180 degree rotation, 3 = 270 degree rotation

using namespace std::this_thread; // Sleep_for, sleep_until
using namespace std::chrono; // Nanoseconds, system_clock, seconds

// Define window dimensions
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 1200;
const int SPAWN_INTERVAL_MS = 500;

void drawSquare(float x, float y, float size) {
  glBegin(GL_QUADS); // This creates quadrilaterals -- We will be using this to create the shapes of the tetris figures.
  glVertex2f(x, y); // The following 4 lines are creating the 4 different sides of a quadrilateral (a square of 1 pixel*).
  glVertex2f(x + size, y);
  glVertex2f(x + size, y + size);
  glVertex2f(x, y + size);
  glEnd();
}

void drawTetromino(float x, float y, float size, Tetris::Shape shape, int orientation) {
  Tetris tetris(shape);
  glColor3f(tetris.color[0], tetris.color[1], tetris.color[2]);
  const auto & tetromino = tetris.tetrominoes[orientation];

  for (int row = 0; row < tetromino.size(); ++row) {
    for (int col = 0; col < tetromino[row].size(); ++col) {
      if (tetromino[row][col]) {
        drawSquare(x + col * size, y + row * size, size);
      }
    }
  }
}

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0); // This clears all filters/colors and sets the background to black
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 10, 0, 20, -1, 1); // Specifies the size of the projection on the computer screen. 
  glMatrixMode(GL_MODELVIEW);
}

void spawnBlock() {
  srand(time(0));
  blockType = rand() % 7 + 1;
  if (blockType == 0) {
    shape = Tetris::Shape::I;
  } else if (blockType == 1) {
    shape = Tetris::Shape::J;
  } else if (blockType == 2) {
    shape = Tetris::Shape::L;
  } else if (blockType == 3) {
    shape = Tetris::Shape::O;
  } else if (blockType == 4) {
    shape = Tetris::Shape::S;
  } else if (blockType == 5) {
    shape = Tetris::Shape::T;
  } else if (blockType == 6) {
    shape = Tetris::Shape::Z;
  }
  piece_x = 3.0f;
  piece_y = 17.0f;
}

bool validMove(float x, float y, int pieceOrientation, int dx, int dy, Tetris::Shape shape) {
  Tetris tetris(shape);
  const auto & tetromino = tetris.tetrominoes[pieceOrientation];

  for (int row = 0; row < tetromino.size(); ++row) {
    for (int col = 0; col < tetromino[row].size(); ++col) {
      if (tetromino[row][col]) {
        float newX = x + col + dx;
        float newY = y + row + dy;

        if (newX < 0 || newX > 9 || newY < 0 || newY > 19) {
          return false; // Out of bounds
        }
        // Check for collision code here
      }
    }
  }

  return true;
}

void timer(int value) {
  if (validMove(piece_x, piece_y, pieceOrientation, 0, -1, shape)) {
    piece_y -= 1.0f;
  }

   if (piece_y <= 0.0f) {
    spawnBlock();
  }

  glutPostRedisplay();
  glutTimerFunc(SPAWN_INTERVAL_MS, timer, 0);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT); // Clear the screen before drawing the new tetromino position
  glColor3f(1.0, 1.0, 1.0); // White color for the grid lines

  // Draw grid lines
  glLineWidth(1.0); // 1 pixel for the width of the grid lines
  glBegin(GL_LINES); // primitive to create straight lines

  // Vertical lines
  for (int i = 0; i <= 10; i++) {
    glVertex2f(i, 0);
    glVertex2f(i, 20);
  }

  //Horizontal Lines---->
  for (int i = 0; i <= 20; i++) {
    glVertex2f(0, i);
    glVertex2f(10, i);
  }
  glEnd();

  drawTetromino(piece_x, piece_y, 1.0f, shape, pieceOrientation);

  glutSwapBuffers();
}

void handleInput(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_UP:
    pieceOrientation = (pieceOrientation + 1) % 4;
    glutPostRedisplay(); // Updates the displaying image when an action has occurred
    break;

  case GLUT_KEY_RIGHT:
    if (validMove(piece_x, piece_y, pieceOrientation, 1, 0, shape)) {
      piece_x += 1.0f;
    }
    glutPostRedisplay();
    break;

  case GLUT_KEY_LEFT:
    if (validMove(piece_x, piece_y, pieceOrientation, -1, 0, shape)) {
      piece_x -= 1.0f;
    }
    glutPostRedisplay();
    break;

  case GLUT_KEY_DOWN:
    if (validMove(piece_x, piece_y, pieceOrientation, 0, -1, shape)) {
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
  spawnBlock();
  glutDisplayFunc(display);
  glutSpecialFunc(handleInput);
  glutTimerFunc(1000, timer, 0);
  glutMainLoop();
  return 0;
}