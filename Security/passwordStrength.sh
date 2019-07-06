#!/bin/bash

#	Roman Parkhomenko
# CST-221
# 07/05/2019
# Password Strength

# The purpose of this script is to read a password, determine it's strength, and then notify
# the user of the password's strength and the factors that should be improved. To pass the
# the script, the password must be at least 8 characters, contain at least one number, and
# contain at least one special symbol.

# Counter variable.
x=0

# Read password.
read -p "Please enter a password to test and hit Enter: " password;

passwordLength=${#password}
if (("$passwordLength" < "8")); then
	echo 'Your password should be at least 8 characters long.'
else
	let "x++"
fi

if [[ $password =~ [0-9] ]]; then
	let "x++"
else
	echo 'Your password should have at least one number.'
fi

if [[ $password == *['!'@#\$%^\&*()_+]* ]]; then
	let "x++"
else
	echo 'Your password should contain at least one special character.'
fi

if [ "$x" -eq "3" ]; then
	echo 'Your password is secure!'
fi
