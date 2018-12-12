/**
 * This file is part of the "plotfx" project
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
#include "dimension.h"
#include <iostream>

namespace plotfx {

const DimensionConfig* dimension_find(
    const DimensionMap& map,
    const std::string& key) {
  const auto& iter = map.find(key);
  if (iter == map.end()) {
    return nullptr;
  } else {
    return &iter->second;
  }
}

void dimension_add(
    DimensionMap* map,
    const std::string& key) {
  if (dimension_find(*map, key)) {
    return;
  }

  DimensionConfig d;
  d.key = key;
  map->emplace(d.key, d);
}

DimensionMapFn<Color> dimension_map_color_continuous() {
  return [] (const auto& dimension, const auto& value, Color* color) {
    *color = dimension.colors.get(domain_translate(dimension.domain, value));
    return OK;
  };
}

DimensionMapFn<Color> dimension_map_color_discrete() {
  return [] (const auto& dimension, const auto& value, Color* color) {
    auto idx =
        domain_translate(dimension.domain, value) *
        domain_cardinality(dimension.domain);

    *color = dimension.colors.get(idx);
    return OK;
  };
}

ReturnCode dimension_resolve(
    const DataFrame& data,
    DimensionConfig* dimension) {
  const DataColumn* column = nullptr;
  if (auto rc = column_find(data, dimension->key, &column); !rc) {
    return rc;
  }

  domain_fit(column->data, &dimension->domain);
  return OK;
}

ReturnCode dimension_resolve_all(
    const DataFrame& data,
    DimensionMap* map) {
  for (auto& e : *map) {
    if (auto rc = dimension_resolve(data, &e.second); !rc) {
      return rc;
    }
  }

  return OK;
}

} // namespace plotfx

