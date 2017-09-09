VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Object = "{AC4C85D1-B16C-11D1-A718-006008C5F933}#2.0#0"; "G2Com.dll"
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "shdocvw.dll"
Object = "{DBCC7B7A-4EED-474B-9030-EBBA207E7157}#1.0#0"; "Project1.ocx"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Test Cases"
   ClientHeight    =   7830
   ClientLeft      =   4470
   ClientTop       =   3105
   ClientWidth     =   10755
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7830
   ScaleWidth      =   10755
   StartUpPosition =   2  'CenterScreen
   Begin TabDlg.SSTab TestTabTabular 
      Height          =   7815
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   10755
      _ExtentX        =   18971
      _ExtentY        =   13785
      _Version        =   393216
      Style           =   1
      Tabs            =   2
      Tab             =   1
      TabsPerRow      =   15
      TabHeight       =   520
      TabCaption(0)   =   "Linking G2 Server with COM-compliant application"
      TabPicture(0)   =   "Form.frx":0000
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "TestTab1"
      Tab(0).ControlCount=   1
      TabCaption(1)   =   "Data Types"
      TabPicture(1)   =   "Form.frx":001C
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "TC73TestCaseTab"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).ControlCount=   1
      Begin TabDlg.SSTab TestTab1 
         Height          =   7095
         Left            =   -74880
         TabIndex        =   1
         Top             =   480
         Width           =   10485
         _ExtentX        =   18494
         _ExtentY        =   12515
         _Version        =   393216
         Tabs            =   13
         Tab             =   10
         TabHeight       =   520
         TabCaption(0)   =   "Test Case 4"
         TabPicture(0)   =   "Form.frx":0038
         Tab(0).ControlEnabled=   0   'False
         Tab(0).Control(0)=   "TC4Param(0)"
         Tab(0).Control(1)=   "TC4Command(1)"
         Tab(0).Control(2)=   "TC4Step3"
         Tab(0).Control(3)=   "TC4Step2"
         Tab(0).Control(4)=   "TC4Step1"
         Tab(0).Control(5)=   "Label3(1)"
         Tab(0).Control(6)=   "Label2(1)"
         Tab(0).ControlCount=   7
         TabCaption(1)   =   "Test Case 6"
         TabPicture(1)   =   "Form.frx":0054
         Tab(1).ControlEnabled=   0   'False
         Tab(1).Control(0)=   "TC6Command"
         Tab(1).Control(1)=   "TC6Step2"
         Tab(1).Control(2)=   "TC6G2Gateway1"
         Tab(1).Control(3)=   "TC6Step1"
         Tab(1).Control(4)=   "Label4"
         Tab(1).ControlCount=   5
         TabCaption(2)   =   "Test Case 7"
         TabPicture(2)   =   "Form.frx":0070
         Tab(2).ControlEnabled=   0   'False
         Tab(2).Control(0)=   "TC7Connection"
         Tab(2).Control(1)=   "TC7StartRPC"
         Tab(2).Control(2)=   "TC7StartItem"
         Tab(2).Control(3)=   "TC7CallRPC"
         Tab(2).Control(4)=   "TC7CallItemRetVal"
         Tab(2).Control(4).Enabled=   0   'False
         Tab(2).Control(5)=   "TC7CallItem"
         Tab(2).Control(6)=   "TC7Frame2"
         Tab(2).Control(7)=   "TC7Frame1"
         Tab(2).Control(8)=   "TCCycleLights"
         Tab(2).Control(9)=   "TC7G2Gateway"
         Tab(2).Control(10)=   "TC7Label1"
         Tab(2).Control(11)=   "TC7Redlight"
         Tab(2).Control(12)=   "TC7Yellowlight"
         Tab(2).Control(13)=   "TC7Greenlight"
         Tab(2).Control(14)=   "TC7Shape4"
         Tab(2).Control(15)=   "TC7Label5"
         Tab(2).ControlCount=   16
         TabCaption(3)   =   "Test Case 8"
         TabPicture(3)   =   "Form.frx":008C
         Tab(3).ControlEnabled=   0   'False
         Tab(3).Control(0)=   "TC8Command"
         Tab(3).Control(1)=   "TC8Conn"
         Tab(3).Control(2)=   "TC8LabelRes"
         Tab(3).Control(3)=   "TC8G2Gateway"
         Tab(3).Control(4)=   "TC8Label5"
         Tab(3).Control(5)=   "TC8Label1"
         Tab(3).ControlCount=   6
         TabCaption(4)   =   "Test Case 9"
         TabPicture(4)   =   "Form.frx":00A8
         Tab(4).ControlEnabled=   0   'False
         Tab(4).Control(0)=   "TC9Command"
         Tab(4).Control(1)=   "TC9Wait"
         Tab(4).Control(2)=   "TC9ConString"
         Tab(4).Control(3)=   "TC9ConLabel"
         Tab(4).Control(4)=   "TC9Label1"
         Tab(4).ControlCount=   5
         TabCaption(5)   =   "Test Case 10"
         TabPicture(5)   =   "Form.frx":00C4
         Tab(5).ControlEnabled=   0   'False
         Tab(5).Control(0)=   "TC10Frame1"
         Tab(5).Control(1)=   "TC10ConString"
         Tab(5).Control(2)=   "TC10G2Gateway"
         Tab(5).Control(3)=   "Tc10Label1"
         Tab(5).Control(4)=   "TC10Caption"
         Tab(5).ControlCount=   5
         TabCaption(6)   =   "Test Case 11"
         TabPicture(6)   =   "Form.frx":00E0
         Tab(6).ControlEnabled=   0   'False
         Tab(6).Control(0)=   "TC11Frame2"
         Tab(6).Control(1)=   "TC11Frame1"
         Tab(6).Control(2)=   "TC11ConStr"
         Tab(6).Control(3)=   "TC11G2Gateway"
         Tab(6).Control(4)=   "TC11ConsLab"
         Tab(6).Control(5)=   "TC11Caption"
         Tab(6).ControlCount=   6
         TabCaption(7)   =   "Test Case 12"
         TabPicture(7)   =   "Form.frx":00FC
         Tab(7).ControlEnabled=   0   'False
         Tab(7).Control(0)=   "TC12Label5"
         Tab(7).Control(1)=   "TC12Shape4"
         Tab(7).Control(2)=   "TC12Red"
         Tab(7).Control(3)=   "TC12Yel"
         Tab(7).Control(4)=   "TC12Green"
         Tab(7).Control(5)=   "TC12G2Gateway"
         Tab(7).Control(6)=   "Label5"
         Tab(7).Control(7)=   "TC12Command"
         Tab(7).Control(8)=   "TC12ConStr"
         Tab(7).Control(9)=   "TC12Reconnect"
         Tab(7).ControlCount=   10
         TabCaption(8)   =   "Test Case 22"
         TabPicture(8)   =   "Form.frx":0118
         Tab(8).ControlEnabled=   0   'False
         Tab(8).Control(0)=   "TC22WebBrowser"
         Tab(8).Control(1)=   "TC22Start"
         Tab(8).Control(2)=   "TC22Label"
         Tab(8).ControlCount=   3
         TabCaption(9)   =   "Test Case 23"
         TabPicture(9)   =   "Form.frx":0134
         Tab(9).ControlEnabled=   0   'False
         Tab(9).Control(0)=   "TC23WebBrowser"
         Tab(9).Control(1)=   "TC23Start"
         Tab(9).Control(2)=   "TC23Label"
         Tab(9).ControlCount=   3
         TabCaption(10)  =   "Test Case 24"
         TabPicture(10)  =   "Form.frx":0150
         Tab(10).ControlEnabled=   -1  'True
         Tab(10).Control(0)=   "Label6"
         Tab(10).Control(0).Enabled=   0   'False
         Tab(10).Control(1)=   "TC24Start"
         Tab(10).Control(1).Enabled=   0   'False
         Tab(10).Control(2)=   "TC24Text"
         Tab(10).Control(2).Enabled=   0   'False
         Tab(10).ControlCount=   3
         TabCaption(11)  =   "Test Case 25"
         TabPicture(11)  =   "Form.frx":016C
         Tab(11).ControlEnabled=   0   'False
         Tab(11).Control(0)=   "TC25Start"
         Tab(11).Control(1)=   "TC25Label"
         Tab(11).ControlCount=   2
         TabCaption(12)  =   "Test Case 92"
         TabPicture(12)  =   "Form.frx":0188
         Tab(12).ControlEnabled=   0   'False
         Tab(12).Control(0)=   "Picture1"
         Tab(12).Control(1)=   "Command1"
         Tab(12).Control(2)=   "Image1"
         Tab(12).Control(3)=   "Label2(0)"
         Tab(12).ControlCount=   4
         Begin VB.PictureBox Picture1 
            Height          =   1575
            Left            =   -72360
            ScaleHeight     =   1515
            ScaleWidth      =   1755
            TabIndex        =   81
            Top             =   2760
            Width           =   1815
         End
         Begin VB.CommandButton Command1 
            Caption         =   "Get icon from G2"
            Height          =   495
            Left            =   -74520
            TabIndex        =   80
            Top             =   2760
            Width           =   1815
         End
         Begin VB.CommandButton TC25Start 
            Caption         =   "Start"
            Height          =   375
            Left            =   -74880
            TabIndex        =   71
            Top             =   2340
            Width           =   9735
         End
         Begin VB.TextBox TC24Text 
            Enabled         =   0   'False
            Height          =   4335
            Left            =   360
            MultiLine       =   -1  'True
            TabIndex        =   69
            Top             =   2940
            Width           =   9375
         End
         Begin VB.CommandButton TC24Start 
            Caption         =   "Start"
            Height          =   375
            Left            =   360
            TabIndex        =   68
            Top             =   2340
            Width           =   9375
         End
         Begin SHDocVwCtl.WebBrowser TC23WebBrowser 
            Height          =   4335
            Left            =   -74880
            TabIndex        =   66
            Top             =   2940
            Width           =   9735
            ExtentX         =   17171
            ExtentY         =   7646
            ViewMode        =   0
            Offline         =   0
            Silent          =   0
            RegisterAsBrowser=   0
            RegisterAsDropTarget=   1
            AutoArrange     =   0   'False
            NoClientEdge    =   0   'False
            AlignLeft       =   0   'False
            NoWebView       =   0   'False
            HideFileNames   =   0   'False
            SingleClick     =   0   'False
            SingleSelection =   0   'False
            NoFolders       =   0   'False
            Transparent     =   0   'False
            ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
            Location        =   "http:///"
         End
         Begin SHDocVwCtl.WebBrowser TC22WebBrowser 
            Height          =   4335
            Left            =   -74640
            TabIndex        =   65
            Top             =   2940
            Width           =   9495
            ExtentX         =   16748
            ExtentY         =   7646
            ViewMode        =   0
            Offline         =   0
            Silent          =   0
            RegisterAsBrowser=   0
            RegisterAsDropTarget=   1
            AutoArrange     =   0   'False
            NoClientEdge    =   0   'False
            AlignLeft       =   0   'False
            NoWebView       =   0   'False
            HideFileNames   =   0   'False
            SingleClick     =   0   'False
            SingleSelection =   0   'False
            NoFolders       =   0   'False
            Transparent     =   0   'False
            ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
            Location        =   "http:///"
         End
         Begin VB.CommandButton TC23Start 
            Caption         =   "Start"
            Height          =   375
            Left            =   -74880
            TabIndex        =   64
            Top             =   2460
            Width           =   9735
         End
         Begin VB.CommandButton TC22Start 
            Caption         =   "Start"
            Height          =   375
            Left            =   -74760
            TabIndex        =   62
            Top             =   2400
            Width           =   9615
         End
         Begin VB.CommandButton TC12Reconnect 
            Caption         =   "Connect"
            Height          =   375
            Left            =   -70920
            TabIndex        =   60
            Tag             =   "1"
            Top             =   2520
            Width           =   1215
         End
         Begin VB.TextBox TC12ConStr 
            Height          =   405
            Left            =   -73080
            TabIndex        =   59
            Text            =   "localhost:1111"
            Top             =   2520
            Width           =   1935
         End
         Begin VB.CommandButton TC12Command 
            Caption         =   "Cycle Lights"
            Height          =   495
            Left            =   -71760
            TabIndex        =   57
            Top             =   4350
            Width           =   1215
         End
         Begin VB.Frame TC11Frame2 
            Caption         =   "Call G2 Procedure"
            Height          =   1935
            Left            =   -71160
            TabIndex        =   49
            Top             =   3720
            Width           =   2415
            Begin VB.TextBox TC11Res 
               Enabled         =   0   'False
               Height          =   405
               Left            =   1080
               TabIndex        =   54
               Top             =   1440
               Width           =   975
            End
            Begin VB.TextBox TC11Input 
               Height          =   375
               Left            =   1080
               TabIndex        =   52
               Text            =   "100"
               Top             =   960
               Width           =   975
            End
            Begin VB.CommandButton TC11CALL 
               Caption         =   "Call"
               Height          =   495
               Left            =   600
               TabIndex        =   50
               Top             =   360
               Width           =   1215
            End
            Begin VB.Label TC11Label6 
               Caption         =   "Result"
               Height          =   255
               Left            =   120
               TabIndex        =   53
               Top             =   1560
               Width           =   615
            End
            Begin VB.Label TC11Label5 
               Caption         =   "Input"
               Height          =   255
               Left            =   120
               TabIndex        =   51
               Top             =   1080
               Width           =   735
            End
         End
         Begin VB.Frame TC11Frame1 
            Caption         =   "Display Data in G2"
            Height          =   1935
            Left            =   -74040
            TabIndex        =   45
            Top             =   3720
            Width           =   2295
            Begin VB.TextBox TC11MsgText 
               Height          =   375
               Left            =   120
               TabIndex        =   47
               Text            =   "Hello G2"
               Top             =   1320
               Width           =   2055
            End
            Begin VB.CommandButton TC11PostMsg 
               Caption         =   "Post Message"
               Height          =   495
               Left            =   480
               TabIndex        =   46
               Top             =   360
               Width           =   1215
            End
            Begin VB.Label Label1 
               Caption         =   "Message"
               Height          =   255
               Left            =   480
               TabIndex        =   48
               Top             =   960
               Width           =   1575
            End
         End
         Begin VB.TextBox TC11ConStr 
            Height          =   375
            Left            =   -72600
            TabIndex        =   44
            Text            =   "localhost:1111"
            Top             =   2640
            Width           =   2295
         End
         Begin VB.Frame TC10Frame1 
            Caption         =   "Post Message"
            Height          =   1095
            Left            =   -74280
            TabIndex        =   39
            Top             =   3900
            Width           =   4215
            Begin VB.CommandButton TC10Post 
               Caption         =   "Post"
               Height          =   375
               Left            =   3000
               TabIndex        =   41
               Top             =   360
               Width           =   1095
            End
            Begin VB.TextBox TC10Msg 
               Height          =   375
               Left            =   120
               TabIndex        =   40
               Text            =   "Test Message"
               Top             =   360
               Width           =   2775
            End
         End
         Begin VB.TextBox TC10ConString 
            Height          =   375
            Left            =   -72360
            TabIndex        =   38
            Text            =   "localhost:1111"
            Top             =   3180
            Width           =   2175
         End
         Begin VB.CommandButton TC9Command 
            Caption         =   "Start"
            Height          =   495
            Left            =   -74400
            TabIndex        =   35
            Top             =   4260
            Width           =   2055
         End
         Begin VB.CheckBox TC9Wait 
            Caption         =   "Wait connection establish"
            Height          =   255
            Left            =   -74400
            TabIndex        =   34
            Top             =   3660
            Width           =   2415
         End
         Begin VB.TextBox TC9ConString 
            Height          =   375
            Left            =   -72960
            TabIndex        =   33
            Text            =   "localhost:1111"
            Top             =   2940
            Width           =   1935
         End
         Begin VB.TextBox TC7Connection 
            Height          =   375
            Left            =   -72120
            TabIndex        =   30
            Text            =   "localhost:1111"
            Top             =   3180
            Width           =   1695
         End
         Begin VB.CommandButton TC8Command 
            Caption         =   "Start Communication"
            Height          =   495
            Left            =   -74520
            TabIndex        =   28
            Top             =   4620
            Width           =   1695
         End
         Begin VB.TextBox TC8Conn 
            Height          =   375
            Left            =   -72960
            TabIndex        =   27
            Text            =   "localhost:1111"
            Top             =   3420
            Width           =   2295
         End
         Begin VB.CommandButton TC7StartRPC 
            Caption         =   "Post Message"
            Height          =   495
            Left            =   -72180
            TabIndex        =   19
            Top             =   4440
            Width           =   1215
         End
         Begin VB.TextBox TC7StartItem 
            Height          =   285
            Left            =   -72480
            TabIndex        =   17
            Text            =   "Hello G2!"
            Top             =   5640
            Width           =   1935
         End
         Begin VB.CommandButton TC7CallRPC 
            Caption         =   "Call"
            Height          =   495
            Left            =   -69480
            TabIndex        =   18
            Top             =   4320
            Width           =   1215
         End
         Begin VB.TextBox TC7CallItemRetVal 
            ForeColor       =   &H80000003&
            Height          =   285
            Left            =   -69120
            TabIndex        =   15
            TabStop         =   0   'False
            Top             =   5520
            Width           =   975
         End
         Begin VB.TextBox TC7CallItem 
            Height          =   285
            Left            =   -69120
            TabIndex        =   16
            Text            =   "100"
            Top             =   5040
            Width           =   975
         End
         Begin VB.Frame TC7Frame2 
            Caption         =   "Call G2 Procedure"
            Height          =   1935
            Left            =   -70080
            TabIndex        =   22
            Top             =   4080
            Width           =   2295
            Begin VB.Label TCInput 
               Caption         =   "Input:"
               Height          =   210
               Index           =   0
               Left            =   360
               TabIndex        =   24
               Top             =   1065
               Width           =   495
            End
            Begin VB.Label TC7Label7 
               Caption         =   "Result:"
               Height          =   225
               Left            =   315
               TabIndex        =   23
               Top             =   1500
               Width           =   540
            End
         End
         Begin VB.Frame TC7Frame1 
            Caption         =   "Display Data In G2"
            Height          =   1935
            Left            =   -72720
            TabIndex        =   20
            Top             =   4080
            Width           =   2295
            Begin VB.Label TC7Label6 
               Caption         =   "Enter Message to Display on G2 Message Board"
               Height          =   390
               Left            =   270
               TabIndex        =   21
               Top             =   1020
               Width           =   1860
            End
         End
         Begin VB.CommandButton TCCycleLights 
            Caption         =   "Cycle Lights"
            Height          =   495
            Left            =   -66105
            TabIndex        =   14
            Top             =   6255
            Visible         =   0   'False
            Width           =   1215
         End
         Begin VB.CommandButton TC6Command 
            Caption         =   "Set G2Location = ""pc1:1122"""
            Height          =   375
            Left            =   -74400
            TabIndex        =   10
            Top             =   4440
            Width           =   3495
         End
         Begin VB.TextBox TC4Param 
            Height          =   405
            Index           =   0
            Left            =   -73800
            TabIndex        =   7
            Text            =   "TestValue"
            Top             =   4320
            Width           =   1815
         End
         Begin VB.CommandButton TC4Command 
            Caption         =   "Start Test Case"
            Height          =   375
            Index           =   1
            Left            =   -73920
            TabIndex        =   3
            Top             =   5160
            Width           =   2055
         End
         Begin VB.Image Image1 
            Height          =   1575
            Left            =   -69840
            Stretch         =   -1  'True
            Top             =   2760
            Width           =   1815
         End
         Begin VB.Label Label2 
            Alignment       =   2  'Center
            AutoSize        =   -1  'True
            Caption         =   "Test Case 92:  Getting the Icon for a G2Item"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   300
            Index           =   0
            Left            =   -74880
            TabIndex        =   79
            Top             =   1920
            Width           =   5445
            WordWrap        =   -1  'True
         End
         Begin VB.Label TC25Label 
            Caption         =   "Test Case 25: Using G2 ActiveXLink in C++ with MFC"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   -74880
            TabIndex        =   70
            Top             =   1800
            Width           =   9735
         End
         Begin VB.Label Label6 
            Caption         =   "Test Case 24:  Example of the Use of ActiveXLink in a C++ Program"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   615
            Left            =   240
            TabIndex        =   67
            Top             =   1800
            Width           =   9375
         End
         Begin VB.Label TC23Label 
            Caption         =   "Test Case 23: Sending a Message to G2 from Internet Explorer(Using G2 ActiveXLink with Microsoft Internet Explorer)"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   735
            Left            =   -74880
            TabIndex        =   63
            Top             =   1800
            Width           =   9615
         End
         Begin VB.Label TC22Label 
            Caption         =   "Test Case 22:  Connecting with G2 on Startup (Using G2 ActiveXLink with Microsoft Internet Explorer)"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   615
            Left            =   -74760
            TabIndex        =   61
            Top             =   1800
            Width           =   9735
         End
         Begin VB.Label Label5 
            Caption         =   "Connection String"
            Height          =   375
            Left            =   -74640
            TabIndex        =   58
            Top             =   2640
            Width           =   2415
         End
         Begin GensymAxlCtl.G2Gateway TC12G2Gateway 
            Left            =   -74280
            OleObjectBlob   =   "Form.frx":01A4
            Top             =   6000
         End
         Begin VB.Shape TC12Green 
            FillColor       =   &H0000FF00&
            FillStyle       =   0  'Solid
            Height          =   495
            Left            =   -72720
            Shape           =   3  'Circle
            Top             =   5040
            Width           =   495
         End
         Begin VB.Shape TC12Yel 
            FillColor       =   &H0000FFFF&
            FillStyle       =   0  'Solid
            Height          =   495
            Left            =   -72720
            Shape           =   3  'Circle
            Top             =   4440
            Width           =   495
         End
         Begin VB.Shape TC12Red 
            FillColor       =   &H000000FF&
            FillStyle       =   0  'Solid
            Height          =   495
            Left            =   -72720
            Shape           =   3  'Circle
            Top             =   3840
            Width           =   495
         End
         Begin VB.Shape TC12Shape4 
            FillColor       =   &H00404040&
            FillStyle       =   0  'Solid
            Height          =   1935
            Left            =   -72840
            Top             =   3720
            Width           =   735
         End
         Begin VB.Label TC12Label5 
            Caption         =   "Test Case 12:  Calling a Procedure in G2 and Visual Basic(Using G2 ActiveXLink with Microsoft Visual Basic)"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   975
            Left            =   -74760
            TabIndex        =   56
            Top             =   1800
            Width           =   9615
         End
         Begin VB.Label TC8LabelRes 
            Caption         =   "If Test Case work corret in G2 should appear following message: Test Case 8: Test method 'Call' from G2 ActiveX"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   9.75
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   -1  'True
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H000000FF&
            Height          =   495
            Left            =   -72480
            TabIndex        =   55
            Top             =   4560
            Width           =   6255
         End
         Begin GensymAxlCtl.G2Gateway TC11G2Gateway 
            Left            =   -74400
            OleObjectBlob   =   "Form.frx":0226
            Top             =   6000
         End
         Begin VB.Label TC11ConsLab 
            Caption         =   "Connection String"
            Height          =   495
            Left            =   -74400
            TabIndex        =   43
            Top             =   2760
            Width           =   2895
         End
         Begin VB.Label TC11Caption 
            Caption         =   "Test Case 11:  Calling a Procedure in G2(Using G2 ActiveXLink with Microsoft Visual Basic) "
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   615
            Left            =   -74520
            TabIndex        =   42
            Top             =   1800
            Width           =   9255
         End
         Begin GensymAxlCtl.G2Gateway TC10G2Gateway 
            Left            =   -74520
            OleObjectBlob   =   "Form.frx":02A8
            Top             =   5460
         End
         Begin VB.Label Tc10Label1 
            Caption         =   "Connection String"
            Height          =   255
            Left            =   -74400
            TabIndex        =   37
            Top             =   3300
            Width           =   2295
         End
         Begin VB.Label TC10Caption 
            Caption         =   "Test Case 10:  Posting a Message on the G2 Message Board to communicate with G2 (Using G2 ActiveXLink with Microsoft Visual Basic)"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   735
            Left            =   -74760
            TabIndex        =   36
            Top             =   1800
            Width           =   9255
         End
         Begin VB.Label TC9ConLabel 
            Caption         =   "Connection String"
            Height          =   375
            Left            =   -74520
            TabIndex        =   32
            Top             =   3060
            Width           =   2295
         End
         Begin VB.Label TC9Label1 
            Caption         =   "Test Case 9:  Connecting with G2 on Startup (Using G2 ActiveXLink with Microsoft Visual Basic)"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   615
            Left            =   -74880
            TabIndex        =   31
            Top             =   1800
            Width           =   9375
         End
         Begin GensymAxlCtl.G2Gateway TC7G2Gateway 
            Left            =   -74280
            OleObjectBlob   =   "Form.frx":032A
            Top             =   6660
         End
         Begin VB.Label TC7Label1 
            Caption         =   "Connection string"
            Height          =   375
            Left            =   -74640
            TabIndex        =   29
            Top             =   3180
            Width           =   2415
         End
         Begin GensymAxlCtl.G2Gateway TC8G2Gateway 
            Left            =   -74160
            OleObjectBlob   =   "Form.frx":03AC
            Top             =   5220
         End
         Begin VB.Label TC8Label5 
            Caption         =   "Connection String"
            Height          =   375
            Left            =   -74520
            TabIndex        =   26
            Top             =   3540
            Width           =   2655
         End
         Begin VB.Label TC8Label1 
            Caption         =   "Test Case 8:   Making a connection to G2(Using G2 ActiveXLink with Microsoft Visual Basic )"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   615
            Left            =   -74760
            TabIndex        =   25
            Top             =   1800
            Width           =   9615
         End
         Begin VB.Shape TC7Redlight 
            FillColor       =   &H00000040&
            FillStyle       =   0  'Solid
            Height          =   495
            Left            =   -67080
            Shape           =   3  'Circle
            Top             =   5640
            Visible         =   0   'False
            Width           =   495
         End
         Begin VB.Shape TC7Yellowlight 
            FillColor       =   &H00004040&
            FillStyle       =   0  'Solid
            Height          =   495
            Left            =   -67080
            Shape           =   3  'Circle
            Top             =   6180
            Visible         =   0   'False
            Width           =   495
         End
         Begin VB.Shape TC7Greenlight 
            FillColor       =   &H00004000&
            FillStyle       =   0  'Solid
            Height          =   495
            Left            =   -67080
            Shape           =   3  'Circle
            Top             =   6840
            Visible         =   0   'False
            Width           =   495
         End
         Begin VB.Shape TC7Shape4 
            FillColor       =   &H0080FFFF&
            FillStyle       =   0  'Solid
            Height          =   1815
            Left            =   -67200
            Top             =   5625
            Visible         =   0   'False
            Width           =   735
         End
         Begin VB.Label TC7Label5 
            Caption         =   "Test Case 7: Building Your Connection Form (Using G2 ActiveXLink with Microsoft Visual Basic)"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   735
            Left            =   -74760
            TabIndex        =   13
            Top             =   1800
            Width           =   9495
         End
         Begin VB.Label TC6Step2 
            Caption         =   "2.Done"
            Height          =   255
            Left            =   -74400
            TabIndex        =   12
            Top             =   3960
            Width           =   2895
         End
         Begin VB.Label TC4Step3 
            Caption         =   "3. Done"
            Height          =   255
            Left            =   -73800
            TabIndex        =   11
            Top             =   3720
            Width           =   2775
         End
         Begin GensymAxlCtl.G2Gateway TC6G2Gateway1 
            Left            =   -74400
            OleObjectBlob   =   "Form.frx":042E
            Top             =   5280
         End
         Begin VB.Label TC6Step1 
            Caption         =   $"Form.frx":04B0
            Height          =   375
            Left            =   -74400
            TabIndex        =   9
            Top             =   3360
            Width           =   6255
         End
         Begin VB.Label Label4 
            Caption         =   "Test Case 6: Setting Properties Programmatically of the G2 ActiveXLink control (Using G2 ActiveXLink with Microsoft Visual Basic)"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   735
            Left            =   -74880
            TabIndex        =   8
            Top             =   1800
            Width           =   9615
         End
         Begin VB.Label TC4Step2 
            Caption         =   "2. Use it to start a G2 procedure in a running G2"
            Height          =   495
            Left            =   -73800
            TabIndex        =   6
            Top             =   3480
            Width           =   4095
         End
         Begin VB.Label TC4Step1 
            Caption         =   "1. Create an Instance of the control"
            Height          =   375
            Left            =   -73800
            TabIndex        =   5
            Top             =   3240
            Width           =   2895
         End
         Begin VB.Label Label3 
            Caption         =   "Procedure Parameter"
            Height          =   255
            Index           =   1
            Left            =   -73920
            TabIndex        =   4
            Top             =   4080
            Width           =   3975
         End
         Begin VB.Label Label2 
            Alignment       =   2  'Center
            AutoSize        =   -1  'True
            Caption         =   "Test Case 4:  Creating the Control Programmatically ( Using G2 ActiveXLink with Microsoft Visual Basic)"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   840
            Index           =   1
            Left            =   -74880
            TabIndex        =   2
            Top             =   1800
            Width           =   9855
            WordWrap        =   -1  'True
         End
      End
      Begin TabDlg.SSTab TC73TestCaseTab 
         Height          =   6855
         Left            =   120
         TabIndex        =   72
         Top             =   720
         Width           =   10335
         _ExtentX        =   18230
         _ExtentY        =   12091
         _Version        =   393216
         Tabs            =   1
         TabHeight       =   520
         TabCaption(0)   =   "Test Case "
         TabPicture(0)   =   "Form.frx":0545
         Tab(0).ControlEnabled=   -1  'True
         Tab(0).Control(0)=   "TXCLocLab"
         Tab(0).Control(0).Enabled=   0   'False
         Tab(0).Control(1)=   "TCXG2Gateway"
         Tab(0).Control(1).Enabled=   0   'False
         Tab(0).Control(2)=   "Label7"
         Tab(0).Control(2).Enabled=   0   'False
         Tab(0).Control(3)=   "TC91G2Gateway"
         Tab(0).Control(3).Enabled=   0   'False
         Tab(0).Control(4)=   "TCXConnect"
         Tab(0).Control(4).Enabled=   0   'False
         Tab(0).Control(5)=   "TCXConStr"
         Tab(0).Control(5).Enabled=   0   'False
         Tab(0).Control(6)=   "TCXConsole"
         Tab(0).Control(6).Enabled=   0   'False
         Tab(0).Control(7)=   "TCXStart"
         Tab(0).Control(7).Enabled=   0   'False
         Tab(0).Control(8)=   "TCXTestCase90"
         Tab(0).Control(8).Enabled=   0   'False
         Tab(0).ControlCount=   9
         Begin Project1.UserControl1 TCXTestCase90 
            Height          =   375
            Left            =   6720
            TabIndex        =   82
            Top             =   480
            Width           =   1815
            _ExtentX        =   3201
            _ExtentY        =   661
         End
         Begin VB.CommandButton TCXStart 
            Caption         =   "Start"
            Height          =   255
            Left            =   240
            TabIndex        =   76
            Top             =   1560
            Width           =   9855
         End
         Begin VB.TextBox TCXConsole 
            Height          =   4815
            Left            =   240
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   75
            Top             =   1800
            Width           =   9855
         End
         Begin VB.TextBox TCXConStr 
            Height          =   285
            Left            =   2160
            TabIndex        =   74
            Text            =   "localhost:1111"
            Top             =   1080
            Width           =   3255
         End
         Begin VB.CommandButton TCXConnect 
            Caption         =   "Connect"
            Height          =   300
            Left            =   5520
            TabIndex        =   73
            Tag             =   "1"
            Top             =   1080
            Width           =   1215
         End
         Begin GensymAxlCtl.G2Gateway TC91G2Gateway 
            Left            =   9480
            OleObjectBlob   =   "Form.frx":0561
            Top             =   480
         End
         Begin VB.Label Label7 
            Caption         =   "Data Types Test Case"
            BeginProperty Font 
               Name            =   "MS Sans Serif"
               Size            =   12
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   240
            TabIndex        =   78
            Top             =   600
            Width           =   3615
         End
         Begin GensymAxlCtl.G2Gateway TCXG2Gateway 
            Left            =   8640
            OleObjectBlob   =   "Form.frx":05EB
            Top             =   480
         End
         Begin VB.Label TXCLocLab 
            Caption         =   "Connection String"
            Height          =   255
            Left            =   840
            TabIndex        =   77
            Top             =   1080
            Width           =   1335
         End
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public TC12NextMode As String
Public TC12Mode As String
Public winX99 As G2Window
Public gitX99 As G2Item
      Private Declare Function CreatePipe Lib "kernel32" ( _
          phReadPipe As Long, _
          phWritePipe As Long, _
          lpPipeAttributes As Any, _
          ByVal nSize As Long) As Long

      Private Declare Function ReadFile Lib "kernel32" ( _
          ByVal hFile As Long, _
          ByVal lpBuffer As String, _
          ByVal nNumberOfBytesToRead As Long, _
          lpNumberOfBytesRead As Long, _
          ByVal lpOverlapped As Any) As Long

      Private Type SECURITY_ATTRIBUTES
          nLength As Long
          lpSecurityDescriptor As Long
          bInheritHandle As Long
      End Type

      Private Type STARTUPINFO
         cb As Long
         lpReserved As Long
         lpDesktop As Long
         lpTitle As Long
         dwX As Long
         dwY As Long
         dwXSize As Long
         dwYSize As Long
         dwXCountChars As Long
         dwYCountChars As Long
         dwFillAttribute As Long
         dwFlags As Long
         wShowWindow As Integer
         cbReserved2 As Integer
         lpReserved2 As Long
         hStdInput As Long
         hStdOutput As Long
         hStdError As Long
      End Type

      Private Type PROCESS_INFORMATION
         hProcess As Long
         hThread As Long
         dwProcessID As Long
         dwThreadID As Long
      End Type

      Private Declare Function CreateProcessA Lib "kernel32" (ByVal _
         lpApplicationName As Long, ByVal lpCommandLine As String, _
         lpProcessAttributes As Any, lpThreadAttributes As Any, _
         ByVal bInheritHandles As Long, ByVal dwCreationFlags As Long, _
         ByVal lpEnvironment As Long, ByVal lpCurrentDirectory As Long, _
         lpStartupInfo As Any, lpProcessInformation As Any) As Long

      Private Declare Function CloseHandle Lib "kernel32" (ByVal _
         hObject As Long) As Long
      Private Declare Function SetHandleInformation Lib "kernel32" (ByVal _
         hObject As Long, ByVal dwMask As Integer, ByVal dwFlags As Integer) As Long
      Private Declare Function WaitForSingleObject Lib "kernel32" (ByVal _
         hObject As Long, ByVal Wait As Long) As Long
      Private Const NORMAL_PRIORITY_CLASS = &H20&
      Private Const STARTF_USESTDHANDLES = &H100&

