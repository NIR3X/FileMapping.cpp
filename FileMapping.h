#pragma once

#include <windows.h>
#include <cstdint>
#include <string>
#include <vector>

class CFileMapping {
protected:
	HANDLE hFile;
	HANDLE hMapFile;
	LPVOID mapView;
	SIZE_T fileSize;

public:
	CFileMapping(
		const std::wstring& filePath,
		DWORD dwDesiredAccess = GENERIC_READ,
		DWORD dwShareMode = FILE_SHARE_READ,
		DWORD dwCreationDisposition = OPEN_EXISTING,
		DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
		bool open = false,
		DWORD dwPageProtection = PAGE_READONLY,
		SIZE_T size = 0,
		const std::wstring& name = {},
		DWORD dwFileMapAccess = FILE_MAP_READ
	);
	~CFileMapping();

	LPVOID getMapView() const;
	SIZE_T getFileSize() const;
};
