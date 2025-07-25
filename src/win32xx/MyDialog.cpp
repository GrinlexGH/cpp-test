#include "stdafx.h"
#include "MyDialog.h"
#include "resource.h"

// Constructor.
CMyDialog::CMyDialog(UINT resID) : CDialog(resID)
{
}

// Called when the dialog window is destroyed.
void CMyDialog::OnDestroy()
{
    // End the application
    ::PostQuitMessage(0);
}

// Process the dialog's window messages.
INT_PTR CMyDialog::DialogProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    try
    {
    //  switch (msg)
    //  {
    //  Additional messages to be handled go here
    //  }

        // Pass unhandled messages on to parent DialogProc.
        return DialogProcDefault(msg, wparam, lparam);
    }

    catch (const CException& e)
    {
        // Display the exception and continue.
        CString str1;
        str1 << e.GetText() << L'\n' << e.GetErrorString();
        CString str2;
        str2 << "Error: " << e.what();
        ::MessageBox(nullptr, str1, str2, MB_ICONERROR);
    }

    // Catch all unhandled std::exception types.
    catch (const std::exception& e)
    {
        // Display the exception and continue.
        CString str1 = e.what();
        ::MessageBox(nullptr, str1, L"Error: std::exception", MB_ICONERROR);
    }

    return 0;
}

// Handle the command notifications from controls.
BOOL CMyDialog::OnCommand(WPARAM wparam, LPARAM)
{
    UINT id = LOWORD(wparam);
    switch (id)
    {
    case IDC_BUTTON1:   return OnButton();
    case IDC_CHECK1:    return OnCheck1();
    case IDC_CHECK2:    return OnCheck2();
    case IDC_CHECK3:    return OnCheck3();

    case IDC_RADIO1:
    case IDC_RADIO2:    // intentionally blank
    case IDC_RADIO3:    return OnRangeOfRadioIDs(IDC_RADIO1, IDC_RADIO3, id);
    }

    return FALSE;
}

// Called before the dialog is displayed.
BOOL CMyDialog::OnInitDialog()
{
    // Set the application icon
    SetIconLarge(IDW_MAIN);
    SetIconSmall(IDW_MAIN);

    // Attach the controls to our CWnd member objects.
    AttachItem(IDC_EDIT1, m_edit);
    AttachItem(IDC_LIST1, m_listBox);
    AttachItem(IDC_RICHEDIT1, m_richEdit);

    // Put some text in the edit boxes
    SetDlgItemText(IDC_EDIT1, L"Edit Control");
    SetDlgItemText(IDC_RICHEDIT1, L"Rich Edit Window");

    // Put some text in the list box
    for (int i = 0; i < 8; i++)
        m_listBox.AddString(L"ListBox");

    // Select the first radio button
    CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1);

    // Ajust the pattern image size.
    m_patternImage.LoadBitmap(IDB_BITMAP1);
    m_patternImage = DpiScaleUpBitmap(m_patternImage);
    LPARAM lparam = reinterpret_cast<LPARAM>(m_patternImage.GetHandle());
    SendDlgItemMessage(IDC_STATIC1, STM_SETIMAGE, IMAGE_BITMAP, lparam);

    return TRUE;
}

// Called when the OK button or Enter key is pressed.
void CMyDialog::OnOK()
{
    MessageBox(L"OK Button Pressed.  Program will exit now.", L"Button", MB_OK);
    CDialog::OnOK();
}

// Called when the button is pressed.
BOOL CMyDialog::OnButton()
{
    SetDlgItemText(IDC_STATIC3, L"Button Pressed");
    TRACE("Button Pressed\n");
    return TRUE;
}

// Called when Check Box 1 is clicked.
BOOL CMyDialog::OnCheck1()
{
    SetDlgItemText(IDC_STATIC3, L"Check Box 1");
    TRACE("Check Box 1\n");
    return TRUE;
}

// Called when Check Box 2 is clicked.
BOOL CMyDialog::OnCheck2()
{
    SetDlgItemText(IDC_STATIC3, L"Check Box 2");
    TRACE("Check Box 2\n");
    return TRUE;
}

// Called when Check Box 3 is clicked.
BOOL CMyDialog::OnCheck3()
{
    SetDlgItemText(IDC_STATIC3, L"Check Box 3");
    TRACE("Check Box 3\n");
    return TRUE;
}

// Called when a radio button is selected.
BOOL CMyDialog::OnRangeOfRadioIDs(UINT idFirst, UINT idLast, UINT idClicked)
{
    CheckRadioButton(idFirst, idLast, idClicked);

    CString str;
    UINT button = idClicked - idFirst + 1U;
    str << "Radio" << button;
    TRACE(str); TRACE("\n");
    SetDlgItemText(IDC_STATIC3, str);

    return  TRUE;
}
