# MAINLAND

> Wrapper of main function and its arguments for C++17

## Usage

```cxx
#include <son8/main.hxx>
// son8::exit is return replacement class thats calls std::exit
void son8::main(Args const &args) {
    auto mainland = (args.end() - args.begin());
    if (bool r = mainland % 2; not r) exit = 8;
    if (args.size() > 2) exit(args.size());
    if (exit.get() == 8) exit();
} // return args|1 = 0, args|2 = 8, args|3+ = 3+
```

### Reminder

* main is void because otherwise it would crush when forget to return, so use exit class for return values

###### each folder MAY contain README with additional information about project