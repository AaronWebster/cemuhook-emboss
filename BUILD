# Copyright 2021 Aaron Webster
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2.0

load("@com_google_emboss//:build_defs.bzl", "emboss_cc_library")

emboss_cc_library(
    name = "protocol_emboss",
    srcs = ["protocol.emb"],
)

cc_library(
    name = "crc32_engine",
    srcs = ["crc32_engine.cc"],
    hdrs = ["crc32_engine.h"],
)

cc_binary(
    name = "protocol_test_main",
    srcs = ["protocol_test_main.cc"],
    deps = [
        ":protocol_emboss",
        "@com_google_absl//absl/base",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings",
    ],
)
