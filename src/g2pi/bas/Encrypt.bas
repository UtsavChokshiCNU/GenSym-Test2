Attribute VB_Name = "Encrypt"

Private Declare Function CryptAcquireContext Lib "advapi32.dll" Alias "CryptAcquireContextA" ( _
   phProv As Long, ByVal pszContainer As Long, ByVal pszProvider As String, _
   ByVal dwProvType As Long, ByVal dwFlags As Long) As Long

Private Declare Function CryptCreateHash Lib "advapi32.dll" (ByVal hProv As Long, _
   ByVal Algid As Long, ByVal hKey As Long, ByVal dwFlags As Long, phHash As Long) As Long

Private Declare Function CryptHashData Lib "advapi32.dll" (ByVal hHash As Long, _
   ByVal pbData As String, ByVal dwDataLen As Long, ByVal dwFlags As Long) As Long

Private Declare Function CryptDeriveKey Lib "advapi32.dll" ( _
   ByVal hProv As Long, ByVal Algid As Long, ByVal hBaseData As Long, ByVal dwFlags As Long, _
   phKey As Long) As Long

Private Declare Function CryptDestroyHash Lib "advapi32.dll" (ByVal hHash As Long) As Long

Private Declare Function CryptDestroyKey Lib "advapi32.dll" (ByVal hKey As Long) As Long

Private Declare Function CryptEncrypt Lib "advapi32.dll" (ByVal hKey As Long, _
   ByVal hHash As Long, ByVal Final As Long, ByVal dwFlags As Long, ByVal pbData As String, _
   pdwDataLen As Long, ByVal dwBufLen As Long) As Long

Private Declare Function CryptDecrypt Lib "advapi32.dll" (ByVal hKey As Long, _
   ByVal hHash As Long, ByVal Final As Long, ByVal dwFlags As Long, ByVal pbData As String, _
   pdwDataLen As Long) As Long

Private Declare Function CryptReleaseContext Lib "advapi32.dll" (ByVal hProv As Long, _
   ByVal dwFlags As Long) As Long

' ================================================================================
'Constants
' ================================================================================
Private Const CRYPT_NEWKEYSET = &H8
Private Const CRYPT_MACHINE_KEYSET = &H20
Private Const CRYPT_VERIFYCONTEXT = &HF0000000
Private Const MS_DEF_PROV = "Microsoft Base Cryptographic Provider v1.0" & vbNullChar
Private Const PROV_RSA_FULL = 1
Private Const ALG_CLASS_DATA_ENCRYPT = 24576
Private Const ALG_CLASS_HASH = 32768
Private Const ALG_TYPE_ANY = 0
Private Const ALG_TYPE_BLOCK = 1536
Private Const ALG_TYPE_STREAM = 2048
Private Const ALG_SID_RC2 = 2
Private Const ALG_SID_RC4 = 1
Private Const ALG_SID_MD5 = 3
Private Const CALG_MD5 = ((ALG_CLASS_HASH Or ALG_TYPE_ANY) Or ALG_SID_MD5)
Private Const CALG_RC2 = ((ALG_CLASS_DATA_ENCRYPT Or ALG_TYPE_BLOCK) Or ALG_SID_RC2)
Private Const CALG_RC4 = ((ALG_CLASS_DATA_ENCRYPT Or ALG_TYPE_STREAM) Or ALG_SID_RC4)
Private Const ENCRYPT_ALGORITHM = CALG_RC4
Private Const ENCRYPT_BLOCK_SIZE = 1
Private Const CRYPT_EXPORTABLE = 1

Private Const ERR_CRYPTOINVALIDINPUTBUFFER = 100
Private Const ERR_CRYPTOINITILIZEFAILED = 101

'------------------------------------------------------------------------------
'
'   Procedure Name  :   Encrypt
'   Description     :   Encrypt a string
'
'   Parameters
'   ----------
'   InputBuffer         String to encrypt
'   Password            Key to use
'   OutputBuffer        Encrypted string
'
'------------------------------------------------------------------------------
Public Function Encrypter(ByVal InputBuffer As String, ByVal password As String, _
                        ByRef OutputBuffer As String) As Boolean

Dim lngHCryptprov As Long
Dim lngHHash As Long
Dim lngHkey As Long
Dim lngCryptLength As Long
Dim lngCryptBufLen As Long
Dim strCryptBuffer As String
Dim strError As String
Dim lngResult As Long

    On Error GoTo Encrypt_Terminate
 
    Encrypter = False
    OutputBuffer = ""
    
    If Trim(InputBuffer = "") Then
       Err.Raise ERR_CRYPTOINVALIDINPUTBUFFER, "modCrypto.Encrypt PROC", "InputBuffer can not be empty."
    End If

    'Create the crypto handle
    If Not Initialize(lngHCryptprov, lngHHash, lngHkey, password) Then
        Err.Raise ERR_CRYPTOINITILIZEFAILED, "modCrypto.Encrypt PROC", "Failed to initialize crypto environment."
    End If
  
    'Create a buffer for the CryptEncrypt function
    lngCryptLength = Len(InputBuffer)
    lngCryptBufLen = lngCryptLength * 2
    strCryptBuffer = String(lngCryptBufLen, vbNullChar)
    LSet strCryptBuffer = InputBuffer
  
    'Encrypt the text data
    If Not CBool(CryptEncrypt(lngHkey, 0, 1, 0, strCryptBuffer, lngCryptLength, lngCryptBufLen)) Then
        strError = "Error occurred during CryptEncrypt." & vbCrLf
        strError = strError & "Bytes required:" & CStr(lngCryptLength) & vbCrLf
        Err.Raise Err.LastDllError, "modCrypto.Encrypt PROC", strError
    End If
  
    OutputBuffer = Mid$(strCryptBuffer, 1, lngCryptLength)
    Encrypter = True
  
