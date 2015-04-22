#!/bin/bash

export CDIR=`pwd`

echo "Current folder is $CDIR"

echo "All variable for this build are `env`"

echo "current user used for this build is `whoami`"

export SF=`dirname $0`

cd $SF/../Debug

make "$@"

cd $CDIR

