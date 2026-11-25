/*
 * Automatically generated C config: don't edit
 * Busybox version: 1.28.0
 */
#define AUTOCONF_TIMESTAMP "2021-08-12 23:33:06 CDT"

#ifdef MAKE_SUID
# define IF_HAVE_DOT_CONFIG(...) __VA_ARGS__ "CONFIG_HAVE_DOT_CONFIG"
#else
# define IF_HAVE_DOT_CONFIG(...) __VA_ARGS__
#endif
#define IF_NOT_HAVE_DOT_CONFIG(...)

/*
 * Settings
 */
#ifdef MAKE_SUID
# define IF_DESKTOP(...) __VA_ARGS__ "CONFIG_DESKTOP"
#else
# define IF_DESKTOP(...) __VA_ARGS__
#endif
#define IF_NOT_DESKTOP(...)
#define IF_EXTRA_COMPAT(...)
#define IF_NOT_EXTRA_COMPAT(...) __VA_ARGS__
#define IF_FEDORA_COMPAT(...)
#define IF_NOT_FEDORA_COMPAT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_INCLUDE_SUSv2(...) __VA_ARGS__ "CONFIG_INCLUDE_SUSv2"
#else
# define IF_INCLUDE_SUSv2(...) __VA_ARGS__
#endif
#define IF_NOT_INCLUDE_SUSv2(...)
#ifdef MAKE_SUID
# define IF_LONG_OPTS(...) __VA_ARGS__ "CONFIG_LONG_OPTS"
#else
# define IF_LONG_OPTS(...) __VA_ARGS__
#endif
#define IF_NOT_LONG_OPTS(...)
#ifdef MAKE_SUID
# define IF_SHOW_USAGE(...) __VA_ARGS__ "CONFIG_SHOW_USAGE"
#else
# define IF_SHOW_USAGE(...) __VA_ARGS__
#endif
#define IF_NOT_SHOW_USAGE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VERBOSE_USAGE(...) __VA_ARGS__ "CONFIG_FEATURE_VERBOSE_USAGE"
#else
# define IF_FEATURE_VERBOSE_USAGE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VERBOSE_USAGE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_COMPRESS_USAGE(...) __VA_ARGS__ "CONFIG_FEATURE_COMPRESS_USAGE"
#else
# define IF_FEATURE_COMPRESS_USAGE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_COMPRESS_USAGE(...)
#ifdef MAKE_SUID
# define IF_LFS(...) __VA_ARGS__ "CONFIG_LFS"
#else
# define IF_LFS(...) __VA_ARGS__
#endif
#define IF_NOT_LFS(...)
#define IF_PAM(...)
#define IF_NOT_PAM(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_DEVPTS(...) __VA_ARGS__ "CONFIG_FEATURE_DEVPTS"
#else
# define IF_FEATURE_DEVPTS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DEVPTS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UTMP(...) __VA_ARGS__ "CONFIG_FEATURE_UTMP"
#else
# define IF_FEATURE_UTMP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UTMP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_WTMP(...) __VA_ARGS__ "CONFIG_FEATURE_WTMP"
#else
# define IF_FEATURE_WTMP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_WTMP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_PIDFILE(...) __VA_ARGS__ "CONFIG_FEATURE_PIDFILE"
#else
# define IF_FEATURE_PIDFILE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_PIDFILE(...)
#ifdef MAKE_SUID
# define IF_PID_FILE_PATH(...) __VA_ARGS__ "CONFIG_PID_FILE_PATH"
#else
# define IF_PID_FILE_PATH(...) __VA_ARGS__
#endif
#define IF_NOT_PID_FILE_PATH(...)
#ifdef MAKE_SUID
# define IF_BUSYBOX(...) __VA_ARGS__ "CONFIG_BUSYBOX"
#else
# define IF_BUSYBOX(...) __VA_ARGS__
#endif
#define IF_NOT_BUSYBOX(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INSTALLER(...) __VA_ARGS__ "CONFIG_FEATURE_INSTALLER"
#else
# define IF_FEATURE_INSTALLER(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INSTALLER(...)
#define IF_INSTALL_NO_USR(...)
#define IF_NOT_INSTALL_NO_USR(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_SUID(...) __VA_ARGS__ "CONFIG_FEATURE_SUID"
#else
# define IF_FEATURE_SUID(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SUID(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SUID_CONFIG(...) __VA_ARGS__ "CONFIG_FEATURE_SUID_CONFIG"
#else
# define IF_FEATURE_SUID_CONFIG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SUID_CONFIG(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SUID_CONFIG_QUIET(...) __VA_ARGS__ "CONFIG_FEATURE_SUID_CONFIG_QUIET"
#else
# define IF_FEATURE_SUID_CONFIG_QUIET(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SUID_CONFIG_QUIET(...)
#define IF_FEATURE_PREFER_APPLETS(...)
#define IF_NOT_FEATURE_PREFER_APPLETS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_BUSYBOX_EXEC_PATH(...) __VA_ARGS__ "CONFIG_BUSYBOX_EXEC_PATH"
#else
# define IF_BUSYBOX_EXEC_PATH(...) __VA_ARGS__
#endif
#define IF_NOT_BUSYBOX_EXEC_PATH(...)
#define IF_SELINUX(...)
#define IF_NOT_SELINUX(...) __VA_ARGS__
#define IF_FEATURE_CLEAN_UP(...)
#define IF_NOT_FEATURE_CLEAN_UP(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_SYSLOG(...) __VA_ARGS__ "CONFIG_FEATURE_SYSLOG"
#else
# define IF_FEATURE_SYSLOG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SYSLOG(...)
#ifdef MAKE_SUID
# define IF_PLATFORM_LINUX(...) __VA_ARGS__ "CONFIG_PLATFORM_LINUX"
#else
# define IF_PLATFORM_LINUX(...) __VA_ARGS__
#endif
#define IF_NOT_PLATFORM_LINUX(...)

/*
 * Build Options
 */
#define IF_STATIC(...)
#define IF_NOT_STATIC(...) __VA_ARGS__
#define IF_PIE(...)
#define IF_NOT_PIE(...) __VA_ARGS__
#define IF_NOMMU(...)
#define IF_NOT_NOMMU(...) __VA_ARGS__
#define IF_BUILD_LIBBUSYBOX(...)
#define IF_NOT_BUILD_LIBBUSYBOX(...) __VA_ARGS__
#define IF_FEATURE_LIBBUSYBOX_STATIC(...)
#define IF_NOT_FEATURE_LIBBUSYBOX_STATIC(...) __VA_ARGS__
#define IF_FEATURE_INDIVIDUAL(...)
#define IF_NOT_FEATURE_INDIVIDUAL(...) __VA_ARGS__
#define IF_FEATURE_SHARED_BUSYBOX(...)
#define IF_NOT_FEATURE_SHARED_BUSYBOX(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_CROSS_COMPILER_PREFIX(...) __VA_ARGS__ "CONFIG_CROSS_COMPILER_PREFIX"
#else
# define IF_CROSS_COMPILER_PREFIX(...) __VA_ARGS__
#endif
#define IF_NOT_CROSS_COMPILER_PREFIX(...)
#ifdef MAKE_SUID
# define IF_SYSROOT(...) __VA_ARGS__ "CONFIG_SYSROOT"
#else
# define IF_SYSROOT(...) __VA_ARGS__
#endif
#define IF_NOT_SYSROOT(...)
#ifdef MAKE_SUID
# define IF_EXTRA_CFLAGS(...) __VA_ARGS__ "CONFIG_EXTRA_CFLAGS"
#else
# define IF_EXTRA_CFLAGS(...) __VA_ARGS__
#endif
#define IF_NOT_EXTRA_CFLAGS(...)
#ifdef MAKE_SUID
# define IF_EXTRA_LDFLAGS(...) __VA_ARGS__ "CONFIG_EXTRA_LDFLAGS"
#else
# define IF_EXTRA_LDFLAGS(...) __VA_ARGS__
#endif
#define IF_NOT_EXTRA_LDFLAGS(...)
#ifdef MAKE_SUID
# define IF_EXTRA_LDLIBS(...) __VA_ARGS__ "CONFIG_EXTRA_LDLIBS"
#else
# define IF_EXTRA_LDLIBS(...) __VA_ARGS__
#endif
#define IF_NOT_EXTRA_LDLIBS(...)
#define IF_USE_PORTABLE_CODE(...)
#define IF_NOT_USE_PORTABLE_CODE(...) __VA_ARGS__

/*
 * Installation Options ("make install" behavior)
 */
#ifdef MAKE_SUID
# define IF_INSTALL_APPLET_SYMLINKS(...) __VA_ARGS__ "CONFIG_INSTALL_APPLET_SYMLINKS"
#else
# define IF_INSTALL_APPLET_SYMLINKS(...) __VA_ARGS__
#endif
#define IF_NOT_INSTALL_APPLET_SYMLINKS(...)
#define IF_INSTALL_APPLET_HARDLINKS(...)
#define IF_NOT_INSTALL_APPLET_HARDLINKS(...) __VA_ARGS__
#define IF_INSTALL_APPLET_SCRIPT_WRAPPERS(...)
#define IF_NOT_INSTALL_APPLET_SCRIPT_WRAPPERS(...) __VA_ARGS__
#define IF_INSTALL_APPLET_DONT(...)
#define IF_NOT_INSTALL_APPLET_DONT(...) __VA_ARGS__
#define IF_INSTALL_SH_APPLET_SYMLINK(...)
#define IF_NOT_INSTALL_SH_APPLET_SYMLINK(...) __VA_ARGS__
#define IF_INSTALL_SH_APPLET_HARDLINK(...)
#define IF_NOT_INSTALL_SH_APPLET_HARDLINK(...) __VA_ARGS__
#define IF_INSTALL_SH_APPLET_SCRIPT_WRAPPER(...)
#define IF_NOT_INSTALL_SH_APPLET_SCRIPT_WRAPPER(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_PREFIX(...) __VA_ARGS__ "CONFIG_PREFIX"
#else
# define IF_PREFIX(...) __VA_ARGS__
#endif
#define IF_NOT_PREFIX(...)

/*
 * Debugging Options
 */
#define IF_DEBUG(...)
#define IF_NOT_DEBUG(...) __VA_ARGS__
#define IF_DEBUG_PESSIMIZE(...)
#define IF_NOT_DEBUG_PESSIMIZE(...) __VA_ARGS__
#define IF_DEBUG_SANITIZE(...)
#define IF_NOT_DEBUG_SANITIZE(...) __VA_ARGS__
#define IF_UNIT_TEST(...)
#define IF_NOT_UNIT_TEST(...) __VA_ARGS__
#define IF_WERROR(...)
#define IF_NOT_WERROR(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_NO_DEBUG_LIB(...) __VA_ARGS__ "CONFIG_NO_DEBUG_LIB"
#else
# define IF_NO_DEBUG_LIB(...) __VA_ARGS__
#endif
#define IF_NOT_NO_DEBUG_LIB(...)
#define IF_DMALLOC(...)
#define IF_NOT_DMALLOC(...) __VA_ARGS__
#define IF_EFENCE(...)
#define IF_NOT_EFENCE(...) __VA_ARGS__

/*
 * Library Tuning
 */
#define IF_FEATURE_USE_BSS_TAIL(...)
#define IF_NOT_FEATURE_USE_BSS_TAIL(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_RTMINMAX(...) __VA_ARGS__ "CONFIG_FEATURE_RTMINMAX"
#else
# define IF_FEATURE_RTMINMAX(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_RTMINMAX(...)
#ifdef MAKE_SUID
# define IF_FEATURE_BUFFERS_USE_MALLOC(...) __VA_ARGS__ "CONFIG_FEATURE_BUFFERS_USE_MALLOC"
#else
# define IF_FEATURE_BUFFERS_USE_MALLOC(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_BUFFERS_USE_MALLOC(...)
#define IF_FEATURE_BUFFERS_GO_ON_STACK(...)
#define IF_NOT_FEATURE_BUFFERS_GO_ON_STACK(...) __VA_ARGS__
#define IF_FEATURE_BUFFERS_GO_IN_BSS(...)
#define IF_NOT_FEATURE_BUFFERS_GO_IN_BSS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_PASSWORD_MINLEN(...) __VA_ARGS__ "CONFIG_PASSWORD_MINLEN"
#else
# define IF_PASSWORD_MINLEN(...) __VA_ARGS__
#endif
#define IF_NOT_PASSWORD_MINLEN(...)
#ifdef MAKE_SUID
# define IF_MD5_SMALL(...) __VA_ARGS__ "CONFIG_MD5_SMALL"
#else
# define IF_MD5_SMALL(...) __VA_ARGS__
#endif
#define IF_NOT_MD5_SMALL(...)
#ifdef MAKE_SUID
# define IF_SHA3_SMALL(...) __VA_ARGS__ "CONFIG_SHA3_SMALL"
#else
# define IF_SHA3_SMALL(...) __VA_ARGS__
#endif
#define IF_NOT_SHA3_SMALL(...)
#define IF_FEATURE_FAST_TOP(...)
#define IF_NOT_FEATURE_FAST_TOP(...) __VA_ARGS__
#define IF_FEATURE_ETC_NETWORKS(...)
#define IF_NOT_FEATURE_ETC_NETWORKS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_EDITING(...) __VA_ARGS__ "CONFIG_FEATURE_EDITING"
#else
# define IF_FEATURE_EDITING(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_EDITING(...)
#ifdef MAKE_SUID
# define IF_FEATURE_EDITING_MAX_LEN(...) __VA_ARGS__ "CONFIG_FEATURE_EDITING_MAX_LEN"
#else
# define IF_FEATURE_EDITING_MAX_LEN(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_EDITING_MAX_LEN(...)
#define IF_FEATURE_EDITING_VI(...)
#define IF_NOT_FEATURE_EDITING_VI(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_EDITING_HISTORY(...) __VA_ARGS__ "CONFIG_FEATURE_EDITING_HISTORY"
#else
# define IF_FEATURE_EDITING_HISTORY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_EDITING_HISTORY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_EDITING_SAVEHISTORY(...) __VA_ARGS__ "CONFIG_FEATURE_EDITING_SAVEHISTORY"
#else
# define IF_FEATURE_EDITING_SAVEHISTORY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_EDITING_SAVEHISTORY(...)
#define IF_FEATURE_EDITING_SAVE_ON_EXIT(...)
#define IF_NOT_FEATURE_EDITING_SAVE_ON_EXIT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_REVERSE_SEARCH(...) __VA_ARGS__ "CONFIG_FEATURE_REVERSE_SEARCH"
#else
# define IF_FEATURE_REVERSE_SEARCH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_REVERSE_SEARCH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAB_COMPLETION(...) __VA_ARGS__ "CONFIG_FEATURE_TAB_COMPLETION"
#else
# define IF_FEATURE_TAB_COMPLETION(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAB_COMPLETION(...)
#ifdef MAKE_SUID
# define IF_FEATURE_USERNAME_COMPLETION(...) __VA_ARGS__ "CONFIG_FEATURE_USERNAME_COMPLETION"
#else
# define IF_FEATURE_USERNAME_COMPLETION(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_USERNAME_COMPLETION(...)
#ifdef MAKE_SUID
# define IF_FEATURE_EDITING_FANCY_PROMPT(...) __VA_ARGS__ "CONFIG_FEATURE_EDITING_FANCY_PROMPT"
#else
# define IF_FEATURE_EDITING_FANCY_PROMPT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_EDITING_FANCY_PROMPT(...)
#define IF_FEATURE_EDITING_ASK_TERMINAL(...)
#define IF_NOT_FEATURE_EDITING_ASK_TERMINAL(...) __VA_ARGS__
#define IF_LOCALE_SUPPORT(...)
#define IF_NOT_LOCALE_SUPPORT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_UNICODE_SUPPORT(...) __VA_ARGS__ "CONFIG_UNICODE_SUPPORT"
#else
# define IF_UNICODE_SUPPORT(...) __VA_ARGS__
#endif
#define IF_NOT_UNICODE_SUPPORT(...)
#define IF_UNICODE_USING_LOCALE(...)
#define IF_NOT_UNICODE_USING_LOCALE(...) __VA_ARGS__
#define IF_FEATURE_CHECK_UNICODE_IN_ENV(...)
#define IF_NOT_FEATURE_CHECK_UNICODE_IN_ENV(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_SUBST_WCHAR(...) __VA_ARGS__ "CONFIG_SUBST_WCHAR"
#else
# define IF_SUBST_WCHAR(...) __VA_ARGS__
#endif
#define IF_NOT_SUBST_WCHAR(...)
#ifdef MAKE_SUID
# define IF_LAST_SUPPORTED_WCHAR(...) __VA_ARGS__ "CONFIG_LAST_SUPPORTED_WCHAR"
#else
# define IF_LAST_SUPPORTED_WCHAR(...) __VA_ARGS__
#endif
#define IF_NOT_LAST_SUPPORTED_WCHAR(...)
#define IF_UNICODE_COMBINING_WCHARS(...)
#define IF_NOT_UNICODE_COMBINING_WCHARS(...) __VA_ARGS__
#define IF_UNICODE_WIDE_WCHARS(...)
#define IF_NOT_UNICODE_WIDE_WCHARS(...) __VA_ARGS__
#define IF_UNICODE_BIDI_SUPPORT(...)
#define IF_NOT_UNICODE_BIDI_SUPPORT(...) __VA_ARGS__
#define IF_UNICODE_NEUTRAL_TABLE(...)
#define IF_NOT_UNICODE_NEUTRAL_TABLE(...) __VA_ARGS__
#define IF_UNICODE_PRESERVE_BROKEN(...)
#define IF_NOT_UNICODE_PRESERVE_BROKEN(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_NON_POSIX_CP(...) __VA_ARGS__ "CONFIG_FEATURE_NON_POSIX_CP"
#else
# define IF_FEATURE_NON_POSIX_CP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_NON_POSIX_CP(...)
#define IF_FEATURE_VERBOSE_CP_MESSAGE(...)
#define IF_NOT_FEATURE_VERBOSE_CP_MESSAGE(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_USE_SENDFILE(...) __VA_ARGS__ "CONFIG_FEATURE_USE_SENDFILE"
#else
# define IF_FEATURE_USE_SENDFILE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_USE_SENDFILE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_COPYBUF_KB(...) __VA_ARGS__ "CONFIG_FEATURE_COPYBUF_KB"
#else
# define IF_FEATURE_COPYBUF_KB(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_COPYBUF_KB(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SKIP_ROOTFS(...) __VA_ARGS__ "CONFIG_FEATURE_SKIP_ROOTFS"
#else
# define IF_FEATURE_SKIP_ROOTFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SKIP_ROOTFS(...)
#ifdef MAKE_SUID
# define IF_MONOTONIC_SYSCALL(...) __VA_ARGS__ "CONFIG_MONOTONIC_SYSCALL"
#else
# define IF_MONOTONIC_SYSCALL(...) __VA_ARGS__
#endif
#define IF_NOT_MONOTONIC_SYSCALL(...)
#ifdef MAKE_SUID
# define IF_IOCTL_HEX2STR_ERROR(...) __VA_ARGS__ "CONFIG_IOCTL_HEX2STR_ERROR"
#else
# define IF_IOCTL_HEX2STR_ERROR(...) __VA_ARGS__
#endif
#define IF_NOT_IOCTL_HEX2STR_ERROR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HWIB(...) __VA_ARGS__ "CONFIG_FEATURE_HWIB"
#else
# define IF_FEATURE_HWIB(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HWIB(...)

/*
 * Applets
 */

/*
 * Archival Utilities
 */
#ifdef MAKE_SUID
# define IF_FEATURE_SEAMLESS_XZ(...) __VA_ARGS__ "CONFIG_FEATURE_SEAMLESS_XZ"
#else
# define IF_FEATURE_SEAMLESS_XZ(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SEAMLESS_XZ(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SEAMLESS_LZMA(...) __VA_ARGS__ "CONFIG_FEATURE_SEAMLESS_LZMA"
#else
# define IF_FEATURE_SEAMLESS_LZMA(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SEAMLESS_LZMA(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SEAMLESS_BZ2(...) __VA_ARGS__ "CONFIG_FEATURE_SEAMLESS_BZ2"
#else
# define IF_FEATURE_SEAMLESS_BZ2(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SEAMLESS_BZ2(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SEAMLESS_GZ(...) __VA_ARGS__ "CONFIG_FEATURE_SEAMLESS_GZ"
#else
# define IF_FEATURE_SEAMLESS_GZ(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SEAMLESS_GZ(...)
#define IF_FEATURE_SEAMLESS_Z(...)
#define IF_NOT_FEATURE_SEAMLESS_Z(...) __VA_ARGS__
#define IF_AR(...)
#define IF_NOT_AR(...) __VA_ARGS__
#define IF_FEATURE_AR_LONG_FILENAMES(...)
#define IF_NOT_FEATURE_AR_LONG_FILENAMES(...) __VA_ARGS__
#define IF_FEATURE_AR_CREATE(...)
#define IF_NOT_FEATURE_AR_CREATE(...) __VA_ARGS__
#define IF_UNCOMPRESS(...)
#define IF_NOT_UNCOMPRESS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_GUNZIP(...) __VA_ARGS__ "CONFIG_GUNZIP"
#else
# define IF_GUNZIP(...) __VA_ARGS__
#endif
#define IF_NOT_GUNZIP(...)
#ifdef MAKE_SUID
# define IF_ZCAT(...) __VA_ARGS__ "CONFIG_ZCAT"
#else
# define IF_ZCAT(...) __VA_ARGS__
#endif
#define IF_NOT_ZCAT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_GUNZIP_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_GUNZIP_LONG_OPTIONS"
#else
# define IF_FEATURE_GUNZIP_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_GUNZIP_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_BUNZIP2(...) __VA_ARGS__ "CONFIG_BUNZIP2"
#else
# define IF_BUNZIP2(...) __VA_ARGS__
#endif
#define IF_NOT_BUNZIP2(...)
#ifdef MAKE_SUID
# define IF_BZCAT(...) __VA_ARGS__ "CONFIG_BZCAT"
#else
# define IF_BZCAT(...) __VA_ARGS__
#endif
#define IF_NOT_BZCAT(...)
#ifdef MAKE_SUID
# define IF_UNLZMA(...) __VA_ARGS__ "CONFIG_UNLZMA"
#else
# define IF_UNLZMA(...) __VA_ARGS__
#endif
#define IF_NOT_UNLZMA(...)
#ifdef MAKE_SUID
# define IF_LZCAT(...) __VA_ARGS__ "CONFIG_LZCAT"
#else
# define IF_LZCAT(...) __VA_ARGS__
#endif
#define IF_NOT_LZCAT(...)
#ifdef MAKE_SUID
# define IF_LZMA(...) __VA_ARGS__ "CONFIG_LZMA"
#else
# define IF_LZMA(...) __VA_ARGS__
#endif
#define IF_NOT_LZMA(...)
#ifdef MAKE_SUID
# define IF_UNXZ(...) __VA_ARGS__ "CONFIG_UNXZ"
#else
# define IF_UNXZ(...) __VA_ARGS__
#endif
#define IF_NOT_UNXZ(...)
#ifdef MAKE_SUID
# define IF_XZCAT(...) __VA_ARGS__ "CONFIG_XZCAT"
#else
# define IF_XZCAT(...) __VA_ARGS__
#endif
#define IF_NOT_XZCAT(...)
#ifdef MAKE_SUID
# define IF_XZ(...) __VA_ARGS__ "CONFIG_XZ"
#else
# define IF_XZ(...) __VA_ARGS__
#endif
#define IF_NOT_XZ(...)
#ifdef MAKE_SUID
# define IF_BZIP2(...) __VA_ARGS__ "CONFIG_BZIP2"
#else
# define IF_BZIP2(...) __VA_ARGS__
#endif
#define IF_NOT_BZIP2(...)
#ifdef MAKE_SUID
# define IF_FEATURE_BZIP2_DECOMPRESS(...) __VA_ARGS__ "CONFIG_FEATURE_BZIP2_DECOMPRESS"
#else
# define IF_FEATURE_BZIP2_DECOMPRESS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_BZIP2_DECOMPRESS(...)
#ifdef MAKE_SUID
# define IF_CPIO(...) __VA_ARGS__ "CONFIG_CPIO"
#else
# define IF_CPIO(...) __VA_ARGS__
#endif
#define IF_NOT_CPIO(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CPIO_O(...) __VA_ARGS__ "CONFIG_FEATURE_CPIO_O"
#else
# define IF_FEATURE_CPIO_O(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CPIO_O(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CPIO_P(...) __VA_ARGS__ "CONFIG_FEATURE_CPIO_P"
#else
# define IF_FEATURE_CPIO_P(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CPIO_P(...)
#ifdef MAKE_SUID
# define IF_DPKG(...) __VA_ARGS__ "CONFIG_DPKG"
#else
# define IF_DPKG(...) __VA_ARGS__
#endif
#define IF_NOT_DPKG(...)
#ifdef MAKE_SUID
# define IF_DPKG_DEB(...) __VA_ARGS__ "CONFIG_DPKG_DEB"
#else
# define IF_DPKG_DEB(...) __VA_ARGS__
#endif
#define IF_NOT_DPKG_DEB(...)
#ifdef MAKE_SUID
# define IF_GZIP(...) __VA_ARGS__ "CONFIG_GZIP"
#else
# define IF_GZIP(...) __VA_ARGS__
#endif
#define IF_NOT_GZIP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_GZIP_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_GZIP_LONG_OPTIONS"
#else
# define IF_FEATURE_GZIP_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_GZIP_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_GZIP_FAST(...) __VA_ARGS__ "CONFIG_GZIP_FAST"
#else
# define IF_GZIP_FAST(...) __VA_ARGS__
#endif
#define IF_NOT_GZIP_FAST(...)
#define IF_FEATURE_GZIP_LEVELS(...)
#define IF_NOT_FEATURE_GZIP_LEVELS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_GZIP_DECOMPRESS(...) __VA_ARGS__ "CONFIG_FEATURE_GZIP_DECOMPRESS"
#else
# define IF_FEATURE_GZIP_DECOMPRESS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_GZIP_DECOMPRESS(...)
#ifdef MAKE_SUID
# define IF_LZOP(...) __VA_ARGS__ "CONFIG_LZOP"
#else
# define IF_LZOP(...) __VA_ARGS__
#endif
#define IF_NOT_LZOP(...)
#define IF_UNLZOP(...)
#define IF_NOT_UNLZOP(...) __VA_ARGS__
#define IF_LZOPCAT(...)
#define IF_NOT_LZOPCAT(...) __VA_ARGS__
#define IF_LZOP_COMPR_HIGH(...)
#define IF_NOT_LZOP_COMPR_HIGH(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_RPM(...) __VA_ARGS__ "CONFIG_RPM"
#else
# define IF_RPM(...) __VA_ARGS__
#endif
#define IF_NOT_RPM(...)
#ifdef MAKE_SUID
# define IF_RPM2CPIO(...) __VA_ARGS__ "CONFIG_RPM2CPIO"
#else
# define IF_RPM2CPIO(...) __VA_ARGS__
#endif
#define IF_NOT_RPM2CPIO(...)
#ifdef MAKE_SUID
# define IF_TAR(...) __VA_ARGS__ "CONFIG_TAR"
#else
# define IF_TAR(...) __VA_ARGS__
#endif
#define IF_NOT_TAR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_LONG_OPTIONS"
#else
# define IF_FEATURE_TAR_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_CREATE(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_CREATE"
#else
# define IF_FEATURE_TAR_CREATE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_CREATE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_AUTODETECT(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_AUTODETECT"
#else
# define IF_FEATURE_TAR_AUTODETECT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_AUTODETECT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_FROM(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_FROM"
#else
# define IF_FEATURE_TAR_FROM(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_FROM(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_OLDGNU_COMPATIBILITY(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_OLDGNU_COMPATIBILITY"
#else
# define IF_FEATURE_TAR_OLDGNU_COMPATIBILITY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_OLDGNU_COMPATIBILITY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_OLDSUN_COMPATIBILITY(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_OLDSUN_COMPATIBILITY"
#else
# define IF_FEATURE_TAR_OLDSUN_COMPATIBILITY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_OLDSUN_COMPATIBILITY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_GNU_EXTENSIONS(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_GNU_EXTENSIONS"
#else
# define IF_FEATURE_TAR_GNU_EXTENSIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_GNU_EXTENSIONS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_TO_COMMAND(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_TO_COMMAND"
#else
# define IF_FEATURE_TAR_TO_COMMAND(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_TO_COMMAND(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_UNAME_GNAME(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_UNAME_GNAME"
#else
# define IF_FEATURE_TAR_UNAME_GNAME(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_UNAME_GNAME(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TAR_NOPRESERVE_TIME(...) __VA_ARGS__ "CONFIG_FEATURE_TAR_NOPRESERVE_TIME"
#else
# define IF_FEATURE_TAR_NOPRESERVE_TIME(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TAR_NOPRESERVE_TIME(...)
#define IF_FEATURE_TAR_SELINUX(...)
#define IF_NOT_FEATURE_TAR_SELINUX(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_UNZIP(...) __VA_ARGS__ "CONFIG_UNZIP"
#else
# define IF_UNZIP(...) __VA_ARGS__
#endif
#define IF_NOT_UNZIP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UNZIP_CDF(...) __VA_ARGS__ "CONFIG_FEATURE_UNZIP_CDF"
#else
# define IF_FEATURE_UNZIP_CDF(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UNZIP_CDF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UNZIP_BZIP2(...) __VA_ARGS__ "CONFIG_FEATURE_UNZIP_BZIP2"
#else
# define IF_FEATURE_UNZIP_BZIP2(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UNZIP_BZIP2(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UNZIP_LZMA(...) __VA_ARGS__ "CONFIG_FEATURE_UNZIP_LZMA"
#else
# define IF_FEATURE_UNZIP_LZMA(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UNZIP_LZMA(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UNZIP_XZ(...) __VA_ARGS__ "CONFIG_FEATURE_UNZIP_XZ"
#else
# define IF_FEATURE_UNZIP_XZ(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UNZIP_XZ(...)
#define IF_FEATURE_LZMA_FAST(...)
#define IF_NOT_FEATURE_LZMA_FAST(...) __VA_ARGS__

