#include <iostream>
#include <chrono> 
#include <torch/script.h>
//#include <torchvision/vision.h>

using namespace std::chrono; 

int main(int argc, const char *argv[])
{
    torch::NoGradGuard no_grad;
    std::string model_path = argv[1];
    std::cout << "Loading model " << model_path << std::endl;
    torch::jit::script::Module model = torch::jit::load(model_path, torch::kCUDA);
    std::cout << "Loaded model " << model_path << std::endl;
    for (int i=0; i<=1000; i++){
	    auto start = high_resolution_clock::now(); 
	    at::Tensor input_tensor = torch::randn({640, 480, 3}, torch::kCUDA);
	    std::vector<torch::jit::IValue> inputs;
	    inputs.emplace_back(input_tensor);
	    auto output = model.forward(inputs);
	    auto stop = high_resolution_clock::now();
	    auto duration = duration_cast<microseconds>(stop - start); 
	    std::cout << i << ": " << duration.count() << "ms" << std::endl; 
    }
    return 0;
}
