#include "graph_elems.h"
#include "logic_elems.h"
#include <algorithm>
#include <cmath>

#include <cassert>
#include <iostream>
#include <vector>

using namespace graph;

namespace port_menu {
uchar noflag = 0;
uchar labeltype = FL_NORMAL_LABEL;
uchar labelfont = FL_HELVETICA;
uchar labelsize = FL_NORMAL_SIZE;
uchar labelcolor = FL_BLACK;
uchar noshortcut = 0;
const char* endmenu = 0;
Fl_Callback* nocallback = nullptr;
void* nouserdata = nullptr;
};  // namespace port_menu

void callback4logic (void* lable)
{
  Label* lableptr = (Label*)(lable);
  lableptr->redraw();
}

void invert_port (Fl_Widget*, void* userdata)
{
  Port* l_c = (Port*)userdata;
  Label* label = ((Element*)(l_c->parent()))->get_draw_elem();

  if (l_c->get_type() == port_types::input)
  {
    l_c->invert();
  }
  else
  {
    logic::Element* log_el = label->logic_elem;
    log_el->invert();
  }
  label->redraw();
}

void delete_through_port (Fl_Widget*, void* userdata)
{
  Port* l_c = (Port*)userdata;

  std::vector<Link*> links = l_c->get_links();
  for (Link* i : links)
  {
    if ((i != nullptr) && ((i->get_input_port()) != nullptr) &&
        ((i->get_output_port()) != nullptr))
    {
      i->delete_link();
    }
  }
}

// инвертирует выход
void invert_elem (Fl_Widget*, void* userdata)
{
  Label* l = (Label*)userdata;
  logic::Element* log_el = l->logic_elem;
  log_el->invert();
  l->redraw();
}

void delete_all_elem_links (Fl_Widget*, void* userdata)
{
  Label* l = (Label*)userdata;
  l->delete_all_links();
}

void delete_elem (Fl_Widget* a, void* userdata)
{
  Label* l = (Label*)userdata;

  // удаляем связи
  l->delete_all_links();

  // удаляем Element
  Fl::delete_widget(l->parent());
  Fl::do_widget_deletion();
}

// конструктор класса Link
Link::Link(Port* c1, Port* c2)
    : Fl_Widget{std::min(c1->x(), c2->x()), std::min(c1->y(), c2->y()),
                abs(c1->x() - c2->x()) + c1->w(),
                abs(c1->y() - c2->y()) + c1->w()}
{
  if (c1->get_type() == port_types::input)
  {
    input_port = c1;
    output_port = c2;
  }
  else
  {
    output_port = c1;
    input_port = c2;
  }
}

