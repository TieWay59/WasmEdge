// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2022 Second State INC

#include "host/challenge_tieway59/tw59func.h"

namespace WasmEdge {
namespace Host {

Expect<void> HostFuncExampleSetClassID::body(
    [[maybe_unused]] Runtime::Instance::MemoryInstance *MemInst, uint32_t CID) {
  Env.ClassID = CID;
  return {};
}

Expect<uint32_t>
HostFuncExampleAddStudent::body(Runtime::Instance::MemoryInstance *MemInst,
                                uint32_t StudentPtr, uint32_t StudentLen) {
  // Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  char *Student = MemInst->getPointer<char *>(StudentPtr);
  std::string NewStudent;
  std::copy_n(Student, StudentLen, std::back_inserter(NewStudent));
  Env.Students.push_back(std::move(NewStudent));
  return Env.Students.size();
}

Expect<void>
HostFuncExampleSetClassName::body(Runtime::Instance::MemoryInstance *MemInst,
                                  uint32_t ClassNamePtr,
                                  uint32_t ClassNameLen) {
  // Check memory instance from module.
  if (MemInst == nullptr) {
    return Unexpect(ErrCode::ExecutionFailed);
  }

  char *ClassName = MemInst->getPointer<char *>(ClassNamePtr);
  std::string NewClassName;
  std::copy_n(ClassName, ClassNameLen, std::back_inserter(NewClassName));
  Env.ClassName = std::move(NewClassName);
  return {};
}

Expect<void> HostFuncExamplePrint::body(
    [[maybe_unused]] Runtime::Instance::MemoryInstance *MemInst) {
  std::cout << "Class ID: " << Env.ClassID << std::endl;
  std::cout << "Class Name: " << Env.ClassName << std::endl;
  for (auto &Student : Env.Students) {
    std::cout << "Student: " << Student << std::endl;
  }
  return {};
}

Expect<uint32_t> HostFuncExampleBinaryGCD::body(
    [[maybe_unused]] Runtime::Instance::MemoryInstance *MemInst, uint32_t a,
    uint32_t b) {

  /* GCD(0, b) == b; GCD(a, 0) == a,
     GCD(0, 0) == 0 */
  if (a == 0)
    return b;
  if (b == 0)
    return a;

  /*Finding K, where K is the
    greatest power of 2
    that divides both a and b. */
  int k;
  for (k = 0; ((a | b) & 1) == 0; ++k) {
    a >>= 1;
    b >>= 1;
  }

  /* Dividing a by 2 until a becomes odd */
  while ((a & 1) == 0)
    a >>= 1;

  /* From here on, 'a' is always odd. */
  do {
    /* If b is even, remove all factor of 2 in b */
    while ((b & 1) == 0)
      b >>= 1;

    /* Now a and b are both odd.
       Swap if necessary so a <= b,
       then set b = b - a (which is even).*/
    if (a > b) {
      // Swap u and v.
      auto t = a;
      a = b;
      b = t;
    }

    b = (b - a);
  } while (b != 0);

  /* restore common factors of 2 */
  return a << k;
}

} // namespace Host
} // namespace WasmEdge