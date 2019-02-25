SUBDIRS := hacklib plugins tools demoapp

ADDON_DIR := $(HOME)/config/add-ons/skinobe

default .DEFAULT:
	-@for f in $(SUBDIRS) ; do \
		$(MAKE) -C $$f $@ ; \
	done

inst:
	-mkdir $(ADDON_DIR)
	-ln -s "`pwd`/plugins/gem/obj.x86/gem" $(ADDON_DIR)
	-ln -s "`pwd`/plugins/gonx/obj.x86/gonx" $(ADDON_DIR)
	-ln -s "`pwd`/plugins/qnx/obj.x86/qnx" $(ADDON_DIR)
	-ln -s "`pwd`/plugins/osx/obj.x86/osx" $(ADDON_DIR)
	-ln -s "`pwd`/plugins/sequel/obj.x86/sequel" $(ADDON_DIR)
