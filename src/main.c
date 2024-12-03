#include <string.h>
#include "gbaregs.h"
#include "game.h"
#include "tileset.h"
#include "timer.h"
#include "keyb.h"
#include "intr.h"
#include "sound.h"

#define SCR_BASE_BLOCK	0
#define CHR_BASE_BLOCK	2

static int handle_keys(unsigned long msec);
void splash_screen(void);
void score_screen(void);

int main(void)
{
	unsigned long msec;
	uint16_t next_upd = 0;

	intr_init();
	reset_msec_timer();
	set_intr();

	init_sound();
	splash_screen();

	/* set mode 0 and enable BG0 */
	REG_DISPCNT = DISPCNT_BG0;
	/* BG0: scr/chr base blocks */
	REG_BG0CNT = BGCNT_CHR_BASE(CHR_BASE_BLOCK) | BGCNT_SCR_BASE(SCR_BASE_BLOCK);

	scrmem = (uint16_t*)VRAM_SCR_BLOCK_ADDR(SCR_BASE_BLOCK);
	chrmem = (uint16_t*)VRAM_CHR_BLOCK_ADDR(CHR_BASE_BLOCK);

	setup_tileset(chrmem);
	score_screen();

	key_repeat(500, 75, KEY_LEFT | KEY_RIGHT | KEY_DOWN);

	for(;;) {
		while(REG_VCOUNT < 160);	/* wait vsync */

		msec = timer_msec;

		if(handle_keys(msec) || msec >= next_upd) {
			next_upd = msec + update(msec);
		}
	}
	return 0;
}


static int handle_keys(unsigned long msec)
{
	int upd = 0;

	update_keyb();

	if(KEYPRESS(KEY_A)) {
		game_input('w');
		upd = 1;
	}
	if(KEYPRESS(KEY_B)) {
		game_input('\n');
		upd = 1;
	}
	if(KEYPRESS(KEY_START)) {
		game_input('p');
		upd = 1;
	}
	if(KEYPRESS(KEY_SELECT)) {
		game_input('\b');
		upd = 1;
	}
	if(KEYPRESS(KEY_UP)) {
		game_input('\n');
		upd = 1;
	}
	if(KEYPRESS(KEY_DOWN)) {
		game_input('s');
		upd = 1;
	}
	if(KEYPRESS(KEY_LEFT)) {
		game_input('a');
		upd = 1;
	}
	if(KEYPRESS(KEY_RIGHT)) {
		game_input('d');
		upd = 1;
	}
	if(KEYPRESS(KEY_LT | KEY_RT)) {
		game_input('m');
	}

	return upd;
}
