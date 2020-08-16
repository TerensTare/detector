#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#ifdef __APPLE__
#include <TargetConditionals.h> // needed for detecting if on mac or on ios
#endif

#if __cplusplus >= 201703L
#define DETECT_INLINE inline
#else
#define DETECT_INLINE
#endif

namespace detect
{
    namespace detail
    {
        struct tag_type_t
        {
            tag_type_t() = delete;
            ~tag_type_t() = delete;

            tag_type_t(tag_type_t const &) = delete;
            tag_type_t &operator=(tag_type_t const &) = delete;

            tag_type_t(tag_type_t &&) = delete;
            tag_type_t &operator=(tag_type_t &&) = delete;
        };
    } // namespace detail

    struct windows_t final : detail::tag_type_t
    {
    };

    struct linux_t final : detail::tag_type_t
    {
    };

    struct macos_t final : detail::tag_type_t
    {
    };

    struct ios_t final : detail::tag_type_t
    {
    };

    struct android_t final : detail::tag_type_t
    {
    };

    struct unix_t final : detail::tag_type_t
    {
    };


    template <typename O>
    struct is_os;

    template <>
    struct is_os<windows_t>
    {
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64)
        DETECT_INLINE static constexpr bool value{true};
#else
        DETECT_INLINE static constexpr bool value{false};
#endif
    };

    template <>
    struct is_os<linux_t>
    {
#if defined(__linux__) && !defined(__android__)
        DETECT_INLINE static constexpr bool value{true};
#else
        DETECT_INLINE static constexpr bool value{false};
#endif
    };

    template <>
    struct is_os<macos_t>
    {
#ifdef TARGET_OS_MAC
        DETECT_INLINE static constexpr bool value{true};
#else
        DETECT_INLINE static constexpr bool value{false};
#endif
    };

    template <>
    struct is_os<ios_t>
    {
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
        DETECT_INLINE static constexpr bool value{true};
#else
        DETECT_INLINE static constexpr bool value{false};
#endif
    };

    template <>
    struct is_os<android_t>
    {
#ifdef __android__
        DETECT_INLINE static constexpr bool value{true};
#else
        DETECT_INLINE static constexpr bool value{false};
#endif
    };

    template <>
    struct is_os<unix_t>
    {
#if !defined(__linux__) && defined(__unix__)
        DETECT_INLINE static constexpr bool value{true};
#else
        DETECT_INLINE static constexpr bool value{false};
#endif
    };

    template <typename O>
    DETECT_INLINE static constexpr bool is_os_v{is_os<O>::value};

    DETECT_INLINE static constexpr bool is_windows_v{is_os<windows_t>::value};
    DETECT_INLINE static constexpr bool is_linux_v{is_os<linux_t>::value};
    DETECT_INLINE static constexpr bool is_macos_v{is_os<macos_t>::value};
    DETECT_INLINE static constexpr bool is_ios_v{is_os<ios_t>::value};
    DETECT_INLINE static constexpr bool is_android_v{is_os<android_t>::value};
    DETECT_INLINE static constexpr bool is_unix_v{is_os<unix_t>::value};

    struct gcc_t final : detail::tag_type_t
    {
    };

    struct clang_t final : detail::tag_type_t
    {
    };

    struct msvc_t final : detail::tag_type_t
    {
    };

    template <typename C>
    struct is_compiler;

    template <>
    struct is_compiler<gcc_t>
    {
#ifdef __GNUC__
        DETECT_INLINE static constexpr bool value{true};
#else
        DETECT_INLINE static constexpr bool value{false};
#endif
    };

    template <>
    struct is_compiler<clang_t>
    {
#ifdef __clang__
        DETECT_INLINE static constexpr bool value{true};
#else
        DETECT_INLINE static constexpr bool value{false};
#endif
    };

    template <>
    struct is_compiler<msvc_t>
    {
#ifdef _MSC_VER
        DETECT_INLINE static constexpr bool value{true};
#else
        DETECT_INLINE static constexpr bool value{false};
#endif
    };

    template <typename C>
    DETECT_INLINE static constexpr bool is_compiler_v{is_compiler<C>::value};

    DETECT_INLINE static constexpr bool is_gcc_v{is_compiler<gcc_t>::value};
    DETECT_INLINE static constexpr bool is_clang_v{is_compiler<clang_t>::value};
    DETECT_INLINE static constexpr bool is_msvc_v{is_compiler<msvc_t>::value};
} // namespace detect

#endif // !DETECTOR_HPP
