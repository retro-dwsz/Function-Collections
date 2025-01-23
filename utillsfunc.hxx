/**
 * Utillsfunc.hxx "Utility"
 * functions and classes by @author David "Rétro" Siřait.
 * This file contains various reusable functions and classes.
 * This is not meant to be executed directly.
 *
 * You can freely edit this file
 * Contact me via discord @dwsz56
 *
 *
 * Do not run or compile. Use it by importing.
 * Requieres C++23 (-std=c++23)
 *
 * Compile: clang++ -std=c++23 -o <file> <file>.cpp -O3 -Wall -pedantic -pthread -mwindows -lgdi32 -luser32 -lws2_32 -W#warnings
 * -W#warnings and -mwindows are optional
 */

#pragma once

#include "Includes.hxx"

namespace Misc{
    // Helper function to convert std::any to a string for printing
    TP::STR any_to_string(const std::any& value) {
        try {
            if (value.type() == typeid(int)) {
                return std::to_string(std::any_cast<int>(value));
            } else if (value.type() == typeid(double)) {
                return std::to_string(std::any_cast<double>(value));
            } else if (value.type() == typeid(std::string)) {
                return std::any_cast<std::string>(value);
            } else if (value.type() == typeid(const char*)) {
                return std::string(std::any_cast<const char*>(value));
            } else {
                return "<Unsupported Type>";
            }
        } catch (const std::bad_any_cast&) {
            return "<Error: Bad Cast>";
        }
    }
    // Function to break down a string into a vector of its characters
    TP::VSTR breakdownString(const TP::STR& input) {
        TP::VSTR result;
        for (char c : input) {
            result.push_back(TP::STR(1, c));
        }
        return result;
    }

    // Function to split a string into substrings based on a delimiter
    TP::VSTR sepr(const TP::STR& tx) {
        TP::VSTR result;
        for (char ch : tx) {
            result.push_back(TP::STR(1, ch)); // Convert each character to a string
        }
        return result;
    }

    // Function to get console size
    std::map<TP::STR, int> GetCSize() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int width, rows;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return {{"width", width}, {"rows", rows}};
    }

    // Function to print text in the middle of the console
    TP::STR printmid(const TP::STR& text, int offset = 0, char ch = '=', bool p = true) {
        int terminal_width = Misc::GetCSize()["width"] + offset;
        int text_length = text.length();
        int border_length = (terminal_width - text_length - 4) / 2;
        TP::STR top_border(border_length, ch);
        TP::STR bottom_border(border_length + (text_length % 2), ch);

        TP::SSTR content_stream;
        content_stream << top_border << "[" << text << "]" << bottom_border << std::endl;
        TP::STR content = content_stream.str();

        if (p) {
            std::cout << content;
        }

        return content;
    }
}

// --------------------- Python-like Utilities ---------------------
namespace pylike{
    template <typename... Args>
    void pyprint(const TP::STR& fmt, Args&&... args) {
        // Use std::format to substitute arguments into the string
        std::cout << std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...)) << std::endl;
    }

    // Fun function to generate a random string of given length
    TP::STR random_string(size_t length, const TP::STR charset = "ABCDE") {
        // const TP::STR charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, charset.size() - 1);

        TP::STR random_str;
        for (size_t i = 0; i < length; ++i) {
            random_str += charset[dis(gen)];
        }
        return random_str;
    }

    // Function to pause execution for a specified number of seconds
    void hold(int sec) {
        std::this_thread::sleep_for(std::chrono::seconds(sec));
    }
}

// --------------------- Colouring utilites ---------------------
namespace Colouring {
    // Function to convert HEX to RGB
    void hex_to_rgb(const char* hex, int* r, int* g, int* b) {
        sscanf(hex, "%2x%2x%2x", r, g, b);
    }

    // // Function to change text colour using ANSI escape codes with RGB values
    // void colortx(const char* tx, const char* hex) {
    //     int r, g, b;
    //     hex_to_rgb(hex, &r, &g, &b);
    //     printf("\033[38;2;%d;%d;%dm%s\033[0m", r, g, b, tx);
    // }

