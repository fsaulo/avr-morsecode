#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *tabela = "**ETIANMSURWDKGOHVF?L?PJBXCYZQ??54?3?*?2*??*???16??*?*?*7*??8*90";

void ponto() {
	printf(".");
}

void traco() {
	printf("-");
}

void converte(int pos) {
	if (pos) {
		converte(pos / 2);
		if (pos != 1) pos % 2 ? traco() : ponto();
	}
}

void morse(char ch) {
	if (ch >= 'a' && ch <= 'z') ch -= 32;
	if ((ch < '0' && ch > '9') && (ch < 'A' || ch > 'Z')) return;
	int i = 0;
	while (tabela[++i] != ch);
	converte(i);
}

char buffer[100] = { 0 };

int main()
{
	int i = 0, ch;

	while (scanf("%100[^\n]", buffer) != EOF) 
	{
		while ((ch = getchar() != '\n') && ch != EOF);
		while (buffer[i] != '\0') {
			morse(buffer[i++]);
			if (i < strlen(buffer)) printf(" ");
		}
		i = 0;
		printf("\n");
	}
}
