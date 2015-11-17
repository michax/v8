// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_COMPILER_JS_CALL_REDUCER_H_
#define V8_COMPILER_JS_CALL_REDUCER_H_

#include "src/base/flags.h"
#include "src/compiler/graph-reducer.h"

namespace v8 {
namespace internal {
namespace compiler {

// Forward declarations.
class CommonOperatorBuilder;
class JSGraph;
class JSOperatorBuilder;
class SimplifiedOperatorBuilder;


// Performs strength reduction on {JSCallFunction} nodes, which might allow
// inlining or other optimizations to be performed afterwards.
class JSCallReducer final : public Reducer {
 public:
  // Flags that control the mode of operation.
  enum Flag {
    kNoFlags = 0u,
    kDeoptimizationEnabled = 1u << 0,
  };
  typedef base::Flags<Flag> Flags;

  JSCallReducer(JSGraph* jsgraph, Flags flags)
      : jsgraph_(jsgraph), flags_(flags) {}

  Reduction Reduce(Node* node) final;

 private:
  Reduction ReduceFunctionPrototypeApply(Node* node);
  Reduction ReduceFunctionPrototypeCall(Node* node);
  Reduction ReduceJSCallFunction(Node* node);

  Graph* graph() const;
  Flags flags() const { return flags_; }
  JSGraph* jsgraph() const { return jsgraph_; }
  Isolate* isolate() const;
  CommonOperatorBuilder* common() const;
  JSOperatorBuilder* javascript() const;
  SimplifiedOperatorBuilder* simplified() const;

  JSGraph* const jsgraph_;
  Flags const flags_;
};

DEFINE_OPERATORS_FOR_FLAGS(JSCallReducer::Flags)

}  // namespace compiler
}  // namespace internal
}  // namespace v8

#endif  // V8_COMPILER_JS_CALL_REDUCER_H_
