AMO Tools Suite  
---------------

AMO Tools Suite is a cross-platform collection of calculations and tools to support industrial equipment modeling.
See our hosted documentation for the latest release at [ornl-amo.github.io](https://ornl-amo.github.io/)

### Dependencies
#### C++
- make
- CMake (cmake-curses to use the ccmake gui)
- GCC 4.8.5 or later
  - Windows: MinGW or Cygwin or Visual Studio Build Tools or with other C++ compiler
- Doxygen (only for building documentation)

#### Web Assembly Compilation SDK
- Emscripten (emsdk) - Follow instructions for install https://emscripten.org/docs/getting_started/downloads.html

#### Node
- Node LTS [https://nodejs.org/en/](https://nodejs.org/en/) 

### Building
- `cd` into the emsdk directory: 
    - run `emsdk install latest` followed by `emsdk activate latest`
    - Activate PATH and other environment variables by running `source emsdk_env.sh` or on Windows run `emsdk_env.bat`
- `cd` into AMO-Tools-Suite directory:  
    - create directory `buildwasm` and cd into it 
    - run `'emcmake cmake -DBUILD_WASM=ON ..'` 
        -   Note: If multiple compilers are present and default environment is not used, use -G "XXX Makefiles",
        example for windows using MinGW => `emcmake cmake -D BUILD_WASM=ON .. -G "MinGW Makefiles"`  
    - run `emmake make`

### Unit Tests
- To run the WASM unit tests:
  - Install node_modules dependencies: `cd` into AMO-Tools-Suite directory and  
    run `npm install` followed by `npm run test-wasm`
- To build C++ unit tests, ensure the `BUILD_TESTING` flag is set (which is default) then: 
  - create directory `buildcpp` and cd into it
  - run `'cmake ..'`  
    -   Note: If multiple compilers are present and default environment is not used, use -G "XXX Makefiles",
    example for windows using MinGW => `cmake .. -G "MinGW Makefiles"`
  - run `'cmake --build .'`
  - execute `cpp_tests.exe`
- On MacOS or Linux, the test executable can be found under the `bin` directory. On Windows, the executable can be found under either the `Debug` or `Release` directories, depending on CMake configuration

### Packaging
- Enable the `BUILD_PACKAGE` flag in the CMakeCache, then `cmake ./` then `make package`
- Or use this directly for Windows: `cmake -D BUILD_TESTING:BOOL=OFF ./` and `cmake --build . --config Release --target PACKAGE`
- To make package on Linux or Mac, run `ccmake.` and set BUILD_TESTING OFF, BUILD_PACKAGE ON, then configure and generate. Then `make package`.

### Documentation
- To generate documentation: `doxygen Doxyfile`

### Dockerizing 
To make it easy for developers local building and testing, it is dockerized. To run it in docker follow this steps.
- Download the repository
- Open command line tool, change directory to the repository run `docker-compose up -d`
- To stop the running container run `docker-compose down`
- Running Unit Tests
  - WASM: in a browser, launch [http://localhost:3000/](http://localhost:3000/)
  - C++: run `docker exec -it amo-tools-suite-build /bin/bash` and run the executable `/home/AMO-Tools-Suite/build-cpp/bin/cpp_tests`
    - Note: 
      - Every time the container is started it will rebuild the application, to check status run `docker-compose logs --tail 5` 
      - **_This is not a tutorial for docker, assumption is made the user is knowledgeable.**_
