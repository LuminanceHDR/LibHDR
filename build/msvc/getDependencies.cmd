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

IF NOT EXIST %TEMP_DIR%\zlib125.zip (
	%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/zlib125.zip http://prdownloads.sourceforge.net/libpng/zlib125.zip?download
)
IF NOT EXIST zlib-1.2.5 (
	%CYGWIN_DIR%\bin\unzip.exe -q %TEMP_DIR%/zlib125.zip
	REN zlib-1.2.6 zlib-1.2.5
	pushd zlib-1.2.5\contrib\masmx64
	call bld_ml64.bat
	cd ..\masmx86
	call bld_ml32.bat
	cd ..\vstudio\%VS_SHORT%
	devenv zlibvc.sln /build "%Configuration%|%Platform%"
	popd
)

IF NOT EXIST %TEMP_DIR%\expat-2.0.1.tar (
	%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/expat-2.0.1.tar.gz http://sourceforge.net/projects/expat/files/expat/2.0.1/expat-2.0.1.tar.gz/download
	%CYGWIN_DIR%\bin\gzip.exe -d %TEMP_DIR%/expat-2.0.1.tar.gz
)
IF NOT EXIST expat-2.0.1 (
	%CYGWIN_DIR%\bin\tar.exe -xf %TEMP_DIR%/expat-2.0.1.tar
)

IF NOT EXIST exiv2-trunk (
	set exiv2-compile=true
	%CYGWIN_DIR%\bin\svn.exe co -r 2672 svn://dev.exiv2.org/svn/trunk exiv2-trunk
) ELSE (
	rem svn update exiv2-trunk
	rem set exiv2-compile=true
)

IF DEFINED exiv2-compile (
	REM msvc64 is the right one for Win32 too
	pushd exiv2-trunk\msvc64 		
	devenv exiv2.sln /upgrade
	devenv exiv2.sln /build "%Configuration%DLL|%Platform%" 
	popd
)


IF NOT EXIST %TEMP_DIR%\jpegsr8d.zip (
	%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/jpegsr8d.zip http://www.ijg.org/files/jpegsr8d.zip
)
IF NOT EXIST libjpeg (
	%CYGWIN_DIR%\bin\unzip.exe -q %TEMP_DIR%/jpegsr8d.zip
	ren jpeg-8d libjpeg

	pushd libjpeg
	copy jconfig.vc jconfig.h
	copy makejsln.v10 makejsln.sln
	copy makeasln.v10 makeasln.sln
	copy makejvcx.v10 jpeg.vcxproj
	copy makecvcx.v10 cjpeg.vcxproj
	copy makedvcx.v10 djpeg.vcxproj
	copy maketvcx.v10 jpegtran.vcxproj
	copy makewvcx.v10 wrjpgcom.vcxproj
	copy makervcx.v10 rdjpgcom.vcxpr

	nmake /f makefile.vc
	popd
)

IF NOT EXIST %TEMP_DIR%\tiff-4.0.1.zip (
	%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/tiff-4.0.1.zip http://download.osgeo.org/libtiff/tiff-4.0.1.zip
)

IF NOT EXIST tiff-4.0.1 (
	%CYGWIN_DIR%\bin\unzip.exe -q %TEMP_DIR%/tiff-4.0.1.zip

	echo.JPEG_SUPPORT=^0> tiff-4.0.1\qtpfsgui_commands.in
	echo.JPEGDIR=..\..\libjpeg>> tiff-4.0.1\qtpfsgui_commands.in
	echo.JPEG_INCLUDE=-I$^(JPEGDIR^)>> tiff-4.0.1\qtpfsgui_commands.in
	echo.JPEG_LIB=$^(JPEGDIR^)\libjpeg.lib>> tiff-4.0.1\qtpfsgui_commands.in
	echo.ZIP_SUPPORT=^0>> tiff-4.0.1\qtpfsgui_commands.in
	echo.ZLIBDIR=..\..\zlib-1.2.5\contrib\vstudio\%VS_SHORT%\%RawPlatform%\ZlibDll%Configuration%>> tiff-4.0.1\qtpfsgui_commands.in
	echo.ZLIB_INCLUDE=-I..\..\zlib-1.2.5>> tiff-4.0.1\qtpfsgui_commands.in
	echo.ZLIB_LIB=$^(ZLIBDIR^)\zlibwapi.lib>> tiff-4.0.1\qtpfsgui_commands.in

	pushd tiff-4.0.1
	nmake /s /c /f Makefile.vc @qtpfsgui_commands.in
	popd
)

IF NOT EXIST %TEMP_DIR%\LibRaw-0.14.5.zip (
	%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/LibRaw-0.14.5.zip http://www.libraw.org/data/LibRaw-0.14.5.zip
)
IF NOT EXIST LibRaw-0.14.5 (
	%CYGWIN_DIR%\bin\unzip.exe -q %TEMP_DIR%/LibRaw-0.14.5.zip

	pushd LibRaw-0.14.5
	nmake /f Makefile.msvc
	popd
)

