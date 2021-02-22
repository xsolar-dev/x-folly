/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <folly/portability/Filesystem.h>

#include <folly/portability/GMock.h>
#include <folly/portability/GTest.h>

using namespace testing;

class FilesystemTest : public Test {};

TEST_F(FilesystemTest, lexically_normal) {
  // cases from cppreference.com
  // implementation either std::filesystem or boost::filesystem
  auto gold = folly::fs::which == folly::fs::which_enum::std;
  auto sep = std::string({folly::fs::path::preferred_separator});
  EXPECT_THAT(
      folly::fs::lexically_normal("foo/./bar/..").native(),
      Eq(folly::fs::path(gold ? "foo" + sep : "foo").native()));
  EXPECT_THAT(
      folly::fs::lexically_normal("foo/.///bar/../").native(),
      Eq(folly::fs::path(gold ? "foo" + sep : "foo" + sep + ".").native()));
}