Private Sub Command1_Click()
    RunTestCase92
End Sub

Private Sub Form_Load()
  TC12NextMode = "slow"
End Sub

Private Sub Form_Resize()
  
  'TestTabTabular.Width = Form1.Width - 32
  'TestTabTabular.Height = Form1.Height - 64
 
  'TestTab1.Width = TestTabTabular.Width - 320
  'TestTab1.Height = TestTabTabular.Height - 800
  
End Sub

Private Sub Frame1_DragDrop(Source As Control, x As Single, Y As Single)

End Sub

Private Sub TC10ConsLab_Click()

End Sub

Private Sub TC10Post_Click()
  TC10G2Gateway.G2Location = TC10ConString.Text
  TC10G2Gateway.Connect (True)
  TC10G2Gateway.PostMessage TC10Msg.Text
  TC10G2Gateway.Disconnect
End Sub

Private Sub TC11CALL_Click()
  TC11G2Gateway.G2Location = TC11ConStr.Text
  TC11G2Gateway.Connect (True)
 
  rannum = TC11G2Gateway.Call("G2RANDOMGENERATOR", Val(TC11Input.Text))
  TC11Res.Text = Str(rannum)
  TC7G2Gateway.Disconnect

End Sub

Private Sub TC11PostMsg_Click()
  TC11G2Gateway.G2Location = TC11ConStr.Text
  TC11G2Gateway.Connect (True)
  rannum = TC11G2Gateway.Call("POST-MESSAGE", TC11MsgText.Text)
  TC11G2Gateway.Disconnect

