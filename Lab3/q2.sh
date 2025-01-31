#!/bin/bash

read -p "Enter the directory path: " directory

read -p "Enter the pattern:" pattern

ls $directory | grep "$pattern" 
