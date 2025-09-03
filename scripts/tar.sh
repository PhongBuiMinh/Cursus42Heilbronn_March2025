#!/bin/bash

PATH_TO_PROJECT=../
ARCHIVE_NAME=project

chmod +x tar.sh

echo -e "\nArchiving the project...\n"
if [ "$1" == "basic" ]; then
	tar -xf $ARCHIVE_MAME.tar $PATH_TO_PROJECT
elif [ "$1" == "compressed" ]; then
	tar -xzf $ARCHIVE_NAME.tar.gz $PATH_TO_PROJECT
else
	echo "Usage: $0 [basic / compressed]"
	exit 2
fi