End Sub

Private Sub TC12Command_Click()
    rannu = TC12G2Gateway.Call("CHANGE-SIGNAL", TC12NextMode)
    If TC12NextMode = "stop" Then
        TC12NextMode = "slow"
    ElseIf TC12NextMode = "slow" Then
        TC12NextMode = "proceed"
    Else
        TC12NextMode = "stop"
    End If

End Sub

Private Sub TC12G2Gateway_RpcStarted(ByVal ProcedureName As String, InputArguments As Variant)
    
    
    
    TC12Mode = UCase(InputArguments)
    If ProcedureName = "CYCLELIGHTS" Then Call Update_Light(TC12Mode)
End Sub
Private Sub Update_Light(Mode As String)
If Mode = "PROCEED" Then
    TC12Red.FillColor = &H0
    TC12Yel.FillColor = &H0
    TC12Green.FillColor = &HFF00&
ElseIf Mode = "STOP" Then
   TC12Red.FillColor = &HFF
   TC12Yel.FillColor = &H0
   TC12Green.FillColor = &H0
Else
   TC12Red.FillColor = &H0
   TC12Yel.FillColor = &HFFFF&
   TC12Green.FillColor = &H0
End If
End Sub

Private Sub TC12Reconnect_Click()
  If TC12Reconnect.Tag = 1 Then
      TC12G2Gateway.Disconnect
      TC12G2Gateway.G2Location = TC12ConStr.Text
      TC12G2Gateway.Connect (True)
      TC12Reconnect.Caption = "Disconnect"
      TC12Reconnect.Tag = 2
  Else
      TC12G2Gateway.Disconnect
      TC12Reconnect.Caption = "Connect"
      TC12Reconnect.Tag = 1
  End If
