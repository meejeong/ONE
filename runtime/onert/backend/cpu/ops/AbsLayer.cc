/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "AbsLayer.h"

#include "OperationUtils.h"

#include <cker/operation/Elementwise.h>

namespace onert
{
namespace backend
{
namespace cpu
{
namespace ops
{

AbsLayer::AbsLayer() : _input(nullptr), _output(nullptr)
{
  // DO NOTHING
}

void AbsLayer::absFloat32()
{
  nnfw::cker::Abs(getTensorShape(_input), reinterpret_cast<const float *>(_input->buffer()),
                  getTensorShape(_output), reinterpret_cast<float *>(_output->buffer()));
}

void AbsLayer::absQuant8() { throw std::runtime_error{"NYI"}; }

void AbsLayer::configure(const Tensor *input, Tensor *output)
{
  _input = input;
  _output = output;
}

void AbsLayer::run()
{
  if (_input->data_type() == OperandType::FLOAT32)
  {
    absFloat32();
  }
  else if (_input->data_type() == OperandType::QUANT_UINT8_ASYMM)
  {
    absQuant8();
  }
}

} // namespace ops
} // namespace cpu
} // namespace backend
} // namespace onert
