// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#pragma once

#include "host/challenge_tieway59/tw59env.h"
#include "runtime/importobj.h"

#include <cstdint>

namespace WasmEdge {
namespace Host {

class HostFuncExampleModule : public Runtime::ImportObject {
public:
  HostFuncExampleModule();

  HostFuncExampleEnvironment &getEnv() { return Env; }

private:
  HostFuncExampleEnvironment Env;
};

} // namespace Host
} // namespace WasmEdge