//===----------------------------------------------------------------------===//
//
//                         DuckDB
//
// parser/parser.hpp
//
// Author: Hannes Mühleisen & Mark Raasveldt
//
//===----------------------------------------------------------------------===//

#pragma once

#include <algorithm>
#include <vector>

#include "common/exception.hpp"
#include "common/internal_types.hpp"
#include "optimizer/rule.hpp"
#include "parser/expression/cast_expression.hpp"
#include "parser/expression/constant_expression.hpp"

namespace duckdb {

class ConstantCastRule : public OptimizerRule {
  public:
	ConstantCastRule() {
		root = std::unique_ptr<OptimizerNode>(
		    new OptimizerNodeExpression(ExpressionType::OPERATOR_CAST));
		root->children.push_back(std::unique_ptr<OptimizerNode>(
		    new OptimizerNodeExpression(ExpressionType::VALUE_CONSTANT)));
		root->child_policy = ChildPolicy::UNORDERED;
	}

	std::unique_ptr<AbstractExpression>
	Apply(AbstractExpression &root,
	      std::vector<AbstractExpression *> &bindings) {
		auto &cast_expr = (CastExpression &)root;
		auto const_expr =
		    reinterpret_cast<ConstantExpression *>(root.children[0].get());
		return make_unique<ConstantExpression>(
		    const_expr->value.CastAs(cast_expr.return_type));
	};
};

} // namespace duckdb
