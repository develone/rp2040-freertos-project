#!/bin/bash

cd ~/

rm -rf picoprobe

git clone git@github.com:develone/picoprobe.git 

cd picoprobe

git clone git@github.com:develone/pico-sdk.git

cd pico-sdk

git submodule update --init

cd ../

mkdir build

cd build 

export PICO_SDK_PATH=/home/devel/picoprobe/pico-sdk/

echo $PICO_SDK_PATH

cd ~/picoprobe/build

