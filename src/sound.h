#ifndef SOUND_H_
#define SOUND_H_

#define DS_ONCE		0
#define DS_LOOP		1
#define DS_MONO		0
#define DS_STEREO	2

void init_sound(void);

void play_dsound(void *rdata, void *ldata, unsigned long offs, unsigned long len,
		unsigned short rate, unsigned short mode);
void stop_dsound(void);

void pause_dsound(void);
void resume_dsound(void);

void snd_stick(void);
void snd_shift(void);
void snd_rot(void);

void snd_test(void);

#endif	/* SOUND_H_ */