int Label::handle(int event)
{
  if (event == FL_ENTER)
  {
    std::cout << "+__________Label_enter__________+\n";
    is_entered = true;
    redraw();
    return 1;
  }
  if (event == FL_LEAVE)
  {
    std::cout << "+__________Label_leave__________+\n";
    is_entered = false;
    redraw();
    return 1;
  }
  if (event == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
  {
    auto temp = menu->popup(Fl::event_x(), Fl::event_y());
    if (temp && temp->callback())
      temp->do_callback(nullptr);
    return 1;
  }
  return 1;
  return 0;
}

void Label::delete_all_links()
{
  Element* el = (Element*)(this->parent());
  std::vector<Port*> ports = el->get_input_ports();

  // удаляем связи у каждого входа
  for (Port* i : ports)
  {
    if (i != nullptr)
    {
      std::vector<Link*> links = i->get_links();
      for (Link* j : links)
        if (j != nullptr)
        {
          j->delete_link();
        }
    }
  }

  // удаляем каждый вход (size -1 означает, что 1 оставляем)
  for (int i = 0; i < ports.size() - 1; i++)
  {
    if (ports[i] != nullptr)
    {
      el->delete_port(ports[i]);
    }
  }

  // удаляем все связи у выхода
  Port* output_port = el->get_output_port();
  std::vector<Link*> links = output_port->get_links();
  for (Link* i : links)
    if (i != nullptr)
    {
      i->delete_link();
    }

  // удаляем выход
  el->delete_port(output_port);
}

// отрисовка объектов класса Link
void Link::draw()
{
  fl_line_style(0, 3);
  fl_color(FL_BLACK);

  fl_line(input_port->x(), input_port->y() + input_port->h() / 2,
          output_port->x() + output_port->w(),
          output_port->y() + output_port->h() / 2);
}

void Link::delete_link()
{
  logic::Element* input_log_el;
  logic::Element* output_log_el;

  // удаляем связь из порта-начала:
  for (int i = 0;
       ((input_port != nullptr) && (i < input_port->get_links().size()));
       i++)
  {
    if (input_port->get_links()[i] == this)
    {
      input_port->delete_link_by_index(i);

      input_log_el =
          ((Element*)(input_port->parent()))->get_draw_elem()->logic_elem;
      break;
    }
  }

  // удаляем связь из порта-конца:
  for (int i = 0;
       ((input_port != nullptr) && (i < output_port->get_links().size()));
       i++)
  {
    if (output_port->get_links()[i] == this)
    {
      output_port->delete_link_by_index(i);

      output_log_el =
          ((Element*)(output_port->parent()))->get_draw_elem()->logic_elem;
      break;
    }
  }

  if (input_log_el->remove_sorse(output_log_el, input_port->is_inverted()))
    std::cout << "deleted sorse" << std::endl;

  // нужно удалять сам входной порт
  auto temp = (graph::Element*)input_port->parent();
  temp->delete_port(input_port);
  int n = temp->get_input_ports().size();

  temp->resize(temp->x(), temp->y(), temp->w(),
               (temp->h()) * (n + 1) / (n + 2));
  int circle_w = temp->w();
  circle_w /= 9;
  for (int i = 0; i < n; i++)
  {
    Port* l_c = temp->get_input_ports()[i];
    l_c->resize(temp->x(),
                temp->y() + temp->h() / (n + 1) * (i + 1) - circle_w / 2,
                circle_w, circle_w);
  }
  temp->get_output_port()->resize(temp->x() + temp->w() - circle_w,
                                  temp->y() + temp->h() / 2 - circle_w / 2,
                                  circle_w, circle_w);

  // удаляем связь как виджет:
  Fl::delete_widget(this);
  Fl::do_widget_deletion();
}

// конструктор абстрактного класса Element
Element::Element(int x_, int y_, int w_, int h_, int inputs_n_,
                 const char* l)
    : Fl_Group{x_ - w_ * 2 / 5, y_, w_ * 9 / 5, h_, l}, inputs_n{inputs_n_},
      elem_link_lenth{w_ * 2 / 5}, line_thikness{w_ / 25}
{
  end();
  draw_elem = new Label{x_, y_, w_, h_};
  add_resizable(*draw_elem);
  // TODO: не рисовать вход если max_input_amount = 0
  if (inputs_n != 0)
  {
    Port* first_input_port =
        new Port{x_ - w_ * 2 / 5, y_ + h_ / 2 - w_ / 10, w_ / 5, w_ / 5,
                 port_types::input};

    add(first_input_port);

    input_ports.push_back(first_input_port);
  }

  // Выходной порт
  output_port = new Port{x_ + w_ * 6 / 5, y_ + h_ / 2 - w_ / 10, w_ / 5,
                         w_ / 5, port_types::output};
  add(output_port);

  // Входные порты если их число конечно или ограничено снизу
  for (int i = 1; i < inputs_n; i++)
    add_input_port_pre();
  if (inputs_n < 0)
    for (int i = 1; i < -inputs_n; i++)
      add_input_port_pre();
}

//  конструктор класса Source

Src0::Src0(int x, int y, int h, int w, const char* l)
    : Element{x, y, h, w, 0, "no_input"}
{
  draw_elem->logic_elem = new logic::Src(callback4logic, draw_elem, 0);
  draw_elem->set_value(logic::Value::False);
  input_ports = {};

  set_lable(draw_src0);
}

//  конструктор класса Source

Src1::Src1(int x, int y, int h, int w, const char* l)
    : Element{x, y, h, w, 0, "no_input"}
{
  draw_elem->logic_elem = new logic::Src(callback4logic, draw_elem, 1);
  draw_elem->set_value(logic::Value::True);
  input_ports = {};

  set_lable(draw_src1);
}

//  конструктор класса И
And::And(int x, int y, int h, int w, const char* l)
    : Element{x, y, h, w, -1, l}
{
  draw_elem->logic_elem = new logic::And{callback4logic, draw_elem};
  set_lable(draw_and);
}

// обработка взаимодействия с объектом класса Elem
int Element::handle(int event)
{
  if (Fl_Group::handle(event))
    return 1;
  return 0;
}

void Element::delete_port(Port* l_c)
{
  if (l_c->get_type() == port_types::input)
  {
    for (int i = 0; i < input_ports.size(); i++)
    {
      if (input_ports[i] == l_c)
      {
        input_ports.erase(input_ports.begin() + i);
        std::vector<Port*>(input_ports).swap(input_ports);

        Fl::delete_widget(l_c);
        Fl::do_widget_deletion();
        break;
      }
    }
  }
}

void Element::add_input_port()
{
  if (inputs_n < 0)
  {
    int n = this->input_ports.size();  // кол-во входов
    std::cout << x() << std::endl
              << y() << std::endl
              << w() << std::endl
              << h();
    this->resize(x(), y(), w(),
                 (h()) * (n + 2) /
                     (n + 1));  // пропорционально увеличили всю группу

    int circle_w = this->w();
    circle_w /= 9;
    Port* new_l_s = new Port{0, 0, circle_w, circle_w, port_types::input};

    this->input_ports.push_back(new_l_s);
    this->add(new_l_s);

    n++;

    for (int i = 0; i < n; i++)
    {
      Port* l_c = input_ports[i];
      l_c->resize(x(), y() + h() / (n + 1) * (i + 1) - circle_w / 2,
                  circle_w, circle_w);
    }

    output_port->resize(x() + w() - circle_w, y() + h() / 2 - circle_w / 2,
                        circle_w, circle_w);
    redraw();
    window()->redraw();
  }
}

void Element::add_input_port_pre()
{
  int n = this->input_ports.size();  // кол-во входов
  std::cout << x() << std::endl
            << y() << std::endl
            << w() << std::endl
            << h();
  this->resize(x(), y(), w(),
               (h()) * (n + 3) /
                   (n + 1));  // пропорционально увеличили всю группу

  int circle_w = this->w();
  circle_w /= 9;
  Port* new_l_s = new Port{0, 0, circle_w, circle_w, port_types::input};

  this->input_ports.push_back(new_l_s);
  this->add(new_l_s);

  n++;

  for (int i = 0; i < n; i++)
  {
    Port* l_c = input_ports[i];
    l_c->resize(x(), y() + h() / (n + 1) * (i + 1) - circle_w / 2, circle_w,
                circle_w);
  }

  output_port->resize(x() + w() - circle_w, y() + h() / 2 - circle_w / 2,
                      circle_w, circle_w);
}

Label::Label(
    int x, int y, int w, int h, const char* l,
    std::function<void(int, int, int, int, logic::Value)> Label_draw)
    : Label_draw_{Label_draw}, Fl_Widget{x, y, w, h, l}
{
  menu = new Fl_Menu_Item[4];
  menu[0] = Fl_Menu_Item{"inversion",          port_menu::noshortcut,
                         invert_elem,          this,
                         port_menu::noflag,    port_menu::labeltype,
                         port_menu::labelfont, port_menu::labelsize,
                         port_menu::labelcolor};

  menu[1] = Fl_Menu_Item{"delete all links",    port_menu::noshortcut,
                         delete_all_elem_links, this,
                         port_menu::noflag,     port_menu::labeltype,
                         port_menu::labelfont,  port_menu::labelsize,
                         port_menu::labelcolor};
  menu[2] = Fl_Menu_Item{"delete elem",        port_menu::noshortcut,
                         delete_elem,          this,
                         port_menu::noflag,    port_menu::labeltype,
                         port_menu::labelfont, port_menu::labelsize,
                         port_menu::labelcolor};

  menu[3] = Fl_Menu_Item{
      port_menu::endmenu,    port_menu::noshortcut, port_menu::nocallback,
      port_menu::nouserdata, port_menu::noflag,     port_menu::labeltype,
      port_menu::labelfont,  port_menu::labelsize,  port_menu::labelcolor};
}

void Label::draw()
{
  draw_box(FL_FLAT_BOX, 16);
  if (Label_draw_)
  {
    int x_elem = x() + w() / 6;
    int y_elem = y() + h() / 6;
    int w_elem = 2 * w() / 3;
    int h_elem = 2 * h() / 3;
    Label_draw_(x_elem, y_elem, w_elem, h_elem, logic_elem->get_value());
  }
  if (is_entered)
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);
    fl_rect(x() + 4, y() + 4, w() - 8, h() - 8);
  }

  // рисуем инвертированность выхода
  if (logic_elem->is_inverted())
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);

    fl_begin_polygon();
    fl_circle(x() + w() - w() / 11, y() + h() / 2, w() / 11);
    fl_end_polygon();

    fl_color(FL_WHITE);
    fl_line_style(0, 2);
    fl_begin_loop();
    fl_circle(x() + w() - w() / 10, y() + h() / 2, w() / 10);
    fl_end_loop;
  }

  // рисуем инвертированность входа
  Element* par = (Element*)(this->parent());
  std::vector<Port*> input_ports = par->get_input_ports();

  for (int i = 0; i < input_ports.size(); i++)
  {
    if (input_ports[i]->is_inverted())
    {
      Port* p = input_ports[i];
      fl_color(FL_BLACK);
      fl_line_style(0, 2);

      fl_begin_polygon();
      fl_circle(this->x() + this->w() / 11, p->y() + p->h() / 2,
                this->w() / 11);
      fl_end_polygon();

      fl_color(FL_WHITE);
      fl_line_style(0, 2);
      fl_begin_loop();
      fl_circle(this->x() + this->w() / 10, p->y() + p->h() / 2,
                this->w() / 10);
      fl_end_loop;
    }
  }
}