End Sub

Private Sub TC21Start_Click()
  
End Sub

Private Sub TC22Start_Click()
  strVal = App.Path + "\TestCase22.htm"
  TC22WebBrowser.Navigate2 (strVal)
  
End Sub

Private Sub TC23Start_Click()
  strVal = App.Path + "\TestCase23.htm"
  TC23WebBrowser.Navigate2 (strVal)
End Sub

Private Sub TC24Start_Click()
 strApp = App.Path + "\App\g2cpp.exe"
 Rem + " > " + App.Path + "\" + strResult
 Rem i = Shell(strApp, vbHide)
 TC24Text.Text = ExecCmd(strApp)
 
 
End Sub

Private Sub TC25Start_Click()
  strApp = App.Path + "\App\g2mfc.exe"
  i = Shell(strApp, vbNormalFocus)
  
End Sub

Private Sub TC4Command_Click(Index As Integer)
  TC4Step3.FontBold = False
  TC4Step1.FontBold = True
  Dim myCTL As G2Gateway
  Set myCTL = New G2Gateway
  TC4Step1.FontBold = False
  TC4Step2.FontBold = True
  myCTL.start "G2PROC-ONE", TC4Param.Text
  TC4Step2.FontBold = False
  TC4Step3.FontBold = True
End Sub

Private Sub TC6Command_Click()
  TC6Step2.FontBold = False
  TC6Step1.FontBold = True
  TC6G2Gateway1.G2Location = "pc1:1122"
  TC6Step1.FontBold = False
  TC6Step2.FontBold = True

End Sub

Private Sub TC72Start_Click()
  TC72G2Gateway.G2Location = TC72ConStr.Text
  TC72G2Gateway.Connect (True)
  RunTestCase72
  TC72G2Gateway.Disconnect
End Sub

Private Sub TC73Start_Click()
  TC73G2Gateway.G2Location = TC73ConStr.Text
  TC73G2Gateway.Connect (True)
  RunTestCase73
  TC73G2Gateway.Disconnect
End Sub

Private Sub TC74Start_Click()

  End Sub

Private Sub TC7CallRPC_Click()
  TC7G2Gateway.G2Location = TC7Connection.Text
  TC7G2Gateway.Connect (True)
 
  rannum = TC7G2Gateway.Call("G2RANDOMGENERATOR", Val(TC7CallItem.Text))
  TC7CallItemRetVal.Text = Str(rannum)
  TC7G2Gateway.Disconnect

End Sub

Private Sub TC7StartRPC_Click()
  TC7G2Gateway.G2Location = TC7Connection.Text
  TC7G2Gateway.Connect (True)
  rannum = TC7G2Gateway.Call("POST-MESSAGE", TC7StartItem.Text)
  TC7G2Gateway.Disconnect
End Sub

Private Sub TC8Command_Click()
  TC8G2Gateway.G2Location = TC8Conn.Text
  TC8G2Gateway.Connect (True)
  rannum = TC8G2Gateway.Call("POST-MESSAGE", "Test Case 8: Test method 'Call' from G2 ActiveX")
  TC8G2Gateway.Disconnect
  
End Sub

Private Sub TC9Command_Click()
  TC9Form.Wait = TC9Wait.Value
  
  TC9Form.G2Location = TC9ConString.Text
  TC9Form.Show (False)
End Sub

 Private Function ExecCmd(ByVal cmdline As String) As String
          Dim proc As PROCESS_INFORMATION, ret As Long, bSuccess As Long
          Dim start As STARTUPINFO
          Dim sa As SECURITY_ATTRIBUTES, hReadPipe As Long, hWritePipe _
          As Long
          Dim bytesread As Long, mybuff As String
          Dim i As Integer
          Dim strResult As String
          
          mybuff = String(256, Chr$(65))

          sa.nLength = Len(sa)
          sa.bInheritHandle = 1&
          sa.lpSecurityDescriptor = 0&
          
          ret = CreatePipe(hReadPipe, hWritePipe, sa, 0)
          If ret = 0 Then
              MsgBox "CreatePipe failed. Error: " & Err.LastDllError
              Exit Function
          End If

       start.cb = Len(start)
       start.dwFlags = STARTF_USESTDHANDLES
       start.hStdOutput = hWritePipe
       start.hStdError = hWritePipe
       start.wShowWindow = vbHide
       res = SetHandleInformation(hReadPipe, HANDLE_FLAG_INHERIT, 0)
       ' Start the shelled application:
       ret& = CreateProcessA(0&, cmdline, sa, sa, 1&, _
       NORMAL_PRIORITY_CLASS, 0&, 0&, start, proc)
       If ret <> 1 Then
           MsgBox "CreateProcess failed. Error: " & Err.LastDllError
       End If
       bSuccess = WaitForSingleObject(proc.hProcess, 100000)
       res = CloseHandle(hWritePipe)
       bSuccess = 1
       strResult = ""
       Do While (bSuccess = 1)
       
       bSuccess = ReadFile(hReadPipe, mybuff, 100, bytesread, 0&)
       If bytesread <> 0 Then
          strResult = strResult + Left(mybuff, bytesread)
       End If
       Loop
       
        ret& = CloseHandle(proc.hProcess)
        ret& = CloseHandle(proc.hThread)
        ret& = CloseHandle(hReadPipe)
        ret& = CloseHandle(hWritePipe)
        
        ExecCmd = strResult
        
      End Function


Private Sub TCXConnect_Click()
 If TCXConnect.Tag = 1 Then
    TCXConnect.Tag = 0
    TCXG2Gateway.G2Location = TCXConStr.Text
    TCXG2Gateway.Connect (True)
    TCXConnect.Caption = "Disconect"
 Else
   TCXConnect.Tag = 1
   TCXConnect.Caption = "Connect"
   TCXG2Gateway.Disconnect
 End If
End Sub
Private Sub TCXG2Gateway_AttributeModified(localItem As GensymAxlCtl.G2Item, ByVal attributeName As String, ByVal newValue As Variant, ByVal subscriptionHndl As Long, ByVal userData As Variant)
  Log "AtributeChage event" + userData + vbCrLf
End Sub
Private Sub TCXG2Gateway_CustomEvent(localItem As GensymAxlCtl.G2Item, ByVal EventName As String, ByVal newValue As Variant, ByVal subscriptionHndl As Long, ByVal userData As Variant)
  Log "CustomEvent event" + userData + vbCrLf
End Sub
Private Sub TCXG2Gateway_IconColorChanged(localItem As GensymAxlCtl.G2Item, ByVal subscriptionHndl As Long, ByVal chgStruct As Object, ByVal userData As Variant)
  Log "IconColorChanged event:" + userData + vbCrLf
End Sub
Private Sub TCXG2Gateway_ItemAdded(localItem As GensymAxlCtl.G2Workspace, ByVal subscriptionHndl As Long, ByVal userData As Variant)
 Log "ItemAdded event: Passed " + userData + vbCrLf
End Sub
Private Sub TCXG2Gateway_ItemDeleted(localItem As GensymAxlCtl.G2Item, ByVal subscriptionHndl As Long, ByVal userData As Variant)
Log "Item Deleted event:" + userData + vbCrLf
End Sub
Private Sub TCXG2Gateway_ItemRemoved(localItem As GensymAxlCtl.G2Workspace, ByVal subscriptionHndl As Long, ByVal userData As Variant)
Log "ItemAdded event: Passed " + userData + vbCrLf
End Sub
Private Sub TCXG2Gateway_ItemSelected(localWindow As GensymAxlCtl.G2Window, ByVal subscriptionHandle As Long, ByVal userData As Variant)
 Log "ItemSelected event: Passed " + userData + vbCrLf
End Sub
Private Sub TCXG2Gateway_RpcCalled(ByVal ProcedureName As String, InputArguments As Variant, ReturnArguments As Variant)
Log "RpcCalled"
End Sub
Private Sub TCXG2Gateway_ValueChanged(localItem As GensymAxlCtl.G2Item, ByVal newValue As Variant, ByVal subscriptionHndl As Long, ByVal userData As Variant)
 Log "Value Changed" + userData
End Sub
Private Sub TCXStart_Click()
  
    TCXConnect_Click
    TCXConsole.Text = ""
      
    RunTestCase26
    RunTestCase27
    RunTestCase28
    RunTestCase29
    RunTestCase30
    RunTestCase31
    RunTestCase32
    RunTestCase33
    RunTestCase34
    RunTestCase35
    RunTestCase36
    RunTestCase37
    RunTestCase38
    RunTestCase39
    RunTestCase40
    RunTestCase41
    RunTestCase42
    RunTestCase43
    RunTestCase44
    RunTestCase45
    RunTestCase46
    RunTestCase47
    RunTestCase48
   'RunTestCase49 ' run with some error
    RunTestCase50
    RunTestCase51
    RunTestCase52
    RunTestCase53
    RunTestCase54
    RunTestCase55
    RunTestCase56
    RunTestCase57
    RunTestCase58
    RunTestCase59
   'RunTestCase60 ' run with some error
    RunTestCase61
    RunTestCase63
    RunTestCase64
    RunTestCase65
    RunTestCase66
    RunTestCase67
    RunTestCase68
    RunTestCase69
    RunTestCase70
    RunTestCase71
    RunTestCase72
    RunTestCase73
    RunTestCase74
    RunTestCase75
    RunTestCase76
    RunTestCase77
    RunTestCase78
    RunTestCase79
    RunTestCase80
    'RunTestCase81
    'RunTestCase82
    'RunTestCase83
    RunTestCase84
    RunTestCase85
    RunTestCase86
    RunTestCase87
    RunTestCase90
    RunTestCase91
    RunTestCase92
    RunTestCase93
    RunTestCase94
    RunTestCase95
    RunTestCase96
    RunTestCase97
    RunTestCase98
    RunTestCase99
    RunTestCase101
    RunTestCase102
    RunTestCase103
    RunTestCase104
    RunTestCase105
    RunTestCase106
    RunTestCase107
    RunTestCase108
    RunTestCase109
    RunTestCase110
    RunTestCase111
    RunTestCase112
End Sub
Private Sub RunTestCase26()
Dim s As G2Structure
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 26:  Mapping Data Types (Starting with G2 data types)" + vbCrLf)
Dim nameV
nameV = Array("G2-integer-min", "G2-integer-max", "G2-float-min", "G2-float-max")
Dim xVal
xVal = Array(-2 ^ 29, 2 ^ 29 - 1, -1.79 * 10 ^ 308, 4.94065645841247 ^ -324)
For i = 0 To 3 Step 1
Call TestCase26Helper(nameV(i), xVal(i), i + 1)
Next i
End Sub
Private Sub TestCase26Helper(valName, valExpRes, valIndex)
Dim s As G2Structure
On Error GoTo erro26handle:
Set s = TCXG2Gateway.Call("TESTCASE26", "RunTestCase26", valIndex)
valComSingel = s(valName)
valComExpect = valExpRes
Call ASSERT("26 " + valName + ":", Str(valComSingel), Str(valComExpect))
 
Exit Sub
erro26handle:
  Log "TestCase26 for type " + valName + " : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase27()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 27: Mapping Data Types (Starting with G2 data types)" + vbCrLf)
s = "TESTCASE27"
For i = 0 To 9 Step 1
code = TCXG2Gateway.Call("TESTCASE27", s, i)
Call ASSERT("27 " + "Character code for the letter " + Mid$(s, i + 1, 1) + ":", code, AscW(Mid$(s, i + 1, 1)))
Next i
End Sub
Private Sub RunTestCase28()
Dim s As G2Structure
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 28: Overriding the Mapping of Simple Data Types in G2" + vbCrLf)
Dim nameV
nameV = Array("com-single", "com-double", "com-byte", "com-integer", "com-long")
Dim xVal
xVal = Array(56, 56.249, 56, 56, 56)

For i = 0 To 4 Step 1
Call TestCase28Helper(nameV(i), xVal(i), i + 1)
Next i
End Sub
Private Sub TestCase28Helper(valName, valExpRes, valIndex)
Dim s As G2Structure
On Error GoTo erro28handle:
Set s = TCXG2Gateway.Call("TESTCASE28", "RunTestCase28", valIndex)
valComSingel = s(valName)
valComExpect = valExpRes
Call ASSERT("28 " + valName + ":", Str(valComSingel), Str(valComExpect))
 
Exit Sub
erro28handle:
  Log "TestCase28 for type " + valName + " : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase29()
 
Dim DRet As Date
Dim DExp As Date
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 29: Mapping Date and Time in G2" + vbCrLf)
 
