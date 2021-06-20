/*
 * ASCII to morse code
 *
 * Created 18_06_2016 01:39AM
 * Saulo G. Felix
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define F_CPU 16000000UL
#define BAUD  9600

#include <util/delay.h>
#include <util/setbaud.h>

void serial_init() {
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

int serial_out(char data, FILE* stream) {
	if (data == '\n') {
		serial_out('\r', stream);
	}

	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
	return 0;
}

int serial_in(FILE* stream) {
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

FILE serial_stdin  = FDEV_SETUP_STREAM(NULL, serial_in, _FDEV_SETUP_READ);
FILE serial_stdout = FDEV_SETUP_STREAM(serial_out, NULL, _FDEV_SETUP_WRITE);

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
	serial_init();

	stdin  = &serial_stdin;
	stdout = &serial_stdout;

	int i = 0;

	for (;;) {
		scanf("%s", buffer);
		while (buffer[i] != '\0') {
			morse(buffer[i++]);
			if (i < strlen(buffer)) printf(" ");
		} 
		printf("\n");
		i = 0;
	}
}
