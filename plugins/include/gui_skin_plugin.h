#ifndef _GUI_SKIN_PLUGIN_H
#define _GUI_SKIN_PLUGIN_H

#include <SupportDefs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_HOOKS 16

class BView;
class BButton;
class BCheckBox;
class BRadioButton;
class BMenuBar;
class BMenu;
class BRect;


/* functions plugin is expected to implement */
void BView__Draw(BView *_this, BRect updateRect);
void BButton__Draw(BButton *_this, BRect updateRect);
void BCheckBox__Draw(BCheckBox *_this, BRect updateRect);
void BRadioButton__Draw(BRadioButton *_this, BRect updateRect);
void BMenuBar__Draw(BMenuBar *_this, BRect updateRect);
void BMenu__DrawBackground(BMenu *_this, BRect updateRect);
void BBox__Draw(BMenu *_this, BRect updateRect);



/* this is to avoid mistakely putting a function at the wrong place in the list... */
/* plugins should fill a struct of this type and return it */
typedef struct gui_hooklist_t {
	uint32 numhooks;
	uint32 reserved;
	union {
		void *hooks[MAX_HOOKS];
		struct {
			void (*BView__Draw)(BView *, BRect);
			void (*BButton__Draw)(BButton *, BRect);
			void (*BCheckBox__Draw)(BCheckBox *, BRect);
			void (*BRadioButton__Draw)(BRadioButton *, BRect);
			void (*BMenuBar__Draw)(BMenuBar *, BRect);
			void (*BMenu__DrawBackground)(BMenu *, BRect);
			void (*BBox_Draw)(BMenu, BRect);
		} funcs;
	} u;
} gui_hooklist_t;

/**
 * \param trampolines pointer to the trampolines, in case a method wants to call its original
 */
extern gui_hooklist_t *gui_skin_plugin_init(uint32 version, status_t *err, void *trampolines);

extern const char gui_skin_plugin_description[]; // export this string to describe your plugin


#ifdef __cplusplus
}
#endif

#endif /* _GUI_SKIN_PLUGIN_H */
