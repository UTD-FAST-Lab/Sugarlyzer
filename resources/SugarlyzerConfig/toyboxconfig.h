#define KGEN_x25 ((!defined KGENMACRO_TOYBOX_SELINUX))
#define KGEN_x23 ((!defined KGENMACRO_TOYBOX_LSM_NONE))
#define KGEN_x28 ((!defined KGENMACRO_TOYBOX_SMACK))
#define KGEN_x54 ((defined KGENMACRO_MKNOD_Z||(!(defined KGENMACRO_MKNOD&&(!defined KGENMACRO_TOYBOX_LSM_NONE)))))
#define KGEN_x39 ((defined KGENMACRO_MKNOD&&(KGEN_x23)))
#define KGEN_x48 (((!defined KGENMACRO_MKNOD_Z)||(KGEN_x39)))
#define KGEN_x66 ((defined KGENMACRO_TOYBOX_FORK&&(defined KGENMACRO_TOYBOX_FORK||(!defined KGENMACRO_BOOTCHARTD))))
#define KGEN_x70 ((defined KGENMACRO_TOYBOX_SELINUX||(!defined KGENMACRO_RUNCON)))
#define KGEN_x78 ((defined KGENMACRO_SORT_FLOAT||(!(defined KGENMACRO_SORT_BIG&&defined KGENMACRO_TOYBOX_FLOAT))))
#define KGEN_x58 ((defined KGENMACRO_SORT_BIG&&defined KGENMACRO_TOYBOX_FLOAT))
#define KGEN_x76 (((!defined KGENMACRO_SORT_FLOAT)||(KGEN_x58)))
#define KGEN_x88 ((defined KGENMACRO_TOYBOX_LIBCRYPTO||(!defined KGENMACRO_SHA512SUM)))
#define KGEN_x64 ((!defined KGENMACRO_TOYBOX_LIBCRYPTO))
#define KGEN_x99 ((defined KGENMACRO_KLOGD&&(defined KGENMACRO_KLOGD||(!defined KGENMACRO_KLOGD_SOURCE_RING_BUFFER))))
#define KGEN_x103 ((defined KGENMACRO_TOYBOX_LIBCRYPTO||(!defined KGENMACRO_SHA224SUM)))
#define KGEN_x112 ((defined KGENMACRO_TOYBOX_PRLIMIT||(!defined KGENMACRO_ULIMIT)))
#define KGEN_x87 ((!defined KGENMACRO_TOYBOX_PRLIMIT))
#define KGEN_x122 ((defined KGENMACRO_TOYBOX_FIFREEZE||(!defined KGENMACRO_FSFREEZE)))
#define KGEN_x97 ((!defined KGENMACRO_TOYBOX_FIFREEZE))
#define KGEN_x137 ((defined KGENMACRO_TOYBOX_FORK||(!defined KGENMACRO_NBD_CLIENT)))
#define KGEN_x45 ((!defined KGENMACRO_TOYBOX_FORK))
#define KGEN_x146 ((defined KGENMACRO_LS||(!defined KGENMACRO_LS_COLOR)))
#define KGEN_x121 ((!defined KGENMACRO_LS))
#define KGEN_x155 ((defined KGENMACRO_TOYBOX_FORK&&(defined KGENMACRO_TOYBOX_FORK||(!defined KGENMACRO_CRONTAB))))
#define KGEN_x161 ((defined KGENMACRO_TOYBOX_ON_ANDROID||(!defined KGENMACRO_STOP)))
#define KGEN_x136 ((!defined KGENMACRO_TOYBOX_ON_ANDROID))
#define KGEN_x168 ((defined KGENMACRO_TOYBOX_SELINUX||(!defined KGENMACRO_LOAD_POLICY)))
#define KGEN_x179 ((defined KGENMACRO_TOYBOX_LIBZ||(!defined KGENMACRO_GZIP)))
#define KGEN_x158 ((!defined KGENMACRO_TOYBOX_LIBZ))
#define KGEN_x188 ((defined KGENMACRO_TOYBOX_HELP||(!defined KGENMACRO_TOYBOX_HELP_DASHDASH)))
#define KGEN_x167 ((!defined KGENMACRO_TOYBOX_HELP))
#define KGEN_x196 ((defined KGENMACRO_TOYBOX_ON_ANDROID||(!defined KGENMACRO_SETPROP)))
#define KGEN_x204 ((defined KGENMACRO_TOYBOX_FLOAT||(!defined KGENMACRO_TIME)))
#define KGEN_x178 ((!defined KGENMACRO_TOYBOX_FLOAT))
#define KGEN_x213 ((defined KGENMACRO_TOYBOX_LIBZ||(!defined KGENMACRO_ZCAT)))
#define KGEN_x191 ((defined KGENMACRO_TOYBOX&&defined KGENMACRO_HELP))
#define KGEN_x199 (((!defined KGENMACRO_HELP_EXTRAS)||(KGEN_x191)))
#define KGEN_x203 ((!(KGEN_x191)))
#define KGEN_x231 ((defined KGENMACRO_TOYBOX_ON_ANDROID||(!defined KGENMACRO_SENDEVENT)))
#define KGEN_x238 ((defined KGENMACRO_TOYBOX_FLOAT||(!defined KGENMACRO_TIMEOUT)))
#define KGEN_x255 ((defined KGENMACRO_MDEV||(!defined KGENMACRO_MDEV_CONF)))
#define KGEN_x230 ((!defined KGENMACRO_MDEV))
#define KGEN_x262 ((defined KGENMACRO_SLEEP_FLOAT||(!(defined KGENMACRO_SLEEP&&defined KGENMACRO_TOYBOX_FLOAT))))
#define KGEN_x237 ((defined KGENMACRO_SLEEP&&defined KGENMACRO_TOYBOX_FLOAT))
#define KGEN_x258 (((!defined KGENMACRO_SLEEP_FLOAT)||(KGEN_x237)))
#define KGEN_x280 ((defined KGENMACRO_TOYBOX_SHADOW||(!defined KGENMACRO_SU)))
#define KGEN_x265 ((!defined KGENMACRO_TOYBOX_SHADOW))
#define KGEN_x287 ((defined KGENMACRO_TOYBOX_LIBZ||(!defined KGENMACRO_GUNZIP)))
#define KGEN_x295 ((defined KGENMACRO_SORT||(!defined KGENMACRO_SORT_BIG)))
#define KGEN_x270 ((!defined KGENMACRO_SORT))
#define KGEN_x304 ((defined KGENMACRO_TOYBOX_UTMPX||(!defined KGENMACRO_WHO)))
#define KGEN_x278 ((!defined KGENMACRO_TOYBOX_UTMPX))
#define KGEN_x317 ((defined KGENMACRO_TOYBOX_SELINUX||(!defined KGENMACRO_CHCON)))
#define KGEN_x324 ((defined KGENMACRO_TOYBOX_SELINUX||(!defined KGENMACRO_SETENFORCE)))
#define KGEN_x298 (((!defined KGENMACRO_MKPASSWD)||(KGEN_x136)))
#define KGEN_x334 ((defined KGENMACRO_TOYBOX_ON_ANDROID&&(KGEN_x298)&&(defined KGENMACRO_TOYBOX_ON_ANDROID||defined KGENMACRO_MKPASSWD)))
#define KGEN_x316 ((defined KGENMACRO_TOYBOX_ON_ANDROID&&defined KGENMACRO_TOYBOX_SELINUX))
#define KGEN_x333 ((!(KGEN_x316)))
#define KGEN_x330 (((!defined KGENMACRO_GETPROP)||(KGEN_x316)))
#define KGEN_x357 ((defined KGENMACRO_TOYBOX_UTMPX||(!defined KGENMACRO_W)))
#define KGEN_x367 ((defined KGENMACRO_NETCAT||(!defined KGENMACRO_NETCAT_LISTEN)))
#define KGEN_x347 ((!defined KGENMACRO_NETCAT))
#define KGEN_x374 ((defined KGENMACRO_TOYBOX_CONTAINER||(!defined KGENMACRO_NSENTER)))
#define KGEN_x177 ((!defined KGENMACRO_TOYBOX_CONTAINER))
#define KGEN_x381 ((defined KGENMACRO_TOYBOX_LIBCRYPTO||(!defined KGENMACRO_SHA384SUM)))
#define KGEN_x390 ((defined KGENMACRO_TOYBOX_FALLOCATE||(!defined KGENMACRO_FALLOCATE)))
#define KGEN_x364 ((!defined KGENMACRO_TOYBOX_FALLOCATE))
#define KGEN_x399 ((defined KGENMACRO_TAIL||(!defined KGENMACRO_TAIL_SEEK)))
#define KGEN_x373 ((!defined KGENMACRO_TAIL))
#define KGEN_x406 ((defined KGENMACRO_TOYBOX_SHADOW||(!defined KGENMACRO_LOGIN)))
#define KGEN_x413 ((defined KGENMACRO_TOYBOX_UTMPX||(!defined KGENMACRO_UPTIME)))
#define KGEN_x420 ((defined KGENMACRO_MKFIFO_Z||(!(defined KGENMACRO_MKFIFO&&(!defined KGENMACRO_TOYBOX_LSM_NONE)))))
#define KGEN_x389 ((defined KGENMACRO_MKFIFO&&(KGEN_x23)))
#define KGEN_x416 (((!defined KGENMACRO_MKFIFO_Z)||(KGEN_x389)))
#define KGEN_x428 ((defined KGENMACRO_TOYBOX_ON_ANDROID||(!defined KGENMACRO_LOG)))
#define KGEN_x435 ((defined KGENMACRO_ID_Z||(!(defined KGENMACRO_ID&&(!defined KGENMACRO_TOYBOX_LSM_NONE)))))
#define KGEN_x405 ((defined KGENMACRO_ID&&(KGEN_x23)))
#define KGEN_x431 (((!defined KGENMACRO_ID_Z)||(KGEN_x405)))
#define KGEN_x440 ((defined KGENMACRO_TOYBOX_FORK||defined KGENMACRO_TOYBOX_MUSL_NOMMU_IS_BROKEN))
#define KGEN_x439 (((KGEN_x45)||(!defined KGENMACRO_TOYBOX_MUSL_NOMMU_IS_BROKEN)))
#define KGEN_x457 ((defined KGENMACRO_TOYBOX_ICONV&&(defined KGENMACRO_TOYBOX_ICONV||(!defined KGENMACRO_ICONV))))
#define KGEN_x463 ((defined KGENMACRO_TOYBOX_SHADOW&&(defined KGENMACRO_TOYBOX_SHADOW||(!defined KGENMACRO_SULOGIN))))
#define KGEN_x477 ((defined KGENMACRO_LSPCI||(!defined KGENMACRO_LSPCI_TEXT)))
#define KGEN_x454 ((!defined KGENMACRO_LSPCI))
#define KGEN_x448 (((!defined KGENMACRO_PASSWD)||defined KGENMACRO_TOYBOX_SHADOW))
#define KGEN_x489 ((defined KGENMACRO_TOYBOX_ON_ANDROID||(!defined KGENMACRO_START)))
#define KGEN_x496 ((defined KGENMACRO_TOYBOX_LIBCRYPTO||(!defined KGENMACRO_SHA256SUM)))
#define KGEN_x503 ((defined KGENMACRO_TOYBOX_SELINUX||(!defined KGENMACRO_GETENFORCE)))
#define KGEN_x518 ((defined KGENMACRO_MKDIR_Z||(!(defined KGENMACRO_MKDIR&&(!defined KGENMACRO_TOYBOX_LSM_NONE)))))
#define KGEN_x488 ((defined KGENMACRO_MKDIR&&(!defined KGENMACRO_TOYBOX_LSM_NONE)))
#define KGEN_x512 (((!defined KGENMACRO_MKDIR_Z)||(KGEN_x488)))
#define KGEN_x526 ((defined KGENMACRO_TOYBOX_CONTAINER||(!defined KGENMACRO_UNSHARE)))
#define KGEN_x541 ((defined KGENMACRO_KILL||(!defined KGENMACRO_KILLALL5)))
#define KGEN_x521 ((!defined KGENMACRO_KILL))
#define KGEN_x547 ((defined KGENMACRO_TOYBOX_HELP||(!defined KGENMACRO_HELP)))
#define KGEN_x557 ((defined KGENMACRO_CP||(!defined KGENMACRO_CP_PRESERVE)))
#define KGEN_x532 ((!defined KGENMACRO_CP))
#define KGEN_x560 ((!defined KGENMACRO_GREP))
#define KGEN_x563 ((defined KGENMACRO_FGREP||(KGEN_x560)))
#define KGEN_x556 (((!defined KGENMACRO_FGREP)||defined KGENMACRO_GREP))
#define KGEN_x577 ((defined KGENMACRO_TOYBOX_FLOAT||(!defined KGENMACRO_SEQ)))
#define KGEN_x584 ((defined KGENMACRO_TOYBOX_SELINUX||(!defined KGENMACRO_RESTORECON)))
#define KGEN_x587 ((defined KGENMACRO_EGREP||(!defined KGENMACRO_GREP)))
#define KGEN_x583 ((defined KGENMACRO_GREP||(!defined KGENMACRO_EGREP)))
#ifdef KGENMACRO_KILL
#define CFG_KILL 1
#else
#define CFG_KILL 0
#endif
#ifdef KGENMACRO_TOYBOX_NORECURSE
#define CFG_TOYBOX_NORECURSE 1
#else
#define CFG_TOYBOX_NORECURSE 0
#endif
#if (((defined KGENMACRO_SYSLOGD&&(defined KGENMACRO_SYSLOGD||(!defined KGENMACRO_LOGGER)))||((!defined KGENMACRO_SYSLOGD)&&(!defined KGENMACRO_LOGGER))))
#ifdef KGENMACRO_LOGGER
#define CFG_LOGGER 1
#else
#define CFG_LOGGER 0
#endif
#endif
#ifdef KGENMACRO_WHICH
#define CFG_WHICH 1
#else
#define CFG_WHICH 0
#endif
#ifdef KGENMACRO_DHCP6
#define CFG_DHCP6 1
#else
#define CFG_DHCP6 0
#endif
#ifdef KGENMACRO_LSATTR
#define CFG_LSATTR 1
#else
#define CFG_LSATTR 0
#endif
#ifdef KGENMACRO_UUDECODE
#define CFG_UUDECODE 1
#else
#define CFG_UUDECODE 0
#endif
#if (((defined KGENMACRO_TOYBOX_CONTAINER&&(KGEN_x526))||((KGEN_x177)&&(KGEN_x526)&&((KGEN_x177)||defined KGENMACRO_UNSHARE))))
#ifdef KGENMACRO_UNSHARE
#define CFG_UNSHARE 1
#else
#define CFG_UNSHARE 0
#endif
#endif
#ifdef KGENMACRO_USERADD
#define CFG_USERADD 1
#else
#define CFG_USERADD 0
#endif
#if (((defined KGENMACRO_TOYBOX_FORK&&(defined KGENMACRO_TOYBOX_FORK||(!defined KGENMACRO_OPENVT)))||((!defined KGENMACRO_TOYBOX_FORK)&&(!defined KGENMACRO_OPENVT))))
#ifdef KGENMACRO_OPENVT
#define CFG_OPENVT 1
#else
#define CFG_OPENVT 0
#endif
#endif
#ifdef KGENMACRO_IONICE
#define CFG_IONICE 1
#else
#define CFG_IONICE 0
#endif
#ifdef KGENMACRO_SWITCH_ROOT
#define CFG_SWITCH_ROOT 1
#else
#define CFG_SWITCH_ROOT 0
#endif
#ifdef KGENMACRO_WATCH
#define CFG_WATCH 1
#else
#define CFG_WATCH 0
#endif
#ifdef KGENMACRO_FACTOR
#define CFG_FACTOR 1
#else
#define CFG_FACTOR 0
#endif
#ifdef KGENMACRO_TOYBOX_HELP
#define CFG_TOYBOX_HELP 1
#else
#define CFG_TOYBOX_HELP 0
#endif
#ifdef KGENMACRO_IFCONFIG
#define CFG_IFCONFIG 1
#else
#define CFG_IFCONFIG 0
#endif
#ifdef KGENMACRO_GROUPS
#define CFG_GROUPS 1
#else
#define CFG_GROUPS 0
#endif
#if ((!defined KGENMACRO_TOYBOX_ANDROID_SCHEDPOLICY))
#ifdef KGENMACRO_TOYBOX_ANDROID_SCHEDPOLICY
#define CFG_TOYBOX_ANDROID_SCHEDPOLICY 1
#else
#define CFG_TOYBOX_ANDROID_SCHEDPOLICY 0
#endif
#endif
#ifdef KGENMACRO_MKDIR
#define CFG_MKDIR 1
#else
#define CFG_MKDIR 0
#endif
#ifdef KGENMACRO_CATV
#define CFG_CATV 1
#else
#define CFG_CATV 0
#endif
#ifdef KGENMACRO_MODINFO
#define CFG_MODINFO 1
#else
#define CFG_MODINFO 0
#endif
#if (((defined KGENMACRO_MDEV&&(KGEN_x255))||((KGEN_x230)&&(KGEN_x255)&&(defined KGENMACRO_MDEV_CONF||(KGEN_x230)))))
#ifdef KGENMACRO_MDEV_CONF
#define CFG_MDEV_CONF 1
#else
#define CFG_MDEV_CONF 0
#endif
#endif
#if (((KGEN_x48)&&(KGEN_x54)))
#ifdef KGENMACRO_MKNOD_Z
#define CFG_MKNOD_Z 1
#else
#define CFG_MKNOD_Z 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_ON_ANDROID&&(KGEN_x196))||((KGEN_x136)&&(KGEN_x196)&&((KGEN_x136)||defined KGENMACRO_SETPROP))))
#ifdef KGENMACRO_SETPROP
#define CFG_SETPROP 1
#else
#define CFG_SETPROP 0
#endif
#endif
#ifdef KGENMACRO_IPCS
#define CFG_IPCS 1
#else
#define CFG_IPCS 0
#endif
#ifdef KGENMACRO_FREERAMDISK
#define CFG_FREERAMDISK 1
#else
#define CFG_FREERAMDISK 0
#endif
#ifdef KGENMACRO_TEST_MANY_OPTIONS
#define CFG_TEST_MANY_OPTIONS 1
#else
#define CFG_TEST_MANY_OPTIONS 0
#endif
#ifdef KGENMACRO_UNIX2DOS
#define CFG_UNIX2DOS 1
#else
#define CFG_UNIX2DOS 0
#endif
#if (((defined KGENMACRO_TOYBOX_FLOAT&&(KGEN_x577))||((KGEN_x178)&&(KGEN_x577)&&((KGEN_x178)||defined KGENMACRO_SEQ))))
#ifdef KGENMACRO_SEQ
#define CFG_SEQ 1
#else
#define CFG_SEQ 0
#endif
#endif
#ifdef KGENMACRO_ASCII
#define CFG_ASCII 1
#else
#define CFG_ASCII 0
#endif
#if (((KGEN_x439)&&(KGEN_x440)))
#ifdef KGENMACRO_TOYBOX_FORK
#define CFG_TOYBOX_FORK 1
#else
#define CFG_TOYBOX_FORK 0
#endif
#endif
#ifdef KGENMACRO_TEST_UTF8TOWC
#define CFG_TEST_UTF8TOWC 1
#else
#define CFG_TEST_UTF8TOWC 0
#endif
#ifdef KGENMACRO_LSUSB
#define CFG_LSUSB 1
#else
#define CFG_LSUSB 0
#endif
#ifdef KGENMACRO_PS
#define CFG_PS 1
#else
#define CFG_PS 0
#endif
#ifdef KGENMACRO_SYNC
#define CFG_SYNC 1
#else
#define CFG_SYNC 0
#endif
#if (((defined KGENMACRO_TOYBOX_LIBZ&&(KGEN_x179))||((KGEN_x158)&&(KGEN_x179)&&(defined KGENMACRO_GZIP||(KGEN_x158)))))
#ifdef KGENMACRO_GZIP
#define CFG_GZIP 1
#else
#define CFG_GZIP 0
#endif
#endif
#ifdef KGENMACRO_CHRT
#define CFG_CHRT 1
#else
#define CFG_CHRT 0
#endif
#if (((defined KGENMACRO_TOYBOX_FORK&&(KGEN_x137))||((KGEN_x45)&&(KGEN_x137)&&((KGEN_x45)||defined KGENMACRO_NBD_CLIENT))))
#ifdef KGENMACRO_NBD_CLIENT
#define CFG_NBD_CLIENT 1
#else
#define CFG_NBD_CLIENT 0
#endif
#endif
#ifdef KGENMACRO_FTPGET
#define CFG_FTPGET 1
#else
#define CFG_FTPGET 0
#endif
#ifdef KGENMACRO_RMMOD
#define CFG_RMMOD 1
#else
#define CFG_RMMOD 0
#endif
#ifdef KGENMACRO_TAIL
#define CFG_TAIL 1
#else
#define CFG_TAIL 0
#endif
#ifdef KGENMACRO_MORE
#define CFG_MORE 1
#else
#define CFG_MORE 0
#endif
#ifdef KGENMACRO_CMP
#define CFG_CMP 1
#else
#define CFG_CMP 0
#endif
#if (((defined KGENMACRO_TOYBOX_LIBZ&&(KGEN_x287))||((KGEN_x158)&&(KGEN_x287)&&((KGEN_x158)||defined KGENMACRO_GUNZIP))))
#ifdef KGENMACRO_GUNZIP
#define CFG_GUNZIP 1
#else
#define CFG_GUNZIP 0
#endif
#endif
#ifdef KGENMACRO_UNAME
#define CFG_UNAME 1
#else
#define CFG_UNAME 0
#endif
#ifdef KGENMACRO_UNAME_RELEASE
#define CFG_UNAME_RELEASE "5.4.0-139-generic"
#else
#define CFG_UNAME_RELEASE ""
#endif
#ifdef KGENMACRO_TAC
#define CFG_TAC 1
#else
#define CFG_TAC 0
#endif
#if (((defined KGENMACRO_TOYBOX_SELINUX&&(KGEN_x168))||((KGEN_x25)&&(KGEN_x168)&&((KGEN_x25)||defined KGENMACRO_LOAD_POLICY))))
#ifdef KGENMACRO_LOAD_POLICY
#define CFG_LOAD_POLICY 1
#else
#define CFG_LOAD_POLICY 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_ON_ANDROID&&defined KGENMACRO_TOYBOX_SELINUX&&(KGEN_x330))||((KGEN_x333)&&(KGEN_x330)&&(defined KGENMACRO_GETPROP||(KGEN_x333)))))
#ifdef KGENMACRO_GETPROP
#define CFG_GETPROP 1
#else
#define CFG_GETPROP 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_FIFREEZE&&(KGEN_x122))||((KGEN_x97)&&(KGEN_x122)&&(defined KGENMACRO_FSFREEZE||(KGEN_x97)))))
#ifdef KGENMACRO_FSFREEZE
#define CFG_FSFREEZE 1
#else
#define CFG_FSFREEZE 0
#endif
#endif
#ifdef KGENMACRO_MV
#define CFG_MV 1
#else
#define CFG_MV 0
#endif
#ifdef KGENMACRO_PATCH
#define CFG_PATCH 1
#else
#define CFG_PATCH 0
#endif
#ifdef KGENMACRO_PKILL
#define CFG_PKILL 1
#else
#define CFG_PKILL 0
#endif
#ifdef KGENMACRO_DOS2UNIX
#define CFG_DOS2UNIX 1
#else
#define CFG_DOS2UNIX 0
#endif
#if (((defined KGENMACRO_TOYBOX_ON_ANDROID&&(KGEN_x231))||((KGEN_x136)&&(KGEN_x231)&&((KGEN_x136)||defined KGENMACRO_SENDEVENT))))
#ifdef KGENMACRO_SENDEVENT
#define CFG_SENDEVENT 1
#else
#define CFG_SENDEVENT 0
#endif
#endif
#ifdef KGENMACRO_ACPI
#define CFG_ACPI 1
#else
#define CFG_ACPI 0
#endif
#ifdef KGENMACRO_TEST_SCANKEY
#define CFG_TEST_SCANKEY 1
#else
#define CFG_TEST_SCANKEY 0
#endif
#ifdef KGENMACRO_MKTEMP
#define CFG_MKTEMP 1
#else
#define CFG_MKTEMP 0
#endif
#ifdef KGENMACRO_READLINK
#define CFG_READLINK 1
#else
#define CFG_READLINK 0
#endif
#ifdef KGENMACRO_DF
#define CFG_DF 1
#else
#define CFG_DF 0
#endif
#if (((defined KGENMACRO_TOYBOX_HELP&&(KGEN_x188))||((KGEN_x167)&&(KGEN_x188)&&(defined KGENMACRO_TOYBOX_HELP_DASHDASH||(KGEN_x167)))))
#ifdef KGENMACRO_TOYBOX_HELP_DASHDASH
#define CFG_TOYBOX_HELP_DASHDASH 1
#else
#define CFG_TOYBOX_HELP_DASHDASH 0
#endif
#endif
#ifdef KGENMACRO_BZCAT
#define CFG_BZCAT 1
#else
#define CFG_BZCAT 0
#endif
#ifdef KGENMACRO_DIFF
#define CFG_DIFF 1
#else
#define CFG_DIFF 0
#endif
#ifdef KGENMACRO_TRUNCATE
#define CFG_TRUNCATE 1
#else
#define CFG_TRUNCATE 0
#endif
#ifdef KGENMACRO_DECOMPRESS
#define CFG_DECOMPRESS 1
#else
#define CFG_DECOMPRESS 0
#endif
#ifdef KGENMACRO_YES
#define CFG_YES 1
#else
#define CFG_YES 0
#endif
#ifdef KGENMACRO_ARP
#define CFG_ARP 1
#else
#define CFG_ARP 0
#endif
#if (((KGEN_x431)&&(KGEN_x435)))
#ifdef KGENMACRO_ID_Z
#define CFG_ID_Z 1
#else
#define CFG_ID_Z 0
#endif
#endif
#ifdef KGENMACRO_HOST
#define CFG_HOST 1
#else
#define CFG_HOST 0
#endif
#ifdef KGENMACRO_FOLD
#define CFG_FOLD 1
#else
#define CFG_FOLD 0
#endif
#ifdef KGENMACRO_SHA1SUM
#define CFG_SHA1SUM 1
#else
#define CFG_SHA1SUM 0
#endif
#ifdef KGENMACRO_TEST_HUMAN_READABLE
#define CFG_TEST_HUMAN_READABLE 1
#else
#define CFG_TEST_HUMAN_READABLE 0
#endif
#if (defined KGENMACRO_TOYBOX_SHADOW)
#ifdef KGENMACRO_TOYBOX_SHADOW
#define CFG_TOYBOX_SHADOW 1
#else
#define CFG_TOYBOX_SHADOW 0
#endif
#endif
#ifdef KGENMACRO_USLEEP
#define CFG_USLEEP 1
#else
#define CFG_USLEEP 0
#endif
#ifdef KGENMACRO_NICE
#define CFG_NICE 1
#else
#define CFG_NICE 0
#endif
#ifdef KGENMACRO_RFKILL
#define CFG_RFKILL 1
#else
#define CFG_RFKILL 0
#endif
#if (((defined KGENMACRO_LSPCI&&(KGEN_x477))||((KGEN_x454)&&(KGEN_x477)&&(defined KGENMACRO_LSPCI_TEXT||(KGEN_x454)))))
#ifdef KGENMACRO_LSPCI_TEXT
#define CFG_LSPCI_TEXT 1
#else
#define CFG_LSPCI_TEXT 0
#endif
#endif
#ifdef KGENMACRO_GETFATTR
#define CFG_GETFATTR 1
#else
#define CFG_GETFATTR 0
#endif
#if ((!defined KGENMACRO_EXIT))
#ifdef KGENMACRO_EXIT
#define CFG_EXIT 1
#else
#define CFG_EXIT 0
#endif
#endif
#ifdef KGENMACRO_VCONFIG
#define CFG_VCONFIG 1
#else
#define CFG_VCONFIG 0
#endif
#ifdef KGENMACRO_SETFATTR
#define CFG_SETFATTR 1
#else
#define CFG_SETFATTR 0
#endif
#if (((defined KGENMACRO_TOYBOX_ON_ANDROID&&(KGEN_x489))||((KGEN_x136)&&(KGEN_x489)&&((KGEN_x136)||defined KGENMACRO_START))))
#ifdef KGENMACRO_START
#define CFG_START 1
#else
#define CFG_START 0
#endif
#endif
#ifdef KGENMACRO_TRACEROUTE
#define CFG_TRACEROUTE 1
#else
#define CFG_TRACEROUTE 0
#endif
#ifdef KGENMACRO_TEE
#define CFG_TEE 1
#else
#define CFG_TEE 0
#endif
#ifdef KGENMACRO_TEST
#define CFG_TEST 1
#else
#define CFG_TEST 0
#endif
#ifdef KGENMACRO_ID
#define CFG_ID 1
#else
#define CFG_ID 0
#endif
#ifdef KGENMACRO_TOYBOX_SUID
#define CFG_TOYBOX_SUID 1
#else
#define CFG_TOYBOX_SUID 0
#endif
#ifdef KGENMACRO_TFTP
#define CFG_TFTP 1
#else
#define CFG_TFTP 0
#endif
#ifdef KGENMACRO_FDISK
#define CFG_FDISK 1
#else
#define CFG_FDISK 0
#endif
#ifdef KGENMACRO_BUNZIP2
#define CFG_BUNZIP2 1
#else
#define CFG_BUNZIP2 0
#endif
#ifdef KGENMACRO_MOUNT
#define CFG_MOUNT 1
#else
#define CFG_MOUNT 0
#endif
#if (defined KGENMACRO_TOYBOX)
#ifdef KGENMACRO_TOYBOX
#define CFG_TOYBOX 1
#else
#define CFG_TOYBOX 0
#endif
#endif
#ifdef KGENMACRO_HOSTID
#define CFG_HOSTID 1
#else
#define CFG_HOSTID 0
#endif
#ifdef KGENMACRO_EXPR
#define CFG_EXPR 1
#else
#define CFG_EXPR 0
#endif
#ifdef KGENMACRO_CP
#define CFG_CP 1
#else
#define CFG_CP 0
#endif
#ifdef KGENMACRO_MICROCOM
#define CFG_MICROCOM 1
#else
#define CFG_MICROCOM 0
#endif
#ifdef KGENMACRO_PARTPROBE
#define CFG_PARTPROBE 1
#else
#define CFG_PARTPROBE 0
#endif
#if (((defined KGENMACRO_TOYBOX_SELINUX&&(KGEN_x70))||((KGEN_x25)&&(KGEN_x70)&&((KGEN_x25)||defined KGENMACRO_RUNCON))))
#ifdef KGENMACRO_RUNCON
#define CFG_RUNCON 1
#else
#define CFG_RUNCON 0
#endif
#endif
#ifdef KGENMACRO_SPLIT
#define CFG_SPLIT 1
#else
#define CFG_SPLIT 0
#endif
#ifdef KGENMACRO_SED
#define CFG_SED 1
#else
#define CFG_SED 0
#endif
#ifdef KGENMACRO_RESET
#define CFG_RESET 1
#else
#define CFG_RESET 0
#endif
#ifdef KGENMACRO_WGET
#define CFG_WGET 1
#else
#define CFG_WGET 0
#endif
#if (((KGEN_x25)||(!defined KGENMACRO_TOYBOX_SMACK)))
#ifdef KGENMACRO_TOYBOX_SELINUX
#define CFG_TOYBOX_SELINUX 1
#else
#define CFG_TOYBOX_SELINUX 0
#endif
#endif
#ifdef KGENMACRO_NOHUP
#define CFG_NOHUP 1
#else
#define CFG_NOHUP 0
#endif
#ifdef KGENMACRO_IP
#define CFG_IP 1
#else
#define CFG_IP 0
#endif
#if ((!defined KGENMACRO_TOYBOX_PRLIMIT))
#ifdef KGENMACRO_TOYBOX_PRLIMIT
#define CFG_TOYBOX_PRLIMIT 1
#else
#define CFG_TOYBOX_PRLIMIT 0
#endif
#endif
#ifdef KGENMACRO_LSPCI
#define CFG_LSPCI 1
#else
#define CFG_LSPCI 0
#endif
#ifdef KGENMACRO_HEAD
#define CFG_HEAD 1
#else
#define CFG_HEAD 0
#endif
#ifdef KGENMACRO_TOYBOX_I18N
#define CFG_TOYBOX_I18N 1
#else
#define CFG_TOYBOX_I18N 0
#endif
#ifdef KGENMACRO_UMOUNT
#define CFG_UMOUNT 1
#else
#define CFG_UMOUNT 0
#endif
#ifdef KGENMACRO_DIRNAME
#define CFG_DIRNAME 1
#else
#define CFG_DIRNAME 0
#endif
#if (((defined KGENMACRO_TOYBOX&&defined KGENMACRO_HELP&&(KGEN_x199))||((KGEN_x203)&&(KGEN_x199)&&(defined KGENMACRO_HELP_EXTRAS||(KGEN_x203)))))
#ifdef KGENMACRO_HELP_EXTRAS
#define CFG_HELP_EXTRAS 1
#else
#define CFG_HELP_EXTRAS 0
#endif
#endif
#ifdef KGENMACRO_CLEAR
#define CFG_CLEAR 1
#else
#define CFG_CLEAR 0
#endif
#ifdef KGENMACRO_PASTE
#define CFG_PASTE 1
#else
#define CFG_PASTE 0
#endif
#if ((!defined KGENMACRO_CD))
#ifdef KGENMACRO_CD
#define CFG_CD 1
#else
#define CFG_CD 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_FLOAT&&(KGEN_x238))||((KGEN_x178)&&(KGEN_x238)&&((KGEN_x178)||defined KGENMACRO_TIMEOUT))))
#ifdef KGENMACRO_TIMEOUT
#define CFG_TIMEOUT 1
#else
#define CFG_TIMEOUT 0
#endif
#endif
#ifdef KGENMACRO_VI
#define CFG_VI 1
#else
#define CFG_VI 0
#endif
#ifdef KGENMACRO_STRINGS
#define CFG_STRINGS 1
#else
#define CFG_STRINGS 0
#endif
#if (((KGEN_x463)||((!defined KGENMACRO_TOYBOX_SHADOW)&&(!defined KGENMACRO_SULOGIN))))
#ifdef KGENMACRO_SULOGIN
#define CFG_SULOGIN 1
#else
#define CFG_SULOGIN 0
#endif
#endif
#ifdef KGENMACRO_CKSUM
#define CFG_CKSUM 1
#else
#define CFG_CKSUM 0
#endif
#if (((defined KGENMACRO_KILL&&(KGEN_x541))||((KGEN_x521)&&(KGEN_x541)&&(defined KGENMACRO_KILLALL5||(KGEN_x521)))))
#ifdef KGENMACRO_KILLALL5
#define CFG_KILLALL5 1
#else
#define CFG_KILLALL5 0
#endif
#endif
#ifdef KGENMACRO_SETSID
#define CFG_SETSID 1
#else
#define CFG_SETSID 0
#endif
#ifdef KGENMACRO_GROUPADD
#define CFG_GROUPADD 1
#else
#define CFG_GROUPADD 0
#endif
#if (((KGEN_x556)&&(KGEN_x563)))
#ifdef KGENMACRO_FGREP
#define CFG_FGREP 1
#else
#define CFG_FGREP 0
#endif
#endif
#ifdef KGENMACRO_MKFIFO
#define CFG_MKFIFO 1
#else
#define CFG_MKFIFO 0
#endif
#if (((defined KGENMACRO_TOYBOX_SELINUX&&(KGEN_x584))||((KGEN_x25)&&(KGEN_x584)&&((KGEN_x25)||defined KGENMACRO_RESTORECON))))
#ifdef KGENMACRO_RESTORECON
#define CFG_RESTORECON 1
#else
#define CFG_RESTORECON 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_CONTAINER&&(KGEN_x374))||((KGEN_x177)&&(KGEN_x374)&&((KGEN_x177)||defined KGENMACRO_NSENTER))))
#ifdef KGENMACRO_NSENTER
#define CFG_NSENTER 1
#else
#define CFG_NSENTER 0
#endif
#endif
#ifdef KGENMACRO_TOYBOX_FLOAT
#define CFG_TOYBOX_FLOAT 1
#else
#define CFG_TOYBOX_FLOAT 0
#endif
#ifdef KGENMACRO_ENV
#define CFG_ENV 1
#else
#define CFG_ENV 0
#endif
#ifdef KGENMACRO_STAT
#define CFG_STAT 1
#else
#define CFG_STAT 0
#endif
#ifdef KGENMACRO_TELNET
#define CFG_TELNET 1
#else
#define CFG_TELNET 0
#endif
#if (((defined KGENMACRO_TOYBOX_LIBCRYPTO&&(KGEN_x381))||((KGEN_x64)&&(KGEN_x381)&&((KGEN_x64)||defined KGENMACRO_SHA384SUM))))
#ifdef KGENMACRO_SHA384SUM
#define CFG_SHA384SUM 1
#else
#define CFG_SHA384SUM 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_UTMPX&&(KGEN_x413))||((KGEN_x278)&&(KGEN_x413)&&((KGEN_x278)||defined KGENMACRO_UPTIME))))
#ifdef KGENMACRO_UPTIME
#define CFG_UPTIME 1
#else
#define CFG_UPTIME 0
#endif
#endif
#ifdef KGENMACRO_LS
#define CFG_LS 1
#else
#define CFG_LS 0
#endif
#ifdef KGENMACRO_PRINTF
#define CFG_PRINTF 1
#else
#define CFG_PRINTF 0
#endif
#ifdef KGENMACRO_LOGNAME
#define CFG_LOGNAME 1
#else
#define CFG_LOGNAME 0
#endif
#ifdef KGENMACRO_BLKID
#define CFG_BLKID 1
#else
#define CFG_BLKID 0
#endif
#ifdef KGENMACRO_PGREP
#define CFG_PGREP 1
#else
#define CFG_PGREP 0
#endif
#if (((defined KGENMACRO_SORT&&(KGEN_x295))||((KGEN_x270)&&(KGEN_x295)&&(defined KGENMACRO_SORT_BIG||(KGEN_x270)))))
#ifdef KGENMACRO_SORT_BIG
#define CFG_SORT_BIG 1
#else
#define CFG_SORT_BIG 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_LIBCRYPTO&&(KGEN_x88))||((KGEN_x64)&&(KGEN_x88)&&(defined KGENMACRO_SHA512SUM||(KGEN_x64)))))
#ifdef KGENMACRO_SHA512SUM
#define CFG_SHA512SUM 1
#else
#define CFG_SHA512SUM 0
#endif
#endif
#if ((((KGEN_x136)&&(KGEN_x298))||(KGEN_x334)))
#ifdef KGENMACRO_MKPASSWD
#define CFG_MKPASSWD 1
#else
#define CFG_MKPASSWD 0
#endif
#endif
#ifdef KGENMACRO_PWDX
#define CFG_PWDX 1
#else
#define CFG_PWDX 0
#endif
#ifdef KGENMACRO_SHRED
#define CFG_SHRED 1
#else
#define CFG_SHRED 0
#endif
#if (((defined KGENMACRO_TOYBOX_SHADOW&&(KGEN_x448))||((KGEN_x265)&&(KGEN_x448)&&(defined KGENMACRO_PASSWD||(KGEN_x265)))))
#ifdef KGENMACRO_PASSWD
#define CFG_PASSWD 1
#else
#define CFG_PASSWD 0
#endif
#endif
#ifdef KGENMACRO_CAL
#define CFG_CAL 1
#else
#define CFG_CAL 0
#endif
#ifdef KGENMACRO_INOTIFYD
#define CFG_INOTIFYD 1
#else
#define CFG_INOTIFYD 0
#endif
#if (((KGEN_x155)||((!defined KGENMACRO_TOYBOX_FORK)&&(!defined KGENMACRO_CRONTAB))))
#ifdef KGENMACRO_CRONTAB
#define CFG_CRONTAB 1
#else
#define CFG_CRONTAB 0
#endif
#endif
#ifdef KGENMACRO_TASKSET
#define CFG_TASKSET 1
#else
#define CFG_TASKSET 0
#endif
#ifdef KGENMACRO_BRCTL
#define CFG_BRCTL 1
#else
#define CFG_BRCTL 0
#endif
#ifdef KGENMACRO_LAST
#define CFG_LAST 1
#else
#define CFG_LAST 0
#endif
#ifdef KGENMACRO_WC
#define CFG_WC 1
#else
#define CFG_WC 0
#endif
#if (((defined KGENMACRO_MKE2FS&&(defined KGENMACRO_MKE2FS||(!defined KGENMACRO_MKE2FS_EXTENDED)))||((!defined KGENMACRO_MKE2FS)&&(!defined KGENMACRO_MKE2FS_EXTENDED))))
#ifdef KGENMACRO_MKE2FS_EXTENDED
#define CFG_MKE2FS_EXTENDED 1
#else
#define CFG_MKE2FS_EXTENDED 0
#endif
#endif
#ifdef KGENMACRO_MKE2FS
#define CFG_MKE2FS 1
#else
#define CFG_MKE2FS 0
#endif
#ifdef KGENMACRO_TOYBOX_FREE
#define CFG_TOYBOX_FREE 1
#else
#define CFG_TOYBOX_FREE 0
#endif
#ifdef KGENMACRO_SWAPON
#define CFG_SWAPON 1
#else
#define CFG_SWAPON 0
#endif
#ifdef KGENMACRO_CHMOD
#define CFG_CHMOD 1
#else
#define CFG_CHMOD 0
#endif
#ifdef KGENMACRO_TFTPD
#define CFG_TFTPD 1
#else
#define CFG_TFTPD 0
#endif
#ifdef KGENMACRO_REALPATH
#define CFG_REALPATH 1
#else
#define CFG_REALPATH 0
#endif
#ifdef KGENMACRO_UNIQ
#define CFG_UNIQ 1
#else
#define CFG_UNIQ 0
#endif
#if (defined KGENMACRO_TOYBOX_FIFREEZE)
#ifdef KGENMACRO_TOYBOX_FIFREEZE
#define CFG_TOYBOX_FIFREEZE 1
#else
#define CFG_TOYBOX_FIFREEZE 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_UTMPX&&(KGEN_x304))||((KGEN_x278)&&(KGEN_x304)&&(defined KGENMACRO_WHO||(KGEN_x278)))))
#ifdef KGENMACRO_WHO
#define CFG_WHO 1
#else
#define CFG_WHO 0
#endif
#endif
#ifdef KGENMACRO_HWCLOCK
#define CFG_HWCLOCK 1
#else
#define CFG_HWCLOCK 0
#endif
#ifdef KGENMACRO_DMESG
#define CFG_DMESG 1
#else
#define CFG_DMESG 0
#endif
#ifdef KGENMACRO_MKNOD
#define CFG_MKNOD 1
#else
#define CFG_MKNOD 0
#endif
#ifdef KGENMACRO_MOUNTPOINT
#define CFG_MOUNTPOINT 1
#else
#define CFG_MOUNTPOINT 0
#endif
#if (defined KGENMACRO_TOYBOX_FALLOCATE)
#ifdef KGENMACRO_TOYBOX_FALLOCATE
#define CFG_TOYBOX_FALLOCATE 1
#else
#define CFG_TOYBOX_FALLOCATE 0
#endif
#endif
#ifdef KGENMACRO_KILLALL
#define CFG_KILLALL 1
#else
#define CFG_KILLALL 0
#endif
#if (((defined KGENMACRO_TOYBOX_LIBCRYPTO&&(KGEN_x103))||((KGEN_x64)&&(KGEN_x103)&&((KGEN_x64)||defined KGENMACRO_SHA224SUM))))
#ifdef KGENMACRO_SHA224SUM
#define CFG_SHA224SUM 1
#else
#define CFG_SHA224SUM 0
#endif
#endif
#ifdef KGENMACRO_DHCPD
#define CFG_DHCPD 1
#else
#define CFG_DHCPD 0
#endif
#ifdef KGENMACRO_SLEEP
#define CFG_SLEEP 1
#else
#define CFG_SLEEP 0
#endif
#ifdef KGENMACRO_INSTALL
#define CFG_INSTALL 1
#else
#define CFG_INSTALL 0
#endif
#if (((defined KGENMACRO_TOYBOX_UTMPX&&(KGEN_x357))||((KGEN_x278)&&(KGEN_x357)&&((KGEN_x278)||defined KGENMACRO_W))))
#ifdef KGENMACRO_W
#define CFG_W 1
#else
#define CFG_W 0
#endif
#endif
#ifdef KGENMACRO_BASE64
#define CFG_BASE64 1
#else
#define CFG_BASE64 0
#endif
#if (((defined KGENMACRO_TOYBOX_FALLOCATE&&(KGEN_x390))||((KGEN_x364)&&(KGEN_x390)&&(defined KGENMACRO_FALLOCATE||(KGEN_x364)))))
#ifdef KGENMACRO_FALLOCATE
#define CFG_FALLOCATE 1
#else
#define CFG_FALLOCATE 0
#endif
#endif
#ifdef KGENMACRO_KLOGD
#define CFG_KLOGD 1
#else
#define CFG_KLOGD 0
#endif
#ifdef KGENMACRO_INSMOD
#define CFG_INSMOD 1
#else
#define CFG_INSMOD 0
#endif
#ifdef KGENMACRO_MKSWAP
#define CFG_MKSWAP 1
#else
#define CFG_MKSWAP 0
#endif
#ifdef KGENMACRO_RENICE
#define CFG_RENICE 1
#else
#define CFG_RENICE 0
#endif
#ifdef KGENMACRO_CHATTR
#define CFG_CHATTR 1
#else
#define CFG_CHATTR 0
#endif
#ifdef KGENMACRO_NETSTAT
#define CFG_NETSTAT 1
#else
#define CFG_NETSTAT 0
#endif
#ifdef KGENMACRO_OD
#define CFG_OD 1
#else
#define CFG_OD 0
#endif
#if (((defined KGENMACRO_DHCPD&&(defined KGENMACRO_DHCPD||(!defined KGENMACRO_DEBUG_DHCP)))||((!defined KGENMACRO_DHCPD)&&(!defined KGENMACRO_DEBUG_DHCP))))
#ifdef KGENMACRO_DEBUG_DHCP
#define CFG_DEBUG_DHCP 1
#else
#define CFG_DEBUG_DHCP 0
#endif
#endif
#ifdef KGENMACRO_TOYBOX_DEBUG
#define CFG_TOYBOX_DEBUG 1
#else
#define CFG_TOYBOX_DEBUG 0
#endif
#ifdef KGENMACRO_TTY
#define CFG_TTY 1
#else
#define CFG_TTY 0
#endif
#ifdef KGENMACRO_DU
#define CFG_DU 1
#else
#define CFG_DU 0
#endif
#ifdef KGENMACRO_CROND
#define CFG_CROND 1
#else
#define CFG_CROND 0
#endif
#ifdef KGENMACRO_TOYBOX_MUSL_NOMMU_IS_BROKEN
#define CFG_TOYBOX_MUSL_NOMMU_IS_BROKEN 1
#else
#define CFG_TOYBOX_MUSL_NOMMU_IS_BROKEN 0
#endif
#ifdef KGENMACRO_PWD
#define CFG_PWD 1
#else
#define CFG_PWD 0
#endif
#if (((KGEN_x583)&&(KGEN_x587)))
#ifdef KGENMACRO_EGREP
#define CFG_EGREP 1
#else
#define CFG_EGREP 0
#endif
#endif
#if (((KGEN_x66)||((!defined KGENMACRO_TOYBOX_FORK)&&(!defined KGENMACRO_BOOTCHARTD))))
#ifdef KGENMACRO_BOOTCHARTD
#define CFG_BOOTCHARTD 1
#else
#define CFG_BOOTCHARTD 0
#endif
#endif
#ifdef KGENMACRO_COMM
#define CFG_COMM 1
#else
#define CFG_COMM 0
#endif
#ifdef KGENMACRO_ONEIT
#define CFG_ONEIT 1
#else
#define CFG_ONEIT 0
#endif
#ifdef KGENMACRO_UNLINK
#define CFG_UNLINK 1
#else
#define CFG_UNLINK 0
#endif
#ifdef KGENMACRO_NETCAT
#define CFG_NETCAT 1
#else
#define CFG_NETCAT 0
#endif
#if (((defined KGENMACRO_PASSWD&&(defined KGENMACRO_PASSWD||(!defined KGENMACRO_PASSWD_SAD)))||((!defined KGENMACRO_PASSWD)&&(!defined KGENMACRO_PASSWD_SAD))))
#ifdef KGENMACRO_PASSWD_SAD
#define CFG_PASSWD_SAD 1
#else
#define CFG_PASSWD_SAD 0
#endif
#endif
#ifdef KGENMACRO_HEXEDIT
#define CFG_HEXEDIT 1
#else
#define CFG_HEXEDIT 0
#endif
#if (((defined KGENMACRO_TOYBOX_LIBCRYPTO&&(KGEN_x496))||((KGEN_x64)&&(KGEN_x496)&&((KGEN_x64)||defined KGENMACRO_SHA256SUM))))
#ifdef KGENMACRO_SHA256SUM
#define CFG_SHA256SUM 1
#else
#define CFG_SHA256SUM 0
#endif
#endif
#ifdef KGENMACRO_CHVT
#define CFG_CHVT 1
#else
#define CFG_CHVT 0
#endif
#ifdef KGENMACRO_FLOCK
#define CFG_FLOCK 1
#else
#define CFG_FLOCK 0
#endif
#ifdef KGENMACRO_XARGS
#define CFG_XARGS 1
#else
#define CFG_XARGS 0
#endif
#ifdef KGENMACRO_FSTYPE
#define CFG_FSTYPE 1
#else
#define CFG_FSTYPE 0
#endif
#ifdef KGENMACRO_LSMOD
#define CFG_LSMOD 1
#else
#define CFG_LSMOD 0
#endif
#ifdef KGENMACRO_MIX
#define CFG_MIX 1
#else
#define CFG_MIX 0
#endif
#ifdef KGENMACRO_INIT
#define CFG_INIT 1
#else
#define CFG_INIT 0
#endif
#ifdef KGENMACRO_DEALLOCVT
#define CFG_DEALLOCVT 1
#else
#define CFG_DEALLOCVT 0
#endif
#if (((defined KGENMACRO_TAIL&&(KGEN_x399))||((KGEN_x373)&&(KGEN_x399)&&(defined KGENMACRO_TAIL_SEEK||(KGEN_x373)))))
#ifdef KGENMACRO_TAIL_SEEK
#define CFG_TAIL_SEEK 1
#else
#define CFG_TAIL_SEEK 0
#endif
#endif
#ifdef KGENMACRO_BASENAME
#define CFG_BASENAME 1
#else
#define CFG_BASENAME 0
#endif
#ifdef KGENMACRO_RM
#define CFG_RM 1
#else
#define CFG_RM 0
#endif
#ifdef KGENMACRO_LN
#define CFG_LN 1
#else
#define CFG_LN 0
#endif
#if (((KGEN_x457)||((!defined KGENMACRO_TOYBOX_ICONV)&&(!defined KGENMACRO_ICONV))))
#ifdef KGENMACRO_ICONV
#define CFG_ICONV 1
#else
#define CFG_ICONV 0
#endif
#endif
#ifdef KGENMACRO_FIND
#define CFG_FIND 1
#else
#define CFG_FIND 0
#endif
#if (((defined KGENMACRO_MKE2FS&&(defined KGENMACRO_MKE2FS||(!defined KGENMACRO_MKE2FS_JOURNAL)))||((!defined KGENMACRO_MKE2FS)&&(!defined KGENMACRO_MKE2FS_JOURNAL))))
#ifdef KGENMACRO_MKE2FS_JOURNAL
#define CFG_MKE2FS_JOURNAL 1
#else
#define CFG_MKE2FS_JOURNAL 0
#endif
#endif
#ifdef KGENMACRO_MODPROBE
#define CFG_MODPROBE 1
#else
#define CFG_MODPROBE 0
#endif
#ifdef KGENMACRO_CUT
#define CFG_CUT 1
#else
#define CFG_CUT 0
#endif
#if (((defined KGENMACRO_MKE2FS&&(defined KGENMACRO_MKE2FS||(!defined KGENMACRO_MKE2FS_LABEL)))||((!defined KGENMACRO_MKE2FS)&&(!defined KGENMACRO_MKE2FS_LABEL))))
#ifdef KGENMACRO_MKE2FS_LABEL
#define CFG_MKE2FS_LABEL 1
#else
#define CFG_MKE2FS_LABEL 0
#endif
#endif
#ifdef KGENMACRO_XXD
#define CFG_XXD 1
#else
#define CFG_XXD 0
#endif
#ifdef KGENMACRO_XZCAT
#define CFG_XZCAT 1
#else
#define CFG_XZCAT 0
#endif
#ifdef KGENMACRO_HELLO
#define CFG_HELLO 1
#else
#define CFG_HELLO 0
#endif
#if (((KGEN_x99)||((!defined KGENMACRO_KLOGD)&&(!defined KGENMACRO_KLOGD_SOURCE_RING_BUFFER))))
#ifdef KGENMACRO_KLOGD_SOURCE_RING_BUFFER
#define CFG_KLOGD_SOURCE_RING_BUFFER 1
#else
#define CFG_KLOGD_SOURCE_RING_BUFFER 0
#endif
#endif
#ifdef KGENMACRO_COUNT
#define CFG_COUNT 1
#else
#define CFG_COUNT 0
#endif
#if (((KGEN_x76)&&(KGEN_x78)))
#ifdef KGENMACRO_SORT_FLOAT
#define CFG_SORT_FLOAT 1
#else
#define CFG_SORT_FLOAT 0
#endif
#endif
#ifdef KGENMACRO_MD5SUM
#define CFG_MD5SUM 1
#else
#define CFG_MD5SUM 0
#endif
#if (defined KGENMACRO_TOYBOX_UID_SYS)
#ifdef KGENMACRO_TOYBOX_UID_SYS
#define CFG_TOYBOX_UID_SYS 100
#else
#define CFG_TOYBOX_UID_SYS 0
#endif
#endif
#ifdef KGENMACRO_FALSE
#define CFG_FALSE 1
#else
#define CFG_FALSE 0
#endif
#ifdef KGENMACRO_TAR
#define CFG_TAR 1
#else
#define CFG_TAR 0
#endif
#if (((defined KGENMACRO_TOYBOX_SHADOW&&(KGEN_x406))||((KGEN_x265)&&(KGEN_x406)&&((KGEN_x265)||defined KGENMACRO_LOGIN))))
#ifdef KGENMACRO_LOGIN
#define CFG_LOGIN 1
#else
#define CFG_LOGIN 0
#endif
#endif
#ifdef KGENMACRO_MAKEDEVS
#define CFG_MAKEDEVS 1
#else
#define CFG_MAKEDEVS 0
#endif
#ifdef KGENMACRO_PRINTENV
#define CFG_PRINTENV 1
#else
#define CFG_PRINTENV 0
#endif
#ifdef KGENMACRO_TOYBOX_LIBCRYPTO
#define CFG_TOYBOX_LIBCRYPTO 1
#else
#define CFG_TOYBOX_LIBCRYPTO 0
#endif
#ifdef KGENMACRO_PING
#define CFG_PING 1
#else
#define CFG_PING 0
#endif
#if (((KGEN_x512)&&(KGEN_x518)))
#ifdef KGENMACRO_MKDIR_Z
#define CFG_MKDIR_Z 1
#else
#define CFG_MKDIR_Z 0
#endif
#endif
#if (((defined KGENMACRO_CAT&&(defined KGENMACRO_CAT||(!defined KGENMACRO_CAT_V)))||((!defined KGENMACRO_CAT)&&(!defined KGENMACRO_CAT_V))))
#ifdef KGENMACRO_CAT_V
#define CFG_CAT_V 1
#else
#define CFG_CAT_V 0
#endif
#endif
#ifdef KGENMACRO_IOTOP
#define CFG_IOTOP 1
#else
#define CFG_IOTOP 0
#endif
#ifdef KGENMACRO_COMPRESS
#define CFG_COMPRESS 1
#else
#define CFG_COMPRESS 0
#endif
#if ((!defined KGENMACRO_TOYBOX_ON_ANDROID))
#ifdef KGENMACRO_TOYBOX_ON_ANDROID
#define CFG_TOYBOX_ON_ANDROID 1
#else
#define CFG_TOYBOX_ON_ANDROID 0
#endif
#endif
#ifdef KGENMACRO_FSYNC
#define CFG_FSYNC 1
#else
#define CFG_FSYNC 0
#endif
#ifdef KGENMACRO_ECHO
#define CFG_ECHO 1
#else
#define CFG_ECHO 0
#endif
#ifdef KGENMACRO_TELNETD
#define CFG_TELNETD 1
#else
#define CFG_TELNETD 0
#endif
#ifdef KGENMACRO_TRUE
#define CFG_TRUE 1
#else
#define CFG_TRUE 0
#endif
#ifdef KGENMACRO_CPIO
#define CFG_CPIO 1
#else
#define CFG_CPIO 0
#endif
#if (((KGEN_x416)&&(KGEN_x420)))
#ifdef KGENMACRO_MKFIFO_Z
#define CFG_MKFIFO_Z 1
#else
#define CFG_MKFIFO_Z 0
#endif
#endif
#ifdef KGENMACRO_FSCK
#define CFG_FSCK 1
#else
#define CFG_FSCK 0
#endif
#if (defined KGENMACRO_TOYBOX_UID_USR)
#ifdef KGENMACRO_TOYBOX_UID_USR
#define CFG_TOYBOX_UID_USR 500
#else
#define CFG_TOYBOX_UID_USR 0
#endif
#endif
#ifdef KGENMACRO_CHGRP
#define CFG_CHGRP 1
#else
#define CFG_CHGRP 0
#endif
#ifdef KGENMACRO_MDEV
#define CFG_MDEV 1
#else
#define CFG_MDEV 0
#endif
#ifdef KGENMACRO_TR
#define CFG_TR 1
#else
#define CFG_TR 0
#endif
#ifdef KGENMACRO_DHCP
#define CFG_DHCP 1
#else
#define CFG_DHCP 0
#endif
#ifdef KGENMACRO_GROUPDEL
#define CFG_GROUPDEL 1
#else
#define CFG_GROUPDEL 0
#endif
#ifdef KGENMACRO_EXPAND
#define CFG_EXPAND 1
#else
#define CFG_EXPAND 0
#endif
#ifdef KGENMACRO_CAT
#define CFG_CAT 1
#else
#define CFG_CAT 0
#endif
#ifdef KGENMACRO_SWAPOFF
#define CFG_SWAPOFF 1
#else
#define CFG_SWAPOFF 0
#endif
#if (((defined KGENMACRO_TOYBOX_HELP&&(KGEN_x547))||((KGEN_x167)&&(KGEN_x547)&&((KGEN_x167)||defined KGENMACRO_HELP))))
#ifdef KGENMACRO_HELP
#define CFG_HELP 1
#else
#define CFG_HELP 0
#endif
#endif
#ifdef KGENMACRO_DD
#define CFG_DD 1
#else
#define CFG_DD 0
#endif
#ifdef KGENMACRO_RMDIR
#define CFG_RMDIR 1
#else
#define CFG_RMDIR 0
#endif
#ifdef KGENMACRO_GREP
#define CFG_GREP 1
#else
#define CFG_GREP 0
#endif
#ifdef KGENMACRO_BLOCKDEV
#define CFG_BLOCKDEV 1
#else
#define CFG_BLOCKDEV 0
#endif
#ifdef KGENMACRO_UUENCODE
#define CFG_UUENCODE 1
#else
#define CFG_UUENCODE 0
#endif
#ifdef KGENMACRO_TUNCTL
#define CFG_TUNCTL 1
#else
#define CFG_TUNCTL 0
#endif
#ifdef KGENMACRO_TOYBOX_PEDANTIC_ARGS
#define CFG_TOYBOX_PEDANTIC_ARGS 1
#else
#define CFG_TOYBOX_PEDANTIC_ARGS 0
#endif
#ifdef KGENMACRO_IORENICE
#define CFG_IORENICE 1
#else
#define CFG_IORENICE 0
#endif
#if (((KGEN_x258)&&(KGEN_x262)))
#ifdef KGENMACRO_SLEEP_FLOAT
#define CFG_SLEEP_FLOAT 1
#else
#define CFG_SLEEP_FLOAT 0
#endif
#endif
#ifdef KGENMACRO_PIDOF
#define CFG_PIDOF 1
#else
#define CFG_PIDOF 0
#endif
#ifdef KGENMACRO_CHOWN
#define CFG_CHOWN 1
#else
#define CFG_CHOWN 0
#endif
#ifdef KGENMACRO_CHROOT
#define CFG_CHROOT 1
#else
#define CFG_CHROOT 0
#endif
#ifdef KGENMACRO_VMSTAT
#define CFG_VMSTAT 1
#else
#define CFG_VMSTAT 0
#endif
#ifdef KGENMACRO_SKELETON_ALIAS
#define CFG_SKELETON_ALIAS 1
#else
#define CFG_SKELETON_ALIAS 0
#endif
#ifdef KGENMACRO_NL
#define CFG_NL 1
#else
#define CFG_NL 0
#endif
#ifdef KGENMACRO_PIVOT_ROOT
#define CFG_PIVOT_ROOT 1
#else
#define CFG_PIVOT_ROOT 0
#endif
#if (((defined KGENMACRO_TOYBOX_LIBZ&&(KGEN_x213))||((KGEN_x158)&&(KGEN_x213)&&((KGEN_x158)||defined KGENMACRO_ZCAT))))
#ifdef KGENMACRO_ZCAT
#define CFG_ZCAT 1
#else
#define CFG_ZCAT 0
#endif
#endif
#ifdef KGENMACRO_PMAP
#define CFG_PMAP 1
#else
#define CFG_PMAP 0
#endif
#if (((defined KGENMACRO_TOYBOX_SHADOW&&(KGEN_x280))||((KGEN_x265)&&(KGEN_x280)&&(defined KGENMACRO_SU||(KGEN_x265)))))
#ifdef KGENMACRO_SU
#define CFG_SU 1
#else
#define CFG_SU 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_ON_ANDROID&&(KGEN_x161))||((KGEN_x136)&&(KGEN_x161)&&(defined KGENMACRO_STOP||(KGEN_x136)))))
#ifdef KGENMACRO_STOP
#define CFG_STOP 1
#else
#define CFG_STOP 0
#endif
#endif
#if (((defined KGENMACRO_LS&&(KGEN_x146))||((KGEN_x121)&&(KGEN_x146)&&(defined KGENMACRO_LS_COLOR||(KGEN_x121)))))
#ifdef KGENMACRO_LS_COLOR
#define CFG_LS_COLOR 1
#else
#define CFG_LS_COLOR 0
#endif
#endif
#ifdef KGENMACRO_DUMPLEASES
#define CFG_DUMPLEASES 1
#else
#define CFG_DUMPLEASES 0
#endif
#ifdef KGENMACRO_HOSTNAME
#define CFG_HOSTNAME 1
#else
#define CFG_HOSTNAME 0
#endif
#ifdef KGENMACRO_SYSCTL
#define CFG_SYSCTL 1
#else
#define CFG_SYSCTL 0
#endif
#ifdef KGENMACRO_NPROC
#define CFG_NPROC 1
#else
#define CFG_NPROC 0
#endif
#ifdef KGENMACRO_ROUTE
#define CFG_ROUTE 1
#else
#define CFG_ROUTE 0
#endif
#ifdef KGENMACRO_LSOF
#define CFG_LSOF 1
#else
#define CFG_LSOF 0
#endif
#ifdef KGENMACRO_USERDEL
#define CFG_USERDEL 1
#else
#define CFG_USERDEL 0
#endif
#ifdef KGENMACRO_LOSETUP
#define CFG_LOSETUP 1
#else
#define CFG_LOSETUP 0
#endif
#if (defined KGENMACRO_TOYBOX_UTMPX)
#ifdef KGENMACRO_TOYBOX_UTMPX
#define CFG_TOYBOX_UTMPX 1
#else
#define CFG_TOYBOX_UTMPX 0
#endif
#endif
#ifdef KGENMACRO_TOYBOX_LIBZ
#define CFG_TOYBOX_LIBZ 1
#else
#define CFG_TOYBOX_LIBZ 0
#endif
#ifdef KGENMACRO_REV
#define CFG_REV 1
#else
#define CFG_REV 0
#endif
#ifdef KGENMACRO_SH
#define CFG_SH 1
#else
#define CFG_SH 0
#endif
#ifdef KGENMACRO_IPCRM
#define CFG_IPCRM 1
#else
#define CFG_IPCRM 0
#endif
#ifdef KGENMACRO_LINK
#define CFG_LINK 1
#else
#define CFG_LINK 0
#endif
#if (defined KGENMACRO_TOYBOX_ICONV)
#ifdef KGENMACRO_TOYBOX_ICONV
#define CFG_TOYBOX_ICONV 1
#else
#define CFG_TOYBOX_ICONV 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_PRLIMIT&&(KGEN_x112))||((KGEN_x87)&&(KGEN_x112)&&(defined KGENMACRO_ULIMIT||(KGEN_x87)))))
#ifdef KGENMACRO_ULIMIT
#define CFG_ULIMIT 1
#else
#define CFG_ULIMIT 0
#endif
#endif
#ifdef KGENMACRO_DATE
#define CFG_DATE 1
#else
#define CFG_DATE 0
#endif
#ifdef KGENMACRO_WHOAMI
#define CFG_WHOAMI 1
#else
#define CFG_WHOAMI 0
#endif
#if (((defined KGENMACRO_MKE2FS&&(defined KGENMACRO_MKE2FS||(!defined KGENMACRO_MKE2FS_GEN)))||((!defined KGENMACRO_MKE2FS)&&(!defined KGENMACRO_MKE2FS_GEN))))
#ifdef KGENMACRO_MKE2FS_GEN
#define CFG_MKE2FS_GEN 1
#else
#define CFG_MKE2FS_GEN 0
#endif
#endif
#ifdef KGENMACRO_GETTY
#define CFG_GETTY 1
#else
#define CFG_GETTY 0
#endif
#ifdef KGENMACRO_FTPPUT
#define CFG_FTPPUT 1
#else
#define CFG_FTPPUT 0
#endif
#if (((defined KGENMACRO_TOYBOX_SELINUX&&(KGEN_x324))||((KGEN_x25)&&(KGEN_x324)&&((KGEN_x25)||defined KGENMACRO_SETENFORCE))))
#ifdef KGENMACRO_SETENFORCE
#define CFG_SETENFORCE 1
#else
#define CFG_SETENFORCE 0
#endif
#endif
#ifdef KGENMACRO_TOP
#define CFG_TOP 1
#else
#define CFG_TOP 0
#endif
#ifdef KGENMACRO_EJECT
#define CFG_EJECT 1
#else
#define CFG_EJECT 0
#endif
#if (((KGEN_x23)||(KGEN_x25))) && (((KGEN_x23)||(KGEN_x28)))
#ifdef KGENMACRO_TOYBOX_LSM_NONE
#define CFG_TOYBOX_LSM_NONE 1
#else
#define CFG_TOYBOX_LSM_NONE 0
#endif
#endif
#ifdef KGENMACRO_FILE
#define CFG_FILE 1
#else
#define CFG_FILE 0
#endif
#if (((defined KGENMACRO_TOYBOX_SELINUX&&(KGEN_x317))||((KGEN_x25)&&(KGEN_x317)&&((KGEN_x25)||defined KGENMACRO_CHCON))))
#ifdef KGENMACRO_CHCON
#define CFG_CHCON 1
#else
#define CFG_CHCON 0
#endif
#endif
#ifdef KGENMACRO_SORT
#define CFG_SORT 1
#else
#define CFG_SORT 0
#endif
#ifdef KGENMACRO_SKELETON
#define CFG_SKELETON 1
#else
#define CFG_SKELETON 0
#endif
#if (((defined KGENMACRO_TOYBOX_FORK&&(defined KGENMACRO_TOYBOX_FORK||(!defined KGENMACRO_TCPSVD)))||((!defined KGENMACRO_TOYBOX_FORK)&&(!defined KGENMACRO_TCPSVD))))
#ifdef KGENMACRO_TCPSVD
#define CFG_TCPSVD 1
#else
#define CFG_TCPSVD 0
#endif
#endif
#ifdef KGENMACRO_TOUCH
#define CFG_TOUCH 1
#else
#define CFG_TOUCH 0
#endif
#ifdef KGENMACRO_REBOOT
#define CFG_REBOOT 1
#else
#define CFG_REBOOT 0
#endif
#if ((!defined KGENMACRO_TOYBOX_CONTAINER))
#ifdef KGENMACRO_TOYBOX_CONTAINER
#define CFG_TOYBOX_CONTAINER 1
#else
#define CFG_TOYBOX_CONTAINER 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_FLOAT&&(KGEN_x204))||((KGEN_x178)&&(KGEN_x204)&&(defined KGENMACRO_TIME||(KGEN_x178)))))
#ifdef KGENMACRO_TIME
#define CFG_TIME 1
#else
#define CFG_TIME 0
#endif
#endif
#ifdef KGENMACRO_READAHEAD
#define CFG_READAHEAD 1
#else
#define CFG_READAHEAD 0
#endif
#ifdef KGENMACRO_SYSLOGD
#define CFG_SYSLOGD 1
#else
#define CFG_SYSLOGD 0
#endif
#ifdef KGENMACRO_TOYBOX_SMACK
#define CFG_TOYBOX_SMACK 1
#else
#define CFG_TOYBOX_SMACK 0
#endif
#if (((defined KGENMACRO_NETCAT&&(KGEN_x367))||((KGEN_x347)&&(KGEN_x367)&&(defined KGENMACRO_NETCAT_LISTEN||(KGEN_x347)))))
#ifdef KGENMACRO_NETCAT_LISTEN
#define CFG_NETCAT_LISTEN 1
#else
#define CFG_NETCAT_LISTEN 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_SELINUX&&(KGEN_x503))||((KGEN_x25)&&(KGEN_x503)&&((KGEN_x25)||defined KGENMACRO_GETENFORCE))))
#ifdef KGENMACRO_GETENFORCE
#define CFG_GETENFORCE 1
#else
#define CFG_GETENFORCE 0
#endif
#endif
#ifdef KGENMACRO_FREE
#define CFG_FREE 1
#else
#define CFG_FREE 0
#endif
#if (((defined KGENMACRO_XARGS&&(defined KGENMACRO_XARGS||(!defined KGENMACRO_XARGS_PEDANTIC)))||((!defined KGENMACRO_XARGS)&&(!defined KGENMACRO_XARGS_PEDANTIC))))
#ifdef KGENMACRO_XARGS_PEDANTIC
#define CFG_XARGS_PEDANTIC 1
#else
#define CFG_XARGS_PEDANTIC 0
#endif
#endif
#if (((defined KGENMACRO_TOYBOX_ON_ANDROID&&(KGEN_x428))||((KGEN_x136)&&(KGEN_x428)&&((KGEN_x136)||defined KGENMACRO_LOG))))
#ifdef KGENMACRO_LOG
#define CFG_LOG 1
#else
#define CFG_LOG 0
#endif
#endif
#ifdef KGENMACRO_ARPING
#define CFG_ARPING 1
#else
#define CFG_ARPING 0
#endif
#if (((defined KGENMACRO_CP&&(KGEN_x557))||((KGEN_x532)&&(KGEN_x557)&&(defined KGENMACRO_CP_PRESERVE||(KGEN_x532)))))
#ifdef KGENMACRO_CP_PRESERVE
#define CFG_CP_PRESERVE 1
#else
#define CFG_CP_PRESERVE 0
#endif
#endif

