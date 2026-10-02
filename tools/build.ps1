[CmdletBinding()]
param(
    [ValidateSet('Debug', 'Release', 'DebugWindow')]
    [string]$Configuration = 'Debug',
    [switch]$Rebuild
)

$ErrorActionPreference = 'Stop'
$vswherePath = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio/Installer/vswhere.exe'
if (!(Test-Path -LiteralPath $vswherePath)) {
    throw 'Visual Studio Installer was not found. Install Visual Studio or Build Tools with Desktop development with C++, MSVC v143, and a Windows SDK.'
}

$installationPath = & $vswherePath -latest -products '*' -requires Microsoft.Component.MSBuild Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if ($LASTEXITCODE -ne 0 -or !$installationPath) {
    throw 'No Visual Studio installation with MSBuild and C++ tools was found.'
}
$msbuildPath = Join-Path $installationPath 'MSBuild/Current/Bin/MSBuild.exe'
$projectDirectory = [System.IO.Path]::GetFullPath((Join-Path $PSScriptRoot '../webview2'))
$projectPath = Join-Path $projectDirectory 'webview2.vcxproj'
$buildTarget = if ($Rebuild) { 'Rebuild' } else { 'Build' }
$buildArguments = @(
    $projectPath,
    '/nologo',
    '/m',
    '/v:minimal',
    "/t:$buildTarget",
    "/p:Configuration=$Configuration",
    '/p:Platform=x64',
    "/p:SolutionDir=$projectDirectory/"
)

& $msbuildPath @buildArguments
exit $LASTEXITCODE
