// generated by Fast Light User Interface Designer (fluid) version 1.0008

#ifndef alignment_panel_h
#define alignment_panel_h
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
extern Fl_Window *alignment_window;
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
extern void alignment_cb(Fl_Input*, long);
extern Fl_Input *horizontal_input;
extern Fl_Input *vertical_input;
extern Fl_Input *snap_input;
#include <FL/Fl_Button.H>
extern void header_input_cb(Fl_Input*, void*);
extern Fl_Input *header_file_input;
extern void code_input_cb(Fl_Input*, void*);
extern Fl_Input *code_file_input;
#include <FL/Fl_Light_Button.H>
extern void include_H_from_C_button_cb(Fl_Light_Button*, void*);
extern Fl_Light_Button *include_H_from_C_button;
Fl_Window* make_alignment_window();
#endif
