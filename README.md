## Run Instructions
I ran my code within a Docker container. All of the necessary configuration
is included within the Dockerfile. To build and run, do the following.

1. Build and enter Docker container:
```bash
docker build -t vast .
docker run -it -v "$(pwd):/app" vast /bin/bash
```

2. Run main binary
```bash
# Ensure you are in the build directory.
cd build

# Run cmake and make.
cmake ..
make

# Execute binary.
./main

# To run with flags
./main --numTrucks 7 --numStations 2
```

3. Run tests
```bash
ctest
```