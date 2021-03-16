import torch

class MyCell(torch.nn.Module):
    def __init__(self):
        super(MyCell, self).__init__()

    def forward(self, x):
        return x+3

my_cell = MyCell().cuda()
x = torch.rand(3, 4, 3).cuda()
traced_cell = torch.jit.trace(my_cell, x)

print(traced_cell)
res = traced_cell(x)
print(res)

torch.jit.save(traced_cell, 'test.pt')
