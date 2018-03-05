#include "Files.h"
#include <Windows.h>

char* convert(char* source){
	int len = strlen(source);
	char* arr = new char[len+1];
	strncpy(arr, source, len);
	arr[len] = (char)0;
	return arr;
}

vector<char*>* find(char* mask) {
	vector<char*>* list = new vector<char*>();
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFileEx(mask, FindExInfoBasic, &ffd, FindExSearchNameMatch, NULL, FIND_FIRST_EX_LARGE_FETCH);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			list->push_back(convert(ffd.cFileName));
		} while (FindNextFile(hFind, &ffd) != 0);
		FindClose(hFind);
	}
	return list;
}