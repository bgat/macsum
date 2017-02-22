#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#if ORIG
/* http://www.cse.yorku.ca/~oz/hash.html */

/* This algorithm (k=33) was first reported by Dan Bernstein
 * many years ago in comp.lang.c. Another version of this
 * algorithm (now favored by Bernstein) uses xor: hash(i) =
 * hash(i - 1) * 33 ^ str[i]; */
unsigned long
hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}
#endif

unsigned long
djb2_hash(unsigned long c)
{
	static unsigned long hash = 5381;
	hash = ((hash << 5) + hash) ^ c; /* hash * 33 ^ c */
	return hash;
}

int main(int argc, const char *argv[], const char *env[])
{
	unsigned long c, hash = 0;
	unsigned char mac[6];
	const int nmac = sizeof(mac) / sizeof (*mac);

	while (1) {
		c = fgetc(stdin);
		if (c == EOF || !c)
			break;
		hash = djb2_hash(c);
	}
	fprintf(stdout, "hash: %16lx\n", hash);

	for (c = 0; c < nmac; c++)
		mac[c] = hash >> ((5 - c) * 8);

	/* unicast, locally-administered */
	mac[0] &= ~1;
	mac[0] |= 2;

	fprintf(stdout, "mac: ");
	for (c = 0; c < nmac; c++) {
		fprintf(stdout, "%s%02x", c == 0 ? "" : ":", mac[c]);
	}
	fprintf(stdout, "\n");
	return 0;
}

