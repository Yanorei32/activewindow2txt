# activewindow2txt


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

