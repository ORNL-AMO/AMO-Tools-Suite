#!/bin/bash



if [ ["$TRAVIS_BRANCH" == "$PRODUCTION"] && [$"TRAVIS_OS_NAME" != "windows"] ]
then
    make package
    ls -a
elif [ ["$TRAVIS_BRANCH" == "$PRODUCTION"] && ["$TRAVIS_OS_NAME" == "windows"] ]
then
    cmake --build . --config Release --target PACKAGE
    ls -a Release/
fi
