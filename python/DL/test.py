import tensorflow
mnist = input_data.read_data_sets("MNIST_data/", one_hot = True)

print( mnist.train.shape )