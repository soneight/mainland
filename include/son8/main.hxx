#ifndef SON8_MAIN_HXX
#define SON8_MAIN_HXX

#include <son8/exit.hxx>

namespace son8 {

    class Args final {
        class Impl_;
        Impl_ *implPtr_;
        Args( int args, char *argv[] ) noexcept;
    public:
        ~Args( );
        class Storage;
        using Arg = char const *;
        using Iterator = Arg const *;
        Args( ) = delete;
        Args( Args && ) = delete;
        Args( Args const & ) = delete;
        Args &operator=( Args && ) = delete;
        Args &operator=( Args const & ) = delete;

        [[nodiscard]] Iterator begin( ) const noexcept;
        [[nodiscard]] Iterator end( ) const noexcept;
        [[nodiscard]] Iterator cbegin( ) const noexcept;
        [[nodiscard]] Iterator cend( ) const noexcept;
        [[nodiscard]] int size( ) const noexcept;
    }; // class Args

    void main( Args const &args );
} // namespace son8

#endif//SON8_MAIN_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
