#ifndef KEYB_H_
#define KEYB_H_

#include <stdint.h>

#define KEYPRESS(key)	((keystate & (key)) && (keydelta & (key)))
#define KEYRELEASE(key)	((keystate & (key)) == 0 && (keydelta & (key)))

uint16_t keystate, keydelta;

void key_repeat(int start, int rep, uint16_t mask);

void update_keyb(void);

#endif	/* KEYB_H_ */
