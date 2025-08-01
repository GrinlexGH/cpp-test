#pragma once

// Predefinitions for windows.h go here
//#define WIN32_LEAN_AND_MEAN   // Exclude rarely-used stuff from Windows headers

// Rarely modified header files should be included here
#include <vector>   // Add support for std::vector
#include <map>      // Add support for std::map
#include <string>   // Add support for std::string
#include <sstream>  // Add support for stringstream
#include <cassert>  // Add support for the assert macro
#include <stdio.h>  // Add support for C style printf, sprintf, etc.
#include <stdlib.h> // Add support for C style character conversions atoi etc.
#include <tchar.h>  // Add support for C style TCHARs.

// Add the Win32++ library
#include <wxx_appcore.h>         // Add CWinApp
#include <wxx_archive.h>         // Add CArchive
#include <wxx_controls.h>        // Add CAnimation, CComboBox, CComboBoxEx, CDateTime, CHeader, CHotKey, CIPAddress, CProgressBar, CSpinButton, CScrollBar, CSlider, CToolTip
#include <wxx_criticalsection.h> // Add CCriticalSection, CThreadLock
#include <wxx_cstring.h>         // Add CString, CStringA, CStringW
#include <wxx_ddx.h>             // Add CDataExchange
#include <wxx_dialog.h>          // Add CDialog, CResizer
#include <wxx_dockframe.h>       // Add CDockFrame, CMDIDockFrame
#include <wxx_docking.h>         // Add CDocker, CDockContainer
#include <wxx_exception.h>       // Add CException, CFileException, CNotSupportedException, CResourceException, CUserException, CWinException
#include <wxx_file.h>            // Add CFile
#include <wxx_filefind.h>        // Add CFileFind
#include <wxx_folderdialog.h>    // Add CFolderDialog
#include <wxx_frame.h>           // Add CFrame
#include <wxx_gdi.h>             // Add CDC, CGDIObject, CBitmap, CBrush, CFont, CPalatte, CPen, CRgn
#include <wxx_hglobal.h>         // Add CHGlobal
#include <wxx_imagelist.h>       // Add CImageList
#include <wxx_listview.h>        // Add CListView
#include <wxx_mdi.h>             // Add CMDIChild, CMDIFrame, CDockMDIFrame
#include <wxx_menu.h>            // Add CMenu
#include <wxx_menubar.h>         // Add CMenuBar
#include <wxx_metafile.h>        // Add CMetaFile, CEnhMetaFile
#include <wxx_mutex.h>           // Add CEvent, CMutex, CSemaphore
#include <wxx_propertysheet.h>   // Add CPropertyPage, CPropertySheet
#include <wxx_rebar.h>           // Add CRebar
#include <wxx_rect.h>            // Add CPoint, CRect, CSize
#include <wxx_regkey.h>          // Add CRegKey
#include <wxx_richedit.h>        // Add CRichEdit
#include <wxx_scrollview.h>      // Add CScrollView
#include <wxx_setup.h>           // Adds macros, windows header files, and CObject
#include <wxx_socket.h>          // Add CSocket
#include <wxx_statusbar.h>       // Add CStatusBar
#include <wxx_stdcontrols.h>     // Add CButton, CEdit, CListBox
#include <wxx_tab.h>             // Add CTab, CTabbedMDI
#include <wxx_textconv.h>        // Add AtoT, AtoW, TtoA, TtoW, WtoA, WtoT etc.
#include <wxx_themes.h>          // Add MenuTheme, ReBarTheme, StatusBarTheme, ToolBarTheme
#include <wxx_thread.h>          // Add CWinThread
#include <wxx_time.h>            // Add CTime
#include <wxx_toolbar.h>         // Add CToolBar
#include <wxx_treeview.h>        // Add CTreeView
#include <wxx_webbrowser.h>      // Add CWebBrowser, CAXHost
#include <wxx_wincore.h>         // Add CWnd

// WIN32_LEAN_AND_MEAN can't be used with these
#ifndef WIN32_LEAN_AND_MEAN
  #include <wxx_commondlg.h>        // Add CCommonDialog, CColorDialog, CFileDialog, CFindReplace, CFontDialog
  #include <wxx_preview.h>          // Add CPrintPreview
  #include <wxx_printdialogs.h>     // Add CPageSetupDialog, CPrintDialog
  #include <wxx_printdialogex.h>    // Add CPrintDialogEx

  // Visual Studio or Clang compiler
  #if defined (_MSC_VER) || defined(__clang_major__)
    #include <wxx_ribbon.h>         // Add CRibbon, CRibbonFrame
  #endif

  #include <wxx_taskdialog.h>       // Add CTaskDialog
#endif  // define WIN32_LEAN_AND_MEAN
