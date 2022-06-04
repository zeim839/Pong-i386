#if defined(__linux__)
#error "Pong-i386 must be compiled with an i386 cross-compiler."
#endif
 
#if !defined(__i386__)
#error "Pong-i386 must be compiled with an i386 cross-compiler."
#endif

#include "../graphics/VGADebug.h"
#include "GDT.h"
#include "IDT.h"

void kernelMain (void) {
    VGADebug vga;
    vga.Clear();

    unsigned char KERNEL_START[] = "[info] Kernel started";
    vga.Println(&KERNEL_START[0], 25);

    GDT::loadGDTP();

    unsigned char GDT_SUCCESS[] = "[info] GDT Installed";
    vga.Println(&GDT_SUCCESS[0], 20);
    
    IDT::clearTable();
    IDT::setIDT();
    
    unsigned char IDT_SUCCESS[] = "[info] IDT Installed";
    vga.Println(&IDT_SUCCESS[0], 20);
}

extern "C" {
    void kernelEntry (void) { kernelMain(); }
}