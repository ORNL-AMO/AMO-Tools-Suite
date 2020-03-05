#!/bin/bash

if (("$TRAVIS_BRANCH" == "$PRODUCTION"))
then
  if (("$TRAVIS_OS_NAME" != "windows"))
  then
    make package
    ls -a
  else
    cmake --build . --config Release --target PACKAGE
    ls -a Release/
  fi
fi
