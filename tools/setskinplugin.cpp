#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <Application.h>
#include <Directory.h>
#include <Roster.h>
#include <Screen.h>
#include <View.h>
#include <Window.h>
#define _ZETA_TS_FIND_DIR_ // what a crappy fix
#include <FindDirectory.h>

int usage(int argc, char **argv)
{
	fprintf(stderr, "usage: %s [-d|-l|<skinpluginname>]\n", argv[0]);
	fprintf(stderr, "\t-l: list skin plugins\n");
	fprintf(stderr, "\t-d: use default look\n");
	return 1;
}

int main(int argc, char **argv)
{
	bool usedefaultlook = false;
	int settings_fd;
        char pathbuf[B_PATH_NAME_LENGTH];

	if (argc < 2)
		return usage(argc, argv);
	if (!strcmp(argv[1], "-l")) {
		find_directory(B_USER_ADDONS_DIRECTORY, 0L, false, pathbuf, B_PATH_NAME_LENGTH);
		strcat(pathbuf, "/skinobe");
		BDirectory dir(pathbuf);
		BEntry e;
		strcpy(pathbuf, "skinobe/");
		while (dir.GetNextEntry(&e) == B_OK)
			if (e.GetName(pathbuf+8) == B_OK) {
				image_id iid;
				iid = load_add_on(pathbuf);
				const char *description = NULL;
				get_image_symbol(iid, "gui_skin_plugin_description", B_SYMBOL_TYPE_DATA, (void **)&description);
				printf("%s (%s)\n", pathbuf+8, description?description:"no description");
				unload_add_on(iid);
			}
		return 0;
	}
	if (!strcmp(argv[1], "-d"))
		usedefaultlook = true;

	BApplication app("application/x-vnd.mmu_man.setskinplugin");

	// write the setting file first
        find_directory(B_USER_SETTINGS_DIRECTORY, 0L, false, pathbuf, B_PATH_NAME_LENGTH);
        strcat(pathbuf, "/x-vnd.mmu_man.skinobe");
        fprintf(stderr, "user settings file: %s\n", pathbuf);
        settings_fd = open(pathbuf, O_WRONLY|O_CREAT|O_TRUNC, 0644);
        if (settings_fd >= B_OK) {
		if (!usedefaultlook)
	                write(settings_fd, argv[1], strlen(argv[1]));
		//write(settings_fd, "\0", 1); // terminate the string
                close(settings_fd);
        } else
		perror("can't open the settings file");

	// tell loaded apps about the change
	BMessage *msg = new BMessage('SKIN');
	if (!usedefaultlook)
		msg->AddString("skinpluginname", argv[1]);
	be_roster->Broadcast(msg);

	// force a redraw (ugly)
	BScreen bs;
	BWindow *win = new BWindow(bs.Frame(), "force redraw", B_BORDERED_WINDOW, B_NOT_MOVABLE|B_NOT_CLOSABLE|B_NOT_RESIZABLE);
	BView *tview = new BView(win->Bounds(), "transparent view", B_FOLLOW_NONE, B_WILL_DRAW);
	tview->SetViewColor(B_TRANSPARENT_32_BIT);
	win->AddChild(tview);
	win->Show();
	snooze(100000);
	win->Hide();
	win->Lock();
	win->Quit();
	//delete win; // B_DONT_DO_THAT !!! Quit() does it.
	return 0;
}