DExp = TimeValue("10/1/2008 11:34:32 PM") + DateValue("10/1/2008 11:34:32 PM")
 
DRet = TCXG2Gateway.Call("TESTCASE29PASS", "RunTestCase29", DExp)
Call ASSERT("29 Week of day", Weekday(DRet), Weekday(DExp))
Call ASSERT("29", Str(DRet), Str(DExp))
 
End Sub


Private Sub RunTestCase30()
Dim s As G2Structure
Dim DRet As Currency
Dim DExp As Currency
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 30: Mapping Currency in G2" + vbCrLf)
Set s = TCXG2Gateway.Call("TESTCASE30", "Run Test Case 30")
DRet = s("Currency")
DExp = "$10.51"
Call ASSERT("30", Str(DRet), Str(DExp))
End Sub
Private Sub RunTestCase31()
 
Dim DRet() As Variant
Dim DExp As Currency
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 31:  Mapping Multi Dimensional Arrays to a Structure in G2" + vbCrLf)
Dim x1
x1 = Array("some", "test", "tost")
x = Array(x1, x1)
Dim matrix(9, 9) As Double
maxDim0 = 9
maxDim1 = 9
For i = 0 To maxDim0
    For j = 0 To maxDim1
        matrix(i, j) = (i * 10) + j
    Next j
Next i
 
Y = TCXG2Gateway.Call("TESTCASE31PASS", "Run Test Case 31", matrix)
strExp = "some"
Call ASSERT("31", Y(0, 0), matrix(0, 0))
End Sub
Private Sub RunTestCase32()
Dim DRet() As Variant
Dim DExp As Currency
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 32:  Example for One-Dimensional Array in G2" + vbCrLf)
Dim Arr(1 To 3) As Variant
s = TCXG2Gateway.Call("TESTCASE32", "Run Test Case 32")
strExp = "some"
Call ASSERT("32", s(1), strExp)
End Sub
Private Sub RunTestCase33()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 33:  Example for Two-Dimensional Array in G2" + vbCrLf)
strExp = "some"
s = TCXG2Gateway.Call("TESTCASE33", "Run Test Case 33")
Call ASSERT("33", s(0, 0), strExp)
End Sub
Private Sub RunTestCase34()
Dim DRet() As Variant
Dim DExp As Currency
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 34:  Example for Multidimensional Array in G2" + vbCrLf)
Dim Arr(1 To 4, 1 To 3) As Integer
s = TCXG2Gateway.Call("TESTCASE34", "Run Test Case 34")
strExp = 8
Call ASSERT("34", Str(s(4, 2)), Str(strExp))
End Sub

Private Sub RunTestCase35()
Dim symX As New G2Symbol
symX = "Example"
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 35:  Send a G2Symbol as a parameter from G2 to VB in uppercase" + vbCrLf)
strExp = "EXAMPLE"
symX.UpperCase = True
strVal = TCXG2Gateway.Call("TESTCASE35AND36EATAVAR", "Run Test Case 35", symX)
Call ASSERT("35", strVal, strExp)
End Sub
Private Sub RunTestCase36()
Dim symX As New G2Symbol
symX = "Example"
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 36:  Send a G2Symbol as a parameter from G2 to VB in lowercase" + vbCrLf)
strExp = "Example"
symX.UpperCase = False
strVal = TCXG2Gateway.Call("TESTCASE35AND36EATAVAR", "Run Test Case 36", symX)
Call ASSERT("36", strVal, strExp)
End Sub
Private Sub RunTestCase37()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Set g2Struct = New G2Structure

g2Struct.Add "Line", "Conn-Rod"
g2Struct.Add "Machine", 5
g2Struct.Add "Speed", 240.6

Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 37:  Creating a Variable to Represent a G2Structure and send G2stucture to G2" + vbCrLf)
Set g2StructRet = TCXG2Gateway.Call("TESTCASE37", "Run Test Case 37", g2Struct)
Call ASSERTG2StructureToString("37", g2StructRet, g2Struct)

End Sub
Private Sub RunTestCase38()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Set g2Struct = TCXG2Gateway.MakeG2ComVariable(g2StructureType, "Line", "Conn-Rod", "Machine", 5, "Speed", 240.6)
      
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 38:   Creating a Variable to Represent a G2Structure by “MakeG2ComVariable”, send details Names and values as a parameter list and send G2Structure to G2" + vbCrLf)
Set g2StructRet = TCXG2Gateway.Call("TESTCASE38", "Run Test Case 38", g2Struct)
Call ASSERTG2StructureToString("38", g2StructRet, g2Struct)

End Sub
Private Sub RunTestCase39()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Dim x
x = Array("Line", "Conn-Rod", "Machine", 5, "Speed", 240.6)
Set g2Struct = TCXG2Gateway.MakeG2ComVariable(g2StructureType, x)

Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 39:  Creating a Variable to Represent a G2Structure by “MakeG2ComVariable”, send details  Names and values from a single array and send G2Structure to G2" + vbCrLf)
Set g2StructRet = TCXG2Gateway.Call("TESTCASE39", "Run Test Case 39", g2Struct)
Call ASSERTG2StructureToString("39", g2StructRet, g2Struct)

End Sub
Private Sub RunTestCase40()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Dim x
x = Array("Line", "Conn-Rod", "Machine")
Set g2Struct = TCXG2Gateway.MakeG2ComVariable(g2StructureType, x, 5, "Speed", 240.6)
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 40:  Creating a Variable to Represent a G2Structure by “MakeG2ComVariable”, send details  Names from an array, values from a parameter list and send G2Structure to G2" + vbCrLf)
Set g2StructRet = TCXG2Gateway.Call("TESTCASE40", "Run Test Case 40", g2Struct)
Call ASSERTG2StructureToString("40", g2StructRet, g2Struct)
End Sub
Private Sub RunTestCase41()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Dim x
x = Array("Line", "Conn-Rod", "Machine")
Dim Y
Y = Array("Conn-Rod", 5, 240.6)

Set g2Struct = TCXG2Gateway.MakeG2ComVariable(g2StructureType, x, Y)

Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 41:  Creating a Variable to Represent a G2Structure by “MakeG2ComVariable”, send details  Names from an array, values from a second array and send G2Structure to G2" + vbCrLf)
Set g2StructRet = TCXG2Gateway.Call("TESTCASE41", "Run Test Case 41", g2Struct)
Call ASSERTG2StructureToString("41", g2StructRet, g2Struct)
End Sub
Private Sub RunTestCase42()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Set g2Struct = TCXG2Gateway.MakeG2ComVariable(g2StructureType, "Line", "Conn-Rod", "Machine", 5, "Speed", 240.6)
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 42:   Reading the Value of a G2Structure Property" + vbCrLf)
Set g2StructRet = TCXG2Gateway.Call("TESTCASE42", "Run Test Case 42", g2Struct)
Call ASSERTG2StructureToString("42", g2StructRet, g2Struct)
Call ASSERT("42", Str(g2Struct("Speed")), Str(240.6))
End Sub
Private Sub RunTestCase43()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Set g2Struct = TCXG2Gateway.MakeG2ComVariable(g2StructureType, "Line", "Conn-Rod", "Machine", 5, "Speed", 240.6)
Dim x
x = Array("Conn-Rod", 5, 240.6)
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 43:    Reading the Value of all parameters G2Structure Property" + vbCrLf)
Set g2StructRet = TCXG2Gateway.Call("TESTCASE43", "Run Test Case 43", g2Struct)
'Call ASSERTG2StructureToString("43", g2StructRet, g2Struct)
Dim NameVal
Dim var As Variant
Log ("Value in structure" + vbCrLf)
i = 0
For Each NameVal In g2Struct
      Call ASSERT("43", NameVal.Value, x(i))
      'Log (NameVal.Value)
      'Log (vbCrLf)
      i = i + 1
      Next

End Sub
Private Sub RunTestCase44()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Set g2Struct = New G2Structure

Dim x
x = Array("Conn-Rod", 5, 240.6)

g2Struct.Add "Line", "Conn-Rod"
g2Struct.Add "Machine", 5
g2Struct.Add "Speed", 240.6

Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 44:   Reading the Value of parameters of G2Structure Property with numeric index" + vbCrLf)
Set g2StructRet = TCXG2Gateway.Call("TESTCASE44", "Run Test Case 44", g2Struct)
'Call ASSERTG2StructureToString("44", g2StructRet, g2Struct)
For i = 0 To g2Struct.Count - 1
      Call ASSERT("44", g2Struct(i), x(i))
      'Log (g2Struct(i))
      'Log (vbCrLf)
      Next i
End Sub
Private Sub RunTestCase45()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Set g2Struct = New G2Structure
Dim x
x = Array("Line", "Machine", "Speed")
Dim Y
Y = Array("Conn-Rod", 5, 240.6)

Set g2Struct = TCXG2Gateway.MakeG2ComVariable(g2StructureType, x, Y)

Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 45:   Setting the Value of a  G2Structure Property" + vbCrLf)
Log ("Before chagne" + vbCrLf)
Call ASSERT("45", Str(g2Struct("Speed")), Str(240.6))
g2Struct("Speed") = 305.1
Log ("After chagne" + vbCrLf)
Call ASSERT("45", Str(g2Struct("Speed")), Str(305.1))
End Sub
Private Sub RunTestCase46()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Set g2Struct = New G2Structure
Dim x
x = Array("Line", "Machine", "Speed")
Dim Y
Y = Array("Conn-Rod", 5, 240.6)
Set g2Struct = TCXG2Gateway.MakeG2ComVariable(g2StructureType, x, Y)
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 46:    Determining the Number of Name/Value Pairs in G2Structure" + vbCrLf)
Call ASSERT("46", Str(g2Struct.Count), Str(3))
End Sub

Private Sub RunTestCase47()
Dim g2Struct  As G2Structure
Dim g2StructRet  As G2Structure
Set g2Struct = New G2Structure
Dim x
x = Array("Line", "Machine", "Speed")
Set g2Struct = TCXG2Gateway.MakeG2ComVariable(g2StructureType, "Line", "Conn- Rod", "Machine", 5, "Speed", 240.6)
i = 0
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 47:   Obtaining Lists of Property Names for G2Structure" + vbCrLf)
For Each NameVal In g2Struct
       Call ASSERT("47", UCase(NameVal.Name), UCase(x(i)))
       i = i + 1
       Next
End Sub
Private Sub RunTestCase48()
Dim i As Integer
Dim arX As Variant
Dim g2Struct As New G2Structure

Dim x
x = Array("Line", "Machine", "Speed")
g2Struct.Add "Line", "Conn-Rod"
g2Struct.Add "Machine", 5
g2Struct.Add "Speed", 240.6

i = 0
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 48:   Obtaining Lists of Property Names for G2Structure with the numeric Index" + vbCrLf)
arX = g2Struct.Names
For i = 0 To g2Struct.Count - 1
   Call ASSERT("48", UCase(arX(i)), UCase(x(i)))
Next i
End Sub
Private Sub RunTestCase49()
Dim i As Integer
Dim arX As Variant
Dim g2Struct As New G2Structure

Dim x
x = Array("Line", "Machine", "Speed")
Dim Y
Y = Array("Line", "Speed")

g2Struct.Add "Line", "Conn-Rod"

g2Struct.Add "Machine", 5
g2Struct.Add "Speed", 240.6

i = 0
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 49:   Removing a Name/Value Pair from a G2Structure" + vbCrLf)
Log ("Before remove 'Machine'" + vbCrLf)
arX = g2Struct.Names
For i = 0 To g2Struct.Count - 1
   Call ASSERT("49", UCase(arX(i)), UCase(x(i)))
Next i
Log ("After remove 'Machine'" + vbCrLf)
On Error GoTo ErrorHandler
g2Struct.Remove (UCase("Machine"))
arX = g2Struct.Names
For i = 0 To g2Struct.Count - 1
   Call ASSERT("49", UCase(arX(i)), UCase(Y(i)))
Next i
Exit Sub

