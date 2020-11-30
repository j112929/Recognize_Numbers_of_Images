/**
 * A simple test program helps you to debug your easynn implementation.
 */

#include <stdio.h>
#include "src/libeasynn.h"
int main() {


    /*program *prog = create_program();

    int inputs0[] = {};
    int inputs2[] = {0};
    append_expression(prog, 0, "x", "Input", inputs0, 0);
    append_expression(prog, 1, "f", "Linear", inputs0, 1);

    int inputs1[] = {0, 0};
//    append_expression(prog, 11, "", "Mul", inputs1, 2);
    evaluation *eval = build(prog);
    add_kwargs_double(eval, "in_features", 2);
    add_kwargs_double(eval, "out_features", 2);
    size_t shape1[] = {2,2};
    size_t shape2[] = {2};
    size_t shape3[] = {2,2};
    double data1[4] = {0.306221,0.055236,0.428912,0.106088};
    double data2[2] = {0.233890,0.464297};
    double data3[4] = {0.225397,0.193471,0.456060,0.996765};
    add_op_param_ndarray(prog, "weight", 2, shape1,  data1);
    add_op_param_ndarray(prog, "bias", 1, shape2,  data2);
    add_kwargs_ndarray(eval, "x", 2, shape3,  data3);
    int dim = 0;
    size_t *shape = shape;
    double *data = data;
    if (execute(eval, &dim, &shape, &data) != 0)
    {
        printf("evaluation fails\n");
        return -1;
    }


    if (dim == 0)
        printf("res = %f\n", data[0]);
    else
        printf("result as tensor is not supported yet\n");*/
    return 0;
}