void Element::draw()
{
  int x_ = x() + elem_link_lenth;
  int w_ = w() - 2 * elem_link_lenth;
  int y_ = y();
  int h_ = h();
  int x_input_link = x_ - elem_link_lenth;
  int y_input_link = y_ + h_ / 2;

  ////// если 0 портов - рисовать 1

  // input link
  int n = input_ports.size();  // кол-во входов
  for (int i = 0; i < n; i++)
  {
    fl_color(16);
    fl_line_style(0, 4);
    fl_line(x_, y_ + (h_ / (n + 1)) * (i + 1), x_input_link,
            y_ + (h_ / (n + 1)) * (i + 1));
  }
  int x_output_link = x_ + w_ + elem_link_lenth;
  int y_output_link = y_ + h_ / 2;

  //  output link
  fl_color(16);
  fl_line_style(0, 4);
  fl_line(x_ + w_, y_ + h_ / 2, x_output_link, y_output_link);

  Fl_Group::draw();
}

void Element::invert()
{
  output_port->invert();
  redraw();
}

// конструктор класса НЕ
Buff::Buff(int x, int y, int w, int h, const char* l)
    : Element{x, y, w, h, 1, l}
{
  inputs_n = 1;
  draw_elem->logic_elem = new logic::Buff{callback4logic, draw_elem};
  set_lable(draw_buff);
}

