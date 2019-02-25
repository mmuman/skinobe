#include <stdio.h>
#include <Application.h>
#include <Box.h>
#include <Button.h>
#include <CheckBox.h>
#include <Menu.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <RadioButton.h>
#include <View.h>
#include <Window.h>
#include <ScrollBar.h>

class MyWindow : public BWindow {
	public:
	MyWindow(BRect frame, const char *name);
	~MyWindow();
	virtual void MessageReceived(BMessage *msg);
};

static BMenuItem *enabledItem;
static BView *view;
static BBox *box1;
static BBox *box2;
static BBox *box3;
static BBox *box4;
static BRadioButton *radio1;
static BRadioButton *radio2;
static BRadioButton *radio3;
static BCheckBox *cb1;
static BCheckBox *cb2;
static BCheckBox *cb3;
static BButton *b1;
static BButton *b2;

MyWindow::MyWindow(BRect frame, const char *name)
	: BWindow(frame, name, B_TITLED_WINDOW, B_QUIT_ON_WINDOW_CLOSE)
{
}

MyWindow::~MyWindow()
{
}

void MyWindow::MessageReceived(BMessage *msg)
{
	bool en;
	switch (msg->what) {
	case 'Enab':
		en = !radio1->IsEnabled();
		radio1->SetEnabled(en);
		radio2->SetEnabled(en);
		radio3->SetEnabled(en);
		cb1->SetEnabled(en);
		cb2->SetEnabled(en);
		cb2->SetValue(en);
		b1->SetEnabled(en);
		b2->SetEnabled(en);
		enabledItem->SetMarked(en);
		break;
	default:
		BWindow::MessageReceived(msg);
	}
}

int main(int argc, char **argv)
{
	BRect frame(0,0,640-1,480-1);
	new BApplication("application/x-vnd.mmu_man-SkinobeDemoApp");
	BWindow *win;
	win = new MyWindow(frame.OffsetByCopy(50,50), "DemoApp");
	
	// Menu stuff
	BMenuItem *item;
	BMenuBar *bar = new BMenuBar(BRect(0,0,640-1,10), "menubar");
	BMenu *menuFile = new BMenu("File");
	item = new BMenuItem("About...", new BMessage(B_ABOUT_REQUESTED), 'A');
	item->SetTarget(be_app);
	menuFile->AddItem(item);
	menuFile->AddItem(new BSeparatorItem);
	menuFile->AddItem(new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED), 'Q'));
	bar->AddItem(new BMenuItem(menuFile));
	enabledItem = new BMenuItem("Enabled", new BMessage('Enab'), 'E');
	BMenu *menuControl = new BMenu("Controls");
	item = new BMenuItem("Foo", new BMessage('Foo '));
	item->SetEnabled(false);
	menuControl->AddItem(enabledItem);
	menuControl->AddItem(new BSeparatorItem);
	menuControl->AddItem(item);
	bar->AddItem(new BMenuItem(menuControl));
	enabledItem->SetMarked(true);
	win->AddChild(bar);
	//win->SetKeyMenuBar(bar);
	//bar->ResizeToPreferred();
	frame.top += bar->Bounds().Height() + 1;
	
	// Background view
	view = new BView(frame, "bgview", B_FOLLOW_ALL, 0);//B_WILL_DRAW);
	//view = new BBox(frame, "bgview", B_FOLLOW_ALL, B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE_JUMP, B_NO_BORDER);
	view->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	win->AddChild(view);

	// some controls
	box1 = new BBox(BRect(10,10,390,390), "box1");//, B_FOLLOW_LEFT | B_FOLLOW_TOP, B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE_JUMP, B_PLAIN_BORDER);
	box1->SetLabel("Some controls");
	view->AddChild(box1);
	box2 = new BBox(BRect(200,20,270,20+30), "box2");
	box2->SetBorder(B_NO_BORDER);
	box2->SetLabel("No");
	box1->AddChild(box2);
	box3 = new BBox(BRect(200,20+40,270,20+40+30), "box3");
	box3->SetBorder(B_PLAIN_BORDER);
	box3->SetLabel("Plain");
	box1->AddChild(box3);
	box4 = new BBox(BRect(200,20+80,270,20+80+30), "box4");
	box4->SetLabel("Fancy");
	box1->AddChild(box4);

	radio1 = new BRadioButton(BRect(10,20,80,20+20-1), "r1", "Machin", new BMessage('Foo '));
	radio2 = new BRadioButton(BRect(10,20+20,80,20+20+20-1), "r2", "Truc", new BMessage('Foo '));
	radio3 = new BRadioButton(BRect(10,20+40,80,20+40+20-1), "r3", "Bidule", new BMessage('Foo '));
	box1->AddChild(radio1);
	box1->AddChild(radio2);
	box1->AddChild(radio3);

	cb1 = new BCheckBox(BRect(10,20+60,90,40+60-1), "cb1", "Windows sux", new BMessage('WSux'));
	cb2 = new BCheckBox(BRect(10,20+80,80,40+80-1), "cb2", "Enabled", new BMessage('Enab'));
	cb2->SetValue(B_CONTROL_ON);
	box1->AddChild(cb1);
	box1->AddChild(cb2);

	b1 = new BButton(BRect(10,20+100,90,40+100-1), "b1", "Yes", new BMessage('Yes'));
	b2 = new BButton(BRect(10,20+130,90,40+130-1), "b2", "No", new BMessage('No'));
	b2->MakeDefault(true);
	box1->AddChild(b1);
	box1->AddChild(b2);

	BScrollBar *sb = new BScrollBar(BRect(450,50,450+14*2,50+14*2), "sb", NULL, 0, 500, B_VERTICAL);
	
	//BRect(450,50,460,200)
	view->AddChild(sb);
	sb->ResizeTo(14, 150);
	printf("B_H_SCROLL_BAR_HEIGHT = %f\n", B_H_SCROLL_BAR_HEIGHT);
	printf("B_V_SCROLL_BAR_WIDTH = %f\n", B_V_SCROLL_BAR_WIDTH);
	
	win->Show();
	be_app->Run();
	return 0;
}
