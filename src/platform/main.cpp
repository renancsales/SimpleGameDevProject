
#include <game.h>
#include <asserts.h>


int main(int argc, const char * argv[])
{
#if PRODUCTION_BUILD == 1
    SetTraceLogLevel(LOG_NONE);
#endif

    Game game("Game", 800, 600);
    game.Run();

    return 0;
}
