/* Most keyboards writing to the 8042 keyboard controller are at the very
least capable of acknowledging PS/2 commands. This driver implements the
PS/2 protocol to the extent necessary by the game loop; it is interrupt
driven but writes incoming IRQ data to a buffer variable, which the game
loop queries iteratively. This approach synchronizes IRQs with the game
loop without the added complexity of traditional polling. */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../graphics/VGADebug.h"
#include "io.h"

#define CMD_PORT    0x64
#define DAT_PORT    0x60

#define ACK         0xFA
#define PASS_ST     0xAA
#define RESEND      0xFE

#define CMD_LED     0xED
#define CMD_ECHO    0xEE
#define CMD_RST     0xFF
#define CMD_DISABLE 0xF5
#define CMD_ENABLE  0xF4
#define CMD_TYPESET 0xF0

static class Keyboard {
 private:
  bool init = false;
  bool mutex = false;
  size_t typeset;
  uint8_t lastDataBuffer;

  /* Polls for in-buffer/out-buffer full events. Useful when interrupts
  are disabled.*/
  void waitForIBF ();
  void waitForOBF ();

  /* Waits for in buffer full or out buffer empty signals
  and then reads/writes to 8042 keyboard controller buffer.*/
  bool readFromBuffer (uint8_t& writeTo);

  voidbool writeToBuffer (
    uint8_t cmd,
    uint8_t* res = nullptr
  );

  bool writeToBuffer (
    uint8_t cmd,
    uint8_t data,
    uint8_t* res= nullptr
  );

  /* Test if IRQ is bound, disable interrupts, echo, reset & self test,
  reset LED indicators, set typematic rate & delay, enable keyboard,
  enable interupts. */
  bool init ();

  /* Set keyboard typeset 2 */
  bool setTypeset ();

  /* Reset and start self-test. Returns self test passed/failed. */
  bool reset ();

  /* Send the echo command. Returns true/false if keyboard also echos. */
  bool echo ();

  /* Sends the set LED command and passes an empty data byte, effectively
  turning off all keyboard LED indicators.*/
  bool resetLED ();

  /* Sets the typematic rate and key delay. Bits [0-4] are the typematic
  repeat rate, bits [5-6] are the key delay, bit 7 must be zero. */
  bool setTypematicRate (uint8_t typeByte);

  /* Enable/disable keyboard scanning. */
  bool enable ();
  bool disable ();

  /* Lock/unlock mutext and start/stop interrupts. Prevents IRQs or other
  threads from interfering with time-critical buffer fns..*/
  bool lock ();
  void unlock ();

 public:
  /* This driver is interrupt-driven. Pass an IRQ struct to handle
  IRQ1 buffer messages. IRQ must be bound before initialization.*/
  void BindIRQ ();

  /* When an IRQ1 arrives, any scancodes are saved to the lastDataBuffer.
  GetChar returns the assosciated character, or 'Z' (non-game char) if N/A.
  The game loop then reads keyboard input by calling GetChar() on every iteration.
  This provides a level of abstraction that is superior to polling, especially
  since keyboard data isnt needed real-time. */
  char GetChar ();
}

#endif
