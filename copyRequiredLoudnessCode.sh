#!/bin/bash

srcdir="/home/dominic/git/loudness/src"
dstdir="./src/loudnessCode"

for srcfile in ${srcdir}/*
do
    echo $srcfile
    cp -r $srcfile $dstdir
done

rm "$dstdir/models/SteadyStateLoudnessANSIS342007.cpp"
rm "$dstdir/models/SteadyStateLoudnessANSIS342007.h"
rm "$dstdir/modules/AudioFileCutter.cpp"
rm "$dstdir/modules/AudioFileCutter.h"
rm "$dstdir/modules/Biquad.cpp"
rm "$dstdir/modules/Biquad.h"
rm "$dstdir/modules/SMA.cpp"
rm "$dstdir/modules/SMA.h"
rm -rf "$dstdir/modules/temp/"
rm "$dstdir/support/AudioFileProcessor.cpp"
rm "$dstdir/support/AudioFileProcessor.h"
rm "$dstdir/support/Timer.cpp"
rm "$dstdir/support/Timer.h"
