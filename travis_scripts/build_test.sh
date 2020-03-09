#!/bin/bash

set -ev

cmake -D BUILD_TESTING:BOOL=ON -D BUILD_PACKAGE:BOOL=$PACKAGE ./
cmake --build . --config Release

if [[ $TRAVIS_OS_NAME == "windows" ]]; then
  ./Release/amo_tools_suite_tests;
else
  ./bin/amo_tools_suite_tests;
fi

npm run test
npm run at

if [[ $TRAVIS_OS_NAME == "windows" ]]; then
  echo "Skipping Doxygen";
else
  doxygen Doxyfile.in;
fi

if [[ $TRAVIS_BRANCH == $PRODUCTION ]]; then
  if [[ $TRAVIS_OS_NAME == 'windows' ]]; then
    travis_retry cmake --build . --config Release --target PACKAGE;
  else
    make package;
  fi
else
  echo "."
fi


exit 0;
