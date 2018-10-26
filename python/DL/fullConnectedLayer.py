class FullCOonnectedLayer(object):
    def __init__(self, input_size, output_size, activator):
        self.input_size = input_size
        self.output_size = output_size
        self.activator = activator
        self.W = np.random.uniform(-0.1, 0.1, (output_size, input_size))
        self.b = np.zeros((output_size, 1))
        self.output = np.zeros((output_size, 1))

    def forward(self, intput_array):
        self.input = input_array
        self.output = self.activator(np.dot(self.W, input_array) + self.b)

    def backward(self, delta_array):
        self.
