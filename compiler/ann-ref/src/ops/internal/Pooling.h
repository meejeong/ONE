/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __POOLING_H__
#define __POOLING_H__

#include "Shape.h"

#include <cstdint>

bool genericPoolingPrepare(const Shape &input, int32_t padding_left, int32_t padding_right,
                           int32_t padding_top, int32_t padding_bottom, int32_t stride_width,
                           int32_t stride_height, int32_t filter_width, int32_t filter_height,
                           Shape *output);


#endif // __POOLING_H__
