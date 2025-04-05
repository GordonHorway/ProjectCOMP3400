#!/bin/zsh

FILEDIRECTORY=$1

for FILE in $(ls)
do
    cp $FILE $FILEDIRECTORY/$FILE.bak
done

echo "all done!"