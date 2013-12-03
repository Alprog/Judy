
#define GTK

#include <gtk/gtk.h>

#include <Scintilla.h>
#include <SciLexer.h>
#define PLAT_GTK 1
#include <ScintillaWidget.h>


static int exit_app(GtkWidget*w, GdkEventAny*e, gpointer p) {
	gtk_main_quit();
	return w || e || p || 1;	// Avoid warnings
}

int main(int argc, char **argv) {
	GtkWidget *app;
	GtkWidget *editor;
	ScintillaObject *sci;

	gtk_init(&argc, &argv);
	app = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	editor = scintilla_new();
	sci = SCINTILLA(editor);

	gtk_container_add(GTK_CONTAINER(app), editor);
	/*gtk_signal_connect(GTK_OBJECT(app), "delete_event",
		GTK_SIGNAL_FUNC(exit_app), 0);

	scintilla_set_id(sci, 0);
	gtk_widget_set_usize(editor, 500, 300);

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
	gtk_main();*/

	return 0;
}
