#include <GL/freeglut.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

float piece_x = 5.0f;
float piece_y = 15.0f;
int piece_type = 1;
int blockType = 0;

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

// Define window dimensions
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 1200;

void drawSquare(float x, float y, float size) {
   glBegin(GL_QUADS); //This creates quadrilaterals -- We will be using this to create the shapes of the tetris figures.
   glVertex2f(x, y); //The following 4 lines are creating the 4 different sides of a quadrilateral (a square of 1 pixel*).
   glVertex2f(x + size, y);
   glVertex2f(x + size, y + size);
   glVertex2f(x, y + size);
   glEnd();
}

//------------------------------------------------------------

//Shapes for the tetris figures
void L_shape(float x, float y, float size) {
   glColor3f(0.0f, 0.0f, 1.0f);
   drawSquare(x, y, size);
   drawSquare(x, y + size, size);  
   drawSquare(x, y + 2*size, size);
   drawSquare(x + size, y, size);
}
void I_shape(float x, float y, float size) {
    glColor3f(1.0f, 0.0f, 1.0f);
    drawSquare(x, y, size);
    drawSquare(x, y + size, size);  
    drawSquare(x, y + 2*size, size);
    drawSquare(x, y + 3*size, size);
}
void O_shape(float x, float y, float size) {
    glColor3f(0.0f, 1.0f, 1.0f);
    drawSquare(x, y, size);
    drawSquare(x, y + size, size);  
    drawSquare(x + size, y, size);
    drawSquare(x + size, y + size, size);
}
void T_shape(float x, float y, float size) {
    glColor3f(1.0f, 0.0f, 0.0f);
    drawSquare(x, y, size);
    drawSquare(x + size, y, size);  
    drawSquare(x - size, y, size);
    drawSquare(x, y + size, size);
}
void S_shape(float x, float y, float size) {
    glColor3f(0.0f, 1.0f, 0.0f);
    drawSquare(x, y, size);
    drawSquare(x - size, y, size);  
    drawSquare(x, y + size, size);
    drawSquare(x + size, y + size, size);
}
void Z_shape(float x, float y, float size) {
    glColor3f(1.0f, 1.0f, 0.0f);
    drawSquare(x, y, size);
    drawSquare(x + size, y, size);  
    drawSquare(x, y + size, size);
    drawSquare(x - size, y + size, size);
}
void J_shape(float x, float y, float size) {
    glColor3f(1.0f, 0.5f, 0.0f);
    drawSquare(x, y, size);
    drawSquare(x, y + size, size);  
    drawSquare(x + size, y, size);
    drawSquare(x + 2 * size, y, size);
}

//--------------------------------------------------------


void init() {
   glClearColor(0.0, 0.0, 0.0, 0.0); //This clears all filters/colors and sets the background to black
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 10, 0, 20, -1, 1); //Specifies the size of the projection on the computer screen. 
   glMatrixMode(GL_MODELVIEW);
} //We project a black background for the base of the tetris game.

//----------------------------------------------------------

void dropBlock() {
   srand(time(0));
   blockType = rand() % 7 + 1;
   piece_x = 5.0f;
   piece_y = 15.0f;
}

//----------------------------------------------------------

void display() {
   dropBlock();
   glColor3f(1.0, 1.0, 1.0); // white color for the grid lines
   
   // draw grid lines
   glLineWidth(1.0); // 1 pixel for the width of the grid lines
   glBegin(GL_LINES); //primitive to create straight lines

   //Vertical lines---->
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

   switch (blockType) {
      case 1: I_shape(piece_x, piece_y, 1.0f);
      case 2: J_shape(piece_x, piece_y, 1.0f);
      case 3: L_shape(piece_x, piece_y, 1.0f);
      case 4: O_shape(piece_x, piece_y, 1.0f);
      case 5: S_shape(piece_x, piece_y, 1.0f);
      case 6: T_shape(piece_x, piece_y, 1.0f);
      case 7: Z_shape(piece_x, piece_y, 1.0f);
   }

   glutSwapBuffers(); //There's 2 buffers, and we are always switching them to make it work faster.
}

//---------------------------------------------------------------

void User_Input(int key, int x, int y){
   switch (key){
   case GLUT_KEY_UP:
      /* code */
      glutPostRedisplay(); //Updates the displaying image when an action has occurred.
      break;
   
   case GLUT_KEY_RIGHT:
      /* code */
      piece_x += 1.0f;
      glutPostRedisplay();
      break;

   case GLUT_KEY_LEFT:
      /* code */
      piece_x -= 1.0f;
      glutPostRedisplay();
      break;

   case GLUT_KEY_DOWN:
      /* code */ 
      piece_y -= 1.0f;
      glutPostRedisplay();
      break;
   }
}

//---------------------------------------------------------------


int main(int argc, char** argv) {

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowPosition(300, 100);
glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
glutCreateWindow("TETRIS");
init();
glutDisplayFunc(display);
glutSpecialFunc(User_Input);

glutMainLoop();
return 0;
}