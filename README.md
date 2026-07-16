# file-manager

File manager training project.

## Requirements

- CMake 3.14 or newer;
- a C++17 compiler.

On Windows, the repository scripts automatically download Boost 1.80 and build
the two required static libraries: Boost.DateTime and Boost.Test. You do not
need to install Boost or specify its location manually. The archive, sources,
and built libraries are cached under `library/` and reused by later builds.

On other platforms, Boost.DateTime and Boost.Test 1.75 or newer must be
available as system packages. The CI workflow installs only these components.

## Build

```console
cmake -S . -B build
cmake --build build --config Release --parallel
ctest --test-dir build -C Release --output-on-failure
```

During the first Windows configuration, the install script performs these
steps automatically:

1. Downloads the official Boost 1.80 7z archive with visible progress.
2. Verifies its SHA256 checksum.
3. Extracts it into `library/boost_1_80_0`.
4. Bootstraps Boost.Build.
5. Builds only Boost.DateTime and Boost.Test in Debug and Release variants.

Each completed step is cached. Reconfiguring or creating another build
directory does not repeat the download, extraction, bootstrap, or library
build.

The scripts can also be run manually for diagnostics:

```console
library\download-boost.1.80.0-library.bat
library\install-boost.1.80.0-library.bat
```

To use a separately installed Boost instead, disable the automatic scripts and
pass its root directory:

```console
cmake -S . -B build -DFILE_MANAGER_AUTO_INSTALL_BOOST=OFF -DBoost_ROOT=C:\path\to\boost
```

Disable tests with `-DBUILD_TESTING=OFF`.

## Contributing

Please read the contribution guidelines before starting work on a pull request.

1. One pull request per issue.
2. Name the branch after the issue title.
3. Use `main` as the base branch.
4. Include tests and documentation.
5. Keep the change in one commit.
6. Use `Closed #X` in the commit message, where `X` is the issue number.
7. Follow the coding style guide.
