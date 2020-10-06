#include <assert.h>
#include "evaluation.h"

std::map<std::string, double> contextMap;
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
}

void evaluation::add_kwargs_ndarray(
        const char *key,
        int dim,
        size_t shape[],
        double data[]) {
}

int evaluation::execute() {
    map<string, double> key_str;
    string keys_;
    std::vector<int> t_i;
    double val_ = 0.0;
    for (auto i : exps) {
        if (0 != i.opname.compare("")) {
            if (0 == i.optype.compare("Input")) {
                Input(i, key_str, keys_, val_);
            }
        } else if (0 == i.opname.compare("")) {
            if (0 == i.optype.compare("Const")) {
                Const(i, key_str, keys_, val_);
            } else if (0 == i.optype.compare("Add")) {
                Add(i, key_str, keys_, val_);
            } else if (0 == i.optype.compare("Sub")) {
                Sub(t_i, i, key_str, keys_, val_);
            } else if (0 == i.optype.compare("Mul")) {
                Mul(i, key_str, keys_, val_);
            }
        }
    }
    result_ = val_;
    key_str.clear();
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



double &evaluation::get_result() {
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
