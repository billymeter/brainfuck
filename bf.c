#include <stdio.h>
#include <stdlib.h>

#define YES 1
#define NO  0

int looper = 0;
char array[30000] = {0};
char *p = array;

void processCmd(char cmd, FILE *fp, int doCmd) {
	long pos = 0;
	char c;

	switch(cmd) {
		case '+':
			if (doCmd)
				++*p;
			break;
		case '-':
			if (doCmd)
				--*p;
			break;
		case '>':
			if (doCmd)
				++p;
			break;
		case '<':
			if (doCmd)
				--p;
			break;
		case '.':
			if (doCmd)
				putchar(*p);
			break;
		case ',':
			if (doCmd)
				*p = getchar();
			break;
		case '[':
			pos = ftell(fp);
			if (*p) {
				doCmd = YES;
				while (*p) {
					fseek(fp, pos, SEEK_SET);
					c = fgetc(fp);
					while( c!= ']' && c != EOF) {
						processCmd(c, fp, YES);
						c = fgetc(fp);
					}
				}
			} else if (*p == 0)  {
				c = fgetc(fp);
				while (c != ']' && c!= EOF) {
					processCmd(c, fp, NO);
					c = fgetc(fp);
				}
			}
	}
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <program name>\n", argv[0]);
		exit(1);
	}

	FILE *fp = fopen(argv[1], "r");

	if (!fp) {
		fprintf(stderr, "file '%s' not found\n", argv[1]);
		exit(1);
	}

	char c = fgetc(fp);
	while (c != EOF) {
		processCmd(c, fp, YES);
		c = fgetc(fp);
	}

	fclose(fp);

	return 0;
}
