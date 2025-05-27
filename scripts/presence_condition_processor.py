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

def simplify_presence_condition(condition_str, explicitly_keep=None):
    """
    Simplify a presence condition by removing variables starting with DEF__,
    optionally keeping specific variables regardless of their naming.
    
    Args:
        condition_str: The condition string to simplify
        explicitly_keep: Optional set of variable names to keep regardless of their prefix
    
    Returns:
        simplified_condition: The simplified Z3 condition
        kept_vars: List of Z3 variables that are kept
    """
    # Set default value for explicitly_keep if None
    if explicitly_keep is None:
        explicitly_keep = set()
    
    # Parse the condition string into a Python AST
    expr_ast = ast.parse(condition_str, mode='eval').body
    
    # Convert AST to Z3 expression
    var_dict = {}
    condition = ast_to_z3(expr_ast, var_dict)
    
    # Extract all variables from the formula
    all_vars = set(var_dict.values())
    
    # Determine variables to eliminate (those starting with "DEF__" AND not in explicitly_keep)
    eliminate_vars = [v for v in all_vars if (v.decl().name().startswith("DEF__") and 
                                             v.decl().name() not in explicitly_keep)]
    
    # Variables to keep (those not starting with "DEF__" OR in explicitly_keep)
    kept_vars = [v for v in all_vars if (not v.decl().name().startswith("DEF__") or 
                                        v.decl().name() in explicitly_keep)]
    
    # # Existentially quantify over the unwanted variables
    # simplified_condition = simplify(Exists(eliminate_vars, condition))

    if eliminate_vars:
        # Recreate bound vars
        bound_vars = [Bool(v.decl().name()) for v in eliminate_vars]
        substitutions = [(v, b) for v, b in zip(eliminate_vars, bound_vars)]
        condition_substituted = substitute(condition, substitutions)
        simplified_condition = simplify(Exists(bound_vars, condition_substituted))
    else:
        # No vars to eliminate, use the original condition
        simplified_condition = simplify(condition)
    
    return simplified_condition, kept_vars

def get_all_solutions(simplified_condition, keep_vars):
    # Create solver
    solver = Solver()
    solver.add(simplified_condition)
    
    # Generate all possible assignments for the kept variables
    solutions = []
    
    # Generate all possible combinations of True/False for the kept variables
    possible_assignments = list(itertools.product([True, False], repeat=len(keep_vars)))
    
    satisfied_once = False
    
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
            satisfied_once = True
    
    if satisfied_once:
        return solutions
    else:
        return None

if __name__ == "__main__":    
    # case 1: remove DEF__ variables
   with open('./input.txt', 'r') as f:
       condition_str = f.read()
   condition_str = condition_str.replace("\\n", "")
   condition_str = condition_str.replace("\n", "")
   condition_str = condition_str.replace("    ", " ")
   print(condition_str)
   # simplified_condition, kept_vars_z3 = simplify_presence_condition(condition_str)
   # print("Simplified condition:", simplified_condition)
   # print("Kept variables:", [v.decl().name() for v in kept_vars_z3])
   
   # solutions = get_all_solutions(simplified_condition, kept_vars_z3)
# print(f"\nFound {len(solutions)} solution(s):")
# for i, solution in enumerate(solutions, 1):
#     print(f"Solution {i}:", solution)


# Test case 2: Keep specific DEF__ variables
   explicitly_keep = {""}  # Explicitly keep DEF__c
   simplified_condition, kept_vars_z3 = simplify_presence_condition(condition_str, explicitly_keep)
   print("Simplified condition:", simplified_condition)
   print("Kept_Vars variables:", [v.decl().name() for v in kept_vars_z3])
   
   solutions = get_all_solutions(simplified_condition, kept_vars_z3)
   
   if solutions is None:
       print("No solutions found.")
   else:
       print(f"Found {len(solutions)} solution(s):")
       for i, solution in enumerate(solutions, 1):
           print(f"Solution {i}:", solution)
