#include "dmcsv_parser.hpp"
#include "dmcsv_writer.hpp"
#include <vector>
#include <queue>

int main()
{
    const char * test_file = "round_trip.csv";
    //std::ofstream out(test_file);

    //std::queue<std::vector<std::string>> q;
    //q.push({ "name", "age", "ip" });
    //q.push({ "Tom", "23", "172.30.10.29" });
    //q.push({ "Plus", "22", "172.30.10.18" });
    //q.push({ "Andy", "27", "172.30.10.21" });

    //auto writer = csv::make_csv_writer(out);
    //for (; !q.empty(); q.pop())
    //    writer.write_row(q.front());

    //out.close();
    try
    {
        csv::CSVReader reader(test_file);
        csv::CSVRow rows;

        for (size_t i = 0; reader.read_row(rows); i++) {
            std::cout << rows["name"].get<std::string>() << "\t"
                << rows["age"].get<std::string>() << "\t"
                << rows["ip"].get<std::string>() << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }



    return 0;
}
