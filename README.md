# MAINLAND
> C++17 Main Function Wrapper

## Usage

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

### Reminder

* main is void because otherwise it would crush when forget to return, so use exit class for return values

## [CONTRIBUTING](./CONTRIBUTING.md)
> Project Contribution Rules

## [LICENSE](./LICENSE) [Apache-2.0](./LICENSE.Apache-2.0.md) [NOTICE](./NOTICE)
> Project Copying Rules with attribution notice

###### each folder MAY contain README with additional materials
