# activewindow2txt

## format

| text                                  | description                      |
|:--------------------------------------|:---------------------------------|
| `{activewindow2txt:title}`            | Window Title                     |
| `{activewindow2txt:processId}`        | Process ID                       |
| `{activewindow2txt:applicationPath}`  | Application executable full path |
| `{activewindow2txt:applicationName}`  | Application executable name      |
| `{activewindow2txt:applicationAlias}` | Application alias name           |

## build (example)

Windows 10 SDK is required.

```
cl ^
	main.cxx ^
	"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x64\Psapi.Lib" ^
	"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x64\ShLwApi.Lib" ^
	"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x64\User32.Lib" ^
	/std:c++latest ^
	/Fe:activewindow2txt.exe
```

