#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int count_word(FILE* fp) {
	char s;
	bool flag = false;
	int count = 0;
	while ((s = fgetc(fp)) != EOF) {
		if (isspace(s)) {
			if (flag) {
				count += 1;
				flag = false;
			}
		}
		else
			flag = true;
	}
	count += flag;
	fseek(fp, 0, SEEK_SET);
	return count;
}


void count_rate_en(FILE* fp) {
	char symbols = 0;
	int characters[128] = { 0 };
	char s;
	while ((s = fgetc(fp)) != EOF) {
		symbols += 1;
		characters[(int)s] += 1;
	}
	for (int i = 'A'; i <= 'z'; i++) {
		if (i <= 'Z' || i >= 'a') {
			printf("%c %d %.3f\n", (char)i, characters[i], characters[i] / (symbols * 1.0));
		}
	}
	fseek(fp, 0, SEEK_SET);
}


void count_rate_en_ir(FILE* fp) {
	int symbols = 0;
	char s;
	int characters[128] = { 0 };
	while ((s = fgetc(fp)) != EOF) {
		symbols++;
		characters[(int)s] += 1;
		if ((int)s <= 'Z')
			characters[(int)s + 32] += 1;
		else if ((int)s >= 'a')
			characters[(int)s - 32] += 1;
	}
	for (int i = 'A'; i <= 'Z'; i++)
		printf("%c %d %.3f\n", (char)i, characters[i], characters[i] / (symbols * 1.0));
	fseek(fp, 0, SEEK_SET);
}


void count_rate_ASCII(FILE* fp) {
	int symbols = 0;
	char s;
	int characters[128] = { 0 };
	while ((s = fgetc(fp)) != EOF){
		symbols++;
		characters[(int)s] += 1;
	}
	//symbol ASCII 0-128
	for (int i = 0; i < 128; i++)
		printf("%c %d %.3f\n", (char)i, characters[i], characters[i] / (symbols * 1.0));
	fseek(fp, 0, SEEK_SET);
}


int main(int argc, char* argv[]) {
	FILE* fp;
	fp = fopen(argv[1], "r");
	if (fp != NULL) {
		printf("File open\n");
		switch (argc) {
		case 1:
			printf("File not found");
			break;
		case 2:
			count_rate_ASCII(fp);
			break;
		case 3:
			if (!strcmp(argv[2], "-w") || !strcmp(argv[2], "--word")) {
				printf("count words: %d", count_word(fp));
			}
			else if (!strcmp(argv[2], "--all")) {
				count_rate_ASCII(fp);
			}
			else if (!strcmp(argv[2], "--en")) {
				count_rate_en(fp);
			}
			break;
		case 4:
			if (!strcmp(argv[3], "--ir")) {
				count_rate_en_ir(fp);
			}
		}
		fclose(fp);
	}
	return 0;
}