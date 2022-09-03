import numpy as np
import time

# save theta to mnist_train.npz that can be used by easynn
def save_theta(theta):
    f1_W, f1_b, f2_W, f2_b = theta

    np.savez_compressed("p5_params.npz", **{
        "f1.weight": f1_W,
        "f1.bias": f1_b,
        "f2.weight": f2_W,
        "f2.bias": f2_b
    })


# initialize theta using uniform distribution [-bound, bound]
# return theta as (f1_W, f1_b, f2_W, f2_b)
def initialize_theta(bound):
    f1_W = np.random.uniform(-bound, bound, (32, 784))
    f1_b = np.random.uniform(-bound, bound, 32)
    f2_W = np.random.uniform(-bound, bound, (10, 32))
    f2_b = np.random.uniform(-bound, bound, 10)
    return (f1_W, f1_b, f2_W, f2_b)


# forward:
#   x = Flatten(images)
#   g = Linear_f1(x)
#   h = ReLU(g)
#   z = Linear_f2(h)
# return (z, h, g, x)
def forward(images, theta):
    # number of samples
    N = images.shape[0]

    # unpack theta into f1 and f2
    f1_W, f1_b, f2_W, f2_b = theta

    # x = Flatten(images)
    x = images.astype(float).transpose(0, 3, 1, 2).reshape((N, -1))

    # g = Linear_f1(x)
    g = np.zeros((N, f1_b.shape[0]))
    for i in range(N):
        g[i, :] = np.matmul(f1_W, x[i]) + f1_b

    # h = ReLU(g)
    h = g * (g > 0)

    # z = Linear_f2(h)
    z = np.zeros((N, f2_b.shape[0]))
    for i in range(N):
        z[i, :] = np.matmul(f2_W, h[i]) + f2_b

    return (z, h, g, x)


# backprop:
#   J = cross entropy between labels and softmax(z)
# return nabla_J
# 计算雅可比矩阵
def backprop(labels, theta, z, h, g, x):
    # number of samples
    N = labels.shape[0]

    # unpack theta into f1 and f2
    f1_W, f1_b, f2_W, f2_b = theta

    # nabla_J consists of partial J to partial f1_W, f1_b, f2_W, f2_b
    p_f1_W = np.zeros(f1_W.shape)  # w1
    p_f1_b = np.zeros(f1_b.shape)  # b1
    p_f2_W = np.zeros(f2_W.shape)  # W2
    p_f2_b = np.zeros(f2_b.shape)  # b2
    for i in range(N):
        # compute the contribution to nabla_J for sample i

        # cross entropy and softmax
        #   compute partial J to partial z[i]
        #   scale by 1/N for averaging
        expz = np.exp(z[i] - max(z[i]))
        p_z = expz / sum(expz) / N  # J ,对h进行求导
        p_z[labels[i]] -= 1 / N
        # z = Linear_f2(h)
        #   compute partial J to partial h[i]
        #   accumulate partial J to partial f2_W, f2_b
        # ToDo: uncomment code below to add your own code
        p_h = np.dot(f2_W.transpose(), p_z)
        p_f2_W += p_z.reshape(-1,1)*h[i].reshape(1,-1)
        p_f2_b += p_z

        # h = ReLU(g)
        #   compute partial J to partial g[i]
        # ToDo: uncomment code below to add your own code
        p_g = p_h* partial_derivative_of_relu(g[i])

        # g = Linear_f1(x)
        #   accumulate partial J to partial f1_W, f1_b
        # ToDo: uncomment code below to add your own code
        p_f1_W += p_g.reshape(-1,1) * x[i]
        p_f1_b += p_g
    #
    return (p_f1_W, p_f1_b, p_f2_W, p_f2_b)

def partial_derivative_of_relu(matrix):
    matrix[matrix <= 0] = 0
    matrix[matrix > 0] = 1
    return matrix
# apply SGD to update theta by nabla_J and the learning rate epsilon
# return updated theta
# 梯度更新规则
def update_theta(theta, nabla_J, epsilon):
    # ToDo: modify code below as needed
    # theta -= epsilon * nabla_J
    f1_W, f1_b, f2_W, f2_b = theta
    p_f1_W, p_f1_b, p_f2_W, p_f2_b = nabla_J
    f1_W -= epsilon * p_f1_W
    f1_b -= epsilon * p_f1_b
    f2_W -= epsilon * p_f2_W
    f2_b -= epsilon * p_f2_b
    updated_theta = (f1_W, f1_b, f2_W, f2_b)
    return updated_theta


# ToDo: set numpy random seed to the last 8 digits of your CWID
np.random.seed(20478895)

# load training data and split them for validation/training
mnist_train = np.load("mnist_train.npz")
validation_images = mnist_train["images"][:1000]
validation_labels = mnist_train["labels"][:1000]
training_images = mnist_train["images"][1000:]
training_labels = mnist_train["labels"][1000:]

# hyperparameters
bound = 0.01  # initial weight range
epsilon = 0.0001
    # 0.00009  # learning rate
batch_size = 4
    # 4

# start training
start = time.time()
theta = initialize_theta(bound)
batches = training_images.shape[0] // batch_size
sum_loss = 0
sum_accuracy = 0
for epoch in range(10):
    indices = np.arange(training_images.shape[0])
    np.random.shuffle(indices)
    for i in range(batches):
        batch_images = training_images[indices[i * batch_size:(i + 1) * batch_size]]
        batch_labels = training_labels[indices[i * batch_size:(i + 1) * batch_size]]

        z, h, g, x = forward(batch_images, theta)
        nabla_J = backprop(batch_labels, theta, z, h, g, x)
        theta = update_theta(theta, nabla_J, epsilon)

    # check accuracy using validation examples
    z, _, _, _ = forward(validation_images, theta)
    pred_labels = z.argmax(axis=1)
    count = sum(pred_labels == validation_labels)

    expz = np.exp(z-np.max(z,axis=1,keepdims=True))
    pred = expz/sum(expz)
    loss=sum(-np.log(pred[i,validation_labels[i]]) for i in range(1000))
    accuracy = count / validation_images.shape[0]
    print("epoch %d, accuracy %.3f,loss %.3f, time %.2f" % (
        epoch, accuracy, loss, time.time() - start))
    sum_accuracy = sum_accuracy+accuracy
    sum_loss = sum_loss+loss

avg_accuracy = sum_accuracy / 10
avg_loss = sum_loss / 10
print("accuracy %.3f,loss %.3f" % (avg_accuracy, avg_loss))

# save the weights to be submitted
save_theta(theta)