Encrypt_Terminate:

    'Destroy session key.
    If (lngHkey) Then
        lngResult = CryptDestroyKey(lngHkey)
    End If
  
    'Destroy hash object
    If lngHHash Then
        CryptDestroyHash (lngHHash)
    End If
  
    'Release Context provider handle
    If lngHCryptprov Then
        lngResult = CryptReleaseContext(lngHCryptprov, 0)
    End If
 
    ' raise error
    If Err.Number <> 0 Then
        Err.Raise Err.Number, Err.Source, Err.Description
    End If

End Function
'------------------------------------------------------------------------------
'
'   Procedure Name  :   Decrypt
'   Description     :   Decrypt a string
'
'   Parameters
'   ----------
'   InputBuffer         String to decrypt
'   Password            Key to use
'   OutputBuffer        decrypted string
'
'------------------------------------------------------------------------------
Public Function Decrypt(ByVal InputBuffer As String, _
 ByVal password As String, ByRef OutputBuffer As String) As Boolean
  
On Error GoTo Decrypt_Terminate
  
    Dim lngHCryptprov As Long
    Dim lngHHash As Long
    Dim lngHkey As Long
    Dim lngCryptLength As Long
    Dim lngCryptBufLen As Long
    Dim strCryptBuffer As String
    Dim strError As String
    Dim lngResult As Long
     
    Decrypt = False
    OutputBuffer = ""
     
    If Trim(InputBuffer = "") Then
        Err.Raise ERR_CRYPTOINVALIDINPUTBUFFER, "modCrypto.Decrypt PROC", "InputBuffer can not be empty."
    End If
         
     'Create the crypto handle
    If Not Initialize(lngHCryptprov, lngHHash, lngHkey, password) Then
        Err.Raise ERR_CRYPTOINITILIZEFAILED, "modCrypto.Decrypt PROC", "Failed to initialize crypto environment."
    End If
        
    'Prepare strCryptBuffer for CryptDecrypt
    lngCryptBufLen = Len(InputBuffer) * 2
    strCryptBuffer = String(lngCryptBufLen, vbNullChar)
    LSet strCryptBuffer = InputBuffer
     
    'Decrypt data
    If Not CBool(CryptDecrypt(lngHkey, 0, 1, 0, strCryptBuffer, lngCryptBufLen)) Then
        strError = "Error occurred during CryptEncrypt." & vbCrLf
        strError = strError & "Bytes required:" & CStr(lngCryptLength) & vbCrLf
        Err.Raise Err.LastDllError, "modCrypto.Decrypt PROC", strError
    End If
     
    'Setup output buffer with just decrypted data
    OutputBuffer = Mid$(strCryptBuffer, 1, lngCryptBufLen / 2)
    Decrypt = True
     
Decrypt_Terminate:
     
    'Destroy session key.
    If (lngHkey) Then
        lngResult = CryptDestroyKey(lngHkey)
    End If
     
    'Destroy hash object
    If lngHHash Then
        CryptDestroyHash (lngHHash)
    End If
     
    'Release Context provider handle
    If lngHCryptprov Then
        lngResult = CryptReleaseContext(lngHCryptprov, 0)
    End If
     
    ' raise error
    If Err.Number <> 0 Then
        Err.Raise Err.Number, Err.Source, Err.Description
    End If

End Function
' ======================
'  Initialize CryptoAPI
' ======================
Private Function Initialize(ByRef lngHCryptprov As Long, ByRef lngHHash As Long, _
           ByRef lngHkey As Long, ByVal strPassword As String) As Boolean
  
Dim lngResult As Long
  
    On Error GoTo Initialize_terminate
    
    Initialize = False
 
    ' If there is no default key container then create one using Flags field
    ' ----------------------------------------------------------------------
    If Not CBool(CryptAcquireContext(lngHCryptprov, 0&, MS_DEF_PROV, PROV_RSA_FULL, 0)) Then
        If Not CBool(CryptAcquireContext(lngHCryptprov, 0&, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET)) Then
            Err.Raise Err.LastDllError, "Initialize", "Error occurred during CryptAcquireContext."
        End If
    End If
  
    ' Create a hash object
    ' --------------------
    If Not CBool(CryptCreateHash(lngHCryptprov, CALG_MD5, 0, 0, lngHHash)) Then
        Err.Raise Err.LastDllError, "Initialize", "Error occurred during CryptCreateHash."
    End If
  
    ' Hash in the password text
    ' -------------------------
    If Not CBool(CryptHashData(lngHHash, strPassword, Len(strPassword), 0)) Then
        Err.Raise Err.LastDllError, "Initialize", "Error occurred during CryptHashData."
    End If
      
    ' Create a session key from the hash object
    ' -----------------------------------------
    If Not CBool(CryptDeriveKey(lngHCryptprov, ENCRYPT_ALGORITHM, lngHHash, 0, lngHkey)) Then
        Err.Raise Err.LastDllError, "Initialize", "Error occurred during CryptDeriveKey."
    End If
  
    Initialize = True

Initialize_terminate:

    ' raise error
    ' -----------
    If Err.Number <> 0 Then
        Err.Raise Err.Number, Err.Source, Err.Description
    End If

End Function

