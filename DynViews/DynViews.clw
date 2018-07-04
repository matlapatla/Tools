; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDynViewsDlg
LastTemplate=CView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DynViews.h"

ClassCount=5
Class1=CDynViewsApp
Class2=CDynViewsDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DYNVIEWS_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Class4=CMyView
Class5=COpenGLView
Resource5=IDD_DYNVIEWS_DIALOG (English (U.S.))

[CLS:CDynViewsApp]
Type=0
HeaderFile=DynViews.h
ImplementationFile=DynViews.cpp
Filter=N

[CLS:CDynViewsDlg]
Type=0
HeaderFile=DynViewsDlg.h
ImplementationFile=DynViewsDlg.cpp
Filter=D
LastObject=IDC_ADDOPENGLVIEW
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=DynViewsDlg.h
ImplementationFile=DynViewsDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_DYNVIEWS_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CDynViewsDlg

[DLG:IDD_DYNVIEWS_DIALOG (English (U.S.))]
Type=1
Class=CDynViewsDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TABCTRL,SysTabControl32,1342177280
Control4=IDC_ADDVIEW,button,1342242816
Control5=IDC_ADDOPENGLVIEW,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CMyView]
Type=0
HeaderFile=MyView.h
ImplementationFile=MyView.cpp
BaseClass=CView
Filter=C
LastObject=CMyView
VirtualFilter=VWC

[CLS:COpenGLView]
Type=0
HeaderFile=OpenGLView.h
ImplementationFile=OpenGLView.cpp
BaseClass=CMyView
Filter=C
VirtualFilter=VWC

