#ifndef ISR_H
#define ISR_H

#include "../graphics/VGADebug.h"

namespace ISR {  

/* src: tables.s */
// @TODO: extern "C" void resolveISR();

/* Reserved intel interrupt gates (0-31) */

void igte_DivByZero ();             // 0. Divide by zero
void igte_Debug ();                 // 1. Debug
void igte_NonMask ();               // 2. Non Maskable interrupt
void igte_Brkpt ();                 // 3. Breakpoint
void igte_IOvrflw ();               // 4. Into Detected Overflow
void igte_OutOfBounds ();           // 5. Out of bounds
void igte_BadOpcode ();             // 6. Bad ASM opcode
void igte_NoCoProc ();              // 7. No co-processor
void igte_DoubleFault ();           // 8. Double fault
void igte_CoProcSegOvrRn ();        // 9. Co-processor segment overrun
void igte_BadTSS ();                // 10. Bad TSS
void igte_NoSegment ();             // 11. Segment not present
void igte_StackFault();             // 12. Stack fault
void igte_GPFault ();               // 13. General protection fault
void igte_PageFault ();             // 14. Page fault
void igte_UnknIntrpt ();            // 15. Unknown interrupt
void igte_CoProcFlt ();             // 16. Co-processor fault
void igte_AlgnCheck ();             // 17. Alignment check
void igte_MachineCheck ();          // 18. Machine check
void igte_Reserved ();              // [19-31] Reserved interrupts.

}

#endif