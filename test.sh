#!/bin/env bash

set -euo pipefail

# must be >= 0
DATALEN_MIN=0
# must be <= 32767
DATALEN_MAX=1000

INPUT_FILE="input.bin"
OUTPUT_FILE="output.bin"

MY_PROGRAM="./main"
ORIG_PROGRAM="wine task/ReverseTestTask1.exe"

# how much run random test
RUNS_COUNT=10

die()
{
	echo $@ 1>&2
	exit 42
}

checksum()
{
	md5sum "$1" | cut -f1 -d" "
}

run_test()
{

local len=$((${DATALEN_MIN} + ${RANDOM} % ${DATALEN_MAX}))
head -c${len} </dev/random >"${INPUT_FILE}"

rm -f "${OUTPUT_FILE}"

${MY_PROGRAM}
local my=$(checksum "${OUTPUT_FILE}")

${ORIG_PROGRAM}
local orig=$(checksum "${OUTPUT_FILE}")

test "${my}" = "${orig}" || die "Oh no, this is wrong result!"

}

for _ in $(seq 1 "${RUNS_COUNT}"); do
	run_test
done
