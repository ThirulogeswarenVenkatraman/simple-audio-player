#include "include/smp.h"

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
