#include <iostream>
#include "src/gameClasses/Game.h"

int main(int argc, char* argv[]) {


    Game game{};

    // TODO: change to constructor
    int err = game.start(argc, argv);
    if (err == -1) {
        std::cout << "Error to start!" << std::endl;
        return 1;
    }

    return 0;
}