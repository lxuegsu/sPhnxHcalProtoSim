#!/bin/csh

echo " welcome to process.csh ! "

set DIR =  /direct/phenix+sim01/phnxreco/users/lxue/G4Sim_HCalPrototype/XHeVision2/towerbuild 
set EXE       = $DIR/bin/analysis

set INPUTDIR  = $DIR/input/datalist
set INPUTROOT = `cat $INPUTDIR/$1.list` 
set OUTPUTDIR  = $DIR/output

#set RUNNUMBER=`echo $INPUTROOT | awk -F. '{print $1}' | awk -F- '{print $2 "-" $3}'`
set ROOTFILE=`echo $INPUTROOT | awk -F/ '{print $10}'`
set OUTROOT="$OUTPUTDIR/$ROOTFILE"

$EXE $INPUTROOT $OUTROOT
echo "job $1 finished"
