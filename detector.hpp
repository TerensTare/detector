#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#ifdef __APPLE__
#include <TargetConditionals.h> // needed for detecting if on mac or on ios
#endif

#if (defined(_M_AMD64) || defined(_M_X64) || defined(__amd64)) && !defined(__x86_64__)
#define DETECTED_X86_64
#endif

// MSVC doesn't correctly report __cplusplus unless you pass /Zc:__cplusplus
#ifdef _MSVC_LANG
#define DETECTED_CXX _MSVC_LANG
#else
#define DETECTED_CXX __cplusplus
#endif

#if DETECTED_CXX >= 201703L
#define DETECT_INLINE inline
#else
#define DETECT_INLINE
#endif

namespace detect
{
    //////////////////////
    // os-related stuff //
    //////////////////////

    struct windows_t;
    struct linux_t;
    struct macos_t;
    struct ios_t;
    struct android_t;
    struct unix_t;

    template <typename O>
    static constexpr bool is_os_v = false;

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64)
    template <>
    DETECT_INLINE constexpr bool is_os_v<windows_t> = true;
#endif

#if defined(__linux__) && !defined(__android__)
    template <>
    DETECT_INLINE constexpr bool is_os_v<linux_t> = true;
#endif

#ifdef TARGET_OS_MAC
    template <>
    DETECT_INLINE constexpr bool is_os_v<macos_t> = true;
#endif

#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
    template <>
    DETECT_INLINE constexpr bool is_os_v<ios_t> = true;
#endif

#ifdef __android__
    template <>
    DETECT_INLINE constexpr bool is_os_v<android_t> = true;
#endif

#if !defined(__linux__) && defined(__unix__)
    template <>
    DETECT_INLINE constexpr bool is_os_v<linux_t> = true;
#endif

    static constexpr bool is_windows_v = is_os_v<windows_t>;
    static constexpr bool is_linux_v = is_os_v<linux_t>;
    static constexpr bool is_macos_v = is_os_v<macos_t>;
    static constexpr bool is_ios_v = is_os_v<ios_t>;
    static constexpr bool is_android_v = is_os_v<android_t>;
    static constexpr bool is_unix_v = is_os_v<unix_t>;

    template <typename O>
    struct is_os
    {
        static constexpr bool value = is_os_v<O>;
    };

    ////////////////////////////
    // compiler-related stuff //
    ////////////////////////////

    struct gcc_t;
    struct clang_t;
    struct msvc_t;
    struct mingw_t;

    template <typename C>
    static constexpr bool is_compiler_v = false;

#if defined(__GNUC__) && !defined(__clang__)
    template <>
    DETECT_INLINE constexpr bool is_compiler_v<gcc_t> = true;
#endif

#ifdef __clang__
    template <>
    DETECT_INLINE constexpr bool is_compiler_v<clang_t> = true;
#endif

#if defined(_MSC_VER) && !defined(__clang__)
    template <>
    DETECT_INLINE constexpr bool is_compiler_v<msvc_t> = true;
#endif

#if defined(__MINGW32__) || !defined(__MINGW64__)
    template <>
    DETECT_INLINE constexpr bool is_compiler_v<mingw_t> = true;
#endif

    static constexpr bool is_gcc_v = is_compiler_v<gcc_t>;
    static constexpr bool is_clang_v = is_compiler_v<clang_t>;
    static constexpr bool is_msvc_v = is_compiler_v<msvc_t>;
    static constexpr bool is_mingw_v = is_compiler_v<mingw_t>;

    template <typename C>
    struct is_compiler
    {
        static constexpr bool value = is_compiler_v<C>;
    };

    ////////////////////////////////
    // C++ standard-related stuff //
    ////////////////////////////////

    struct cxx_11;
    struct cxx_14;
    struct cxx_17;
    struct cxx_20;
    struct cxx_23;

    template <typename T>
    static constexpr bool is_std_v = false;

    template <>
    DETECT_INLINE constexpr bool is_std_v<cxx_11> = DETECTED_CXX == 201103L;

    template <>
    DETECT_INLINE constexpr bool is_std_v<cxx_14> = DETECTED_CXX == 201402L;

    template <>
    DETECT_INLINE constexpr bool is_std_v<cxx_17> = DETECTED_CXX == 201703L;

    template <>
    DETECT_INLINE constexpr bool is_std_v<cxx_20> = DETECTED_CXX == 202002L;

    template <>
    DETECT_INLINE constexpr bool is_std_v<cxx_23> = DETECTED_CXX == 202302L;

    static constexpr bool is_cxx_11 = is_std_v<cxx_11>;
    static constexpr bool is_cxx_14 = is_std_v<cxx_14>;
    static constexpr bool is_cxx_17 = is_std_v<cxx_17>;
    static constexpr bool is_cxx_20 = is_std_v<cxx_20>;
    static constexpr bool is_cxx_23 = is_std_v<cxx_23>;

    template <typename S>
    struct is_std
    {
        static constexpr bool value = is_std_v<S>;
    };

    /////////////////////////////////
    // debug/release related stuff //
    /////////////////////////////////

    struct debug_t;
    struct release_t;

    template <typename B>
    static constexpr bool is_build_v = false;

