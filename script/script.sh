#! /bin/bash

DEFAULT="\e[0m"
BLACK="\e[1;30m"
RED="\e[1;31m"
GREEN="\e[1;32m"
YELLOW="\e[1;33m"
BLUE="\e[1;34m"
MAGENTA="\e[1;35m"
CYAN="\e[1;36m"
WHITE="\e[1;37m"

# echo -e "$RED This is red color\e[0m"
echo -e "${RED}This is red color$DEFAULT"

#! /bin/bash

cleanup_unix_like()
{
	echo "🚀 Starting Docker daemon on $1..."
	if [[ "$1" == "Darwin" ]]; then
		open -a Docker
	else
		systemctl start docker
	fi

	echo "🧼 Starting Docker cleanup..."
	CONTAINERS=$(docker ps -aq)
	if [ "$CONTAINERS" != "" ]; then
		echo "Removing containers..."
		docker rm -f $CONTAINERS # -a (all containers); -q (container IDs)
	else
		echo "No containers to remove."
	fi
	# docker container prune # remove stopped containers

	echo "Pruning images..."
	# docker image prune # remove unused images
	docker image prune -a --force

	echo "Pruning containers..."
	docker volume prune --force

	# docker system prune # remove s-containers, u-networks, d-images, b-cache
	# echo "Cleaning docker"
	# docker system prune --volumes --force # remove everything
	echo "✅ Docker cleanup complete."
}

cleanup_windows()
{
	echo "🚀 Starting Docker daemon..."
	powershell.exe -Command "Start-Process 'Docker Desktop'"
	# Start-Process "C:\Program Files\Docker\Docker\Docker Desktop.exe"

	echo "🧹 Cleaning up Docker..."
	# docker ps -q | xargs -r docker stop
	docker stop $(docker ps -q)

	# docker container prune -f
	docker rm $(docker ps -a -q)

	# docker image prune -a -f
	docker rmi $(docker images -q)

	# docker volume prune -f
	docker volume rm $(docker volume ls -q)

	# docker network prune -f
	docker network rm $(docker network ls -q)

	echo "✅ Docker cleanup complete for Windows."
}

echo "🔍 Detecting operating system..."
if command -v uname; then
	OS_TYPE="$(uname)"
else
	OS_TYPE="Windows"
fi

if [[ "$OS_TYPE" == "Linux" || "$OS_TYPE" == "Darwin" ]]; then
	cleanup_unix_like "$OS_TYPE"
elif [ "$OS_TYPE" == "Windows" ]; then
	cleanup_windows
else
	echo "❌ Unsupported OS: $OS_TYPE"
	exit 1
fi

# FROM ubuntu:latest
# RUN apt-get update && apt-get install -y libc6
# # Stage 1: Build with Alpine
# FROM alpine:latest AS builder

# RUN apk add --no-cache g++ valgrind
# WORKDIR /docker
# COPY . .

# # Stage 2: Runtime with Ubuntu
# FROM ubuntu:latest

# RUN apt-get update && apt-get install -y libc6

# COPY --from=builder /docker /docker

# all:
# 	@./docker_config.sh

# build_ai:
# 	@docker build -f env/ai -t ai .

# ai: build_ai
# 	@docker run --rm -it -v $(PATH_TO_PROJECT):$(WORKDIR) ai

# build_valgrind:
# 	@docker build -f env/valgrind -t valgrind .

# valgrind: build_valgrind
# 	@docker run --rm -it -v $(PATH_TO_PROJECT):$(WORKDIR) valgrind

# .PHONY: build_ai ai build_valgrind build_valgrind

# docker run -it -v $(PWD):/ valgrind:1.0 \
# /bin/sh -c "g++ get_next_line.c get_next_line_utils.c && \
# valgrind ./a.out"

🔍 So, will it rebuild the image?
Yes, the command will run every time, because Make doesn’t check if the Docker image already exists — it just executes the recipe.
But Docker itself may skip rebuilding layers if nothing has changed. So the build might be fast and mostly cached.

What does > /dev/null 2>&1 mean?
It’s a combination of two redirections:
> /dev/null
Redirects standard output (stdout) to /dev/null
/dev/null is a special file that discards anything written to it — like a black hole
So: anything the command would normally print gets thrown away
2>&1
Redirects standard error (stderr) (file descriptor 2) to wherever stdout (1) is currently going
Since stdout was just redirected to /dev/null, stderr goes there too
