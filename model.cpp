#include <iostream>
#include <torch/script.h>

int main(int argc, const char *argv[])
{
    torch::NoGradGuard no_grad;
    std::string model_path = argv[1];
    torch::jit::script::Module model = torch::jit::load(model_path);
    std::cout << "This is a dummy model" << std::endl;
    return 0;
}