    static TP::STR colortx(const TP::STR& tx, const TP::STR& hex = "75fb7e") {
        std::ostringstream colored_text;

        if (hex == "random") {
            // Random coloring for each character
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, 255);

            for (char c : tx) {
                int r = dist(gen);
                int g = dist(gen);
                int b = dist(gen);
                colored_text << "\033[38;2;" << r << ";" << g << ";" << b << "m" << c << "\033[0m";
            }
        } else {
            // Single color for the entire string
            int r = std::stoi(hex.substr(0, 2), nullptr, 16);
            int g = std::stoi(hex.substr(2, 2), nullptr, 16);
            int b = std::stoi(hex.substr(4, 2), nullptr, 16);
            colored_text << "\033[38;2;" << r << ";" << g << ";" << b << "m" << tx << "\033[0m";
        }

        return colored_text.str();
    }

    // Function to convert RGB to HEX
    void rhex(int r, int g, int b, char* hex) {
        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
            printf("RGB values must be between 0 and 255\n");
            return;
        }
        sprintf(hex, "#%02X%02X%02X", r, g, b);
    }

    // Function to convert HEX to RGB and return as a tuple
    void hrgb(const char* hex, int* r, int* g, int* b) {
        if (hex[0] == '#') {
            hex++;
        }
        if (strlen(hex) != 6) {
            printf("Invalid HEX format. Ensure it's in #RRGGBB format.\n");
            return;
        }
        sscanf(hex, "%2x%2x%2x", r, g, b);
    }
};

// --------------------- Random Utilities ---------------------
namespace Randoms {
    static std::vector<int> generate_l(int LB, int UB, const std::vector<int>& exc, int le) {
        std::vector<int> possible_nums;
        for (int i = LB; i <= UB; ++i) {
            if (std::find(exc.begin(), exc.end(), i) == exc.end()) {
                possible_nums.push_back(i);
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(possible_nums.begin(), possible_nums.end(), g);
        return std::vector<int>(possible_nums.begin(), possible_nums.begin() + le);
    }

    static int randomint(int LB, int UB) {
        // Create a random number generator
        std::random_device rd; // Non-deterministic random seed
        std::mt19937 gen(rd()); // Mersenne Twister random number generator

        // Define the distribution for integers in the range [LB, UB]
        std::uniform_int_distribution<> distrib(LB, UB);

        // Generate and return the random number
        return distrib(gen);
    }

    // Fun function to generate a random floating-point number
    float random_float(float min, float max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
};

// --------------------- File and Memory Utilities ---------------------
namespace fs = std::filesystem;
namespace Files {
    static TP::VSTR get_folder_files(const TP::STR& path, const TP::STR& only = "") {
        if (!fs::is_directory(path)) {
            return {};
        }
        TP::VSTR files;
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_regular_file() && (only.empty() || entry.path().extension() == only)) {
                files.push_back(entry.path().filename().string());
            }
        }
        return files;
    }

    static size_t get_folder_size(const TP::STR& folder_path) {
        size_t total_size = 0;
        for (const auto& dir_entry : fs::directory_iterator(folder_path)) {
            if (dir_entry.is_regular_file()) {
                total_size += dir_entry.file_size();
            }
        }
        return total_size;
    }

    static TP::STR format_size(size_t size_bytes) {
        if (size_bytes < 1024) {
            return std::to_string(size_bytes) + " bytes";
        } else if (size_bytes < 1024 * 1024) {
            return std::to_string(static_cast<double>(size_bytes) / 1024.0) + " KB";
        } else {
            return std::to_string(static_cast<double>(size_bytes) / (1024 * 1024)) + " MB";
        }
    }
};
// --------------------- Array Utilities ---------------------
namespace Arrays{
    static std::vector<int> GetDummy() {
        std::vector<int> random_data(10);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(-10, 10);

        std::generate(random_data.begin(), random_data.end(), [&]() { return dist(gen); });
        return random_data;
    }

    // Function to print a container
    template <typename Container>
    void printer(const Container& container, TP::STR end = "") {
        std::cout << "[";
        bool first = true;
        for (const auto& element : container) {
            if (!first) {
                std::cout << ", " << end;
            }
            first = false;
            std::cout << element;
        }
        std::cout << "]" << std::endl;
    }