ErrorHandler:
Log "Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase50()
Dim i As Integer
Dim arX As Variant
Dim item As New G2Item
item.ClassName = UCase("example-class")
i = item.Count
Call item.Add("TxtAt", "Created with ActiveXLink")
Call item.Add("IntAt", 22)
i = item.Count
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 50:   Create instance of an existing G2 class (G2Item)" + vbCrLf)
Call ASSERT("50", Str(i), Str(2))
valIt = TCXG2Gateway.Call("IFITEMEXIST", "Test Case 50", item)
If valIt = True Then
Call Log("Test Case 50 |OK|: The class " + item.ClassName + " present in G2" + vbCrLf)
Else
Call Log("Test Case 50 |ERROR|: The class " + item.ClassName + " does not present in G2" + vbCrLf)
End If
End Sub
Private Sub RunTestCase51()
Dim i As Integer
Dim arX As Variant
Dim item As New G2Item
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 51:   Send a G2Item without setting ClassName property" + vbCrLf)
valIt = TCXG2Gateway.Call("IFITEMEXIST", "Test Case 51", item)
If valIt = True Then
Call Log("Test Case 51 |ERROR|: The G2 does not reported about error when class item does not set correct class name " + vbCrLf)
Else
Call Log("Test Case 51 |OK|: The G2 reported about error because class item does not set correct class name " + vbCrLf)
End If
End Sub
Private Sub RunTestCase52()
Dim i As Integer
Dim arX As Variant
Dim item As New G2Item
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 52:   Send a G2Item with the ClassName property set to an unknown class" + vbCrLf)
item.ClassName = UCase("example-class123")
valIt = TCXG2Gateway.Call("IFITEMEXIST", "Test Case 51", item)
If valIt = True Then
Call Log("Test Case 52 |ERROR|: The class " + item.ClassName + " present in G2" + vbCrLf)
Else
Call Log("Test Case 52 |OK|: The class " + item.ClassName + " does not present in G2" + vbCrLf)
End If
End Sub
Private Sub RunTestCase53()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 53:   Create a G2Item and adding attributes" + vbCrLf)
Log ("The result of this test case see in TWNG in RESULT-WS workspace. It should create appropriate item" + vbCrLf)
Dim newEC As New G2Item
Dim symX As New G2Symbol
newEC.ClassName = "EXAMPLE-CLASS"
newEC.Name = "EXAMPLE-CLASS-TEST53"
newEC.Add "DeptNo", 58
newEC.Add "Manager", "Oiltree"
symX = "miserable"
newEC.Add "Rating", symX
newEC.Add "Performance", 0.3

TCXG2Gateway.start "USEANITEM", newEC, 100
End Sub
Private Sub RunTestCase54()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 54:   Define a G2Item with attributes that do not exist in G2" + vbCrLf)
Log ("The result of this test case see in TWNG in RESULT-WS workspace. It should create appropriate item" + vbCrLf)
Dim newEC As New G2Item
Dim symX As New G2Symbol
newEC.ClassName = "EXAMPLE-CLASS"
newEC.Name = "EXAMPLE-CLASS-TEST54"
newEC.Add "DeptNo", 58
newEC.Add "Manager", "Oiltree"
newEC.Add "Manager_NotE", "Oiltree"
symX = "miserable"
newEC.Add "Rating", symX
newEC.Add "Performance", 0.3
TCXG2Gateway.start "USEANITEM", newEC, 150
End Sub
Private Sub RunTestCase55()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 55:   Send an attribute value to G2 that does not match the type defined in the class definition" + vbCrLf)
Log ("The result of this test case see in TWNG in RESULT-WS workspace. It should create appropriate item" + vbCrLf)
Dim newEC As New G2Item
Dim symX As New G2Symbol
newEC.ClassName = "EXAMPLE-CLASS"
newEC.Name = "EXAMPLE-CLASS-TEST55"
newEC.Add "DeptNo", "Oiltree"
newEC.Add "Manager", 54
newEC.Add "Manager_NotE", "Oiltree"
symX = "miserable"
newEC.Add "Rating", symX
newEC.Add "Performance", 0.3
TCXG2Gateway.start "USEANITEM", newEC, 200
End Sub
Private Sub RunTestCase56()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 56:   Reading the Attribute Values of G2Item via G2 procedure" + vbCrLf)
Dim g2iX As G2Item
Dim iX As Integer

Dim xEpectedValue
Dim xSym As New G2Symbol
xSym = "superior"
xEpectedValue = Array(57, "Santos", xSym, 9.7)


Set g2iX = TCXG2Gateway.Call("TESTCASE56")

For iX = 0 To g2iX.Count - 1
Call ASSERT("56", g2iX(iX), xEpectedValue(iX))
Next iX
End Sub
Private Sub RunTestCase57()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 57:  Example of getting value of attributes of Item by index (index can be either a number (0-based) or an attribute name)" + vbCrLf)
Dim g2iX As G2Item
Dim iX As Integer
Dim xEpectedValue
Dim xSym As New G2Symbol
xSym = "superior"
xEpectedValue = Array(57, "Santos", xSym, 9.7)

Dim xField
xField = Array("deptno", "Manager", "RaTiNg", "PERFORMANCE")

Set g2iX = TCXG2Gateway.Call("TESTCASE57")

Log ("By Index" + vbCrLf)
For iX = 0 To g2iX.Count - 1
Call ASSERT("57", g2iX(iX), xEpectedValue(iX))
Next iX
Log ("By Field Name" + vbCrLf)
For iX = 0 To g2iX.Count - 1
Call ASSERT("57", g2iX(xField(iX)), xEpectedValue(iX))
Next iX
End Sub
Private Sub RunTestCase58()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 58:   Example of Getting Attribute Names, Values, and Types" + vbCrLf)
Dim g2iX As G2Item
Dim iX As Integer

Dim xEpectedValue
Dim xSym As New G2Symbol
xSym = "superior"
xEpectedValue = Array(57, "Santos", xSym, 9.7)
Dim xField
xField = Array("deptno", "Manager", "RaTiNg", "PERFORMANCE")
Dim xType
xType = Array(1, 4, 3, 6)
Dim vn, vv, vt

Set g2iX = TCXG2Gateway.Call("TESTCASE58")
If Not g2iX Is Nothing Then
 vn = g2iX.AttrNames
 vv = g2iX.AttrValues
 vt = g2iX.AttrTypes

For iX = 0 To g2iX.Count - 1
Call ASSERT("58 by Name  ", UCase(vn(iX)), UCase(xField(iX)))
Call ASSERT("58 by Value ", vv(iX), xEpectedValue(iX))
Call ASSERT("58 by Type  ", vt(iX), xType(iX))
Next iX
Else
    Log ("Test Case 58 |ERROR| : G2 Item is empty")
End If

End Sub

Private Sub Log(strVal)
If IsNumeric(strVal) = True Then
        TCXConsole.Text = TCXConsole.Text + Str(strVal)
      Else
        TCXConsole.Text = TCXConsole.Text + strVal
      End If
  'TCXG2Gateway.PostMessage (strVal)
End Sub
Private Sub RunTestCase59()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 59:  Create Symbolic attributes" + vbCrLf)
Log ("The result of this test case see in TWNG in RESULT-WS workspace. It should create appropriate item" + vbCrLf)
Dim newEC As New G2Item
Dim symX As New G2Symbol
newEC.ClassName = "EXAMPLE-CLASS"
newEC.Name = "EXAMPLE-CLASS-TEST59"
newEC.Add "DeptNo", 58
newEC.Add "Manager", "Oiltree"
'symX = "miserable"
'newEC.Add "Rating", symX
newEC.Add "Rating", "MISERABLE"
Call newEC.Symbolize("Rating", True)
newEC.Add "Performance", 0.3
newEC.Add "Data", 1.3
TCXG2Gateway.start "USEANITEM", newEC, 250
End Sub


Private Sub RunTestCase60()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 60:   Removing attributes" + vbCrLf)
Dim newEC As New G2Item
Dim symX As New G2Symbol
newEC.ClassName = "Example-Class"
newEC.Add "DeptNo", 58
newEC.Add "Manager", "Oiltree"
symX = "miserable"
newEC.Add "Rating", symX
newEC.Add "Performance", 0.3
newEC.Add "Data", 1.3
newEC.Remove (1)
Set g2iX = TCXG2Gateway.Call("TESTCASE58")
g2iX.Remove (1)
End Sub
Private Sub RunTestCase61()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 61:   Example of Iterating Over the Attributes of a G2Item" + vbCrLf)
Dim g2iX As G2Item
Dim x
Dim xSym As New G2Symbol
Dim xSym1 As New G2Symbol
xSym = "superior"
Set g2iX = TCXG2Gateway.Call("TESTCASE61")
Dim xEpectedValue
xEpectedValue = Array(57, "Santos", xSym, 9.7)
Dim xField
xField = Array("deptno", "Manager", "RaTiNg", "PERFORMANCE")
Dim xType
xType = Array(1, 4, 3, 6)
Dim xEpectedValueNew
xSym1 = "average"
xEpectedValueNew = Array(59, "Martin", xSym1, 5.8)
iX = 0
For Each x In g2iX
Call ASSERT("61 by Name  ", UCase(x.Name), UCase(xField(iX)))
Call ASSERT("61 by Value ", x.Value, xEpectedValue(iX))
Call ASSERT("61 by Type  ", x.Type, xType(iX))

  If x.Type = 1 Then
      x.Value = 59
 ElseIf x.Type = 4 Then
     x.Value = "Martin"
 ElseIf x.Type = 3 Then
    x.Value = xSym1
 Else
     x.Value = 5.8
End If
    iX = iX + 1
Next
iX = 0
For Each x In g2iX
    Call ASSERT("61 by Name  ", UCase(x.Name), UCase(xField(iX)))
    Call ASSERT("61 by Value ", x.Value, xEpectedValueNew(iX))
    Call ASSERT("61 by Type  ", x.Type, xType(iX))
    iX = iX + 1
Next
End Sub
Private Sub RunTestCase63()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 63: Determining the Number of Elements in G2ListOrArray" + vbCrLf)
Dim item As G2Item
Dim list As G2ListOrArray

Set item = TCXG2Gateway.Call("TESTCASE63")
Set list = item.Value
iExpect = 5
Call ASSERT("63", list.Count, iExpect)
End Sub
Private Sub RunTestCase64()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 64: Getting Element Values for G2ListOrArray" + vbCrLf)
Dim item As G2Item
Dim iar As G2ListOrArray
Dim i As Integer
Dim Hold As Integer
Dim x
x = Array(7, 5, 3, 1, -1)
Dim Y
Y = Array(-1, 7, 5, 3, 1)

Set item = TCXG2Gateway.Call("TESTCASE64")
Set iar = item.Value
Log ("Before list change" + vbCrLf)
For i = 0 To iar.Count - 1 Step 1
    Call ASSERT("64", iar(i), x(i))
Next i

If iar.Count > 0 Then Hold = iar(iar.Count - 1)
For i = iar.Count - 2 To 0 Step -1
iar(i + 1) = iar(i)
Next i
If iar.Count > 0 Then iar(0) = Hold
Log ("After list change" + vbCrLf)
For i = 0 To iar.Count - 1 Step 1
    Call ASSERT("64", iar(i), Y(i))
Next i
End Sub
Private Sub RunTestCase65()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 65: Determining the Type of G2ListOrArray" + vbCrLf)
Dim item As G2Item
Dim iar As G2ListOrArray
Dim iar1 As G2ListOrArray

Set item = TCXG2Gateway.Call("TESTCASE65", 1)
Set iar = item.Value
Call ASSERT("65", iar.Type, g2ItemOrValueList)

Set item = TCXG2Gateway.Call("TESTCASE65", 0)
Set iar1 = item.Value
Call ASSERT("65", iar1.Type, g2ItemOrValueArray)
End Sub
Private Sub RunTestCase66()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 66:  Set the List or array" + vbCrLf)
Dim item As New G2Item
Dim iar As New G2ListOrArray
Dim x
x = Array(7, 5, 3, 1, -1)
iar.Type = g2ItemOrValueList
For i = 0 To 4 Step 1
iar.Add (x(i))
Next i
item.Value = iar
For i = 0 To 4 Step 1
Call ASSERT("66", iar(i), x(i))
Next i
 
TCXG2Gateway.start "TESTCASE66", item
End Sub
Private Sub RunTestCase67()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 67:  Inserting element to the List or Array" + vbCrLf)
Dim item As New G2Item
Dim iar As New G2ListOrArray
Dim x
x = Array(7, 5, 3, 1, -1)
Dim Y
Y = Array(-1, 1, 3, 5, 7)
iar.Type = g2ItemOrValueList
iar.Add (x(0))
For i = 1 To 4 Step 1
 Call iar.Insert(0, x(i))
Next i
For i = 0 To 4 Step 1
Call ASSERT("67", iar(i), Y(i))
Next i
End Sub
Private Sub RunTestCase68()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 68:    Appending element to the List or Array" + vbCrLf)
Dim item As New G2Item
Dim iar As New G2ListOrArray
Dim x
x = Array(7, 5, 3, 1, -1)
Dim Y
Y = Array(7, -1, 1, 3, 5)
iar.Type = g2ItemOrValueList
iar.Add (x(0))
For i = 1 To 4 Step 1
 Call iar.Append(0, x(i))
Next i
For i = 0 To 4 Step 1
Call ASSERT("68", iar(i), Y(i))
Next i
End Sub
Private Sub RunTestCase69()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 69: Adding element to the List or Array" + vbCrLf)
Dim item As New G2Item
Dim iar As New G2ListOrArray
Dim x
x = Array(7, 5, 3, 1, -1)
iar.Type = g2ItemOrValueList
For i = 0 To 4 Step 1
 iar.Add (x(i))
