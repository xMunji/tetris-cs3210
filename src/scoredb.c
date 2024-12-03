#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scoredb.h"
#include "debug.h"
#include "gbaregs.h"

#define MAGIC "GBATRIS1"
#define SCORE_OFFS	8


#define read_sram(offs, buf, sz) \
	sramcpy(buf, (unsigned char*)SRAM_ADDR + (offs), sz)
#define write_sram(offs, buf, sz) \
	sramcpy((unsigned char*)SRAM_ADDR + (offs), buf, sz)

static void sramcpy(void *dst, void *src, int size);

int last_score_rank = -1;

int load_scores(void)
{
	int i;
	char magic[8];

	read_sram(0, magic, 8);
	if(memcmp(magic, MAGIC, sizeof magic) != 0) {
		for(i=0; i<10; i++) {
			memcpy(scores[i].name, "----", NAME_SIZE + 1);
		}
		/* scores[10] keeps the last entered name. initialize it empty */
		scores[10].name[0] = 0;
		return -1;
	}

	read_sram(SCORE_OFFS, scores, sizeof scores);
	return 0;
}

void save_scores(void)
{
	write_sram(0, MAGIC, 8);
	write_sram(SCORE_OFFS, scores, sizeof scores);
}

void save_score(char *name, int score, int lines, int level)
{
	int i, rank = -1;

	if(!score) {
		last_score_rank = -1;
		return;
	}

	for(i=0; i<10; i++) {
		if(scores[i].score <= score) {
			rank = i;
			break;
		}
	}
	last_score_rank = rank;

	if(rank == -1) return;

	memmove(scores + rank + 1, scores + rank, (9 - rank) * sizeof(struct score_entry));

	if(strlen(name) > NAME_SIZE) {
		name[NAME_SIZE] = 0;
	}
	sprintf(scores[rank].name, "%s", name);
	scores[rank].score = score;
	scores[rank].lines = lines;
	scores[rank].level = level;

	/* also copy to the last entered name slot */
	scores[10] = scores[rank];

	save_scores();
}

int is_highscore(int score)
{
	return scores[9].score <= score;
}

static void sramcpy(void *dst, void *src, int size)
{
	unsigned char *sptr = src;
	unsigned char *dptr = dst;
	while(size-- > 0) {
		*dptr++ = *sptr++;
	}
}
