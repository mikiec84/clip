/**
 * This file is part of the "clip" project
 *   Copyright (c) 2018 Paul Asmuth
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "box.h"

#include "environment.h"
#include "layout.h"
#include "color_reader.h"
#include "sexpr_conv.h"
#include "sexpr_util.h"
#include "graphics/color.h"
#include "graphics/page_description.h"

#include <functional>

using namespace std::placeholders;
using std::bind;

namespace clip::elements::layout::box {

struct BoxBorderConfig {
  Color color;
  Measure width;
};

struct BoxElement {
  Measure font_size;
  std::optional<Color> background;
  Color border_color;
  std::array<Measure, 4> margins;
  std::array<BoxBorderConfig, 4> borders;
  std::vector<ElementRef> elements;
};

ReturnCode draw(
    std::shared_ptr<BoxElement> config,
    const LayoutInfo& layout,
    Page* layer) {
  /* convert units  */
  auto margins = config->margins;
  for (auto& m : margins) {
    convert_unit_typographic(layer->dpi, config->font_size, &m);
  }

  /* calculate body box */
  auto bbox = layout_margin_box(
      layout.content_box,
      margins[0],
      margins[1],
      margins[2],
      margins[3]);

  /* draw background */
  if (config->background) {
    const auto& bg_box = bbox;

    fillRectangle(
        layer,
        Point(bg_box.x, bg_box.y),
        bg_box.w,
        bg_box.h,
        *config->background);
  }

  /* draw children */
  for (const auto& e : config->elements) {
    LayoutInfo layout;
    layout.content_box = bbox;

    if (auto rc = e->draw(layout, layer); !rc) {
      return rc;
    }
  }

  /* draw top border  */
  if (config->borders[0].width > 0) {
    StrokeStyle border_style;
    border_style.line_width = config->borders[0].width;
    border_style.color = config->borders[0].color;

    strokeLine(
        layer,
        Point(bbox.x, bbox.y),
        Point(bbox.x + bbox.w, bbox.y),
        border_style);
  }

  /* draw right border  */
  if (config->borders[1].width > 0) {
    StrokeStyle border_style;
    border_style.line_width = config->borders[1].width;
    border_style.color = config->borders[1].color;

    strokeLine(
        layer,
        Point(bbox.x + bbox.w, bbox.y),
        Point(bbox.x + bbox.w, bbox.y + bbox.h),
        border_style);
  }

  /* draw top border  */
  if (config->borders[2].width > 0) {
    StrokeStyle border_style;
    border_style.line_width = config->borders[2].width;
    border_style.color = config->borders[2].color;

    strokeLine(
        layer,
        Point(bbox.x, bbox.y + bbox.h),
        Point(bbox.x + bbox.w, bbox.y + bbox.h),
        border_style);
  }

  /* draw left border  */
  if (config->borders[3].width > 0) {
    StrokeStyle border_style;
    border_style.line_width = config->borders[3].width;
    border_style.color = config->borders[3].color;

    strokeLine(
        layer,
        Point(bbox.x, bbox.y),
        Point(bbox.x, bbox.y + bbox.h),
        border_style);
  }

  return OK;
}

ReturnCode build(
    const Environment& env,
    const Expr* expr,
    ElementRef* elem) {
  auto config = std::make_shared<BoxElement>();
  config->font_size = env.font_size;
  config->border_color = env.foreground_color;

  auto config_rc = expr_walk_map(expr_next(expr), {
    {
      "margin",
      expr_calln_fn({
        bind(&measure_read, _1, &config->margins[0]),
        bind(&measure_read, _1, &config->margins[1]),
        bind(&measure_read, _1, &config->margins[2]),
        bind(&measure_read, _1, &config->margins[3]),
      })
    },
    {"margin-top", bind(&measure_read, _1, &config->margins[0])},
    {"margin-right", bind(&measure_read, _1, &config->margins[1])},
    {"margin-bottom", bind(&measure_read, _1, &config->margins[2])},
    {"margin-left", bind(&measure_read, _1, &config->margins[3])},
    {
      "border-color",
      expr_calln_fn({
        bind(&color_read, env, _1, &config->borders[0].color),
        bind(&color_read, env, _1, &config->borders[1].color),
        bind(&color_read, env, _1, &config->borders[2].color),
        bind(&color_read, env, _1, &config->borders[3].color),
      })
    },
    {"border-top-color", bind(&color_read, env, _1, &config->borders[0].color)},
    {"border-right-color", bind(&color_read, env, _1, &config->borders[1].color)},
    {"border-bottom-color", bind(&color_read, env, _1, &config->borders[2].color)},
    {"border-left-color", bind(&color_read, env, _1, &config->borders[3].color)},
    {
      "border-width",
      expr_calln_fn({
        bind(&measure_read, _1, &config->borders[0].width),
        bind(&measure_read, _1, &config->borders[1].width),
        bind(&measure_read, _1, &config->borders[2].width),
        bind(&measure_read, _1, &config->borders[3].width),
      })
    },
    {"border-top-width", bind(&measure_read, _1, &config->borders[0].width)},
    {"border-right-width", bind(&measure_read, _1, &config->borders[1].width)},
    {"border-bottom-width", bind(&measure_read, _1, &config->borders[2].width)},
    {"border-left-width", bind(&measure_read, _1, &config->borders[3].width)},
    {"background-color", bind(&color_read_opt, env, _1, &config->background)},
    {
      "foreground-color",
      expr_calln_fn({
        bind(&color_read, env, _1, &config->border_color),
      })
    },
    {"border-color", bind(&color_read, env, _1, &config->border_color)},
    {"body", bind(&element_build_list, env, _1, &config->elements)},
  });

  if (!config_rc) {
    return config_rc;
  }

  *elem = std::make_shared<Element>();
  (*elem)->draw = bind(&draw, config, _1, _2);
  return OK;
}

} // namespace clip::elements::layout::box

