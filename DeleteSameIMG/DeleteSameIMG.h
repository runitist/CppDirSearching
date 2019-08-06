#pragma once

#include <iostream> //I/O��Ʈ�� ���
#include <io.h> //���� ����ü ���
#include <string>//��Ʈ�� ��ü ��� ���
#include <list>//����Ʈ �ڷ��� ���

using namespace std;

void searchingDir(string path);
int isFileOrDir(_finddata_t fd);
list<_finddata_t> getFileList(string path);
void list_Quick_sort(list<_finddata_t>& arr, list<_finddata_t>::iterator start, list<_finddata_t>::iterator end);
void deleteSameIMG(list<_finddata_t>& fl);
list<_finddata_t>::iterator partition(list<_finddata_t>& arr, list<_finddata_t>::iterator start, list<_finddata_t>::iterator end);