    std::vector<int> flatArr(const std::vector<std::any>& arr) {
        std::vector<int> flattened;
        for (const auto& element : arr) {
            if (element.type() == typeid(std::vector<std::any>)) {
                auto sub_arr = std::any_cast<std::vector<std::any>>(element);
                flattened.insert(flattened.end(), flatArr(sub_arr).begin(), flatArr(sub_arr).end());
            } else {
                flattened.push_back(std::any_cast<int>(element));
            }
        }
        return flattened;
    }

    std::vector<int> arrize(int number) {
        TP::STR str_num = std::to_string(number);
        std::vector<int> digits;
        for (char c : str_num) {
            if (isdigit(c)) {
                digits.push_back(c - '0');
            } else {
                digits.push_back(static_cast<int>(c));
            }
        }
        return digits;
    }

    // Function to reverse a vector in-place
    template <typename T>
    void reverse(std::vector<T>& arr) {
        std::reverse(arr.begin(), arr.end());
    }

    // Function to find the minimum element in an array
    template <typename T>
    T min_element(const std::vector<T>& arr) {
        return *std::min_element(arr.begin(), arr.end());
    }

    // Function to find the maximum element in an array
    template <typename T>
    T max_element(const std::vector<T>& arr) {
        return *std::max_element(arr.begin(), arr.end());
    }

    // Function to remove duplicates from a vector
    template <typename T>
    std::vector<T> remove_duplicates(const std::vector<T>& arr) {
        std::vector<T> unique_arr = arr;
        std::sort(unique_arr.begin(), unique_arr.end());
        unique_arr.erase(std::unique(unique_arr.begin(), unique_arr.end()), unique_arr.end());
        return unique_arr;
    }

    // Function to shuffle an array randomly (like Python's random.shuffle)
    template <typename T>
    void shuffle(std::vector<T>& arr) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(arr.begin(), arr.end(), g);
    }

    // Function to count occurrences of a value in a vector
    template <typename T>
    int count_occurrences(const std::vector<T>& arr, const T& value) {
        return std::count(arr.begin(), arr.end(), value);
    }

    // Function to merge two sorted arrays into a single sorted array
    template <typename T>
    std::vector<T> merge_sorted(const std::vector<T>& arr1, const std::vector<T>& arr2) {
        std::vector<T> result;
        auto it1 = arr1.begin(), it2 = arr2.begin();
        while (it1 != arr1.end() && it2 != arr2.end()) {
            if (*it1 < *it2) {
                result.push_back(*it1);
                ++it1;
            } else {
                result.push_back(*it2);
                ++it2;
            }
        }
        result.insert(result.end(), it1, arr1.end());
        result.insert(result.end(), it2, arr2.end());
        return result;
    }

    // Function to rotate an array (rotate left by n positions)
    template <typename T>
    void rotate_left(std::vector<T>& arr, int n) {
        n = n % arr.size();  // To handle cases where n > arr.size()
        std::rotate(arr.begin(), arr.begin() + n, arr.end());
    }

    // Function to rotate an array (rotate right by n positions)
    template <typename T>
    void rotate_right(std::vector<T>& arr, int n) {
        n = n % arr.size();  // To handle cases where n > arr.size()
        std::rotate(arr.rbegin(), arr.rbegin() + n, arr.rend());
    }

    // Function to generate a random array of a specified size and range
    std::vector<int> random_array(int size, int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = dis(gen);
        }
        return arr;
    }

    // Function to compute the sum of elements in an array
    template <typename T>
    T sum(const std::vector<T>& arr) {
        return std::accumulate(arr.begin(), arr.end(), T(0));
    }

}

namespace Numc {

    /**
     * Sums up the values in a range.
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     * @param init - Initial value for the sum.
     * @return The sum of the range.
     */
    template<typename Iterator>
    auto Sum(Iterator begin, Iterator end, typename std::iterator_traits<Iterator>::value_type init = 0) {
        return std::accumulate(begin, end, init);
    }

    /**
     * Computes the cumulative sum (partial sum) of a sequence.
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     * @param result - Output container where the cumulative sum will be stored.
     */
    template<typename Iterator, typename OutputIterator>
    void CumulativeSum(Iterator begin, Iterator end, OutputIterator result) {
        std::partial_sum(begin, end, result);
    }

