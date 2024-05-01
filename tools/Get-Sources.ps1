# Add this function using dot-source: . .\Get-Sources.ps1
# Call it from anywhere: Get-Sources
# Call it specifying the Path: Get-Sources ..\src\logger\

function Get-Sources {
  param(
    [Parameter(Position=0)]
    [string]$Path = "."
  )

  Get-ChildItem -Path $Path\* -Include *.h, *.cpp | Select-Object Name
}