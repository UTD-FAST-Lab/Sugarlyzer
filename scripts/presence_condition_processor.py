from z3 import *
import ast
import itertools

# Function to convert a parsed AST expression to a Z3 expression
def ast_to_z3(expr, var_dict):
    if isinstance(expr, ast.Name):
        return var_dict.setdefault(expr.id, Bool(expr.id))
    elif isinstance(expr, ast.UnaryOp) and isinstance(expr.op, ast.Not):
        return Not(ast_to_z3(expr.operand, var_dict))
    elif isinstance(expr, ast.Call):
        func_name = expr.func.id
        args = [ast_to_z3(arg, var_dict) for arg in expr.args]
        if func_name == "And":
            return And(*args)
        elif func_name == "Or":
            return Or(*args)
        elif func_name == "Not":
            return Not(args[0])
    raise ValueError(f"Unsupported expression: {ast.dump(expr)}")

def simplify_presence_condition(condition_str):
    # Parse the condition string into a Python AST
    expr_ast = ast.parse(condition_str, mode='eval').body
    
    # Convert AST to Z3 expression
    var_dict = {}
    condition = ast_to_z3(expr_ast, var_dict)
    
    # Extract all variables from the formula
    all_vars = set(var_dict.values())
    
    # Determine variables to eliminate (those starting with "DEF__")
    eliminate_vars = [v for v in all_vars if v.decl().name().startswith("DEF__")]
    
    # Variables to keep (those not starting with "DEF__")
    kept_vars = [v for v in all_vars if not v.decl().name().startswith("DEF__")]
    
    # Existentially quantify over the unwanted variables
    simplified_condition = simplify(Exists(eliminate_vars, condition))
    
    return simplified_condition, kept_vars

def get_all_solutions(simplified_condition, keep_vars):
    # Create solver
    solver = Solver()
    solver.add(simplified_condition)
    
    # Generate all possible assignments for the kept variables
    solutions = []
    
    # Generate all possible combinations of True/False for the kept variables
    possible_assignments = list(itertools.product([True, False], repeat=len(keep_vars)))
    
    for assignment in possible_assignments:
        # Create a constraint for this specific assignment
        assignment_constraint = []
        for var, value in zip(keep_vars, assignment):
            if value:
                assignment_constraint.append(var)
            else:
                assignment_constraint.append(Not(var))
        
        # Check if this assignment satisfies the simplified condition
        temp_solver = Solver()
        temp_solver.add(simplified_condition)
        temp_solver.add(And(*assignment_constraint))
        
        if temp_solver.check() == sat:
            solutions.append(dict(zip([v.decl().name() for v in keep_vars], assignment)))
    
    return solutions

if __name__ == "__main__":
    # Example with DEF__ variables
    condition_str = "Or(Or(And(Or (And (Not(DEF__STDLIB_H) , (DEF___STRICT_ANSI__) , Not(DEF___need_malloc_and_calloc) , Not(DEF___USE_EXTERN_INLINES) , (DEF_HAVE_TLSV1_X))))),Or(And(Or (And (Not(DEF__STDLIB_H) , Not(DEF___STRICT_ANSI__) , Not(DEF___need_malloc_and_calloc) , Not(DEF___USE_EXTERN_INLINES) , (DEF_HAVE_TLSV1_X))))))"
    
    simplified_condition, kept_vars_z3 = simplify_presence_condition(condition_str)
    print("Simplified condition:", simplified_condition)
    print("Kept variables:", [v.decl().name() for v in kept_vars_z3])
    
    solutions = get_all_solutions(simplified_condition, kept_vars_z3)
    print(f"\nFound {len(solutions)} solution(s):")
    for i, solution in enumerate(solutions, 1):
        print(f"Solution {i}:", solution)