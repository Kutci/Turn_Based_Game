#include "Core/GameEngine.h"

int main()
{
    GameEngine engine;
    engine.init("assets/config.txt");
    engine.run();
    return 0;
}
