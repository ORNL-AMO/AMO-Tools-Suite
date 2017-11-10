AMO Tools Suite  <img src="https://img.shields.io/badge/license-MIT-blue.svg"> 
---------------

AMO Tools Suite is a cross-platform collection of calculations and tools to support industrial equipment modeling.

To generate documentation: `doxygen Doxygen.in` or see the hosted documentation for the latest Tools-Suite release at [ornl-amo.github.io](https://ornl-amo.github.io/)

To build node modules: `npm install` or if already installed, `node-gyp rebuild` to update modules.

To run tests for the node addon: `npm run test`

To edit the CMakeCache: `ccmake .` from root project directory, enable desired build options, then `make` to build.

To build C++ unit tests directly: `cmake --build . --target amo_tools_suite_tests` from root project directory.

To create C++ installer package: `ccmake .` from root project directory, then enable `BUILD_PACKAGE` flag, then `cmake ./` , then `make package`
