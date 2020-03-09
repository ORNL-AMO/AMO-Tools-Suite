#!/bin/bash

set -ev

if [[ $TRAVIS_OS_NAME == "linux" ]]; then
  sudo apt-get update;
  sudo apt-get install -y make;
  sudo apt-get install -y doxygen;
fi
if [[ $TRAVIS_OS_NAME == "windows" ]]; then
  choco install make --yes;
  choco install doxygen.install --yes;
  choco install visualstudio2017buildtools --yes;
  choco install nsis --yes;
fi
if [[ $TRAVIS_OS_NAME == "osx" ]]; then
  bew update;
  brew install make;
  brew install doxygen;
fi

exit 0;