/*
 * Coreutils
 */
#ifdef MAKE_SUID
# define IF_BASENAME(...) __VA_ARGS__ "CONFIG_BASENAME"
#else
# define IF_BASENAME(...) __VA_ARGS__
#endif
#define IF_NOT_BASENAME(...)
#ifdef MAKE_SUID
# define IF_CAT(...) __VA_ARGS__ "CONFIG_CAT"
#else
# define IF_CAT(...) __VA_ARGS__
#endif
#define IF_NOT_CAT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CATN(...) __VA_ARGS__ "CONFIG_FEATURE_CATN"
#else
# define IF_FEATURE_CATN(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CATN(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CATV(...) __VA_ARGS__ "CONFIG_FEATURE_CATV"
#else
# define IF_FEATURE_CATV(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CATV(...)
#ifdef MAKE_SUID
# define IF_CHGRP(...) __VA_ARGS__ "CONFIG_CHGRP"
#else
# define IF_CHGRP(...) __VA_ARGS__
#endif
#define IF_NOT_CHGRP(...)
#ifdef MAKE_SUID
# define IF_CHMOD(...) __VA_ARGS__ "CONFIG_CHMOD"
#else
# define IF_CHMOD(...) __VA_ARGS__
#endif
#define IF_NOT_CHMOD(...)
#ifdef MAKE_SUID
# define IF_CHOWN(...) __VA_ARGS__ "CONFIG_CHOWN"
#else
# define IF_CHOWN(...) __VA_ARGS__
#endif
#define IF_NOT_CHOWN(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CHOWN_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_CHOWN_LONG_OPTIONS"
#else
# define IF_FEATURE_CHOWN_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CHOWN_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_CHROOT(...) __VA_ARGS__ "CONFIG_CHROOT"
#else
# define IF_CHROOT(...) __VA_ARGS__
#endif
#define IF_NOT_CHROOT(...)
#ifdef MAKE_SUID
# define IF_CKSUM(...) __VA_ARGS__ "CONFIG_CKSUM"
#else
# define IF_CKSUM(...) __VA_ARGS__
#endif
#define IF_NOT_CKSUM(...)
#ifdef MAKE_SUID
# define IF_COMM(...) __VA_ARGS__ "CONFIG_COMM"
#else
# define IF_COMM(...) __VA_ARGS__
#endif
#define IF_NOT_COMM(...)
#ifdef MAKE_SUID
# define IF_CP(...) __VA_ARGS__ "CONFIG_CP"
#else
# define IF_CP(...) __VA_ARGS__
#endif
#define IF_NOT_CP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CP_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_CP_LONG_OPTIONS"
#else
# define IF_FEATURE_CP_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CP_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_CUT(...) __VA_ARGS__ "CONFIG_CUT"
#else
# define IF_CUT(...) __VA_ARGS__
#endif
#define IF_NOT_CUT(...)
#ifdef MAKE_SUID
# define IF_DATE(...) __VA_ARGS__ "CONFIG_DATE"
#else
# define IF_DATE(...) __VA_ARGS__
#endif
#define IF_NOT_DATE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DATE_ISOFMT(...) __VA_ARGS__ "CONFIG_FEATURE_DATE_ISOFMT"
#else
# define IF_FEATURE_DATE_ISOFMT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DATE_ISOFMT(...)
#define IF_FEATURE_DATE_NANO(...)
#define IF_NOT_FEATURE_DATE_NANO(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_DATE_COMPAT(...) __VA_ARGS__ "CONFIG_FEATURE_DATE_COMPAT"
#else
# define IF_FEATURE_DATE_COMPAT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DATE_COMPAT(...)
#ifdef MAKE_SUID
# define IF_DD(...) __VA_ARGS__ "CONFIG_DD"
#else
# define IF_DD(...) __VA_ARGS__
#endif
#define IF_NOT_DD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DD_SIGNAL_HANDLING(...) __VA_ARGS__ "CONFIG_FEATURE_DD_SIGNAL_HANDLING"
#else
# define IF_FEATURE_DD_SIGNAL_HANDLING(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DD_SIGNAL_HANDLING(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DD_THIRD_STATUS_LINE(...) __VA_ARGS__ "CONFIG_FEATURE_DD_THIRD_STATUS_LINE"
#else
# define IF_FEATURE_DD_THIRD_STATUS_LINE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DD_THIRD_STATUS_LINE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DD_IBS_OBS(...) __VA_ARGS__ "CONFIG_FEATURE_DD_IBS_OBS"
#else
# define IF_FEATURE_DD_IBS_OBS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DD_IBS_OBS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DD_STATUS(...) __VA_ARGS__ "CONFIG_FEATURE_DD_STATUS"
#else
# define IF_FEATURE_DD_STATUS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DD_STATUS(...)
#ifdef MAKE_SUID
# define IF_DF(...) __VA_ARGS__ "CONFIG_DF"
#else
# define IF_DF(...) __VA_ARGS__
#endif
#define IF_NOT_DF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DF_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_DF_FANCY"
#else
# define IF_FEATURE_DF_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DF_FANCY(...)
#ifdef MAKE_SUID
# define IF_DIRNAME(...) __VA_ARGS__ "CONFIG_DIRNAME"
#else
# define IF_DIRNAME(...) __VA_ARGS__
#endif
#define IF_NOT_DIRNAME(...)
#ifdef MAKE_SUID
# define IF_DOS2UNIX(...) __VA_ARGS__ "CONFIG_DOS2UNIX"
#else
# define IF_DOS2UNIX(...) __VA_ARGS__
#endif
#define IF_NOT_DOS2UNIX(...)
#ifdef MAKE_SUID
# define IF_UNIX2DOS(...) __VA_ARGS__ "CONFIG_UNIX2DOS"
#else
# define IF_UNIX2DOS(...) __VA_ARGS__
#endif
#define IF_NOT_UNIX2DOS(...)
#ifdef MAKE_SUID
# define IF_DU(...) __VA_ARGS__ "CONFIG_DU"
#else
# define IF_DU(...) __VA_ARGS__
#endif
#define IF_NOT_DU(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DU_DEFAULT_BLOCKSIZE_1K(...) __VA_ARGS__ "CONFIG_FEATURE_DU_DEFAULT_BLOCKSIZE_1K"
#else
# define IF_FEATURE_DU_DEFAULT_BLOCKSIZE_1K(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DU_DEFAULT_BLOCKSIZE_1K(...)
#ifdef MAKE_SUID
# define IF_ECHO(...) __VA_ARGS__ "CONFIG_ECHO"
#else
# define IF_ECHO(...) __VA_ARGS__
#endif
#define IF_NOT_ECHO(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FANCY_ECHO(...) __VA_ARGS__ "CONFIG_FEATURE_FANCY_ECHO"
#else
# define IF_FEATURE_FANCY_ECHO(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FANCY_ECHO(...)
#ifdef MAKE_SUID
# define IF_ENV(...) __VA_ARGS__ "CONFIG_ENV"
#else
# define IF_ENV(...) __VA_ARGS__
#endif
#define IF_NOT_ENV(...)
#ifdef MAKE_SUID
# define IF_EXPAND(...) __VA_ARGS__ "CONFIG_EXPAND"
#else
# define IF_EXPAND(...) __VA_ARGS__
#endif
#define IF_NOT_EXPAND(...)
#ifdef MAKE_SUID
# define IF_UNEXPAND(...) __VA_ARGS__ "CONFIG_UNEXPAND"
#else
# define IF_UNEXPAND(...) __VA_ARGS__
#endif
#define IF_NOT_UNEXPAND(...)
#ifdef MAKE_SUID
# define IF_EXPR(...) __VA_ARGS__ "CONFIG_EXPR"
#else
# define IF_EXPR(...) __VA_ARGS__
#endif
#define IF_NOT_EXPR(...)
#ifdef MAKE_SUID
# define IF_EXPR_MATH_SUPPORT_64(...) __VA_ARGS__ "CONFIG_EXPR_MATH_SUPPORT_64"
#else
# define IF_EXPR_MATH_SUPPORT_64(...) __VA_ARGS__
#endif
#define IF_NOT_EXPR_MATH_SUPPORT_64(...)
#ifdef MAKE_SUID
# define IF_FACTOR(...) __VA_ARGS__ "CONFIG_FACTOR"
#else
# define IF_FACTOR(...) __VA_ARGS__
#endif
#define IF_NOT_FACTOR(...)
#ifdef MAKE_SUID
# define IF_FALSE(...) __VA_ARGS__ "CONFIG_FALSE"
#else
# define IF_FALSE(...) __VA_ARGS__
#endif
#define IF_NOT_FALSE(...)
#ifdef MAKE_SUID
# define IF_FOLD(...) __VA_ARGS__ "CONFIG_FOLD"
#else
# define IF_FOLD(...) __VA_ARGS__
#endif
#define IF_NOT_FOLD(...)
#ifdef MAKE_SUID
# define IF_FSYNC(...) __VA_ARGS__ "CONFIG_FSYNC"
#else
# define IF_FSYNC(...) __VA_ARGS__
#endif
#define IF_NOT_FSYNC(...)
#ifdef MAKE_SUID
# define IF_HEAD(...) __VA_ARGS__ "CONFIG_HEAD"
#else
# define IF_HEAD(...) __VA_ARGS__
#endif
#define IF_NOT_HEAD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FANCY_HEAD(...) __VA_ARGS__ "CONFIG_FEATURE_FANCY_HEAD"
#else
# define IF_FEATURE_FANCY_HEAD(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FANCY_HEAD(...)
#ifdef MAKE_SUID
# define IF_HOSTID(...) __VA_ARGS__ "CONFIG_HOSTID"
#else
# define IF_HOSTID(...) __VA_ARGS__
#endif
#define IF_NOT_HOSTID(...)
#ifdef MAKE_SUID
# define IF_ID(...) __VA_ARGS__ "CONFIG_ID"
#else
# define IF_ID(...) __VA_ARGS__
#endif
#define IF_NOT_ID(...)
#ifdef MAKE_SUID
# define IF_GROUPS(...) __VA_ARGS__ "CONFIG_GROUPS"
#else
# define IF_GROUPS(...) __VA_ARGS__
#endif
#define IF_NOT_GROUPS(...)
#ifdef MAKE_SUID
# define IF_INSTALL(...) __VA_ARGS__ "CONFIG_INSTALL"
#else
# define IF_INSTALL(...) __VA_ARGS__
#endif
#define IF_NOT_INSTALL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INSTALL_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_INSTALL_LONG_OPTIONS"
#else
# define IF_FEATURE_INSTALL_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INSTALL_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_LINK(...) __VA_ARGS__ "CONFIG_LINK"
#else
# define IF_LINK(...) __VA_ARGS__
#endif
#define IF_NOT_LINK(...)
#ifdef MAKE_SUID
# define IF_LN(...) __VA_ARGS__ "CONFIG_LN"
#else
# define IF_LN(...) __VA_ARGS__
#endif
#define IF_NOT_LN(...)
#ifdef MAKE_SUID
# define IF_LOGNAME(...) __VA_ARGS__ "CONFIG_LOGNAME"
#else
# define IF_LOGNAME(...) __VA_ARGS__
#endif
#define IF_NOT_LOGNAME(...)
#ifdef MAKE_SUID
# define IF_LS(...) __VA_ARGS__ "CONFIG_LS"
#else
# define IF_LS(...) __VA_ARGS__
#endif
#define IF_NOT_LS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LS_FILETYPES(...) __VA_ARGS__ "CONFIG_FEATURE_LS_FILETYPES"
#else
# define IF_FEATURE_LS_FILETYPES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LS_FILETYPES(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LS_FOLLOWLINKS(...) __VA_ARGS__ "CONFIG_FEATURE_LS_FOLLOWLINKS"
#else
# define IF_FEATURE_LS_FOLLOWLINKS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LS_FOLLOWLINKS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LS_RECURSIVE(...) __VA_ARGS__ "CONFIG_FEATURE_LS_RECURSIVE"
#else
# define IF_FEATURE_LS_RECURSIVE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LS_RECURSIVE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LS_WIDTH(...) __VA_ARGS__ "CONFIG_FEATURE_LS_WIDTH"
#else
# define IF_FEATURE_LS_WIDTH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LS_WIDTH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LS_SORTFILES(...) __VA_ARGS__ "CONFIG_FEATURE_LS_SORTFILES"
#else
# define IF_FEATURE_LS_SORTFILES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LS_SORTFILES(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LS_TIMESTAMPS(...) __VA_ARGS__ "CONFIG_FEATURE_LS_TIMESTAMPS"
#else
# define IF_FEATURE_LS_TIMESTAMPS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LS_TIMESTAMPS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LS_USERNAME(...) __VA_ARGS__ "CONFIG_FEATURE_LS_USERNAME"
#else
# define IF_FEATURE_LS_USERNAME(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LS_USERNAME(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LS_COLOR(...) __VA_ARGS__ "CONFIG_FEATURE_LS_COLOR"
#else
# define IF_FEATURE_LS_COLOR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LS_COLOR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LS_COLOR_IS_DEFAULT(...) __VA_ARGS__ "CONFIG_FEATURE_LS_COLOR_IS_DEFAULT"
#else
# define IF_FEATURE_LS_COLOR_IS_DEFAULT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LS_COLOR_IS_DEFAULT(...)
#ifdef MAKE_SUID
# define IF_MD5SUM(...) __VA_ARGS__ "CONFIG_MD5SUM"
#else
# define IF_MD5SUM(...) __VA_ARGS__
#endif
#define IF_NOT_MD5SUM(...)
#ifdef MAKE_SUID
# define IF_SHA1SUM(...) __VA_ARGS__ "CONFIG_SHA1SUM"
#else
# define IF_SHA1SUM(...) __VA_ARGS__
#endif
#define IF_NOT_SHA1SUM(...)
#ifdef MAKE_SUID
# define IF_SHA256SUM(...) __VA_ARGS__ "CONFIG_SHA256SUM"
#else
# define IF_SHA256SUM(...) __VA_ARGS__
#endif
#define IF_NOT_SHA256SUM(...)
#ifdef MAKE_SUID
# define IF_SHA512SUM(...) __VA_ARGS__ "CONFIG_SHA512SUM"
#else
# define IF_SHA512SUM(...) __VA_ARGS__
#endif
#define IF_NOT_SHA512SUM(...)
#ifdef MAKE_SUID
# define IF_SHA3SUM(...) __VA_ARGS__ "CONFIG_SHA3SUM"
#else
# define IF_SHA3SUM(...) __VA_ARGS__
#endif
#define IF_NOT_SHA3SUM(...)

/*
 * Common options for md5sum, sha1sum, sha256sum, sha512sum, sha3sum
 */
#ifdef MAKE_SUID
# define IF_FEATURE_MD5_SHA1_SUM_CHECK(...) __VA_ARGS__ "CONFIG_FEATURE_MD5_SHA1_SUM_CHECK"
#else
# define IF_FEATURE_MD5_SHA1_SUM_CHECK(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MD5_SHA1_SUM_CHECK(...)
#ifdef MAKE_SUID
# define IF_MKDIR(...) __VA_ARGS__ "CONFIG_MKDIR"
#else
# define IF_MKDIR(...) __VA_ARGS__
#endif
#define IF_NOT_MKDIR(...)
#ifdef MAKE_SUID
# define IF_MKFIFO(...) __VA_ARGS__ "CONFIG_MKFIFO"
#else
# define IF_MKFIFO(...) __VA_ARGS__
#endif
#define IF_NOT_MKFIFO(...)
#ifdef MAKE_SUID
# define IF_MKNOD(...) __VA_ARGS__ "CONFIG_MKNOD"
#else
# define IF_MKNOD(...) __VA_ARGS__
#endif
#define IF_NOT_MKNOD(...)
#ifdef MAKE_SUID
# define IF_MKTEMP(...) __VA_ARGS__ "CONFIG_MKTEMP"
#else
# define IF_MKTEMP(...) __VA_ARGS__
#endif
#define IF_NOT_MKTEMP(...)
#ifdef MAKE_SUID
# define IF_MV(...) __VA_ARGS__ "CONFIG_MV"
#else
# define IF_MV(...) __VA_ARGS__
#endif
#define IF_NOT_MV(...)
#ifdef MAKE_SUID
# define IF_NICE(...) __VA_ARGS__ "CONFIG_NICE"
#else
# define IF_NICE(...) __VA_ARGS__
#endif
#define IF_NOT_NICE(...)
#ifdef MAKE_SUID
# define IF_NL(...) __VA_ARGS__ "CONFIG_NL"
#else
# define IF_NL(...) __VA_ARGS__
#endif
#define IF_NOT_NL(...)
#ifdef MAKE_SUID
# define IF_NOHUP(...) __VA_ARGS__ "CONFIG_NOHUP"
#else
# define IF_NOHUP(...) __VA_ARGS__
#endif
#define IF_NOT_NOHUP(...)
#ifdef MAKE_SUID
# define IF_NPROC(...) __VA_ARGS__ "CONFIG_NPROC"
#else
# define IF_NPROC(...) __VA_ARGS__
#endif
#define IF_NOT_NPROC(...)
#ifdef MAKE_SUID
# define IF_OD(...) __VA_ARGS__ "CONFIG_OD"
#else
# define IF_OD(...) __VA_ARGS__
#endif
#define IF_NOT_OD(...)
#ifdef MAKE_SUID
# define IF_PASTE(...) __VA_ARGS__ "CONFIG_PASTE"
#else
# define IF_PASTE(...) __VA_ARGS__
#endif
#define IF_NOT_PASTE(...)
#ifdef MAKE_SUID
# define IF_PRINTENV(...) __VA_ARGS__ "CONFIG_PRINTENV"
#else
# define IF_PRINTENV(...) __VA_ARGS__
#endif
#define IF_NOT_PRINTENV(...)
#ifdef MAKE_SUID
# define IF_PRINTF(...) __VA_ARGS__ "CONFIG_PRINTF"
#else
# define IF_PRINTF(...) __VA_ARGS__
#endif
#define IF_NOT_PRINTF(...)
#ifdef MAKE_SUID
# define IF_PWD(...) __VA_ARGS__ "CONFIG_PWD"
#else
# define IF_PWD(...) __VA_ARGS__
#endif
#define IF_NOT_PWD(...)
#ifdef MAKE_SUID
# define IF_READLINK(...) __VA_ARGS__ "CONFIG_READLINK"
#else
# define IF_READLINK(...) __VA_ARGS__
#endif
#define IF_NOT_READLINK(...)
#ifdef MAKE_SUID
# define IF_FEATURE_READLINK_FOLLOW(...) __VA_ARGS__ "CONFIG_FEATURE_READLINK_FOLLOW"
#else
# define IF_FEATURE_READLINK_FOLLOW(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_READLINK_FOLLOW(...)
#ifdef MAKE_SUID
# define IF_REALPATH(...) __VA_ARGS__ "CONFIG_REALPATH"
#else
# define IF_REALPATH(...) __VA_ARGS__
#endif
#define IF_NOT_REALPATH(...)
#ifdef MAKE_SUID
# define IF_RM(...) __VA_ARGS__ "CONFIG_RM"
#else
# define IF_RM(...) __VA_ARGS__
#endif
#define IF_NOT_RM(...)
#ifdef MAKE_SUID
# define IF_RMDIR(...) __VA_ARGS__ "CONFIG_RMDIR"
#else
# define IF_RMDIR(...) __VA_ARGS__
#endif
#define IF_NOT_RMDIR(...)
#ifdef MAKE_SUID
# define IF_SEQ(...) __VA_ARGS__ "CONFIG_SEQ"
#else
# define IF_SEQ(...) __VA_ARGS__
#endif
#define IF_NOT_SEQ(...)
#ifdef MAKE_SUID
# define IF_SHRED(...) __VA_ARGS__ "CONFIG_SHRED"
#else
# define IF_SHRED(...) __VA_ARGS__
#endif
#define IF_NOT_SHRED(...)
#ifdef MAKE_SUID
# define IF_SHUF(...) __VA_ARGS__ "CONFIG_SHUF"
#else
# define IF_SHUF(...) __VA_ARGS__
#endif
#define IF_NOT_SHUF(...)
#ifdef MAKE_SUID
# define IF_SLEEP(...) __VA_ARGS__ "CONFIG_SLEEP"
#else
# define IF_SLEEP(...) __VA_ARGS__
#endif
#define IF_NOT_SLEEP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FANCY_SLEEP(...) __VA_ARGS__ "CONFIG_FEATURE_FANCY_SLEEP"
#else
# define IF_FEATURE_FANCY_SLEEP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FANCY_SLEEP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FLOAT_SLEEP(...) __VA_ARGS__ "CONFIG_FEATURE_FLOAT_SLEEP"
#else
# define IF_FEATURE_FLOAT_SLEEP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FLOAT_SLEEP(...)
#ifdef MAKE_SUID
# define IF_SORT(...) __VA_ARGS__ "CONFIG_SORT"
#else
# define IF_SORT(...) __VA_ARGS__
#endif
#define IF_NOT_SORT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SORT_BIG(...) __VA_ARGS__ "CONFIG_FEATURE_SORT_BIG"
#else
# define IF_FEATURE_SORT_BIG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SORT_BIG(...)
#ifdef MAKE_SUID
# define IF_SPLIT(...) __VA_ARGS__ "CONFIG_SPLIT"
#else
# define IF_SPLIT(...) __VA_ARGS__
#endif
#define IF_NOT_SPLIT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SPLIT_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_SPLIT_FANCY"
#else
# define IF_FEATURE_SPLIT_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SPLIT_FANCY(...)
#ifdef MAKE_SUID
# define IF_STAT(...) __VA_ARGS__ "CONFIG_STAT"
#else
# define IF_STAT(...) __VA_ARGS__
#endif
#define IF_NOT_STAT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_STAT_FORMAT(...) __VA_ARGS__ "CONFIG_FEATURE_STAT_FORMAT"
#else
# define IF_FEATURE_STAT_FORMAT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_STAT_FORMAT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_STAT_FILESYSTEM(...) __VA_ARGS__ "CONFIG_FEATURE_STAT_FILESYSTEM"
#else
# define IF_FEATURE_STAT_FILESYSTEM(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_STAT_FILESYSTEM(...)
#ifdef MAKE_SUID
# define IF_STTY(...) __VA_ARGS__ "CONFIG_STTY"
#else
# define IF_STTY(...) __VA_ARGS__
#endif
#define IF_NOT_STTY(...)
#ifdef MAKE_SUID
# define IF_SUM(...) __VA_ARGS__ "CONFIG_SUM"
#else
# define IF_SUM(...) __VA_ARGS__
#endif
#define IF_NOT_SUM(...)
#ifdef MAKE_SUID
# define IF_SYNC(...) __VA_ARGS__ "CONFIG_SYNC"
#else
# define IF_SYNC(...) __VA_ARGS__
#endif
#define IF_NOT_SYNC(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SYNC_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_SYNC_FANCY"
#else
# define IF_FEATURE_SYNC_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SYNC_FANCY(...)
#ifdef MAKE_SUID
# define IF_TAC(...) __VA_ARGS__ "CONFIG_TAC"
#else
# define IF_TAC(...) __VA_ARGS__
#endif
#define IF_NOT_TAC(...)
#ifdef MAKE_SUID
# define IF_TAIL(...) __VA_ARGS__ "CONFIG_TAIL"
#else
# define IF_TAIL(...) __VA_ARGS__
#endif
#define IF_NOT_TAIL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FANCY_TAIL(...) __VA_ARGS__ "CONFIG_FEATURE_FANCY_TAIL"
#else
# define IF_FEATURE_FANCY_TAIL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FANCY_TAIL(...)
#ifdef MAKE_SUID
# define IF_TEE(...) __VA_ARGS__ "CONFIG_TEE"
#else
# define IF_TEE(...) __VA_ARGS__
#endif
#define IF_NOT_TEE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TEE_USE_BLOCK_IO(...) __VA_ARGS__ "CONFIG_FEATURE_TEE_USE_BLOCK_IO"
#else
# define IF_FEATURE_TEE_USE_BLOCK_IO(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TEE_USE_BLOCK_IO(...)
#ifdef MAKE_SUID
# define IF_TEST(...) __VA_ARGS__ "CONFIG_TEST"
#else
# define IF_TEST(...) __VA_ARGS__
#endif
#define IF_NOT_TEST(...)
#ifdef MAKE_SUID
# define IF_TEST1(...) __VA_ARGS__ "CONFIG_TEST1"
#else
# define IF_TEST1(...) __VA_ARGS__
#endif
#define IF_NOT_TEST1(...)
#ifdef MAKE_SUID
# define IF_TEST2(...) __VA_ARGS__ "CONFIG_TEST2"
#else
# define IF_TEST2(...) __VA_ARGS__
#endif
#define IF_NOT_TEST2(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TEST_64(...) __VA_ARGS__ "CONFIG_FEATURE_TEST_64"
#else
# define IF_FEATURE_TEST_64(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TEST_64(...)
#ifdef MAKE_SUID
# define IF_TIMEOUT(...) __VA_ARGS__ "CONFIG_TIMEOUT"
#else
# define IF_TIMEOUT(...) __VA_ARGS__
#endif
#define IF_NOT_TIMEOUT(...)
#ifdef MAKE_SUID
# define IF_TOUCH(...) __VA_ARGS__ "CONFIG_TOUCH"
#else
# define IF_TOUCH(...) __VA_ARGS__
#endif
#define IF_NOT_TOUCH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TOUCH_NODEREF(...) __VA_ARGS__ "CONFIG_FEATURE_TOUCH_NODEREF"
#else
# define IF_FEATURE_TOUCH_NODEREF(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TOUCH_NODEREF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TOUCH_SUSV3(...) __VA_ARGS__ "CONFIG_FEATURE_TOUCH_SUSV3"
#else
# define IF_FEATURE_TOUCH_SUSV3(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TOUCH_SUSV3(...)
#ifdef MAKE_SUID
# define IF_TR(...) __VA_ARGS__ "CONFIG_TR"
#else
# define IF_TR(...) __VA_ARGS__
#endif
#define IF_NOT_TR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TR_CLASSES(...) __VA_ARGS__ "CONFIG_FEATURE_TR_CLASSES"
#else
# define IF_FEATURE_TR_CLASSES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TR_CLASSES(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TR_EQUIV(...) __VA_ARGS__ "CONFIG_FEATURE_TR_EQUIV"
#else
# define IF_FEATURE_TR_EQUIV(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TR_EQUIV(...)
#ifdef MAKE_SUID
# define IF_TRUE(...) __VA_ARGS__ "CONFIG_TRUE"
#else
# define IF_TRUE(...) __VA_ARGS__
#endif
#define IF_NOT_TRUE(...)
#ifdef MAKE_SUID
# define IF_TRUNCATE(...) __VA_ARGS__ "CONFIG_TRUNCATE"
#else
# define IF_TRUNCATE(...) __VA_ARGS__
#endif
#define IF_NOT_TRUNCATE(...)
#ifdef MAKE_SUID
# define IF_TTY(...) __VA_ARGS__ "CONFIG_TTY"
#else
# define IF_TTY(...) __VA_ARGS__
#endif
#define IF_NOT_TTY(...)
#ifdef MAKE_SUID
# define IF_UNAME(...) __VA_ARGS__ "CONFIG_UNAME"
#else
# define IF_UNAME(...) __VA_ARGS__
#endif
#define IF_NOT_UNAME(...)
#ifdef MAKE_SUID
# define IF_UNAME_OSNAME(...) __VA_ARGS__ "CONFIG_UNAME_OSNAME"
#else
# define IF_UNAME_OSNAME(...) __VA_ARGS__
#endif
#define IF_NOT_UNAME_OSNAME(...)
#ifdef MAKE_SUID
# define IF_BB_ARCH(...) __VA_ARGS__ "CONFIG_BB_ARCH"
#else
# define IF_BB_ARCH(...) __VA_ARGS__
#endif
#define IF_NOT_BB_ARCH(...)
#ifdef MAKE_SUID
# define IF_UNIQ(...) __VA_ARGS__ "CONFIG_UNIQ"
#else
# define IF_UNIQ(...) __VA_ARGS__
#endif
#define IF_NOT_UNIQ(...)
#ifdef MAKE_SUID
# define IF_UNLINK(...) __VA_ARGS__ "CONFIG_UNLINK"
#else
# define IF_UNLINK(...) __VA_ARGS__
#endif
#define IF_NOT_UNLINK(...)
#ifdef MAKE_SUID
# define IF_USLEEP(...) __VA_ARGS__ "CONFIG_USLEEP"
#else
# define IF_USLEEP(...) __VA_ARGS__
#endif
#define IF_NOT_USLEEP(...)
#ifdef MAKE_SUID
# define IF_UUDECODE(...) __VA_ARGS__ "CONFIG_UUDECODE"
#else
# define IF_UUDECODE(...) __VA_ARGS__
#endif
#define IF_NOT_UUDECODE(...)
#ifdef MAKE_SUID
# define IF_BASE64(...) __VA_ARGS__ "CONFIG_BASE64"
#else
# define IF_BASE64(...) __VA_ARGS__
#endif
#define IF_NOT_BASE64(...)
#ifdef MAKE_SUID
# define IF_UUENCODE(...) __VA_ARGS__ "CONFIG_UUENCODE"
#else
# define IF_UUENCODE(...) __VA_ARGS__
#endif
#define IF_NOT_UUENCODE(...)
#ifdef MAKE_SUID
# define IF_WC(...) __VA_ARGS__ "CONFIG_WC"
#else
# define IF_WC(...) __VA_ARGS__
#endif
#define IF_NOT_WC(...)
#ifdef MAKE_SUID
# define IF_FEATURE_WC_LARGE(...) __VA_ARGS__ "CONFIG_FEATURE_WC_LARGE"
#else
# define IF_FEATURE_WC_LARGE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_WC_LARGE(...)
#ifdef MAKE_SUID
# define IF_WHO(...) __VA_ARGS__ "CONFIG_WHO"
#else
# define IF_WHO(...) __VA_ARGS__
#endif
#define IF_NOT_WHO(...)
#ifdef MAKE_SUID
# define IF_W(...) __VA_ARGS__ "CONFIG_W"
#else
# define IF_W(...) __VA_ARGS__
#endif
#define IF_NOT_W(...)
#ifdef MAKE_SUID
# define IF_USERS(...) __VA_ARGS__ "CONFIG_USERS"
#else
# define IF_USERS(...) __VA_ARGS__
#endif
#define IF_NOT_USERS(...)
#ifdef MAKE_SUID
# define IF_WHOAMI(...) __VA_ARGS__ "CONFIG_WHOAMI"
#else
# define IF_WHOAMI(...) __VA_ARGS__
#endif
#define IF_NOT_WHOAMI(...)
#ifdef MAKE_SUID
# define IF_YES(...) __VA_ARGS__ "CONFIG_YES"
#else
# define IF_YES(...) __VA_ARGS__
#endif
#define IF_NOT_YES(...)

