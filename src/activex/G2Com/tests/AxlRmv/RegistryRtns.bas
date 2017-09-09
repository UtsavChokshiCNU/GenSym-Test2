Attribute VB_Name = "RegistryRtns"
    Option Explicit
    
    Global Const ERROR_SUCCESS = 0
    Global Const HKEY_CLASSES_ROOT = &H80000000
    Global Const KEY_ALL_ACCESS = &H3F
    
    Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long
    Declare Function RegDeleteKey& Lib "advapi32.dll" Alias "RegDeleteKeyA" (ByVal hKey As Long, ByVal lpSubKey As String)
    Declare Function RegEnumKey Lib "advapi32.dll" Alias "RegEnumKeyA" (ByVal hKey As Long, ByVal dwIndex As Long, ByVal lpName As String, ByVal cbName As Long) As Long
    Declare Function RegOpenKeyEx Lib "advapi32.dll" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, phkResult As Long) As Long
    Declare Function RegQueryValue Lib "advapi32.dll" (ByVal hKey As Long, ByVal txtSubkey As String, txtSubkeyVal As String, length As Long) As Long
' Delete the specified key and all its subkeys
' ============================================
Function DeleteKey(hive As Long, key_name As String) As Long
    Dim pos             As Integer
    Dim parent_key_name As String
    Dim parent_hKey     As Long
    Dim lRetVal         As Long

    If Mid(key_name, Len(key_name)) = "\" Then key_name = Mid(key_name, 1, Len(key_name) - 1)

    ' Delete the key's subkeys.
    ' -------------------------
    lRetVal = DeleteSubkeys(hive, key_name)
    If lRetVal <> ERROR_SUCCESS Then GoTo JumpOut

    ' Get the parent's name.
    ' ----------------------
    pos = InStrRev(key_name, "\")
    If pos = 0 Then
    
        ' This is a top-level key.  Delete it from the section.
        ' -----------------------------------------------------
        lRetVal = RegDeleteKey(hive, key_name)
        If lRetVal <> ERROR_SUCCESS Then GoTo JumpOut
    Else
    
        ' This is not a top-level key.  Find the parent key.
        ' --------------------------------------------------
        parent_key_name = Mid$(key_name, 1, pos - 1)
        key_name = Mid$(key_name, pos + 1)

        ' Open the parent key.
        ' --------------------
        lRetVal = RegOpenKeyEx(hive, parent_key_name, 0&, KEY_ALL_ACCESS, parent_hKey)
        If lRetVal <> ERROR_SUCCESS Then GoTo JumpOut
            
        ' Delete the key from its parent.
        ' -------------------------------
        lRetVal = RegDeleteKey(parent_hKey, key_name)
        If lRetVal <> ERROR_SUCCESS Then GoTo JumpOut

        ' Close the parent key.
        ' ---------------------
        RegCloseKey parent_hKey
    End If
    lRetVal = ERROR_SUCCESS
JumpOut:
    DeleteKey = lRetVal
    Exit Function
End Function
' =======================================
' Delete all the specified key's subkeys.
' =======================================
Function DeleteSubkeys(section As Long, key_name As String) As Long
    Dim hKey        As Long
    Dim subkeys     As Collection
    Dim subkey_num  As Long
    Dim length      As Long
    Dim subkey_name As String
    Dim lRetVal     As Long

    ' Open the key.
    ' ------------=
    lRetVal = RegOpenKeyEx(section, key_name, 0&, KEY_ALL_ACCESS, hKey)
    If lRetVal <> ERROR_SUCCESS Then GoTo JumpOut

    ' Enumerate the subkeys.
    ' ----------------------
    Set subkeys = New Collection
    subkey_num = 0
    Do
        ' Enumerate subkeys until we get an error.
        ' ----------------------------------------
        length = 256
        subkey_name = Space$(length)
        lRetVal = RegEnumKey(hKey, subkey_num, subkey_name, length)
        If lRetVal <> ERROR_SUCCESS Then Exit Do
        subkey_num = subkey_num + 1

        subkey_name = Mid(subkey_name, 1, InStr(subkey_name, Chr$(0)) - 1)
        subkeys.Add subkey_name
    Loop
    
    ' Recursively delete the subkeys and their subkeys.
    ' -------------------------------------------------
    For subkey_num = 1 To subkeys.Count
    
        ' Delete the subkey's subkeys.
        ' ----------------------------
        lRetVal = DeleteSubkeys(section, key_name & "\" & subkeys(subkey_num))
        If lRetVal <> ERROR_SUCCESS Then GoTo JumpOut

        ' Delete the subkey.
        ' ------------------
        lRetVal = RegDeleteKey(hKey, subkeys(subkey_num))
        If lRetVal <> ERROR_SUCCESS Then GoTo JumpOut
        
    Next subkey_num

    ' Close the key.
    ' --------------
    RegCloseKey hKey
    lRetVal = ERROR_SUCCESS
JumpOut:
    DeleteSubkeys = lRetVal
    Exit Function
End Function

