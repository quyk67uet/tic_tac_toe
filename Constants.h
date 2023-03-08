#ifndef CONSTANT_H_
#define CONSTANT_H_

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int BOARD_EDGE_LENGTH = 300;

const int BOX_EDGE_LENGTH = 100;

enum LBox
{
    EMPTY_BOX,
    PRESSING_BOX,
    X_TICKED_BOX,
    O_TICKED_BOX,
    TOTAL_BOX
};

#endif // CONSTANT_H_
