#include <stdio.h>
#include <string.h>
#include <afx.h>

#define BUF_SIZE 512

int main(int argc, char *argv[]) 
{
	//CFileException ex;
	int i = 1;
	int gle;
	DWORD nIn;
	bool flag = true;
	char buf[BUF_SIZE];

	if (argc < 2) {
		printf("Argc Error\n");
		return 1;
	}

	if (!strcmp(argv[1], "-s")) {
		i++;
		flag = false;
	}

	for (i; i < argc; i++) {
		HANDLE hFile = CreateFile(argv[i], GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_SHARE_READ, NULL);
		printf("FileName %s\n", argv[i]);
		if (hFile == INVALID_HANDLE_VALUE && (gle = GetLastError()) == 2 && flag) printf("Cat Error : File does not exist.\nThe system cannot find the file specified.\n"); //ex.ReportError();
		else {
			while (ReadFile(hFile, buf, BUF_SIZE-1, &nIn, NULL) && nIn > 0) {
				buf[nIn] = 0;
				printf("%s", buf);
			}
			putchar('\n');
		}
		CloseHandle(hFile);
	}

	return 0;
}