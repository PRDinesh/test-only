//
// "$Id: ide_support_ui.fl 6614 2009-01-01 16:11:32Z matt $"
//
// Setting and shell dialogs for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

// generated by Fast Light User Interface Designer (fluid) version 1.0300

#include "ide_support_ui.h"
#include "ide_support.h"
#include <FL/Fl_File_Chooser.H>

Fl_Double_Window *dbmanager_window=(Fl_Double_Window *)0;

static void cb_fileopen(Fl_Button*, void*) {
  const char *filename = fl_file_chooser("Load Database", "*.db", 0, 0);
if (filename) {
  ui_load_database(filename);
};
}

Fl_Tree *dbmanager_tree=(Fl_Tree *)0;

Fl_Double_Window* make_dbmanager_window() {
  { dbmanager_window = new Fl_Double_Window(409, 510);
    { new Fl_File_Input(80, 4, 280, 36, "Database:");
    } // Fl_File_Input* o
    { Fl_Button* o = new Fl_Button(360, 14, 36, 26, "@fileopen");
      o->labelcolor((Fl_Color)94);
      o->callback((Fl_Callback*)cb_fileopen);
    } // Fl_Button* o
    { dbmanager_tree = new Fl_Tree(12, 52, 208, 444);
      dbmanager_tree->box(FL_DOWN_BOX);
      dbmanager_tree->color((Fl_Color)55);
      dbmanager_tree->selection_color(FL_BACKGROUND_COLOR);
      dbmanager_tree->labeltype(FL_NORMAL_LABEL);
      dbmanager_tree->labelfont(0);
      dbmanager_tree->labelsize(14);
      dbmanager_tree->labelcolor(FL_FOREGROUND_COLOR);
      dbmanager_tree->align(Fl_Align(FL_ALIGN_CENTER));
      dbmanager_tree->when(FL_WHEN_RELEASE);
      Fl_Group::current()->resizable(dbmanager_tree);
      dbmanager_tree->showroot(0);
      dbmanager_tree->labelsize(12);
    } // Fl_Tree* dbmanager_tree
    { Fl_Group* o = new Fl_Group(232, 52, 164, 444);
      { new Fl_Button(304, 468, 92, 28, "Close");
      } // Fl_Button* o
      { Fl_Group* o = new Fl_Group(232, 128, 164, 340);
        o->end();
        Fl_Group::current()->resizable(o);
      } // Fl_Group* o
      { Fl_Box* o = new Fl_Box(232, 52, 164, 76, "Show editor\nfor selected\nItem here");
        o->box(FL_THIN_DOWN_BOX);
      } // Fl_Box* o
      o->end();
    } // Fl_Group* o
    dbmanager_window->end();
  } // Fl_Double_Window* dbmanager_window
  return dbmanager_window;
}

//
// End of "$Id: ide_support_ui.fl 6614 2009-01-01 16:11:32Z matt $".
//