/*
 * Common options
 */
#ifdef MAKE_SUID
# define IF_FEATURE_VERBOSE(...) __VA_ARGS__ "CONFIG_FEATURE_VERBOSE"
#else
# define IF_FEATURE_VERBOSE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VERBOSE(...)

/*
 * Common options for cp and mv
 */
#ifdef MAKE_SUID
# define IF_FEATURE_PRESERVE_HARDLINKS(...) __VA_ARGS__ "CONFIG_FEATURE_PRESERVE_HARDLINKS"
#else
# define IF_FEATURE_PRESERVE_HARDLINKS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_PRESERVE_HARDLINKS(...)

/*
 * Common options for df, du, ls
 */
#ifdef MAKE_SUID
# define IF_FEATURE_HUMAN_READABLE(...) __VA_ARGS__ "CONFIG_FEATURE_HUMAN_READABLE"
#else
# define IF_FEATURE_HUMAN_READABLE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HUMAN_READABLE(...)

/*
 * Console Utilities
 */
#ifdef MAKE_SUID
# define IF_CHVT(...) __VA_ARGS__ "CONFIG_CHVT"
#else
# define IF_CHVT(...) __VA_ARGS__
#endif
#define IF_NOT_CHVT(...)
#ifdef MAKE_SUID
# define IF_CLEAR(...) __VA_ARGS__ "CONFIG_CLEAR"
#else
# define IF_CLEAR(...) __VA_ARGS__
#endif
#define IF_NOT_CLEAR(...)
#ifdef MAKE_SUID
# define IF_DEALLOCVT(...) __VA_ARGS__ "CONFIG_DEALLOCVT"
#else
# define IF_DEALLOCVT(...) __VA_ARGS__
#endif
#define IF_NOT_DEALLOCVT(...)
#ifdef MAKE_SUID
# define IF_DUMPKMAP(...) __VA_ARGS__ "CONFIG_DUMPKMAP"
#else
# define IF_DUMPKMAP(...) __VA_ARGS__
#endif
#define IF_NOT_DUMPKMAP(...)
#ifdef MAKE_SUID
# define IF_FGCONSOLE(...) __VA_ARGS__ "CONFIG_FGCONSOLE"
#else
# define IF_FGCONSOLE(...) __VA_ARGS__
#endif
#define IF_NOT_FGCONSOLE(...)
#ifdef MAKE_SUID
# define IF_KBD_MODE(...) __VA_ARGS__ "CONFIG_KBD_MODE"
#else
# define IF_KBD_MODE(...) __VA_ARGS__
#endif
#define IF_NOT_KBD_MODE(...)
#ifdef MAKE_SUID
# define IF_LOADFONT(...) __VA_ARGS__ "CONFIG_LOADFONT"
#else
# define IF_LOADFONT(...) __VA_ARGS__
#endif
#define IF_NOT_LOADFONT(...)
#ifdef MAKE_SUID
# define IF_SETFONT(...) __VA_ARGS__ "CONFIG_SETFONT"
#else
# define IF_SETFONT(...) __VA_ARGS__
#endif
#define IF_NOT_SETFONT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SETFONT_TEXTUAL_MAP(...) __VA_ARGS__ "CONFIG_FEATURE_SETFONT_TEXTUAL_MAP"
#else
# define IF_FEATURE_SETFONT_TEXTUAL_MAP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SETFONT_TEXTUAL_MAP(...)
#ifdef MAKE_SUID
# define IF_DEFAULT_SETFONT_DIR(...) __VA_ARGS__ "CONFIG_DEFAULT_SETFONT_DIR"
#else
# define IF_DEFAULT_SETFONT_DIR(...) __VA_ARGS__
#endif
#define IF_NOT_DEFAULT_SETFONT_DIR(...)

/*
 * Common options for loadfont and setfont
 */
#ifdef MAKE_SUID
# define IF_FEATURE_LOADFONT_PSF2(...) __VA_ARGS__ "CONFIG_FEATURE_LOADFONT_PSF2"
#else
# define IF_FEATURE_LOADFONT_PSF2(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LOADFONT_PSF2(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LOADFONT_RAW(...) __VA_ARGS__ "CONFIG_FEATURE_LOADFONT_RAW"
#else
# define IF_FEATURE_LOADFONT_RAW(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LOADFONT_RAW(...)
#ifdef MAKE_SUID
# define IF_LOADKMAP(...) __VA_ARGS__ "CONFIG_LOADKMAP"
#else
# define IF_LOADKMAP(...) __VA_ARGS__
#endif
#define IF_NOT_LOADKMAP(...)
#ifdef MAKE_SUID
# define IF_OPENVT(...) __VA_ARGS__ "CONFIG_OPENVT"
#else
# define IF_OPENVT(...) __VA_ARGS__
#endif
#define IF_NOT_OPENVT(...)
#ifdef MAKE_SUID
# define IF_RESET(...) __VA_ARGS__ "CONFIG_RESET"
#else
# define IF_RESET(...) __VA_ARGS__
#endif
#define IF_NOT_RESET(...)
#ifdef MAKE_SUID
# define IF_RESIZE(...) __VA_ARGS__ "CONFIG_RESIZE"
#else
# define IF_RESIZE(...) __VA_ARGS__
#endif
#define IF_NOT_RESIZE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_RESIZE_PRINT(...) __VA_ARGS__ "CONFIG_FEATURE_RESIZE_PRINT"
#else
# define IF_FEATURE_RESIZE_PRINT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_RESIZE_PRINT(...)
#ifdef MAKE_SUID
# define IF_SETCONSOLE(...) __VA_ARGS__ "CONFIG_SETCONSOLE"
#else
# define IF_SETCONSOLE(...) __VA_ARGS__
#endif
#define IF_NOT_SETCONSOLE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SETCONSOLE_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_SETCONSOLE_LONG_OPTIONS"
#else
# define IF_FEATURE_SETCONSOLE_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SETCONSOLE_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_SETKEYCODES(...) __VA_ARGS__ "CONFIG_SETKEYCODES"
#else
# define IF_SETKEYCODES(...) __VA_ARGS__
#endif
#define IF_NOT_SETKEYCODES(...)
#ifdef MAKE_SUID
# define IF_SETLOGCONS(...) __VA_ARGS__ "CONFIG_SETLOGCONS"
#else
# define IF_SETLOGCONS(...) __VA_ARGS__
#endif
#define IF_NOT_SETLOGCONS(...)
#ifdef MAKE_SUID
# define IF_SHOWKEY(...) __VA_ARGS__ "CONFIG_SHOWKEY"
#else
# define IF_SHOWKEY(...) __VA_ARGS__
#endif
#define IF_NOT_SHOWKEY(...)

/*
 * Debian Utilities
 */
#ifdef MAKE_SUID
# define IF_PIPE_PROGRESS(...) __VA_ARGS__ "CONFIG_PIPE_PROGRESS"
#else
# define IF_PIPE_PROGRESS(...) __VA_ARGS__
#endif
#define IF_NOT_PIPE_PROGRESS(...)
#ifdef MAKE_SUID
# define IF_RUN_PARTS(...) __VA_ARGS__ "CONFIG_RUN_PARTS"
#else
# define IF_RUN_PARTS(...) __VA_ARGS__
#endif
#define IF_NOT_RUN_PARTS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_RUN_PARTS_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_RUN_PARTS_LONG_OPTIONS"
#else
# define IF_FEATURE_RUN_PARTS_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_RUN_PARTS_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_RUN_PARTS_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_RUN_PARTS_FANCY"
#else
# define IF_FEATURE_RUN_PARTS_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_RUN_PARTS_FANCY(...)
#ifdef MAKE_SUID
# define IF_START_STOP_DAEMON(...) __VA_ARGS__ "CONFIG_START_STOP_DAEMON"
#else
# define IF_START_STOP_DAEMON(...) __VA_ARGS__
#endif
#define IF_NOT_START_STOP_DAEMON(...)
#ifdef MAKE_SUID
# define IF_FEATURE_START_STOP_DAEMON_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_START_STOP_DAEMON_LONG_OPTIONS"
#else
# define IF_FEATURE_START_STOP_DAEMON_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_START_STOP_DAEMON_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_START_STOP_DAEMON_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_START_STOP_DAEMON_FANCY"
#else
# define IF_FEATURE_START_STOP_DAEMON_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_START_STOP_DAEMON_FANCY(...)
#ifdef MAKE_SUID
# define IF_WHICH(...) __VA_ARGS__ "CONFIG_WHICH"
#else
# define IF_WHICH(...) __VA_ARGS__
#endif
#define IF_NOT_WHICH(...)

/*
 * klibc-utils
 */
#define IF_MINIPS(...)
#define IF_NOT_MINIPS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_NUKE(...) __VA_ARGS__ "CONFIG_NUKE"
#else
# define IF_NUKE(...) __VA_ARGS__
#endif
#define IF_NOT_NUKE(...)
#ifdef MAKE_SUID
# define IF_RESUME(...) __VA_ARGS__ "CONFIG_RESUME"
#else
# define IF_RESUME(...) __VA_ARGS__
#endif
#define IF_NOT_RESUME(...)
#ifdef MAKE_SUID
# define IF_RUN_INIT(...) __VA_ARGS__ "CONFIG_RUN_INIT"
#else
# define IF_RUN_INIT(...) __VA_ARGS__
#endif
#define IF_NOT_RUN_INIT(...)

/*
 * Editors
 */
#ifdef MAKE_SUID
# define IF_AWK(...) __VA_ARGS__ "CONFIG_AWK"
#else
# define IF_AWK(...) __VA_ARGS__
#endif
#define IF_NOT_AWK(...)
#ifdef MAKE_SUID
# define IF_FEATURE_AWK_LIBM(...) __VA_ARGS__ "CONFIG_FEATURE_AWK_LIBM"
#else
# define IF_FEATURE_AWK_LIBM(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_AWK_LIBM(...)
#ifdef MAKE_SUID
# define IF_FEATURE_AWK_GNU_EXTENSIONS(...) __VA_ARGS__ "CONFIG_FEATURE_AWK_GNU_EXTENSIONS"
#else
# define IF_FEATURE_AWK_GNU_EXTENSIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_AWK_GNU_EXTENSIONS(...)
#ifdef MAKE_SUID
# define IF_CMP(...) __VA_ARGS__ "CONFIG_CMP"
#else
# define IF_CMP(...) __VA_ARGS__
#endif
#define IF_NOT_CMP(...)
#ifdef MAKE_SUID
# define IF_DIFF(...) __VA_ARGS__ "CONFIG_DIFF"
#else
# define IF_DIFF(...) __VA_ARGS__
#endif
#define IF_NOT_DIFF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DIFF_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_DIFF_LONG_OPTIONS"
#else
# define IF_FEATURE_DIFF_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DIFF_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DIFF_DIR(...) __VA_ARGS__ "CONFIG_FEATURE_DIFF_DIR"
#else
# define IF_FEATURE_DIFF_DIR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DIFF_DIR(...)
#ifdef MAKE_SUID
# define IF_ED(...) __VA_ARGS__ "CONFIG_ED"
#else
# define IF_ED(...) __VA_ARGS__
#endif
#define IF_NOT_ED(...)
#ifdef MAKE_SUID
# define IF_PATCH(...) __VA_ARGS__ "CONFIG_PATCH"
#else
# define IF_PATCH(...) __VA_ARGS__
#endif
#define IF_NOT_PATCH(...)
#ifdef MAKE_SUID
# define IF_SED(...) __VA_ARGS__ "CONFIG_SED"
#else
# define IF_SED(...) __VA_ARGS__
#endif
#define IF_NOT_SED(...)
#ifdef MAKE_SUID
# define IF_VI(...) __VA_ARGS__ "CONFIG_VI"
#else
# define IF_VI(...) __VA_ARGS__
#endif
#define IF_NOT_VI(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_MAX_LEN(...) __VA_ARGS__ "CONFIG_FEATURE_VI_MAX_LEN"
#else
# define IF_FEATURE_VI_MAX_LEN(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_MAX_LEN(...)
#define IF_FEATURE_VI_8BIT(...)
#define IF_NOT_FEATURE_VI_8BIT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_VI_COLON(...) __VA_ARGS__ "CONFIG_FEATURE_VI_COLON"
#else
# define IF_FEATURE_VI_COLON(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_COLON(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_YANKMARK(...) __VA_ARGS__ "CONFIG_FEATURE_VI_YANKMARK"
#else
# define IF_FEATURE_VI_YANKMARK(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_YANKMARK(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_SEARCH(...) __VA_ARGS__ "CONFIG_FEATURE_VI_SEARCH"
#else
# define IF_FEATURE_VI_SEARCH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_SEARCH(...)
#define IF_FEATURE_VI_REGEX_SEARCH(...)
#define IF_NOT_FEATURE_VI_REGEX_SEARCH(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_VI_USE_SIGNALS(...) __VA_ARGS__ "CONFIG_FEATURE_VI_USE_SIGNALS"
#else
# define IF_FEATURE_VI_USE_SIGNALS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_USE_SIGNALS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_DOT_CMD(...) __VA_ARGS__ "CONFIG_FEATURE_VI_DOT_CMD"
#else
# define IF_FEATURE_VI_DOT_CMD(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_DOT_CMD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_READONLY(...) __VA_ARGS__ "CONFIG_FEATURE_VI_READONLY"
#else
# define IF_FEATURE_VI_READONLY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_READONLY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_SETOPTS(...) __VA_ARGS__ "CONFIG_FEATURE_VI_SETOPTS"
#else
# define IF_FEATURE_VI_SETOPTS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_SETOPTS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_SET(...) __VA_ARGS__ "CONFIG_FEATURE_VI_SET"
#else
# define IF_FEATURE_VI_SET(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_SET(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_WIN_RESIZE(...) __VA_ARGS__ "CONFIG_FEATURE_VI_WIN_RESIZE"
#else
# define IF_FEATURE_VI_WIN_RESIZE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_WIN_RESIZE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_ASK_TERMINAL(...) __VA_ARGS__ "CONFIG_FEATURE_VI_ASK_TERMINAL"
#else
# define IF_FEATURE_VI_ASK_TERMINAL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_ASK_TERMINAL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_UNDO(...) __VA_ARGS__ "CONFIG_FEATURE_VI_UNDO"
#else
# define IF_FEATURE_VI_UNDO(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_UNDO(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_UNDO_QUEUE(...) __VA_ARGS__ "CONFIG_FEATURE_VI_UNDO_QUEUE"
#else
# define IF_FEATURE_VI_UNDO_QUEUE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_UNDO_QUEUE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VI_UNDO_QUEUE_MAX(...) __VA_ARGS__ "CONFIG_FEATURE_VI_UNDO_QUEUE_MAX"
#else
# define IF_FEATURE_VI_UNDO_QUEUE_MAX(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VI_UNDO_QUEUE_MAX(...)
#ifdef MAKE_SUID
# define IF_FEATURE_ALLOW_EXEC(...) __VA_ARGS__ "CONFIG_FEATURE_ALLOW_EXEC"
#else
# define IF_FEATURE_ALLOW_EXEC(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_ALLOW_EXEC(...)

/*
 * Finding Utilities
 */
#ifdef MAKE_SUID
# define IF_FIND(...) __VA_ARGS__ "CONFIG_FIND"
#else
# define IF_FIND(...) __VA_ARGS__
#endif
#define IF_NOT_FIND(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_PRINT0(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_PRINT0"
#else
# define IF_FEATURE_FIND_PRINT0(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_PRINT0(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_MTIME(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_MTIME"
#else
# define IF_FEATURE_FIND_MTIME(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_MTIME(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_MMIN(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_MMIN"
#else
# define IF_FEATURE_FIND_MMIN(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_MMIN(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_PERM(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_PERM"
#else
# define IF_FEATURE_FIND_PERM(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_PERM(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_TYPE(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_TYPE"
#else
# define IF_FEATURE_FIND_TYPE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_TYPE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_XDEV(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_XDEV"
#else
# define IF_FEATURE_FIND_XDEV(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_XDEV(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_MAXDEPTH(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_MAXDEPTH"
#else
# define IF_FEATURE_FIND_MAXDEPTH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_MAXDEPTH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_NEWER(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_NEWER"
#else
# define IF_FEATURE_FIND_NEWER(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_NEWER(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_INUM(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_INUM"
#else
# define IF_FEATURE_FIND_INUM(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_INUM(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_EXEC(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_EXEC"
#else
# define IF_FEATURE_FIND_EXEC(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_EXEC(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_EXEC_PLUS(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_EXEC_PLUS"
#else
# define IF_FEATURE_FIND_EXEC_PLUS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_EXEC_PLUS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_USER(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_USER"
#else
# define IF_FEATURE_FIND_USER(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_USER(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_GROUP(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_GROUP"
#else
# define IF_FEATURE_FIND_GROUP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_GROUP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_NOT(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_NOT"
#else
# define IF_FEATURE_FIND_NOT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_NOT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_DEPTH(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_DEPTH"
#else
# define IF_FEATURE_FIND_DEPTH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_DEPTH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_PAREN(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_PAREN"
#else
# define IF_FEATURE_FIND_PAREN(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_PAREN(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_SIZE(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_SIZE"
#else
# define IF_FEATURE_FIND_SIZE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_SIZE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_PRUNE(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_PRUNE"
#else
# define IF_FEATURE_FIND_PRUNE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_PRUNE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_DELETE(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_DELETE"
#else
# define IF_FEATURE_FIND_DELETE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_DELETE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_PATH(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_PATH"
#else
# define IF_FEATURE_FIND_PATH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_PATH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_REGEX(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_REGEX"
#else
# define IF_FEATURE_FIND_REGEX(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_REGEX(...)
#define IF_FEATURE_FIND_CONTEXT(...)
#define IF_NOT_FEATURE_FIND_CONTEXT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_FIND_LINKS(...) __VA_ARGS__ "CONFIG_FEATURE_FIND_LINKS"
#else
# define IF_FEATURE_FIND_LINKS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FIND_LINKS(...)
#ifdef MAKE_SUID
# define IF_GREP(...) __VA_ARGS__ "CONFIG_GREP"
#else
# define IF_GREP(...) __VA_ARGS__
#endif
#define IF_NOT_GREP(...)
#ifdef MAKE_SUID
# define IF_EGREP(...) __VA_ARGS__ "CONFIG_EGREP"
#else
# define IF_EGREP(...) __VA_ARGS__
#endif
#define IF_NOT_EGREP(...)
#ifdef MAKE_SUID
# define IF_FGREP(...) __VA_ARGS__ "CONFIG_FGREP"
#else
# define IF_FGREP(...) __VA_ARGS__
#endif
#define IF_NOT_FGREP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_GREP_CONTEXT(...) __VA_ARGS__ "CONFIG_FEATURE_GREP_CONTEXT"
#else
# define IF_FEATURE_GREP_CONTEXT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_GREP_CONTEXT(...)
#ifdef MAKE_SUID
# define IF_XARGS(...) __VA_ARGS__ "CONFIG_XARGS"
#else
# define IF_XARGS(...) __VA_ARGS__
#endif
#define IF_NOT_XARGS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_XARGS_SUPPORT_CONFIRMATION(...) __VA_ARGS__ "CONFIG_FEATURE_XARGS_SUPPORT_CONFIRMATION"
#else
# define IF_FEATURE_XARGS_SUPPORT_CONFIRMATION(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_XARGS_SUPPORT_CONFIRMATION(...)
#ifdef MAKE_SUID
# define IF_FEATURE_XARGS_SUPPORT_QUOTES(...) __VA_ARGS__ "CONFIG_FEATURE_XARGS_SUPPORT_QUOTES"
#else
# define IF_FEATURE_XARGS_SUPPORT_QUOTES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_XARGS_SUPPORT_QUOTES(...)
#ifdef MAKE_SUID
# define IF_FEATURE_XARGS_SUPPORT_TERMOPT(...) __VA_ARGS__ "CONFIG_FEATURE_XARGS_SUPPORT_TERMOPT"
#else
# define IF_FEATURE_XARGS_SUPPORT_TERMOPT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_XARGS_SUPPORT_TERMOPT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_XARGS_SUPPORT_ZERO_TERM(...) __VA_ARGS__ "CONFIG_FEATURE_XARGS_SUPPORT_ZERO_TERM"
#else
# define IF_FEATURE_XARGS_SUPPORT_ZERO_TERM(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_XARGS_SUPPORT_ZERO_TERM(...)
#ifdef MAKE_SUID
# define IF_FEATURE_XARGS_SUPPORT_REPL_STR(...) __VA_ARGS__ "CONFIG_FEATURE_XARGS_SUPPORT_REPL_STR"
#else
# define IF_FEATURE_XARGS_SUPPORT_REPL_STR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_XARGS_SUPPORT_REPL_STR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_XARGS_SUPPORT_PARALLEL(...) __VA_ARGS__ "CONFIG_FEATURE_XARGS_SUPPORT_PARALLEL"
#else
# define IF_FEATURE_XARGS_SUPPORT_PARALLEL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_XARGS_SUPPORT_PARALLEL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_XARGS_SUPPORT_ARGS_FILE(...) __VA_ARGS__ "CONFIG_FEATURE_XARGS_SUPPORT_ARGS_FILE"
#else
# define IF_FEATURE_XARGS_SUPPORT_ARGS_FILE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_XARGS_SUPPORT_ARGS_FILE(...)

