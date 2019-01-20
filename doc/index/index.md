
# Common.

For using library just use `src` dir in your project. C code is ready for using.

Makefile is need to create test projects. If you want to create or update test project run `make` from root path. Run `make clean` do delete test projects.

# Structure of directories.

* `src` directory consists subdirectories with libraries. Commonly based on macros. One subdirectory is one project.

* `test` directory consists tests or examples for every project in library.

* `doc` directory consists documentation for projects.

* `Makefile` builds or rebuilds test projects, creating `_build` and `_run` directories and using `gcc` compiler. Attention! Makefile rebuilds only on change `*.c` files, not on change `*.h`  files.

* `_build` directory consists object files of `src` and `test` directories.

* `_run` directory consists of bin files of every example in test directory.

# Features of library projects.

In any projects of collection all definitions of macros, structure, function etc. start with `ZX_` or `zx_` and then the same set of chars. For example in test-project all macros starts with `ZX_TEST` and all functions and structures with `zx_test`. So, if such beginning of units already using in your project you can change zx-beginnig of definition in this library to avoid ambiguotios. Example for Linux:

    cd <LIBRARY_PATH>
    find . -name '*.c' -o -name '*.h' -type f -print0 | xargs -0 sed -i 's/\<ZX_/MY_BEGINNING/g'
    find . -name '*.c' -o -name '*.h' -type f -print0 | xargs -0 sed -i 's/\<zx_/my_beginning/g'

Where `<LIBRARY_PATH>` is path to library.