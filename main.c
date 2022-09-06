#include "include/smp.h"

int main(int argc, char *argv[]) 
{
    state = InitSystem();
    while(state) {
        EvntHandler();
        Render();
    }
    FreeResources();
    return 0;
}
