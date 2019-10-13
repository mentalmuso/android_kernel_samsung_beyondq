#!/bin/bash

DEVICE=beyond2qlte
VER=N9750_v1.1
DEFCONFIG=beyond2qlte_usa_single_defconfig
AKDEVICE='/device.name1=*/c\device.name1=beyond2qlte'
AKDEVICE2='/device.name2=*/c\device.name2=beyond2qltexx'

BUILD_CROSS_COMPILE=/home/mentalmuso/kernel/toolchain/4.9-2/bin/aarch64-linux-android-
KERNEL_LLVM_BIN=/home/mentalmuso/kernel/toolchain/clang2/bin/clang
CLANG_TRIPLE=aarch64-linux-gnu-
KERNEL_MAKE_ENV="DTC_EXT=$(pwd)/tools/dtc CONFIG_BUILD_ARM64_DT_OVERLAY=y"
KERN=/home/mentalmuso/kernel/android_kernel_samsung_beyond
TODAY=`date +%Y-%m-%d.%H:%M`
WETA=$KERN/WETA
AKOLDZIP=$WETA/weta_anykernel/WETA_Kernel_*
AKOLDIMG=$WETA/weta_anykernel/zImage

export ANDROID_MAJOR_VERSION=p
export PLATFORM_VERSION=9.0.0

mkdir out
mkdir $WETA/beyondqlteusa

export ARCH=arm64

make -j8 -C $(pwd) O=$(pwd)/out $KERNEL_MAKE_ENV ARCH=arm64 CROSS_COMPILE=$BUILD_CROSS_COMPILE REAL_CC=$KERNEL_LLVM_BIN CLANG_TRIPLE=$CLANG_TRIPLE $DEFCONFIG
make -j8 -C $(pwd) O=$(pwd)/out $KERNEL_MAKE_ENV ARCH=arm64 CROSS_COMPILE=$BUILD_CROSS_COMPILE REAL_CC=$KERNEL_LLVM_BIN CLANG_TRIPLE=$CLANG_TRIPLE

cp out/arch/arm64/boot/Image $(pwd)/arch/arm64/boot/Image
cp $(pwd)/out/arch/arm64/boot/Image-dtb $(pwd)/WETA/beyondqlteusa/Image-dtb

#  anykernel
#cd $WETA/weta_anykernel
#sed -i $AKDEVICE anykernel.sh
#sed -i $AKDEVICE2 anykernel.sh
#rm $AKOLDZIP && rm $AKOLDIMG
#cp $WETA/$DEVICE/Image-dtb $WETA/weta_anykernel/zImage
#zip -r -7 WETA_Kernel_$VER.zip *
#mv WETA_Kernel_$VER.zip $WETA/$DEVICE

echo " "
echo "###########################################"
echo "# Kernel zip and img found in WETA folder #"
echo "###########################################"
echo " "


