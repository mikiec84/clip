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
#pragma once
#include "sexpr.h"
#include "core/environment.h"
#include "element.h"
#include "core/layout.h"

namespace clip::elements::plot {

ReturnCode build(
    const Environment& env,
    const Expr* expr,
    ElementRef* elem);

} // namespace clip::elements::plot

