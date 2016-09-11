#!/bin/bash

# -----------------------
# Identify the script dir
# -----------------------

# source:
# http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
BUILD_DIR="$PWD"

echo "DIR = ${DIR}"
echo "BUILD_DIR = ${BUILD_DIR}"

if [ "$SRC_DIR" == "$DIR" ]
then
    echo "You must use a separate directory for building."
    echo "(try 'mkdir build; cd build; ../configure.sh')"
    exit 1
fi


#cpprest(include openssl)

mkdir ${DIR}/cpprestsdk-2.8.0/Build_android/build
cd ${DIR}/cpprestsdk-2.8.0/Build_android/build

( exec ../configure.sh --ndk ~/android-ndk-r10 --skip-boost --skip-libiconv )

cd ${BUILD_DIR}


##copy openssl folder
cp -r "${DIR}/cpprestsdk-2.8.0/Build_android/build/openssl" "${BUILD_DIR}"


cmake .. -DCMAKE_TOOLCHAIN_FILE=../android.toolchain.cmake \
	-DANDROID_NDK="${ANDROID_NDK}" \
	-DANDROID_ABI=armeabi-v7a \
	-DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-clang3.4 \
	-DANDROID_STL_FORCE_FEATURES=ON \
	-DANDROID_NATIVE_API_LEVEL=android-9 \
	-DANDROID_GOLD_LINKER=OFF \
	-DCMAKE_BUILD_TYPE=Debug



