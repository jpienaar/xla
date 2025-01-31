/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef XLA_STREAM_EXECUTOR_TPU_STATUS_HELPER_H_
#define XLA_STREAM_EXECUTOR_TPU_STATUS_HELPER_H_

#include "tsl/c/tsl_status.h"
#include "tsl/platform/status.h"

class StatusHelper {
 public:
  StatusHelper() : c_status(TSL_NewStatus()) {}

  ~StatusHelper() { TSL_DeleteStatus(c_status); }

  static tsl::Status FromC(  // TENSORFLOW_STATUS_OK
      TSL_Status* const c_status) {
    if (TSL_GetCode(c_status) == TSL_Code::TSL_OK) {
      return ::tsl::OkStatus();
    } else {
      return tsl::Status(  // TENSORFLOW_STATUS_OK
          absl::StatusCode(TSL_GetCode(c_status)), TSL_Message(c_status));
    }
  }

  bool ok() const { return (TSL_GetCode(c_status) == TSL_Code::TSL_OK); }

  tsl::Status status() const {  // TENSORFLOW_STATUS_OK
    return FromC(c_status);
  }

  TSL_Status* const c_status;  // NOLINT
};

#endif  // XLA_STREAM_EXECUTOR_TPU_STATUS_HELPER_H_
