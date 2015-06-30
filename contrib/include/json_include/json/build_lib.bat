@setlocal

@call "%VS100COMNTOOLS%vsvars32.bat"

@set COMPILER=cl /nologo /MD /O2 /W3 /c /EHsc /D_CRT_SECURE_NO_DEPRECATE /DJSON_NO_AUTOLINK /I "../"
@set LIBER=lib /nologo

@%COMPILER% *.cpp
@%LIBER% /out:lib/json.lib *.obj
@del *.obj

@rem multi debug
@set COMPILER=cl /nologo /MDd /Od /W3 /c /EHsc /D_CRT_SECURE_NO_DEPRECATE /DJSON_NO_AUTOLINK /I "../"
@set LIBER=lib /nologo

@%COMPILER% *.cpp
@%LIBER% /out:lib/json_d.lib *.obj
@del *.obj

@endlocal