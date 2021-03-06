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
#include "color_palette.h"

namespace clip {

const std::unordered_map<
    std::string_view,
    std::vector<std::string_view>>
    COLOR_PALETTES = {

  // the "fnordmetric" color palette
  {
    "fnord",
    {
      "#4572a7",
      "#aa4643",
      "#db843d",
      "#89a54e",
      "#80699b",
      "#3d96ae",
    }
  },

  // the "zhang" color palette
  // source: https://www.nature.com/articles/s41586-019-1364-3
  {
    "zhang",
    {
      "#6a88c4",
      "#75c042",
      "#efeb52",
      "#f5a325",
      "#f92d23",
      "#9551a1",
      "#323085",
      "#a2a2a2",
    }
  }

};

ReturnCode color_palette_default(const std::string& name, ColorPalette* colors) {
  auto iter = COLOR_PALETTES.find(name);
  if (iter == COLOR_PALETTES.end()) {
    std::string valid_values;

    for (const auto& v : COLOR_PALETTES) {
      valid_values += fmt::format(
          "  - {}\n",
          std::string(v.first.data(), v.first.size()));
    }

    return errorf(
        ERROR,
        "invalid value to <color-palette-name>; got '{}' but expected one of:\n{}",
        name,
        valid_values);
  }

  colors->clear();

  for (const auto& v : iter->second) {
    Color c;
    c.parse(std::string(v.data(), v.length()));
    colors->push_back(c);
  }

  return OK;
}

ColorPalette color_palette_default() {
  ColorPalette c;
  color_palette_default("fnord", &c);
  return c;
}

} // namespace clip

