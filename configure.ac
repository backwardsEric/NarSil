dnl Process this file with autoconf to produce a configure script.
AC_INIT(NarSil, 1.4.0, nckmccnnll@gmail.com)
AC_CONFIG_SRCDIR(src)
AC_CONFIG_MACRO_DIR([m4])

for i in configure.ac m4/*; do
	AS_IF([test $i -nt configure], [
		AC_MSG_ERROR([$i is newer than configure! Run ./autogen.sh!])
	])
done

BUILDSYS_INIT

AC_SUBST(PACKAGE, narsil)

AC_CONFIG_HEADERS(src/autoconf.h)


AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version number of package])

AC_ARG_WITH(setgid,
	[AS_HELP_STRING([--with-setgid=NAME], [install angband as group NAME])],
	[wsetgid=yes])
AC_ARG_WITH(private_dirs,
	[AS_HELP_STRING([--with-private-dirs], [use private scorefiles/savefiles])])
AC_ARG_WITH(no_install,
	[AS_HELP_STRING([--with-no-install], [don't install, just run in-place])])

if test "x$with_setgid" = "xyes"; then
	AC_MSG_ERROR([Please specify a group to install as.])
fi

if test "x$wsetgid" = "x" && test "x$with_no_install" = "x"; then
	with_private_dirs="yes"
fi

if test "x$wsetgid$with_private_dirs$with_no_install" != "xyes";  then

	echo "Please run ./configure with only one of:

--with-setgid=<groupname>
    This configures the game to store savefiles and scorefiles in a central
    location on the system, writeable only by the group \"groupname\".  If you
    want a traditional installation of Angband, where all users share a
    scorefile, then use this option, and set the groupname to your \"games\"
    group.  This option requires the game to have the \"setgid\" bit set on its
    permissions, and thus this option requires root when installing.

--with-private-dirs
    This configures the game to store savefiles and scorefiles for each user
    in that user's home directory.  The game requires no special privileges if
    you do this, and should be used for most installations of the game. This
    is the default, if you specify none of these three options.

--with-no-install
    This leaves the game to run from the directory into which it was extracted
    and compiled, touching nothing else on the system - make install is not
    run.
"
	AC_MSG_ERROR([Please specify an installation method.])
fi

if test "x$with_no_install" = "x"; then
	echo "Note: You have chosen to compile for installation, with data files
    in standard locations. For development, you may wish to consider using
    --with-no-install which will leave the game to run from the directory
    into which it was extracted and compiled.
"
fi

AC_ARG_WITH(sphinx,
	[AS_HELP_STRING([--with-sphinx], [build the documentation with sphinx-build])])
AC_PATH_PROGS([SPHINXBUILD],
	[sphinx-build sphinx-build3 sphinx-build2],
	[NOTFOUND],
	[$PATH$PATH_SEPARATOR/usr/share/sphinx/scripts/python3$PATH_SEPARATOR/usr/share/sphinx/scripts/python2])
AC_ARG_VAR([SPHINXBUILD], [full path to sphinx-build for building documentation; overrides auto-detected path])
AC_ARG_VAR([DOC_HTML_THEME], [the builtin Sphinx HTML theme to use or, if not set or empty, use the theme configured in docs/conf.py (currently the better theme)])
if test "x$with_sphinx" = "xyes"; then
    if test x"$SPHINXBUILD" = x || test x"$SPHINXBUILD" = xNOTFOUND ; then
        AC_MSG_ERROR([--with-sphinx specified but could not locate sphinx-build.  Set SPHINXBUILD to the full path to sphinx-build.])
    fi
else
    SPHINXBUILD=
fi

# Prefer cc to gcc (default behavior is the opposite) for better compatibility
# with OpenBSD and FreeBSD.
AC_PROG_CC([cc gcc clang])
AC_PROG_CPP
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_RANLIB
AC_CHECK_TOOL(RC, windres, no)
AC_PATH_PROG(AR, ar)
AC_PATH_PROG(RM, rm)
AC_PATH_PROG(MV, mv)
AC_PATH_PROG(CP, cp)

AC_HEADER_DIRENT
AC_CHECK_HEADERS([fcntl.h])
AC_HEADER_STDBOOL
AC_CHECK_FUNCS([mkdir setresgid setegid stat])

dnl needed because h-basic.h checks for this define for autoconf support.
CPPFLAGS="$CPPFLAGS -DHAVE_CONFIG_H"
CPPFLAGS="$CPPFLAGS -I." 

AC_ARG_ENABLE(release,
	[AS_HELP_STRING([--enable-release], [enable a release build])],
	[AS_CASE(${enableval},
		[yes], [release=yes],
		[no], [release=no],
		[AC_MSG_ERROR([bad value ${enableval} for --enable-release])])],
	[release=no])

if test x"$release" = xyes ; then
	dnl Currently only adding -DNDEBUG to CFLAGS.  Also leave something
	dnl in autoconf.h so reconfiguring with or without release build will
	dnl trigger rebuilds without running make clean.
	CFLAGS="$CFLAGS -DNDEBUG"
	AC_DEFINE(RELEASE_BUILD, 1, [Define to mark as a release build with extra optimizations.])
fi

if test "$GCC" = "yes"; then
	CFLAGS="$CFLAGS -W -Wall -Wextra -Wno-unused-parameter -pedantic"
	CFLAGS="$CFLAGS -Wstrict-prototypes -Wmissing-prototypes -Wwrite-strings"
	CFLAGS="$CFLAGS -Wnested-externs -Wshadow"
fi

MY_PROG_MAKE_SYSVINC
MY_PROG_MAKE_SINCLUDE

dnl Work around an autoconf bug.
if test "$prefix" = "NONE"; then
	prefix="${ac_default_prefix}"
fi
if test "$exec_prefix" = "NONE"; then
	exec_prefix="${prefix}"
fi

if test "x$with_private_dirs" != "x"; then
	AC_DEFINE(USE_PRIVATE_PATHS, 1, [Define to use private save and score paths.])
fi

# Only change bindir if it's the configure-supplied default, which handily doesn't expand exec_prefix
if test "x$bindir" = "x\${exec_prefix}/bin"; then
  bindir=${exec_prefix}/games
fi

if test "x$with_no_install" != "x"; then
	configpath="${PWD}/lib/"
elif test "x$enable_win" = xyes; then
	configpath=".\\\\lib\\\\"
else
	configpath="${sysconfdir}/${PACKAGE}/"
fi

if test "x$enable_win" != xyes; then
	case "/$configpath" in
		*/) MY_EXPAND_DIR(configdir, "$configpath")  ;;
		*)  MY_EXPAND_DIR(configdir, "$configpath/") ;;
	esac
