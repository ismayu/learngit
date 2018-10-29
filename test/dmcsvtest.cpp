#include "dmcsv_parser.hpp"
#include "dmcsv_writer.hpp"
#include <vector>
#include <queue>

#include "gtest.h"
#include "dsv_filter.hpp"

uint64_t dmcsv_count = 0;
std::string strFile = "slist.csv";
TEST(dmcsv, dmcsv_write) {
    std::ofstream out(strFile);

    std::queue<std::vector<std::string>> q;
    q.push({ "name", "age", "ip" });

    for (int i = 0; i < 200000; ++i)
    {
        dmcsv_count += i;
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
        uint64_t qwCount = dmcsv_count;

        csv::CSVReader reader(strFile, csv::DEFAULT_CSV);
        csv::CSVRow rows;
        for (size_t i = 0; reader.read_row(rows); i++) {
            //qwCount -= rows["age"].get<uint64_t>();
            qwCount -= rows[1].get<uint64_t>();
            //std::cout << rows["name"].get<std::string>() << "," << rows["age"].get<std::uint64_t>() << "," << rows["ip"].get<std::string>() << std::endl;
        }
        std::cout << qwCount << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

uint64_t dsv_filter_count = 0;

TEST(dsv_filter, dsv_filter_read) {

    dsv_filter oFilter;
    if (!oFilter.load(strFile))
    {
        return;
    }

    uint64_t qwCount = dmcsv_count;

    for (int i = 1; i < static_cast<int>(oFilter.grid().row_count()); ++i)
    {
        strtk::token_grid::row_type row = oFilter.grid().row(i);
        qwCount -= row.get<uint64_t>(1);
    }

    std::cout << qwCount << std::endl;
}
