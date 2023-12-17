#ifndef MY_FLTK_H
#define MY_FLTH_H
#include "graph_elems.h"
#include "logicmap.h"
#include "mapgroup.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Window.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <iostream>

int choise (int a, int b, int c);

template <class T> void add_elem (Fl_Widget*, void*);

template <class T> T* add_elem_from_file (void* userdata, int xx, int yy);

#endif