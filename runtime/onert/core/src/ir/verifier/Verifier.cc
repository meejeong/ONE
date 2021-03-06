/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include "Verifier.h"

#include "ir/Graph.h"
#include "ir/OperationIndexMap.h"

#include "util/logging.h"

namespace onert
{
namespace ir
{
namespace verifier
{

//
// DAGChecker
//

bool DAGChecker::verify(const Graph &graph) const
{
  auto &operations = graph.operations();
  bool cyclic = false;

  OperationIndexMap<bool> visited;
  operations.iterate(
      [&](const OperationIndex &index, const Operation &) { visited[index] = false; });
  OperationIndexMap<bool> on_stack = visited; // Copy from visited

  std::function<void(const OperationIndex &index, const Operation &)> dfs_recursive =
      [&](const OperationIndex &index, const Operation &node) -> void {
    if (on_stack[index])
      cyclic = true;
    if (visited[index])
      return;
    visited[index] = true;
    on_stack[index] = true;

    for (auto output : node.getOutputs() | Remove::DUPLICATED)
    {
      const auto &operand = graph.operands().at(output);
      for (const auto &use : operand.getUses())
      {
        dfs_recursive(use, graph.operations().at(use));
      }
    }

    on_stack[index] = false;
  };

  operations.iterate(dfs_recursive);

  return !cyclic;
}

//
// EdgeConsistencyVerifier
//

bool EdgeConsistencyChecker::verify(const Graph &graph) const
{
  auto &operations = graph.operations();
  uint32_t mismatches = 0;
  operations.iterate([&](const OperationIndex &index, const Operation &node) {
    for (auto operand_index : node.getInputs() | ir::Remove::UNDEFINED)
    {
      auto &operand = graph.operands().at(operand_index);
      mismatches += (operand.getUses().contains(index) ? 0 : 1);
    }
    for (auto operand_index : node.getOutputs())
    {
      auto &operand = graph.operands().at(operand_index);
      mismatches += (operand.getDef().contains(index) ? 0 : 1);
    }
  });
  return mismatches == 0;
}

} // namespace verifier
} // namespace ir
} // namespace onert
