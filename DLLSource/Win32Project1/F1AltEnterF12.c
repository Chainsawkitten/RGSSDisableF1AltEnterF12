#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <Strsafe.h>

#ifdef F1ALTENTERF12_EXPORTS
#define F1ALTENTERF12_API __declspec(dllexport)
#else
#define F1ALTENTERF12_API __declspec(dllimport) 
#endif

int disableF1 = 1;
int disableF12 = 1;
int disableAltEnter = 1;

F1ALTENTERF12_API LRESULT CALLBACK messageHandling(int nCode, WPARAM wParam, LPARAM lParam) {
	BYTE keyboardState[256];
	GetKeyboardState(keyboardState);

	// Disable F12.
	if (disableF12) {
		keyboardState[VK_F12] = 0;
		SetKeyboardState(keyboardState);

		if (wParam == VK_F12)
			return 0;
	}

	// Disable F1.
	if (disableF1) {
		if (wParam == VK_F1)
			return 1;
	}

	// Disable Alt+Enter.
	if (disableAltEnter) {
		if (wParam == VK_RETURN && keyboardState[VK_MENU] != 0)
			return 1;
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

F1ALTENTERF12_API void hook(int f1, int f12, int altEnter) {
	disableF1 = f1;
	disableF12 = f12;
	disableAltEnter = altEnter;

	HOOKPROC hookProc;
	static HINSTANCE hinstDLL;
	static HHOOK hhook;;

	// Load module
	hinstDLL = LoadLibrary(L"F1AltEnterF12.dll");

	// Handle errors
	if (hinstDLL == NULL) {
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		// Display the error message and exit the process
		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCWSTR)"") + 40) * sizeof(TCHAR));
		StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), "", dw, lpMsgBuf);
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		ExitProcess(dw);
	}

	// Get hook procedure
	hookProc = (HOOKPROC)GetProcAddress(hinstDLL, "_messageHandling@12");

	// Handle errors
	if (hookProc == NULL) {
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		// Display the error message and exit the process
		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCWSTR)"") + 40) * sizeof(TCHAR));
		StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), "", dw, lpMsgBuf);
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		ExitProcess(dw);
	}

	// Set hook
	hhook = SetWindowsHookEx(WH_KEYBOARD, hookProc, hinstDLL, GetCurrentThreadId());

	// Handle errors
	if (hhook == NULL) {
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError();

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		// Display the error message and exit the process
		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCWSTR)"") + 40) * sizeof(TCHAR));
		StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), "", dw, lpMsgBuf);
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		ExitProcess(dw);
	}
}