else
	configdir="$configpath"
fi


if test "x$with_no_install" != "x"; then
	libpath="${PWD}/lib/"
	bindir=".."
elif test "x$enable_win" = xyes; then
	libpath=".\\\\lib\\\\"
else
	libpath="${datarootdir}/${PACKAGE}/"
fi

if test "x$enable_win" != xyes; then
	case "/$libpath" in
		*/) MY_EXPAND_DIR(libdatadir, "$libpath")  ;;
		*)  MY_EXPAND_DIR(libdatadir, "$libpath/") ;;
	esac
else
	libdatadir="$libpath"
fi

if test "x$with_no_install" != "x"; then
	docdir="${PWD}/doc/"
else
	# Only change docdir if it's the configure-supplied default, which handily doesn't expand prefix
	if test "x$docdir" = "x\${datarootdir}/doc/\${PACKAGE_TARNAME}"; then
		docdir=${datarootdir}/doc/${PACKAGE}
	fi
fi

case "/$docdir" in
 	*/) MY_EXPAND_DIR(docdatadir, "$docdir")  ;;
	*)  MY_EXPAND_DIR(docdatadir, "$docdir/") ;;
esac

if test "x$with_no_install" != "x"; then
	varpath="${PWD}/lib/"
elif test "x$enable_win" = xyes; then
	varpath=".\\\\lib\\\\"
else
	varpath="${localstatedir}/games/${PACKAGE}/"
fi

if test "x$enable_win" != xyes; then
	case "/$varpath" in
		*/) MY_EXPAND_DIR(vardatadir, "$varpath")  ;;
		*)  MY_EXPAND_DIR(vardatadir, "$varpath/") ;;
	esac
else
	vardatadir="$varpath"
fi

if test "x$with_private_dirs" != "x"; then
	varshareddatadir="${vardatadir}user/"
else
	varshareddatadir="${vardatadir}"
fi

