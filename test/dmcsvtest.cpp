#include "dmcsv_parser.hpp"
#include "dmcsv_writer.hpp"
#include <vector>
#include <queue>

#include "gtest.h"

TEST(dmcsv, dmcsv_write) {
    std::string strFile = "slist.csv";
    std::ofstream out(strFile);

    std::queue<std::vector<std::string>> q;
    q.push({ "name", "age", "ip" });
    q.push({ "Tom", std::to_string(std::numeric_limits<uint64_t>::max()).c_str(), "172.30.10.29" });
    q.push({ "Plus", "22", "172.30.10.18" });
    q.push({ "Andy", "27", "172.30.10.21" });

    for (int i = 0; i < 100000; ++i)
    {
        q.push({ "Andy" + std::to_string(i), std::to_string(i), "172.30.10.21" });
    }

    auto writer = csv::make_csv_writer(out);
    for (; !q.empty(); q.pop())
        writer.write_row(q.front());

    out.close();
}

TEST(dmcsv, dmcsv_read) {
    try
    {
        std::string strFile = "slist.csv";
        csv::CSVReader reader(strFile, csv::DEFAULT_CSV);
        csv::CSVRow rows;
        uint64_t qwCount = 0;
        for (size_t i = 0; reader.read_row(rows); i++) {
            qwCount += rows["age"].get<uint64_t>();
        }
        std::cout << qwCount << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
