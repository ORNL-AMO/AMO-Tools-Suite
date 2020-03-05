#!/bin/bash

if (("$TRAVIS_BRANCH" == "$PRODUCTION"))
then
  if (("$TRAVIS_OS_NAME" == "windows"))
  then
    cmake --build . --config Release --target PACKAGE
    ls -a
    ls -s Release/
  else
    make package
    ls -a
  fi
fi
