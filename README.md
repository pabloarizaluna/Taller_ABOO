# Taller_ABOO
## Building Taller_ABOO

1. Create a temporary directory, which we denote as <cmake_build_dir>, where you want to put the generated Makefiles, project files as well the object files and output binaries and enter there.

For example

```
mkdir build
cd build
```

2. Run cmake

```
cmake ..
```

3. Build. From build directory execute make.

For example

```
make -j3
```

## Running Taller_ABOO

1. Run my_fancy_executable to generate a .csv file from a .txt file

```
./my_fancy_executable input_file output_file
```

2. Now run opt_bin_tree with a .csv file
```
./opt_bin_tree input_file time_to_find(seconds)
```
