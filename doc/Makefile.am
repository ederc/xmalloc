# Copyright 2012 Christian Eder
# 
# This file is part of XMALLOC, licensed under the GNU General Public
# License version 3. See COPYING for more information.

if BUILD_DOCS
DOC_TARGETS = doc
REFDOC_TARGETS = html/index.html
endif

if BUILD_REFS

endif

all all-local: $(DOC_TARGETS) $(REFDOC_TARGETS)

docdir = $(datadir)/doc/xmalloc-$(VERSION)
doc_DATA = $(DOC_TARGETS) caution.png note.png docbook.css

refdocdir = $(datadir)/doc/xmalloc-$(VERSION)/reference
refdoc_DATA = $(REFDOC_TARGETS)

doc: $(srcdir)/config.xsl $(srcdir)/tutorial.xml
	$(XMLTO) xhtml -m $(srcdir)/config.xsl $(srcdir)/tutorial.xml
	sed -e s/index.html/tutorial.html/g index.html >tutorial.html
	rm -f index.html

html/index.html:
	$(DOXYGEN)

install-data-local:
	mkdir -p $(DESTDIR)$(refdocdir)
	if test -x $(builddir)/html; then \
		$(install_sh) $(builddir)/html/* $(DESTDIR)$(refdocdir); \
	else \
		$(install_sh) $(srcdir)/html/* $(DESTDIR)$(refdocdir); \
	fi

uninstall-hook:
	rm -rf $(DESTDIR)$(refdocdir)

maintainer-clean-local:
	rm -rf $(builddir)/html

dist-hook:
	mkdir -p $(distdir)/html
	if test -x $(builddir)/html; then \
		cp $(builddir)/html/* $(distdir)/html; \
	else \
		cp $(srcdir)/html/* $(distdir)/html; \
	fi

EXTRA_DIST = \
	tutorial.xml	\
	tutorial.html	\
	caution.png	\
	note.png	\
	config.xsl	\
	docbook.css

MAINTAINERCLEANFILES = \
	tutorial.html
