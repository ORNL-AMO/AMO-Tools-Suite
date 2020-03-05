#!/bin/bash

if (("$TRAVIS_BRANCH" == "$PRODUCTION"))
then
  if (("$TRAVIS_OS_NAME" == "windows"))
  then
    cmake --build . --config Release --target PACKAGE
  else
    make package
  fi
fi
