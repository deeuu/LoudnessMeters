#!/bin/bash

srcdirs="/home/dominic/git/loudness/src/thirdParty
/home/dominic/git/loudness/src/modules
/home/dominic/git/loudness/src/models
/home/dominic/git/loudness/src/support"
dstdir="./src/loudnessCode"

for srcfile in ${srcdirs}
do
    echo $srcfile
    cp -r $srcfile $dstdir
done

rm "$dstdir/models/StationaryLoudnessANSIS342007.cpp"
rm "$dstdir/models/StationaryLoudnessANSIS342007.h"
rm "$dstdir/models/StationaryLoudnessCHGM2011.cpp"
rm "$dstdir/models/StationaryLoudnessCHGM2011.h"
rm "$dstdir/models/StationaryLoudnessDIN456311991.cpp"
rm "$dstdir/models/StationaryLoudnessDIN456311991.h"
rm "$dstdir/modules/InstantaneousLoudnessDIN456311991.cpp"
rm "$dstdir/modules/InstantaneousLoudnessDIN456311991.h"
rm "$dstdir/modules/MainLoudnessDIN456311991.cpp"
rm "$dstdir/modules/MainLoudnessDIN456311991.h"
rm "$dstdir/modules/OctaveBank.cpp"
rm "$dstdir/modules/OctaveBank.h"
rm "$dstdir/modules/AudioFileCutter.cpp"
rm "$dstdir/modules/AudioFileCutter.h"
rm "$dstdir/modules/Biquad.cpp"
rm "$dstdir/modules/Biquad.h"
rm "$dstdir/modules/SMA.cpp"
rm "$dstdir/modules/SMA.h"
rm "$dstdir/support/AudioFileProcessor.cpp"
rm "$dstdir/support/AudioFileProcessor.h"
rm "$dstdir/support/Timer.cpp"
rm "$dstdir/support/Timer.h"
