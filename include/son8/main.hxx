#ifndef SON8_MAIN_HXX
#define SON8_MAIN_HXX

#include <son8/exit.hxx>

namespace son8 {

    class Arguments final {
        class Impl_;
        Impl_ *implPtr_;
        Arguments( int args, char *argv[] ) noexcept;
    public:
        ~Arguments( );
        class Storage;
        using Arg = char const *;
        using Iterator = Arg const *;
        Arguments( ) = delete;
        Arguments( Arguments && ) = delete;
        Arguments( Arguments const & ) = delete;
        Arguments &operator=( Arguments && ) = delete;
        Arguments &operator=( Arguments const & ) = delete;

        [[nodiscard]] Iterator begin( ) const noexcept;
        [[nodiscard]] Iterator end( ) const noexcept;
        [[nodiscard]] Iterator cbegin( ) const noexcept;
        [[nodiscard]] Iterator cend( ) const noexcept;
        [[nodiscard]] int size( ) const noexcept;
    }; // class Arguments

    using Args = Arguments const &;

    void main( Args args );
} // namespace son8

#endif//SON8_MAIN_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
