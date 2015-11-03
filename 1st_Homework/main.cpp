#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Usage : 1st_Homework file1 file2 output_file\n");
		exit(1);
	}

	HANDLE hFile1 = CreateFile(argv[1],
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_SHARE_READ,
		NULL);
	
	HANDLE hFile2 = CreateFile(argv[2],
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_SHARE_READ,
		NULL);

	if (hFile1 == NULL || hFile2 == NULL) {
		printf("File not exists\n");
		exit(1);
	}

	HANDLE hOutput = CreateFile(argv[3],
		GENERIC_ALL,
		NULL,
		NULL,
		CREATE_NEW,
		NULL,
		NULL);
	
	if (hOutput == NULL) {
		printf("Cannot Create New File. Error : %d\n", GetLastError());
		exit(1);
	}

}