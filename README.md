# Particle Trajectory Reconstruction - Voronoi

## About this project

This is a new particle trajectory reconstruction approach, using Voronoi diagrams to assist clusterization of tracklets, aiming for performance and parallelism.

Code is designed for the LHCb, but can easily be extended for solving similar problems.

## Installation
Code is written on C++ and can be compiled with:
```shell
$ cgal_create_CMakeLists -c Core -s input.cpp
  cmake .
  make
```

The plots are written in python and run on Python >= 2.7.0

## Authors

Leonardo Teixeira Menezes <br />
Murilo Rangel <br />
Cedric Potterat <br />

## Contribute
Pull Requests welcome.

## License
MIT