    /**
     * Calculates the dot product of two sequences.
     * @param begin1 - Iterator to the start of the first sequence.
     * @param end1 - Iterator to the end of the first sequence.
     * @param begin2 - Iterator to the start of the second sequence.
     * @return The dot product of the two sequences.
     */
    template<typename Iterator>
    auto DotProduct(Iterator begin1, Iterator end1, Iterator begin2) {
        return std::inner_product(begin1, end1, begin2, 0);
    }

    /**
     * Fills a range with consecutive values starting from a specified value.
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     * @param start - The value from which the range will start.
     */
    template<typename Iterator>
    void Iota(Iterator begin, Iterator end, typename std::iterator_traits<Iterator>::value_type start) {
        std::iota(begin, end, start);
    }

    /**
     * Computes the difference between adjacent elements in a sequence.
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     * @param result - Output container where the differences will be stored.
     */
    template<typename Iterator, typename OutputIterator>
    void AdjacentDifference(Iterator begin, Iterator end, OutputIterator result) {
        std::adjacent_difference(begin, end, result);
    }

    /**
     * Performs a parallel reduction of a sequence (C++17).
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     * @param init - Initial value for the reduction operation.
     * @return The reduced result.
     */
    template<typename Iterator>
    auto ParallelReduce(Iterator begin, Iterator end, typename std::iterator_traits<Iterator>::value_type init = 0) {
        return std::reduce(begin, end, init);
    }

    /**
     * Finds the minimum value in a sequence.
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     * @return The minimum value in the sequence.
     */
    template<typename Iterator>
    auto Min(Iterator begin, Iterator end) {
        return *std::min_element(begin, end);
    }

    /**
     * Finds the maximum value in a sequence.
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     * @return The maximum value in the sequence.
     */
    template<typename Iterator>
    auto Max(Iterator begin, Iterator end) {
        return *std::max_element(begin, end);
    }

    /**
     * Computes the average of a sequence of numbers.
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     * @return The average of the numbers in the sequence.
     */
    template<typename Iterator>
    auto Average(Iterator begin, Iterator end) {
        auto sum = std::accumulate(begin, end, typename std::iterator_traits<Iterator>::value_type{0});
        auto count = std::distance(begin, end);
        return sum / count;
    }

    /**
     * Reverses a sequence in place.
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     */
    template<typename Iterator>
    void Reverse(Iterator begin, Iterator end) {
        std::reverse(begin, end);
    }

    /**
     * Shuffles the sequence randomly.
     * @param begin - Iterator to the start of the range.
     * @param end - Iterator to the end of the range.
     */
    template<typename Iterator>
    void Shuffle(Iterator begin, Iterator end) {
        std::shuffle(begin, end, std::default_random_engine{});
    }
}

// --------------------- Text Effects and Animations ---------------------
namespace TextEffects {
    // Creates a typing animation effect when printing text
    static void typewrite(const TP::STR& text, int delay_ms = 50) {
        for (char c : text) {
            std::cout << c << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        }
        std::cout << std::endl;
    }

