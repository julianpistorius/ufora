#!/bin/bash

#   Copyright 2015 Ufora Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

function kill_all_running_procs {
    $WORKSPACE/ufora/scripts/killexp test.py > /dev/null
    $WORKSPACE/ufora/scripts/killexp FakeEC2Machine > /dev/null
    $WORKSPACE/ufora/scripts/killexp nodejs > /dev/null
    $WORKSPACE/ufora/scripts/killexp sharedStateMainline > /dev/null
}

function run_test {
    echo
    echo "********************************************************************************"
    echo "*    EXECUTING $TEST_NAME tests"
    echo "********************************************************************************"
    echo
    kill_all_running_procs

    TEST_LOG=$TEST_OUTPUT_DIR/$TEST_NAME.log

    if [ -z "$TEST_TIMEOUT" ]; then
        TEST_TIMEOUT=720
    fi

    python -u $WORKSPACE/test.py --baseport=$BASEPORT -timeout=$TEST_TIMEOUT $TEST_ARGS &> $TEST_LOG
    if [ $? -ne 0 ]; then
        cat $TEST_LOG
        exit 1
    fi
}

function stop_tests_and_exit {
    echo
    echo "********************************************************************************"
    echo "*    COLLECTING NOSE RESULTS"
    echo "********************************************************************************"
    echo

    find $WORKSPACE/* -name 'nose*log' | xargs -I {} mv -v '{}' $TEST_OUTPUT_DIR/

    echo
    echo "********************************************************************************"
    echo "*    PACKAGING ARTIFACTS"
    echo "********************************************************************************"
    echo


    find | grep 'core\.[0-9]\+$' | xargs -I{} mv -v '{}' $ARTIFACT_DIR/

    tar czf $TEST_OUTPUT_DIR/artifacts.tar.gz $ARTIFACT_DIR/
}

if [ -z $BASEPORT ]; then
    export BASEPORT=30000
fi
export PYTHONPATH=$WORKSPACE

cd $WORKSPACE

if [ -z $NESTED_TESTS_GUARD ]; then
    if [ -z $TEST_OUTPUT_DIR ]; then
        TEST_OUTPUT_DIR=$WORKSPACE
    fi

    export ARTIFACT_DIR=$TEST_OUTPUT_DIR/artifacts
    export ROOT_DATA_DIR=$ARTIFACT_DIR

    echo "ROOT_DATA_DIR: $ROOT_DATA_DIR"

    mkdir $ARTIFACT_DIR

    pip install -e $WORKSPACE/packages/python

    # Necessary in order to access S3 keys with dots ('.') in their name
    cat > ~/.boto << EOM
[s3]
calling_format = boto.s3.connection.OrdinaryCallingFormat
EOM

    trap stop_tests_and_exit SIGTERM SIGINT SIGHUP SIGPIPE EXIT

    export NESTED_TESTS_GUARD=1
fi