#define USE_TOYBOX_CONTAINER(...) __VA_ARGS__
#define USE_TOYBOX_FIFREEZE(...) __VA_ARGS__
#define USE_TOYBOX_ICONV(...) __VA_ARGS__ 
#define USE_TOYBOX_FALLOCATE(...) __VA_ARGS__ 
#define USE_TOYBOX_UTMPX(...) __VA_ARGS__ 
#define USE_TOYBOX_SHADOW(...) __VA_ARGS__ 
#define USE_TOYBOX_ON_ANDROID(...) __VA_ARGS__
#define USE_TOYBOX_ANDROID_SCHEDPOLICY(...) __VA_ARGS__
#define USE_TOYBOX_FORK(...) __VA_ARGS__ 
#define USE_TOYBOX_PRLIMIT(...) __VA_ARGS__
#define USE_BASENAME(...) __VA_ARGS__ 
#define USE_CAL(...) __VA_ARGS__ 
#define USE_CAT(...) __VA_ARGS__ 
#define USE_CAT_V(...) __VA_ARGS__
#define USE_CATV(...) __VA_ARGS__ 
#define USE_CHGRP(...) __VA_ARGS__ 
#define USE_CHOWN(...) __VA_ARGS__ 
#define USE_CHMOD(...) __VA_ARGS__ 
#define USE_CKSUM(...) __VA_ARGS__ 
#define USE_CMP(...) __VA_ARGS__ 
#define USE_COMM(...) __VA_ARGS__ 
#define USE_CP(...) __VA_ARGS__ 
#define USE_CP_PRESERVE(...) __VA_ARGS__ 
#define USE_MV(...) __VA_ARGS__ 
#define USE_INSTALL(...) __VA_ARGS__ 
#define USE_CPIO(...) __VA_ARGS__ 
#define USE_CUT(...) __VA_ARGS__ 
#define USE_DATE(...) __VA_ARGS__ 
#define USE_DF(...) __VA_ARGS__ 
#define USE_DIRNAME(...) __VA_ARGS__ 
#define USE_DU(...) __VA_ARGS__ 
#define USE_ECHO(...) __VA_ARGS__ 
#define USE_ENV(...) __VA_ARGS__ 
#define USE_EXPAND(...) __VA_ARGS__ 
#define USE_FALSE(...) __VA_ARGS__ 
#define USE_FILE(...) __VA_ARGS__ 
#define USE_FIND(...) __VA_ARGS__ 
#define USE_GREP(...) __VA_ARGS__ 
#define USE_EGREP(...) __VA_ARGS__ 
#define USE_FGREP(...) __VA_ARGS__ 
#define USE_HEAD(...) __VA_ARGS__ 
#define USE_ID(...) __VA_ARGS__ 
#define USE_ID_Z(...) __VA_ARGS__
#define USE_GROUPS(...) __VA_ARGS__ 
#define USE_LOGNAME(...) __VA_ARGS__ 
#define USE_WHOAMI(...) __VA_ARGS__ 
#define USE_KILL(...) __VA_ARGS__ 
#define USE_KILLALL5(...) __VA_ARGS__ 
#define USE_LINK(...) __VA_ARGS__ 
#define USE_LN(...) __VA_ARGS__ 
#define USE_LS(...) __VA_ARGS__ 
#define USE_LS_COLOR(...) __VA_ARGS__ 
#define USE_MKDIR(...) __VA_ARGS__ 
#define USE_MKDIR_Z(...) __VA_ARGS__
#define USE_MKFIFO(...) __VA_ARGS__ 
#define USE_MKFIFO_Z(...) __VA_ARGS__
#define USE_NICE(...) __VA_ARGS__ 
#define USE_NL(...) __VA_ARGS__ 
#define USE_NOHUP(...) __VA_ARGS__ 
#define USE_OD(...) __VA_ARGS__ 
#define USE_PASTE(...) __VA_ARGS__ 
#define USE_PATCH(...) __VA_ARGS__ 
#define USE_PRINTF(...) __VA_ARGS__ 
#define USE_PS(...) __VA_ARGS__ 
#define USE_TOP(...) __VA_ARGS__ 
#define USE_IOTOP(...) __VA_ARGS__ 
#define USE_PGREP(...) __VA_ARGS__ 
#define USE_PKILL(...) __VA_ARGS__ 
#define USE_PWD(...) __VA_ARGS__ 
#define USE_RENICE(...) __VA_ARGS__ 
#define USE_RM(...) __VA_ARGS__ 
#define USE_RMDIR(...) __VA_ARGS__ 
#define USE_SED(...) __VA_ARGS__ 
#define USE_SLEEP(...) __VA_ARGS__ 
#define USE_SLEEP_FLOAT(...) __VA_ARGS__ 
#define USE_SORT(...) __VA_ARGS__ 
#define USE_SORT_BIG(...) __VA_ARGS__ 
#define USE_SORT_FLOAT(...) __VA_ARGS__ 
#define USE_SPLIT(...) __VA_ARGS__ 
#define USE_STRINGS(...) __VA_ARGS__ 
#define USE_TAIL(...) __VA_ARGS__ 
#define USE_TAIL_SEEK(...) __VA_ARGS__ 
#define USE_TEE(...) __VA_ARGS__ 
#define USE_TIME(...) __VA_ARGS__ 
#define USE_TOUCH(...) __VA_ARGS__ 
#define USE_TRUE(...) __VA_ARGS__ 
#define USE_TTY(...) __VA_ARGS__ 
#define USE_ULIMIT(...) __VA_ARGS__
#define USE_UNAME(...) __VA_ARGS__ 
#define USE_UNIQ(...) __VA_ARGS__ 
#define USE_UNLINK(...) __VA_ARGS__ 
#define USE_UUDECODE(...) __VA_ARGS__ 
#define USE_UUENCODE(...) __VA_ARGS__ 
#define USE_WC(...) __VA_ARGS__ 
#define USE_WHO(...) __VA_ARGS__ 
#define USE_XARGS(...) __VA_ARGS__ 
#define USE_XARGS_PEDANTIC(...) __VA_ARGS__
#define USE_ARP(...) __VA_ARGS__
#define USE_ARPING(...) __VA_ARGS__
#define USE_BOOTCHARTD(...) __VA_ARGS__
#define USE_BRCTL(...) __VA_ARGS__
#define USE_COMPRESS(...) __VA_ARGS__
#define USE_DECOMPRESS(...) __VA_ARGS__
#define USE_CROND(...) __VA_ARGS__
#define USE_CRONTAB(...) __VA_ARGS__
#define USE_DD(...) __VA_ARGS__
#define USE_DHCP6(...) __VA_ARGS__
#define USE_DHCP(...) __VA_ARGS__
#define USE_DHCPD(...) __VA_ARGS__
#define USE_DEBUG_DHCP(...) __VA_ARGS__
#define USE_DIFF(...) __VA_ARGS__
#define USE_DUMPLEASES(...) __VA_ARGS__
#define USE_EXPR(...) __VA_ARGS__
#define USE_FDISK(...) __VA_ARGS__
#define USE_FOLD(...) __VA_ARGS__
#define USE_FSCK(...) __VA_ARGS__
#define USE_GETFATTR(...) __VA_ARGS__
#define USE_GETTY(...) __VA_ARGS__
#define USE_GROUPADD(...) __VA_ARGS__
#define USE_GROUPDEL(...) __VA_ARGS__
#define USE_GZIP(...) __VA_ARGS__
#define USE_GUNZIP(...) __VA_ARGS__
#define USE_ZCAT(...) __VA_ARGS__
#define USE_HOST(...) __VA_ARGS__
#define USE_ICONV(...) __VA_ARGS__
#define USE_INIT(...) __VA_ARGS__
#define USE_IP(...) __VA_ARGS__
#define USE_IPCRM(...) __VA_ARGS__
#define USE_IPCS(...) __VA_ARGS__
#define USE_KLOGD(...) __VA_ARGS__
#define USE_KLOGD_SOURCE_RING_BUFFER(...) __VA_ARGS__
#define USE_LAST(...) __VA_ARGS__
#define USE_LOGGER(...) __VA_ARGS__
#define USE_LSOF(...) __VA_ARGS__
#define USE_MDEV(...) __VA_ARGS__
#define USE_MDEV_CONF(...) __VA_ARGS__
#define USE_MKE2FS(...) __VA_ARGS__
#define USE_MKE2FS_JOURNAL(...) __VA_ARGS__
#define USE_MKE2FS_GEN(...) __VA_ARGS__
#define USE_MKE2FS_LABEL(...) __VA_ARGS__
#define USE_MKE2FS_EXTENDED(...) __VA_ARGS__
#define USE_MODPROBE(...) __VA_ARGS__
#define USE_MORE(...) __VA_ARGS__
#define USE_OPENVT(...) __VA_ARGS__
#define USE_DEALLOCVT(...) __VA_ARGS__
#define USE_PING(...) __VA_ARGS__
#define USE_ROUTE(...) __VA_ARGS__
#define USE_SETFATTR(...) __VA_ARGS__
#define USE_SH(...) __VA_ARGS__
#define USE_CD(...) __VA_ARGS__
#define USE_EXIT(...) __VA_ARGS__
#define USE_SULOGIN(...) __VA_ARGS__
#define USE_SYSLOGD(...) __VA_ARGS__
#define USE_TAR(...) __VA_ARGS__
#define USE_TCPSVD(...) __VA_ARGS__
#define USE_TELNET(...) __VA_ARGS__
#define USE_TELNETD(...) __VA_ARGS__
#define USE_TEST(...) __VA_ARGS__
#define USE_TFTP(...) __VA_ARGS__
#define USE_TFTPD(...) __VA_ARGS__
#define USE_TRACEROUTE(...) __VA_ARGS__
#define USE_TR(...) __VA_ARGS__
#define USE_USERADD(...) __VA_ARGS__
#define USE_USERDEL(...) __VA_ARGS__
#define USE_VI(...) __VA_ARGS__
#define USE_WATCH(...) __VA_ARGS__
#define USE_WGET(...) __VA_ARGS__
#define USE_XZCAT(...) __VA_ARGS__
#define USE_ACPI(...) __VA_ARGS__ 
#define USE_ASCII(...) __VA_ARGS__
#define USE_BASE64(...) __VA_ARGS__ 
#define USE_BLKID(...) __VA_ARGS__ 
#define USE_FSTYPE(...) __VA_ARGS__ 
#define USE_BLOCKDEV(...) __VA_ARGS__ 
#define USE_BUNZIP2(...) __VA_ARGS__ 
#define USE_BZCAT(...) __VA_ARGS__ 
#define USE_CHCON(...) __VA_ARGS__
#define USE_CHROOT(...) __VA_ARGS__ 
#define USE_CHRT(...) __VA_ARGS__ 
#define USE_CHVT(...) __VA_ARGS__ 
#define USE_CLEAR(...) __VA_ARGS__ 
#define USE_COUNT(...) __VA_ARGS__ 
#define USE_DOS2UNIX(...) __VA_ARGS__ 
#define USE_UNIX2DOS(...) __VA_ARGS__ 
#define USE_EJECT(...) __VA_ARGS__ 
#define USE_FACTOR(...) __VA_ARGS__ 
#define USE_FALLOCATE(...) __VA_ARGS__ 
#define USE_FLOCK(...) __VA_ARGS__ 
#define USE_FREE(...) __VA_ARGS__ 
#define USE_FREERAMDISK(...) __VA_ARGS__ 
#define USE_FSFREEZE(...) __VA_ARGS__ 
#define USE_FSYNC(...) __VA_ARGS__ 
#define USE_HELP(...) __VA_ARGS__ 
#define USE_HELP_EXTRAS(...) __VA_ARGS__ 
#define USE_HEXEDIT(...) __VA_ARGS__ 
#define USE_HWCLOCK(...) __VA_ARGS__ 
#define USE_INOTIFYD(...) __VA_ARGS__ 
#define USE_INSMOD(...) __VA_ARGS__ 
#define USE_IONICE(...) __VA_ARGS__ 
#define USE_IORENICE(...) __VA_ARGS__ 
#define USE_LOGIN(...) __VA_ARGS__ 
#define USE_LOSETUP(...) __VA_ARGS__ 
#define USE_LSATTR(...) __VA_ARGS__ 
#define USE_CHATTR(...) __VA_ARGS__ 
#define USE_LSMOD(...) __VA_ARGS__ 
#define USE_LSPCI(...) __VA_ARGS__ 
#define USE_LSPCI_TEXT(...) __VA_ARGS__ 
#define USE_LSUSB(...) __VA_ARGS__ 
#define USE_MAKEDEVS(...) __VA_ARGS__ 
#define USE_MIX(...) __VA_ARGS__ 
#define USE_MKPASSWD(...) __VA_ARGS__ 
#define USE_MKSWAP(...) __VA_ARGS__ 
#define USE_MODINFO(...) __VA_ARGS__ 
#define USE_MOUNTPOINT(...) __VA_ARGS__ 
#define USE_NBD_CLIENT(...) __VA_ARGS__ 
#define USE_UNSHARE(...) __VA_ARGS__
#define USE_NSENTER(...) __VA_ARGS__
#define USE_ONEIT(...) __VA_ARGS__ 
#define USE_PARTPROBE(...) __VA_ARGS__ 
#define USE_PIVOT_ROOT(...) __VA_ARGS__ 
#define USE_PMAP(...) __VA_ARGS__ 
#define USE_PRINTENV(...) __VA_ARGS__ 
#define USE_PWDX(...) __VA_ARGS__ 
#define USE_READAHEAD(...) __VA_ARGS__ 
#define USE_READLINK(...) __VA_ARGS__ 
#define USE_REALPATH(...) __VA_ARGS__ 
#define USE_REBOOT(...) __VA_ARGS__ 
#define USE_RESET(...) __VA_ARGS__ 
#define USE_REV(...) __VA_ARGS__ 
#define USE_RMMOD(...) __VA_ARGS__ 
#define USE_SETSID(...) __VA_ARGS__ 
#define USE_SHRED(...) __VA_ARGS__ 
#define USE_STAT(...) __VA_ARGS__ 
#define USE_SWAPOFF(...) __VA_ARGS__ 
#define USE_SWAPON(...) __VA_ARGS__ 
#define USE_SWITCH_ROOT(...) __VA_ARGS__ 
#define USE_SYSCTL(...) __VA_ARGS__ 
#define USE_TAC(...) __VA_ARGS__ 
#define USE_NPROC(...) __VA_ARGS__ 
#define USE_TASKSET(...) __VA_ARGS__ 
#define USE_TIMEOUT(...) __VA_ARGS__ 
#define USE_TRUNCATE(...) __VA_ARGS__ 
#define USE_UPTIME(...) __VA_ARGS__ 
#define USE_USLEEP(...) __VA_ARGS__ 
#define USE_VCONFIG(...) __VA_ARGS__ 
#define USE_VMSTAT(...) __VA_ARGS__ 
#define USE_W(...) __VA_ARGS__ 
#define USE_WHICH(...) __VA_ARGS__ 
#define USE_XXD(...) __VA_ARGS__ 
#define USE_YES(...) __VA_ARGS__ 
#define USE_FTPGET(...) __VA_ARGS__ 
#define USE_FTPPUT(...) __VA_ARGS__ 
#define USE_IFCONFIG(...) __VA_ARGS__ 
#define USE_MICROCOM(...) __VA_ARGS__ 
#define USE_NETCAT(...) __VA_ARGS__ 
#define USE_NETCAT_LISTEN(...) __VA_ARGS__ 
#define USE_NETSTAT(...) __VA_ARGS__ 
#define USE_RFKILL(...) __VA_ARGS__ 
#define USE_TUNCTL(...) __VA_ARGS__ 
#define USE_DMESG(...) __VA_ARGS__ 
#define USE_HOSTNAME(...) __VA_ARGS__ 
#define USE_KILLALL(...) __VA_ARGS__ 
#define USE_MD5SUM(...) __VA_ARGS__ 
#define USE_SHA1SUM(...) __VA_ARGS__ 
#define USE_SHA224SUM(...) __VA_ARGS__
#define USE_SHA256SUM(...) __VA_ARGS__
#define USE_SHA384SUM(...) __VA_ARGS__
#define USE_SHA512SUM(...) __VA_ARGS__
#define USE_MKNOD(...) __VA_ARGS__ 
#define USE_MKNOD_Z(...) __VA_ARGS__
#define USE_MKTEMP(...) __VA_ARGS__ 
#define USE_MOUNT(...) __VA_ARGS__ 
#define USE_PASSWD(...) __VA_ARGS__ 
#define USE_PASSWD_SAD(...) __VA_ARGS__
#define USE_PIDOF(...) __VA_ARGS__ 
#define USE_SEQ(...) __VA_ARGS__ 
#define USE_SU(...) __VA_ARGS__ 
#define USE_SYNC(...) __VA_ARGS__ 
#define USE_UMOUNT(...) __VA_ARGS__ 
#define USE_HELLO(...) __VA_ARGS__
#define USE_HOSTID(...) __VA_ARGS__
#define USE_SKELETON(...) __VA_ARGS__
#define USE_SKELETON_ALIAS(...) __VA_ARGS__
#define USE_TEST_HUMAN_READABLE(...) __VA_ARGS__
#define USE_TEST_MANY_OPTIONS(...) __VA_ARGS__
#define USE_TEST_SCANKEY(...) __VA_ARGS__
#define USE_TEST_UTF8TOWC(...) __VA_ARGS__
#define USE_GETENFORCE(...) __VA_ARGS__
#define USE_GETPROP(...) __VA_ARGS__
#define USE_LOAD_POLICY(...) __VA_ARGS__
#define USE_LOG(...) __VA_ARGS__
#define USE_RESTORECON(...) __VA_ARGS__
#define USE_RUNCON(...) __VA_ARGS__
#define USE_SENDEVENT(...) __VA_ARGS__
#define USE_SETENFORCE(...) __VA_ARGS__
#define USE_SETPROP(...) __VA_ARGS__
#define USE_START(...) __VA_ARGS__
#define USE_STOP(...) __VA_ARGS__
#define USE_TOYBOX(...) __VA_ARGS__ 
#define USE_TOYBOX_SUID(...) __VA_ARGS__ 
#define USE_TOYBOX_LSM_NONE(...) __VA_ARGS__ 
#define USE_TOYBOX_SELINUX(...) __VA_ARGS__
#define USE_TOYBOX_SMACK(...) __VA_ARGS__
#define USE_TOYBOX_LIBCRYPTO(...) __VA_ARGS__
#define USE_TOYBOX_LIBZ(...) __VA_ARGS__
#define USE_TOYBOX_FLOAT(...) __VA_ARGS__ 
#define USE_TOYBOX_HELP(...) __VA_ARGS__ 
#define USE_TOYBOX_HELP_DASHDASH(...) __VA_ARGS__ 
#define USE_TOYBOX_I18N(...) __VA_ARGS__ 
#define USE_TOYBOX_FREE(...) __VA_ARGS__
#define USE_TOYBOX_NORECURSE(...) __VA_ARGS__
#define USE_TOYBOX_DEBUG(...) __VA_ARGS__
#define USE_TOYBOX_PEDANTIC_ARGS(...) __VA_ARGS__
#define USE_TOYBOX_MUSL_NOMMU_IS_BROKEN(...) __VA_ARGS__
