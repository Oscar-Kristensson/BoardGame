' This script launches a hidden terminal where the BoardGame.exe
' can run without showing the terminal on windows. Thanks Windows :)
Set WshShell = CreateObject("WScript.Shell")
WshShell.Run "BoardGame.exe", 0, False