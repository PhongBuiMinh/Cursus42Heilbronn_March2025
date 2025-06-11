#!/bin/bash

./server && ARG=$(./server) && ./client $ARG avc
