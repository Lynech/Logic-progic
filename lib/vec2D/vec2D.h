#ifndef VEC2D_H
#define VEC2D_H
#include <iostream>

class Vec2d
{
public:
  double x;
  double y;

public:
  Vec2d();

  double get_x () const;

  double get_y () const;

  Vec2d(double x_, double y_);
  Vec2d operator+= (const Vec2d& rval);
  //   Vec2d operator+ (const Vec2d& rval) const;
};

std::ostream& operator<< (std::ostream& stream, Vec2d vect);
Vec2d operator+ (const Vec2d& lval, const Vec2d& rval);
Vec2d operator- (const Vec2d& lval, const Vec2d& rval);
Vec2d operator* (const double& lval, const Vec2d& rval);
Vec2d operator* (const Vec2d& lval, const double& rval);
double operator* (const Vec2d& lval, const Vec2d& rval);

#endif