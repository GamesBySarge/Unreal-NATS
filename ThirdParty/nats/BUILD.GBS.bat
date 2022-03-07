@echo off

echo Building NATS dependencies

REM TODO Get this from the environment or command-line
set BASE_DIR=D:\fu\Plugins\GBSNats
set SCRIPT_DIR=%BASE_DIR%\ThirdParty\nats
set BUILD_TYPE=Release

set SOURCE_DIR=%SCRIPT_DIR%\protobuf-c
set BUILD_DIR=%SCRIPT_DIR%\Intermediate\protobuf-c
set INSTALL_DIR=%SCRIPT_DIR%\Binaries
set VCPKG_DIR=D:\vcpkg
set VCPKG_TARGET_TRIPLET=x64-windows

mkdir %INSTALL_DIR%
mkdir %BUILD_DIR%

pushd %BUILD_DIR%

cmake -G "Visual Studio 16 2019" -S %SOURCE_DIR% -DCMAKE_TOOLCHAIN_FILE=%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=%VCPKG_TARGET_TRIPLET% -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR% -DBUILD_SHARED_LIBS=1 -DCMAKE_BUILD_TYPE=%BUILD_TYPE% %SOURCE_DIR%\build-cmake

cmake --build . --config %BUILD_TYPE%
cmake --install . 

popd

echo Building NATS

set SOURCE_DIR=%SCRIPT_DIR%\nats.c
set BUILD_DIR=%SCRIPT_DIR%\Intermediate\nats

mkdir %BUILD_DIR%

pushd %BUILD_DIR%

cmake -G "Visual Studio 16 2019" -S %SOURCE_DIR% -DCMAKE_TOOLCHAIN_FILE=%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=%VCPKG_TARGET_TRIPLET% -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR% -DBUILD_SHARED_LIBS=1 -DNATS_BUILD_LIB_STATIC=OFF -DBUILD_TESTING=OFF -DCMAKE_BUILD_TYPE=%BUILD_TYPE% %SOURCE_DIR%

cmake --build . --config %BUILD_TYPE%
cmake --install . 

popd

echo Copying editor libraries

copy %INSTALL_DIR%\bin\*.dll %BASE_DIR%\Binaries\Win64
copy %INSTALL_DIR%\lib\*.dll %BASE_DIR%\Binaries\Win64
