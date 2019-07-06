#!/bin/bash

#	Roman Parkhomenko
# CST-221
# 07/05/2019
# Manage Users

# The purpose of this script is to read a text file containing a list of usernames and passwords.
# The script will loop through the file and based on the command given, add or remove the list of
# users to a given group name.

filename=$1
group=$2
operation=$3

if grep -q $group /etc/group
then
     echo "$group group already exists!"
else
     groupadd $group
fi

# Function to add user to group
if [[ "$3" == "-a" ]]; then

$filename
while read -r username password
do
  name="$username"
	pass="$password"
	echo "Username: $name"
	echo "Password: $pass"

  if [ $(id -u) -eq 0 ]; then
		egrep "^$name" /etc/passwd >/dev/null
		if [ $? -eq 0 ]; then
			echo "$name exists!"
			exit 1
		else
			useradd -m -p $pass $name
			[ $? -eq 0 ] && echo "User has been added to system!" || echo "Failed to add user."
		fi
	else
		echo "You must have root access to add users!"
		exit 2
	fi
	usermod -aG $group $name
done < "$filename"
fi

# # Function to remove user from a user group.
if [[ "$3" == "-r" ]]; then

$filename
while read -r username password
do
	name="$username"
	pass="$password"
	userdel -r $name
	echo "$name deleted."
done < "$filename"

if grep -q $group /etc/group
then
	groupdel $group
else
     	echo "Group does not exist."
fi

fi
