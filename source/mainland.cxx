#include <son8/main.hxx>
// std
#include <atomic> // `atomic, memory_order_relaxed`
#include <cstddef> // `byte`
#include <cstdlib> // `exit, EXIT_(FAILURE|SUCCESS)`
#include <new> // `[placement new]`
#include <stdexcept> // `out_of_range`

namespace son8 {
    // Arguments `pImpl`
    class Arguments::Impl_ final {
        friend class Arguments;
        struct Span_ final {
            Span_( int size, char **data ) noexcept : size_{ size }, data_{ data } { }
            [[nodiscard]] auto size( ) const noexcept -> int { return size_; }
            [[nodiscard]] auto begin( ) const noexcept -> Iterator { return data_;}
            [[nodiscard]] auto end( ) const noexcept -> Iterator { return data_ + size_; }
        private:
            int size_;
            char **data_;
        }; // struct Span_
        Span_ args_;
        Impl_( int argc, char *argv[] ) noexcept : args_{ argc, argv } { }
    public:
        ~Impl_( ) = default;

        Impl_( ) = delete;
        Impl_( Impl_ && ) = delete;
        Impl_( Impl_ const & ) = delete;
        Impl_ &operator=( Impl_ && ) = delete;
        Impl_ &operator=( Impl_ const & ) = delete;

        [[nodiscard]] auto begin( ) const noexcept { return args_.begin( ); }
        [[nodiscard]] auto end( ) const noexcept { return args_.end( ); }
        [[nodiscard]] auto size( ) const noexcept { return args_.size( ); }
    }; // class `Arguments::Impl_`
    // Arguments Storage
    struct Arguments::Storage final {
        alignas( Impl_ ) std::byte impl_storage[sizeof( Impl_ )];
        Arguments const &args( int argc, char *argv[] ) noexcept {
            static Arguments args_{ argc, argv };
            return args_;
        }
        static auto get( ) noexcept -> Storage & {
            static Storage storage_;
            return storage_;
        }
    }; // class `Arguments::Storage`
    // Arguments
    Arguments::Arguments( int argc, char *argv[] ) noexcept
    : implPtr_{ new ( Storage::get( ).impl_storage ) Impl_{ argc, argv }}
    { }
    Arguments::~Arguments( ) { implPtr_->~Impl_( ); }
    auto Arguments::begin( ) const noexcept  -> Iterator { return implPtr_->begin( ); }
    auto Arguments::end( ) const noexcept    -> Iterator { return implPtr_->end( ); }
    auto Arguments::cbegin( ) const noexcept -> Iterator { return implPtr_->begin( ); }
    auto Arguments::cend( ) const noexcept   -> Iterator { return implPtr_->end( ); }
    auto Arguments::size( ) const noexcept -> int { return implPtr_->size( ); }
    // array operators
    // -- safe(signed)
    auto Arguments::operator[]( signed idxSafe ) const -> Arg {
        if ( idxSafe < size( )) return *( begin( ) + idxSafe );
        throw std::out_of_range{ "son8::mainland: Arguments signed index safe array operator out of range access" };
    }
    // -- unsafe(unsigned)
    auto Arguments::operator[]( unsigned idx ) const noexcept -> Arg {
        return *( begin( ) + idx );
    }
    // Exit
    namespace {
        std::atomic< int > exit_value{ EXIT_SUCCESS };
    }

    int const Exit::Success = EXIT_SUCCESS;
    int const Exit::Failure = EXIT_FAILURE;

    void Exit::success( ) { exit( Success ); }
    void Exit::failure( ) { exit( Failure ); }

    void Exit::operator=( int value ) const noexcept {
        exit_value.store( value, std::memory_order_relaxed );
    }
    void Exit::operator()( ) const {
        std::exit( get( ) );
    }
    void Exit::operator()( int value ) const {
        exit_value.store( value, std::memory_order_relaxed );
        exit( );
    }
    int Exit::get( ) const noexcept {
        return exit_value.load( std::memory_order_relaxed );
    }
    // edit
    void Exit::Edit::failure( ) noexcept {
        exit = Failure;
    }
    void Exit::Edit::success( ) noexcept {
        exit = Success;
    }

} // namespace son8

auto main( int argc, char *argv[] ) -> int try {
    son8::Arguments const &args = son8::Arguments::Storage::get( ).args( argc, argv );
    son8::main( args );
    return son8::exit.get( );
} catch ( ... ) {
    throw;
} // main() try

// Apache License 2.0
// NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
// SPDX-License-Identifier: Apache-2.0
// lib: `mainland` C++17 Main Function Wrapper
// Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
