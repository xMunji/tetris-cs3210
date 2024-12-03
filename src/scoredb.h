#ifndef SCOREDB_H_
#define SCOREDB_H_

#define NAME_SIZE	4

struct score_entry {
	char name[8];
	uint32_t score;
	uint16_t lines;
	uint8_t level, unused;
} __attribute__((packed));

/* last entry is used just to keep the last entered name
 * and present it as a default choice in the highscore UI
 */
struct score_entry scores[11];

int last_score_rank;

int load_scores(void);
void save_scores(void);
void save_score(char *name, int score, int lines, int level);
int is_highscore(int score);

#endif	/* SCOREDB_H_ */