// конструктор класса ИЛИ
Or::Or(int x, int y, int w, int h, const char* l)
    : Element{x, y, w, h, -1, l}
{
  inputs_n = -1;
  draw_elem->logic_elem = new logic::Or{callback4logic, draw_elem};
  set_lable(draw_or);
}

void draw_and (int x, int y, int w, int h, logic::Value value)
{
  // выбор цвета в зависимости от значения
  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_rectf(x + 1, y + 1, w / 2, h);

  // правая часть (окружность) заливка
  fl_pie(x + 1, y + 1, w - 2, h - 2, -90.0, 90.0);

  // левая часть обрамление
  fl_color(FL_BLACK);
  fl_line_style(0, 2);
  fl_line(x, y, x, y + h);
  fl_line(x, y, x + w / 2, y);
  fl_line(x, y + h, x + w / 2, y + h);

  // правая часть обрамление
  fl_arc(x, y, w, h, -90.0, 90.0);
}

void draw_src0 (int x, int y, int w, int h, logic::Value value)
{
  // выбор цвета в зависимости от значения
  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_rectf(x + 1, y + 1, w - 2, h - 2);
  fl_color(FL_BLACK);
  if (value == logic::Value::False)
  {
    fl_draw("0", x + w / 2, y + h / 2);
  }
  else if (value == logic::Value::True)
  {
    fl_draw("1", x + w / 2, y + h / 2);
  }
}

