/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MIR_CAFFE2_IMPORTER_H
#define MIR_CAFFE2_IMPORTER_H

#include <string>
#include <memory>
#include <vector>

#include "mir/Graph.h"

namespace mir_caffe2
{

std::unique_ptr<mir::Graph> loadModel(std::string predict_net, std::string init_net,
                                      const std::vector<std::vector<int>> &input_shapes);

} // namespace mir_caffe2

#endif // MIR_CAFFE2_IMPORTER_H
