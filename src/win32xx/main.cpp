#include "stdafx.h"
#include "DialogApp.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
    try {
        // Start Win32++.
        CDialogApp theApp;

        // Run the application.
        return theApp.Run();
    } catch (const CException& e) { // Catch all unhandled CException types.
        // Display the exception and continue.
        CString str1;
        str1 << e.GetText() << L'\n' << e.GetErrorString();
        CString str2;
        str2 << "Error: " << e.what();
        ::MessageBox(nullptr, str1, str2, MB_ICONERROR);
    } catch (const std::exception& e) { // Catch all unhandled std::exception types.
        // Display the exception and continue.
        CString str1 = e.what();
        ::MessageBox(nullptr, str1, L"Error: std::exception", MB_ICONERROR);
    }

    return -1;
}