#if defined(_DEBUG) || defined(DEBUG)
    template <>
    DETECT_INLINE constexpr bool is_build_v<debug_t> = true;
#endif

#if defined(NDEBUG) || !(defined(DEBUG) && defined(_DEBUG))
    template <>
    DETECT_INLINE constexpr bool is_build_v<release_t> = true;
#endif

    static constexpr bool is_debug_v = is_build_v<debug_t>;
    static constexpr bool is_release_v = is_build_v<release_t>;

    template <typename B>
    struct is_build
    {
        static constexpr bool value = is_build_v<B>;
    };

    ///////////////////////
    // simd instructions //
    ///////////////////////

    struct x86sse_t;
    struct x86sse2_t;
    struct sse_t;
    struct sse2_t;
    struct sse3_t;
    struct ssse3_t;
    struct sse4_1_t;
    struct sse4_2_t;
    struct avx_t;
    struct avx2_t;

    template <typename S>
    static constexpr bool is_simd_v = false;

#if defined(_M_IX86_FP) && (_M_IX86_FP == 1)
    template <>
    DETECT_INLINE constexpr bool is_simd_v<x86sse_t> = true;
#endif

#if defined(_M_IX86_FP) && (_M_IX86_FP == 2)
    template <>
    DETECT_INLINE constexpr bool is_simd_v<x86sse2_t> = true;
#endif

#ifdef __SSE__
    template <>
    DETECT_INLINE constexpr bool is_simd_v<sse_t> = true;
#endif

#if defined(__SSE2__) || defined(__x86_x64__) || defined(DETECTED_X86_64)
    template <>
    DETECT_INLINE constexpr bool is_simd_v<sse2_t> = true;
#endif

#ifdef __SSE3__
    template <>
    DETECT_INLINE constexpr bool is_simd_v<sse3_t> = true;
#endif

#ifdef __SSSE3__
    template <>
    DETECT_INLINE constexpr bool is_simd_v<ssse3_t> = true;
#endif

#ifdef __SSE4_1__
    template <>
    DETECT_INLINE constexpr bool is_simd_v<sse4_1_t> = true;
#endif

#ifdef __SSE4_2__
    template <>
    DETECT_INLINE constexpr bool is_simd_v<sse4_2_t> = true;
#endif

#ifdef __AVX__
    template <>
    DETECT_INLINE constexpr bool is_simd_v<avx_t> = true;
#endif

#ifdef __AVX2__
    template <>
    DETECT_INLINE constexpr bool is_simd_v<avx2_t> = true;
#endif

    static constexpr bool is_x86_sse_v = is_simd_v<x86sse_t>;
    static constexpr bool is_x86_sse2_v = is_simd_v<x86sse2_t>;
    static constexpr bool is_sse_v = is_simd_v<sse_t>;
    static constexpr bool is_sse2_v = is_simd_v<sse2_t>;
    static constexpr bool is_sse3_v = is_simd_v<sse3_t>;
    static constexpr bool is_ssse3_v = is_simd_v<ssse3_t>;
    static constexpr bool is_sse4_1_v = is_simd_v<sse4_1_t>;
    static constexpr bool is_sse4_2_v = is_simd_v<sse4_2_t>;
    static constexpr bool is_avx_v = is_simd_v<avx_t>;
    static constexpr bool is_avx2_v = is_simd_v<avx2_t>;

    template <typename S>
    struct is_simd
    {
        static constexpr bool value = is_simd_v<S>;
    };
} // namespace detect

#ifdef DETECTED_X86_64
#undef DETECTED_X86_64
#endif

#undef DETECTED_CXX

#endif // !DETECTOR_HPP
