MKPATH=../../mk/
include $(MKPATH)buildsys.mk

DATA = luthien-16.png luthien-32.png luthien-128.png luthien-256.png \
 luthien-512.png
PACKAGE = icons


# If this isn't a --with-no-install build and at least one of the SDL, SDL2,
# or X11 front ends has been configured, install the desktop and icon files
# into the paths expected by https://freedesktop.org/software/appstream/docs/chap-Metadata.html#spec-component-location
# (see also https://github.com/angband/angband/pull/5302 ).
install-extra:
	@if test x"${NOINSTALL}" != xyes ; then \
		if test x"${ENABLESDL2}" = xyes ; then \
			desktop_file=narsil-sdl2.desktop ; \
                elif test x"${ENABLESDL}" = xyes ; then \
			desktop_file=narsil-sdl.desktop ; \
		elif test x"${ENABLEX11}" = xyes ; then \
			desktop_file=narsil-x11.desktop ; \
		else \
			desktop_file=none ; \
		fi ; \
		if test x"$$desktop_file" != xnone ; then \
			i=narsil.metainfo.xml ; \
			i_d="${DESTDIR}${datadir}/metainfo/$$i" ; \
			${INSTALL_STATUS}; \
			if ${MKDIR_P} "$$(dirname $$i_d)" && ${INSTALL} -m 644 "$$i" "$$i_d" ; then \
				${INSTALL_OK}; \
			else \
				${INSTALL_FAILED}; \
			fi ; \
			i="$$desktop_file" ; \
			i_d="${DESTDIR}${datadir}/applications/narsil.desktop" ; \
			${INSTALL_STATUS}; \
			if ${MKDIR_P} "$$(dirname $$i_d)" && ${INSTALL} -m 644 "$$i" "$$i_d" ; then \
				${INSTALL_OK}; \
			else \
				${INSTALL_FAILED}; \
			fi ; \
			for res in 16 32 128 256 512 ; do \
				i=luthien-"$$res".png ; \
				i_d="${DESTDIR}${datadir}"/icons/hicolor/"$$res"x"$$res"/apps/narsil.png ; \
				${INSTALL_STATUS}; \
				if ${MKDIR_P} "$$(dirname $$i_d)" && ${INSTALL} -m 644 "$$i" "$$i_d" ; then \
					${INSTALL_OK}; \
				else \
					${INSTALL_FAILED}; \
				fi \
			done ; \
		fi ; \
	fi
