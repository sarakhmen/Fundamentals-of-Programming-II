#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nameval Nameval;
typedef struct NVtab NVtab;
int addname(NVtab* nvtab, Nameval newname);
int delname(NVtab* nvtab, char *name);

struct Nameval {
	char *name;
	int value;
};

struct NVtab{
	int nval;
	int max;
	Nameval *nameval;
};

enum {NVINIT = 1, NVGROW = 2};


int addname(NVtab* nvtab, Nameval newname){
	if(nvtab->nameval == NULL){
		nvtab->nameval = (Nameval*) malloc(NVINIT*sizeof(Nameval));
		if(nvtab->nameval == NULL)
			return -1;
		nvtab->max = NVINIT;
		nvtab->nval = 0;
	}
	else if(nvtab->nval >= nvtab->max){
		nvtab->nameval = (Nameval*) realloc(nvtab->nameval, (NVGROW*nvtab->max)*sizeof(Nameval));
		if(nvtab->nameval == NULL){
			nvtab->max = 0;
			return -1;
		}
		nvtab->max *= NVGROW;
	}
	nvtab->nameval[nvtab->nval] = newname;
	return nvtab->nval++;
}

int delname(NVtab* nvtab, char *name){
	for(int i = 0; i < nvtab->nval; i++)
		if(strcmp(nvtab->nameval[i].name, name) == 0){
			memmove(nvtab->nameval+i, nvtab->nameval+i+1,
				(nvtab->nval-(i+1))*sizeof(Nameval));
			nvtab->nval--;
			return 1;
		}
	return 0;
}

int main(void){
	NVtab nvtab={.nameval = NULL};
	int ind;
	for(int i = 0; i<1000000000; i++){
		ind = addname(&nvtab, (Nameval){.name = "Andy", .value = 12});
		if(ind == -1){
			printf("Error while creating %d element. You lost everything!\n", i);
			return 1;
		}
	}
	printf("Success!\n");
	return 0;
}


//всі накопичені дані втрачаються, бо наш вказівник nameval
//тепер вказує на NULL