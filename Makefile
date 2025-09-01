FOO = $(shell date)
BAR := $(shell date)

all:
	echo "FOO is $(FOO)"
	echo "BAR is $(BAR)"
# BAR was evaluated once when Make read the file. (fix value)
# FOO was evaluated again when used — so the time changed. (dynamic value)

# UNAME_S := $(shell uname -s)
# $(info UNAME_S is $(UNAME_S))
