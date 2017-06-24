#!/bin/sh

LATEST_RELEASE=`git tag | grep RELEASE_ | sort | tail -1`
COMMITS_SINCE_RELEASE=`git log --oneline $LATEST_RELEASE..HEAD | egrep -c .`

BOARD=TYTMD RELEASE=1 gmake V=1
arm-none-eabi-objcopy -O binary espruino_1v92.${COMMITS_SINCE_RELEASE}_tyt.elf espruino_1v92.${COMMITS_SINCE_RELEASE}_tyt.img
../md380tools/md380-fw --wrap espruino_1v92.${COMMITS_SINCE_RELEASE}_tyt.img espruino_1v92.${COMMITS_SINCE_RELEASE}_tyt.bin
../md380tools/md380-dfu upgrade espruino_1v92.${COMMITS_SINCE_RELEASE}_tyt.bin
