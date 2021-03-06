/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
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

#include <circlechef/RawModel.h>
#include <circlechef/RecipeChef.h>

#include <memory>
#include <iostream>

int entry(int argc, char **argv)
{
  if (argc != 3)
  {
    std::cerr << "ERROR: Failed to parse arguments" << std::endl;
    std::cerr << std::endl;
    std::cerr << "USAGE: " << argv[0] << " [circle] [output]" << std::endl;
    return 255;
  }

  // Load TF lite model from a circle file
  std::unique_ptr<circlechef::RawModel> rawmodel = circlechef::load_circle(argv[1]);
  if (rawmodel == nullptr)
  {
    std::cerr << "ERROR: Failed to load circle '" << argv[1] << "'" << std::endl;
    return 255;
  }

  const circle::Model *tflmodel = rawmodel->model();
  if (tflmodel == nullptr)
  {
    std::cerr << "ERROR: Failed to load circle '" << argv[1] << "'" << std::endl;
    return 255;
  }

  // Generate ModelRecipe recipe
  std::unique_ptr<circlechef::ModelRecipe> recipe = circlechef::generate_recipe(tflmodel);
  if (recipe.get() == nullptr)
  {
    std::cerr << "ERROR: Failed to generate recipe" << std::endl;
    return 255;
  }

  // Save to a file
  bool result = circlechef::write_recipe(argv[2], recipe);
  if (!result)
  {
    std::cerr << "ERROR: Failed to write to recipe '" << argv[2] << "'" << std::endl;
    return 255;
  }
  return 0;
}
