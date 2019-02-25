Skin-o-Be
(c) 2003, mmu_man, revol@free.fr

This is a tech demo of a way to add skinning capability to BeOS.

How it's done:

It requires binary patching libbe.so to hook in a replacement libtextencoding.so that forwards text encoding calls to the real library, and munges the prologue of Draw() methods of GUI classes in libbe, to hook them to allow for plugins to draw the objects for them.

This way one can adapt the look of GUI apps on the fly.

Testing:

There is a tests/ folder that contains several apps that were patched to use a libBe.so, which is one of the patched libbe.so in tests/lib/ (the name is changed to fool the elf loader, normal use doesn't require patching apps). 

* Make sure you copy the correct libBe.so_foo for you to libBe.so in tests/lib/.
* Rebuild everything for your version of BeOS. R5 and Dano/Zeta need different binaries. In a terminal go to the base folder (cd /where/you/unzipped/libbehack) and type:
make clean
make
make inst

This will make sure there are no left binaries, build them, and install symlinks pointing to the plugins for the library to find to load.

* Run some apps in tests/, the demoapp shows most skinable controls.

* In the Terminal, get the list of available plugins:
./setskinp -l

* Then try the one you want, for ex for the QNX look:
./setskinp qnx

* You can revert to the default (internal) look by:
./setskinp -d

Installing:

*WARNING* This can render your system unbootable

Make sure you have another installation you can boot to recover.
While it used to work long ago, there is no garantee it will work on your version of BeOS.
It will actually *NOT* work in Zeta as libbe.so doesn't link anymore to libtextencoding.so there. It should be possible to use ld with a special ldscript to add the dependancy but I didn't look at it.
Also, since this patches the opcodes of method prologues and uses C++ mangled symbols it might not work with a recent gcc build, nor Haiku likely (and certainly not gcc4 built Haiku).
Also, because libbe changed several times through BeOS revisions it is necessary that you binary patch your own libbe, and not take one of the libBe.so in tests/lib/.

* Make a build:
make clean
make
make inst

* Copy the hack library:
cp hacklib/obj.x86/lib_te_gui_hack.so /system/lib

* Make a copy of /system/lib/libbe.so just in case.
cp /system/lib/libbe.so /system/lib/libbe.so.original

* Hexedit your libbe.so (with DiskProbe) and replace the string:
libtextencoding.so
by
lib_te_gui_hack.so

On reboot you should then be able to use the setskinp command to change the look.
A definitive installation should replace the symlinks for the plugins by a copy of the binaries and setskinp should be copied to /bin.

Happy hacking.