#include <mysqlx/xdevapi.h>
#include <iostream>
#include <vector>
#include "config.h"

int main()
{
    server::loadConfigFile();

    std::string
        host = server::getConfig("host"),
        _port = server::getConfig("port"),
        user = server::getConfig("user"),
        password = server::getConfig("password");

	int port = !_port.empty() ? std::stoi(_port) : 33060;

    if (host.empty() || user.empty()) {
        std::cout << "[ServerConfiguration] configuration not found\n";
        return 1;
    }

	std::cout
        << "[ServerConfiguration]" << std::endl
        << "Host: " << host << std::endl
        << "Port: " << port << std::endl
        << "User: " << user << std::endl;

    mysqlx::Session *sess = nullptr;

    try {
        sess = new mysqlx::Session(host, port, user, password);
    } catch (const mysqlx::Error &err) {
        std::cout << "ERROR: " << err << std::endl;
        return 1;
    } catch (std::exception &ex) {
        std::cout << "STD EXCEPTION: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "UNKNOWN EXCEPTION" << std::endl;
        return 1;
	}

    mysqlx::SqlStatement stmt = sess->sql("SELECT Name, Population FROM world.country WHERE Population > 100000000 ORDER BY Population DESC");
    mysqlx::SqlResult result = stmt.execute();

	std::cout << "Countries with population over 100 million (biggest first):" << std::endl;
    for(const auto& row : result.fetchAll()) {
        std::cout << "\tName: " << row[0] << ", Population: " << row[1] << std::endl;
	}

	sess->close();
    delete sess;

	return 0;
}