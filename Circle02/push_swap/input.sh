#!/bin/bash

OS=$(uname)
NAME=./push_swap
MIN=-300
MAX=300

chmod +x input.sh $NAME

if [ "$OS" == "Darwin" ]; then
	RANDOMIZER="sort -R"
	CHECKER=checker_Mac
elif [ "$OS" == "Windows" ]; then
	RANDOMIZER=shuf
	CHECKER=checker_linux
fi

ARG=$(seq $MIN $MAX | $RANDOMIZER | head -n $1 | paste -sd' ' -)

echo -e "\n======= Push_Swap Tester =======\n"

echo -e "File information"
file $NAME

echo -e "\nPassing set of $1 numbers\n $ARG"

echo -e "\nCounting required operations..."
$NAME $ARG | wc -l | tr -d ' '

echo -e "\nTesting with checker program"
$NAME $ARG | ./tests/$CHECKER $ARG

# case $1 in
#   5)
# 	ARG=$(seq $MIN $MAX | sort -R | head -n 5 | paste -sd' ' -)
# 	;;
#   100)
# 	ARG=$(seq $MIN $MAX | shuf | head -n 100 | paste -sd' ' -)
# 	;;
#   500)
# 	ARG=$(seq $MIN $MAX | shuf | head -n 500 | paste -sd' ' -)
# 	;;
#   *)
# 	echo "Usage: $0 [5|100|500]"
# 	exit 1
# 	;;
# esac

# ARG=""
# $NAME "$@"

# # Generate N unique random numbers between MIN and MAX
# N=100           # Number of random numbers you want
# MIN=-100        # Minimum value
# MAX=100         # Maximum value

# # Generate and store in ARG
# ARG=$(shuf -i $MIN-$MAX -n $N)
# ARG=$(seq $MIN $MAX | shuf | head -n 5 | paste -sd' ' -)
# paste: joins lines
# -s: serial mode (one line)
# -d' ': delimiter is a space
