#include <son8/main.hxx>
// std
#include <atomic> // atomic, memory_order_relaxed
#include <cstddef> // byte
#include <cstdlib> // exit, EXIT_(FAILURE|SUCCESS)
#include <new> // [placement new]

namespace son8 {
    // Arguments pImpl
    class Arguments::Impl_ final {
        friend class Arguments;
        struct Span_ final {
            using Iterator = Arguments::Iterator;
            Span_( int size, char **data ) noexcept : size_{ size }, data_{ data } { }
            int size( ) const noexcept { return size_; }
            Iterator begin( ) const noexcept { return data_;}
            Iterator end( ) const noexcept { return data_ + size_; }
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

        auto begin( ) const noexcept { return args_.begin( ); }
        auto end( ) const noexcept { return args_.end( ); }
        auto size( ) const noexcept { return args_.size( ); }
    }; // class Arguments::Impl_
    // Arguments Storage
    class Arguments::Storage final {
    public:
        alignas( Arguments::Impl_ ) std::byte impl_storage[sizeof( Arguments::Impl_ )];
        Arguments const &args( int argc, char *argv[] ) const noexcept {
            static Arguments args_{ argc, argv };
            return args_;
        }
        static Storage &get( ) noexcept {
            static Storage storage_;
            return storage_;
        }
    }; // class ArgumentsStorage_
    // Arguments
    Arguments::Arguments( int argc, char *argv[] ) noexcept
    : implPtr_{ new (Arguments::Storage::get( ).impl_storage ) Impl_{ argc, argv } }
    { }
    Arguments::~Arguments( ) { implPtr_->~Impl_( ); }
    Arguments::Iterator Arguments::begin( ) const noexcept { return implPtr_->begin( ); }
    Arguments::Iterator Arguments::end( ) const noexcept { return implPtr_->end( ); }
    Arguments::Iterator Arguments::cbegin( ) const noexcept { return implPtr_->begin( ); }
    Arguments::Iterator Arguments::cend( ) const noexcept { return implPtr_->end( ); }
    int Arguments::size( ) const noexcept { return implPtr_->size( ); }
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
        exit = Exit::Failure;
    }
    void Exit::Edit::success( ) noexcept {
        exit = Exit::Success;
    }


} // namespace son8

auto main( int argc, char *argv[] ) -> int try {
    son8::Arguments const &args = son8::Arguments::Storage::get( ).args( argc, argv );
    son8::main( args );
    son8::exit( );
} catch ( ... ) {
    throw;
} // main() try

// Apache License 2.0
// NO WARRANTY OF ANY KIND see <http://www.apache.org/licenses/LICENSE-2.0>
// SPDX-License-Identifier: Apache-2.0
// lib: `mainland` C++17 Main Function Wrapper
// Ⓒ Copyright (c) 2025-2026 Oleg'Ease'Kharchuk ᦒ
