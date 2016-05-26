#!/bin/bash
FILES=/path/to/*
for f in $FILES
do
	echo "Processing $f file..."
	# take action on each file. $f store current file name
	Icon-O-Matic "$f" &
	hey Icon-O-Matic Set Text [1 to 4] of View 0 of View 4 of View 0 of Window 1 to  "$f.rdef"
	# invoke the save button
	hey Icon-O-Matic DO of View 7  of View 0 of Window 1
	hey Icon-O-Matic QUIT
done


