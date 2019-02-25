//TRAMPOLINE_1(0, Draw__5BViewG5BRect, void, BView, BRect )
TRAMPOLINE_PRIV(0, Run__12BApplication, thread_id, BApplication, void )
//#if 0
TRAMPOLINE_1(1, Draw__5BViewG5BRect, void, BView, BRect/* updateRect*/ )
TRAMPOLINE_1(2, Draw__7BButtonG5BRect, void, BButton, BRect/* updateRect*/ )
TRAMPOLINE_1(3, Draw__9BCheckBoxG5BRect, void, BCheckBox, BRect/* updateRect*/ )
TRAMPOLINE_1(4, Draw__12BRadioButtonG5BRect, void, BRadioButton, BRect/* updateRect*/ )
TRAMPOLINE_1(5, Draw__8BMenuBarG5BRect, void, BMenuBar, BRect )
TRAMPOLINE_1(6, DrawBackground__5BMenuG5BRect, void, BMenu, BRect )
TRAMPOLINE_1(7, Draw__4BBoxG5BRect, void, BBox, BRect )
//#endif
#ifdef WRAP_UI_COLOR
TRAMPOLINE_2(10, ui_color__F11color_which, struct rgb_color, enum color_which which)
#endif

