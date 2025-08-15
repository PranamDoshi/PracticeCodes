import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim


class Net(nn.Module):

    """
    Given architecture:
        1.	Input → 1 channel, size 32×32
        2.	conv1: (1, 6, kernel=5×5, stride=1) →
    Output size per dimension:
    H_{out} = \frac{H_{in} - k}{\text{stride}} + 1 = \frac{32 - 5}{1} + 1 = 28
    So result: 6×28×28
        3.	(Usually a pooling layer here) — LeNet uses 2×2 avg-pool (stride 2):
    28 \to 14
    → Output: 6×14×14
        4.	conv2: (6, 16, kernel=5×5, stride=1) →
    14 \to 14 - 5 + 1 = 10
    → Output: 16×10×10
        5.	(Again pooling layer) — 2×2 (stride 2):
    10 \to 5
    → Output: 16×5×5
        6.	Flatten: 16×5×5 = 400 features → matches fc1’s in_features=400

    Input size of nn is 32x32, Why 32×32?
        Because with this kernel/pooling combination, only a 32×32 input gives you exactly 400 features after the conv+pool layers, which is what fc1 expects. 
        If you started with MNIST’s 28×28, the size wouldn’t match unless you changed kernel sizes, strides, or fully connected input dimensions.
    """

    def __init__(self, learning_rate: float):
        super(Net, self).__init__()
        # 1 input image channel, 6 output channels, 5x5 square convolution
        # kernel
        self.conv1 = nn.Conv2d(1, 6, 5)
        self.conv2 = nn.Conv2d(6, 16, 5)

        # an affine operation: y = Wx + b
        self.fc1 = nn.Linear(16 * 5 * 5, 120)  # 5*5 from image dimension
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

        self.learning_rate = learning_rate

        self.create_optimizer()

    def forward(self, input):
        # Convolution layer C1: 1 input image channel, 6 output channels,
        # 5x5 square convolution, it uses RELU activation function, and
        # outputs a Tensor with size (N, 6, 28, 28), where N is the size of the batch
        c1 = F.relu(self.conv1(input))

        # Subsampling layer S2: 2x2 grid, purely functional,
        # this layer does not have any parameter, and outputs a (N, 6, 14, 14) Tensor
        s2 = F.max_pool2d(c1, (2, 2))

        # Convolution layer C3: 6 input channels, 16 output channels,
        # 5x5 square convolution, it uses RELU activation function, and
        # outputs a (N, 16, 10, 10) Tensor
        c3 = F.relu(self.conv2(s2))

        # Subsampling layer S4: 2x2 grid, purely functional,
        # this layer does not have any parameter, and outputs a (N, 16, 5, 5) Tensor
        s4 = F.max_pool2d(c3, 2)

        # Flatten operation: purely functional, outputs a (N, 400) Tensor
        s4 = torch.flatten(s4, 1)

        # Fully connected layer F5: (N, 400) Tensor input,
        # and outputs a (N, 120) Tensor, it uses RELU activation function
        f5 = F.relu(self.fc1(s4))

        # Fully connected layer F6: (N, 120) Tensor input,
        # and outputs a (N, 84) Tensor, it uses RELU activation function
        f6 = F.relu(self.fc2(f5))

        # Gaussian layer OUTPUT: (N, 84) Tensor input, and
        # outputs a (N, 10) Tensor
        output = self.fc3(f6)

        return output
    
    def calculate_loss(self, input):
        output = self.__call__(input)
        target = torch.rand_like(output)  # a dummy target, for example

        # target = target.view(1, -1)  # make it the same shape as output
        # print(target.size())
        # print(output.size())

        criterion = nn.MSELoss()

        loss = criterion(output, target)
        print(loss)

        return loss

        # print(loss.grad_fn)  # MSELoss
        # print(loss.grad_fn.next_functions[0][0])  # Linear
        # print(loss.grad_fn.next_functions[0][0].next_functions[0][0])  # ReLU

    def backward(self, loss):
        # self.zero_grad()     # zeroes the gradient buffers of all parameters

        print('conv1.bias.grad before backward')
        print(self.conv1.bias.grad)

        loss.backward()

        print('conv1.bias.grad after backward')
        print(self.conv1.bias.grad)

    def apply_gredient_decent(self):
        for f in self.parameters():
            f.data.sub_(f.grad.data * self.learning_rate)

    def create_optimizer(self):
        self.optimizer = optim.SGD(self.parameters(), lr=self.learning_rate)

    def run(self, input):
        out = net(input)
        print(out)

    def training_step(self, input):
        self.optimizer.zero_grad()   # zero the gradient buffers
        loss = self.calculate_loss(input)
        self.backward(loss)
        self.optimizer.step()    # Does the update

if __name__ == "__main__":
    net = Net(learning_rate=0.01)
    print(net)

    print("\n------------------------------------\n")

    params = list(net.parameters())
    print(len(params))
    for index in range(len(params)):
        print(params[index].size())  # conv1's .weight

    print("\n------------------------------------\n")

    input = torch.randn(1, 1, 32, 32)
    net.run(input)

    print("\n------------------------------------\n")

    # loss = net.calculate_loss(input)
    # net.backward(loss)
    # net.apply_gredient_decent()

    # net.training_step(input)

    for _ in range(100):
        temp_input = torch.randn(32, 1, 32, 32)
        net.training_step(temp_input)

    print("\n------------------------------------\n")

    net.run(input)