AC_ARG_WITH(gamedata_in_lib,
	[AS_HELP_STRING([--with-gamedata-in-lib], [store the game data in the lib path.])])

GAMEDATA_IN_LIB="false"
if test "x$with_gamedata_in_lib" = "xyes"; then
	GAMEDATA_IN_LIB="true"
	AC_DEFINE(GAMEDATA_IN_LIB, 1, [Define to store the game data in the lib path.])
fi
AC_SUBST(GAMEDATA_IN_LIB)

AC_SUBST([configdir])
AC_SUBST([libdatadir])
AC_SUBST([vardatadir])
AC_SUBST([varshareddatadir])
AC_SUBST([docdatadir])

AC_DEFINE_UNQUOTED([DEFAULT_CONFIG_PATH], "${configdir}", [Path to the game's configuration data])
AC_DEFINE_UNQUOTED([DEFAULT_LIB_PATH], "${libdatadir}", [Path to the game's lib directory])
AC_DEFINE_UNQUOTED([DEFAULT_DATA_PATH], "${vardatadir}", [Path to the game's variable data])

NOINSTALL="$with_no_install"; AC_SUBST(NOINSTALL)
SETEGID="$with_setgid";      AC_SUBST(SETEGID)
if test "x$wsetgid" = "xyes"; then
	AC_DEFINE(SETGID, 1, [Define if running as a central install on a multiuser system that has setresgid or setegid support.])
fi

dnl Frontends
AC_ARG_ENABLE(curses,
	[AS_HELP_STRING([--enable-curses], [enable Curses frontend (default: enabled)])],
	[enable_curses=$enableval],
	[enable_curses=default])
AC_ARG_ENABLE(x11,
	[AS_HELP_STRING([--enable-x11], [enable X11 frontend (default: enabled)])],
	[enable_x11=$enableval],
	[enable_x11=default])
AC_ARG_ENABLE(sdl2,
	[AS_HELP_STRING([--enable-sdl2], [enable SDL2 frontend (default: disabled)])],
	[enable_sdl2=$enableval],
	[enable_sdl2=no])
AC_ARG_ENABLE(sdl,
	[AS_HELP_STRING([--enable-sdl], [enable SDL frontend (default: disabled)])],
	[enable_sdl=$enableval],
	[enable_sdl=no])
AC_ARG_ENABLE(win,
	[AS_HELP_STRING([--enable-win], [enable Windows frontend (default: disabled)])],
	[enable_win=$enableval],
	[enable_win=no])
AC_ARG_ENABLE(test,
	[AS_HELP_STRING([--enable-test], [enable test frontend (default: disabled)])],
	[enable_test=$enableval],
	[enable_test=no])
AC_ARG_ENABLE(stats,
	[AS_HELP_STRING([--enable-stats], [enable stats frontend (default: disabled)])],
	[enable_stats=$enableval],
	[enable_stats=no])
AC_ARG_ENABLE(spoil,
	[AS_HELP_STRING([--enable-spoil], [enable command-line spoiler generation (default: enabled)])],
	[enable_spoil=$enableval],
	[enable_spoil=default])

dnl Sound modules
AC_ARG_ENABLE(sdl2_mixer,
	[AS_HELP_STRING([--enable-sdl2-mixer], [enable SDL2 mixer sound support (default: disabled unless SDL2 enabled)])],
	[enable_sdl2_mixer=$enable_sdl2_mixer],
	[enable_sdl2_mixer=$enable_sdl2])
AC_ARG_ENABLE(sdl_mixer,
	[AS_HELP_STRING([--enable-sdl-mixer], [enable SDL mixer sound support (default: disabled unless SDL enabled)])],
	[enable_sdl_mixer=$enable_sdl_mixer],
	[enable_sdl_mixer=$enable_sdl])

MAINFILES="\$(BASEMAINFILES)"

dnl The libraries needed when linking the test cases start out the same
dnl as what is needed to link the game but, typically, do not need to pick
dnl up the extra dependencies needed by the front ends.
TEST_LIBS="${LIBS}"

dnl The Windows front end does not allow access to the others so disable them
dnl unless explicitly told to build them.
if test x"$enable_win" = xyes; then
	default_override=no
else
	default_override=yes
fi
if test x"$enable_curses" = xdefault; then
	enable_curses="$default_override"
fi
if test x"$enable_x11" = xdefault; then
	enable_x11="$default_override"
fi
if test x"$enable_spoil" = xdefault; then
	enable_spoil="$default_override"
fi

dnl curses checking
if test "$enable_curses" = "yes"; then
	AM_PATH_NCURSESW(with_curses=yes, with_curses=no)
	if test "$with_curses" = "yes"; then
		AC_DEFINE(USE_NCURSES, 1, [Define to 1 if NCurses is found.])
		AC_DEFINE(USE_GCU, 1, [Define to 1 if using the Curses frontend.])
		CPPFLAGS="${CPPFLAGS} ${NCURSES_CFLAGS}"
		LIBS="${LIBS} ${NCURSES_LIBS}"
		MAINFILES="${MAINFILES} \$(GCUMAINFILES)"
	else
		AC_CHECK_LIB([ncursesw], [initscr], [
			AC_DEFINE(USE_NCURSES, 1, [Define to 1 if NCurses is found.])
			AC_DEFINE(USE_GCU, 1, [Define to 1 if using the Curses frontend.])
			AC_DEFINE(_XOPEN_SOURCE_EXTENDED, 1, [Defined for systems that guard ncurses decls with _XOPEN_SOURCE_EXTENDED])
			with_curses=yes
			LIBS="${LIBS} -lncursesw"
			MAINFILES="${MAINFILES} \$(GCUMAINFILES)"
		])
		AC_SEARCH_LIBS([keypad], [tinfow tinfo])
	fi
fi

AC_CHECK_FUNCS([mvwaddnwstr use_default_colors can_change_color])

dnl X11 checking
with_x11=no
if test "$enable_x11" = "yes"; then
	AC_PATH_XTRA

	if test "x$have_x" = "xyes"; then
		AC_DEFINE(USE_X11, 1, [Define to 1 if using the X11 frontend and X11 libraries are found.])
		CPPFLAGS="$CPPFLAGS $X_CFLAGS"
		LIBS="${LIBS} ${X_PRE_LIBS} ${X_LIBS} -lX11 ${X_EXTRA_LIBS}"
		MAINFILES="${MAINFILES} \$(X11MAINFILES)"
		with_x11=yes
	fi
fi
ENABLEX11="$with_x11"; AC_SUBST(ENABLEX11)

with_sdl2=no
if test "$enable_sdl2" = "yes" || test "$enable_sdl2_mixer" = "yes"; then
	dnl SDL2 checking
	AM_PATH_SDL2(2.0.0,,)

	found_sdl2_mixer=no
	if test "$SDL2_CONFIG" != "no"; then
		hold_CPPFLAGS="${CPPFLAGS}"
		hold_LIBS="${LIBS}"
		CPPFLAGS="${CPPFLAGS} ${SDL2_CFLAGS}"
		LIBS="${LIBS} ${SDL2_LIBS}"
		if test "$enable_sdl2" = "yes"; then
			AC_CHECK_LIB(SDL2_image, IMG_LoadPNG_RW, with_sdl2=yes, with_sdl2=no)
			AC_CHECK_LIB(SDL2_ttf, TTF_Init, with_sdl2x=yes, with_sdl2=no)
			if test "$with_sdl2" = "yes"; then
				AC_DEFINE(USE_SDL2, 1, [Define to 1 if using the SDL2 interface and SDL2 is found.])
				LIBS="${LIBS} -lSDL2_image -lSDL2_ttf"
				MAINFILES="${MAINFILES} \$(SDL2MAINFILES)"
			fi
		fi
		if test "$enable_sdl2_mixer" = "yes"; then
			AC_CHECK_LIB(SDL2_mixer, Mix_OpenAudio, found_sdl2_mixer=yes, found_sdl2_mixer=no)
			if test "$found_sdl2_mixer" = "yes"; then
				AC_DEFINE(SOUND_SDL2, 1, [Define to 1 if using SDL2_mixer sound support and it's found.])
				AC_DEFINE(SOUND, 1, [Define to 1 if including sound support.])
				LIBS="${LIBS} -lSDL2_mixer"
				MAINFILES="${MAINFILES} \$(SNDSDLFILES)"
			fi
		fi
		if test "$with_sdl2" = "yes" || test "$found_sdl2_mixer" = "yes"; then
			if test "$enable_sdl" = "yes"; then
				AC_MSG_WARN([disabling SDL:  --enable-sdl2 or --enable-sdl2-mixer also set and SDL2 was found; can not mix SDL2 and SDL])
				enable_sdl=no
			fi
			if test "$enable_sdl_mixer" = "yes"; then
				AC_MSG_WARN([disabling SDL mixer:  --enable-sdl2 or --enable-sdl2-mixer also set and SDL2 was found; can not mix SDL2 and SDL])
				enable_sdl_mixer=no
			fi
		else
			dnl Not using SDL2 so restore flags.
			CPPFLAGS="${hold_CPPFLAGS}"
			LIBS="${hold_LIBS}"
		fi
	fi
fi
ENABLESDL2="$with_sdl2"; AC_SUBST(ENABLESDL2)
with_sdl=no
if test "$enable_sdl" = "yes" || test "$enable_sdl_mixer" = "yes"; then
	dnl SDL checking
	AM_PATH_SDL(1.2.10,,)

	found_sdl_mixer=no
	if test "$SDL_CONFIG" != "no"; then
		hold_CPPFLAGS="${CPPFLAGS}"
		hold_LIBS="${LIBS}"
		CPPFLAGS="${CPPFLAGS} ${SDL_CFLAGS}"
		LIBS="${LIBS} ${SDL_LIBS}"
		if test "$enable_sdl" = "yes"; then
			AC_CHECK_LIB(SDL_image, IMG_LoadPNG_RW, with_sdl=yes, with_sdl=no)
			AC_CHECK_LIB(SDL_ttf, TTF_Init, with_sdlx=yes, with_sdl=no)
			if test "$with_sdl" = "yes"; then
				AC_DEFINE(USE_SDL, 1, [Define to 1 if using the SDL interface and SDL is found.])
				LIBS="${LIBS} -lSDL_image -lSDL_ttf"
				MAINFILES="${MAINFILES} \$(SDLMAINFILES)"
			fi
		fi
		if test "$enable_sdl_mixer" = "yes"; then
			AC_CHECK_LIB(SDL_mixer, Mix_OpenAudio, found_sdl_mixer=yes, found_sdl_mixer=no)
			if test "$found_sdl_mixer" = "yes"; then
				AC_DEFINE(SOUND_SDL, 1, [Define to 1 if using SDL_mixer sound support and it's found.])
				AC_DEFINE(SOUND, 1, [Define to 1 if including sound support.])
				LIBS="${LIBS} -lSDL_mixer"
				MAINFILES="${MAINFILES} \$(SNDSDLFILES)"
			fi
		fi
		if test "$with_sdl" = "no" && test "$found_sdl_mixer" = "no"; then
			dnl Not using SDL so restore flags.
			CPPFLAGS="${hold_CPPFLAGS}"
			LIB="${hold_LIBS}"
		fi
	fi
fi
ENABLESDL="$with_sdl"; AC_SUBST(ENABLESDL)

dnl Test checking
if test "$enable_test" = "yes"; then
	AC_DEFINE(USE_TEST, 1, [Define to 1 to build the test frontend])
	MAINFILES="${MAINFILES} \$(TESTMAINFILES)"
fi

dnl Stats checking
LDFLAGS_SAVE="$LDFLAGS"
if test "$enable_stats" = "yes"; then
	# SQLite3 detection
	SQLITE3_OK=yes
	AC_CHECK_HEADER(sqlite3.h, [], [
		SQLITE3_OK=missing
		for sqlite3_path in $SEARCH_DIR_HEADERS; do
			if test "x$ac_cv_header_sqlite3_h" != xyes; then
				unset ac_cv_header_sqlite3_h
				AC_CHECK_HEADER($sqlite3_path/sqlite3.h,
					[
						SQLITE3_CFLAGS="-I$sqlite3_path"
						SQLITE3_OK=yes
					]
				)
			fi
		done
	])
	if test "x$SQLITE3_OK" = xyes; then
		AC_CHECK_LIB(sqlite3, sqlite3_open, [
			SQLITE3_LIBS="-lsqlite3"
		], [
			SQLITE3_OK=missing
			for sqlite3_path in $SEARCH_DIR_LIBS; do
				if test "x$ac_cv_lib_sqlite3_sqlite3_open" != xyes; then
					unset ac_cv_lib_sqlite3_sqlite3_open
					LDFLAGS="${LDFLAGS_SAVE} -L$sqlite3_path"
					AC_CHECK_LIB(sqlite3, sqlite3_open, [
						SQLITE3_LDFLAGS="-L$sqlite3_path"
						SQLITE3_LIBS="-lsqlite3"
						SQLITE3_OK=yes
					])
				fi
			done	
		])
	fi
	if test "x$SQLITE3_OK" = xyes; then
		AC_DEFINE(USE_STATS, 1, [Define to 1 to build the stats frontend])
		CPPFLAGS="${CPPFLAGS} ${SQLITE3_CFLAGS}"
		LDFLAGS="${LDFLAGS_SAVE} ${SQLITE3_LDFLAGS}"
		LIBS="${LIBS} ${SQLITE3_LIBS} -lm"
		MAINFILES="${MAINFILES} \$(STATSMAINFILES)"
		AC_SUBST(USE_STATS, 1)
	else
		AC_MSG_ERROR(Could not find sqlite3 library; disabling stats)
		enable_stats=no
		AC_DEFINE(USE_STATS, 0, [Define to 0 to omit the stats frontend])
		LDFLAGS="$LDFLAGS_SAVE"
		AC_SUBST(USE_STATS, 0)
	fi
fi

dnl Spoiler checking
if test "$enable_spoil" = "yes"; then
	AC_DEFINE(USE_SPOIL, 1, [Define to 1 to build the command-line spoiler generation])
	MAINFILES="${MAINFILES} \$(SPOILMAINFILES)"
fi

dnl Windows checking
if test "$enable_win" = "yes"; then
	if test x"$with_no_install" != x || test x"$with_setgid" != x ; then
		AC_MSG_ERROR([--enable-win is not compatible with --with-no-install or --with-setgid])
	fi
	AC_DEFINE(USE_WIN, 1, [Define to 1 if using the Windows interface.])
	AC_DEFINE(SOUND, 1, [Define to 1 if including sound support.])
	CPPFLAGS="${CPPFLAGS} -DWINDOWS -Iwin/include"
	CFLAGS="${CFLAGS} -static"
	LDFLAGS="${LDFLAGS} -Lwin/lib"
	LIBS="${LIBS} -mwindows -lwinmm -lzlib -llibpng -lmsimg32"
	TEST_LIBS="${TEST_LIBS} -mwindows"
dnl Note complete replacement of all main files
	MAINFILES="\$(WINMAINFILES)"
fi
# Set up for Windows-specific behavior in the Makefiles.
ENABLEWIN="$enable_win"; AC_SUBST(ENABLEWIN)

dnl Remember if we are cross compiling.  Currently used so "make tests" only
dnl compiles but does not run test cases when cross compiling.
if test x"$build_alias" = x"$host_alias" ; then
	CROSS_COMPILE=no
else
	CROSS_COMPILE=yes
fi
AC_SUBST(CROSS_COMPILE)

dnl If installing elsewhere or using the Windows front end, allow the test
dnl cases which use set_file_paths() to find the data files.  This relies on
dnl the setting for TEST_DEFAULT_PATH in src/tests/unit-test.h which uses a
dnl relative path and has the drawback that a test case will not work if it
dnl uses set_file_paths() and the working directory is not the top level
dnl directory of a distribution.  Also set TEST_WORKING_DIRECTORY so, that
dnl when run by src/tests/run-tests, the working directory will match that.
if test x"$with_no_install" = x || test x"$enable_win" = xyes ; then
	CFLAGS="${CFLAGS} -DTEST_OVERRIDE_PATHS"
	case "$srcdir" in
		.) TEST_WORKING_DIRECTORY="$PWD" ;;
		[\\/]* | ?:[\\/]* ) TEST_WORKING_DIRECTORY="$srcdir" ;;
		*) TEST_WORKING_DIRECTORY="$PWD/$srcdir" ;;
	esac
else
	TEST_WORKING_DIRECTORY=
fi
AC_SUBST(TEST_WORKING_DIRECTORY)

AC_SUBST(MAINFILES, ${MAINFILES})
AC_SUBST(TEST_LIBS, ${TEST_LIBS})
AC_CONFIG_FILES([mk/buildsys.mk mk/extra.mk])
AC_OUTPUT

if test "x$with_private_dirs" = "xyes"; then
	displayedvardatadir="(not used)"
else
	displayedvardatadir="$vardatadir"
fi

if test "x$with_no_install" = "xyes" || test "x$enable_win" = "xyes"; then
	displayedprefix="(not used)"
	displayedbindir="(not used)"
	displayeddocdir="(not used)"
else
	displayedprefix="${prefix}"
	displayedbindir="${bindir}"
	displayeddocdir="${docdatadir}"
fi

if test "x$enable_win" = "xyes"; then
	displayedconfigdir="./lib"
	displayedlibdatadir="./lib"
else
	displayedconfigdir="${configdir}"
	displayedlibdatadir="${libdatadir}"
fi

echo
echo "Configuration:"
echo
echo "  Install path:                           ${displayedprefix}"
echo "  binary path:                            ${displayedbindir}"
echo "  config path:                            ${displayedconfigdir}"
echo "  lib path:                               ${displayedlibdatadir}"
echo "  doc path:                               ${displayeddocdir}"
echo "  var path:                               ${displayedvardatadir}"
if test "x$with_gamedata_in_lib" = "xyes"; then
	echo "  gamedata path:                          ${displayedlibdatadir}"
else
	echo "  gamedata path:                          ${displayedconfigdir}"
fi
if test "x$wsetgid" = "xyes"; then
	echo "  (as group ${SETEGID})"
elif test "x$with_private_dirs" = "xyes" && test ! "x$enable_win" = "xyes"; then
	echo "  (with private save and score files in ~/.angband/Angband/)"
fi
if test "x$with_sphinx" = "xyes"; then
	echo "  documentation:                          Yes"
else
	echo "  documentation:                          No"
fi

echo
echo "-- Frontends --"
local_player_frontends=""
if test "$enable_curses" = "yes"; then
	if test "$with_curses" = "no"; then
		echo "- Curses                                  No; missing libraries"
	else
		echo "- Curses                                  Yes"
		local_player_frontends="$local_player_frontends"+
	fi
else
	echo "- Curses                                  Disabled"
fi
if test "$enable_x11" = "yes"; then
	if test "$with_x11" = "no"; then
		echo "- X11                                     No; missing libraries"
	else
		echo "- X11                                     Yes"
		local_player_frontends="$local_player_frontends"+
	fi
else
	echo "- X11                                     Disabled"
fi
if test "$enable_sdl2" = "yes"; then
	if test "$with_sdl2" = "no"; then
		echo "- SDL2                                    No; missing libraries"
	else
		echo "- SDL2                                    Yes"
		local_player_frontends="$local_player_frontends"+
	fi
else
	echo "- SDL2                                    Disabled"
fi
if test "$enable_sdl" = "yes"; then
	if test "$with_sdl" = "no"; then
		echo "- SDL                                     No; missing libraries"
	else
		echo "- SDL                                     Yes"
		local_player_frontends="$local_player_frontends"+
	fi
else
	echo "- SDL                                     Disabled"
fi

if test "$enable_win" = "yes"; then
	echo "- Windows                                 Yes"
	local_player_frontends="$local_player_frontends"+
else
	echo "- Windows                                 Disabled"
fi

if test "$enable_test" = "yes"; then
	echo "- Test                                    Yes"
else
    echo "- Test                                    No"
fi

if test "$enable_stats" = "yes"; then
	echo "- Stats                                   Yes"
else
    echo "- Stats                                   No"
fi

if test "$enable_spoil" = "yes"; then
	echo "- Spoilers                                Yes"
else
    echo "- Spoilers                                No"
fi

echo

if test "$enable_sdl2_mixer" = "yes"; then
	if test "$found_sdl2_mixer" = "no"; then
		echo "- SDL2 sound                              No; missing libraries"
	else
		echo "- SDL2 sound                              Yes"
	fi
else
	echo "- SDL2 sound                              Disabled"
fi
if test "$enable_sdl_mixer" = "yes"; then
	if test "$found_sdl_mixer" = "no"; then
		echo "- SDL sound                               No; missing libraries"
	else
		echo "- SDL sound                               Yes"
	fi
else
	echo "- SDL sound                               Disabled"
fi

if test x"$local_player_frontends" = "x" ; then
	AC_MSG_WARN([No player frontends are enabled.  Check your --enable options and prerequisites for the frontends.])
fi