Next i
For i = 0 To 4 Step 1
Call ASSERT("69", iar(i), x(i))
Next i
End Sub
Private Sub RunTestCase70()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 70: Removing element from the List or Array" + vbCrLf)
Dim item As New G2Item
Dim iar As New G2ListOrArray
Dim x
x = Array(7, 5, 3, 1, -1)
Dim Y
Y = Array(7, 3, 1)
iar.Type = g2ItemOrValueList
For i = 0 To 4 Step 1
 iar.Add (x(i))
Next i
iar.Remove (1)
iar.Remove (3)
For i = 0 To 2 Step 1
Call ASSERT("70", iar(i), Y(i))
Next i
End Sub
Private Sub RunTestCase71()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 71: Iterating Over Elements of a List or Array" + vbCrLf)
Dim item As New G2Item
Dim iar As New G2ListOrArray
Dim x
x = Array(7, 5, 3, 1, -1)
iar.Type = g2ItemOrValueList
For i = 0 To 4 Step 1
 iar.Add (x(i))
Next i
Log ("Before change" + vbCrLf)
For i = 0 To 4 Step 1
Call ASSERT("71", iar(i), x(i))
Next i
Dim x1 As Variant

For Each x1 In iar
x1 = 4
Next
Log ("variable x change" + vbCrLf)
For i = 0 To 4 Step 1
Call ASSERT("71", iar(i), x(i))
Next i
Log ("list change" + vbCrLf)
Dim x2 As Variant
For Each x2 In iar
x2.Value = 4
Next
For i = 0 To 4 Step 1
Call ASSERT("71", iar(i), 4)
Next i
End Sub

Private Sub RunTestCase72()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 72:    Sending Lists and Arrays to G2" + vbCrLf)
Log ("The result of this test case see in TWNG in RESULT-WS workspace. It should create appropriate item" + vbCrLf)
Dim g2ValList As New G2ListOrArray
g2ValList.Type = g2ValueList
g2ValList.Add 2
g2ValList.Add "Oi"
g2ValList.Add 29.8
TCXG2Gateway.start "TESTCASE72", g2ValList
End Sub
Private Sub RunTestCase73()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 73: Send a subclass of a G2 list or array to G2" + vbCrLf)
Log ("The result of this test case see in TWNG in RESULT-WS workspace. It should create appropriate item" + vbCrLf)

Dim itemX As New G2Item
Dim arrayX As New G2ListOrArray
arrayX.Type = g2SymbolArray
arrayX.Add "unacceptable"
arrayX.Add "poor"
arrayX.Add "fair"
arrayX.Add "good"
arrayX.Add "excellent"
itemX.ClassName = "symarsub"
itemX.Name = "Grades"
itemX.Value = arrayX
itemX.Add "Language", "English"
itemX.Add "Group", 1
TCXG2Gateway.start "TESTCASE73", itemX
End Sub
Private Sub RunTestCase74()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 74: Access the properties and methods of G2Item by casting G2Workspace on G2Item" + vbCrLf)
On Error GoTo ErrorRunTestCase74
Dim g2Wkspc As New G2Workspace
Dim g2Itm As G2Item
Set g2Itm = g2Wkspc
g2Itm.Name = "Made-by-AxL"
g2Itm.Create (TCXG2Gateway)
Exit Sub
ErrorRunTestCase74:
Log "TestCase74  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase75()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 75:    Event Notification for ItemAdded" + vbCrLf)
On Error GoTo ErrorRunTestCase75
Dim Gw2Res As G2Workspace
Dim Gw2Itm As G2Item
Set Gw2Res = TCXG2Gateway.Call("RETURN-WS-TE")
hndl = Gw2Res.SubscribeToItemAddition("TESTCASE75")
Log "Subscribe to 'ItemAddition' event correct" + vbCrLf
Log "For completed test case you should manual create in TESTEVENT workspace some object and application should write appropriate message in log" + vbCrLf
 
Exit Sub
ErrorRunTestCase75:
Log "TestCase75  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase76()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 76:    Event Notification for ItemRemoved" + vbCrLf)
On Error GoTo ErrorRunTestCase76
Dim Gw2Res As G2Workspace
Dim Gw2Itm As G2Item
Set Gw2Res = TCXG2Gateway.Call("RETURN-WS-TE")
hndl = Gw2Res.SubscribeToItemRemoval("TESTCASE76")
Log "Subscribe to 'ItemRemoval ' event correct"
Exit Sub
ErrorRunTestCase76:
Log "TestCase76  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase77()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 77: Subscribing to Workspace Additions" + vbCrLf)
Dim Gw2Res As G2Workspace
Set Gw2Res = TCXG2Gateway.Call("RETURN-WS")
Dim subVal As Variant
On Error GoTo ErrorRunTestCase77
subVal = Gw2Res.SubscribeToItemAddition("RETURN-WS")
Log ("TestCase77 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase77:
Log "TestCase77  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase78()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 78: Subscribing to Workspace Removals" + vbCrLf)
Dim Gw2Res As G2Workspace
Set Gw2Res = TCXG2Gateway.Call("RETURN-WS")
Dim subVal As Variant
On Error GoTo ErrorRunTestCase78
subVal = Gw2Res.SubscribeToItemRemoval("RETURN-WS")
Log ("TestCase78 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase78:
Log "TestCase78  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase79()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 79: Unsubscribing from Workspace Additions" + vbCrLf)
Dim Gw2Res As G2Workspace
Set Gw2Res = TCXG2Gateway.Call("RETURN-WS")
Dim subVal As Variant
On Error GoTo ErrorRunTestCase79
subVal = Gw2Res.SubscribeToItemAddition("RETURN-WS")
Gw2Res.UnsubscribeFromItemAddition
Log ("TestCase79 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase79:
Log "TestCase79  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase80()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 80: Unsubscribing from Workspace Removals" + vbCrLf)
Dim Gw2Res As G2Workspace
Set Gw2Res = TCXG2Gateway.Call("RETURN-WS")
Dim subVal As Variant
On Error GoTo ErrorRunTestCase80
subVal = Gw2Res.SubscribeToItemRemoval("RETURN-WS")
Gw2Res.UnsubscribeFromItemRemoval
Log ("TestCase80 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase80:
Log "TestCase80  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase81()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 81: Access the properties and methods of G2Item by casting G2Window on G2Item" + vbCrLf)
Dim g2Win As G2Window
Dim g2Itm As G2Item
On Error GoTo ErrorRunTestCase81
Set g2Win = TCXG2Gateway.Call("TESTCASE81")
Set g2Itm = g2Win
g2Itm.Name = "Made-by-AxL"
g2Itm.Update
Log ("TestCase81 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase81:
Log "TestCase81  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase82()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 82: Access the properties and methods of G2Item by casting G2Window on G2Item" + vbCrLf)
Dim g2Win As G2Window
Dim g2Itm As G2Item
On Error GoTo ErrorRunTestCase82
Set g2Win = TCXG2Gateway.Call("TESTCASE81")
Set g2Itm = g2Win
g2Itm.Name = "Made-by-AxL"
g2Itm.Update
Log ("TestCase82 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase82:
Log "TestCase82  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase83()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 83: Change the user mode of the g2-window" + vbCrLf)
Dim g2Win As G2Window
Dim g2Itm As G2Item
On Error GoTo ErrorRunTestCase83
Set g2Win = TCXG2Gateway.Call("TESTCASE81")
g2Win.g2UserMode = "developer"
Set g2Itm = g2Win
g2Itm.Update
Log ("TestCase83 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase83:
Log "TestCase83  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase84()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 84: Subscribing to Window Events in G2Window" + vbCrLf)
Dim g2Win As G2Window
Dim g2Itm As G2Item
On Error GoTo ErrorRunTestCase84
Set g2Win = TCXG2Gateway.Call("TESTCASE81")
g2Win.SubscribeToSelection ("TestCase84")
Log ("TestCase84 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase84:
Log "TestCase84 : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase85()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 85: Getting the G2 User Mode of a Window" + vbCrLf)
Log ("You should change user mode in TWNG manual than appropriate message should occur in log." + vbCrLf)
Dim g2Win As G2Window
Dim g2Itm As G2Item
On Error GoTo ErrorRunTestCase85
Set g2Win = TCXG2Gateway.Call("TESTCASE81")
g2Win.SubscribeToSelection ("test")
Exit Sub
ErrorRunTestCase85:
Log "TestCase85  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase86()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 86: Subscribing to Selection Events in G2Window" + vbCrLf)
Dim g2Win As G2Window
Dim g2Itm As G2Item
On Error GoTo ErrorRunTestCase86
Set g2Win = TCXG2Gateway.Call("TESTCASE81")
valHandle = g2Win.SubscribeToSelection("test")
If valHandle <> 0 Then
    Log ("TestCase86 : Work correct" + vbCrLf)
Else
    Log ("TestCase86 : Work incorrect, becase handle is incorrect" + vbCrLf)
