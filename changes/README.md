## CHANGES
> [keep a changelog](https://keepachangelog.com/en/1.1.0/) with [semantic versioning](https://semver.org/spec/v2.0.0.html)

### `0.1.1` - 2026-07-22

#### Added

array index operators for `Arguments`:
- unsigned index: undefined behavior
- signed index: throw out of range standard exception

### `v0.1.0` - 2026-07-06
> initial beta release

#### Changed

- `CMake`: library always static

### `v0.0.1` - 2026-05-06
> initial alpha release

#### Added

- Exit: class and exit value with success and failure constants
- Arguments (`Args`): `argc` and `argv` wrapper
- main: main function wrapper
