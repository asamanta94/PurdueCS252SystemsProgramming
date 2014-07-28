#!/bin/bash

# Storing password file
PASSWORD_FILE=$1

# Checking if file exists
if [ -a $PASSWORD_FILE ]; 
then
	PASSWORD=$(<$PASSWORD_FILE)
	LENGTH=${#PASSWORD}
	VALID_LENGTH=6
	TOTAL_SCORE=0

	# If statement to check the validity of the password
	if [ $LENGTH -lt $VALID_LENGTH ];
	then
		echo "Error: Password length invalid."
		exit 0
	else
		TOTAL_SCORE=LENGTH
	fi

	# If statement to check special characters
	if egrep -q [$\#\+%@] $PASSWORD_FILE; 
	then 
		let TOTAL_SCORE=TOTAL_SCORE+5
	fi

	# If statment to check if the password has at least one number
	if egrep -q [0-9] $PASSWORD_FILE;
	then
		let TOTAL_SCORE=TOTAL_SCORE+5
	fi

	# If statement to check if there is at least one alpha character.
	if egrep -q [A-Z] $PASSWORD_FILE;
	then
		let TOTAL_SCORE=TOTAL_SCORE+5
	elif egrep -q [a-z] $PASSWORD_FILE;
	then
		let TOTAL_SCORE=TOTAL_SCORE+5
	fi

	# If statement to check repitition of alphanumeric characters
	if egrep -q [A-Z]+ $PASSWORD_FILE;
	then 
		let TOTAL_SCORE=TOTAL_SCORE-10
	elif egrep -q [a-z]+ $PASSWORD_FILE;
	then
		let TOTAL_SCORE=TOTAL_SCORE-10
	elif egrep -q [0-9]+ $PASSWORD_FILE;
	then
		let TOTAL_SCORE=TOTAL_SCORE-10
	fi

	# If statement to check consecutivity of three lowercase, uppercase characters or 
	# numbers
	if egrep -q [a-z][a-z][a-z] $PASSWORD_FILE;
	then
		let TOTAL_SCORE=TOTAL_SCORE-3
	fi

	if egrep -q [A-Z][A-Z][A-z] $PASSWORD_FILE;
	then
		let TOTAL_SCORE=TOTAL_SCORE-3
	fi
	
	if egrep -q [0-9][0-9][0-9] $PASSWORD_FILE;
	then 
		let TOTAL_SCORE=TOTAL_SCORE-3
	fi

	# Printing final message with score
	echo "Password Score: $TOTAL_SCORE"
else
	echo "$PASSWORD_FILE does not exist"
fi
