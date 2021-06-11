AMO Tools Suite  
---------------

AMO Tools Suite is a cross-platform collection of calculations and tools to support industrial equipment modeling.
See our hosted documentation for the latest release at [ornl-amo.github.io](https://ornl-amo.github.io/)

### Dependencies
#### C++
- make
- CMake (cmake-curses to use the ccmake gui)
- GCC 4.8.5 or later
- Doxygen (only for building documentation)

#### Node
- Node [https://nodejs.org/en/](https://nodejs.org/en/) v8, v9 or v10
- gyp: follow instructions for the OS at [https://github.com/nodejs/node-gyp](node-gyp)
  - depending on platform and instructions, it states the correct python version to install or installs it

### Building
- Edit the CMakeCache and enable desired build options via the ccmake tool: `ccmake .` and `make` to build
- If ccmake isn't available, use `cmake -D BUILD_TESTING:BOOL=ON -D BUILD_PACKAGE:BOOL=OFF --config Debug ./` and `cmake --build .` where config can be `Release`, `Debug`, `MinSizeRel` or `RelWithDebInfo`
- To build node modules: `npm install` or if already installed, `node-gyp rebuild` to rebuild the modules
    - Note: In order to build node modules, edit package.json and change gypfile entry value to true => "gypfile": true 
- To build WASM: use -D BUILD_WASM=ON flag in cmake options => `emcmake cmake -D BUILD_WASM=ON .` followed by `emmake make`
    - Note:
      - Emscripten compiler toolchain needs to be installed first from https://emscripten.org/docs/getting_started/index.html
      - If multiple compilers are present and default environment is not used, use -G "XXX Makefiles",
        example for windows => `emcmake cmake -G "MinGW Makefiles" -D BUILD_WASM=ON .`      

### Unit Tests
- To run the JavaScript unit tests for the node addons: `npm run test`
- To run the WASM unit tests use: `npm run test-wasm`
- To build C++ unit tests directly, ensure the `BUILD_TESTING` flag is set then: `cmake --build . --target amo_tools_suite_tests`
- On MacOS or Linux, the test executable can be found under the `bin` directory. On Windows, the executable can be found under either the `Debug` or `Release` directories, depending on CMake configuration

## Acceptance Tests
- To run the JavaScript acceptance tests (roundtrip testing of JavaScript bindings to calculations to output validation): `npm run at`

### Packaging
- Enable the `BUILD_PACKAGE` flag in the CMakeCache, then `cmake ./` then `make package`
- Or use this directly for Windows: `cmake -D BUILD_TESTING:BOOL=OFF ./` and `cmake --build . --config Release --target PACKAGE`
- To make package on Linux or Mac, run `ccmake.` and set BUILD_TESTING OFF, BUILD_PACKAGE ON, then configure and generate. Then `make package`.

### Documentation
- To generate documentation: `doxygen Doxyfile.in`
