#!/bin/bash

echo -e "Enter amount of random numbers"
./push_swap "$@"

MIN=-300
MAX=300

# ARG=""

case $1 in
  5)
	ARG=$(seq $MIN $MAX | shuf | head -n 5 | paste -sd' ' -)
	;;
  100)
	ARG=$(seq $MIN $MAX | shuf | head -n 100 | paste -sd' ' -)
	;;
  500)
	ARG=$(seq $MIN $MAX | shuf | head -n 500 | paste -sd' ' -)
	;;
esac

echo -e "\n======= Push_Swap Tester ======="
echo -e "Passing set of numbers: $ARG"
echo -e "Counting required operations"
./push_swap $ARG | wc -l
echo -e "Testing with checker program"
./push_swap $ARG | ./tests/checker_linux $ARG

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