/*
 * Init Utilities
 */
#ifdef MAKE_SUID
# define IF_BOOTCHARTD(...) __VA_ARGS__ "CONFIG_BOOTCHARTD"
#else
# define IF_BOOTCHARTD(...) __VA_ARGS__
#endif
#define IF_NOT_BOOTCHARTD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_BOOTCHARTD_BLOATED_HEADER(...) __VA_ARGS__ "CONFIG_FEATURE_BOOTCHARTD_BLOATED_HEADER"
#else
# define IF_FEATURE_BOOTCHARTD_BLOATED_HEADER(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_BOOTCHARTD_BLOATED_HEADER(...)
#ifdef MAKE_SUID
# define IF_FEATURE_BOOTCHARTD_CONFIG_FILE(...) __VA_ARGS__ "CONFIG_FEATURE_BOOTCHARTD_CONFIG_FILE"
#else
# define IF_FEATURE_BOOTCHARTD_CONFIG_FILE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_BOOTCHARTD_CONFIG_FILE(...)
#ifdef MAKE_SUID
# define IF_HALT(...) __VA_ARGS__ "CONFIG_HALT"
#else
# define IF_HALT(...) __VA_ARGS__
#endif
#define IF_NOT_HALT(...)
#ifdef MAKE_SUID
# define IF_POWEROFF(...) __VA_ARGS__ "CONFIG_POWEROFF"
#else
# define IF_POWEROFF(...) __VA_ARGS__
#endif
#define IF_NOT_POWEROFF(...)
#ifdef MAKE_SUID
# define IF_REBOOT(...) __VA_ARGS__ "CONFIG_REBOOT"
#else
# define IF_REBOOT(...) __VA_ARGS__
#endif
#define IF_NOT_REBOOT(...)
#define IF_FEATURE_CALL_TELINIT(...)
#define IF_NOT_FEATURE_CALL_TELINIT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_TELINIT_PATH(...) __VA_ARGS__ "CONFIG_TELINIT_PATH"
#else
# define IF_TELINIT_PATH(...) __VA_ARGS__
#endif
#define IF_NOT_TELINIT_PATH(...)
#ifdef MAKE_SUID
# define IF_INIT(...) __VA_ARGS__ "CONFIG_INIT"
#else
# define IF_INIT(...) __VA_ARGS__
#endif
#define IF_NOT_INIT(...)
#ifdef MAKE_SUID
# define IF_LINUXRC(...) __VA_ARGS__ "CONFIG_LINUXRC"
#else
# define IF_LINUXRC(...) __VA_ARGS__
#endif
#define IF_NOT_LINUXRC(...)
#ifdef MAKE_SUID
# define IF_FEATURE_USE_INITTAB(...) __VA_ARGS__ "CONFIG_FEATURE_USE_INITTAB"
#else
# define IF_FEATURE_USE_INITTAB(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_USE_INITTAB(...)
#define IF_FEATURE_KILL_REMOVED(...)
#define IF_NOT_FEATURE_KILL_REMOVED(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_KILL_DELAY(...) __VA_ARGS__ "CONFIG_FEATURE_KILL_DELAY"
#else
# define IF_FEATURE_KILL_DELAY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_KILL_DELAY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INIT_SCTTY(...) __VA_ARGS__ "CONFIG_FEATURE_INIT_SCTTY"
#else
# define IF_FEATURE_INIT_SCTTY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INIT_SCTTY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INIT_SYSLOG(...) __VA_ARGS__ "CONFIG_FEATURE_INIT_SYSLOG"
#else
# define IF_FEATURE_INIT_SYSLOG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INIT_SYSLOG(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INIT_QUIET(...) __VA_ARGS__ "CONFIG_FEATURE_INIT_QUIET"
#else
# define IF_FEATURE_INIT_QUIET(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INIT_QUIET(...)
#define IF_FEATURE_INIT_COREDUMPS(...)
#define IF_NOT_FEATURE_INIT_COREDUMPS(...) __VA_ARGS__
#define CONFIG_INIT_TERMINAL_TYPE "linux"
#ifdef MAKE_SUID
# define IF_INIT_TERMINAL_TYPE(...) __VA_ARGS__ "CONFIG_INIT_TERMINAL_TYPE"
#else
# define IF_INIT_TERMINAL_TYPE(...) __VA_ARGS__
#endif
#define IF_NOT_INIT_TERMINAL_TYPE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INIT_MODIFY_CMDLINE(...) __VA_ARGS__ "CONFIG_FEATURE_INIT_MODIFY_CMDLINE"
#else
# define IF_FEATURE_INIT_MODIFY_CMDLINE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INIT_MODIFY_CMDLINE(...)

/*
 * Login/Password Management Utilities
 */
#ifdef MAKE_SUID
# define IF_FEATURE_SHADOWPASSWDS(...) __VA_ARGS__ "CONFIG_FEATURE_SHADOWPASSWDS"
#else
# define IF_FEATURE_SHADOWPASSWDS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SHADOWPASSWDS(...)
#ifdef MAKE_SUID
# define IF_USE_BB_PWD_GRP(...) __VA_ARGS__ "CONFIG_USE_BB_PWD_GRP"
#else
# define IF_USE_BB_PWD_GRP(...) __VA_ARGS__
#endif
#define IF_NOT_USE_BB_PWD_GRP(...)
#ifdef MAKE_SUID
# define IF_USE_BB_SHADOW(...) __VA_ARGS__ "CONFIG_USE_BB_SHADOW"
#else
# define IF_USE_BB_SHADOW(...) __VA_ARGS__
#endif
#define IF_NOT_USE_BB_SHADOW(...)
#ifdef MAKE_SUID
# define IF_USE_BB_CRYPT(...) __VA_ARGS__ "CONFIG_USE_BB_CRYPT"
#else
# define IF_USE_BB_CRYPT(...) __VA_ARGS__
#endif
#define IF_NOT_USE_BB_CRYPT(...)
#ifdef MAKE_SUID
# define IF_USE_BB_CRYPT_SHA(...) __VA_ARGS__ "CONFIG_USE_BB_CRYPT_SHA"
#else
# define IF_USE_BB_CRYPT_SHA(...) __VA_ARGS__
#endif
#define IF_NOT_USE_BB_CRYPT_SHA(...)
#ifdef MAKE_SUID
# define IF_ADD_SHELL(...) __VA_ARGS__ "CONFIG_ADD_SHELL"
#else
# define IF_ADD_SHELL(...) __VA_ARGS__
#endif
#define IF_NOT_ADD_SHELL(...)
#ifdef MAKE_SUID
# define IF_REMOVE_SHELL(...) __VA_ARGS__ "CONFIG_REMOVE_SHELL"
#else
# define IF_REMOVE_SHELL(...) __VA_ARGS__
#endif
#define IF_NOT_REMOVE_SHELL(...)
#ifdef MAKE_SUID
# define IF_ADDGROUP(...) __VA_ARGS__ "CONFIG_ADDGROUP"
#else
# define IF_ADDGROUP(...) __VA_ARGS__
#endif
#define IF_NOT_ADDGROUP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_ADDUSER_TO_GROUP(...) __VA_ARGS__ "CONFIG_FEATURE_ADDUSER_TO_GROUP"
#else
# define IF_FEATURE_ADDUSER_TO_GROUP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_ADDUSER_TO_GROUP(...)
#ifdef MAKE_SUID
# define IF_ADDUSER(...) __VA_ARGS__ "CONFIG_ADDUSER"
#else
# define IF_ADDUSER(...) __VA_ARGS__
#endif
#define IF_NOT_ADDUSER(...)
#define IF_FEATURE_CHECK_NAMES(...)
#define IF_NOT_FEATURE_CHECK_NAMES(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_LAST_ID(...) __VA_ARGS__ "CONFIG_LAST_ID"
#else
# define IF_LAST_ID(...) __VA_ARGS__
#endif
#define IF_NOT_LAST_ID(...)
#ifdef MAKE_SUID
# define IF_FIRST_SYSTEM_ID(...) __VA_ARGS__ "CONFIG_FIRST_SYSTEM_ID"
#else
# define IF_FIRST_SYSTEM_ID(...) __VA_ARGS__
#endif
#define IF_NOT_FIRST_SYSTEM_ID(...)
#ifdef MAKE_SUID
# define IF_LAST_SYSTEM_ID(...) __VA_ARGS__ "CONFIG_LAST_SYSTEM_ID"
#else
# define IF_LAST_SYSTEM_ID(...) __VA_ARGS__
#endif
#define IF_NOT_LAST_SYSTEM_ID(...)
#ifdef MAKE_SUID
# define IF_CHPASSWD(...) __VA_ARGS__ "CONFIG_CHPASSWD"
#else
# define IF_CHPASSWD(...) __VA_ARGS__
#endif
#define IF_NOT_CHPASSWD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DEFAULT_PASSWD_ALGO(...) __VA_ARGS__ "CONFIG_FEATURE_DEFAULT_PASSWD_ALGO"
#else
# define IF_FEATURE_DEFAULT_PASSWD_ALGO(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DEFAULT_PASSWD_ALGO(...)
#ifdef MAKE_SUID
# define IF_CRYPTPW(...) __VA_ARGS__ "CONFIG_CRYPTPW"
#else
# define IF_CRYPTPW(...) __VA_ARGS__
#endif
#define IF_NOT_CRYPTPW(...)
#ifdef MAKE_SUID
# define IF_MKPASSWD(...) __VA_ARGS__ "CONFIG_MKPASSWD"
#else
# define IF_MKPASSWD(...) __VA_ARGS__
#endif
#define IF_NOT_MKPASSWD(...)
#ifdef MAKE_SUID
# define IF_DELUSER(...) __VA_ARGS__ "CONFIG_DELUSER"
#else
# define IF_DELUSER(...) __VA_ARGS__
#endif
#define IF_NOT_DELUSER(...)
#ifdef MAKE_SUID
# define IF_DELGROUP(...) __VA_ARGS__ "CONFIG_DELGROUP"
#else
# define IF_DELGROUP(...) __VA_ARGS__
#endif
#define IF_NOT_DELGROUP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DEL_USER_FROM_GROUP(...) __VA_ARGS__ "CONFIG_FEATURE_DEL_USER_FROM_GROUP"
#else
# define IF_FEATURE_DEL_USER_FROM_GROUP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DEL_USER_FROM_GROUP(...)
#ifdef MAKE_SUID
# define IF_GETTY(...) __VA_ARGS__ "CONFIG_GETTY"
#else
# define IF_GETTY(...) __VA_ARGS__
#endif
#define IF_NOT_GETTY(...)
#ifdef MAKE_SUID
# define IF_LOGIN(...) __VA_ARGS__ "CONFIG_LOGIN"
#else
# define IF_LOGIN(...) __VA_ARGS__
#endif
#define IF_NOT_LOGIN(...)
#define IF_LOGIN_SESSION_AS_CHILD(...)
#define IF_NOT_LOGIN_SESSION_AS_CHILD(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_LOGIN_SCRIPTS(...) __VA_ARGS__ "CONFIG_LOGIN_SCRIPTS"
#else
# define IF_LOGIN_SCRIPTS(...) __VA_ARGS__
#endif
#define IF_NOT_LOGIN_SCRIPTS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_NOLOGIN(...) __VA_ARGS__ "CONFIG_FEATURE_NOLOGIN"
#else
# define IF_FEATURE_NOLOGIN(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_NOLOGIN(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SECURETTY(...) __VA_ARGS__ "CONFIG_FEATURE_SECURETTY"
#else
# define IF_FEATURE_SECURETTY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SECURETTY(...)
#ifdef MAKE_SUID
# define IF_PASSWD(...) __VA_ARGS__ "CONFIG_PASSWD"
#else
# define IF_PASSWD(...) __VA_ARGS__
#endif
#define IF_NOT_PASSWD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_PASSWD_WEAK_CHECK(...) __VA_ARGS__ "CONFIG_FEATURE_PASSWD_WEAK_CHECK"
#else
# define IF_FEATURE_PASSWD_WEAK_CHECK(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_PASSWD_WEAK_CHECK(...)
#ifdef MAKE_SUID
# define IF_SU(...) __VA_ARGS__ "CONFIG_SU"
#else
# define IF_SU(...) __VA_ARGS__
#endif
#define IF_NOT_SU(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SU_SYSLOG(...) __VA_ARGS__ "CONFIG_FEATURE_SU_SYSLOG"
#else
# define IF_FEATURE_SU_SYSLOG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SU_SYSLOG(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SU_CHECKS_SHELLS(...) __VA_ARGS__ "CONFIG_FEATURE_SU_CHECKS_SHELLS"
#else
# define IF_FEATURE_SU_CHECKS_SHELLS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SU_CHECKS_SHELLS(...)
#define IF_FEATURE_SU_BLANK_PW_NEEDS_SECURE_TTY(...)
#define IF_NOT_FEATURE_SU_BLANK_PW_NEEDS_SECURE_TTY(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_SULOGIN(...) __VA_ARGS__ "CONFIG_SULOGIN"
#else
# define IF_SULOGIN(...) __VA_ARGS__
#endif
#define IF_NOT_SULOGIN(...)
#ifdef MAKE_SUID
# define IF_VLOCK(...) __VA_ARGS__ "CONFIG_VLOCK"
#else
# define IF_VLOCK(...) __VA_ARGS__
#endif
#define IF_NOT_VLOCK(...)

/*
 * Linux Ext2 FS Progs
 */
#ifdef MAKE_SUID
# define IF_CHATTR(...) __VA_ARGS__ "CONFIG_CHATTR"
#else
# define IF_CHATTR(...) __VA_ARGS__
#endif
#define IF_NOT_CHATTR(...)
#ifdef MAKE_SUID
# define IF_FSCK(...) __VA_ARGS__ "CONFIG_FSCK"
#else
# define IF_FSCK(...) __VA_ARGS__
#endif
#define IF_NOT_FSCK(...)
#ifdef MAKE_SUID
# define IF_LSATTR(...) __VA_ARGS__ "CONFIG_LSATTR"
#else
# define IF_LSATTR(...) __VA_ARGS__
#endif
#define IF_NOT_LSATTR(...)
#define IF_TUNE2FS(...)
#define IF_NOT_TUNE2FS(...) __VA_ARGS__

/*
 * Linux Module Utilities
 */
#ifdef MAKE_SUID
# define IF_MODPROBE_SMALL(...) __VA_ARGS__ "CONFIG_MODPROBE_SMALL"
#else
# define IF_MODPROBE_SMALL(...) __VA_ARGS__
#endif
#define IF_NOT_MODPROBE_SMALL(...)
#ifdef MAKE_SUID
# define IF_DEPMOD(...) __VA_ARGS__ "CONFIG_DEPMOD"
#else
# define IF_DEPMOD(...) __VA_ARGS__
#endif
#define IF_NOT_DEPMOD(...)
#ifdef MAKE_SUID
# define IF_INSMOD(...) __VA_ARGS__ "CONFIG_INSMOD"
#else
# define IF_INSMOD(...) __VA_ARGS__
#endif
#define IF_NOT_INSMOD(...)
#ifdef MAKE_SUID
# define IF_LSMOD(...) __VA_ARGS__ "CONFIG_LSMOD"
#else
# define IF_LSMOD(...) __VA_ARGS__
#endif
#define IF_NOT_LSMOD(...)
#define IF_FEATURE_LSMOD_PRETTY_2_6_OUTPUT(...)
#define IF_NOT_FEATURE_LSMOD_PRETTY_2_6_OUTPUT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_MODINFO(...) __VA_ARGS__ "CONFIG_MODINFO"
#else
# define IF_MODINFO(...) __VA_ARGS__
#endif
#define IF_NOT_MODINFO(...)
#ifdef MAKE_SUID
# define IF_MODPROBE(...) __VA_ARGS__ "CONFIG_MODPROBE"
#else
# define IF_MODPROBE(...) __VA_ARGS__
#endif
#define IF_NOT_MODPROBE(...)
#define IF_FEATURE_MODPROBE_BLACKLIST(...)
#define IF_NOT_FEATURE_MODPROBE_BLACKLIST(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_RMMOD(...) __VA_ARGS__ "CONFIG_RMMOD"
#else
# define IF_RMMOD(...) __VA_ARGS__
#endif
#define IF_NOT_RMMOD(...)

/*
 * Options common to multiple modutils
 */
#ifdef MAKE_SUID
# define IF_FEATURE_CMDLINE_MODULE_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_CMDLINE_MODULE_OPTIONS"
#else
# define IF_FEATURE_CMDLINE_MODULE_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CMDLINE_MODULE_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MODPROBE_SMALL_CHECK_ALREADY_LOADED(...) __VA_ARGS__ "CONFIG_FEATURE_MODPROBE_SMALL_CHECK_ALREADY_LOADED"
#else
# define IF_FEATURE_MODPROBE_SMALL_CHECK_ALREADY_LOADED(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MODPROBE_SMALL_CHECK_ALREADY_LOADED(...)
#define IF_FEATURE_2_4_MODULES(...)
#define IF_NOT_FEATURE_2_4_MODULES(...) __VA_ARGS__
#define IF_FEATURE_INSMOD_VERSION_CHECKING(...)
#define IF_NOT_FEATURE_INSMOD_VERSION_CHECKING(...) __VA_ARGS__
#define IF_FEATURE_INSMOD_KSYMOOPS_SYMBOLS(...)
#define IF_NOT_FEATURE_INSMOD_KSYMOOPS_SYMBOLS(...) __VA_ARGS__
#define IF_FEATURE_INSMOD_LOADINKMEM(...)
#define IF_NOT_FEATURE_INSMOD_LOADINKMEM(...) __VA_ARGS__
#define IF_FEATURE_INSMOD_LOAD_MAP(...)
#define IF_NOT_FEATURE_INSMOD_LOAD_MAP(...) __VA_ARGS__
#define IF_FEATURE_INSMOD_LOAD_MAP_FULL(...)
#define IF_NOT_FEATURE_INSMOD_LOAD_MAP_FULL(...) __VA_ARGS__
#define IF_FEATURE_CHECK_TAINTED_MODULE(...)
#define IF_NOT_FEATURE_CHECK_TAINTED_MODULE(...) __VA_ARGS__
#define IF_FEATURE_INSMOD_TRY_MMAP(...)
#define IF_NOT_FEATURE_INSMOD_TRY_MMAP(...) __VA_ARGS__
#define IF_FEATURE_MODUTILS_ALIAS(...)
#define IF_NOT_FEATURE_MODUTILS_ALIAS(...) __VA_ARGS__
#define IF_FEATURE_MODUTILS_SYMBOLS(...)
#define IF_NOT_FEATURE_MODUTILS_SYMBOLS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_DEFAULT_MODULES_DIR(...) __VA_ARGS__ "CONFIG_DEFAULT_MODULES_DIR"
#else
# define IF_DEFAULT_MODULES_DIR(...) __VA_ARGS__
#endif
#define IF_NOT_DEFAULT_MODULES_DIR(...)
#ifdef MAKE_SUID
# define IF_DEFAULT_DEPMOD_FILE(...) __VA_ARGS__ "CONFIG_DEFAULT_DEPMOD_FILE"
#else
# define IF_DEFAULT_DEPMOD_FILE(...) __VA_ARGS__
#endif
#define IF_NOT_DEFAULT_DEPMOD_FILE(...)

/*
 * Linux System Utilities
 */
