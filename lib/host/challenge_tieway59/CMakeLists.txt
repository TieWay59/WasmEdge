# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2019-2022 Second State INC

wasmedge_add_library(wasmedgeHostModuleHostFuncExample
        tw59func.cpp
        tw59module.cpp
        )

target_link_libraries(wasmedgeHostModuleHostFuncExample
        PUBLIC
        wasmedgeCommon
        wasmedgeSystem
        )