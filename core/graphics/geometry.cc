/**
 * This file is part of the "fviz" project
 *   Copyright (c) 2018 Paul Asmuth
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <algorithm>
#include <iostream>
#include "layout.h"

namespace fviz {

Point::Point() :
    x(0.0f),
    y(0.0f) {}

Point::Point(
    double _x,
    double _y) :
    x(_x),
    y(_y) {}

std::ostream& operator <<(std::ostream& os, const Point& p) {
  os << "Point(";
  os << p.x;
  os << ", ";
  os << p.y;
  os << ")";
  return os;
}

Rectangle::Rectangle() :
    x(0.0f),
    y(0.0f),
    w(0.0f),
    h(0.0f) {}

Rectangle::Rectangle(
    double _x,
    double _y,
    double _w,
    double _h) :
    x(_x),
    y(_y),
    w(_w),
    h(_h) {}

std::ostream& operator <<(std::ostream& os, const Rectangle& r) {
  os << "Rectangle(";
  os << r.x;
  os << ", ";
  os << r.y;
  os << ", ";
  os << r.w;
  os << ", ";
  os << r.h;
  os << ")";
  return os;
}

} // namespace fviz

