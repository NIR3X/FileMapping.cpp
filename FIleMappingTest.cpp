#include "FileMapping.h"
#include <cassert>
#include <iostream>

int main() {
	std::wstring path;
	path.resize(MAX_PATH);
	path.resize(GetModuleFileNameW(NULL, path.data(), path.size()));

	CFileMapping fileMapping(path);
	assert(fileMapping.getFileSize() >= 2);
	LPVOID fileMapView = fileMapping.getMapView();
	assert(fileMapView != NULL);
	assert(*(PUINT16)fileMapView == IMAGE_DOS_SIGNATURE);

	CFileMapping pagingFileWrite({}, 0, 0, 0, 0, false, PAGE_READWRITE, sizeof(UINT32), L"Global\\MyFileMappingObject", FILE_MAP_READ | FILE_MAP_WRITE);
	assert(pagingFileWrite.getFileSize() == sizeof(UINT32));
	LPVOID pagingFileWriteMapView = pagingFileWrite.getMapView();
	assert(pagingFileWriteMapView != NULL);
	*(PUINT32)pagingFileWriteMapView = 123456789;

	CFileMapping pagingFileRead({}, 0, 0, 0, 0, true, PAGE_READONLY, sizeof(UINT32), L"Global\\MyFileMappingObject", FILE_MAP_READ);
	assert(pagingFileRead.getFileSize() == sizeof(UINT32));
	LPVOID pagingFileReadMapView = pagingFileRead.getMapView();
	assert(pagingFileReadMapView!= NULL);
	assert(*(PUINT32)pagingFileReadMapView == 123456789);

	std::cout << "PASS" << std::endl;
}
