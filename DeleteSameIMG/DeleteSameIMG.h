#pragma once

#include <iostream> //I/O��Ʈ�� ���
#include <io.h> //���� ����ü ���
#include <string>//��Ʈ�� ��ü ��� ���
#include <list>//����Ʈ �ڷ��� ���

using namespace std;

void searchingDir(string path);
int isFileOrDir(_finddata_t fd);
list<_finddata_t> getFileList(string path);
void deleteSameIMG(list<_finddata_t>& fl, string &subPath);
void qListSorting(list<_finddata_t>& fl, list<_finddata_t>::iterator istart, list<_finddata_t>::iterator iend);