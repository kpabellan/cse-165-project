#include <GL/freeglut.h>

// Define window dimensions
const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 600;

void init() {
   glClearColor(0.0, 0.0, 0.0, 0.0); //Black Background for the square of the Tetris Game
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 10, 0, 20, -1, 1); //Specifies the size of the projection on the computer screen. 
   glMatrixMode(GL_MODELVIEW);
}

void drawSquare(float x, float y, float size) {
   glBegin(GL_QUADS); //This creates quadrilaterals -- We will be using this to create the game board (just a big square). We will also be using this to create the shapes of the tetris figures.
   glVertex2f(x, y); //The following 4 lines are creating the 4 different sides of a quadrilateral.
   glVertex2f(x + size, y);
   glVertex2f(x + size, y + size);
   glVertex2f(x, y + size);
   glEnd();
}


void display() {
   //glClear(GL_COLOR_BUFFER_BIT);
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

   glutSwapBuffers(); //There's 2 buffers, and we are always switching them to make it work faster.
}


int main(int argc, char** argv) {

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowPosition(300, 100);
glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
glutCreateWindow("TETRIS");
init();
glutDisplayFunc(display);

glutMainLoop();
return 0;
}