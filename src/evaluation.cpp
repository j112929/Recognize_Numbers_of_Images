#include <assert.h>
#include <iostream>
#include "evaluation.h"
//#include "eval_input.h"
//#include "eval_const.h"

std::map<std::string, double> contextMap;
std::map<string, tensor> contextArrMap ;

evaluation::evaluation(const std::vector<expression> &exprs)
        : /*result_(0)*/exps(exprs) {
}

void evaluation::add_kwargs_double(
        const char *key,
        double value) {
    printf("eval->add_kwargs_double key=%s\n", key);
    keyStr = key;
    printf("eval->add_kwargs_double key1=%s\n", keyStr.data());
    contextMap[key] = value;
    printf("eval->add_kwargs_double %f\n", value);
    tensor *t = new tensor(value);
    contextArrMap[key] = *t;
}

void evaluation::add_kwargs_ndarray(
        const char *key,
        int dim,
        size_t shape[],
        double data[]) {
    /*printf("evaluation.add_kwargs_ndarray  key %s, value %p dim %d (",
            key, data, dim);
    for (int i = 0; i != dim; ++i)
        printf("%zu,", shape[i]);
    printf(")\n");*/
    keyStr = key;
    tensor *t = new tensor(dim, shape, data);
    contextArrMap[key] = *t;
}

int evaluation::execute() {
    map<string, double> key_str;
    string keys_;
//    std::vector<int> t_i;
    double val_ = 0.0;

    map<int, tensor> key_str_arr;
//    std::vector<int> t_i;
    variables_.clear();
    for (auto &i : exps) {
        printf("+++execute++++exp_id:%d\n", i.exp_id);
        if (0 != i.opname.compare("")) {
            if (0 == i.optype.compare("Input")) {
//                Input(i, key_str, keys_, val_);
                Input1(i, key_str_arr);
//                ops_.push_back(std::make_shared<eval_input>(i));
            }
        } else if (0 == i.opname.compare("")) {
            if (0 == i.optype.compare("Const")) {
//                Const(i, key_str, keys_, val_);
                Const1(i, key_str_arr);
//                ops_.push_back(std::make_shared<eval_const>(i));
            } else if (0 == i.optype.compare("Add")) {
//                Add(i, key_str, keys_, val_);
                Add1(i, key_str_arr);
            } else if (0 == i.optype.compare("Sub")) {
//                Sub(t_i, i, key_str, keys_, val_);
                Sub1(i, key_str_arr);
            } else if (0 == i.optype.compare("Mul")) {
//                Mul(i, key_str, keys_, val_);
                Mul1(i, key_str_arr);
            }
        }
    }
    /*for (auto &op: ops_) {
        op->eval(variables_, kwargs_);
    }*/
//    printf("val_:%f\n",val_);
//    if(val_ != 0.0){
    /*printf("val_:%f\n",val_);
    result_ = val_;
    key_str.clear();*/
//    } else {
    printf("after size:%lu, first data:%f\n", sizeof(key_str_arr[key_expr_id]), key_str_arr[key_expr_id].data_[0]);
    variables_[key_expr_id] = key_str_arr[key_expr_id];
    printf("after res size:%lu, first data:%f\n", sizeof(variables_[key_expr_id]),
           variables_[key_expr_id].data_[0]);
    key_str_arr.clear();
    contextArrMap.clear();
//    }


    return 0;
}

void evaluation::Mul(expression &i, map<string, double> &key_str, string &keys_, double &val_) {
    val_ = 1.0;
    for (auto q : i.input) {
        keys_ = "t" + to_string(q);
        val_ *= key_str[keys_];
    }
    keys_ = "t" + to_string(i.exp_id);
    key_str[keys_] = val_;
//    key_op_type = 2;
}

void evaluation::Sub(vector<int> &t_i, expression &i, map<string, double> &key_str, string &keys_, double &val_) {
    val_ = 0.0;
    t_i = i.input;
    keys_ = "t" + to_string(t_i[0]);
    val_ = key_str[keys_];
    keys_ = "t" + to_string(t_i[1]);
    val_ = val_ - key_str[keys_];
    keys_ = "t" + to_string(i.exp_id);
    key_str[keys_] = val_;
//    key_op_type = 2;
}

void evaluation::Add(expression &i, map<string, double> &key_str, string &keys_, double &val_) {
    val_ = 0.0;
    for (auto q : i.input) {
        keys_ = "t" + to_string(q);
        val_ += key_str[keys_];
    }
    keys_ = "t" + to_string(i.exp_id);
    key_str[keys_] = val_;
//    key_op_type = 2;
}

