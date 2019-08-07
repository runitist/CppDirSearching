#include "DeleteSameIMG.h"

int main() {

	cout << "동일 이미지 제거 실행" << endl;
	string path = "C:\\DEV\\test";
	searchingDir(path);
	cout << "동일 이미지 제거 완료" << endl;

}

void searchingDir(string path)
{
	//cout << "searchingDir 실행" << endl;
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
			string subPath = path + "\\" + fd.name;
			searchingDir(subPath);//재귀적 호출

			//여기부터 아래로는 재귀 호출상 최하단 디렉토리 내의 파일들의 실행로직.

			list<_finddata_t> fl = getFileList(subPath);
			list<_finddata_t>::iterator itor;
			
			//동일 이미지 삭제.
			deleteSameIMG(fl, subPath);

		}

	} while (_findnext(handle, &fd) == 0);


	_findclose(handle);
}

int isFileOrDir(_finddata_t fd)
//파일인지 디렉토리인지 판별
{
	//cout << "isFileOrDir 실행" << endl;

	if (fd.attrib & _A_SUBDIR)
		return 0; // 디렉토리면 0 반환
	else
		return 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환

}

list<_finddata_t> getFileList(string path)
{
	//cout << "getFileList 실행" << endl;
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

void deleteSameIMG(list<_finddata_t>& fl, string& subPath)
//동일 이미지 비교후 제거
{
	//fl은 해당 디렉토리 내의 모든 파일들의 정보를 가진 리스트이다.
	//fl 정렬


	//동일 이미지 비교

	list<_finddata_t>::iterator istart = fl.begin();//비교 기준점
	list<_finddata_t>::iterator inext = fl.begin();
	++inext;
	list<_finddata_t>::iterator iend = fl.end();
	--iend;

	for (;inext != fl.end(); inext++)
	{
		if (inext->size==istart->size)
		{
			remove((subPath+"\\" + inext->name).c_str());
		}
		else
		{
			istart = inext;
		}
	}

}
