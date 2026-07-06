# MAINLAND
> C++17 Main Function Wrapper

## Usage

### Example

```cxx
#include <son8/main.hxx>
// son8::exit is return replacement class thats calls std::exit
void son8::main( Args args ) {
    auto mainland = ( args.end( ) - args.begin( ) );
    if ( mainland % 2 == 0 ) exit = 8;
    if ( args.size( ) > 2 ) exit( args.size( ) );
    if ( exit.get( ) == 8 ) exit( );
} // return args|1 = 0, args|2 = 8, args|3+ = 3+
```

### Quick notes

- `Args`: here is const reference type, same as `Arguments const &`
- `args`: support `size( ) -> size_t, for range begin/end -> char const *const *`
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
