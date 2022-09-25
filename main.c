#include "include/smp.h"

static int state = 0;

int main(int argc, char *argv[]) 
{
    state = InitSystem();
    while(state) {
        EvntHandler();
        Update();
        Render();
    }
    FreeResources();
    return 0;
}
