#ifndef SON8_MAIN_HXX
#define SON8_MAIN_HXX

#include <son8/exit.hxx>

namespace son8 {
    namespace privates {
        class ArgsStorage_;
    } // namespace son8::privates

    class Args final {
        friend class privates::ArgsStorage_;
        struct Span_ final {
            using element_type = char *;
            using iterator = element_type const *;
            Span_(int size, element_type *data) noexcept : size_{ size }, data_{ data } { }
            int size() const noexcept { return size_; }
            iterator begin() const noexcept { return data_;}
            iterator end() const noexcept { return data_ + size_; }
        private:
            int size_;
            element_type *data_;
        }; // struct Span_
        class Impl_;
        Impl_ *implPtr_;
        Args(int args, char *argv[]) noexcept;
    public:
        ~Args();
        using iterator = Span_::iterator;

        Args() = delete;
        Args(Args &&) = delete;
        Args(Args const &) = delete;
        Args &operator=(Args &&) = delete;
        Args &operator=(Args const &) = delete;

        [[nodiscard]] iterator begin() const noexcept;
        [[nodiscard]] iterator end() const noexcept;
        [[nodiscard]] int size() const noexcept;
    }; // class Args

    void main(Args const &args);
} // namespace son8

#endif//SON8_MAIN_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
