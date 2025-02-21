#include <son8/main.hxx>

#include <atomic>
#include <cstdlib>
#include <new>

namespace son8 {
    // Args pImpl
    class Args::Impl_ final {
        friend class Args;
        struct Span_ final {
            using iterator = Args::iterator;
            Span_(int size, char **data) noexcept : size_{ size }, data_{ data } { }
            int size() const noexcept { return size_; }
            iterator begin() const noexcept { return data_;}
            iterator end() const noexcept { return data_ + size_; }
        private:
            int size_;
            char **data_;
        }; // struct Span_
        Span_ args_;
        Impl_(int argc, char *argv[]) noexcept : args_{ argc, argv } { }
    public:
        ~Impl_() = default;

        Impl_() = delete;
        Impl_(Impl_ &&) = delete;
        Impl_(Impl_ const &) = delete;
        Impl_ &operator=(Impl_ &&) = delete;
        Impl_ &operator=(Impl_ const &) = delete;

        auto begin() const noexcept { return args_.begin(); }
        auto end() const noexcept { return args_.end(); }
        auto size() const noexcept { return args_.size(); }
    }; // class Args::Impl_
    // Args Storage
    class Args::Storage final {
    public:
        alignas(Args::Impl_) char impl_storage[sizeof(Args::Impl_)];
        Args const &args(int argc, char *argv[]) const noexcept {
            static Args args_{ argc, argv };
            return args_;
        }
        static Storage &get() noexcept {
            static Storage storage_;
            return storage_;
        }
    }; // class ArgsStorage_
    // Args
    Args::Args(int argc, char *argv[]) noexcept
    : implPtr_{ new (Args::Storage::get().impl_storage) Impl_{ argc, argv } }
    { }
    Args::~Args() { implPtr_->~Impl_(); }
    Args::iterator Args::begin() const noexcept { return implPtr_->begin(); }
    Args::iterator Args::end() const noexcept { return implPtr_->end(); }
    Args::iterator Args::cbegin() const noexcept { return implPtr_->begin(); }
    Args::iterator Args::cend() const noexcept { return implPtr_->end(); }
    int Args::size() const noexcept { return implPtr_->size(); }
    // Exit
    namespace {
        std::atomic< int > exit_value{ EXIT_SUCCESS };
    }
    void Exit::operator=(int value) const noexcept {
        exit_value.store(value, std::memory_order_relaxed);
    }
    void Exit::operator()() const noexcept {
        std::exit(exit_value.load(std::memory_order_relaxed));
    }
    void Exit::operator()(int value) const noexcept {
        exit_value.store(value, std::memory_order_relaxed);
        std::exit(value);
    }
    int Exit::get() const noexcept {
        return exit_value.load(std::memory_order_relaxed);
    }
} // namespace son8

auto main(int argc, char *argv[]) -> int try {
    son8::Args const &args = son8::Args::Storage::get().args(argc, argv);
    son8::main(args);
    son8::exit();
} catch (...) {
    throw;
} // main() try

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