#ifdef MAKE_SUID
# define IF_ACPID(...) __VA_ARGS__ "CONFIG_ACPID"
#else
# define IF_ACPID(...) __VA_ARGS__
#endif
#define IF_NOT_ACPID(...)
#ifdef MAKE_SUID
# define IF_FEATURE_ACPID_COMPAT(...) __VA_ARGS__ "CONFIG_FEATURE_ACPID_COMPAT"
#else
# define IF_FEATURE_ACPID_COMPAT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_ACPID_COMPAT(...)
#ifdef MAKE_SUID
# define IF_BLKDISCARD(...) __VA_ARGS__ "CONFIG_BLKDISCARD"
#else
# define IF_BLKDISCARD(...) __VA_ARGS__
#endif
#define IF_NOT_BLKDISCARD(...)
#ifdef MAKE_SUID
# define IF_BLKID(...) __VA_ARGS__ "CONFIG_BLKID"
#else
# define IF_BLKID(...) __VA_ARGS__
#endif
#define IF_NOT_BLKID(...)
#ifdef MAKE_SUID
# define IF_FEATURE_BLKID_TYPE(...) __VA_ARGS__ "CONFIG_FEATURE_BLKID_TYPE"
#else
# define IF_FEATURE_BLKID_TYPE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_BLKID_TYPE(...)
#ifdef MAKE_SUID
# define IF_BLOCKDEV(...) __VA_ARGS__ "CONFIG_BLOCKDEV"
#else
# define IF_BLOCKDEV(...) __VA_ARGS__
#endif
#define IF_NOT_BLOCKDEV(...)
#ifdef MAKE_SUID
# define IF_CAL(...) __VA_ARGS__ "CONFIG_CAL"
#else
# define IF_CAL(...) __VA_ARGS__
#endif
#define IF_NOT_CAL(...)
#ifdef MAKE_SUID
# define IF_CHRT(...) __VA_ARGS__ "CONFIG_CHRT"
#else
# define IF_CHRT(...) __VA_ARGS__
#endif
#define IF_NOT_CHRT(...)
#ifdef MAKE_SUID
# define IF_DMESG(...) __VA_ARGS__ "CONFIG_DMESG"
#else
# define IF_DMESG(...) __VA_ARGS__
#endif
#define IF_NOT_DMESG(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DMESG_PRETTY(...) __VA_ARGS__ "CONFIG_FEATURE_DMESG_PRETTY"
#else
# define IF_FEATURE_DMESG_PRETTY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DMESG_PRETTY(...)
#ifdef MAKE_SUID
# define IF_EJECT(...) __VA_ARGS__ "CONFIG_EJECT"
#else
# define IF_EJECT(...) __VA_ARGS__
#endif
#define IF_NOT_EJECT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_EJECT_SCSI(...) __VA_ARGS__ "CONFIG_FEATURE_EJECT_SCSI"
#else
# define IF_FEATURE_EJECT_SCSI(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_EJECT_SCSI(...)
#ifdef MAKE_SUID
# define IF_FALLOCATE(...) __VA_ARGS__ "CONFIG_FALLOCATE"
#else
# define IF_FALLOCATE(...) __VA_ARGS__
#endif
#define IF_NOT_FALLOCATE(...)
#ifdef MAKE_SUID
# define IF_FATATTR(...) __VA_ARGS__ "CONFIG_FATATTR"
#else
# define IF_FATATTR(...) __VA_ARGS__
#endif
#define IF_NOT_FATATTR(...)
#ifdef MAKE_SUID
# define IF_FBSET(...) __VA_ARGS__ "CONFIG_FBSET"
#else
# define IF_FBSET(...) __VA_ARGS__
#endif
#define IF_NOT_FBSET(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FBSET_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_FBSET_FANCY"
#else
# define IF_FEATURE_FBSET_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FBSET_FANCY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FBSET_READMODE(...) __VA_ARGS__ "CONFIG_FEATURE_FBSET_READMODE"
#else
# define IF_FEATURE_FBSET_READMODE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FBSET_READMODE(...)
#ifdef MAKE_SUID
# define IF_FDFORMAT(...) __VA_ARGS__ "CONFIG_FDFORMAT"
#else
# define IF_FDFORMAT(...) __VA_ARGS__
#endif
#define IF_NOT_FDFORMAT(...)
#ifdef MAKE_SUID
# define IF_FDISK(...) __VA_ARGS__ "CONFIG_FDISK"
#else
# define IF_FDISK(...) __VA_ARGS__
#endif
#define IF_NOT_FDISK(...)
#define IF_FDISK_SUPPORT_LARGE_DISKS(...)
#define IF_NOT_FDISK_SUPPORT_LARGE_DISKS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_FDISK_WRITABLE(...) __VA_ARGS__ "CONFIG_FEATURE_FDISK_WRITABLE"
#else
# define IF_FEATURE_FDISK_WRITABLE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FDISK_WRITABLE(...)
#define IF_FEATURE_AIX_LABEL(...)
#define IF_NOT_FEATURE_AIX_LABEL(...) __VA_ARGS__
#define IF_FEATURE_SGI_LABEL(...)
#define IF_NOT_FEATURE_SGI_LABEL(...) __VA_ARGS__
#define IF_FEATURE_SUN_LABEL(...)
#define IF_NOT_FEATURE_SUN_LABEL(...) __VA_ARGS__
#define IF_FEATURE_OSF_LABEL(...)
#define IF_NOT_FEATURE_OSF_LABEL(...) __VA_ARGS__
#define IF_FEATURE_GPT_LABEL(...)
#define IF_NOT_FEATURE_GPT_LABEL(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_FDISK_ADVANCED(...) __VA_ARGS__ "CONFIG_FEATURE_FDISK_ADVANCED"
#else
# define IF_FEATURE_FDISK_ADVANCED(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FDISK_ADVANCED(...)
#ifdef MAKE_SUID
# define IF_FINDFS(...) __VA_ARGS__ "CONFIG_FINDFS"
#else
# define IF_FINDFS(...) __VA_ARGS__
#endif
#define IF_NOT_FINDFS(...)
#ifdef MAKE_SUID
# define IF_FLOCK(...) __VA_ARGS__ "CONFIG_FLOCK"
#else
# define IF_FLOCK(...) __VA_ARGS__
#endif
#define IF_NOT_FLOCK(...)
#ifdef MAKE_SUID
# define IF_FDFLUSH(...) __VA_ARGS__ "CONFIG_FDFLUSH"
#else
# define IF_FDFLUSH(...) __VA_ARGS__
#endif
#define IF_NOT_FDFLUSH(...)
#ifdef MAKE_SUID
# define IF_FREERAMDISK(...) __VA_ARGS__ "CONFIG_FREERAMDISK"
#else
# define IF_FREERAMDISK(...) __VA_ARGS__
#endif
#define IF_NOT_FREERAMDISK(...)
#ifdef MAKE_SUID
# define IF_FSCK_MINIX(...) __VA_ARGS__ "CONFIG_FSCK_MINIX"
#else
# define IF_FSCK_MINIX(...) __VA_ARGS__
#endif
#define IF_NOT_FSCK_MINIX(...)
#ifdef MAKE_SUID
# define IF_FSFREEZE(...) __VA_ARGS__ "CONFIG_FSFREEZE"
#else
# define IF_FSFREEZE(...) __VA_ARGS__
#endif
#define IF_NOT_FSFREEZE(...)
#ifdef MAKE_SUID
# define IF_FSTRIM(...) __VA_ARGS__ "CONFIG_FSTRIM"
#else
# define IF_FSTRIM(...) __VA_ARGS__
#endif
#define IF_NOT_FSTRIM(...)
#ifdef MAKE_SUID
# define IF_GETOPT(...) __VA_ARGS__ "CONFIG_GETOPT"
#else
# define IF_GETOPT(...) __VA_ARGS__
#endif
#define IF_NOT_GETOPT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_GETOPT_LONG(...) __VA_ARGS__ "CONFIG_FEATURE_GETOPT_LONG"
#else
# define IF_FEATURE_GETOPT_LONG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_GETOPT_LONG(...)
#ifdef MAKE_SUID
# define IF_HEXDUMP(...) __VA_ARGS__ "CONFIG_HEXDUMP"
#else
# define IF_HEXDUMP(...) __VA_ARGS__
#endif
#define IF_NOT_HEXDUMP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HEXDUMP_REVERSE(...) __VA_ARGS__ "CONFIG_FEATURE_HEXDUMP_REVERSE"
#else
# define IF_FEATURE_HEXDUMP_REVERSE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HEXDUMP_REVERSE(...)
#ifdef MAKE_SUID
# define IF_HD(...) __VA_ARGS__ "CONFIG_HD"
#else
# define IF_HD(...) __VA_ARGS__
#endif
#define IF_NOT_HD(...)
#ifdef MAKE_SUID
# define IF_XXD(...) __VA_ARGS__ "CONFIG_XXD"
#else
# define IF_XXD(...) __VA_ARGS__
#endif
#define IF_NOT_XXD(...)
#ifdef MAKE_SUID
# define IF_HWCLOCK(...) __VA_ARGS__ "CONFIG_HWCLOCK"
#else
# define IF_HWCLOCK(...) __VA_ARGS__
#endif
#define IF_NOT_HWCLOCK(...)
#define IF_FEATURE_HWCLOCK_ADJTIME_FHS(...)
#define IF_NOT_FEATURE_HWCLOCK_ADJTIME_FHS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_IONICE(...) __VA_ARGS__ "CONFIG_IONICE"
#else
# define IF_IONICE(...) __VA_ARGS__
#endif
#define IF_NOT_IONICE(...)
#ifdef MAKE_SUID
# define IF_IPCRM(...) __VA_ARGS__ "CONFIG_IPCRM"
#else
# define IF_IPCRM(...) __VA_ARGS__
#endif
#define IF_NOT_IPCRM(...)
#ifdef MAKE_SUID
# define IF_IPCS(...) __VA_ARGS__ "CONFIG_IPCS"
#else
# define IF_IPCS(...) __VA_ARGS__
#endif
#define IF_NOT_IPCS(...)
#ifdef MAKE_SUID
# define IF_LAST(...) __VA_ARGS__ "CONFIG_LAST"
#else
# define IF_LAST(...) __VA_ARGS__
#endif
#define IF_NOT_LAST(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LAST_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_LAST_FANCY"
#else
# define IF_FEATURE_LAST_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LAST_FANCY(...)
#ifdef MAKE_SUID
# define IF_LOSETUP(...) __VA_ARGS__ "CONFIG_LOSETUP"
#else
# define IF_LOSETUP(...) __VA_ARGS__
#endif
#define IF_NOT_LOSETUP(...)
#ifdef MAKE_SUID
# define IF_LSPCI(...) __VA_ARGS__ "CONFIG_LSPCI"
#else
# define IF_LSPCI(...) __VA_ARGS__
#endif
#define IF_NOT_LSPCI(...)
#ifdef MAKE_SUID
# define IF_LSUSB(...) __VA_ARGS__ "CONFIG_LSUSB"
#else
# define IF_LSUSB(...) __VA_ARGS__
#endif
#define IF_NOT_LSUSB(...)
#ifdef MAKE_SUID
# define IF_MDEV(...) __VA_ARGS__ "CONFIG_MDEV"
#else
# define IF_MDEV(...) __VA_ARGS__
#endif
#define IF_NOT_MDEV(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MDEV_CONF(...) __VA_ARGS__ "CONFIG_FEATURE_MDEV_CONF"
#else
# define IF_FEATURE_MDEV_CONF(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MDEV_CONF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MDEV_RENAME(...) __VA_ARGS__ "CONFIG_FEATURE_MDEV_RENAME"
#else
# define IF_FEATURE_MDEV_RENAME(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MDEV_RENAME(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MDEV_RENAME_REGEXP(...) __VA_ARGS__ "CONFIG_FEATURE_MDEV_RENAME_REGEXP"
#else
# define IF_FEATURE_MDEV_RENAME_REGEXP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MDEV_RENAME_REGEXP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MDEV_EXEC(...) __VA_ARGS__ "CONFIG_FEATURE_MDEV_EXEC"
#else
# define IF_FEATURE_MDEV_EXEC(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MDEV_EXEC(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MDEV_LOAD_FIRMWARE(...) __VA_ARGS__ "CONFIG_FEATURE_MDEV_LOAD_FIRMWARE"
#else
# define IF_FEATURE_MDEV_LOAD_FIRMWARE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MDEV_LOAD_FIRMWARE(...)
#ifdef MAKE_SUID
# define IF_MESG(...) __VA_ARGS__ "CONFIG_MESG"
#else
# define IF_MESG(...) __VA_ARGS__
#endif
#define IF_NOT_MESG(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MESG_ENABLE_ONLY_GROUP(...) __VA_ARGS__ "CONFIG_FEATURE_MESG_ENABLE_ONLY_GROUP"
#else
# define IF_FEATURE_MESG_ENABLE_ONLY_GROUP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MESG_ENABLE_ONLY_GROUP(...)
#ifdef MAKE_SUID
# define IF_MKE2FS(...) __VA_ARGS__ "CONFIG_MKE2FS"
#else
# define IF_MKE2FS(...) __VA_ARGS__
#endif
#define IF_NOT_MKE2FS(...)
#ifdef MAKE_SUID
# define IF_MKFS_EXT2(...) __VA_ARGS__ "CONFIG_MKFS_EXT2"
#else
# define IF_MKFS_EXT2(...) __VA_ARGS__
#endif
#define IF_NOT_MKFS_EXT2(...)
#ifdef MAKE_SUID
# define IF_MKFS_MINIX(...) __VA_ARGS__ "CONFIG_MKFS_MINIX"
#else
# define IF_MKFS_MINIX(...) __VA_ARGS__
#endif
#define IF_NOT_MKFS_MINIX(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MINIX2(...) __VA_ARGS__ "CONFIG_FEATURE_MINIX2"
#else
# define IF_FEATURE_MINIX2(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MINIX2(...)
#define IF_MKFS_REISER(...)
#define IF_NOT_MKFS_REISER(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_MKDOSFS(...) __VA_ARGS__ "CONFIG_MKDOSFS"
#else
# define IF_MKDOSFS(...) __VA_ARGS__
#endif
#define IF_NOT_MKDOSFS(...)
#ifdef MAKE_SUID
# define IF_MKFS_VFAT(...) __VA_ARGS__ "CONFIG_MKFS_VFAT"
#else
# define IF_MKFS_VFAT(...) __VA_ARGS__
#endif
#define IF_NOT_MKFS_VFAT(...)
#ifdef MAKE_SUID
# define IF_MKSWAP(...) __VA_ARGS__ "CONFIG_MKSWAP"
#else
# define IF_MKSWAP(...) __VA_ARGS__
#endif
#define IF_NOT_MKSWAP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MKSWAP_UUID(...) __VA_ARGS__ "CONFIG_FEATURE_MKSWAP_UUID"
#else
# define IF_FEATURE_MKSWAP_UUID(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MKSWAP_UUID(...)
#ifdef MAKE_SUID
# define IF_MORE(...) __VA_ARGS__ "CONFIG_MORE"
#else
# define IF_MORE(...) __VA_ARGS__
#endif
#define IF_NOT_MORE(...)
#ifdef MAKE_SUID
# define IF_MOUNT(...) __VA_ARGS__ "CONFIG_MOUNT"
#else
# define IF_MOUNT(...) __VA_ARGS__
#endif
#define IF_NOT_MOUNT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MOUNT_FAKE(...) __VA_ARGS__ "CONFIG_FEATURE_MOUNT_FAKE"
#else
# define IF_FEATURE_MOUNT_FAKE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MOUNT_FAKE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MOUNT_VERBOSE(...) __VA_ARGS__ "CONFIG_FEATURE_MOUNT_VERBOSE"
#else
# define IF_FEATURE_MOUNT_VERBOSE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MOUNT_VERBOSE(...)
#define IF_FEATURE_MOUNT_HELPERS(...)
#define IF_NOT_FEATURE_MOUNT_HELPERS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_MOUNT_LABEL(...) __VA_ARGS__ "CONFIG_FEATURE_MOUNT_LABEL"
#else
# define IF_FEATURE_MOUNT_LABEL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MOUNT_LABEL(...)
#define IF_FEATURE_MOUNT_NFS(...)
#define IF_NOT_FEATURE_MOUNT_NFS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_MOUNT_CIFS(...) __VA_ARGS__ "CONFIG_FEATURE_MOUNT_CIFS"
#else
# define IF_FEATURE_MOUNT_CIFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MOUNT_CIFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MOUNT_FLAGS(...) __VA_ARGS__ "CONFIG_FEATURE_MOUNT_FLAGS"
#else
# define IF_FEATURE_MOUNT_FLAGS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MOUNT_FLAGS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MOUNT_FSTAB(...) __VA_ARGS__ "CONFIG_FEATURE_MOUNT_FSTAB"
#else
# define IF_FEATURE_MOUNT_FSTAB(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MOUNT_FSTAB(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MOUNT_OTHERTAB(...) __VA_ARGS__ "CONFIG_FEATURE_MOUNT_OTHERTAB"
#else
# define IF_FEATURE_MOUNT_OTHERTAB(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MOUNT_OTHERTAB(...)
#ifdef MAKE_SUID
# define IF_MOUNTPOINT(...) __VA_ARGS__ "CONFIG_MOUNTPOINT"
#else
# define IF_MOUNTPOINT(...) __VA_ARGS__
#endif
#define IF_NOT_MOUNTPOINT(...)
#ifdef MAKE_SUID
# define IF_NSENTER(...) __VA_ARGS__ "CONFIG_NSENTER"
#else
# define IF_NSENTER(...) __VA_ARGS__
#endif
#define IF_NOT_NSENTER(...)
#ifdef MAKE_SUID
# define IF_PIVOT_ROOT(...) __VA_ARGS__ "CONFIG_PIVOT_ROOT"
#else
# define IF_PIVOT_ROOT(...) __VA_ARGS__
#endif
#define IF_NOT_PIVOT_ROOT(...)
#ifdef MAKE_SUID
# define IF_RDATE(...) __VA_ARGS__ "CONFIG_RDATE"
#else
# define IF_RDATE(...) __VA_ARGS__
#endif
#define IF_NOT_RDATE(...)
#ifdef MAKE_SUID
# define IF_RDEV(...) __VA_ARGS__ "CONFIG_RDEV"
#else
# define IF_RDEV(...) __VA_ARGS__
#endif
#define IF_NOT_RDEV(...)
#ifdef MAKE_SUID
# define IF_READPROFILE(...) __VA_ARGS__ "CONFIG_READPROFILE"
#else
# define IF_READPROFILE(...) __VA_ARGS__
#endif
#define IF_NOT_READPROFILE(...)
#ifdef MAKE_SUID
# define IF_RENICE(...) __VA_ARGS__ "CONFIG_RENICE"
#else
# define IF_RENICE(...) __VA_ARGS__
#endif
#define IF_NOT_RENICE(...)
#ifdef MAKE_SUID
# define IF_REV(...) __VA_ARGS__ "CONFIG_REV"
#else
# define IF_REV(...) __VA_ARGS__
#endif
#define IF_NOT_REV(...)
#ifdef MAKE_SUID
# define IF_RTCWAKE(...) __VA_ARGS__ "CONFIG_RTCWAKE"
#else
# define IF_RTCWAKE(...) __VA_ARGS__
#endif
#define IF_NOT_RTCWAKE(...)
#ifdef MAKE_SUID
# define IF_SCRIPT(...) __VA_ARGS__ "CONFIG_SCRIPT"
#else
# define IF_SCRIPT(...) __VA_ARGS__
#endif
#define IF_NOT_SCRIPT(...)
#ifdef MAKE_SUID
# define IF_SCRIPTREPLAY(...) __VA_ARGS__ "CONFIG_SCRIPTREPLAY"
#else
# define IF_SCRIPTREPLAY(...) __VA_ARGS__
#endif
#define IF_NOT_SCRIPTREPLAY(...)
#ifdef MAKE_SUID
# define IF_SETARCH(...) __VA_ARGS__ "CONFIG_SETARCH"
#else
# define IF_SETARCH(...) __VA_ARGS__
#endif
#define IF_NOT_SETARCH(...)
#ifdef MAKE_SUID
# define IF_LINUX32(...) __VA_ARGS__ "CONFIG_LINUX32"
#else
# define IF_LINUX32(...) __VA_ARGS__
#endif
#define IF_NOT_LINUX32(...)
#ifdef MAKE_SUID
# define IF_LINUX64(...) __VA_ARGS__ "CONFIG_LINUX64"
#else
# define IF_LINUX64(...) __VA_ARGS__
#endif
#define IF_NOT_LINUX64(...)
#ifdef MAKE_SUID
# define IF_SETPRIV(...) __VA_ARGS__ "CONFIG_SETPRIV"
#else
# define IF_SETPRIV(...) __VA_ARGS__
#endif
#define IF_NOT_SETPRIV(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SETPRIV_DUMP(...) __VA_ARGS__ "CONFIG_FEATURE_SETPRIV_DUMP"
#else
# define IF_FEATURE_SETPRIV_DUMP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SETPRIV_DUMP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SETPRIV_CAPABILITIES(...) __VA_ARGS__ "CONFIG_FEATURE_SETPRIV_CAPABILITIES"
#else
# define IF_FEATURE_SETPRIV_CAPABILITIES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SETPRIV_CAPABILITIES(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SETPRIV_CAPABILITY_NAMES(...) __VA_ARGS__ "CONFIG_FEATURE_SETPRIV_CAPABILITY_NAMES"
#else
# define IF_FEATURE_SETPRIV_CAPABILITY_NAMES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SETPRIV_CAPABILITY_NAMES(...)
#ifdef MAKE_SUID
# define IF_SETSID(...) __VA_ARGS__ "CONFIG_SETSID"
#else
# define IF_SETSID(...) __VA_ARGS__
#endif
#define IF_NOT_SETSID(...)
#ifdef MAKE_SUID
# define IF_SWAPON(...) __VA_ARGS__ "CONFIG_SWAPON"
#else
# define IF_SWAPON(...) __VA_ARGS__
#endif
#define IF_NOT_SWAPON(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SWAPON_DISCARD(...) __VA_ARGS__ "CONFIG_FEATURE_SWAPON_DISCARD"
#else
# define IF_FEATURE_SWAPON_DISCARD(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SWAPON_DISCARD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SWAPON_PRI(...) __VA_ARGS__ "CONFIG_FEATURE_SWAPON_PRI"
#else
# define IF_FEATURE_SWAPON_PRI(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SWAPON_PRI(...)
#ifdef MAKE_SUID
# define IF_SWAPOFF(...) __VA_ARGS__ "CONFIG_SWAPOFF"
#else
# define IF_SWAPOFF(...) __VA_ARGS__
#endif
#define IF_NOT_SWAPOFF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SWAPONOFF_LABEL(...) __VA_ARGS__ "CONFIG_FEATURE_SWAPONOFF_LABEL"
#else
# define IF_FEATURE_SWAPONOFF_LABEL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SWAPONOFF_LABEL(...)
#ifdef MAKE_SUID
# define IF_SWITCH_ROOT(...) __VA_ARGS__ "CONFIG_SWITCH_ROOT"
#else
# define IF_SWITCH_ROOT(...) __VA_ARGS__
#endif
#define IF_NOT_SWITCH_ROOT(...)
#ifdef MAKE_SUID
# define IF_TASKSET(...) __VA_ARGS__ "CONFIG_TASKSET"
#else
# define IF_TASKSET(...) __VA_ARGS__
#endif
#define IF_NOT_TASKSET(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TASKSET_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_TASKSET_FANCY"
#else
# define IF_FEATURE_TASKSET_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TASKSET_FANCY(...)
#ifdef MAKE_SUID
# define IF_UEVENT(...) __VA_ARGS__ "CONFIG_UEVENT"
#else
# define IF_UEVENT(...) __VA_ARGS__
#endif
#define IF_NOT_UEVENT(...)
#ifdef MAKE_SUID
# define IF_UMOUNT(...) __VA_ARGS__ "CONFIG_UMOUNT"
#else
# define IF_UMOUNT(...) __VA_ARGS__
#endif
#define IF_NOT_UMOUNT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UMOUNT_ALL(...) __VA_ARGS__ "CONFIG_FEATURE_UMOUNT_ALL"
#else
# define IF_FEATURE_UMOUNT_ALL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UMOUNT_ALL(...)
#ifdef MAKE_SUID
# define IF_UNSHARE(...) __VA_ARGS__ "CONFIG_UNSHARE"
#else
# define IF_UNSHARE(...) __VA_ARGS__
#endif
#define IF_NOT_UNSHARE(...)
#ifdef MAKE_SUID
# define IF_WALL(...) __VA_ARGS__ "CONFIG_WALL"
#else
# define IF_WALL(...) __VA_ARGS__
#endif
#define IF_NOT_WALL(...)

/*
 * Common options for mount/umount
 */
#ifdef MAKE_SUID
# define IF_FEATURE_MOUNT_LOOP(...) __VA_ARGS__ "CONFIG_FEATURE_MOUNT_LOOP"
#else
# define IF_FEATURE_MOUNT_LOOP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MOUNT_LOOP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MOUNT_LOOP_CREATE(...) __VA_ARGS__ "CONFIG_FEATURE_MOUNT_LOOP_CREATE"
#else
# define IF_FEATURE_MOUNT_LOOP_CREATE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MOUNT_LOOP_CREATE(...)
#define IF_FEATURE_MTAB_SUPPORT(...)
#define IF_NOT_FEATURE_MTAB_SUPPORT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_VOLUMEID(...) __VA_ARGS__ "CONFIG_VOLUMEID"
#else
# define IF_VOLUMEID(...) __VA_ARGS__
#endif
#define IF_NOT_VOLUMEID(...)

