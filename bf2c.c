#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <brainfuck.program> <outputfile.c>\n", argv[0]);
		exit(1);
	}

	FILE *openFile = fopen(argv[1], "r");
	FILE *outFile  = fopen(argv[2], "w");

	int indentLevel = 0;
	int i;
	char c = fgetc(openFile);

	fprintf(outFile, "#include <stdio.h>\n\nint main (int argc, char **argv) {\n\tchar array[30000];\n\tchar *p = array;\n\n");
	while (c != EOF) {
		switch(c) {
			case '+':
				for(i=0;i<indentLevel;i++) {
					fprintf(outFile, "\t");
				}
				fprintf(outFile, "\t++*p;\n");
				break;
			case '-':
				for(i=0;i<indentLevel;i++) {
					fprintf(outFile, "\t");
				}
				fprintf(outFile, "\t--*p;\n");
				break;
			case '>':
				for(i=0;i<indentLevel;i++) {
					fprintf(outFile, "\t");
				}
				fprintf(outFile, "\t++p;\n");
				break;
			case '<':
				for(i=0;i<indentLevel;i++) {
					fprintf(outFile, "\t");
				}
				fprintf(outFile, "\t--p;\n");
				break;
			case '.':
				for(i=0;i<indentLevel;i++) {
					fprintf(outFile, "\t");
				}
				fprintf(outFile, "\tputchar(*p);\n");
				break;
			case ',':
				for(i=0;i<indentLevel;i++) {
					fprintf(outFile, "\t");
				}
				fprintf(outFile, "\t*p = getchar();\n");
				break;
			case '[':
				for(i=0;i<indentLevel;i++) {
					fprintf(outFile, "\t");
				}
				fprintf(outFile, "\twhile(*p) {\n");
				indentLevel++;
				break;
			case ']':
				for(i=0;i<indentLevel;i++) {
					fprintf(outFile, "\t");
				}
				fprintf(outFile, "}\n");
				indentLevel--;
				break;
		}
		c = fgetc(openFile);
	}

	fprintf(outFile, "\treturn 0;\n}");

	fclose(openFile);
	fclose(outFile);

	return 0;
}
