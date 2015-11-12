#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Usage : 2nd_Homework.exe infile outfile shift\n");
		return 1;
	}
	
	char dirBuf[BUF_SIZE];
	char buf[BUF_SIZE];
	DWORD length;
	int shift = atoi(argv[3]);

	if (!GetCurrentDirectory(BUF_SIZE, dirBuf)) {
		printf("GetCurrentDirectory Error. gle : %u\n", GetLastError());
		return 1;
	}
	
	printf("Present Directory : ");
	printf(dirBuf);
	printf("\n");

	HANDLE f1 = CreateFile(argv[1],
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL);

	HANDLE f2 = CreateFile(argv[2],
		GENERIC_ALL,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		NULL,
		NULL);

	if (f1 == INVALID_HANDLE_VALUE && f2 == INVALID_HANDLE_VALUE) {
		printf("CreateFile Error. gle : %u\n", GetLastError());
		return 1;
	}

	while (ReadFile(f1, buf, BUF_SIZE, &length, NULL) && length > 0) {
		for (int i = 0; i < length; i++) {
			buf[i] = (buf[i] + shift) % 255;
		}
		WriteFile(f2, buf, length, &length, NULL);
	}

	CloseHandle(f1);
	CloseHandle(f2);
	return 0;
}