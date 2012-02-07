@echo off
SETLOCAL
call setenv.cmd

REM For accessing the https repo 
SET GIT_SSL_NO_VERIFY=1

devenv /? > NUL
IF ERRORLEVEL 1 (
	echo.
	echo.ERROR: This file must be run inside a VS command prompt!
	echo.
	goto error_end
)

IF EXIST ..\build (
	echo.
	echo.ERROR: This file should NOT be executed within the libhdr source directory,
	echo.       but in a new empty folder!
	echo.
	goto error_end
)

IF NOT EXIST %CYGWIN_DIR%\bin\p7zip GOTO cygwin_error
IF NOT EXIST %CYGWIN_DIR%\bin\git.exe GOTO cygwin_error

IF NOT EXIST %CYGWIN_DIR%\bin\cvs.exe GOTO cygwin_error
IF NOT EXIST %CYGWIN_DIR%\bin\gzip.exe GOTO cygwin_error
IF NOT EXIST %CYGWIN_DIR%\bin\sed.exe GOTO cygwin_error
IF NOT EXIST %CYGWIN_DIR%\bin\ssh.exe GOTO cygwin_error
IF NOT EXIST %CYGWIN_DIR%\bin\svn.exe GOTO cygwin_error
IF NOT EXIST %CYGWIN_DIR%\bin\tar.exe GOTO cygwin_error
IF NOT EXIST %CYGWIN_DIR%\bin\unzip.exe GOTO cygwin_error
IF NOT EXIST %CYGWIN_DIR%\bin\wget.exe GOTO cygwin_error
GOTO cygwin_ok

:cygwin_error
echo ERROR: Cygwin with 
echo    cvs
echo    git 
echo    gzip 
echo    sed 
echo    ssh 
echo    svn 
echo    tar 
echo    unzip 
echo    wget
echo is required
GOTO error_end

:cygwin_ok

IF NOT DEFINED Configuration (
	set Configuration=Release
)

ml64.exe > NUL
IF ERRORLEVEL 1 (
	set Platform=Win32
	set RawPlatform=x86
) ELSE (
	set Platform=x64
	set RawPlatform=x64
)
IF DEFINED VS100COMNTOOLS (
	REM Visual Studio 2010
	set VS_SHORT=vc10
	set VS_CMAKE=Visual Studio 10
) ELSE (
	REM Visual Studio 2008
	set VS_SHORT=vc9
	set VS_CMAKE=Visual Studio 9 2008
)
IF %Platform% EQU x64 (
	set VS_CMAKE=%VS_CMAKE% Win64
)

cls
echo.
echo.--- %VS_CMAKE% ---
echo.Configuration = %Configuration%
echo.Platform = %Platform% (%RawPlatform%)
echo.

IF NOT EXIST %TEMP_DIR% (
	mkdir %TEMP_DIR%
)

IF NOT EXIST %TEMP_DIR%\boost_1_47_0.tar.gz (
	%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/boost_1_47_0.tar.gz http://sourceforge.net/projects/boost/files/boost/1.47.0/boost_1_47_0.tar.gz/download
	%CYGWIN_DIR%\bin\gzip.exe -d %TEMP_DIR%/boost_1_47_0.tar.gz

)

IF NOT EXIST boost_1_47_0 (
	echo.Extracting boost. Be patient!

	%CYGWIN_DIR%\bin\tar.exe -xf %TEMP_DIR%/boost_1_47_0.tar

	pushd boost_1_47_0
	bootstrap.bat
	popd
	
	pushd boost_1_47_0
	IF %Platform% EQU Win32 (
		IF %Configuration% EQU Release (
			b2.exe toolset=msvc variant=release
		) ELSE (
			b2.exe toolset=msvc variant=debug
		)
	) ELSE (
		IF %Configuration% EQU Release (
			b2.exe toolset=msvc variant=release address-model=64
		) ELSE (
			b2.exe toolset=msvc variant=debug address-model=64
		)
	)
	popd
)

REM Set Boost-directory as ENV variable (needed for CMake)
pushd boost_1_47_0
SET BOOST_ROOT=%CD%
popd

IF NOT EXIST libhdr (
	%CYGWIN_DIR%\bin\git.exe clone https://code.google.com/p/libhdr/ libhdr
) ELSE (
	pushd libhdr
	%CYGWIN_DIR%\bin\git.exe fetch
	CYGWIN_DIR%\bin\git.exe pull
	popd
)

IF NOT EXIST libhdr.build (
	mkdir libhdr.build
)

pushd libhdr.build
%CMAKE_DIR%\bin\cmake.exe -G "%VS_CMAKE%" ..\libhdr
popd

IF EXIST libhdr.build\LibHDR.sln (
	pushd libhdr.build
	devenv LibHDR.sln /Upgrade
	devenv LibHDR.sln /build "%Configuration%|%Platform%" /Project libHDR
	devenv LibHDR.sln /build "%Configuration%|%Platform%" /Project doc
	popd
)


goto end

:error_end
pause

:end

endlocal