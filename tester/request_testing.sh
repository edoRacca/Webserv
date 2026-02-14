#!/bin/bash

source srcs_bash/run_test.sh

#SECTION - global variables
CMD="build/request"
TEST_DIR="tester/tests/request"
TEST_DIR_LOCAL="tests/request"
OUT_DIR_LOCAL="output"
all=("$TEST_DIR_LOCAL"/*.curl)
all=("${all[@]##*/}")
#SECTION - run
run()
{
	run_test "$counter" "$CMD" "$@"
	((counter++))
}

#SECTION - bash code

rm -f "$OUT_DIR_LOCAL/req_errors.txt"
rm -f "$OUT_DIR_LOCAL/req_temp.txt"
if [[ "$1" == "all" ]];then
	for request in "${all[@]}"; do
		run "$request"
	done
	exit
fi

#SECTION - list test

run simple.curl