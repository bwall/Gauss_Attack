#include <iostream>
#include "md5.h"
#include <Windows.h>
#include <time.h>

using namespace std;

int main(int argc, char ** argv)
{	
	unsigned int iterations = 1 << 15;
	unsigned int tests = 10000;
	unsigned char salt1[] = {0x97, 0x48, 0x6C, 0xAA, 0x22, 0x5F, 0xE8, 0x77, 0xC0, 0x35, 0xCC, 0x03, 0x73, 0x23, 0x6D, 0x51};
	char path[] = "C:\\Documents and Settings\\john\\Local Settings\\Application Data\\Google\\Chrome\\Application~dir1";
	unsigned char null = 0x00;
	cout << "Number of tests: " << iterations << endl;
	cout << "Iterations per hash: " << tests << endl;
	int start = clock();
	for(int y = 0; y < iterations; y++)
	{
		MD5 md5;
		for(int x = 0; x < strlen(path); x++)
		{
			md5.update((unsigned char *)path + x, 1);
			md5.update((unsigned char *)&null, 1);
		}
		md5.update(salt1, 16);
		unsigned char hash[16];
		md5.finalize();
		memcpy(hash, md5.digest, 16);
		for(int x = 0; x < tests; x++)
		{
			MD5 m;
			m.update(hash, 16);
			m.finalize();
			memcpy(hash, m.digest, 16);
		}
	}
	int end = clock();
	double orig = end - start;
	printf ("Original: (%f seconds) %f hashes per second.\n", ((float)end - start)/CLOCKS_PER_SEC, ((double)iterations + 1)/(((float)end - start)/CLOCKS_PER_SEC));

	start = clock();
	for(int y = 0; y < iterations; y++)
	{
		MD5 md5i;
		for(int x = 0; x < strlen(path); x++)
		{
			md5i.update((unsigned char *)path + x, 1);
			md5i.update((unsigned char *)&null, 1);
		}
		md5i.update(salt1, 16);
		md5i.finalize(tests);
	}
	end = clock();
	orig = end - start;
	printf ("Original: (%f seconds) %f hashes per second.\n", ((float)end - start)/CLOCKS_PER_SEC, ((double)iterations + 1)/(((float)end - start)/CLOCKS_PER_SEC));

	cout << endl << "Should be 76405ce7f4e75e352c1cd4d9aeb6be41" << endl;
}