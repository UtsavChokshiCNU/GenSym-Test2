    ' Model for decoding - remove later
    ' ---------------------------------
    nd0 = Asc(Left(PWOut, 1))
    nd2 = Asc(Mid(PWOut, 2, 1))
    nd1 = Asc(Right(PWOut, 1))
    
    magicNr = nd2 - IIf(nd2 >= Asc("A"), Asc("A"), 33)
    magicNr = 23 * magicNr + nd1 - IIf(nd1 >= Asc("A"), Asc("A") - 10, 33)
    magicNr = 23 * magicNr + nd0 - IIf(nd0 >= Asc("A"), Asc("A") - 10, 33)
    
    iRandLen = magicNr Mod 18
    iPWLen = (magicNr - iRandLen) / 18
    
    fSuccess = Decrypt(Mid(PWOut, iRandLen + 3, iPWLen), "832769041-viervoor", decPW)
