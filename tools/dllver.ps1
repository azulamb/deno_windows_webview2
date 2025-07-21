$file = 'webview2/x64/' + $args[0] + '/webview2.dll'
(Get-ItemProperty $file).VersionInfo.FileVersion
