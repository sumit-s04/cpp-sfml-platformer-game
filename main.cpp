#include "Game.h"


int main() {
    if(!font.loadFromFile(dir_font)){ std::cerr << "Error loading font" << std::endl; }
    
    //Game game;
    run();
    return 0;
}


