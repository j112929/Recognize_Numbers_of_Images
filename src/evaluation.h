#ifndef EVALUATION_H
#define EVALUATION_H

#include "expression.h"
using namespace std;
class evaluation
{
public:
    std::string keyStr;
    evaluation(const std::vector<expression> &exprs);

    void add_kwargs_double(
        const char *key,
        double value);

    void add_kwargs_ndarray(
        const char *key,
        int dim,
        size_t shape[],
        double data[]);

    // return 0 for success
    int execute();

    // return the variable computed by the last expression
    double &get_result();


private:
    double result_;
    int key_op_type;
    std::vector<expression> exps;
    double get_map(std::string key);

    void Input(expression &i, std::map<string, double> &key_str, std::string &keys_);

    void Const(expression &i, map<string, double> &key_str, string &keys_);

    void Add(expression &i, map<string, double> &key_str, string &keys_, double &val_);

    void Sub(vector<int> &t_i, expression &i, map<string, double> &key_str, string &keys_, double &val_);

    void Mul(expression &i, map<string, double> &key_str, string &keys_, double &val_);
}; // class evaluation

#endif // EVALUATION_H
