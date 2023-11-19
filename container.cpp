#include "container.h"

Container::Container(char letter, Color color) {
    this->letter = letter;
    this->color = color;
}

Container::Container() {
    this->letter = '.';
    this->color = GREY;
}
