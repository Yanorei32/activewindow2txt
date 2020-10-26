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


x64 Native Tools Command Prompt for VS 2019:

```
cl ^
	main.cxx ^
	"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x64\Psapi.Lib" ^
	"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x64\ShLwApi.Lib" ^
	"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x64\User32.Lib" ^
	/std:c++17 ^
	/Fe:activewindow2txt.exe
```


Cygwin environment:

```bash
g++ \
	main.cxx \
	/cygdrive/c/Windows/System32/psapi.dll \
	/cygdrive/c/Windows/System32/shlwapi.dll \
	--std=c++17 \
	-o activewindow2txt_cyg.exe
```

