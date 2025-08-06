#include "../exports.h"


void Log(const WCHAR* message) {
#ifdef _DEBUG
	//OutputDebugString(message);
	wprintf(message);
#endif
}

void CopyString(wchar_t const* source, rsize_t* size, LPWSTR dest) {
	rsize_t wsize = wcslen(source) + 1;

	if (size) {
		*size = wsize;
	}

	if (dest) {
		wcscpy_s(
			dest,
			wsize,
			source
		);
	}
}
