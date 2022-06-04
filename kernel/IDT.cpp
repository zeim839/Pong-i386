#include "IDT.h"

IDT::GATE  Table[256];                                // IDT entries for interrupts [0, 255]
IDT::DESC  Desc;  

void IDT::setGate (
    size_t id,
    unsigned char flags,
    unsigned int fnPtr
) {
  Table[id].BASE_LOW = (unsigned short)(fnPtr & 0xFFFF);
  Table[id].SEL = CODE_SEL;
  Table[id].ZEROS = 0;
  Table[id].FLAGS = flags;
  Table[id].BASE_HIGH = (unsigned short)((fnPtr >> 16) & 0xFFFF);
}

void IDT::clearTable () {
    unsigned int* ptr = (unsigned int*)&Table[0];
    for (size_t i = 0; i<256; i++) {
        *ptr = 0;
        ptr++;
    }
}

void IDT::setIDT () {
    initDefaultISR();
    
    Desc.LIMIT = TABLE_SIZE - 1;
    Desc.BASE = (unsigned int) &Table;

    __asm__ volatile ("lidt %0" : : "m"(Desc));
}

void IDT::initDefaultISR () {
  setGate(0, 0x8E, (unsigned int)ISR::igte_DivByZero);
  setGate(1, 0x8E, (unsigned int)ISR::igte_Debug);
  setGate(2, 0x8E, (unsigned int)ISR::igte_NonMask);
  setGate(3, 0x8E, (unsigned int)ISR::igte_Brkpt);
  setGate(4, 0x8E, (unsigned int)ISR::igte_IOvrflw);
  setGate(5, 0x8E, (unsigned int)ISR::igte_OutOfBounds);
  setGate(6, 0x8E, (unsigned int)ISR::igte_BadOpcode);
  setGate(7, 0x8E, (unsigned int)ISR::igte_NoCoProc);
  setGate(8, 0x8E, (unsigned int)ISR::igte_DoubleFault);
  setGate(9, 0x8E, (unsigned int)ISR::igte_CoProcSegOvrRn);
  setGate(10, 0x8E, (unsigned int)ISR::igte_BadTSS);
  setGate(11, 0x8E, (unsigned int)ISR::igte_NoSegment);
  setGate(12, 0x8E, (unsigned int)ISR::igte_StackFault);
  setGate(13, 0x8E, (unsigned int)ISR::igte_GPFault);
  setGate(14, 0x8E, (unsigned int)ISR::igte_PageFault);
  setGate(15, 0x8E, (unsigned int)ISR::igte_UnknIntrpt);
  setGate(16, 0x8E, (unsigned int)ISR::igte_CoProcFlt);
  setGate(17, 0x8E, (unsigned int)ISR::igte_AlgnCheck);
  setGate(18, 0x8E, (unsigned int)ISR::igte_MachineCheck);
  setGate(19, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(20, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(21, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(22, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(23, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(24, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(25, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(26, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(27, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(28, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(29, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(30, 0x8E, (unsigned int)ISR::igte_Reserved);
  setGate(31, 0x8E, (unsigned int)ISR::igte_Reserved);
}