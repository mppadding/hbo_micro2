using System;
using Gtk;
using UI = Gtk.Builder.ObjectAttribute;

namespace ui
{
    class MainWindow : Window
    {
        [UI] private Entry _entry = null;
        [UI] private TreeView _treeview;

        public MainWindow() : this(new Builder("MainWindow.glade")) { }

        private MainWindow(Builder builder) : base(builder.GetObject("MainWindow").Handle)
        {
            builder.Autoconnect(this);

            DeleteEvent += Window_DeleteEvent;
        }

        private void Window_DeleteEvent(object sender, DeleteEventArgs a)
        {
            Application.Quit();
        }
    }
}