void evaluation::Const(expression &i, map<string, double> &key_str, string &keys_, double &val_) {
    keys_ = "t" + to_string(i.exp_id);
    key_str[keys_] = contextMap["value"];
    val_ = key_str[keys_];
//    key_op_type = 0;
}

void evaluation::Input(expression &i, map<string, double> &key_str, string &keys_, double &val_) {
    keys_ = "t" + to_string(i.exp_id);
    key_str[keys_] = contextMap[i.opname];
    val_ = key_str[keys_];
//    key_op_type = 1;
}

void evaluation::Input1(expression &i, std::map<int, tensor> &key_str_arr) {
    key_str_arr[i.exp_id] = contextArrMap[i.opname];
//    kwargs_[i.opname] = contextArrMap[i.opname];
    printf("Input size:%lu\n", sizeof(contextArrMap[i.opname].shape_.size()));
}

void evaluation::Const1(expression &i, std::map<int, tensor> &key_str_arr) {

    try {
        key_str_arr[i.exp_id] = contextArrMap[to_string(i.exp_id)];
//    kwargs_["value"] = contextArrMap["value"];
        tensor t = key_str_arr[i.exp_id];
        double *d = t.get_data_array();
        printf("Const1 *d:%lf\n", *d);
        printf("Const1 size:%lu\n", sizeof(contextArrMap[i.opname]));
    }catch (exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void evaluation::Add1(expression &i, std::map<int, tensor> &key_str_arr) {
    tensor t0;
    tensor t1;
    tensor t2;
    vector<double> a1;
    vector<double> a2;
    std::vector<int> input = i.input;
    int j = 0;
    printf("Add1 input.size=%lu\n", input.size());
    printf("Add1 key_expr_id=%d \n", key_expr_id);//4
//    for (auto q: input) {
//        printf("Add1 exp_id =%d \n", q);//0,3
        /*if (j == 0) {
            key_str_arr[key_expr_id] = key_str_arr[q];//TODO  +=
            j++;
            continue;
        }*/
    printf("+++++++exp_id:%d\n", input[0]);
    printf("+++++++exp_id:%d\n", input[1]);
        t1 = key_str_arr[input[1]];
//        t2 = key_str_arr[q];
        t2 = key_str_arr[input[0]];

        a1 = t1.data_;
        a2 = t2.data_;
        for (int k = 0; k < a1.size(); k++) {
            a1[k] += a2[k];
        }
        t1.data_ = a1;
        key_str_arr[i.exp_id] = t1;
    key_str_arr[key_expr_id] = t1;
//    }
    printf("Add1 size:%lu\n", sizeof(key_str_arr[key_expr_id]));
}

void evaluation::Sub1(expression &i, std::map<int, tensor> &key_str_arr) {
    tensor t1;
    tensor t2;
    vector<double> a1;
    vector<double> a2;
    std::vector<int> input = i.input;
    printf("Sub1 input.size=%lu\n", input.size());
    printf("+++++++exp_id:%d\n", input[0]);
    printf("+++++++exp_id:%d\n", input[1]);
    t1 = key_str_arr[input[0]];
    t2 = key_str_arr[input[1]];
    a1 = t1.data_;
    a2 = t2.data_;
    for (int k = 0; k < a1.size(); k++) {
        a1[k] -= a2[k];
    }
    t1.data_ = a1;
    key_str_arr[i.exp_id] = t1;
    key_str_arr[key_expr_id] = t1;
}

void evaluation::Mul1(expression &i, std::map<int, tensor> &key_str_arr) {
    tensor t0;
    tensor t1;//结果
    tensor t2;//临时值
    vector<double> a1;
    vector<double> a2;
    vector<double> a3;
    vector<double> a0;
    int s3 = 1;
    double a = 1;
    int row = 0;
    int col = 0;
    int j = 0;
    std::vector<int> input = i.input;
//    printf("Mul1 input.size=%lu \n", input.size());
    printf("Mul1 key_expr_id=%d \n", key_expr_id);
    for (auto q:input) {
        printf("+++++++exp_id:%d\n", q);
        if (j == 0) {
            key_str_arr[i.exp_id] = key_str_arr[q];
            j++;
            continue;
        }
        t1 = key_str_arr[i.exp_id];
        t2 = key_str_arr[q];
        a1 = t1.data_;
//        printf("a1.size:%lu\n", a1.size());
        a2 = t2.data_;
//        printf("a2.size:%lu\n", a2.size());
        if (a1.size() == 1) {
//            printf("-a2--1: %f\n", a2[0]);
            a = a1[0];
            row = t2.shape_[0];
            col = t2.shape_[1];
            a0 = a2;
            s3 = t2.shape_[0] * t2.shape_[1];
        }
        if (a2.size() == 1) {
            a = a2[0];
            row = t1.shape_[0];
            col = t1.shape_[1];
            a0 = a1;
            s3 = t1.shape_[0] * t1.shape_[1];
//            printf("-a2--s3:%d\n", s3);
        }
        if (a1.size()>1 && a2.size()>1) {
            s3 = t1.shape_[0] * t2.shape_[1];
//            printf("-a3--s3:%d\n", s3);
        }
//        printf("+++++++s3:%d\n", s3);
        a3.assign(s3, 0);
        if (a1.size() > 1 && a2.size() > 1) {
            MultMatrix(t1.shape_[0], t1.shape_[1], a1, t2.shape_[0], t2.shape_[1], a2, a3);
        } else {
            if (a1.size() == 1) {
                OneMatrix(a, t2.shape_[0], t2.shape_[1], a2, a3);
            }else{
                OneMatrix(a,t1.shape_[0], t1.shape_[1], a1,  a3);
            }
        }
//        printf("a3.size:%lu,\n", a3.size());
//        printf("-a3--1: %f\n", a3[0]);
        t1.data_ = a3;
        if(a1.size() > 1 && a2.size() > 1) {
            t1.shape_[1] = t2.shape_[1];//12= 13，
        } else if(a1.size() == 1){
            t1.shape_.push_back(t2.shape_[0]);
            t1.shape_.push_back(t2.shape_[1]);
        } else if(a2.size() == 1){
            printf("--continue--:%lu,\n", a3.size());
        }
        key_str_arr[i.exp_id] = t1;
        j++;
    }
    key_str_arr[key_expr_id] = t1;

    printf("Mul1.output tmp size:%lu\n", sizeof(key_str_arr[key_expr_id]));
}

void evaluation::OneMatrix(double &temp1, int row_2, int col_2, vector<double> &temp2, vector<double> &result) {
    int row_result, col_result;
    int num = 0;
    for (row_result = 0; row_result < row_2; row_result++) {//12
        for (col_result = 0; col_result < col_2; col_result++) {//13
            result[num] = 0;
            //对于m*n大小数组 如需访问其i*j元素 其对应的一维坐标为(i-1)*n+j
            //temp1 为row_1*col_1 需访问其col_row*(i+1)的元素 对应一维坐标为(col_result-1)*col_1+(i+1)
            //temp2 为row_2*col_2 需访问其(i+1)*col_result的元素 对应一维坐标为i*col_2+col_result
            //result[num] += temp1[(row_result - 1)*col_1 + i] * temp2[i*row_2 + col_result-(i+1)];
            result[num] = temp1 * temp2[row_result * col_2 + col_result];//1*12+0
            num++;
        }
    }
}

void evaluation::MultMatrix(int row_1, int col_1, vector<double> &temp1, int row_2, int col_2, vector<double> &temp2,
                            vector<double> &result) {
//    int times = col_1;//times=col_1=row_2 为确定result某元素时进行的乘法(加法)次数
    int row_result, col_result;
    int num = 0;
    //num为一维数组形式的result的索引
    //row_result col_result为二维数组形式的result的索引
    for (row_result = 0; row_result < row_1; row_result++) {
        for (col_result = 0; col_result < col_2; col_result++) {
            result[num] = 0;
            for (int i = 0; i < row_2; i++) {
                //对于m*n大小数组 如需访问其i*j元素 其对应的一维坐标为(i-1)*n+j
                //temp1 为row_1*col_1 需访问其col_row*(i+1)的元素 对应一维坐标为(col_result-1)*col_1+(i+1)
                //temp2 为row_2*col_2 需访问其(i+1)*col_result的元素 对应一维坐标为i*col_2+col_result
                //result[num] += temp1[(row_result - 1)*col_1 + i] * temp2[i*row_2 + col_result-(i+1)];
                result[num] += temp1[row_result * col_1 + i] * temp2[i * col_2 + col_result];
            }
            num++;
        }
    }
}

tensor &evaluation::get_result() {
    printf("evaluation.get_result key_expr_id:%d\n", key_expr_id);
//            printf("evaluation.get_result result:%d\n",variables_[key_expr_id]);
    return variables_[key_expr_id];
}


double &evaluation::get_result1() {
    printf("eval get_result first --------------- key= %s \n", keyStr.data());
    /*if (0 == key_op_type || 1 == key_op_type) {
        result_ = get_map(keyStr);
    }*/
    printf("eval->get_result Input after val %f\n", result_);
    return result_;
}

/*
double evaluation::get_map(string key) {
    printf("eval->Input k %s\n", key.c_str());
    double d = contextMap[key];
    printf("eval->Input d %f\n", d);
    return d;
}*/
