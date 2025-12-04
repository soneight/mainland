#ifndef SON8_EXIT_HXX
#define SON8_EXIT_HXX

namespace son8 {
    class Exit final {
    public:
        Exit( ) noexcept = default;
        ~Exit( ) = default;
        Exit( Exit && ) = delete;
        Exit( Exit const & ) = delete;
        Exit &operator=( Exit && ) = delete;
        Exit &operator=( Exit const & ) = delete;
        void operator=( int value ) const noexcept;
        void operator()( ) const noexcept;
        void operator()( int value ) const noexcept;
        int get( ) const noexcept;
        // EXIT_SUCCESS and EXIT_FAILURE (no constexpr to avoid including stdlib header)
        static int Success;
        static int Failure;
        static void success( ) noexcept;
        static void failure( ) noexcept;
    }; // class Exit

    inline Exit exit;
} // namespace son8

#endif//SON8_EXIT_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
