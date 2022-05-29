#include "../graphics/VGADebug.h"
#include "GDT.h"

void kernelMain (void) {
    VGADebug vga;
    vga.Clear();

    unsigned char KERNEL_START[] = "[info] Kernel started";
    vga.Println(&KERNEL_START[0], 25);

    GDT::loadGDTP();

    unsigned char GDT_SUCCESS[] = "[info] GDT Installed";
    vga.Println(&GDT_SUCCESS[0], 20);

}

extern "C" {
    void kernelEntry (void) { kernelMain(); }
}