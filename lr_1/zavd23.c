#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAB_SIZE 20000000

typedef struct Pixel Pixel;
typedef struct Coords Coords;

unsigned int hash(Coords pos);
Pixel* lookup(Coords pos, int create, int value);
void print_chains();


struct Coords {
	unsigned int x;
	unsigned int y;
};


struct Pixel {
	Coords pos;
	int value;
	Pixel* next;
};

Pixel *coord_table[TAB_SIZE];


unsigned int hash(Coords pos) {
	unsigned int h = pos.y + ((pos.x + 1) / 2);
	return (pos.x + (h * h))%TAB_SIZE;
}


Pixel* lookup(Coords pos, int create, int value) {
	Pixel* pix;
	unsigned int h = hash(pos);
	for(pix = coord_table[h]; pix != NULL; pix = pix->next)
		if((pix->pos.x == pos.x) && (pix->pos.y == pos.y))
			return pix;
	if(create){
		pix = (Pixel*)malloc(sizeof(Pixel));
		pix->pos.x = pos.x;
		pix->pos.y = pos.y;
		pix->value = value;
		pix->next = coord_table[h];
		coord_table[h] = pix;
	}
	return pix;
}


void print_chains() {
	Pixel* p;
	int occupied = 0;
	int added = 0;
	for (int i = 0; i < TAB_SIZE; ++i) {
		if (coord_table[i] == NULL)
			continue;
		++occupied;
		for (p = coord_table[i]; p != NULL; p = p->next) {
			++added;
			//printf("<pixel position> (%u, %u) <value> %d;\t\t", p->pos.x, p->pos.y, p->value);
		}
		//printf("\n");
	}
	printf("\nPixels added: %d\n", added);
	printf("Occupied cells: %d\n", occupied);
}


int main(void) {
	for (int i = 0; i < 1920; ++i)
		for (int j = 0; j < 1080; ++j) {
			lookup((Coords){i, j}, 1, i*j);
		}
	print_chains();
	printf("\n\n");
	return 0;
}