/*
 * Filesystem/Volume identification
 */
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_BCACHE(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_BCACHE"
#else
# define IF_FEATURE_VOLUMEID_BCACHE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_BCACHE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_BTRFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_BTRFS"
#else
# define IF_FEATURE_VOLUMEID_BTRFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_BTRFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_CRAMFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_CRAMFS"
#else
# define IF_FEATURE_VOLUMEID_CRAMFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_CRAMFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_EXFAT(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_EXFAT"
#else
# define IF_FEATURE_VOLUMEID_EXFAT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_EXFAT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_EXT(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_EXT"
#else
# define IF_FEATURE_VOLUMEID_EXT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_EXT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_F2FS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_F2FS"
#else
# define IF_FEATURE_VOLUMEID_F2FS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_F2FS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_FAT(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_FAT"
#else
# define IF_FEATURE_VOLUMEID_FAT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_FAT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_HFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_HFS"
#else
# define IF_FEATURE_VOLUMEID_HFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_HFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_ISO9660(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_ISO9660"
#else
# define IF_FEATURE_VOLUMEID_ISO9660(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_ISO9660(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_JFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_JFS"
#else
# define IF_FEATURE_VOLUMEID_JFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_JFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_LINUXRAID(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_LINUXRAID"
#else
# define IF_FEATURE_VOLUMEID_LINUXRAID(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_LINUXRAID(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_LINUXSWAP(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_LINUXSWAP"
#else
# define IF_FEATURE_VOLUMEID_LINUXSWAP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_LINUXSWAP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_LUKS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_LUKS"
#else
# define IF_FEATURE_VOLUMEID_LUKS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_LUKS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_MINIX(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_MINIX"
#else
# define IF_FEATURE_VOLUMEID_MINIX(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_MINIX(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_NILFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_NILFS"
#else
# define IF_FEATURE_VOLUMEID_NILFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_NILFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_NTFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_NTFS"
#else
# define IF_FEATURE_VOLUMEID_NTFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_NTFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_OCFS2(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_OCFS2"
#else
# define IF_FEATURE_VOLUMEID_OCFS2(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_OCFS2(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_REISERFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_REISERFS"
#else
# define IF_FEATURE_VOLUMEID_REISERFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_REISERFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_ROMFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_ROMFS"
#else
# define IF_FEATURE_VOLUMEID_ROMFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_ROMFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_SQUASHFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_SQUASHFS"
#else
# define IF_FEATURE_VOLUMEID_SQUASHFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_SQUASHFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_SYSV(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_SYSV"
#else
# define IF_FEATURE_VOLUMEID_SYSV(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_SYSV(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_UBIFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_UBIFS"
#else
# define IF_FEATURE_VOLUMEID_UBIFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_UBIFS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_UDF(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_UDF"
#else
# define IF_FEATURE_VOLUMEID_UDF(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_UDF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_VOLUMEID_XFS(...) __VA_ARGS__ "CONFIG_FEATURE_VOLUMEID_XFS"
#else
# define IF_FEATURE_VOLUMEID_XFS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_VOLUMEID_XFS(...)

/*
 * Miscellaneous Utilities
 */
#ifdef MAKE_SUID
# define IF_ADJTIMEX(...) __VA_ARGS__ "CONFIG_ADJTIMEX"
#else
# define IF_ADJTIMEX(...) __VA_ARGS__
#endif
#define IF_NOT_ADJTIMEX(...)
#define IF_BBCONFIG(...)
#define IF_NOT_BBCONFIG(...) __VA_ARGS__
#define IF_FEATURE_COMPRESS_BBCONFIG(...)
#define IF_NOT_FEATURE_COMPRESS_BBCONFIG(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_BEEP(...) __VA_ARGS__ "CONFIG_BEEP"
#else
# define IF_BEEP(...) __VA_ARGS__
#endif
#define IF_NOT_BEEP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_BEEP_FREQ(...) __VA_ARGS__ "CONFIG_FEATURE_BEEP_FREQ"
#else
# define IF_FEATURE_BEEP_FREQ(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_BEEP_FREQ(...)
#ifdef MAKE_SUID
# define IF_FEATURE_BEEP_LENGTH_MS(...) __VA_ARGS__ "CONFIG_FEATURE_BEEP_LENGTH_MS"
#else
# define IF_FEATURE_BEEP_LENGTH_MS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_BEEP_LENGTH_MS(...)
#ifdef MAKE_SUID
# define IF_CHAT(...) __VA_ARGS__ "CONFIG_CHAT"
#else
# define IF_CHAT(...) __VA_ARGS__
#endif
#define IF_NOT_CHAT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CHAT_NOFAIL(...) __VA_ARGS__ "CONFIG_FEATURE_CHAT_NOFAIL"
#else
# define IF_FEATURE_CHAT_NOFAIL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CHAT_NOFAIL(...)
#define IF_FEATURE_CHAT_TTY_HIFI(...)
#define IF_NOT_FEATURE_CHAT_TTY_HIFI(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_CHAT_IMPLICIT_CR(...) __VA_ARGS__ "CONFIG_FEATURE_CHAT_IMPLICIT_CR"
#else
# define IF_FEATURE_CHAT_IMPLICIT_CR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CHAT_IMPLICIT_CR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CHAT_SWALLOW_OPTS(...) __VA_ARGS__ "CONFIG_FEATURE_CHAT_SWALLOW_OPTS"
#else
# define IF_FEATURE_CHAT_SWALLOW_OPTS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CHAT_SWALLOW_OPTS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CHAT_SEND_ESCAPES(...) __VA_ARGS__ "CONFIG_FEATURE_CHAT_SEND_ESCAPES"
#else
# define IF_FEATURE_CHAT_SEND_ESCAPES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CHAT_SEND_ESCAPES(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CHAT_VAR_ABORT_LEN(...) __VA_ARGS__ "CONFIG_FEATURE_CHAT_VAR_ABORT_LEN"
#else
# define IF_FEATURE_CHAT_VAR_ABORT_LEN(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CHAT_VAR_ABORT_LEN(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CHAT_CLR_ABORT(...) __VA_ARGS__ "CONFIG_FEATURE_CHAT_CLR_ABORT"
#else
# define IF_FEATURE_CHAT_CLR_ABORT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CHAT_CLR_ABORT(...)
#ifdef MAKE_SUID
# define IF_CONSPY(...) __VA_ARGS__ "CONFIG_CONSPY"
#else
# define IF_CONSPY(...) __VA_ARGS__
#endif
#define IF_NOT_CONSPY(...)
#ifdef MAKE_SUID
# define IF_CROND(...) __VA_ARGS__ "CONFIG_CROND"
#else
# define IF_CROND(...) __VA_ARGS__
#endif
#define IF_NOT_CROND(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CROND_D(...) __VA_ARGS__ "CONFIG_FEATURE_CROND_D"
#else
# define IF_FEATURE_CROND_D(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CROND_D(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CROND_CALL_SENDMAIL(...) __VA_ARGS__ "CONFIG_FEATURE_CROND_CALL_SENDMAIL"
#else
# define IF_FEATURE_CROND_CALL_SENDMAIL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CROND_CALL_SENDMAIL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_CROND_SPECIAL_TIMES(...) __VA_ARGS__ "CONFIG_FEATURE_CROND_SPECIAL_TIMES"
#else
# define IF_FEATURE_CROND_SPECIAL_TIMES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CROND_SPECIAL_TIMES(...)
#define CONFIG_FEATURE_CROND_DIR "/var/spool/cron"
#ifdef MAKE_SUID
# define IF_FEATURE_CROND_DIR(...) __VA_ARGS__ "CONFIG_FEATURE_CROND_DIR"
#else
# define IF_FEATURE_CROND_DIR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_CROND_DIR(...)
#ifdef MAKE_SUID
# define IF_CRONTAB(...) __VA_ARGS__ "CONFIG_CRONTAB"
#else
# define IF_CRONTAB(...) __VA_ARGS__
#endif
#define IF_NOT_CRONTAB(...)
#ifdef MAKE_SUID
# define IF_DC(...) __VA_ARGS__ "CONFIG_DC"
#else
# define IF_DC(...) __VA_ARGS__
#endif
#define IF_NOT_DC(...)
#ifdef MAKE_SUID
# define IF_FEATURE_DC_LIBM(...) __VA_ARGS__ "CONFIG_FEATURE_DC_LIBM"
#else
# define IF_FEATURE_DC_LIBM(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_DC_LIBM(...)
#define IF_DEVFSD(...)
#define IF_NOT_DEVFSD(...) __VA_ARGS__
#define IF_DEVFSD_MODLOAD(...)
#define IF_NOT_DEVFSD_MODLOAD(...) __VA_ARGS__
#define IF_DEVFSD_FG_NP(...)
#define IF_NOT_DEVFSD_FG_NP(...) __VA_ARGS__
#define IF_DEVFSD_VERBOSE(...)
#define IF_NOT_DEVFSD_VERBOSE(...) __VA_ARGS__
#define IF_FEATURE_DEVFS(...)
#define IF_NOT_FEATURE_DEVFS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_DEVMEM(...) __VA_ARGS__ "CONFIG_DEVMEM"
#else
# define IF_DEVMEM(...) __VA_ARGS__
#endif
#define IF_NOT_DEVMEM(...)
#ifdef MAKE_SUID
# define IF_FBSPLASH(...) __VA_ARGS__ "CONFIG_FBSPLASH"
#else
# define IF_FBSPLASH(...) __VA_ARGS__
#endif
#define IF_NOT_FBSPLASH(...)
#define IF_FLASH_ERASEALL(...)
#define IF_NOT_FLASH_ERASEALL(...) __VA_ARGS__
#define IF_FLASH_LOCK(...)
#define IF_NOT_FLASH_LOCK(...) __VA_ARGS__
#define IF_FLASH_UNLOCK(...)
#define IF_NOT_FLASH_UNLOCK(...) __VA_ARGS__
#define IF_FLASHCP(...)
#define IF_NOT_FLASHCP(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_HDPARM(...) __VA_ARGS__ "CONFIG_HDPARM"
#else
# define IF_HDPARM(...) __VA_ARGS__
#endif
#define IF_NOT_HDPARM(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HDPARM_GET_IDENTITY(...) __VA_ARGS__ "CONFIG_FEATURE_HDPARM_GET_IDENTITY"
#else
# define IF_FEATURE_HDPARM_GET_IDENTITY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HDPARM_GET_IDENTITY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HDPARM_HDIO_SCAN_HWIF(...) __VA_ARGS__ "CONFIG_FEATURE_HDPARM_HDIO_SCAN_HWIF"
#else
# define IF_FEATURE_HDPARM_HDIO_SCAN_HWIF(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HDPARM_HDIO_SCAN_HWIF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HDPARM_HDIO_UNREGISTER_HWIF(...) __VA_ARGS__ "CONFIG_FEATURE_HDPARM_HDIO_UNREGISTER_HWIF"
#else
# define IF_FEATURE_HDPARM_HDIO_UNREGISTER_HWIF(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HDPARM_HDIO_UNREGISTER_HWIF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HDPARM_HDIO_DRIVE_RESET(...) __VA_ARGS__ "CONFIG_FEATURE_HDPARM_HDIO_DRIVE_RESET"
#else
# define IF_FEATURE_HDPARM_HDIO_DRIVE_RESET(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HDPARM_HDIO_DRIVE_RESET(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HDPARM_HDIO_TRISTATE_HWIF(...) __VA_ARGS__ "CONFIG_FEATURE_HDPARM_HDIO_TRISTATE_HWIF"
#else
# define IF_FEATURE_HDPARM_HDIO_TRISTATE_HWIF(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HDPARM_HDIO_TRISTATE_HWIF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HDPARM_HDIO_GETSET_DMA(...) __VA_ARGS__ "CONFIG_FEATURE_HDPARM_HDIO_GETSET_DMA"
#else
# define IF_FEATURE_HDPARM_HDIO_GETSET_DMA(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HDPARM_HDIO_GETSET_DMA(...)
#ifdef MAKE_SUID
# define IF_HEXEDIT(...) __VA_ARGS__ "CONFIG_HEXEDIT"
#else
# define IF_HEXEDIT(...) __VA_ARGS__
#endif
#define IF_NOT_HEXEDIT(...)
#ifdef MAKE_SUID
# define IF_I2CGET(...) __VA_ARGS__ "CONFIG_I2CGET"
#else
# define IF_I2CGET(...) __VA_ARGS__
#endif
#define IF_NOT_I2CGET(...)
#ifdef MAKE_SUID
# define IF_I2CSET(...) __VA_ARGS__ "CONFIG_I2CSET"
#else
# define IF_I2CSET(...) __VA_ARGS__
#endif
#define IF_NOT_I2CSET(...)
#ifdef MAKE_SUID
# define IF_I2CDUMP(...) __VA_ARGS__ "CONFIG_I2CDUMP"
#else
# define IF_I2CDUMP(...) __VA_ARGS__
#endif
#define IF_NOT_I2CDUMP(...)
#ifdef MAKE_SUID
# define IF_I2CDETECT(...) __VA_ARGS__ "CONFIG_I2CDETECT"
#else
# define IF_I2CDETECT(...) __VA_ARGS__
#endif
#define IF_NOT_I2CDETECT(...)
#define IF_INOTIFYD(...)
#define IF_NOT_INOTIFYD(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_LESS(...) __VA_ARGS__ "CONFIG_LESS"
#else
# define IF_LESS(...) __VA_ARGS__
#endif
#define IF_NOT_LESS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_MAXLINES(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_MAXLINES"
#else
# define IF_FEATURE_LESS_MAXLINES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_MAXLINES(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_BRACKETS(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_BRACKETS"
#else
# define IF_FEATURE_LESS_BRACKETS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_BRACKETS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_FLAGS(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_FLAGS"
#else
# define IF_FEATURE_LESS_FLAGS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_FLAGS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_TRUNCATE(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_TRUNCATE"
#else
# define IF_FEATURE_LESS_TRUNCATE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_TRUNCATE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_MARKS(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_MARKS"
#else
# define IF_FEATURE_LESS_MARKS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_MARKS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_REGEXP(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_REGEXP"
#else
# define IF_FEATURE_LESS_REGEXP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_REGEXP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_WINCH(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_WINCH"
#else
# define IF_FEATURE_LESS_WINCH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_WINCH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_ASK_TERMINAL(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_ASK_TERMINAL"
#else
# define IF_FEATURE_LESS_ASK_TERMINAL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_ASK_TERMINAL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_DASHCMD(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_DASHCMD"
#else
# define IF_FEATURE_LESS_DASHCMD(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_DASHCMD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LESS_LINENUMS(...) __VA_ARGS__ "CONFIG_FEATURE_LESS_LINENUMS"
#else
# define IF_FEATURE_LESS_LINENUMS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LESS_LINENUMS(...)
#ifdef MAKE_SUID
# define IF_LSSCSI(...) __VA_ARGS__ "CONFIG_LSSCSI"
#else
# define IF_LSSCSI(...) __VA_ARGS__
#endif
#define IF_NOT_LSSCSI(...)
#ifdef MAKE_SUID
# define IF_MAKEDEVS(...) __VA_ARGS__ "CONFIG_MAKEDEVS"
#else
# define IF_MAKEDEVS(...) __VA_ARGS__
#endif
#define IF_NOT_MAKEDEVS(...)
#define IF_FEATURE_MAKEDEVS_LEAF(...)
#define IF_NOT_FEATURE_MAKEDEVS_LEAF(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_MAKEDEVS_TABLE(...) __VA_ARGS__ "CONFIG_FEATURE_MAKEDEVS_TABLE"
#else
# define IF_FEATURE_MAKEDEVS_TABLE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MAKEDEVS_TABLE(...)
#ifdef MAKE_SUID
# define IF_MAN(...) __VA_ARGS__ "CONFIG_MAN"
#else
# define IF_MAN(...) __VA_ARGS__
#endif
#define IF_NOT_MAN(...)
#ifdef MAKE_SUID
# define IF_MICROCOM(...) __VA_ARGS__ "CONFIG_MICROCOM"
#else
# define IF_MICROCOM(...) __VA_ARGS__
#endif
#define IF_NOT_MICROCOM(...)
#ifdef MAKE_SUID
# define IF_MT(...) __VA_ARGS__ "CONFIG_MT"
#else
# define IF_MT(...) __VA_ARGS__
#endif
#define IF_NOT_MT(...)
#ifdef MAKE_SUID
# define IF_NANDWRITE(...) __VA_ARGS__ "CONFIG_NANDWRITE"
#else
# define IF_NANDWRITE(...) __VA_ARGS__
#endif
#define IF_NOT_NANDWRITE(...)
#ifdef MAKE_SUID
# define IF_NANDDUMP(...) __VA_ARGS__ "CONFIG_NANDDUMP"
#else
# define IF_NANDDUMP(...) __VA_ARGS__
#endif
#define IF_NOT_NANDDUMP(...)
#ifdef MAKE_SUID
# define IF_PARTPROBE(...) __VA_ARGS__ "CONFIG_PARTPROBE"
#else
# define IF_PARTPROBE(...) __VA_ARGS__
#endif
#define IF_NOT_PARTPROBE(...)
#ifdef MAKE_SUID
# define IF_RAIDAUTORUN(...) __VA_ARGS__ "CONFIG_RAIDAUTORUN"
#else
# define IF_RAIDAUTORUN(...) __VA_ARGS__
#endif
#define IF_NOT_RAIDAUTORUN(...)
#ifdef MAKE_SUID
# define IF_READAHEAD(...) __VA_ARGS__ "CONFIG_READAHEAD"
#else
# define IF_READAHEAD(...) __VA_ARGS__
#endif
#define IF_NOT_READAHEAD(...)
#define IF_RFKILL(...)
#define IF_NOT_RFKILL(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_RUNLEVEL(...) __VA_ARGS__ "CONFIG_RUNLEVEL"
#else
# define IF_RUNLEVEL(...) __VA_ARGS__
#endif
#define IF_NOT_RUNLEVEL(...)
#ifdef MAKE_SUID
# define IF_RX(...) __VA_ARGS__ "CONFIG_RX"
#else
# define IF_RX(...) __VA_ARGS__
#endif
#define IF_NOT_RX(...)
#ifdef MAKE_SUID
# define IF_SETFATTR(...) __VA_ARGS__ "CONFIG_SETFATTR"
#else
# define IF_SETFATTR(...) __VA_ARGS__
#endif
#define IF_NOT_SETFATTR(...)
#ifdef MAKE_SUID
# define IF_SETSERIAL(...) __VA_ARGS__ "CONFIG_SETSERIAL"
#else
# define IF_SETSERIAL(...) __VA_ARGS__
#endif
#define IF_NOT_SETSERIAL(...)
#ifdef MAKE_SUID
# define IF_STRINGS(...) __VA_ARGS__ "CONFIG_STRINGS"
#else
# define IF_STRINGS(...) __VA_ARGS__
#endif
#define IF_NOT_STRINGS(...)
#ifdef MAKE_SUID
# define IF_TIME(...) __VA_ARGS__ "CONFIG_TIME"
#else
# define IF_TIME(...) __VA_ARGS__
#endif
#define IF_NOT_TIME(...)
#ifdef MAKE_SUID
# define IF_TTYSIZE(...) __VA_ARGS__ "CONFIG_TTYSIZE"
#else
# define IF_TTYSIZE(...) __VA_ARGS__
#endif
#define IF_NOT_TTYSIZE(...)
#ifdef MAKE_SUID
# define IF_UBIATTACH(...) __VA_ARGS__ "CONFIG_UBIATTACH"
#else
# define IF_UBIATTACH(...) __VA_ARGS__
#endif
#define IF_NOT_UBIATTACH(...)
#ifdef MAKE_SUID
# define IF_UBIDETACH(...) __VA_ARGS__ "CONFIG_UBIDETACH"
#else
# define IF_UBIDETACH(...) __VA_ARGS__
#endif
#define IF_NOT_UBIDETACH(...)
#ifdef MAKE_SUID
# define IF_UBIMKVOL(...) __VA_ARGS__ "CONFIG_UBIMKVOL"
#else
# define IF_UBIMKVOL(...) __VA_ARGS__
#endif
#define IF_NOT_UBIMKVOL(...)
#ifdef MAKE_SUID
# define IF_UBIRMVOL(...) __VA_ARGS__ "CONFIG_UBIRMVOL"
#else
# define IF_UBIRMVOL(...) __VA_ARGS__
#endif
#define IF_NOT_UBIRMVOL(...)
#ifdef MAKE_SUID
# define IF_UBIRSVOL(...) __VA_ARGS__ "CONFIG_UBIRSVOL"
#else
# define IF_UBIRSVOL(...) __VA_ARGS__
#endif
#define IF_NOT_UBIRSVOL(...)
#ifdef MAKE_SUID
# define IF_UBIUPDATEVOL(...) __VA_ARGS__ "CONFIG_UBIUPDATEVOL"
#else
# define IF_UBIUPDATEVOL(...) __VA_ARGS__
#endif
#define IF_NOT_UBIUPDATEVOL(...)
#ifdef MAKE_SUID
# define IF_UBIRENAME(...) __VA_ARGS__ "CONFIG_UBIRENAME"
#else
# define IF_UBIRENAME(...) __VA_ARGS__
#endif
#define IF_NOT_UBIRENAME(...)
#ifdef MAKE_SUID
# define IF_VOLNAME(...) __VA_ARGS__ "CONFIG_VOLNAME"
#else
# define IF_VOLNAME(...) __VA_ARGS__
#endif
#define IF_NOT_VOLNAME(...)
#ifdef MAKE_SUID
# define IF_WATCHDOG(...) __VA_ARGS__ "CONFIG_WATCHDOG"
#else
# define IF_WATCHDOG(...) __VA_ARGS__
#endif
#define IF_NOT_WATCHDOG(...)

/*
 * Networking Utilities
 */
#ifdef MAKE_SUID
# define IF_FEATURE_IPV6(...) __VA_ARGS__ "CONFIG_FEATURE_IPV6"
#else
# define IF_FEATURE_IPV6(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IPV6(...)
#define IF_FEATURE_UNIX_LOCAL(...)
#define IF_NOT_FEATURE_UNIX_LOCAL(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_PREFER_IPV4_ADDRESS(...) __VA_ARGS__ "CONFIG_FEATURE_PREFER_IPV4_ADDRESS"
#else
# define IF_FEATURE_PREFER_IPV4_ADDRESS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_PREFER_IPV4_ADDRESS(...)
#define IF_VERBOSE_RESOLUTION_ERRORS(...)
#define IF_NOT_VERBOSE_RESOLUTION_ERRORS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_ARP(...) __VA_ARGS__ "CONFIG_ARP"
#else
# define IF_ARP(...) __VA_ARGS__
#endif
#define IF_NOT_ARP(...)
#ifdef MAKE_SUID
# define IF_ARPING(...) __VA_ARGS__ "CONFIG_ARPING"
#else
# define IF_ARPING(...) __VA_ARGS__
#endif
#define IF_NOT_ARPING(...)
#ifdef MAKE_SUID
# define IF_BRCTL(...) __VA_ARGS__ "CONFIG_BRCTL"
#else
# define IF_BRCTL(...) __VA_ARGS__
#endif
#define IF_NOT_BRCTL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_BRCTL_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_BRCTL_FANCY"
#else
# define IF_FEATURE_BRCTL_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_BRCTL_FANCY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_BRCTL_SHOW(...) __VA_ARGS__ "CONFIG_FEATURE_BRCTL_SHOW"
#else
# define IF_FEATURE_BRCTL_SHOW(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_BRCTL_SHOW(...)
#ifdef MAKE_SUID
# define IF_DNSD(...) __VA_ARGS__ "CONFIG_DNSD"
#else
# define IF_DNSD(...) __VA_ARGS__
#endif
#define IF_NOT_DNSD(...)
#ifdef MAKE_SUID
# define IF_ETHER_WAKE(...) __VA_ARGS__ "CONFIG_ETHER_WAKE"
#else
# define IF_ETHER_WAKE(...) __VA_ARGS__
#endif
#define IF_NOT_ETHER_WAKE(...)
#ifdef MAKE_SUID
# define IF_FTPD(...) __VA_ARGS__ "CONFIG_FTPD"
#else
# define IF_FTPD(...) __VA_ARGS__
#endif
#define IF_NOT_FTPD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FTPD_WRITE(...) __VA_ARGS__ "CONFIG_FEATURE_FTPD_WRITE"
#else
# define IF_FEATURE_FTPD_WRITE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FTPD_WRITE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FTPD_ACCEPT_BROKEN_LIST(...) __VA_ARGS__ "CONFIG_FEATURE_FTPD_ACCEPT_BROKEN_LIST"
#else
# define IF_FEATURE_FTPD_ACCEPT_BROKEN_LIST(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FTPD_ACCEPT_BROKEN_LIST(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FTPD_AUTHENTICATION(...) __VA_ARGS__ "CONFIG_FEATURE_FTPD_AUTHENTICATION"
#else
# define IF_FEATURE_FTPD_AUTHENTICATION(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FTPD_AUTHENTICATION(...)
#ifdef MAKE_SUID
# define IF_FTPGET(...) __VA_ARGS__ "CONFIG_FTPGET"
#else
# define IF_FTPGET(...) __VA_ARGS__
#endif
#define IF_NOT_FTPGET(...)
#ifdef MAKE_SUID
# define IF_FTPPUT(...) __VA_ARGS__ "CONFIG_FTPPUT"
#else
# define IF_FTPPUT(...) __VA_ARGS__
#endif
#define IF_NOT_FTPPUT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FTPGETPUT_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_FTPGETPUT_LONG_OPTIONS"
#else
# define IF_FEATURE_FTPGETPUT_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FTPGETPUT_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_HOSTNAME(...) __VA_ARGS__ "CONFIG_HOSTNAME"
#else
# define IF_HOSTNAME(...) __VA_ARGS__
#endif
#define IF_NOT_HOSTNAME(...)
#ifdef MAKE_SUID
# define IF_DNSDOMAINNAME(...) __VA_ARGS__ "CONFIG_DNSDOMAINNAME"
#else
# define IF_DNSDOMAINNAME(...) __VA_ARGS__
#endif
#define IF_NOT_DNSDOMAINNAME(...)
#ifdef MAKE_SUID
# define IF_HTTPD(...) __VA_ARGS__ "CONFIG_HTTPD"
#else
# define IF_HTTPD(...) __VA_ARGS__
#endif
#define IF_NOT_HTTPD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_RANGES(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_RANGES"
#else
# define IF_FEATURE_HTTPD_RANGES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_RANGES(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_SETUID(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_SETUID"
#else
# define IF_FEATURE_HTTPD_SETUID(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_SETUID(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_BASIC_AUTH(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_BASIC_AUTH"
#else
# define IF_FEATURE_HTTPD_BASIC_AUTH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_BASIC_AUTH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_AUTH_MD5(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_AUTH_MD5"
#else
# define IF_FEATURE_HTTPD_AUTH_MD5(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_AUTH_MD5(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_CGI(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_CGI"
#else
# define IF_FEATURE_HTTPD_CGI(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_CGI(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_CONFIG_WITH_SCRIPT_INTERPR(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_CONFIG_WITH_SCRIPT_INTERPR"
#else
# define IF_FEATURE_HTTPD_CONFIG_WITH_SCRIPT_INTERPR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_CONFIG_WITH_SCRIPT_INTERPR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_SET_REMOTE_PORT_TO_ENV(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_SET_REMOTE_PORT_TO_ENV"
#else
# define IF_FEATURE_HTTPD_SET_REMOTE_PORT_TO_ENV(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_SET_REMOTE_PORT_TO_ENV(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_ENCODE_URL_STR(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_ENCODE_URL_STR"
#else
# define IF_FEATURE_HTTPD_ENCODE_URL_STR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_ENCODE_URL_STR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_ERROR_PAGES(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_ERROR_PAGES"
#else
# define IF_FEATURE_HTTPD_ERROR_PAGES(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_ERROR_PAGES(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_PROXY(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_PROXY"
#else
# define IF_FEATURE_HTTPD_PROXY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_PROXY(...)
#ifdef MAKE_SUID
# define IF_FEATURE_HTTPD_GZIP(...) __VA_ARGS__ "CONFIG_FEATURE_HTTPD_GZIP"
#else
# define IF_FEATURE_HTTPD_GZIP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_HTTPD_GZIP(...)
#ifdef MAKE_SUID
# define IF_IFCONFIG(...) __VA_ARGS__ "CONFIG_IFCONFIG"
#else
# define IF_IFCONFIG(...) __VA_ARGS__
#endif
#define IF_NOT_IFCONFIG(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IFCONFIG_STATUS(...) __VA_ARGS__ "CONFIG_FEATURE_IFCONFIG_STATUS"
#else
# define IF_FEATURE_IFCONFIG_STATUS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IFCONFIG_STATUS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IFCONFIG_SLIP(...) __VA_ARGS__ "CONFIG_FEATURE_IFCONFIG_SLIP"
#else
# define IF_FEATURE_IFCONFIG_SLIP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IFCONFIG_SLIP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IFCONFIG_MEMSTART_IOADDR_IRQ(...) __VA_ARGS__ "CONFIG_FEATURE_IFCONFIG_MEMSTART_IOADDR_IRQ"
#else
# define IF_FEATURE_IFCONFIG_MEMSTART_IOADDR_IRQ(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IFCONFIG_MEMSTART_IOADDR_IRQ(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IFCONFIG_HW(...) __VA_ARGS__ "CONFIG_FEATURE_IFCONFIG_HW"
#else
# define IF_FEATURE_IFCONFIG_HW(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IFCONFIG_HW(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IFCONFIG_BROADCAST_PLUS(...) __VA_ARGS__ "CONFIG_FEATURE_IFCONFIG_BROADCAST_PLUS"
#else
# define IF_FEATURE_IFCONFIG_BROADCAST_PLUS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IFCONFIG_BROADCAST_PLUS(...)
#ifdef MAKE_SUID
# define IF_IFENSLAVE(...) __VA_ARGS__ "CONFIG_IFENSLAVE"
#else
# define IF_IFENSLAVE(...) __VA_ARGS__
#endif
#define IF_NOT_IFENSLAVE(...)
#ifdef MAKE_SUID
# define IF_IFPLUGD(...) __VA_ARGS__ "CONFIG_IFPLUGD"
#else
# define IF_IFPLUGD(...) __VA_ARGS__
#endif
#define IF_NOT_IFPLUGD(...)
#ifdef MAKE_SUID
# define IF_IFUP(...) __VA_ARGS__ "CONFIG_IFUP"
#else
# define IF_IFUP(...) __VA_ARGS__
#endif
#define IF_NOT_IFUP(...)
#ifdef MAKE_SUID
# define IF_IFDOWN(...) __VA_ARGS__ "CONFIG_IFDOWN"
#else
# define IF_IFDOWN(...) __VA_ARGS__
#endif
#define IF_NOT_IFDOWN(...)
#define CONFIG_IFUPDOWN_IFSTATE_PATH "/var/run/ifstate"
#ifdef MAKE_SUID
# define IF_IFUPDOWN_IFSTATE_PATH(...) __VA_ARGS__ "CONFIG_IFUPDOWN_IFSTATE_PATH"
#else
# define IF_IFUPDOWN_IFSTATE_PATH(...) __VA_ARGS__
#endif
#define IF_NOT_IFUPDOWN_IFSTATE_PATH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IFUPDOWN_IP(...) __VA_ARGS__ "CONFIG_FEATURE_IFUPDOWN_IP"
#else
# define IF_FEATURE_IFUPDOWN_IP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IFUPDOWN_IP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IFUPDOWN_IPV4(...) __VA_ARGS__ "CONFIG_FEATURE_IFUPDOWN_IPV4"
#else
# define IF_FEATURE_IFUPDOWN_IPV4(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IFUPDOWN_IPV4(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IFUPDOWN_IPV6(...) __VA_ARGS__ "CONFIG_FEATURE_IFUPDOWN_IPV6"
#else
# define IF_FEATURE_IFUPDOWN_IPV6(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IFUPDOWN_IPV6(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IFUPDOWN_MAPPING(...) __VA_ARGS__ "CONFIG_FEATURE_IFUPDOWN_MAPPING"
#else
# define IF_FEATURE_IFUPDOWN_MAPPING(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IFUPDOWN_MAPPING(...)
#define IF_FEATURE_IFUPDOWN_EXTERNAL_DHCP(...)
#define IF_NOT_FEATURE_IFUPDOWN_EXTERNAL_DHCP(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_INETD(...) __VA_ARGS__ "CONFIG_INETD"
#else
# define IF_INETD(...) __VA_ARGS__
#endif
#define IF_NOT_INETD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_ECHO(...) __VA_ARGS__ "CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_ECHO"
#else
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_ECHO(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INETD_SUPPORT_BUILTIN_ECHO(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_DISCARD(...) __VA_ARGS__ "CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_DISCARD"
#else
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_DISCARD(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INETD_SUPPORT_BUILTIN_DISCARD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_TIME(...) __VA_ARGS__ "CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_TIME"
#else
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_TIME(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INETD_SUPPORT_BUILTIN_TIME(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_DAYTIME(...) __VA_ARGS__ "CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_DAYTIME"
#else
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_DAYTIME(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INETD_SUPPORT_BUILTIN_DAYTIME(...)
#ifdef MAKE_SUID
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_CHARGEN(...) __VA_ARGS__ "CONFIG_FEATURE_INETD_SUPPORT_BUILTIN_CHARGEN"
#else
# define IF_FEATURE_INETD_SUPPORT_BUILTIN_CHARGEN(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_INETD_SUPPORT_BUILTIN_CHARGEN(...)
#define IF_FEATURE_INETD_RPC(...)
#define IF_NOT_FEATURE_INETD_RPC(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_IP(...) __VA_ARGS__ "CONFIG_IP"
#else
# define IF_IP(...) __VA_ARGS__
#endif
#define IF_NOT_IP(...)
#ifdef MAKE_SUID
# define IF_IPADDR(...) __VA_ARGS__ "CONFIG_IPADDR"
#else
# define IF_IPADDR(...) __VA_ARGS__
#endif
#define IF_NOT_IPADDR(...)
#ifdef MAKE_SUID
# define IF_IPLINK(...) __VA_ARGS__ "CONFIG_IPLINK"
#else
# define IF_IPLINK(...) __VA_ARGS__
#endif
#define IF_NOT_IPLINK(...)
#ifdef MAKE_SUID
# define IF_IPROUTE(...) __VA_ARGS__ "CONFIG_IPROUTE"
#else
# define IF_IPROUTE(...) __VA_ARGS__
#endif
#define IF_NOT_IPROUTE(...)
#ifdef MAKE_SUID
# define IF_IPTUNNEL(...) __VA_ARGS__ "CONFIG_IPTUNNEL"
#else
# define IF_IPTUNNEL(...) __VA_ARGS__
#endif
#define IF_NOT_IPTUNNEL(...)
#ifdef MAKE_SUID
# define IF_IPRULE(...) __VA_ARGS__ "CONFIG_IPRULE"
#else
# define IF_IPRULE(...) __VA_ARGS__
#endif
#define IF_NOT_IPRULE(...)
#ifdef MAKE_SUID
# define IF_IPNEIGH(...) __VA_ARGS__ "CONFIG_IPNEIGH"
#else
# define IF_IPNEIGH(...) __VA_ARGS__
#endif
#define IF_NOT_IPNEIGH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IP_ADDRESS(...) __VA_ARGS__ "CONFIG_FEATURE_IP_ADDRESS"
#else
# define IF_FEATURE_IP_ADDRESS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IP_ADDRESS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IP_LINK(...) __VA_ARGS__ "CONFIG_FEATURE_IP_LINK"
#else
# define IF_FEATURE_IP_LINK(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IP_LINK(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IP_ROUTE(...) __VA_ARGS__ "CONFIG_FEATURE_IP_ROUTE"
#else
# define IF_FEATURE_IP_ROUTE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IP_ROUTE(...)
#define CONFIG_FEATURE_IP_ROUTE_DIR "/etc/iproute2"
#ifdef MAKE_SUID
# define IF_FEATURE_IP_ROUTE_DIR(...) __VA_ARGS__ "CONFIG_FEATURE_IP_ROUTE_DIR"
#else
# define IF_FEATURE_IP_ROUTE_DIR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IP_ROUTE_DIR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IP_TUNNEL(...) __VA_ARGS__ "CONFIG_FEATURE_IP_TUNNEL"
#else
# define IF_FEATURE_IP_TUNNEL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IP_TUNNEL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IP_RULE(...) __VA_ARGS__ "CONFIG_FEATURE_IP_RULE"
#else
# define IF_FEATURE_IP_RULE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IP_RULE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IP_NEIGH(...) __VA_ARGS__ "CONFIG_FEATURE_IP_NEIGH"
#else
# define IF_FEATURE_IP_NEIGH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IP_NEIGH(...)
#define IF_FEATURE_IP_RARE_PROTOCOLS(...)
#define IF_NOT_FEATURE_IP_RARE_PROTOCOLS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_IPCALC(...) __VA_ARGS__ "CONFIG_IPCALC"
#else
# define IF_IPCALC(...) __VA_ARGS__
#endif
#define IF_NOT_IPCALC(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IPCALC_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_IPCALC_LONG_OPTIONS"
#else
# define IF_FEATURE_IPCALC_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IPCALC_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IPCALC_FANCY(...) __VA_ARGS__ "CONFIG_FEATURE_IPCALC_FANCY"
#else
# define IF_FEATURE_IPCALC_FANCY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IPCALC_FANCY(...)
#ifdef MAKE_SUID
# define IF_FAKEIDENTD(...) __VA_ARGS__ "CONFIG_FAKEIDENTD"
#else
# define IF_FAKEIDENTD(...) __VA_ARGS__
#endif
#define IF_NOT_FAKEIDENTD(...)
#ifdef MAKE_SUID
# define IF_NAMEIF(...) __VA_ARGS__ "CONFIG_NAMEIF"
#else
# define IF_NAMEIF(...) __VA_ARGS__
#endif
#define IF_NOT_NAMEIF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_NAMEIF_EXTENDED(...) __VA_ARGS__ "CONFIG_FEATURE_NAMEIF_EXTENDED"
#else
# define IF_FEATURE_NAMEIF_EXTENDED(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_NAMEIF_EXTENDED(...)
#ifdef MAKE_SUID
# define IF_NBDCLIENT(...) __VA_ARGS__ "CONFIG_NBDCLIENT"
#else
# define IF_NBDCLIENT(...) __VA_ARGS__
#endif
#define IF_NOT_NBDCLIENT(...)
#ifdef MAKE_SUID
# define IF_NC(...) __VA_ARGS__ "CONFIG_NC"
#else
# define IF_NC(...) __VA_ARGS__
#endif
#define IF_NOT_NC(...)
#define IF_NETCAT(...)
#define IF_NOT_NETCAT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_NC_SERVER(...) __VA_ARGS__ "CONFIG_NC_SERVER"
#else
# define IF_NC_SERVER(...) __VA_ARGS__
#endif
#define IF_NOT_NC_SERVER(...)
#ifdef MAKE_SUID
# define IF_NC_EXTRA(...) __VA_ARGS__ "CONFIG_NC_EXTRA"
#else
# define IF_NC_EXTRA(...) __VA_ARGS__
#endif
#define IF_NOT_NC_EXTRA(...)
#ifdef MAKE_SUID
# define IF_NC_110_COMPAT(...) __VA_ARGS__ "CONFIG_NC_110_COMPAT"
#else
# define IF_NC_110_COMPAT(...) __VA_ARGS__
#endif
#define IF_NOT_NC_110_COMPAT(...)
#ifdef MAKE_SUID
# define IF_NETSTAT(...) __VA_ARGS__ "CONFIG_NETSTAT"
#else
# define IF_NETSTAT(...) __VA_ARGS__
#endif
#define IF_NOT_NETSTAT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_NETSTAT_WIDE(...) __VA_ARGS__ "CONFIG_FEATURE_NETSTAT_WIDE"
#else
# define IF_FEATURE_NETSTAT_WIDE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_NETSTAT_WIDE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_NETSTAT_PRG(...) __VA_ARGS__ "CONFIG_FEATURE_NETSTAT_PRG"
#else
# define IF_FEATURE_NETSTAT_PRG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_NETSTAT_PRG(...)
#ifdef MAKE_SUID
# define IF_NSLOOKUP(...) __VA_ARGS__ "CONFIG_NSLOOKUP"
#else
# define IF_NSLOOKUP(...) __VA_ARGS__
#endif
#define IF_NOT_NSLOOKUP(...)
#ifdef MAKE_SUID
# define IF_NTPD(...) __VA_ARGS__ "CONFIG_NTPD"
#else
# define IF_NTPD(...) __VA_ARGS__
#endif
#define IF_NOT_NTPD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_NTPD_SERVER(...) __VA_ARGS__ "CONFIG_FEATURE_NTPD_SERVER"
#else
# define IF_FEATURE_NTPD_SERVER(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_NTPD_SERVER(...)
#ifdef MAKE_SUID
# define IF_FEATURE_NTPD_CONF(...) __VA_ARGS__ "CONFIG_FEATURE_NTPD_CONF"
#else
# define IF_FEATURE_NTPD_CONF(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_NTPD_CONF(...)
#ifdef MAKE_SUID
# define IF_PING(...) __VA_ARGS__ "CONFIG_PING"
#else
# define IF_PING(...) __VA_ARGS__
#endif
#define IF_NOT_PING(...)
#ifdef MAKE_SUID
# define IF_PING6(...) __VA_ARGS__ "CONFIG_PING6"
#else
# define IF_PING6(...) __VA_ARGS__
#endif
#define IF_NOT_PING6(...)
#ifdef MAKE_SUID
# define IF_FEATURE_FANCY_PING(...) __VA_ARGS__ "CONFIG_FEATURE_FANCY_PING"
#else
# define IF_FEATURE_FANCY_PING(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_FANCY_PING(...)
#ifdef MAKE_SUID
# define IF_PSCAN(...) __VA_ARGS__ "CONFIG_PSCAN"
#else
# define IF_PSCAN(...) __VA_ARGS__
#endif
#define IF_NOT_PSCAN(...)
#ifdef MAKE_SUID
# define IF_ROUTE(...) __VA_ARGS__ "CONFIG_ROUTE"
#else
# define IF_ROUTE(...) __VA_ARGS__
#endif
#define IF_NOT_ROUTE(...)
#ifdef MAKE_SUID
# define IF_SLATTACH(...) __VA_ARGS__ "CONFIG_SLATTACH"
#else
# define IF_SLATTACH(...) __VA_ARGS__
#endif
#define IF_NOT_SLATTACH(...)
#ifdef MAKE_SUID
# define IF_SSL_CLIENT(...) __VA_ARGS__ "CONFIG_SSL_CLIENT"
#else
# define IF_SSL_CLIENT(...) __VA_ARGS__
#endif
#define IF_NOT_SSL_CLIENT(...)
#ifdef MAKE_SUID
# define IF_TCPSVD(...) __VA_ARGS__ "CONFIG_TCPSVD"
#else
# define IF_TCPSVD(...) __VA_ARGS__
#endif
#define IF_NOT_TCPSVD(...)
#ifdef MAKE_SUID
# define IF_UDPSVD(...) __VA_ARGS__ "CONFIG_UDPSVD"
#else
# define IF_UDPSVD(...) __VA_ARGS__
#endif
#define IF_NOT_UDPSVD(...)
#ifdef MAKE_SUID
# define IF_TELNET(...) __VA_ARGS__ "CONFIG_TELNET"
#else
# define IF_TELNET(...) __VA_ARGS__
#endif
#define IF_NOT_TELNET(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TELNET_TTYPE(...) __VA_ARGS__ "CONFIG_FEATURE_TELNET_TTYPE"
#else
# define IF_FEATURE_TELNET_TTYPE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TELNET_TTYPE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TELNET_AUTOLOGIN(...) __VA_ARGS__ "CONFIG_FEATURE_TELNET_AUTOLOGIN"
#else
# define IF_FEATURE_TELNET_AUTOLOGIN(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TELNET_AUTOLOGIN(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TELNET_WIDTH(...) __VA_ARGS__ "CONFIG_FEATURE_TELNET_WIDTH"
#else
# define IF_FEATURE_TELNET_WIDTH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TELNET_WIDTH(...)
#ifdef MAKE_SUID
# define IF_TELNETD(...) __VA_ARGS__ "CONFIG_TELNETD"
#else
# define IF_TELNETD(...) __VA_ARGS__
#endif
#define IF_NOT_TELNETD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TELNETD_STANDALONE(...) __VA_ARGS__ "CONFIG_FEATURE_TELNETD_STANDALONE"
#else
# define IF_FEATURE_TELNETD_STANDALONE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TELNETD_STANDALONE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TELNETD_INETD_WAIT(...) __VA_ARGS__ "CONFIG_FEATURE_TELNETD_INETD_WAIT"
#else
# define IF_FEATURE_TELNETD_INETD_WAIT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TELNETD_INETD_WAIT(...)
#ifdef MAKE_SUID
# define IF_TFTP(...) __VA_ARGS__ "CONFIG_TFTP"
#else
# define IF_TFTP(...) __VA_ARGS__
#endif
#define IF_NOT_TFTP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TFTP_PROGRESS_BAR(...) __VA_ARGS__ "CONFIG_FEATURE_TFTP_PROGRESS_BAR"
#else
# define IF_FEATURE_TFTP_PROGRESS_BAR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TFTP_PROGRESS_BAR(...)
#ifdef MAKE_SUID
# define IF_TFTPD(...) __VA_ARGS__ "CONFIG_TFTPD"
#else
# define IF_TFTPD(...) __VA_ARGS__
#endif
#define IF_NOT_TFTPD(...)

/*
 * Common options for tftp/tftpd
 */
#ifdef MAKE_SUID
# define IF_FEATURE_TFTP_GET(...) __VA_ARGS__ "CONFIG_FEATURE_TFTP_GET"
#else
# define IF_FEATURE_TFTP_GET(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TFTP_GET(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TFTP_PUT(...) __VA_ARGS__ "CONFIG_FEATURE_TFTP_PUT"
#else
# define IF_FEATURE_TFTP_PUT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TFTP_PUT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TFTP_BLOCKSIZE(...) __VA_ARGS__ "CONFIG_FEATURE_TFTP_BLOCKSIZE"
#else
# define IF_FEATURE_TFTP_BLOCKSIZE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TFTP_BLOCKSIZE(...)
#define IF_TFTP_DEBUG(...)
#define IF_NOT_TFTP_DEBUG(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_TLS(...) __VA_ARGS__ "CONFIG_TLS"
#else
# define IF_TLS(...) __VA_ARGS__
#endif
#define IF_NOT_TLS(...)
#ifdef MAKE_SUID
# define IF_TRACEROUTE(...) __VA_ARGS__ "CONFIG_TRACEROUTE"
#else
# define IF_TRACEROUTE(...) __VA_ARGS__
#endif
#define IF_NOT_TRACEROUTE(...)
#ifdef MAKE_SUID
# define IF_TRACEROUTE6(...) __VA_ARGS__ "CONFIG_TRACEROUTE6"
#else
# define IF_TRACEROUTE6(...) __VA_ARGS__
#endif
#define IF_NOT_TRACEROUTE6(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TRACEROUTE_VERBOSE(...) __VA_ARGS__ "CONFIG_FEATURE_TRACEROUTE_VERBOSE"
#else
# define IF_FEATURE_TRACEROUTE_VERBOSE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TRACEROUTE_VERBOSE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TRACEROUTE_USE_ICMP(...) __VA_ARGS__ "CONFIG_FEATURE_TRACEROUTE_USE_ICMP"
#else
# define IF_FEATURE_TRACEROUTE_USE_ICMP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TRACEROUTE_USE_ICMP(...)
#ifdef MAKE_SUID
# define IF_TUNCTL(...) __VA_ARGS__ "CONFIG_TUNCTL"
#else
# define IF_TUNCTL(...) __VA_ARGS__
#endif
#define IF_NOT_TUNCTL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TUNCTL_UG(...) __VA_ARGS__ "CONFIG_FEATURE_TUNCTL_UG"
#else
# define IF_FEATURE_TUNCTL_UG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TUNCTL_UG(...)
#ifdef MAKE_SUID
# define IF_VCONFIG(...) __VA_ARGS__ "CONFIG_VCONFIG"
#else
# define IF_VCONFIG(...) __VA_ARGS__
#endif
#define IF_NOT_VCONFIG(...)
#ifdef MAKE_SUID
# define IF_WGET(...) __VA_ARGS__ "CONFIG_WGET"
#else
# define IF_WGET(...) __VA_ARGS__
#endif
#define IF_NOT_WGET(...)
#ifdef MAKE_SUID
# define IF_FEATURE_WGET_LONG_OPTIONS(...) __VA_ARGS__ "CONFIG_FEATURE_WGET_LONG_OPTIONS"
#else
# define IF_FEATURE_WGET_LONG_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_WGET_LONG_OPTIONS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_WGET_STATUSBAR(...) __VA_ARGS__ "CONFIG_FEATURE_WGET_STATUSBAR"
#else
# define IF_FEATURE_WGET_STATUSBAR(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_WGET_STATUSBAR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_WGET_AUTHENTICATION(...) __VA_ARGS__ "CONFIG_FEATURE_WGET_AUTHENTICATION"
#else
# define IF_FEATURE_WGET_AUTHENTICATION(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_WGET_AUTHENTICATION(...)
#ifdef MAKE_SUID
# define IF_FEATURE_WGET_TIMEOUT(...) __VA_ARGS__ "CONFIG_FEATURE_WGET_TIMEOUT"
#else
# define IF_FEATURE_WGET_TIMEOUT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_WGET_TIMEOUT(...)
#ifdef MAKE_SUID
# define IF_FEATURE_WGET_HTTPS(...) __VA_ARGS__ "CONFIG_FEATURE_WGET_HTTPS"
#else
# define IF_FEATURE_WGET_HTTPS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_WGET_HTTPS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_WGET_OPENSSL(...) __VA_ARGS__ "CONFIG_FEATURE_WGET_OPENSSL"
#else
# define IF_FEATURE_WGET_OPENSSL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_WGET_OPENSSL(...)
#ifdef MAKE_SUID
# define IF_WHOIS(...) __VA_ARGS__ "CONFIG_WHOIS"
#else
# define IF_WHOIS(...) __VA_ARGS__
#endif
#define IF_NOT_WHOIS(...)
#ifdef MAKE_SUID
# define IF_ZCIP(...) __VA_ARGS__ "CONFIG_ZCIP"
#else
# define IF_ZCIP(...) __VA_ARGS__
#endif
#define IF_NOT_ZCIP(...)
#ifdef MAKE_SUID
# define IF_UDHCPD(...) __VA_ARGS__ "CONFIG_UDHCPD"
#else
# define IF_UDHCPD(...) __VA_ARGS__
#endif
#define IF_NOT_UDHCPD(...)
#define IF_FEATURE_UDHCPD_BASE_IP_ON_MAC(...)
#define IF_NOT_FEATURE_UDHCPD_BASE_IP_ON_MAC(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_UDHCPD_WRITE_LEASES_EARLY(...) __VA_ARGS__ "CONFIG_FEATURE_UDHCPD_WRITE_LEASES_EARLY"
#else
# define IF_FEATURE_UDHCPD_WRITE_LEASES_EARLY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UDHCPD_WRITE_LEASES_EARLY(...)
#ifdef MAKE_SUID
# define IF_DHCPD_LEASES_FILE(...) __VA_ARGS__ "CONFIG_DHCPD_LEASES_FILE"
#else
# define IF_DHCPD_LEASES_FILE(...) __VA_ARGS__
#endif
#define IF_NOT_DHCPD_LEASES_FILE(...)
#ifdef MAKE_SUID
# define IF_DUMPLEASES(...) __VA_ARGS__ "CONFIG_DUMPLEASES"
#else
# define IF_DUMPLEASES(...) __VA_ARGS__
#endif
#define IF_NOT_DUMPLEASES(...)
#ifdef MAKE_SUID
# define IF_DHCPRELAY(...) __VA_ARGS__ "CONFIG_DHCPRELAY"
#else
# define IF_DHCPRELAY(...) __VA_ARGS__
#endif
#define IF_NOT_DHCPRELAY(...)
#ifdef MAKE_SUID
# define IF_UDHCPC(...) __VA_ARGS__ "CONFIG_UDHCPC"
#else
# define IF_UDHCPC(...) __VA_ARGS__
#endif
#define IF_NOT_UDHCPC(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UDHCPC_ARPING(...) __VA_ARGS__ "CONFIG_FEATURE_UDHCPC_ARPING"
#else
# define IF_FEATURE_UDHCPC_ARPING(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UDHCPC_ARPING(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UDHCPC_SANITIZEOPT(...) __VA_ARGS__ "CONFIG_FEATURE_UDHCPC_SANITIZEOPT"
#else
# define IF_FEATURE_UDHCPC_SANITIZEOPT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UDHCPC_SANITIZEOPT(...)
#ifdef MAKE_SUID
# define IF_UDHCPC_DEFAULT_SCRIPT(...) __VA_ARGS__ "CONFIG_UDHCPC_DEFAULT_SCRIPT"
#else
# define IF_UDHCPC_DEFAULT_SCRIPT(...) __VA_ARGS__
#endif
#define IF_NOT_UDHCPC_DEFAULT_SCRIPT(...)
#define IF_UDHCPC6(...)
#define IF_NOT_UDHCPC6(...) __VA_ARGS__
#define IF_FEATURE_UDHCPC6_RFC3646(...)
#define IF_NOT_FEATURE_UDHCPC6_RFC3646(...) __VA_ARGS__
#define IF_FEATURE_UDHCPC6_RFC4704(...)
#define IF_NOT_FEATURE_UDHCPC6_RFC4704(...) __VA_ARGS__
#define IF_FEATURE_UDHCPC6_RFC4833(...)
#define IF_NOT_FEATURE_UDHCPC6_RFC4833(...) __VA_ARGS__

/*
 * Common options for DHCP applets
 */
#define IF_FEATURE_UDHCP_PORT(...)
#define IF_NOT_FEATURE_UDHCP_PORT(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_UDHCP_DEBUG(...) __VA_ARGS__ "CONFIG_UDHCP_DEBUG"
#else
# define IF_UDHCP_DEBUG(...) __VA_ARGS__
#endif
#define IF_NOT_UDHCP_DEBUG(...)
#ifdef MAKE_SUID
# define IF_UDHCPC_SLACK_FOR_BUGGY_SERVERS(...) __VA_ARGS__ "CONFIG_UDHCPC_SLACK_FOR_BUGGY_SERVERS"
#else
# define IF_UDHCPC_SLACK_FOR_BUGGY_SERVERS(...) __VA_ARGS__
#endif
#define IF_NOT_UDHCPC_SLACK_FOR_BUGGY_SERVERS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UDHCP_RFC3397(...) __VA_ARGS__ "CONFIG_FEATURE_UDHCP_RFC3397"
#else
# define IF_FEATURE_UDHCP_RFC3397(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UDHCP_RFC3397(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UDHCP_8021Q(...) __VA_ARGS__ "CONFIG_FEATURE_UDHCP_8021Q"
#else
# define IF_FEATURE_UDHCP_8021Q(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UDHCP_8021Q(...)
#ifdef MAKE_SUID
# define IF_IFUPDOWN_UDHCPC_CMD_OPTIONS(...) __VA_ARGS__ "CONFIG_IFUPDOWN_UDHCPC_CMD_OPTIONS"
#else
# define IF_IFUPDOWN_UDHCPC_CMD_OPTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_IFUPDOWN_UDHCPC_CMD_OPTIONS(...)

/*
 * Print Utilities
 */
#ifdef MAKE_SUID
# define IF_LPD(...) __VA_ARGS__ "CONFIG_LPD"
#else
# define IF_LPD(...) __VA_ARGS__
#endif
#define IF_NOT_LPD(...)
#ifdef MAKE_SUID
# define IF_LPR(...) __VA_ARGS__ "CONFIG_LPR"
#else
# define IF_LPR(...) __VA_ARGS__
#endif
#define IF_NOT_LPR(...)
#ifdef MAKE_SUID
# define IF_LPQ(...) __VA_ARGS__ "CONFIG_LPQ"
#else
# define IF_LPQ(...) __VA_ARGS__
#endif
#define IF_NOT_LPQ(...)

/*
 * Mail Utilities
 */
#ifdef MAKE_SUID
# define IF_MAKEMIME(...) __VA_ARGS__ "CONFIG_MAKEMIME"
#else
# define IF_MAKEMIME(...) __VA_ARGS__
#endif
#define IF_NOT_MAKEMIME(...)
#ifdef MAKE_SUID
# define IF_POPMAILDIR(...) __VA_ARGS__ "CONFIG_POPMAILDIR"
#else
# define IF_POPMAILDIR(...) __VA_ARGS__
#endif
#define IF_NOT_POPMAILDIR(...)
#ifdef MAKE_SUID
# define IF_FEATURE_POPMAILDIR_DELIVERY(...) __VA_ARGS__ "CONFIG_FEATURE_POPMAILDIR_DELIVERY"
#else
# define IF_FEATURE_POPMAILDIR_DELIVERY(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_POPMAILDIR_DELIVERY(...)
#ifdef MAKE_SUID
# define IF_REFORMIME(...) __VA_ARGS__ "CONFIG_REFORMIME"
#else
# define IF_REFORMIME(...) __VA_ARGS__
#endif
#define IF_NOT_REFORMIME(...)
#ifdef MAKE_SUID
# define IF_FEATURE_REFORMIME_COMPAT(...) __VA_ARGS__ "CONFIG_FEATURE_REFORMIME_COMPAT"
#else
# define IF_FEATURE_REFORMIME_COMPAT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_REFORMIME_COMPAT(...)
#ifdef MAKE_SUID
# define IF_SENDMAIL(...) __VA_ARGS__ "CONFIG_SENDMAIL"
#else
# define IF_SENDMAIL(...) __VA_ARGS__
#endif
#define IF_NOT_SENDMAIL(...)
#ifdef MAKE_SUID
# define IF_FEATURE_MIME_CHARSET(...) __VA_ARGS__ "CONFIG_FEATURE_MIME_CHARSET"
#else
# define IF_FEATURE_MIME_CHARSET(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_MIME_CHARSET(...)

/*
 * Process Utilities
 */
#ifdef MAKE_SUID
# define IF_FREE(...) __VA_ARGS__ "CONFIG_FREE"
#else
# define IF_FREE(...) __VA_ARGS__
#endif
#define IF_NOT_FREE(...)
#ifdef MAKE_SUID
# define IF_FUSER(...) __VA_ARGS__ "CONFIG_FUSER"
#else
# define IF_FUSER(...) __VA_ARGS__
#endif
#define IF_NOT_FUSER(...)
#ifdef MAKE_SUID
# define IF_IOSTAT(...) __VA_ARGS__ "CONFIG_IOSTAT"
#else
# define IF_IOSTAT(...) __VA_ARGS__
#endif
#define IF_NOT_IOSTAT(...)
#ifdef MAKE_SUID
# define IF_KILL(...) __VA_ARGS__ "CONFIG_KILL"
#else
# define IF_KILL(...) __VA_ARGS__
#endif
#define IF_NOT_KILL(...)
#ifdef MAKE_SUID
# define IF_KILLALL(...) __VA_ARGS__ "CONFIG_KILLALL"
#else
# define IF_KILLALL(...) __VA_ARGS__
#endif
#define IF_NOT_KILLALL(...)
#ifdef MAKE_SUID
# define IF_KILLALL5(...) __VA_ARGS__ "CONFIG_KILLALL5"
#else
# define IF_KILLALL5(...) __VA_ARGS__
#endif
#define IF_NOT_KILLALL5(...)
#ifdef MAKE_SUID
# define IF_LSOF(...) __VA_ARGS__ "CONFIG_LSOF"
#else
# define IF_LSOF(...) __VA_ARGS__
#endif
#define IF_NOT_LSOF(...)
#ifdef MAKE_SUID
# define IF_MPSTAT(...) __VA_ARGS__ "CONFIG_MPSTAT"
#else
# define IF_MPSTAT(...) __VA_ARGS__
#endif
#define IF_NOT_MPSTAT(...)
#ifdef MAKE_SUID
# define IF_NMETER(...) __VA_ARGS__ "CONFIG_NMETER"
#else
# define IF_NMETER(...) __VA_ARGS__
#endif
#define IF_NOT_NMETER(...)
#ifdef MAKE_SUID
# define IF_PGREP(...) __VA_ARGS__ "CONFIG_PGREP"
#else
# define IF_PGREP(...) __VA_ARGS__
#endif
#define IF_NOT_PGREP(...)
#ifdef MAKE_SUID
# define IF_PKILL(...) __VA_ARGS__ "CONFIG_PKILL"
#else
# define IF_PKILL(...) __VA_ARGS__
#endif
#define IF_NOT_PKILL(...)
#ifdef MAKE_SUID
# define IF_PIDOF(...) __VA_ARGS__ "CONFIG_PIDOF"
#else
# define IF_PIDOF(...) __VA_ARGS__
#endif
#define IF_NOT_PIDOF(...)
#ifdef MAKE_SUID
# define IF_FEATURE_PIDOF_SINGLE(...) __VA_ARGS__ "CONFIG_FEATURE_PIDOF_SINGLE"
#else
# define IF_FEATURE_PIDOF_SINGLE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_PIDOF_SINGLE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_PIDOF_OMIT(...) __VA_ARGS__ "CONFIG_FEATURE_PIDOF_OMIT"
#else
# define IF_FEATURE_PIDOF_OMIT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_PIDOF_OMIT(...)
#ifdef MAKE_SUID
# define IF_PMAP(...) __VA_ARGS__ "CONFIG_PMAP"
#else
# define IF_PMAP(...) __VA_ARGS__
#endif
#define IF_NOT_PMAP(...)
#ifdef MAKE_SUID
# define IF_POWERTOP(...) __VA_ARGS__ "CONFIG_POWERTOP"
#else
# define IF_POWERTOP(...) __VA_ARGS__
#endif
#define IF_NOT_POWERTOP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_POWERTOP_INTERACTIVE(...) __VA_ARGS__ "CONFIG_FEATURE_POWERTOP_INTERACTIVE"
#else
# define IF_FEATURE_POWERTOP_INTERACTIVE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_POWERTOP_INTERACTIVE(...)
#ifdef MAKE_SUID
# define IF_PS(...) __VA_ARGS__ "CONFIG_PS"
#else
# define IF_PS(...) __VA_ARGS__
#endif
#define IF_NOT_PS(...)
#define IF_FEATURE_PS_WIDE(...)
#define IF_NOT_FEATURE_PS_WIDE(...) __VA_ARGS__
#define IF_FEATURE_PS_LONG(...)
#define IF_NOT_FEATURE_PS_LONG(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_PS_TIME(...) __VA_ARGS__ "CONFIG_FEATURE_PS_TIME"
#else
# define IF_FEATURE_PS_TIME(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_PS_TIME(...)
#define IF_FEATURE_PS_UNUSUAL_SYSTEMS(...)
#define IF_NOT_FEATURE_PS_UNUSUAL_SYSTEMS(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_PS_ADDITIONAL_COLUMNS(...) __VA_ARGS__ "CONFIG_FEATURE_PS_ADDITIONAL_COLUMNS"
#else
# define IF_FEATURE_PS_ADDITIONAL_COLUMNS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_PS_ADDITIONAL_COLUMNS(...)
#ifdef MAKE_SUID
# define IF_PSTREE(...) __VA_ARGS__ "CONFIG_PSTREE"
#else
# define IF_PSTREE(...) __VA_ARGS__
#endif
#define IF_NOT_PSTREE(...)
#ifdef MAKE_SUID
# define IF_PWDX(...) __VA_ARGS__ "CONFIG_PWDX"
#else
# define IF_PWDX(...) __VA_ARGS__
#endif
#define IF_NOT_PWDX(...)
#ifdef MAKE_SUID
# define IF_SMEMCAP(...) __VA_ARGS__ "CONFIG_SMEMCAP"
#else
# define IF_SMEMCAP(...) __VA_ARGS__
#endif
#define IF_NOT_SMEMCAP(...)
#ifdef MAKE_SUID
# define IF_BB_SYSCTL(...) __VA_ARGS__ "CONFIG_BB_SYSCTL"
#else
# define IF_BB_SYSCTL(...) __VA_ARGS__
#endif
#define IF_NOT_BB_SYSCTL(...)
#ifdef MAKE_SUID
# define IF_TOP(...) __VA_ARGS__ "CONFIG_TOP"
#else
# define IF_TOP(...) __VA_ARGS__
#endif
#define IF_NOT_TOP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TOP_INTERACTIVE(...) __VA_ARGS__ "CONFIG_FEATURE_TOP_INTERACTIVE"
#else
# define IF_FEATURE_TOP_INTERACTIVE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TOP_INTERACTIVE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TOP_CPU_USAGE_PERCENTAGE(...) __VA_ARGS__ "CONFIG_FEATURE_TOP_CPU_USAGE_PERCENTAGE"
#else
# define IF_FEATURE_TOP_CPU_USAGE_PERCENTAGE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TOP_CPU_USAGE_PERCENTAGE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TOP_CPU_GLOBAL_PERCENTS(...) __VA_ARGS__ "CONFIG_FEATURE_TOP_CPU_GLOBAL_PERCENTS"
#else
# define IF_FEATURE_TOP_CPU_GLOBAL_PERCENTS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TOP_CPU_GLOBAL_PERCENTS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TOP_SMP_CPU(...) __VA_ARGS__ "CONFIG_FEATURE_TOP_SMP_CPU"
#else
# define IF_FEATURE_TOP_SMP_CPU(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TOP_SMP_CPU(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TOP_DECIMALS(...) __VA_ARGS__ "CONFIG_FEATURE_TOP_DECIMALS"
#else
# define IF_FEATURE_TOP_DECIMALS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TOP_DECIMALS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TOP_SMP_PROCESS(...) __VA_ARGS__ "CONFIG_FEATURE_TOP_SMP_PROCESS"
#else
# define IF_FEATURE_TOP_SMP_PROCESS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TOP_SMP_PROCESS(...)
#ifdef MAKE_SUID
# define IF_FEATURE_TOPMEM(...) __VA_ARGS__ "CONFIG_FEATURE_TOPMEM"
#else
# define IF_FEATURE_TOPMEM(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_TOPMEM(...)
#ifdef MAKE_SUID
# define IF_UPTIME(...) __VA_ARGS__ "CONFIG_UPTIME"
#else
# define IF_UPTIME(...) __VA_ARGS__
#endif
#define IF_NOT_UPTIME(...)
#ifdef MAKE_SUID
# define IF_FEATURE_UPTIME_UTMP_SUPPORT(...) __VA_ARGS__ "CONFIG_FEATURE_UPTIME_UTMP_SUPPORT"
#else
# define IF_FEATURE_UPTIME_UTMP_SUPPORT(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_UPTIME_UTMP_SUPPORT(...)
#ifdef MAKE_SUID
# define IF_WATCH(...) __VA_ARGS__ "CONFIG_WATCH"
#else
# define IF_WATCH(...) __VA_ARGS__
#endif
#define IF_NOT_WATCH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SHOW_THREADS(...) __VA_ARGS__ "CONFIG_FEATURE_SHOW_THREADS"
#else
# define IF_FEATURE_SHOW_THREADS(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SHOW_THREADS(...)

/*
 * Runit Utilities
 */
#ifdef MAKE_SUID
# define IF_CHPST(...) __VA_ARGS__ "CONFIG_CHPST"
#else
# define IF_CHPST(...) __VA_ARGS__
#endif
#define IF_NOT_CHPST(...)
#ifdef MAKE_SUID
# define IF_SETUIDGID(...) __VA_ARGS__ "CONFIG_SETUIDGID"
#else
# define IF_SETUIDGID(...) __VA_ARGS__
#endif
#define IF_NOT_SETUIDGID(...)
#ifdef MAKE_SUID
# define IF_ENVUIDGID(...) __VA_ARGS__ "CONFIG_ENVUIDGID"
#else
# define IF_ENVUIDGID(...) __VA_ARGS__
#endif
#define IF_NOT_ENVUIDGID(...)
#ifdef MAKE_SUID
# define IF_ENVDIR(...) __VA_ARGS__ "CONFIG_ENVDIR"
#else
# define IF_ENVDIR(...) __VA_ARGS__
#endif
#define IF_NOT_ENVDIR(...)
#ifdef MAKE_SUID
# define IF_SOFTLIMIT(...) __VA_ARGS__ "CONFIG_SOFTLIMIT"
#else
# define IF_SOFTLIMIT(...) __VA_ARGS__
#endif
#define IF_NOT_SOFTLIMIT(...)
#ifdef MAKE_SUID
# define IF_RUNSV(...) __VA_ARGS__ "CONFIG_RUNSV"
#else
# define IF_RUNSV(...) __VA_ARGS__
#endif
#define IF_NOT_RUNSV(...)
#ifdef MAKE_SUID
# define IF_RUNSVDIR(...) __VA_ARGS__ "CONFIG_RUNSVDIR"
#else
# define IF_RUNSVDIR(...) __VA_ARGS__
#endif
#define IF_NOT_RUNSVDIR(...)
#define IF_FEATURE_RUNSVDIR_LOG(...)
#define IF_NOT_FEATURE_RUNSVDIR_LOG(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_SV(...) __VA_ARGS__ "CONFIG_SV"
#else
# define IF_SV(...) __VA_ARGS__
#endif
#define IF_NOT_SV(...)
#ifdef MAKE_SUID
# define IF_SV_DEFAULT_SERVICE_DIR(...) __VA_ARGS__ "CONFIG_SV_DEFAULT_SERVICE_DIR"
#else
# define IF_SV_DEFAULT_SERVICE_DIR(...) __VA_ARGS__
#endif
#define IF_NOT_SV_DEFAULT_SERVICE_DIR(...)
#ifdef MAKE_SUID
# define IF_SVC(...) __VA_ARGS__ "CONFIG_SVC"
#else
# define IF_SVC(...) __VA_ARGS__
#endif
#define IF_NOT_SVC(...)
#ifdef MAKE_SUID
# define IF_SVLOGD(...) __VA_ARGS__ "CONFIG_SVLOGD"
#else
# define IF_SVLOGD(...) __VA_ARGS__
#endif
#define IF_NOT_SVLOGD(...)
#define IF_CHCON(...)
#define IF_NOT_CHCON(...) __VA_ARGS__
#define IF_GETENFORCE(...)
#define IF_NOT_GETENFORCE(...) __VA_ARGS__
#define IF_GETSEBOOL(...)
#define IF_NOT_GETSEBOOL(...) __VA_ARGS__
#define IF_LOAD_POLICY(...)
#define IF_NOT_LOAD_POLICY(...) __VA_ARGS__
#define IF_MATCHPATHCON(...)
#define IF_NOT_MATCHPATHCON(...) __VA_ARGS__
#define IF_RUNCON(...)
#define IF_NOT_RUNCON(...) __VA_ARGS__
#define IF_SELINUXENABLED(...)
#define IF_NOT_SELINUXENABLED(...) __VA_ARGS__
#define IF_SESTATUS(...)
#define IF_NOT_SESTATUS(...) __VA_ARGS__
#define IF_SETENFORCE(...)
#define IF_NOT_SETENFORCE(...) __VA_ARGS__
#define IF_SETFILES(...)
#define IF_NOT_SETFILES(...) __VA_ARGS__
#define IF_FEATURE_SETFILES_CHECK_OPTION(...)
#define IF_NOT_FEATURE_SETFILES_CHECK_OPTION(...) __VA_ARGS__
#define IF_RESTORECON(...)
#define IF_NOT_RESTORECON(...) __VA_ARGS__
#define IF_SETSEBOOL(...)
#define IF_NOT_SETSEBOOL(...) __VA_ARGS__

/*
 * Shells
 */
#ifdef MAKE_SUID
# define IF_SH_IS_ASH(...) __VA_ARGS__ "CONFIG_SH_IS_ASH"
#else
# define IF_SH_IS_ASH(...) __VA_ARGS__
#endif
#define IF_NOT_SH_IS_ASH(...)
#define IF_SH_IS_HUSH(...)
#define IF_NOT_SH_IS_HUSH(...) __VA_ARGS__
#define IF_SH_IS_NONE(...)
#define IF_NOT_SH_IS_NONE(...) __VA_ARGS__
#define IF_BASH_IS_ASH(...)
#define IF_NOT_BASH_IS_ASH(...) __VA_ARGS__
#define IF_BASH_IS_HUSH(...)
#define IF_NOT_BASH_IS_HUSH(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_BASH_IS_NONE(...) __VA_ARGS__ "CONFIG_BASH_IS_NONE"
#else
# define IF_BASH_IS_NONE(...) __VA_ARGS__
#endif
#define IF_NOT_BASH_IS_NONE(...)
#ifdef MAKE_SUID
# define IF_ASH(...) __VA_ARGS__ "CONFIG_ASH"
#else
# define IF_ASH(...) __VA_ARGS__
#endif
#define IF_NOT_ASH(...)
#ifdef MAKE_SUID
# define IF_ASH_OPTIMIZE_FOR_SIZE(...) __VA_ARGS__ "CONFIG_ASH_OPTIMIZE_FOR_SIZE"
#else
# define IF_ASH_OPTIMIZE_FOR_SIZE(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_OPTIMIZE_FOR_SIZE(...)
#ifdef MAKE_SUID
# define IF_ASH_INTERNAL_GLOB(...) __VA_ARGS__ "CONFIG_ASH_INTERNAL_GLOB"
#else
# define IF_ASH_INTERNAL_GLOB(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_INTERNAL_GLOB(...)
#ifdef MAKE_SUID
# define IF_ASH_BASH_COMPAT(...) __VA_ARGS__ "CONFIG_ASH_BASH_COMPAT"
#else
# define IF_ASH_BASH_COMPAT(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_BASH_COMPAT(...)
#ifdef MAKE_SUID
# define IF_ASH_JOB_CONTROL(...) __VA_ARGS__ "CONFIG_ASH_JOB_CONTROL"
#else
# define IF_ASH_JOB_CONTROL(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_JOB_CONTROL(...)
#ifdef MAKE_SUID
# define IF_ASH_ALIAS(...) __VA_ARGS__ "CONFIG_ASH_ALIAS"
#else
# define IF_ASH_ALIAS(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_ALIAS(...)
#ifdef MAKE_SUID
# define IF_ASH_RANDOM_SUPPORT(...) __VA_ARGS__ "CONFIG_ASH_RANDOM_SUPPORT"
#else
# define IF_ASH_RANDOM_SUPPORT(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_RANDOM_SUPPORT(...)
#ifdef MAKE_SUID
# define IF_ASH_EXPAND_PRMT(...) __VA_ARGS__ "CONFIG_ASH_EXPAND_PRMT"
#else
# define IF_ASH_EXPAND_PRMT(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_EXPAND_PRMT(...)
#ifdef MAKE_SUID
# define IF_ASH_IDLE_TIMEOUT(...) __VA_ARGS__ "CONFIG_ASH_IDLE_TIMEOUT"
#else
# define IF_ASH_IDLE_TIMEOUT(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_IDLE_TIMEOUT(...)
#ifdef MAKE_SUID
# define IF_ASH_MAIL(...) __VA_ARGS__ "CONFIG_ASH_MAIL"
#else
# define IF_ASH_MAIL(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_MAIL(...)
#ifdef MAKE_SUID
# define IF_ASH_ECHO(...) __VA_ARGS__ "CONFIG_ASH_ECHO"
#else
# define IF_ASH_ECHO(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_ECHO(...)
#ifdef MAKE_SUID
# define IF_ASH_PRINTF(...) __VA_ARGS__ "CONFIG_ASH_PRINTF"
#else
# define IF_ASH_PRINTF(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_PRINTF(...)
#ifdef MAKE_SUID
# define IF_ASH_TEST(...) __VA_ARGS__ "CONFIG_ASH_TEST"
#else
# define IF_ASH_TEST(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_TEST(...)
#ifdef MAKE_SUID
# define IF_ASH_HELP(...) __VA_ARGS__ "CONFIG_ASH_HELP"
#else
# define IF_ASH_HELP(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_HELP(...)
#ifdef MAKE_SUID
# define IF_ASH_GETOPTS(...) __VA_ARGS__ "CONFIG_ASH_GETOPTS"
#else
# define IF_ASH_GETOPTS(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_GETOPTS(...)
#ifdef MAKE_SUID
# define IF_ASH_CMDCMD(...) __VA_ARGS__ "CONFIG_ASH_CMDCMD"
#else
# define IF_ASH_CMDCMD(...) __VA_ARGS__
#endif
#define IF_NOT_ASH_CMDCMD(...)
#ifdef MAKE_SUID
# define IF_CTTYHACK(...) __VA_ARGS__ "CONFIG_CTTYHACK"
#else
# define IF_CTTYHACK(...) __VA_ARGS__
#endif
#define IF_NOT_CTTYHACK(...)
#ifdef MAKE_SUID
# define IF_HUSH(...) __VA_ARGS__ "CONFIG_HUSH"
#else
# define IF_HUSH(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH(...)
#ifdef MAKE_SUID
# define IF_HUSH_BASH_COMPAT(...) __VA_ARGS__ "CONFIG_HUSH_BASH_COMPAT"
#else
# define IF_HUSH_BASH_COMPAT(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_BASH_COMPAT(...)
#ifdef MAKE_SUID
# define IF_HUSH_BRACE_EXPANSION(...) __VA_ARGS__ "CONFIG_HUSH_BRACE_EXPANSION"
#else
# define IF_HUSH_BRACE_EXPANSION(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_BRACE_EXPANSION(...)
#ifdef MAKE_SUID
# define IF_HUSH_INTERACTIVE(...) __VA_ARGS__ "CONFIG_HUSH_INTERACTIVE"
#else
# define IF_HUSH_INTERACTIVE(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_INTERACTIVE(...)
#ifdef MAKE_SUID
# define IF_HUSH_SAVEHISTORY(...) __VA_ARGS__ "CONFIG_HUSH_SAVEHISTORY"
#else
# define IF_HUSH_SAVEHISTORY(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_SAVEHISTORY(...)
#ifdef MAKE_SUID
# define IF_HUSH_JOB(...) __VA_ARGS__ "CONFIG_HUSH_JOB"
#else
# define IF_HUSH_JOB(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_JOB(...)
#ifdef MAKE_SUID
# define IF_HUSH_TICK(...) __VA_ARGS__ "CONFIG_HUSH_TICK"
#else
# define IF_HUSH_TICK(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_TICK(...)
#ifdef MAKE_SUID
# define IF_HUSH_IF(...) __VA_ARGS__ "CONFIG_HUSH_IF"
#else
# define IF_HUSH_IF(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_IF(...)
#ifdef MAKE_SUID
# define IF_HUSH_LOOPS(...) __VA_ARGS__ "CONFIG_HUSH_LOOPS"
#else
# define IF_HUSH_LOOPS(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_LOOPS(...)
#ifdef MAKE_SUID
# define IF_HUSH_CASE(...) __VA_ARGS__ "CONFIG_HUSH_CASE"
#else
# define IF_HUSH_CASE(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_CASE(...)
#ifdef MAKE_SUID
# define IF_HUSH_FUNCTIONS(...) __VA_ARGS__ "CONFIG_HUSH_FUNCTIONS"
#else
# define IF_HUSH_FUNCTIONS(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_FUNCTIONS(...)
#ifdef MAKE_SUID
# define IF_HUSH_LOCAL(...) __VA_ARGS__ "CONFIG_HUSH_LOCAL"
#else
# define IF_HUSH_LOCAL(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_LOCAL(...)
#ifdef MAKE_SUID
# define IF_HUSH_RANDOM_SUPPORT(...) __VA_ARGS__ "CONFIG_HUSH_RANDOM_SUPPORT"
#else
# define IF_HUSH_RANDOM_SUPPORT(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_RANDOM_SUPPORT(...)
#ifdef MAKE_SUID
# define IF_HUSH_MODE_X(...) __VA_ARGS__ "CONFIG_HUSH_MODE_X"
#else
# define IF_HUSH_MODE_X(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_MODE_X(...)
#ifdef MAKE_SUID
# define IF_HUSH_ECHO(...) __VA_ARGS__ "CONFIG_HUSH_ECHO"
#else
# define IF_HUSH_ECHO(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_ECHO(...)
#ifdef MAKE_SUID
# define IF_HUSH_PRINTF(...) __VA_ARGS__ "CONFIG_HUSH_PRINTF"
#else
# define IF_HUSH_PRINTF(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_PRINTF(...)
#ifdef MAKE_SUID
# define IF_HUSH_TEST(...) __VA_ARGS__ "CONFIG_HUSH_TEST"
#else
# define IF_HUSH_TEST(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_TEST(...)
#ifdef MAKE_SUID
# define IF_HUSH_HELP(...) __VA_ARGS__ "CONFIG_HUSH_HELP"
#else
# define IF_HUSH_HELP(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_HELP(...)
#ifdef MAKE_SUID
# define IF_HUSH_EXPORT(...) __VA_ARGS__ "CONFIG_HUSH_EXPORT"
#else
# define IF_HUSH_EXPORT(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_EXPORT(...)
#ifdef MAKE_SUID
# define IF_HUSH_EXPORT_N(...) __VA_ARGS__ "CONFIG_HUSH_EXPORT_N"
#else
# define IF_HUSH_EXPORT_N(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_EXPORT_N(...)
#ifdef MAKE_SUID
# define IF_HUSH_READONLY(...) __VA_ARGS__ "CONFIG_HUSH_READONLY"
#else
# define IF_HUSH_READONLY(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_READONLY(...)
#ifdef MAKE_SUID
# define IF_HUSH_KILL(...) __VA_ARGS__ "CONFIG_HUSH_KILL"
#else
# define IF_HUSH_KILL(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_KILL(...)
#ifdef MAKE_SUID
# define IF_HUSH_WAIT(...) __VA_ARGS__ "CONFIG_HUSH_WAIT"
#else
# define IF_HUSH_WAIT(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_WAIT(...)
#ifdef MAKE_SUID
# define IF_HUSH_TRAP(...) __VA_ARGS__ "CONFIG_HUSH_TRAP"
#else
# define IF_HUSH_TRAP(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_TRAP(...)
#ifdef MAKE_SUID
# define IF_HUSH_TYPE(...) __VA_ARGS__ "CONFIG_HUSH_TYPE"
#else
# define IF_HUSH_TYPE(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_TYPE(...)
#ifdef MAKE_SUID
# define IF_HUSH_TIMES(...) __VA_ARGS__ "CONFIG_HUSH_TIMES"
#else
# define IF_HUSH_TIMES(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_TIMES(...)
#ifdef MAKE_SUID
# define IF_HUSH_READ(...) __VA_ARGS__ "CONFIG_HUSH_READ"
#else
# define IF_HUSH_READ(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_READ(...)
#ifdef MAKE_SUID
# define IF_HUSH_SET(...) __VA_ARGS__ "CONFIG_HUSH_SET"
#else
# define IF_HUSH_SET(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_SET(...)
#ifdef MAKE_SUID
# define IF_HUSH_UNSET(...) __VA_ARGS__ "CONFIG_HUSH_UNSET"
#else
# define IF_HUSH_UNSET(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_UNSET(...)
#ifdef MAKE_SUID
# define IF_HUSH_ULIMIT(...) __VA_ARGS__ "CONFIG_HUSH_ULIMIT"
#else
# define IF_HUSH_ULIMIT(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_ULIMIT(...)
#ifdef MAKE_SUID
# define IF_HUSH_UMASK(...) __VA_ARGS__ "CONFIG_HUSH_UMASK"
#else
# define IF_HUSH_UMASK(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_UMASK(...)
#ifdef MAKE_SUID
# define IF_HUSH_GETOPTS(...) __VA_ARGS__ "CONFIG_HUSH_GETOPTS"
#else
# define IF_HUSH_GETOPTS(...) __VA_ARGS__
#endif
#define IF_NOT_HUSH_GETOPTS(...)
#define IF_HUSH_MEMLEAK(...)
#define IF_NOT_HUSH_MEMLEAK(...) __VA_ARGS__

/*
 * Options common to all shells
 */
#ifdef MAKE_SUID
# define IF_FEATURE_SH_MATH(...) __VA_ARGS__ "CONFIG_FEATURE_SH_MATH"
#else
# define IF_FEATURE_SH_MATH(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SH_MATH(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SH_MATH_64(...) __VA_ARGS__ "CONFIG_FEATURE_SH_MATH_64"
#else
# define IF_FEATURE_SH_MATH_64(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SH_MATH_64(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SH_EXTRA_QUIET(...) __VA_ARGS__ "CONFIG_FEATURE_SH_EXTRA_QUIET"
#else
# define IF_FEATURE_SH_EXTRA_QUIET(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SH_EXTRA_QUIET(...)
#define IF_FEATURE_SH_STANDALONE(...)
#define IF_NOT_FEATURE_SH_STANDALONE(...) __VA_ARGS__
#define IF_FEATURE_SH_NOFORK(...)
#define IF_NOT_FEATURE_SH_NOFORK(...) __VA_ARGS__
#ifdef MAKE_SUID
# define IF_FEATURE_SH_READ_FRAC(...) __VA_ARGS__ "CONFIG_FEATURE_SH_READ_FRAC"
#else
# define IF_FEATURE_SH_READ_FRAC(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SH_READ_FRAC(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SH_HISTFILESIZE(...) __VA_ARGS__ "CONFIG_FEATURE_SH_HISTFILESIZE"
#else
# define IF_FEATURE_SH_HISTFILESIZE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SH_HISTFILESIZE(...)

/*
 * System Logging Utilities
 */
#ifdef MAKE_SUID
# define IF_KLOGD(...) __VA_ARGS__ "CONFIG_KLOGD"
#else
# define IF_KLOGD(...) __VA_ARGS__
#endif
#define IF_NOT_KLOGD(...)

/*
 * klogd should not be used together with syslog to kernel printk buffer
 */
#ifdef MAKE_SUID
# define IF_FEATURE_KLOGD_KLOGCTL(...) __VA_ARGS__ "CONFIG_FEATURE_KLOGD_KLOGCTL"
#else
# define IF_FEATURE_KLOGD_KLOGCTL(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_KLOGD_KLOGCTL(...)
#ifdef MAKE_SUID
# define IF_LOGGER(...) __VA_ARGS__ "CONFIG_LOGGER"
#else
# define IF_LOGGER(...) __VA_ARGS__
#endif
#define IF_NOT_LOGGER(...)
#ifdef MAKE_SUID
# define IF_LOGREAD(...) __VA_ARGS__ "CONFIG_LOGREAD"
#else
# define IF_LOGREAD(...) __VA_ARGS__
#endif
#define IF_NOT_LOGREAD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_LOGREAD_REDUCED_LOCKING(...) __VA_ARGS__ "CONFIG_FEATURE_LOGREAD_REDUCED_LOCKING"
#else
# define IF_FEATURE_LOGREAD_REDUCED_LOCKING(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_LOGREAD_REDUCED_LOCKING(...)
#ifdef MAKE_SUID
# define IF_SYSLOGD(...) __VA_ARGS__ "CONFIG_SYSLOGD"
#else
# define IF_SYSLOGD(...) __VA_ARGS__
#endif
#define IF_NOT_SYSLOGD(...)
#ifdef MAKE_SUID
# define IF_FEATURE_ROTATE_LOGFILE(...) __VA_ARGS__ "CONFIG_FEATURE_ROTATE_LOGFILE"
#else
# define IF_FEATURE_ROTATE_LOGFILE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_ROTATE_LOGFILE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_REMOTE_LOG(...) __VA_ARGS__ "CONFIG_FEATURE_REMOTE_LOG"
#else
# define IF_FEATURE_REMOTE_LOG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_REMOTE_LOG(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SYSLOGD_DUP(...) __VA_ARGS__ "CONFIG_FEATURE_SYSLOGD_DUP"
#else
# define IF_FEATURE_SYSLOGD_DUP(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SYSLOGD_DUP(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SYSLOGD_CFG(...) __VA_ARGS__ "CONFIG_FEATURE_SYSLOGD_CFG"
#else
# define IF_FEATURE_SYSLOGD_CFG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SYSLOGD_CFG(...)
#ifdef MAKE_SUID
# define IF_FEATURE_SYSLOGD_READ_BUFFER_SIZE(...) __VA_ARGS__ "CONFIG_FEATURE_SYSLOGD_READ_BUFFER_SIZE"
#else
# define IF_FEATURE_SYSLOGD_READ_BUFFER_SIZE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_SYSLOGD_READ_BUFFER_SIZE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IPC_SYSLOG(...) __VA_ARGS__ "CONFIG_FEATURE_IPC_SYSLOG"
#else
# define IF_FEATURE_IPC_SYSLOG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IPC_SYSLOG(...)
#ifdef MAKE_SUID
# define IF_FEATURE_IPC_SYSLOG_BUFFER_SIZE(...) __VA_ARGS__ "CONFIG_FEATURE_IPC_SYSLOG_BUFFER_SIZE"
#else
# define IF_FEATURE_IPC_SYSLOG_BUFFER_SIZE(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_IPC_SYSLOG_BUFFER_SIZE(...)
#ifdef MAKE_SUID
# define IF_FEATURE_KMSG_SYSLOG(...) __VA_ARGS__ "CONFIG_FEATURE_KMSG_SYSLOG"
#else
# define IF_FEATURE_KMSG_SYSLOG(...) __VA_ARGS__
#endif
#define IF_NOT_FEATURE_KMSG_SYSLOG(...)
