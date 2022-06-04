#include "ISR.h"

void ISR::igte_DivByZero () {
    VGADebug debug;
    unsigned char msg[] = "[INT0] Divide By Zero.";
    debug.Println(&msg[0], 22, 13);
}

void ISR::igte_Debug () {
    VGADebug debug;
    unsigned char msg[] = "[INT1] Debug.";
    debug.Println(&msg[0], 13, 13);
}

void ISR::igte_NonMask () {
    VGADebug debug;
    unsigned char msg[] = "[INT2] Non-maskable interrupt.";
    debug.Println(&msg[0], 30, 13);
}

void ISR::igte_Brkpt () {
    VGADebug debug;
    unsigned char msg[] = "[INT3] Breakpoint.";
    debug.Println(&msg[0], 18, 13);
}

void ISR::igte_IOvrflw () {
    VGADebug debug;
    unsigned char msg[] = "[INT4] Into detected overflow.";
    debug.Println(&msg[0], 30, 13);
}

void ISR::igte_OutOfBounds () {
    VGADebug debug;
    unsigned char msg[] = "[INT5] Out of bounds.";
    debug.Println(&msg[0], 21, 13);
}

void ISR::igte_BadOpcode () {
    VGADebug debug;
    unsigned char msg[] = "[INT6] Bad Opcode.";
    debug.Println(&msg[0], 18, 13);
}

void ISR::igte_NoCoProc () {
    VGADebug debug;
    unsigned char msg[] = "[INT7] No co-processor.";
    debug.Println(&msg[0], 23, 13);
}

void ISR::igte_DoubleFault () {
    VGADebug debug;
    unsigned char msg[] = "[INT8] Double Fault.";
    debug.Println(&msg[0], 20, 13);
}

void ISR::igte_CoProcSegOvrRn () {
    VGADebug debug;
    unsigned char msg[] = "[INT9] Co-processor Segment Overrun.";
    debug.Println(&msg[0], 36, 13);
}

void ISR::igte_BadTSS () {
    VGADebug debug;
    unsigned char msg[] = "[INT10] Bad TSS.";
    debug.Println(&msg[0],16, 13);
}

void ISR::igte_NoSegment () {
    VGADebug debug;
    unsigned char msg[] = "[INT11] Segment not Present.";
    debug.Println(&msg[0], 28, 13);
}

void ISR::igte_StackFault () {
    VGADebug debug;
    unsigned char msg[] = "[INT12] Stack Fault.";
    debug.Println(&msg[0], 20, 13);
}

void ISR::igte_GPFault () {
    VGADebug debug;
    unsigned char msg[] = "[INT13] General Protection Fault.";
    debug.Println(&msg[0], 33, 13);
}

void ISR::igte_PageFault () {
    VGADebug debug;
    unsigned char msg[] = "[INT14] Page Fault.";
    debug.Println(&msg[0], 19, 13);
}

void ISR::igte_UnknIntrpt () {
    VGADebug debug;
    unsigned char msg[] = "[INT15] Unknown Interrupt.";
    debug.Println(&msg[0], 26, 13);
}

void ISR::igte_CoProcFlt () {
    VGADebug debug;
    unsigned char msg[] = "[INT16] Co-processor Fault.";
    debug.Println(&msg[0], 27, 13);
}

void ISR::igte_AlgnCheck () {
    VGADebug debug;
    unsigned char msg[] = "[INT17] Alignment Check.";
    debug.Println(&msg[0], 24, 13);
}

void ISR::igte_MachineCheck () {
    VGADebug debug;
    unsigned char msg[] = "[INT18] Machine Check.";
    debug.Println(&msg[0], 22, 13);
}

void ISR::igte_Reserved () {
    VGADebug debug;
    unsigned char msg[] = "[INT19-31] Reserved Interrupt.";
    debug.Println(&msg[0], 30, 13);
}