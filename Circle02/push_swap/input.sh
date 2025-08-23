#!/bin/bash

ARG="4 67 3 87 23"
./push_swap $ARG | wc -l | ./tests/checker_Mac $ARG

# ./push_swap "$@"
# ARG="1 2"
# ./push_swap $ARG

# STR="AAA BBB CCC"
# ./push_swap "$STR"

# case $1 in
#   1)
# 	args="3 2 1"
# 	;;
#   2)
# 	args="3 1 2"
# 	;;
#   3)
# 	args="2 3 1"
# 	;;
#   4)
# 	args="1 3 2"
# 	;;
#   5)
# 	args="1 2 3"
# 	;;
#   6)
# 	args="2 1 3"
# 	;;

#   2)
# 	args="2 1"
# 	;;
#   3)
# 	args="3 2 5"
# 	;;
#   4)
# 	args="3 2 5 6"
# 	;;
#   5)
# 	args="1 5 2 4 3"
# 	;;
#   6.0)
# 	args="5 3 4 2 1"
# 	;;
#   6.1)
# 	args="3 5 4 2 1"
# 	;;
#   6.2)
# 	args="3 5 0 2 1"
# 	;;
#   10)
# 	args="1 5 -4 6 12 53 0 2 4 3"
# 	;;
# esac

# echo -e "\n======= Push_Swap Tester ======="
# echo -e "Passing set of numbers: $args"
# echo -e "\n======= Push_Swap output ======="
# ./push_swap $args # | ./checker $args

# #!/bin/bash

# # Simple Test Script for push_swap

# echo "=== Push_Swap Tester ==="

# # Test cases
# case $1 in
#   1)
#     args="1 2"
#     ;;
#   2)
#     args="3 2 5"
#     ;;
#   3)
#     args="1 5 2 4 3"
#     ;;
#   4)
#     args=$(shuf -i 1-100 | tr '\n' ' ')
#     ;;
#   *)
#     echo "Usage: $0 [test_number]"
#     echo "Test numbers:"
#     echo "1) 2 arguments (1 2)"
#     echo "2) 3 arguments (3 2 5)"
#     echo "3) 5 arguments (1 5 2 4 3)"
#     echo "4) 100 random arguments"
#     exit 1
#     ;;
# esac

# echo "Testing with: $args"
# echo "=== push_swap output ==="
# ./push_swap $args
# echo "=== checker result ==="
# ./push_swap $args | ./checker $args
