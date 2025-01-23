// clang++ -std=c++23 -O3 -Wall -pedantic -pthread -o int int.cpp
// clang++ -std=c++23 -O3 -Wall -pedantic -pthread -o int int.cpp -lgdi32 -luser32 -lws2_32 -W#warnings


#include <site-packages\Utills\utillsfunc.hxx>
#include <site-packages\Utills\utills_win.hxx>
#include <site-packages\Utills\types.hpp>
#include <typeinfo>
// using namespace WinAPI;


int main0(int argc, char const *argv[]){
    // std::string tx1 = "Hi";
    // std::string tx2 = "Hello";

    std::cout << std::endl;

    auto [columns, rows] = WinAPI::GetTerminalSize();
    std::cout << "Terminal Size: " << columns << " x " << rows << std::endl;
    
    std::cout << std::endl;

    std::cout << "Local IP Address: " << Colouring::colortx(WinAPI::GetLocalIPAddress(), "86d4c5") << std::endl;
    
    std::cout << std::endl;

    auto [nativeWidth, nativeHeight, scalingFactor] = WinAPI::GetScreenInfo();

    std::cout << "Native Resolution: " << nativeWidth << "x" << nativeHeight << "\n";
    std::cout << "Scaling Factor: " << scalingFactor << "x (" << scalingFactor * 100 << "%)\n";

    std::cout << std::endl;

    auto [X, Y] = WinAPI::GetScreenResolution();
    X = int(X * 1.5);
    Y = int(Y * 1.5);
    std::print("Your screen resolution is {} x {}\n", Colouring::colortx(std::to_string(X), "ebd848"), Colouring::colortx(std::to_string(Y), "ebd848"));
    
    std::cout << std::endl;

    WinAPI::CheckPowerStatus();
    
    std::cout << std::endl;

    TP::STR USER = Colouring::colortx(WinAPI::GetUsername());
    std::print("Your name is {}", USER);

    // MessageBox(NULL, tx1.c_str(), tx2.c_str(), MB_OK | MB_ICONINFORMATION);
    return 0;
}

int main1(int argc, char const *argv[]){
    // Example usage
    void Example() {
        std::vector<int> numbers = {1, 2, 3, 4, 5};

        // Sum
        int sum = Sum(numbers.begin(), numbers.end());
        std::cout << "Sum: " << sum << std::endl;

        // Cumulative Sum
        std::vector<int> cumulative(numbers.size());
        CumulativeSum(numbers.begin(), numbers.end(), cumulative.begin());
        std::cout << "Cumulative Sum: ";
        for (auto val : cumulative) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // Dot Product
        std::vector<int> other = {5, 4, 3, 2, 1};
        int dot = DotProduct(numbers.begin(), numbers.end(), other.begin());
        std::cout << "Dot Product: " << dot << std::endl;

        // Iota
        std::vector<int> iotaVec(5);
        Iota(iotaVec.begin(), iotaVec.end(), 10);
        std::cout << "Iota: ";
        for (auto val : iotaVec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // Adjacent Difference
        std::vector<int> adjDiff(numbers.size());
        AdjacentDifference(numbers.begin(), numbers.end(), adjDiff.begin());
        std::cout << "Adjacent Difference: ";
        for (auto val : adjDiff) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // Parallel Reduce
        int reduced = ParallelReduce(numbers.begin(), numbers.end());
        std::cout << "Parallel Reduce: " << reduced << std::endl;

        // Min and Max
        int minVal = Min(numbers.begin(), numbers.end());
        int maxVal = Max(numbers.begin(), numbers.end());
        std::cout << "Min: " << minVal << ", Max: " << maxVal << std::endl;

        // Average
        double avg = Average(numbers.begin(), numbers.end());
        std::cout << "Average: " << avg << std::endl;

        // Reverse
        Reverse(numbers.begin(), numbers.end());
        std::cout << "Reversed: ";
        for (auto val : numbers) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // Shuffle
        Shuffle(numbers.begin(), numbers.end());
        std::cout << "Shuffled: ";
        for (auto val : numbers) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}