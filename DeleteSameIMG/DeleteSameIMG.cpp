#include "DeleteSameIMG.h"

int main() {

	string path = "C:\\DEV\\test";
	searchingDir(path);

}


void searchingDir(string path)
{
	int checkDirFile = 0;
	string dirPath = path + "\\*.*";
	struct _finddata_t fd;//디렉토리 내 파일 및 폴더 정보 저장 객체
	intptr_t handle;


	if ((handle = _findfirst(dirPath.c_str(), &fd)) == -1L) //fd 구조체 초기화.
	{
		//파일이나 디렉토리가 없을 경우.
		cout << "No file in directory!" << endl;
		return;
	}


	do //폴더 탐색 반복 시작
	{
		checkDirFile = isFileOrDir(fd);//현재 객체 종류 확인(파일 or 디렉토리)
		if (checkDirFile == 0 && fd.name[0] != '.') {
			//디렉토리일 때의 로직
			cout << "Dir  : " << path << "\\" << fd.name << endl;
			string subPath = path + "\\" + fd.name;
			searchingDir(subPath);//재귀적 호출

			//여기부터 아래로는 재귀 호출상 최하단 디렉토리 내의 파일들의 실행로직.

			list<_finddata_t> fl = getFileList(subPath);
			list<_finddata_t>::iterator itor;

			//사이즈별로 리스트 퀵소트 실행.
			list_Quick_sort(fl, fl.begin(), --fl.end());

			for (itor  = fl.begin(); itor != fl.end(); itor++)
			{
				cout << "Itor 이름 : " <<subPath<<"\\"<< itor->name << "사이즈 : " << itor->size << endl;
			}

			//동일 이미지 삭제.
			deleteSameIMG(fl);

		}

	} while (_findnext(handle, &fd) == 0);


	_findclose(handle);
}

int isFileOrDir(_finddata_t fd)
//파일인지 디렉토리인지 판별
{

	if (fd.attrib & _A_SUBDIR)
		return 0; // 디렉토리면 0 반환
	else
		return 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환

}

list<_finddata_t> getFileList(string path)
{
	int checkDirFile = 0;
	string dirPath = path + "\\*.*";
	struct _finddata_t fd;//디렉토리 내 파일 및 폴더 정보 저장 객체
	intptr_t handle;
	list<_finddata_t> fList;


	if ((handle = _findfirst(dirPath.c_str(), &fd)) == -1L) //fd 구조체 초기화.
	{
		//파일이나 디렉토리가 없을 경우.
		cout << "No file in directory!" << endl;
		return fList;
	}


	do //폴더 탐색 반복 시작
	{
		checkDirFile = isFileOrDir(fd);//현재 객체 종류 확인(파일 or 디렉토리)
		if (checkDirFile == 1 && fd.name[0] != '.') {
			fList.push_back(fd);
		}

	} while (_findnext(handle, &fd) == 0);


	_findclose(handle);
}

void list_Quick_sort(list<_finddata_t>& arr, list<_finddata_t>::iterator start, list<_finddata_t>::iterator end)
//퀵 정렬
{
	if (start != end)
	{
		list<_finddata_t>::iterator pivotIdx = partition(arr, start, end);

		list_Quick_sort(arr, end, pivotIdx--);
		list_Quick_sort(arr, pivotIdx++, start);
	}
}

list<_finddata_t>::iterator partition(list<_finddata_t>& arr, list<_finddata_t>::iterator start, list<_finddata_t>::iterator end)
{
	list<_finddata_t>::iterator pivotIdx = end;

	for (list<_finddata_t>::iterator idx = start; idx != end++; idx++)
	{
		if (idx->size > pivotIdx->size && pivotIdx._Ptr > idx._Ptr)
		{
			swap(idx, pivotIdx);
		}
		else if (idx->size < pivotIdx->size && pivotIdx._Ptr < idx._Ptr)
		{
			swap(idx, pivotIdx);
		}
	}

	return pivotIdx;
}

void deleteSameIMG(list<_finddata_t>& fl)
//동일 이미지 비교후 제거
{

}