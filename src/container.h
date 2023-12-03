#ifndef CONTAINER_H
#define CONTAINER_H

#include "color.h"

class Container {
public:
    // The letter that is in the container
    char letter;
    // The color of the container
    Color color;

    Container(char letter, Color color);
    Container();

private:

};

#endif