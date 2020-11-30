# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library (src ${DIR_LIB_SRCS}
        other/ other/C.h)
#        other/member.h)
#        op/eval_mul.cpp op/eval_mul.h op/eval_op_prototypes.cpp op/eval_op_prototypes.h op/eval_sub.cpp op/eval_sub.h op/eval_add.h op/eval_add.cpp)
#        op/eval.cpp other/time.cpp other/time.h other/collection.cpp other/collection.h other/base.cpp other/base.h other/derived.cpp tensor.cpp tensor.h op/eval_op.cpp op/eval_op.h op/eval_const.cpp op/eval_const.h op/eval_input.cpp op/eval_input.h  op/eval_binary.cpp  op/eval_binary.h)