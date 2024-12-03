#ifndef UISCR_H_
#define UISCR_H_

void splash_screen(void);
void score_screen(void);
char *name_screen(int score);

void draw_str(int x, int y, const char *s, int pal);

#endif	/* UISCR_H_ */
