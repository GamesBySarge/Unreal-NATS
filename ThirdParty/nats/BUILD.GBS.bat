@echo off

echo Building NATS dependencies

set BASE_DIR=%1
set OUTPUT_DIR=%2

echo BASE_DIR is %1

set SCRIPT_DIR=%BASE_DIR%\ThirdParty\nats
set BUILD_TYPE=Release

set SOURCE_DIR=%SCRIPT_DIR%\protobuf-c
set IMDT_DIR=%SCRIPT_DIR%\Intermediate
set BUILD_DIR=%IMDT_DIR%\protobuf-c
set INSTALL_DIR=%SCRIPT_DIR%\Binaries
set VCPKG_TARGET_TRIPLET=x64-windows

mkdir %IMDT_DIR%
mkdir %INSTALL_DIR%
mkdir %BUILD_DIR%

pushd %BUILD_DIR%

cmake -S %SOURCE_DIR% -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=%VCPKG_TARGET_TRIPLET% -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR% -DBUILD_SHARED_LIBS=1 -DCMAKE_BUILD_TYPE=%BUILD_TYPE% %SOURCE_DIR%\build-cmake

cmake --build . --config %BUILD_TYPE%
cmake --install . 

popd

echo Building NATS

set SOURCE_DIR=%SCRIPT_DIR%\nats.c
set BUILD_DIR=%SCRIPT_DIR%\Intermediate\nats

mkdir %BUILD_DIR%

pushd %BUILD_DIR%

cmake -S %SOURCE_DIR% -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=%VCPKG_TARGET_TRIPLET% -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR% -DBUILD_SHARED_LIBS=1 -DNATS_BUILD_LIB_STATIC=OFF -DBUILD_TESTING=OFF -DNATS_BUILD_EXAMPLES=OFF -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DNATS_BUILD_TLS_USE_OPENSSL_1_1_API=ON %SOURCE_DIR%

cmake --build . --config %BUILD_TYPE%
cmake --install . 

popd

echo Copying dependencies

echo copy %VCPKG_ROOT%\installed\x64-windows\bin\libssl-1_1-x64.dll %OUTPUT_DIR%
copy %VCPKG_ROOT%\installed\x64-windows\bin\libssl-1_1-x64.dll %OUTPUT_DIR%

echo copy %VCPKG_ROOT%\installed\x64-windows\bin\libcrypto-1_1-x64.dll %OUTPUT_DIR%
copy %VCPKG_ROOT%\installed\x64-windows\bin\libcrypto-1_1-x64.dll %OUTPUT_DIR%

echo copy %VCPKG_ROOT%\installed\x64-windows\bin\libprotobuf.dll %OUTPUT_DIR%
copy %VCPKG_ROOT%\installed\x64-windows\bin\libprotobuf.dll %OUTPUT_DIR%
