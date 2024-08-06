#include <Yutils/Logger.hpp>
#include <Yutils/SimpleCSV.hpp>
#include <filesystem>
#include <fstream>
#include <vector>

using std::string_literals::operator""s;

int main()
{
    yutils::SimpleCSV csv(4);

    csv.appendRow(std::vector{"tom"s, "peter"s, "alice"s, ""s});
    csv.appendRow(csv.makeStrVec(1, "", 4.8, ""));
    csv.appendRow(csv.makeStrVec(2, "3", 5.8, 7.0));

    auto filePath = "results/example.csv";
    auto parentPath = std::filesystem::path(filePath).parent_path();
    if (!std::filesystem::exists(parentPath)) {
        std::filesystem::create_directories(parentPath);
    }
    std::ofstream file(filePath);
    if (!file.is_open()) {
        YERROR("Failed to open file: {}", filePath);
        return 1;
    }

    csv.dump(file, true);
}
