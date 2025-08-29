#include <mysqlx/xdevapi.h>
#include <iostream>
#include <vector>

int main()
{
    using namespace mysqlx;

    Session sess("localhost", 33060, "root", "IFe@2024");
    Schema db = sess.getSchema("world");
    std::vector<Table> tables = db.getTables();
    
    std::cout << "Tables from schema world\n";
    for(const auto& t : tables) {
        std::cout << "\t" << t.getName() << std::endl;
    }
}