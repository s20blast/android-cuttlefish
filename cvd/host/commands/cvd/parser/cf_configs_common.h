/*
 * Copyright (C) 2022 The Android Open Source Project
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

#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <json/json.h>

#include "common/libs/utils/result.h"

#define GENERATE_MVP_FLAGS_ONLY true

namespace cuttlefish {

Result<void> ValidateTypo(const Json::Value& root,
                          const std::map<std::string, Json::ValueType>& map);

Result<void> ValidateIntConfig(
    const Json::Value& instances, const std::string& group,
    const std::string& json_flag,
    std::function<Result<void>(int)> validate_config);

Result<void> ValidateIntConfigSubGroup(
    const Json::Value& instances, const std::string& group,
    const std::string& subgroup, const std::string& json_flag,
    std::function<Result<void>(int)> validate_config);

Result<void> ValidateStringConfig(
    const Json::Value& instances, const std::string& group,
    const std::string& json_flag,
    std::function<Result<void>(const std::string&)> validate_config);

Result<void> ValidateStringConfigSubGroup(
    const Json::Value& instances, const std::string& group,
    const std::string& subgroup, const std::string& json_flag,
    std::function<Result<void>(const std::string&)> validate_config);

template <typename T>
Result<void> InitConfig(Json::Value& root, const T& default_value,
                        const std::vector<std::string>& selectors) {
  const int size = selectors.size();
  CF_EXPECT(size > 0, "No keys given for initializing config");
  int i = 0;
  Json::Value* traverse = &root;
  for (const auto& selector : selectors) {
    if (!traverse->isMember(selector)) {
      if (i == size - 1) {
        (*traverse)[selector] = default_value;
      } else {
        (*traverse)[selector] = Json::Value();
      }
    }
    traverse = &(*traverse)[selector];
    ++i;
  }
  return {};
}

void InitIntConfigSubGroupVector(Json::Value& instances,
                                 const std::string& group,
                                 const std::string& subgroup,
                                 const std::string& json_flag,
                                 int default_value);

Result<std::string> GenerateGflag(const Json::Value& instances,
                                  const std::string& gflag_name,
                                  const std::vector<std::string>& selectors);

std::vector<std::string> MergeResults(std::vector<std::string> first_list,
                                      std::vector<std::string> scond_list);

void MergeTwoJsonObjs(Json::Value& dst, const Json::Value& src);

}  // namespace cuttlefish
