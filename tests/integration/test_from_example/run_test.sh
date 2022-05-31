#!/usr/bin/env bash

DIR=`dirname $0`
TEST_EXECUTABLE="$DIR/test_from_example"

if [ ! -f "$TEST_EXECUTABLE" ]; then
    echo "Can't find executable file $TEST_EXECUTABLE"
    exit 1
fi

echo 'Running test from example'
OUTPUT=`$TEST_EXECUTABLE 2>&1`

EXPECTED_OUTPUT='solution: -3, 2, -1'

if [ "$OUTPUT" == "$EXPECTED_OUTPUT" ]; then
    echo Test passed
    exit 0
fi

echo -e "Expected: $EXPECTED_OUTPUT"
echo -e "Got: $OUTPUT"
echo "Test failed"
exit 1
