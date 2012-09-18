# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

if BUILD_DOCS
DOC_TARGETS =
endif

if BUILD_REFS
REFDOC_TARGETS = html/index.html
endif

all all-local: $(DOC_TARGETS) $(REFDOC_TARGETS)

docdir = $(datadir)/doc/xmalloc-$(VERSION)
doc_DATA = $(DOC_TARGETS) caution.png note.png docbook.css

refdocdir = $(datadir)/doc/xmalloc-$(VERSION)/reference
refdoc_DATA = $(REFDOC_TARGETS)

doc: $(srcdir)/config.xsl $(srcdir)/index.xml
	$(XMLTO) xhtml -m $(srcdir)/config.xsl $(srcdir)/index.xml
#sed -e s/index.html/index.html/g index.html >index.html

html/index.html:
	$(DOXYGEN)

install-data-local:
	mkdir -p $(DESTDIR)$(refdocdir)
	if test -x $(builddir)/html ; then \
		cp -R $(builddir)/html/* $(DESTDIR)$(refdocdir); \
	else \
		cp -R $(srcdir)/html/* $(DESTDIR)$(refdocdir); \
	fi
	mkdir -p $(distdir)/html
	if test -x $(builddir)/html; then \
		cp -R $(builddir)/html/* $(distdir)/html; \
	else \
		cp -R $(srcdir)/html/* $(distdir)/html; \
	fi

uninstall-hook:
	rm -rf $(DESTDIR)$(refdocdir)

#clean-local:
#	rm -rf $(builddir)/html $(builddir)/latex

maintainer-clean-local:
	rm -rf $(builddir)/html $(builddir)/latex

#dist-hook:

EXTRA_DIST = \
	index.xml	\
	caution.png	\
	note.png	\
	config.xsl	\
	docbook.css

CLEANFILES = \
	index.html*

DISTCLEANFILES = \
	index.html*

MAINTAINERCLEANFILES = \
	index.html*
