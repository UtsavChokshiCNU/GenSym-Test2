Attribute VB_Name = "PIServersList"
Option Explicit

Declare Function GetEnvironmentVariable Lib "kernel32" Alias "GetEnvironmentVariableA" (ByVal lpName As String, ByVal lpBuffer As String, ByVal nSize As Long) As Long

' This is where we store the information about
' the servers we already know about
' --------------------------------------------
Public Type ServerInfo
    ServerName As String
    userName   As String
    password   As String
End Type
Public nNrServers As Integer
Public Server() As ServerInfo

' How to match the information in the Server table
' with the information on screen
' ------------------------------------------------
Public nTop      As Integer
Public nCursor   As Integer
Public nLastLine As Integer

' Information about destination file
' ----------------------------------
Public fNamed       As Boolean
Public strDestFile  As String
Public fModified    As Boolean

' Section used to communicate with entry form
' -------------------------------------------
Public Const EF_EDIT = 0
Public Const EF_ADD = 1
Public efMode   As Integer
Public efTitle  As String
Public efDone   As Boolean
Public efOK     As Boolean
Public efMod    As Boolean
Public efModPW  As Boolean
Public efServer As ServerInfo
