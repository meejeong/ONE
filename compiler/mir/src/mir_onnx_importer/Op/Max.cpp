/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "Max.h"

#include "ONNXHelpers.h"

#include "mir/ops/MaxOp.h"

namespace mir_onnx
{

static void convertMaxGeneric(const onnx::NodeProto &onnx_node, ConverterContext *context)
{
  std::vector<mir::Operation::Output *> inputs = context->getNodeInputs(onnx_node);
  if (inputs.size() != 2)
  {
    throw std::runtime_error{"Unsupported number of inputs for Max operator"};
  }
  mir::Graph *graph = context->getGraph();
  auto result = createOp<mir::ops::MaxOp>(graph, inputs[0], inputs[1])->getOutput(0);

  context->setNodeOutputs(onnx_node, {result});
}

void convertMaxV1(const onnx::NodeProto &onnx_node, ConverterContext *context)
{
  convertMaxGeneric(onnx_node, context);
}

void convertMaxV6(const onnx::NodeProto &onnx_node, ConverterContext *context)
{
  convertMaxGeneric(onnx_node, context);
}

void convertMaxV8(const onnx::NodeProto &onnx_node, ConverterContext *context)
{
  convertMaxGeneric(onnx_node, context);
}

} // namespace mir_onnx
