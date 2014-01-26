#include <gtk/gtk.h>

#include <Scintilla.h>
#include <SciLexer.h>
#define PLAT_GTK 1
#include <ScintillaWidget.h>

//void *__gxx_personality_v0;

static int exit_app(GtkWidget*w, GdkEventAny*e, gpointer p) {
   //gtk_main_quit();
   return w||e||p||1;	// Avoid warnings
}
 
static void
print_hello(GtkWidget *widget,
gpointer   data)
{
	g_print("Hello World\n");
}

static gboolean
on_delete_event(GtkWidget *widget,
GdkEvent  *event,
gpointer   data)
{
	/* If you return FALSE in the "delete_event" signal handler,
	* GTK will emit the "destroy" signal. Returning TRUE means
	* you don't want the window to be destroyed.
	*
	* This is useful for popping up 'are you sure you want to quit?'
	* type dialogs.
	*/

	g_print("delete event occurred\n");

	return TRUE;
}

/*
int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *button;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Hello");
	g_signal_connect(window, "delete-event", G_CALLBACK(on_delete_event), NULL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER(window), button);
	gtk_widget_show(button);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
*/

int main(int argc, char **argv) {
   GtkWidget *app;
   GtkWidget *editor;
   ScintillaObject *sci;

   gtk_init(&argc, &argv);
   app = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   editor = scintilla_new();
   sci = SCINTILLA(editor);

   GType at = scintilla_get_type();
   gtk_container_add(GTK_CONTAINER(app), editor);

   //gtk_signal_connect(GTK_OBJECT(app), "delete_event", GTK_SIGNAL_FUNC(exit_app), 0);

   scintilla_set_id(sci, 0);
   //gtk_widget_set_usize(editor, 500, 300);

   #define SSM(m, w, l) scintilla_send_message(sci, m, w, l)

   SSM(SCI_STYLECLEARALL, 0, 0);
   SSM(SCI_SETLEXER, SCLEX_CPP, 0);
   SSM(SCI_SETKEYWORDS, 0, (sptr_t)"int char");
   SSM(SCI_STYLESETFORE, SCE_C_COMMENT, 0x008000);
   SSM(SCI_STYLESETFORE, SCE_C_COMMENTLINE, 0x008000);
   SSM(SCI_STYLESETFORE, SCE_C_NUMBER, 0x808000);
   SSM(SCI_STYLESETFORE, SCE_C_WORD, 0x800000);
   SSM(SCI_STYLESETFORE, SCE_C_STRING, 0x800080);
   SSM(SCI_STYLESETBOLD, SCE_C_OPERATOR, 1);
   SSM(SCI_INSERTTEXT, 0, (sptr_t)
    "int main(int argc, char **argv) {\n"
    "    // Start up the gnome\n"
    "    gnome_init(\"stest\", \"1.0\", argc, argv);\n}"
   );
   
   gtk_widget_show_all(app);
   gtk_widget_grab_focus(GTK_WIDGET(editor));
   gtk_main();

   return 0;
}