void draw_src1 (int x, int y, int w, int h, logic::Value value)
{
  // выбор цвета в зависимости от значения
  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_rectf(x + 1, y + 1, w - 2, h - 2);
  fl_color(FL_BLACK);
  if (value == logic::Value::False)
  {
    fl_draw("0", x + w / 2, y + h / 2);
  }
  else if (value == logic::Value::True)
  {
    fl_draw("1", x + w / 2, y + h / 2);
  }
}

void draw_buff (int x, int y, int w, int h, logic::Value value)
{
  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  // заполнение
  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_polygon(x, y, x, y + h, x + w, y + h / 2);
  // обрамление
  fl_color(FL_BLACK);
  fl_line_style(0, 2);
  fl_begin_loop();
  fl_vertex(x, y);
  fl_vertex(x, y + h);
  fl_vertex(x + w, y + h / 2);
  fl_end_loop();
}

void draw_or (int x, int y, int w, int h, logic::Value value)
{

  auto draw_color = FL_BLUE;
  if (value == logic::Value::False)
    draw_color = FL_RED;
  else if (value == logic::Value::True)
    draw_color = FL_GREEN;

  fl_color(draw_color);
  fl_line_style(0, 2);
  fl_push_matrix();
  fl_begin_complex_polygon();
  fl_translate(x, 0);
  fl_scale(2 * w / (double)h, 1.);
  fl_arc(0, y + h / 2, h / 2, -90, 90);
  fl_scale(1 / 4., 1.);
  fl_arc(0, y + h / 2, h / 2, 90, -90);
  fl_end_complex_polygon();
  fl_pop_matrix();

  fl_color(FL_BLACK);
  fl_line_style(0, 2);
  fl_push_matrix();
  fl_begin_loop();
  fl_translate(x, 0);
  fl_scale(2 * w / (double)h, 1.);
  fl_arc(0, y + h / 2, h / 2, -90, 90);
  fl_scale(1 / 4., 1.);
  fl_arc(0, y + h / 2, h / 2, 90, -90);
  fl_end_loop();
  fl_pop_matrix();
}

// конструктор класса LinkCircle
Port::Port(int x, int y, int w, int h, port_types t, const char* l)
    : Fl_Widget{x, y, w, h, l}
{
  type = t;
  menu = new Fl_Menu_Item[3];
  // TODO: make if-else to swap from "invert" to "uninvert"
  menu[0] = Fl_Menu_Item{"inversion",          port_menu::noshortcut,
                         invert_port,          this,
                         port_menu::noflag,    port_menu::labeltype,
                         port_menu::labelfont, port_menu::labelsize,
                         port_menu::labelcolor};
  menu[1] = Fl_Menu_Item{"delete",
                         port_menu::noshortcut,
                         delete_through_port,
                         this,
                         port_menu::noflag,
                         port_menu::labeltype,
                         port_menu::labelfont,
                         port_menu::labelsize,
                         port_menu::labelcolor};
  menu[2] = Fl_Menu_Item{
      port_menu::endmenu,    port_menu::noshortcut, port_menu::nocallback,
      port_menu::nouserdata, port_menu::noflag,     port_menu::labeltype,
      port_menu::labelfont,  port_menu::labelsize,  port_menu::labelcolor};
}

