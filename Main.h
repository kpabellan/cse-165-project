#ifndef MAIN_H
#define MAIN_H

#include <vector>

enum Shape {
    I,
    J,
    L,
    O,
    S,
    T,
    Z
};

class getShape{
   
    Shape shp;
    public:
    Shape gettingShape(Shape xxx){
        shp = xxx;
        return shp;
    }
};

class Tetris : getShape{
    public:
        std::vector<std::vector<std::vector<int>>> tetrominoes;
        float color[3];

        Tetris(Shape shape) {
            switch (gettingShape(shape)) {
                case Shape::I:
                    color[0] = 0.678f;
                    color[1] = 0.847f;
                    color[2] = 0.902f;
                    tetrominoes = {
                        { {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0} }, // 0
                        { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} }, // 90
                        { {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0} }, // 180
                        { {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0} }  // 270
                    };
                    break;
                case Shape::J:
                    color[0] = 0.0f;
                    color[1] = 0.0f;
                    color[2] = 0.545f;
                    tetrominoes = {
                        { {0, 1, 0}, {0, 1, 0}, {1, 1, 0} }, // 0
                        { {1, 0, 0}, {1, 1, 1}, {0, 0, 0} }, // 90
                        { {0, 1, 1}, {0, 1, 0}, {0, 1, 0} }, // 180
                        { {0, 0, 0}, {1, 1, 1}, {0, 0, 1} }  // 270
                    };
                    break;
                case Shape::L:
                    color[0] = 1.0f;
                    color[1] = 0.647f;
                    color[2] = 0.0f;
                    tetrominoes = {
                        { {0, 1, 0}, {0, 1, 0}, {0, 1, 1} }, // 0
                        { {1, 1, 1}, {1, 0, 0}, {0, 0, 0} }, // 90
                        { {1, 1, 0}, {1, 0, 0}, {1, 0, 0} }, // 180
                        { {0, 0, 1}, {1, 1, 1}, {0, 0, 0} }  // 270
                    };
                    break;
                case Shape::O:
                    color[0] = 1.0f;
                    color[1] = 1.0f;
                    color[2] = 0.0f;
                    tetrominoes = {
                        { {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0} }, // 0
                        { {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0} }, // 90
                        { {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0} }, // 180
                        { {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0} }  // 270
                    };
                    break;
                case Shape::S:
                    color[0] = 0.0f;
                    color[1] = 1.0f;
                    color[2] = 0.0f;
                    tetrominoes = {
                        { {0, 1, 1}, {1, 1, 0}, {0, 0, 0} }, // 0
                        { {0, 1, 0}, {0, 1, 1}, {0, 0, 1} }, // 90
                        { {0, 0, 0}, {0, 1, 1}, {1, 1, 0} }, // 180
                        { {1, 0, 0}, {1, 1, 0}, {0, 1, 0} }  // 270
                    };
                    break;
                case Shape::T:
                    color[0] = 1.0f;
                    color[1] = 0.0f;
                    color[2] = 1.0f;
                    tetrominoes = {
                        { {0, 1, 0}, {1, 1, 1}, {0, 0, 0} }, // 0
                        { {0, 1, 0}, {0, 1, 1}, {0, 1, 0} }, // 90
                        { {0, 0, 0}, {1, 1, 1}, {0, 1, 0} }, // 180
                        { {0, 1, 0}, {1, 1, 0}, {0, 1, 0} }  // 270
                    };
                    break;
                case Shape::Z:
                    color[0] = 1.0f;
                    color[1] = 0.0f;
                    color[2] = 0.0f;
                    tetrominoes = {
                        { {1, 1, 0}, {0, 1, 1}, {0, 0, 0} }, // 0
                        { {0, 0, 1}, {0, 1, 1}, {0, 1, 0} }, // 90
                        { {0, 0, 0}, {1, 1, 0}, {0, 1, 1} }, // 180
                        { {0, 1, 0}, {1, 1, 0}, {1, 0, 0} }  // 270
                    };
                    break;
            }
        }
};



#endif


