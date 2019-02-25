SUBDIRS := gem gonx qnx osx sequel

default .DEFAULT:
	-@for f in $(SUBDIRS) ; do \
		$(MAKE) -C $$f $@ ; \
	done

