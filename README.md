# `MAINLAND`
> C++17 Main Function Wrapper

## Usage

### Install
> `CMake` install and find package would be supported only on release, so version `v1.0.0`

use `CMake` fetch functionality below

### Fetch

```cmake
if( NOT TARGET son8__mainland )
    include( FetchContent )
    message( STATUS "${APP}: FetchContent `soneight/mainland`" )
    fetchcontent_declare(
        son8__mainland
        GIT_REPOSITORY https://github.com/soneight/mainland.git
        GIT_TAG        8bba2163f5365d218a90343489e387ba655950c5 # v0.1.2
    )
    fetchcontent_makeavailable( son8__mainland )
endif( )
message( STATUS "${APP}: target `son8__mainland` found" )
```

### Example

```cxx
#include <son8/main.hxx>
// son8::exit is return replacement class that's calls std::exit
void son8::main( Args args ) {
    auto mainland = ( args.end( ) - args.begin( ));
    if ( mainland % 2 == 0 ) exit = 8;
    if ( args.size( ) > 2 ) exit( args.size( ));
    if ( exit.get( ) == 8 ) exit( );
} // return args|1 = 0, args|2 = 8, args|3+ = 3+
```

### Quick notes

- `Args`: here is const reference type, same as `Arguments const &`
- `args`: support
  - `size( ) -> int`: so typical `args[args.size( )]` would throw instead of segfault
  - for range `begin/end -> char const *const *`
  - `operator [signed integer]`: **`S`**`afe` bound checked array access, throws out of range standard exception
  - `operator [unsigned integer]`: **`U`**nsafe` array access, occasionally spawn standard demons from a caller nose
  - Arguments array access require signed int for safe access or unsigned one for unsafe access, other integer types are prohibited
- `Exit::Success / Exit::Failure`: `EXIT_SUCCESS / EXIT_FAILURE`
- `exit = [[ value ]] or Exit::Edit::[[ success( ) / failure( ) ]]`: updating exit value without calling exit
- `exit( ) or exit( [[ value ]] ) or Exit::[[ success( ) / failure( ) ]]`: emergency exit without clearing stack
- `exit.get( )`: get current exit value, by default equal to `Exit::Success`

### Reminder

* main is void because otherwise it would crush when forget to return, so use exit class for return values

## [CONTRIBUTING](./CONTRIBUTING.md)
> Project Contribution Rules

## [LICENSE](./LICENSE) [Apache-2.0](./LICENSE.Apache-2.0.md) [NOTICE](./NOTICE)
> Project Copying Rules with attribution notice

###### each folder MAY contain README with additional materials
###### END OF `MAINLAND`
