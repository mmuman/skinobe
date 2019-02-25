#include <stdio.h>
#include <OS.h>
#include <Application.h>
#include <Message.h>
#include <MessageFilter.h>
#include <InterfaceDefs.h>
#include <Window.h>

extern class BApplication *be_app;

#ifdef __cplusplus
extern "C" {
#endif

extern int32 BApp_created;

extern status_t load_guiskin_plugin(const char *name);

BMessageFilter *mFilter = NULL;

filter_result msg_filter_hook(BMessage *message, BHandler **target, BMessageFilter *messageFilter)
{
	const BWindow *aWin;
//	int32 currWs;
	const char *name = NULL;
//	message->PrintToStream();
	switch (message->what) {
	case 'SKIN':
		message->FindString("skinpluginname", &name);
		load_guiskin_plugin(name);
#if 0
		currWs = current_workspace();
		for (int i = 0; (aWin = be_app->WindowAt(i)); i++) {
/*			status_t err;
			BMessenger msgr((BHandler *)NULL, (BLooper *)aWin, &err);
			//BMessage *msg = new BMessage(_UPDATE_);
			BMessage *msg = new BMessage(B_WORKSPACE_ACTIVATED);
			msg->AddInt64("when", system_time());
			msg->AddInt32("workspace", currWs);
			msg->AddBool("active", true);
			msgr.SendMessage(msg);
*/
			aWin->Invalidate(aWin->Bounds());
		}
#endif
		break;
	}
	return B_DISPATCH_MESSAGE;
}

void _init_app_msg_filter(void)
{
//	fprintf(stderr, "libhack:_init_app_msg_filter()\n");
	mFilter = new BMessageFilter(B_ANY_DELIVERY, B_ANY_SOURCE, msg_filter_hook);
	be_app->Lock();
	be_app->AddCommonFilter(mFilter);
	be_app->Unlock();
}


void _fini_app_msg_filter(void)
{
	fprintf(stderr, "libhack:terminate_before()\n");
}





#ifdef __cplusplus
}
#endif

