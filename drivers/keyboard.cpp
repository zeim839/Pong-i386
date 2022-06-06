#include "Keyboard.h"

bool Keyboard::lock () {
  if (mutex) return false;
  __asm__ volatile ("cli");
  mutex = true;
  return true;
}

void Keyboard::unlock () {
  __asm__ volatile ("sti");
  mutex = false;
}

void keyboard::waitForIBF () {
  /* Second LS bit of CMD_PORT is IBF flag. If its
  0, then the buffer is not full yet and we must wait.*/
  uint8_t status = inb(CMD_PORT) & 0x2;
  while (status == 0) status = inb(CMD_PORT) & 0x2;
}

void Keyboard::waitForOBF () {
  /* First LS bit is OBF status flag. If it is not zero,
  then buffer is full and we must wait before writing.*/
  uint8_t status = inb(CMD_PORT) & 0x1;
  while (status != 0) status = inb(CMD_PORT) & 0x1;
}

bool Keyboard::readFromBuffer (uint8_t* writeTo) {
  if (!lock()) return false;
  waitForIBF();

  if (writeTo != nullptr) *writeTo = inb(DAT_PORT);
  unlock();

  return true;
}

bool Keyboard::writeToBuffer (uint8_t cmd, uint8_t* res) {
  if (!lock()) return false;

  size_t resetCnt = 0;
  uint8_t _res;
  while (resetCnt < 3) {
    waitForOBF();
    outb(CMD_PORT, cmd);

    waitForIBF();
    _res = inb(DAT_PORT);

    if (_res != RESEND) break;
    resetCnt++;
  }
  
  if (res != nullptr) {
    *res = _res;
  }

  unlock();

  if (_res != ACK) return false;
  return true;
}

bool Keyboard::writeToBuffer (
  uint8_t cmd,
  uint8_t data,
  uint8_t* res
) {
  if (!lock()) return false;

  /* Send CMD byte */
  size_t resetCnt = 0;
  uint8_t _res;
  while (resetCnt < 3) {
    waitForOBF();
    outb(CMD_PORT, cmd);

    waitForIBF();
    _res = inb(DAT_PORT);

    if (_res != RESEND) break;
    resetCnt++;
  }

  /* CMDs that require data ALWAYS respond
  with ACK after CMD. */
  if (_res != ACK) {
    unlock();
    return false;
  }

  /* Send data byte. None of the driver cmds
  need more than 1 byte in input, so we only
  wait for 1. */
  resetCnt = 0;
  while (resetCnt < 3) {
    waitForOBF();
    outb(CMD_PORT, data);

    waitForIBF();
    _res = inb(DAT_PORT);

    if (_res != RESEND) break;
    resetCnt++;
  }

  if (res != nullptr) *res = _res;
  unlock();

  if (_res != ACK) return false;
  return true;
}

bool Keyboard::reset () {
  uint8_t res;
  writeToBuffer(CMD_RST, &res);

  /* We dont care if writeToBuffer returns true,
  CMD_RST does not respond with ACK, it responds
  with test result.*/
  if (res == PASS_ST) return true;
  return false;
}

bool Keyboard::echo () {
  uint8_t res;
  writeToBuffer(CMD_RST, &res);

  /* We dont care if writeToBuffer returns true,
  CMD_ECHO does not respond with ACK, it responds
  with echo.*/
  if (res == CMD_ECHO) return true;
  return false;
}

bool Keyboard::resetLED () {
  return writeToBuffer(CMD_LED, (uint8_t)0x0);
}

bool Keyboard::setTypematicRate (uint8_t typeByte) {
  return writeToBuffer(CMD_LED, typeByte);
}

bool Keyboard::enable () {
  if (!inited) return false;
  return writeToBuffer(CMD_ENABLE);
}

bool Keyboard::disable () {
  if (!writeToBuffer(CMD_DISABLE))
    return false;

  /* Disabling scanning may or may not reset
  keyboard to defaults. Might want to re-init
  just in case.*/
  init = false;

  return true; 
}

bool Keyboard::setTypeset () {
  return writeToBuffer(CMD_TYPESET, (uint8_t)0x2);
}

bool Keyboard::init () {
  /* TODO */
}

void Keyboard::BindIRQ () {
  /* TODO */
}

void Keyboard::GetChar () {
  /* TODO */  
}

