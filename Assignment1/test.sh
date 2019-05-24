#!/bin/bash
echo "Welcome to this test script. First I'm going to print the files of my directory:"
ls

echo "Next, I make a new directory and enter into it."
mkdir testscript
cd testscript
ls

echo "Since this is empty, I'm going to create new files with the touch command."
touch testFile1 testFile2 testFile3 testFile4

echo "Now you can see all of my new files:"
ls

echo "Thanks for learning how to script with me!"
