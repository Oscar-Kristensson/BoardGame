# === Configuration ===
$ShortcutName = "BoardGame"                      # Name of the shortcut
$TargetPath = "launcher.vbs"                    # Full path to the executable
#$IconLocation = "C:\Path\To\MyApp.ico"          # (Optional) Path to .ico file
$Arguments = ""                                  # (Optional) Command-line arguments
# $WorkingDirectory = "C:\Path\To"                # (Optional) Start-in directory

# === Create Shortcut ===
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition


$StartMenuPath = "$env:APPDATA\Microsoft\Windows\Start Menu\Programs\$ShortcutName.lnk"
$Shell = New-Object -ComObject WScript.Shell
$Shortcut = $Shell.CreateShortcut($StartMenuPath)

$Shortcut.TargetPath = Join-Path $ScriptDir $TargetPath
$Shortcut.Arguments = $Arguments
$Shortcut.WorkingDirectory = $ScriptDir
#$Shortcut.IconLocation = $IconLocation
$Shortcut.Save()

Write-Host "Shortcut created at: $StartMenuPath"
