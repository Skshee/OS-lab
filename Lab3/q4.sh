#!/bin/sh

read -p "Enter Basics:" Basics

read -p "Enter TA:" TA

GS=$(echo "($Basics + $TA + $Basics* 0.1)" | bc)

echo "GS = $GS"