IF NOT EXIST %TEMP_DIR%\gsl-1.15.tar (
	%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/gsl-1.15.tar.gz ftp://ftp.gnu.org/gnu/gsl/gsl-1.15.tar.gz
	%CYGWIN_DIR%\bin\gzip -d %TEMP_DIR%/gsl-1.15.tar.gz
)
IF NOT EXIST %TEMP_DIR%\gsl-1.15-vc10.zip (
	%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/gsl-1.15-vc10.zip http://gladman.plushost.co.uk/oldsite/computing/gsl-1.15-vc10.zip
)
IF NOT EXIST gsl-1.15 (
	%CYGWIN_DIR%\bin\tar.exe -xf %TEMP_DIR%/gsl-1.15.tar
	%CYGWIN_DIR%\bin\unzip.exe -o -q -d gsl-1.15 %TEMP_DIR%/gsl-1.15-vc10.zip

	pushd gsl-1.15\build.vc10
	IF %VS_SHORT% EQU vc9 (
		%CYGWIN_DIR%\bin\sed.exe -i 's/Format Version 11.00/Format Version 10.00/g' gsl.lib.sln
	)
	devenv gsl.lib.sln /Upgrade
	devenv gsl.lib.sln /build "%Configuration%|%Platform%" /Project gslhdrs
	gslhdrs\%Platform%\%Configuration%\gslhdrs.exe
	devenv gsl.lib.sln /build "%Configuration%|%Platform%" /Project gsllib
	popd
)

IF NOT EXIST OpenExrStuff (
	pushd .
	mkdir OpenExrStuff
	cd OpenExrStuff
	
	for %%v in ("Deploy", "Deploy\include", "Deploy\lib\%Platform%\%Configuration%", "Deploy\bin\%Platform%\%Configuration%", "openexr-cvs") do (
		mkdir %%v
	)
	popd
	
	copy zlib-1.2.5\*.h OpenExrStuff\Deploy\include
	copy zlib-1.2.5\contrib\vstudio\%VS_SHORT%\%RawPlatform%\ZlibDll%Configuration%\*.lib OpenExrStuff\Deploy\lib\%Platform%\%Configuration%
	copy zlib-1.2.5\contrib\vstudio\%VS_SHORT%\%RawPlatform%\ZlibDll%Configuration%\*.dll OpenExrStuff\Deploy\bin\%Platform%\%Configuration%
)
	
pushd OpenExrStuff\openexr-cvs
IF NOT EXIST IlmBase (
	%CYGWIN_DIR%\bin\cvs.exe -d :pserver:anonymous:anonymous@cvs.savannah.nongnu.org:/sources/openexr co IlmBase
	set openexr-compile=true
) ELSE (
	rem %CYGWIN_DIR%\bin\cvs.exe -d :pserver:anonymous:anonymous@cvs.savannah.nongnu.org:/sources/openexr update IlmBase
)
IF NOT EXIST OpenEXR (
	%CYGWIN_DIR%\bin\cvs.exe -d :pserver:anonymous:anonymous@cvs.savannah.nongnu.org:/sources/openexr co OpenEXR
	set openexr-compile=true
) ELSE (
	rem %CYGWIN_DIR%\bin\cvs.exe -d :pserver:anonymous:anonymous@cvs.savannah.nongnu.org:/sources/openexr update OpenEXR
)
popd

IF DEFINED openexr-compile (
	pushd OpenExrStuff\openexr-cvs\IlmBase\vc\vc9\IlmBase
	devenv IlmBase.sln /Upgrade
	devenv IlmBase.sln /build "%Configuration%|%Platform%"
	popd

	pushd OpenExrStuff\openexr-cvs\OpenEXR\vc\vc8\OpenEXR
	devenv OpenEXR.sln /Upgrade
	devenv OpenEXR.sln /build "%Configuration%|%Platform%" /Project IlmImf
	popd
)

IF %Platform% EQU Win32 (
	IF NOT EXIST %TEMP_DIR%\fftw-3.3-dll32.zip (
		%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/fftw-3.3-dll32.zip ftp://ftp.fftw.org/pub/fftw/fftw-3.3-dll32.zip
	)
) ELSE (
	IF NOT EXIST %TEMP_DIR%\fftw-3.3-dll64.zip (
		%CYGWIN_DIR%\bin\wget.exe -O %TEMP_DIR%/fftw-3.3-dll64.zip ftp://ftp.fftw.org/pub/fftw/fftw-3.3-dll64.zip
	)
)