// отрисовка объектов класса LinkCircle
void Port::draw()
{
  fl_color(16);
  fl_line_style(0, 4);
  fl_pie(x(), y(), w(), h(), 0., 360.);
  if (is_entered)
  {
    fl_color(FL_BLACK);
    fl_line_style(0, 2);
    fl_arc(x(), y(), w(), h(), 0., 360.);
  }
}

// обработка взаимодействий с объектом класса LinkCircle
int Port::handle(int event)
{

  int x_ = x(), y_ = y(), w_ = w(), h_ = h();
  switch (event)
  {
  case FL_PUSH:
    if (event == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE)
    {
      auto temp = menu->popup(Fl::event_x(), Fl::event_y());
      if (temp && temp->callback())
        temp->do_callback(nullptr);
      return 1;
    }
    return 1;
  case FL_ENTER:
    is_entered = true;
    redraw();
    return 1;
  case FL_LEAVE:
    is_entered = false;
    redraw();
    return 1;
  case FL_DRAG:
    return 1;
  case FL_RELEASE:
  {
    // элемент (группа), которому принадлежит этот порт
    graph::Element* this_elem_group = (graph::Element*)this->parent();
    MapGroup* map = (MapGroup*)this_elem_group->parent();
    int n = map->children();

    graph::Element* elem_group;
    Port* p;

    bool needed_found = false;
    for (int i = 0; i < n && !needed_found; i++)
    {
      // взяли элемент (группа)
      elem_group = dynamic_cast<graph::Element*>(map->child(i));
      // кол-во сущностей в элементе
      if (elem_group != nullptr)
      {
        int n1 = elem_group->children();
        for (int j = 0; j < n1 && !needed_found; j++)
        {
          // взяли сущность в надежде что она порт
          p = dynamic_cast<Port*>(elem_group->child(j));
          // проверяем, что это порт, он нужного типа и что наведение на
          // него
          if ((p != nullptr) && (p != this) && (Fl::event_inside(p)) &&
              (p->type != this->type) &&
              ("вход не занят"))  // TODO: проверка занятости входа
          {
            needed_found = true;
            break;
          }
        }
      }
    }
    if (!needed_found)
      return 1;
    // определяем, из какого выходит связь и в какой входит
    graph::Element* input_el;
    graph::Element* output_el;
    if (this->type == port_types::input)
    {
      // ведем связь из this в p -> нужно добавить еще один вход в
      // элемент порта
      input_el = (graph::Element*)this->parent();
      output_el = (graph::Element*)p->parent();
    }
    else
    {
      // ведем связь из p в this -> нужно добавить в еще один вход в
      // элемент порта
      output_el = (graph::Element*)this->parent();
      input_el = (graph::Element*)p->parent();
    }
    Link* l = new Link{p, this};
    input_el->add_input_port();

    // добавляем связи в порты
    this->add_link(l);
    p->add_link(l);

    {  // add link to logic
      Port *in_p, *out_p;
      if (this->get_type() == port_types::input)
      {
        in_p = this;
        out_p = p;
      }
      else
      {
        in_p = p;
        out_p = this;
      }
      logic::Element* in_log_el =
          ((graph::Element*)(in_p->parent()))->get_draw_elem()->logic_elem;
      logic::Element* out_log_el =
          ((graph::Element*)(out_p->parent()))->get_draw_elem()->logic_elem;
      // Установили связь
      *out_log_el >> *in_log_el;
    }

    map->add(l);

    l->redraw();

    // input_el->add_input_link(l);
    // output_el->add_output_link(l);

    input_el->redraw();
    output_el->redraw();

    is_entered = false;
    return 1;
  }
  default:
    return Fl_Widget::handle(event);
  }
}

void Port::delete_link_by_index(int i)
{
  links.erase(links.begin() + i);
  std::vector<Link*>(links).swap(links);
}
