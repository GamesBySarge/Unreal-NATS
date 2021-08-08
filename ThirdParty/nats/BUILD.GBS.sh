#!/bin/bash

echo "Running GBSNats ThirdParty nats BUILD.GBS.sh"

SCRIPT_DIR=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
BUILD_TYPE=Release

SYSTEM=$(uname)
MACHINE=$(uname -m)
CMAKE=~/deps/cmake-install/bin/cmake
PLATFORM=${SYSTEM}/${MACHINE}
SOURCE_DIR=${SCRIPT_DIR}/nats.c
BUILD_DIR=${SCRIPT_DIR}/Intermediate
INSTALL_DIR=${SCRIPT_DIR}/Binaries

mkdir -p ${INSTALL_DIR}

${CMAKE} -G "Unix Makefiles" -S ${SOURCE_DIR}  -B ${BUILD_DIR} -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}

pushd ${BUILD_DIR}

make nats_static
make install

popd
