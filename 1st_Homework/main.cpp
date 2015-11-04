#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdint.h>

#define BUF_SIZE 512		// Buffer size used to copying data at once

int main(int argc, char *argv[])
{
	if (argc != 4) {		
		printf("Usage : 1st_Homework file1 file2 output_file\n");
		return false;
	}

	DWORD nIn, nOut;

	wchar_t buf[BUF_SIZE];

	HANDLE hFile1 = CreateFileA(argv[1],				// Creating handles for reading files.
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_SHARE_READ,
		NULL);
	
	HANDLE hFile2 = CreateFileA(argv[2],
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_SHARE_READ,
		NULL);

	if (hFile1 == INVALID_HANDLE_VALUE || hFile2 == INVALID_HANDLE_VALUE) {			// Exception Handling
		printf("File not exists\n");
		return false;
	}

	HANDLE hOutput = CreateFileA(argv[3],		// Always creating new file. If file exists, it overwrites the file.
		GENERIC_ALL,
		NULL,
		NULL,
		CREATE_ALWAYS,
		NULL,
		NULL);
	
	if (hOutput == INVALID_HANDLE_VALUE) {			// Exception Handling
		printf("Cannot Create New File. Error : %u\n", GetLastError());
		return false;
	}
	
	while (ReadFile(hFile1, buf, BUF_SIZE, &nIn, NULL) && nIn > 0) {
		WriteFile(hOutput, buf, nIn, &nOut, NULL);
	}
	
	WriteFile(hOutput, "\r\n", 2, &nOut, NULL);
	
	while (ReadFile(hFile2, buf, BUF_SIZE, &nIn, NULL) && nIn > 0) {
		WriteFile(hOutput, buf, nIn, &nOut, NULL);
	}
	
	CloseHandle(hFile1);		// Deallocating handles
	CloseHandle(hFile2);
	CloseHandle(hOutput);

	printf("File copy Complete.\n");
	return 0;
}