IF NOT EXIST fftw-3.3-dll (
	IF %Platform% EQU Win32 (
		%CYGWIN_DIR%\bin\unzip.exe -q -d fftw-3.3-dll %TEMP_DIR%/fftw-3.3-dll32.zip
	) ELSE (
		%CYGWIN_DIR%\bin\unzip.exe -q -d fftw-3.3-dll %TEMP_DIR%/fftw-3.3-dll64.zip
	)

	pushd fftw-3.3-dll
	lib /def:libfftw3-3.def
	lib /def:libfftw3f-3.def
	lib /def:libfftw3l-3.def
	popd
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

IF NOT EXIST libhdrStuff (
	mkdir libhdrStuff
)

IF NOT EXIST libhdrStuff\libhdr (
	pushd libhdrStuff
	%CYGWIN_DIR%\bin\git.exe clone https://code.google.com/p/libhdr/ libhdr
	popd
) ELSE (
	pushd libhdrStuff\libhdr
	IF %UPDATE_REPO_LIBHDR% EQU 1 (
		%CYGWIN_DIR%\bin\git.exe pull
	)
	popd
)

IF NOT EXIST libhdrStuff\libhdr (
	GOTO error_end
)


IF NOT EXIST libhdrStuff\DEPs (
	pushd libhdrStuff
	mkdir DEPs
	cd DEPs
	mkdir include
	mkdir lib
	mkdir bin
	popd
	
	for %%v in ("exiv2", "libtiff", "libraw", "OpenEXR", "fftw3", "gsl") do (
		mkdir libhdrStuff\DEPs\include\%%v
		mkdir libhdrStuff\DEPs\lib\%%v
		mkdir libhdrStuff\DEPs\bin\%%v
	)
	
	copy exiv2-trunk\msvc64\include\* libhdrStuff\DEPs\include\exiv2
	copy exiv2-trunk\msvc64\include\exiv2\* libhdrStuff\DEPs\include\exiv2

	copy exiv2-trunk\msvc64\exiv2lib\%Platform%\%Configuration%DLL\*.lib libhdrStuff\DEPs\lib\exiv2
	copy exiv2-trunk\msvc64\exiv2lib\%Platform%\%Configuration%DLL\*.dll libhdrStuff\DEPs\bin\exiv2
	
	copy tiff-4.0.1\libtiff\*.h libhdrStuff\DEPs\include\libtiff
	copy tiff-4.0.1\libtiff\*.lib libhdrStuff\DEPs\lib\libtiff
	copy tiff-4.0.1\libtiff\*.dll libhdrStuff\DEPs\bin\libtiff
	
	mkdir libhdrStuff\DEPs\include\libraw\libraw
	copy LibRaw-0.14.5\libraw\*.h libhdrStuff\DEPs\include\libraw\libraw
	copy LibRaw-0.14.5\lib\*.lib libhdrStuff\DEPs\lib\libraw
	copy LibRaw-0.14.5\bin\*.dll libhdrStuff\DEPs\bin\libraw
	
	copy OpenExrStuff\Deploy\include\*.h libhdrStuff\DEPs\include\OpenEXR
	copy OpenExrStuff\Deploy\lib\%Platform%\%Configuration%\*.lib libhdrStuff\DEPs\lib\OpenEXR
	copy OpenExrStuff\Deploy\bin\%Platform%\%Configuration%\*.dll libhdrStuff\DEPs\bin\OpenEXR

	copy fftw-3.3-dll\*.h libhdrStuff\DEPs\include\fftw3
	copy fftw-3.3-dll\*.lib libhdrStuff\DEPs\lib\fftw3
	copy fftw-3.3-dll\*.dll libhdrStuff\DEPs\bin\fftw3

	mkdir libhdrStuff\DEPs\include\gsl\gsl
	copy gsl-1.15\gsl\*.h libhdrStuff\DEPs\include\gsl\gsl
	copy gsl-1.15\build.vc10\lib\%Platform%\%Configuration%\*.lib libhdrStuff\DEPs\lib\gsl
	copy gsl-1.15\build.vc10\dll\*.dll libhdrStuff\DEPs\bin\gsl

)

IF NOT EXIST libhdrStuff\libhdr.build (
	pushd libhdrStuff
	mkdir libhdr.build
	popd
)

pushd libhdrStuff\libhdr.build
	%CMAKE_DIR%\bin\cmake.exe -G "%VS_CMAKE%" ..\libhdr
	IF EXIST LibHDR.sln (
		devenv LibHDR.sln /Upgrade
		REM Building everything, without running the tests
		devenv LibHDR.sln /build "%Configuration%|%Platform%" /Project ALL_BUILD
		devenv LibHDR.sln /build "%Configuration%|%Platform%" /Project doc
	)
	IF EXIST test\Release\libhdr_stats.exe (
		%CMAKE_DIR%\bin\ctest.exe
	)
popd


goto end

:error_end
pause

:end

endlocal