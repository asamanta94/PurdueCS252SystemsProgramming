#!/bin/bash

# Referencing the arguments passed through variables
FILE=$1
BACKUP_DIR=$2
INTERVAL=$3
MAX_BACKUPS=$4
FOREVER_COND=1
OUTPUT_FILE=out.txt
REGEX='^[0-9]+$'

# If any of the arguments are not passed, then the program exits,
# with status 0
if [ -z "$FILE" ];
then
	exit 0
elif [ -z "$BACKUP_DIR" ];
then
	exit 0
elif [ -z "$INTERVAL" ];
then
	exit 0
elif [ -z "$MAX_BACKUPS" ];
then
	exit 0
elif ! [[ $INTERVAL =~ $REGEX ]];
then
	exit 0
elif ! [[ $MAX_BACKUPS =~ $REGEX ]];
then
	exit 0
fi

# If the file provided for backup is a file, then just 
# back it up like a file, otherwise, if the file provided for 
# backup is a directory, then copy it recursively, with the
# name and time stamp
if [ -f $FILE ];
then
	if [ -d $BACKUP_DIR ];
	then
		FILENAME=$(date +"%Y-%m-%d-%H-%M-%S")-$FILE
		mv $FILE $BACKUP_DIR/$FILENAME
	fi
elif [ -d $FILE ];
then
	if [ -d $BACKUP_DIR ];
	then
		FILENAME=$(date +"%Y-%m-%d-%H-%M-%S")-$FILE
		mkdir $BACKUP_DIR/$FILENAME
		cp -r $FILE/* $BACKUP_DIR/$FILENAME
	fi
fi

# Forever loop to keep checking for changes
while [ $FOREVER_COND -gt 0 ];
do
	sleep $INTERVAL
	# If the file provided is a regular file, use normal copy
	# else if the file provided is a directory, recursively copy it
	if [ -f $FILE ];
	then
		diff $FILE $BACKUP_DIR/$FILENAME>$OUTPUT_FILE
		if [ -s $OUTPUT_FILE ];
		then
			NUM_BACKUPS=$(ls | wc -l)
			if [ $NUM_BACKUPS -ge $MAX_BACKUPS ];
			then
				OLDEST_BACKUP=$(ls -t $BACKUP_DIR | sort | head -1)
				rm $BACKUP_DIR/$OLDEST_BACKUP
			fi
			# Mail about the changes
			FILENAME=$(date +"%Y-%m-%d-%H-%M-%S")-$FILE
			cp $FILE $BACKUP_DIR/$FILENAME
			/usr/bin/mailx -s "File Changed" $USER < $OUTPUT_FILE
		fi
	elif [ -d $FILE ];
	then
		diff -r $FILE $BACKUP_DIR/$FILENAME>$OUTPUT_FILE
		if [ -s $OUTPUT_FILE ];
		then
			NUM_BACKUPS=$(ls | wc -l)
			if [ $NUM_BACKUPS -ge $MAX_BACKUPS ];
			then
				OLDEST_BACKUP=$(ls -t $BACKUP_DIR | sort | head -1)
				rm -r $BACKUP_DIR/$OLDEST_BACKUP
			fi
			# Mail about changes
			FILENAME=$(date +"%Y-%m-%d-%H-%M-%S")-$FILE
			mkdir $BACKUP_DIR/$FILENAME
			cp -r $FILE/* $BACKUP_DIR/$FILENAME
			/usr/bin/mailx -s "File Changed" $USER < $OUTPUT_FILE
		fi
	fi
	# remove output file
	rm $OUTPUT_FILE
done