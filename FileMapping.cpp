#include "FileMapping.h"

CFileMapping::CFileMapping(
	const std::wstring& filePath,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	bool open,
	DWORD dwPageProtection,
	SIZE_T size,
	const std::wstring& name,
	DWORD dwFileMapAccess
) : hFile(NULL), hMapFile(NULL), mapView(NULL), fileSize(0) {
	if (filePath.length() == 0) {
		hFile = INVALID_HANDLE_VALUE;
		fileSize = size;
	} else {
		hFile = CreateFileW(filePath.c_str(), dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			hFile = NULL;
			goto fail;
		}

		static_assert(sizeof(fileSize) == sizeof(LARGE_INTEGER));
		if (!GetFileSizeEx(hFile, reinterpret_cast<PLARGE_INTEGER>(&fileSize))) {
			goto fail_close_file;
		}
	}

	hMapFile = open ?
		OpenFileMappingW(dwFileMapAccess, FALSE, name.c_str()) :
		CreateFileMappingW(hFile, NULL, dwPageProtection, size >> 32, size, name.length() == 0 ? NULL : name.c_str());
	if (!hMapFile) {
		goto fail_close_file;
	}

	mapView = MapViewOfFile(hMapFile, dwFileMapAccess, 0, 0, size);
	if (mapView == NULL) {
		goto fail_close_mapping;
	}

	return;

fail_close_mapping:
	CloseHandle(hMapFile);
	hMapFile = NULL;

fail_close_file:
	if (hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(hFile);
	}
	hFile = NULL;

fail:
	fileSize = 0;
}

CFileMapping::~CFileMapping() {
	if (mapView) {
		UnmapViewOfFile(mapView);
		mapView = NULL;
	}

	if (hMapFile) {
		CloseHandle(hMapFile);
		hMapFile = NULL;
	}

	if (hFile) {
		if (hFile != INVALID_HANDLE_VALUE) {
			CloseHandle(hFile);
		}
		hFile = NULL;
	}

	fileSize = 0;
}

LPVOID CFileMapping::getMapView() const {
	return mapView;
}

SIZE_T CFileMapping::getFileSize() const {
	return fileSize;
}
