#include "program.h"
#include "evaluation.h"
extern std::map<std::string,double> contextMap;
program::program()
{
}

void program::append_expression(
    int expr_id,
    const char *op_name,
    const char *op_type,
    int inputs[],
    int num_inputs)
{
    printf("prog.append_expression expr_id %d, op_name %s, op_type %s, inputs %d \n",
            expr_id, op_name, op_type, num_inputs);
    expression *exp = new expression(expr_id, op_name, op_type, inputs, num_inputs);
    vec.push_back(*exp);
}

int program::add_op_param_double(
    const char *key,
    double value)
{
    printf("prog.add_op_param_double  key= %s, value= %f\n",
           key, value);
    keyStr = key;
    printf("prog.add_op_param_double --------------- key= %s \n", keyStr.data());
    contextMap[key] = value;
    printf("prog.add_op_param_double   value= %f\n", contextMap[keyStr]);
    printf("prog.add_op_param_double --------------- key= %s \n", keyStr.data());
    return 0;
}

int program::add_op_param_ndarray(
    const char *key,
    int dim,
    size_t shape[],
    double data[])
{
    return -1;
}

evaluation *program::build()
{
    evaluation *eval = new evaluation(vec);
    eval->keyStr = keyStr;
    return eval;
}
