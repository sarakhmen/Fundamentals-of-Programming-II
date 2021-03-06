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
	Nameval *nvp;
	if(nvtab->nameval == NULL){
		nvtab->nameval = (Nameval*) malloc(NVINIT*sizeof(Nameval));
		if(nvtab->nameval == NULL)
			return -1;
		nvtab->max = NVINIT;
		nvtab->nval = 0;
	}
	else if(nvtab->nval >= nvtab->max){
		nvp = (Nameval*) realloc(nvtab->nameval, (NVGROW*nvtab->max)*sizeof(Nameval));
		if(nvp == NULL)
			return -1;
		nvtab->max *= NVGROW;
		nvtab->nameval = nvp;
	}
	nvtab->nameval[nvtab->nval] = newname;
	return nvtab->nval++;
}

int delname(NVtab* nvtab, char *name){
	for(int i = 0; i < nvtab->nval; i++)
		if(strcmp(nvtab->nameval[i].name, name) == 0){
			nvtab->nameval[i] = nvtab->nameval[nvtab->nval-1];
			nvtab->nval--;
			return 1;
		}
	return 0;
}

int main(void){
	NVtab nvtab={.nameval = NULL};
	addname(&nvtab, (Nameval){.name = "Andy", .value = 12});
	addname(&nvtab, (Nameval){.name = "Billy", .value = 18});
	addname(&nvtab, (Nameval){.name = "Petya", .value = 25});
	addname(&nvtab, (Nameval){.name = "Vasya", .value = 36});
	for(int i = 0; i < nvtab.nval; i++){
		printf("%s %d\n", nvtab.nameval[i].name,
			nvtab.nameval[i].value);
	}
	printf("deleting Billy\n");
	delname(&nvtab, "Billy");
	for(int i = 0; i < nvtab.nval; i++){
		printf("%s %d\n", nvtab.nameval[i].name,
			nvtab.nameval[i].value);
	}
	return 0;
}