// Write a program that outputs all possibilities to put + or - or
// nothing between the numbers 1,2,…,9 (in this order) such that the
// result is 100. For example 1 + 2 + 3 - 4 + 5 + 6 + 78 + 9 = 100.

// The general logic of this solution is to try all combinations of
// operations and see of the results is 100.  There are 8 operators in
// between the 9 digits.  Each operator can have one of three values:
// '+' meaning add, '-' meaning subtract, or nothing, meaning
// accumulate digits.  Thus the operator is a ternary value (it can
// have one of three values).  We create a list of 8 operators, which
// is a list of 8 ternaary values, and treat it list an 8 digit
// ternary number.  Each digit represents an operator.  This makes a
// conventient way to try all combinations of operators.

#include <list>
#include <stdio.h>

using std::list;

#define LIST_SIZE 9

enum Operator {
    ADD,
    SUBTRACT,
    MULTIPLY_AND_ADD,
};

// Returns an operator in the sequence ADD->SUBTRACT->MULTIPLY_AND_ADD->ADD.
static enum Operator IncrementOperator(enum Operator op) {
    if (op == ADD) {
        return SUBTRACT;
    }
    if (op == SUBTRACT) {
        return MULTIPLY_AND_ADD;
    }
    if (op == MULTIPLY_AND_ADD) {
        return ADD;
    }
}

// Returns true when list wraps.
static bool IncrementOperatorList(list<Operator> *ops) {
    bool wrap;
    list<Operator>::reverse_iterator it = ops->rbegin();
    do {
        Operator op = IncrementOperator(*it);
        wrap = (op == ADD);
        *it = op;
        ++it;
    } while (it != ops->rend() && wrap);
    return wrap;
}

static void PrintOp(Operator op) {
    if (op == ADD) {
        printf(" + ");
    } else if (op == SUBTRACT) {
        printf(" - ");
    }
}

// Given a list of operators, comput the sum of the digits 1..9.
static int  ComputeSum(const list<Operator> &ops) {
    int sum = 0;
    int previous_operand = 1;
    int previous_operator = ADD;
    int operand = 1;
    Operator op = ADD;
    for (list<Operator>::const_iterator it = ops.begin();
         it != ops.end(); ++it) {
        op = *it;
        operand++;
        // MULTIPLY_AND_ADD is the accumulation of digits when there is
        // no '+' or '-' operator.
        if (op == MULTIPLY_AND_ADD) {
            previous_operand = previous_operand * 10 + operand;
        } else {
            // The current operator is not MULTIPLY_AND_ADD, and so it
            // has finished accumulating digits.  Apply the previous
            // opertor ('+' or '-') to the sum and the accumulateld
            // digits.
            if (previous_operator == ADD) {
                sum += previous_operand;
            } else if (previous_operator == SUBTRACT) {
                sum -= previous_operand;
            }
            previous_operator = op;
            previous_operand = operand;
        }
    }
    // Apply the operator to the last operand.
    if (op == ADD) {
        sum += operand;
    } else if (op == SUBTRACT) {
        sum -= operand;
    } else {
        if (previous_operator == ADD) {
            sum += previous_operand;
        } else if (previous_operator == SUBTRACT) {
            sum -= previous_operand;
        }
    }
    return sum;
}

static void InitOperatorList(list<Operator> *ops) {
    for (int i = 0; i < LIST_SIZE - 1; i++) {
        ops->push_back(ADD);
    }
}

static void OutputList(const list<Operator> &ops) {
    int operand = 1;
    printf("%d", operand);
    for (list<Operator>::const_iterator it = ops.begin();
         it != ops.end(); ++it) {
        PrintOp(*it);
        operand++;
        printf("%d", operand);
    }
}

int main (int argc, char **argv) {
    list<Operator> ops;
    InitOperatorList(&ops);

    bool done;
    do {
        int sum = ComputeSum(ops);
        if (sum == 100) {
            OutputList(ops);
            printf(" = 100\n");
        }
        done = IncrementOperatorList(&ops);
    } while (!done);
    return 0;
}
