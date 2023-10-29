#include "vec2D.h"
// #include <std_lib_facilities.h>

Vec2d::Vec2d() : x{0}, y{0} {};

double Vec2d::get_x() const { return x; };

double Vec2d::get_y() const { return y; };

Vec2d::Vec2d(double x_, double y_) : x{x_}, y{y_} {};

std::ostream& operator<< (std::ostream& stream, Vec2d vect)
{
  stream << vect.get_x() << " " << vect.get_y();
  return stream;
}

Vec2d Vec2d::operator+= (const Vec2d& rval)
{
  x += rval.x;
  y += rval.y;
  return *this;
}

// Vec2d Vec2d::operator+ (const Vec2d& rval) const
// {
//   Vec2d temp = *this;
//   temp += rval;
//   return temp;
// }

Vec2d operator+ (const Vec2d& lval, const Vec2d& rval)
{
  Vec2d temp = {rval.get_x() + lval.get_x(), lval.get_y() + rval.get_y()};
  return temp;
}

Vec2d operator- (const Vec2d& lval, const Vec2d& rval)
{
  Vec2d temp = {lval.get_x() - rval.get_x(), lval.get_y() - rval.get_y()};
  return temp;
}

Vec2d operator* (const double& lval, const Vec2d& rval)
{
  return {lval * rval.get_x(), lval * rval.get_y()};
}

Vec2d operator* (const Vec2d& lval, const double& rval)
{
  return {rval * lval.get_x(), rval * lval.get_y()};
}

double operator* (const Vec2d& lval, const Vec2d& rval)
{
  return rval.get_x() * lval.get_x() + rval.get_y() * lval.get_y();
}