#ifndef AST_EVALUATOR_HH
#define AST_EVALUATOR_HH

#include "../utils/errors.hh"
#include "nodes.hh"

namespace ast{
    class ASTEvaluator: public ConstASTIntVisitor{
        int32_t visit(const class IntegerLiteral & l){
            return l.value;
        }

        int32_t visit(const class Sequence & s){
            std::vector<ast::types::Expr*> exprs = s.get_exprs();

            if(exprs.empty()){ utils::error("empty sequence");}

            int32_t res = 0;
            for(Expr* expr : exprs){
                res = expr->accept(*this);
            }
            return res;
        }

        int32_t visit(const class IfThenElse & ifthel){
            int32_t res = -1;
            if(ifthel.get_condition().accept(*this)){
                res = ifthel.get_then_part().accept(*this);
            }else{
                res = ifthel.get_else_part().accept(*this);
            }
            return res;
        }

        int32_t visit(const class BinaryOperator & op){
            switch (op.op)
            {
            case o_plus:
                return op.get_left().accept(*this) + op.get_right().accept(*this);
                break;
            case o_minus:
                return op.get_left().accept(*this) - op.get_right().accept(*this);
                break;
            case o_divide:
                return op.get_left().accept(*this) / op.get_right().accept(*this);
                break;
            case o_times:
                return op.get_left().accept(*this) * op.get_right().accept(*this);
                break;
            case o_eq:
                return op.get_left().accept(*this) == op.get_right().accept(*this);
                break;
            case o_ge:
                return op.get_left().accept(*this) >= op.get_right().accept(*this);
                break;
            case o_gt:
                return op.get_left().accept(*this) > op.get_right().accept(*this);
                break;
            case o_le:
                return op.get_left().accept(*this) <= op.get_right().accept(*this);
                break;
            case o_lt:
                return op.get_left().accept(*this) < op.get_right().accept(*this);
                break;
            case o_neq:
                return op.get_left().accept(*this) != op.get_right().accept(*this);
                break;
            default:
                utils::error("uknown operator");
            }
        }
    }
}

#endif