# $NetBSD: Makefile.inc,v 1.34 2020/03/02 16:01:52 roy Exp $
#
# Include this fragment to build libhack.o
# It is .o and not .a to make sure these are the
# objects you get (and not the ones in libc.a)
#

#
# Required variables:
#	HACKSRC		This directory
#
# Optional variables:
#	HACKOBJS	Extra objects to build.
#			The following extra objects are available:
#			gethost.o	cut-down gethostby{name,addr}()
#					that only supports /etc/hosts
#			

.include <bsd.own.mk>

CPPFLAGS+=	-DSMALL
CPPFLAGS+=	-DLIBHACK

HACKOBJS+=	getcap.o getgrent.o getnet.o getnetgr.o getpwent.o jemalloc.o \
		localeconv.o multibyte.o perror.o runetable.o setlocale.o \
		nl_langinfo.o strcasecmp.o \
		strerror.o strsignal.o syslog.o utmp.o fmtcheck.o

.if (${USE_YP} != "no")
HACKOBJS+=	yplib.o
.endif

.if ${HACK_CURSES:Uno} == "yes"
CURSES_SRC!=	cd ${HACKSRC}/../../../lib/libcurses && \
		${MAKE} DISABLE_WCHAR=yes -v SRCS

.for s in ${CURSES_SRC}
CPPFLAGS.${s}+=	-DDISABLE_WCHAR -DSMALL \
		-I${HACKSRC}/../../../lib/libcurses \
		-I${HACKSRC}/../../../lib/libterminfo
HACKOBJS+=	${s:S/.c/.o/}
${s:S/.c/.o/}:	${HACKSRC}/../../../lib/libcurses/${s}
.endfor
.endif

CPPFLAGS.runetable.c+= -I${HACKSRC}/../../../lib/libc/citrus \
			-DALL_80_TO_FF_SW1

CPPFLAGS.syslog.c+= -I${HACKSRC}/../../../lib/libc/include
CPPFLAGS.jemalloc.c+= -I${HACKSRC}/../../../lib/libc/include
CPPFLAGS.gethost.c+= -I${HACKSRC}/../../../lib/libc/net

.if !defined(LIB)
libhack.o: ${HACKOBJS}
	${LD} -r -o $@ ${.ALLSRC}
.endif

.if 1
.PATH.c: \
	${HACKSRC} \
	${HACKSRC}/../../../lib/libc/gen \
	${HACKSRC}/../../../lib/libc/locale \
	${HACKSRC}/../../../lib/libc/stdlib
.else
# XXX .PATH won't work here, because of crunchgen used by various builds
getcap.o:	${HACKSRC}/../../../lib/libc/gen/getcap.c
getgrent.o:	${HACKSRC}/getgrent.c
gethost.o:	${HACKSRC}/gethost.c
getnet.o:	${HACKSRC}/getnet.c
getnetgr.o:	${HACKSRC}/getnetgr.c
getpwent.o:	${HACKSRC}/getpwent.c
localeconv.o:	${HACKSRC}/localeconv.c
multibyte.o:	${HACKSRC}/multibyte.c
perror.o:	${HACKSRC}/perror.c
jemalloc.o:	${HACKSRC}/../../../lib/libc/stdlib/jemalloc.c
runetable.o:	${HACKSRC}/../../../lib/libc/locale/runetable.c
setlocale.o:	${HACKSRC}/setlocale.c
strerror.o:	${HACKSRC}/strerror.c
strsignal.o:	${HACKSRC}/strsignal.c
syslog.o:	${HACKSRC}/syslog.c
utmp.o:		${HACKSRC}/utmp.c
.if (${USE_YP} != "no")
yplib.o:	${HACKSRC}/yplib.c
.endif
.endif
