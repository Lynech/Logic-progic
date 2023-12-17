#ifndef GRAPH_PORT_H
#define GRAPH_PORT_H

#include "graph_elems.h"
#include "graph_link.h"
enum class port_types
{
  input = 0,
  output = 1
};

bool made_logic_link (Port* port1, Port* port2);

Link* made_full_link (Port* port1, Port* port2);

void try_make_link (MapGroup* map, Port* port1, Port* port2);

// класс кружочков связи
class Port : public Fl_Widget
{
private:
  port_types type;           //
  std::vector<Link*> links;  //
  Fl_Menu_Item* menu;

  bool is_entered = false;

  bool inverted = false;

public:
  Port(int x, int y, int w, int h, port_types t, const char* l = 0);

  void draw () override;

  int handle (int event) override;

  port_types get_type () { return type; }  //

  std::vector<Link*> get_links () { return links; }  //

  void add_link (Link* l) { links.push_back(l); }  //

  void delete_link_by_index (int i);  //

  int release_handle ();  //

  Port* find_port ();  //

  bool linked ();  //

  bool is_linked ()
  {
    for (int i = 0; i < links.size(); i++)
      if (links[i])
        return 1;
    return 0;
  }

  void invert () { inverted = !inverted; }

  bool is_inverted () { return inverted; }
};

#endif