    // Creates a bouncing text animation
    static void bounceText(const TP::STR& text, int bounces = 3) {
        int width = Misc::GetCSize()["width"];

        for (int bounce = 0; bounce < bounces; bounce++) {
            for (int i = 0; i < width - text.length(); i++) {
                system("cls");
                TP::STR padding(i, ' ');
                std::cout << padding << text << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            for (int i = width - text.length(); i >= 0; i--) {
                system("cls");
                TP::STR padding(i, ' ');
                std::cout << padding << text << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }
};

// --------------------- ASCII Art Generator ---------------------
namespace ASCIIArt {
    static TP::STR generateProgressBar(int progress, int total) {
        const int bar_width = 50;
        float progress_ratio = static_cast<float>(progress) / total;
        int filled_width = static_cast<int>(bar_width * progress_ratio);

        TP::SSTR ss;
        ss << "[";
        for (int i = 0; i < bar_width; ++i) {
            if (i < filled_width) ss << "█";
            else ss << " ";
        }
        ss << "] " << static_cast<int>(progress_ratio * 100) << "%";
        return ss.str();
    }

    static TP::STR drawBox(const TP::STR& text) {
        int width = text.length() + 4;
        TP::SSTR ss;

        ss << "+" << TP::STR(width-2, '-') << "+" << std::endl;
        ss << "| " << text << " |" << std::endl;
        ss << "+" << TP::STR(width-2, '-') << "+";

        return ss.str();
    }
};

// --------------------- String Transformations ---------------------
namespace StringTransforms {
    // Convert text to leetspeak
    static TP::STR toLeetSpeak(const TP::STR& input) {
        std::map<char, TP::STR> leetMap = {
            {'a', "4"}, {'e', "3"}, {'i', "1"}, {'o', "0"},
            {'s', "5"}, {'t', "7"}, {'l', "1"}, {'b', "8"}
        };

        TP::STR result = input;
        for (auto& [key, value] : leetMap) {
            std::replace_if(result.begin(), result.end(),
                [key](char c) { return std::tolower(c) == key; },
                value[0]);
        }
        return result;
    }

    // Create wave pattern text
    static TP::STR waveText(const TP::STR& input) {
        TP::STR result;
        for (size_t i = 0; i < input.length(); ++i) {
            if (i % 2 == 0) {
                result += std::toupper(input[i]);
            } else {
                result += std::tolower(input[i]);
            }
        }
        return result;
    }

    // Fun function to make a fun "loading" spinner
    void loading_spinner(int duration_seconds = 5) {
        const TP::STR spinner = "|/-\\";
        for (int i = 0; i < duration_seconds * 10; ++i) {
            std::cout << "\r" << spinner[i % spinner.size()] << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "\rDone!" << std::endl;
    }

    // Function to generate a simple progress bar
    void progress_bar(int percentage) {
        int bar_width = 50;
        std::cout << "[";
        int pos = bar_width * percentage / 100;
        for (int i = 0; i < bar_width; ++i) {
            if (i < pos) {
                std::cout << "=";
            } else if (i == pos) {
                std::cout << ">";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "] " << percentage << " %\r" << std::flush;
    }
};

// --------------------- Math Utilities ---------------------
namespace MathUtils {
    // Generate Fibonacci sequence up to n terms
    static std::vector<long long> fibonacci(int n) {
        std::vector<long long> sequence;
        if (n <= 0) return sequence;

        sequence.push_back(0);
        if (n == 1) return sequence;

        sequence.push_back(1);
        for (int i = 2; i < n; ++i) {
            sequence.push_back(sequence[i-1] + sequence[i-2]);
        }
        return sequence;
    }

    // Check if a number is prime
    static bool isPrime(int number) {
        if (number <= 1) return false;
        if (number <= 3) return true;
        if (number % 2 == 0 || number % 3 == 0) return false;

        for (int i = 5; i * i <= number; i += 6) {
            if (number % i == 0 || number % (i + 2) == 0) return false;
        }
        return true;
    }
};

// --------------------- Time Utilities ---------------------
namespace TimeUtils {
    // Format duration in seconds to human-readable format
    static TP::STR formatDuration(int seconds) {
        if (seconds < 0) return "Invalid input";
        if (seconds == 0) return "now";

        int years = seconds / (365 * 24 * 3600);
        seconds %= (365 * 24 * 3600);
        int days = seconds / (24 * 3600);
        seconds %= (24 * 3600);
        int hours = seconds / 3600;
        seconds %= 3600;
        int minutes = seconds / 60;
        seconds %= 60;

        TP::VSTR parts;
        if (years > 0) parts.push_back(std::to_string(years) + " year" + (years > 1 ? "s" : ""));
        if (days > 0) parts.push_back(std::to_string(days) + " day" + (days > 1 ? "s" : ""));
        if (hours > 0) parts.push_back(std::to_string(hours) + " hour" + (hours > 1 ? "s" : ""));
        if (minutes > 0) parts.push_back(std::to_string(minutes) + " minute" + (minutes > 1 ? "s" : ""));
        if (seconds > 0) parts.push_back(std::to_string(seconds) + " second" + (seconds > 1 ? "s" : ""));

        return parts[0];
    }

    // Fun function to return the current timestamp
    TP::STR current_timestamp() {
        auto now = std::chrono::system_clock::now();
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&now_time_t);

        std::ostringstream timestamp;
        timestamp << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
        return timestamp.str();
    }
};
