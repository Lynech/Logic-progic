#ifndef DRAWING_ELEMS_H
#define DRAWING_ELEMS_H

#include "add_elem_impl.h"
#include "graph_elems.h"
#include "logic_elems.h"
#include "map"
#include "mapgroup.h"
#include <FL/Fl_File_Chooser.H>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

void read_file (const std::string& file_name, LogicMap* map);
void write_file (const std::string& file_name, LogicMap* map);

#endif