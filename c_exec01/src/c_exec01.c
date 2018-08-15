/*
 ============================================================================
 Name        : c_exec01.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//#define _GNU_SOURCE
#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <stdarg.h>
#include <inttypes.h>

#include "mhashmap.h"

ssize_t getdelim(char **linep, size_t *n, int delim, FILE *fp){
    int ch;
    size_t i = 0;
    if(!linep || !n || !fp){
        errno = EINVAL;
        return -1;
    }
    if(*linep == NULL){
        if(NULL==(*linep = malloc(*n=128))){
            *n = 0;
            errno = ENOMEM;
            return -1;
        }
    }
    while((ch = fgetc(fp)) != EOF){
        if(i + 1 >= *n){
            char *temp = realloc(*linep, *n + 128);
            if(!temp){
                errno = ENOMEM;
                return -1;
            }
            *n += 128;
            *linep = temp;
        }
        if(ch == delim)
            break;
        (*linep)[i++] = ch;
    }
    (*linep)[i] = '\0';
    return !i && ch == EOF ? -1 : i;
}
ssize_t getline(char **linep, size_t *n, FILE *fp){
    return getdelim(linep, n, '\n', fp);
}

void do1() {
	printf("%d\n", 300 == 299.99999f);
	printf("%d\n", 300 == 299.999999);
	printf("%d\n", 300 == 299.9999f);
	printf("%d\n", 300 == 300.00001f);
}

void do2() {
	int age = 0;
	scanf("%d", &age);
	if(age==20) {
		puts("Adult");
	}
	puts("End");
	return;
}

int getMax(int cnt, ...) {
	int nMax = -999, nParam = 0, i = 0;
	va_list pList = NULL;

	va_start(pList, cnt);
	for(i = 0;i < cnt;i++) {
		nParam = va_arg(pList, int);
		if(nParam > nMax) nMax = nParam;
	}
	va_end(pList);
	return nMax;
}

void do3() {
	int input = 0, i = 0;
	fflush(stdin);
	printf("Enter number to print * : "); fflush(stdout);
	scanf("%d%*c", &input);
	if(input<1) input =1;
	else if(input>9) input = 9;

	while(i<input) {
		putchar('*');
		i++;
	}

	putchar('\n');
	return;
}

void do4() {
	int aList[5] = {30, 40, 10, 50, 20};
	int i =0;

	printf("sizeof(aList)=%llu\n", sizeof(aList));

	for(i=0;i<sizeof(aList)/sizeof(int);i++) {
		if(aList[i]>aList[0]) aList[0] = aList[i];
	}

	for(i=0;i<5;i++) printf("%d\t", aList[i]);
	putchar('\n');

	printf("Max=%d\n", aList[0]);
}

void do5() {
	int aList[5][5] = {0};
	int i = 0, j = 0, nCounter = 0;

	for(i = 0;i<5;i++) {
		if(i%2==0) {
			for(j=0;j<5;j++) aList[i][j] = nCounter++;
		}
		else {
			for(j=4;j>=0;j--) aList[i][j] = nCounter++;
		}
	}

	for(i=0;i<5;i++) {
		for(j=0;j<5;j++) {
			printf("%d\t", aList[i][j]);
		}
		putchar('\n');
	}
}

void do6() {
//	int aList[5] = {30, 40, 10, 50, 20};
	int *aList;
	int nCnt = 0, i = 0,j = 0, nMinIndex = 0, nTmp = 0;

	printf("Enter Count : "); fflush(stdout);
	scanf("%d", &nCnt);
	aList = (int *)malloc(sizeof(int)*nCnt);
	for(i=0;i<nCnt;i++) scanf("%d", aList+i);
//	nCnt = sizeof(aList)/sizeof(int);
	// nCnt = n
	for(i=0;i<nCnt-1;i++) {
		nMinIndex = i;
		for(j=i+1;j<nCnt;j++) {
			if(aList[nMinIndex]>aList[j]) nMinIndex = j;
		}
		if(nMinIndex!=i) {
			nTmp = aList[i];
			aList[i] = aList[nMinIndex];
			aList[nMinIndex] = nTmp;
		}
	}

	for(i=0;i<nCnt;i++) printf("%d\t", aList[i]);
	putchar('\n');
}

void do7() {

	int i, nCnt;

	char* key, *value;

	Hashmap map;

	hashmap_open(&map, 100);

	printf("Enter Count : "); fflush(stdout);
	scanf("%d", &nCnt);
	key = (char *)malloc(sizeof(char)*1024);
	value = (char *)malloc(sizeof(char)*1024);
	for(i=0;i<nCnt;i++) {
		memset(key, '\0', sizeof(char)*1024);
		memset(value, '\0', sizeof(char)*1024);

		scanf("%s %s", key, value);

		hashmap_put(&map, key, key+strlen(key)+1, value, value+strlen(value)+1);
//		hashmap_put(&map, word, NULL, word, NULL);
	}

	iter it = {0,0};


	for(i = 0;NULL != (key = hashmap_iterate(&map, &it, (void**)&value));i++) {
		printf("%3d : %s = %s\n", i, key, (char*)hashmap_get(&map, key, key+strlen(key)+1));
		memset(value, '\0', strlen(value));
	}

	hashmap_close(&map);

	if(key) {
		free(key);
		key = NULL;
	}
	if(value) {
		free(value);
		value = NULL;
	}

	putchar('\n');

}

void mainTask() {
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	int isRun = 1;

	do {

		fflush(stdin);
		printf("Enter Option : "); fflush(stdout);

		if(read>0)
			memset(line, '\0', read);

		if((read = getdelim(&line, &len, '\n', stdin)) < 0) {
			isRun = 0;
			break;
		}

		if(!strcmp("exit", line)) {
			printf("exit is entered\n");
			isRun = 0;
		}
		else if(!strcmp("cls", line)) {
			system("cls");
		}
		else if(!strcmp("1", line)) {
			do1();
		}
		else if(!strcmp("2", line)) {
			do2();
		}
		else if(!strcmp("3", line)) {
			do3();
		}
		else if(!strcmp("4", line)) {
			do4();
		}
		else if(!strcmp("5", line)) {
			do5();
		}
		else if(!strcmp("6", line)) {
			do6();
		}
		else if(!strcmp("7", line)) {
			do7();
		}
		else {
			continue;
		}

	} while(isRun);

	free(line);
}

int main(void) {

	mainTask();

//	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

//	float f = 123.456f;
//	double ld = 123.456;
//	printf("sizof %f=%I64d\n", f, sizeof(f));
//	printf("sizof %lf=%I64d\n", ld, sizeof(ld));

//	printf("f is %f, sizeof(f) =%llu\n", f);
//	printf("ld is %lf\n", ld);

//	puts("_getche()");
//	_getche();
//	puts("getchar()");
//	getchar();

//	int nData = 0x11223344;
//
//	printf("%08X\n", nData & 0x00FFFF00);
//	printf("%08X\n", nData | 0x2211FFFF);
//	printf("%08X\n", nData | 0x2211FFFF);
//	printf("%08X\n", ~nData);
//	printf("%08X\n", nData>>8);
//	printf("%08X\n", nData<<16);
//
//	char str[512] = {0};
//
//	printf("sizeof str[512]=%d\n", sizeof(str));
//
//	int a = 0;
//	a+= 10;
//	a+= 20;
//	a+= 30;
//	printf("a is %d\n", a);
//
//	char name[32] = {0};
//
//	printf("Enter your name : "); fflush(stdout);
//	scanf_s("%s%*c", name);
//
////#ifdef _WIN32
////	fflush(stdin);
////#else
////	fpurge(stdin);
////#endif
//	printf("Enter your age : "); fflush(stdout);
//	scanf_s("%lf%*c", &ld);
//
////#ifdef _WIN32
////	fflush(stdin);
////#else
////	fpurge(stdin);
////#endif
//
//	printf("Name(%s), Age(%lf)\n", name, ld);
//#ifdef _WIN32
//	printf("sizof %f=%I64u\n", f, sizeof(f));
//	printf("sizof %lf=%I64u\n", ld, sizeof(ld));
//#else
//	printf("sizof %f=%llu\n", f, sizeof(f));
//	printf("sizof %lf=%llu\n", ld, sizeof(ld));
//#endif
	return EXIT_SUCCESS;
}