End If
Exit Sub
ErrorRunTestCase86:
Log "TestCase86  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase87()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 87: Unsubscribing to Selection Events in G2Window" + vbCrLf)
Dim g2Win As G2Window
Dim g2Itm As G2Item
On Error GoTo ErrorRunTestCase87
Set g2Win = TCXG2Gateway.Call("TESTCASE81")
valHandle = g2Win.SubscribeToSelection("Test")
g2Win.UnsubscribeFromSelection
Log ("TestCase87 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase87:
Log "TestCase87  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase90()
Dim item As G2Item
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 90:  COM program call a procedure" + vbCrLf)
Set item = TCXTestCase90.CallG2Method
Call ASSERT("90", item.ClassName, "EXAMPLE-CLASS")
Log ("Linked status" + vbCrLf)
Call ASSERT("90", item.Linked, True)
item.Unlink
Call ASSERT("90", item.Linked, False)
Exit Sub
End Sub
Private Sub RunTestCase91()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 91:  Creating and Linking a G2Item" + vbCrLf)
Dim itemX As New G2Item
On Error GoTo ErrorRunTestCase91

itemX.ClassName = "UDC"
itemX.Name = "VBC91"
itemX.Add "TxtAt", "Created with ActiveXLink"
itemX.Add "IntAt", 22

itemX.Create TC91G2Gateway

Log ("TestCase91 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase91:
Log ("TestCase91 : The some error occur" + vbCrLf)
End Sub
Private Sub RunTestCase92()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 92:  Getting the Icon for a G2Item" + vbCrLf)
Dim px As Picture
Dim itemX As New G2Item
On Error GoTo ErrorRunTestCase92
itemX.ClassName = "UDC"
itemX.Name = "VBC92"
itemX.Add "TxtAt", "Created with ActiveXLink"
itemX.Add "IntAt", 22
itemX.Create TC91G2Gateway

Set px = itemX.Icon(Picture1.BackColor)
Set Image1.Picture = px
Set Picture1.Picture = px
itemX.Delete
Log ("TestCase92 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase92:
Log ("TestCase92 : The some error occur" + vbCrLf)
End Sub
Private Sub RunTestCase93()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 93:   Deleting a G2Item" + vbCrLf)
Dim itemX As New G2Item
On Error GoTo ErrorRunTestCase93

itemX.ClassName = "UDC"
itemX.Name = "VBC93"
itemX.Add "TxtAt", "Created with ActiveXLink"
itemX.Add "IntAt", 22

itemX.Create TC91G2Gateway
itemX.Delete
Log ("TestCase93 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase93:
Log ("TestCase93 : The some error occur" + vbCrLf)
End Sub
Private Sub RunTestCase94()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 94: Updating the Item in G2" + vbCrLf)
Dim itemX As New G2Item
Dim itemXUpdated As G2Item

itemX.ClassName = "UDC"
itemX.Name = "VBC94"
itemX.Add "TxtAt", "Created with ActiveXLink"
itemX.Add "IntAt", 22
itemX.Create TC91G2Gateway

itemX("TxtAt") = "Update Example"
itemX("IntAt") = 33
itemX.Value = 15
itemX.Update

Set itemXUpdated = TC91G2Gateway.Call("TESTCASE94RETURN")

Call ASSERT("94", itemXUpdated("TxtAt"), "Update Example")
Call ASSERT("94", itemXUpdated("IntAt"), 33)
Call ASSERT("94", itemXUpdated.Value, 15)
End Sub
Private Sub RunTestCase95()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 95: Refreshing a G2Item" + vbCrLf)
Dim itemX As New G2Item
On Error GoTo ErrorRunTestCase95
itemX.ClassName = "UDC"
itemX.Name = "VBC95"
itemX.Add "TxtAt", "Created with ActiveXLink"
itemX.Add "IntAt", 22
itemX.Value = 101
itemX.Create TC91G2Gateway

Log ("Before change" + vbCrLf)
Call ASSERT("95", itemX.Value, 101)
TC91G2Gateway.Call "TESTCASE95"
itemX.Refresh
Log ("After change" + vbCrLf)
Call ASSERT("95", itemX.Value, 112)
itemX.Delete
Exit Sub
ErrorRunTestCase95:
Log ("TestCase95 : The some error occur" + vbCrLf)
End Sub
Private Sub RunTestCase96()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 96: Verifying Linked Items" + vbCrLf)
Dim itemX As New G2Item
On Error GoTo ErrorRunTestCase96
itemX.ClassName = "UDC"
itemX.Name = "VBC96"
itemX.Add "TxtAt", "Created with ActiveXLink"
itemX.Add "IntAt", 22
itemX.Create TC91G2Gateway

Log ("Linked status" + vbCrLf)
Call ASSERT("96", itemX.Linked, True)
itemX.Unlink
Call ASSERT("96", itemX.Linked, False)
Exit Sub
ErrorRunTestCase96:
Log ("TestCase96 : The some error occur" + vbCrLf)
End Sub
Private Sub RunTestCase97()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 97: Unlinking a G2Item" + vbCrLf)
Dim itemX As New G2Item
On Error GoTo ErrorRunTestCase97
itemX.ClassName = "UDC"
itemX.Name = "VBC97"
itemX.Add "TxtAt", "Created with ActiveXLink"
itemX.Add "IntAt", 22
itemX.Create TC91G2Gateway

Log ("Before change" + vbCrLf)
Call ASSERT("97", itemX.Linked, True)
itemX.Unlink
Log ("After change" + vbCrLf)
Call ASSERT("97", itemX.Linked, False)
itemX.Name = "VBC972"
itemX.Create TC91G2Gateway
Log ("Linked status" + vbCrLf)
Call ASSERT("97", itemX.Linked, True)
itemX.Delete
Exit Sub
ErrorRunTestCase97:
Log ("TestCase97 : The some error occur" + vbCrLf)
End Sub
Private Sub RunTestCase98()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 98:  Getting G2Item Attribute Names, Values, and Types" + vbCrLf)
Dim g2iX As G2Item
Dim iX As Integer

Dim xEpectedValue
Dim xSym As New G2Symbol
xSym = "superior"
xEpectedValue = Array(57, "Santos", xSym, 9.7)
Dim xField
xField = Array("deptno", "Manager", "RaTiNg", "PERFORMANCE")
Dim xType
xType = Array(1, 4, 3, 6)
Dim vn, vv, vt

Set g2iX = TCXG2Gateway.Call("TESTCASE58")
If Not g2iX Is Nothing Then
 vn = g2iX.AttrNames
 vv = g2iX.AttrValues
 vt = g2iX.AttrTypes

For iX = 0 To g2iX.Count - 1
Call ASSERT("98 by Name  ", UCase(vn(iX)), UCase(xField(iX)))
Call ASSERT("98 by Value ", vv(iX), xEpectedValue(iX))
Call ASSERT("98 by Type  ", vt(iX), xType(iX))
Call ASSERT("98 by Type  ", g2iX.AttrType(iX), xType(iX))
Next iX
Else
    Log ("Test Case 98 |ERROR| : G2 Item is empty")
End If

End Sub
Private Sub TCXG2Gateway_RpcStarted(ByVal ProcedureName As String, InputArguments As Variant)
 If ProcedureName = "ConsumeWindow" Then
    Set winX99 = InputArguments(1)
    Set gitX99 = InputArguments(2)
    End If
End Sub
Private Sub RunTestCase99()
Log ("------------------------------------------------" + vbCrLf)
Log ("Test Case 99:  Using Linked Items as Parameters to RPC’s" + vbCrLf)
On Error GoTo ErrorRunTestCase99

Dim itemX As New G2Item
itemX.ClassName = "UDC"
itemX.Name = "VBC99"
itemX.Add "TxtAt", "Created with ActiveXLink"
itemX.Add "IntAt", 22
itemX.Create TCXG2Gateway

TCXG2Gateway.Call ("send-window")
Dim winAsGit As G2Item
Set winAsGit = winX99
TCXG2Gateway.start "Xlator", winAsGit.Reference, gitX99.Reference

itemX.Delete
Log ("TestCase99 : Work correct" + vbCrLf)
Exit Sub
ErrorRunTestCase99:
Log ("TestCase99 : The some error occur" + vbCrLf)
End Sub
Private Sub RunTestCase101()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 101: Subscribing to Attribute Changes" + vbCrLf)
  On Error GoTo ErrorRunTestCase101
  Set item = TCXG2Gateway.Call("TESTCASEFORSUB")
  valHandle = item.SubscribeToAttributeModification("All", "RunTestCase101")
  If valHandle <> 0 Then
     Log ("TestCase101 : Work correct" + vbCrLf)
  Else
     Log ("TestCase101 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase101:
  Log "TestCase101  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase102()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 102: Subscribing to Item Deletions" + vbCrLf)
  On Error GoTo ErrorRunTestCase102
  Set item = TCXG2Gateway.Call("TESTCASEFORSUB")
  valHandle = item.SubscribeToDeletion("RunTestCase102")
  If valHandle <> 0 Then
     Log ("TestCase102 : Work correct" + vbCrLf)
  Else
     Log ("TestCase102 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase102:
  Log "TestCase102  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase103()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 103:  Subscribing to Icon Color Changes" + vbCrLf)
  On Error GoTo ErrorRunTestCase103
  Set item = TCXG2Gateway.Call("TESTCASEFORSUB")
  valHandle = item.SubscribeToIconColorChange("RunTestCase103")
  If valHandle <> 0 Then
     Log ("TestCase103 : Work correct" + vbCrLf)
  Else
     Log ("TestCase103 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase103:
  Log "TestCase103  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase104()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 104:  Subscribing to Variable and Parameter Value Changes" + vbCrLf)
  On Error GoTo ErrorRunTestCase104
  Set item = TCXG2Gateway.Call("TESTCASE104")
  valHandle = item.SubscribeToValueChange("RunTestCase104")
  If valHandle <> 0 Then
     Log ("TestCase104 : Work correct" + vbCrLf)
  Else
     Log ("TestCase104 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase104:
  Log "TestCase104  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase105()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 105:  Subscribing to Custom Events" + vbCrLf)
  On Error GoTo ErrorRunTestCase105
  Set item = TCXG2Gateway.Call("TESTCASEFORSUB")
  valHandle = item.SubscribeToCustomEvent("TestCase105", "RunTestCase105")
  If valHandle <> 0 Then
     Log ("TestCase105 : Work correct" + vbCrLf)
  Else
     Log ("TestCase105 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase105:
  Log "TestCase104  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase106()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 106:  Unsubscribing from Attribute Changes" + vbCrLf)
  On Error GoTo ErrorRunTestCase106
  Set item = TCXG2Gateway.Call("TESTCASEFORSUB")
  valHandle = item.SubscribeToAttributeModification("All", "RunTestCase106")
  Call item.UnsubscribeFromAttributeModification(valHandle)
  If valHandle <> 0 Then
     Log ("TestCase106 : Work correct" + vbCrLf)
  Else
     Log ("TestCase106 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase106:
  Log "TestCase106  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase107()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 107:  Unsubscribing from Item Deletions" + vbCrLf)
  On Error GoTo ErrorRunTestCase107
  Set item = TCXG2Gateway.Call("TESTCASEFORSUB")
  valHandle = item.SubscribeToDeletion("RunTestCase107")
  Call item.UnsubscribeFromDeletion
  If valHandle <> 0 Then
     Log ("TestCase107 : Work correct" + vbCrLf)
  Else
     Log ("TestCase107 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase107:
  Log "TestCase107  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase108()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 108:  Unsubscribing from Icon Color Changes" + vbCrLf)
  On Error GoTo ErrorRunTestCase108
  Set item = TCXG2Gateway.Call("TESTCASEFORSUB")
  valHandle = item.SubscribeToIconColorChange("RunTestCase103")
  Call item.UnsubscribeFromIconColorChange
  If valHandle <> 0 Then
     Log ("TestCase108 : Work correct" + vbCrLf)
  Else
     Log ("TestCase108 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase108:
  Log "TestCase108  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase109()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 109:  Unsubscribing from Custom Events" + vbCrLf)
  On Error GoTo ErrorRunTestCase109
  Set item = TCXG2Gateway.Call("TESTCASEFORSUB")
  valHandle = item.SubscribeToCustomEvent("TestCase109", "RunTestCase105")
  Call item.UnsubscribeFromCustomEvent("TestCase109")
  If valHandle <> 0 Then
     Log ("TestCase109 : Work correct" + vbCrLf)
  Else
     Log ("TestCase109 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase109:
  Log "TestCase109  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub

Private Sub RunTestCase110()
  Dim item As G2Item
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 110:  Unsubscribing from Variable and Parameter Value Changes" + vbCrLf)
  On Error GoTo ErrorRunTestCase110
  Set item = TCXG2Gateway.Call("TESTCASE104")
  valHandle = item.SubscribeToValueChange("RunTestCase110")
  Call item.UnsubscribeFromValueChange
  If valHandle <> 0 Then
     Log ("TestCase110 : Work correct" + vbCrLf)
  Else
     Log ("TestCase110 : Work incorrect, becase handle is incorrect" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase110:
  Log "TestCase110  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase111()
  Dim item As G2Item
  Dim vX As Variant
  Log ("------------------------------------------------" + vbCrLf)
  Log ("Test Case 111:  Unsubscribing from All Event Notification" + vbCrLf)
  On Error GoTo ErrorRunTestCase111
  Set item = TCXG2Gateway.Call("TESTCASEFORSUB")
  Call item.UnsubscribeFromAll
  vX = item.Subscriptions()
  flag = True
  For i = LBound(vX) To UBound(vX)
    flag = False
  Next i
  If flag = True Then
  Log ("TestCase111 : Work correct" + vbCrLf)
  Else
  Log ("TestCase111 : Work incorrect because item has some subscription" + vbCrLf)
  End If
  Exit Sub
ErrorRunTestCase111:
  Log "TestCase111  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub RunTestCase112()
    Dim g2it As G2Item
    Dim i As Integer, n As Integer
    Dim vX As Variant
    Dim Y(0 To 1) As Integer
    Dim x
    x = Array(1, 2)
    Log ("------------------------------------------------" + vbCrLf)
    Log ("Test Case 112:  Getting Information about Subscriptions" + vbCrLf)
    On Error GoTo ErrorRunTestCase112
    Set g2it = TCXG2Gateway.Call("TESTCASEFORSUB")
    valHandle = g2it.SubscribeToAttributeModification("All", "Test")
    valHandle = g2it.SubscribeToDeletion("Test")
    If g2it Is Nothing Then
        Log "TestCase112: ERROR: Item has not been read or created" + vbCrLf
        Else
        vX = g2it.Subscriptions()
        For i = LBound(vX) To UBound(vX)
        Y(i) = vX(i, 1)
        Next i
    End If
    flag = True
    For i = 0 To 1 Step 1
      If x(i) <> Y(i) Then flag = False
    Next i
    If flag = True Then
       Log "TestCase 112: Work correct and all subscriptions present in list" + vbCrLf
    Else
      Log "TestCase 112: Work incorrect because all subscriptions does not present in list" + vbCrLf
    End If
    g2it.UnsubscribeFromAll
  Exit Sub
ErrorRunTestCase112:
  Log "TestCase112  : Error Number: " & Err.Number & " With The Description ->> " & Err.Description & " <<- Occured." + vbCrLf
End Sub
Private Sub ASSERTG2StructureToString(strCase, strVal As G2Structure, strExp As G2Structure)
 flag = True
 If strVal.Count = strExp.Count Then
    For i = 0 To strExp.Count - 1 Step 1
       If strVal(i) <> strExp(i) Then
           flag = False
       End If
    Next
 Else
    flag = False
 End If
    
If flag = True Then
    Log ("Test Case " + strCase + " |OK| : Expected value and return value is equal " + vbCrLf)
Else
    Log ("Test Case " + strCase + " |OK| : Expected value and return value is not equal " + vbCrLf)
End If

End Sub

Private Sub ASSERT(strCase, strVal, strExp)
If strVal = strExp Then
    Log ("Test Case " + strCase + " |OK| : Expected value is = '")
    Log (strExp)
    Log ("' and return value is = '")
    Log (strVal)
    Log ("'" + vbCrLf)
Else
    Log ("Test Case " + strCase + " |ERROR| : Expected value is = '")
    Log (strExp)
    Log ("' and return value is = '")
    Log (strVal)
    Log ("'" + vbCrLf)
End If

End Sub



