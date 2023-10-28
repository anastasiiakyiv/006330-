#include <iostream>
#include <string>
#include <vector>

class IPAddress
{
private:
    int IPv4_1, IPv4_2, IPv4_3, IPv4_4;
    std::vector<std::string> IPv6_blocks;
    bool isIPv6;

    void printIPv4Status() {
        std::cout << "IPv4: " << IPv4_1 << "." << IPv4_2 << "." << IPv4_3 << "." << IPv4_4;
    }

    void printIPv6Status() {
        std::cout << "IPv6: ";
        for (size_t i = 0; i < IPv6_blocks.size(); ++i) {
            std::cout << IPv6_blocks[i];
            if (i < IPv6_blocks.size() - 1) {
                std::cout << ":";
            }
        }
    }

public:
    IPAddress(int IPv4_1, int IPv4_2, int IPv4_3, int IPv4_4)  
        : IPv4_1(IPv4_1), IPv4_2(IPv4_2), IPv4_3(IPv4_3), IPv4_4(IPv4_4), isIPv6(false) {}

    IPAddress(const std::vector<std::string>& IPv6_blocks)
        : IPv6_blocks(IPv6_blocks), isIPv6(true) {}

    IPAddress(const IPAddress& other)
        : IPv4_1(other.IPv4_1), IPv4_2(other.IPv4_2), IPv4_3(other.IPv4_3), IPv4_4(other.IPv4_4),
        IPv6_blocks(other.IPv6_blocks) {}

    void printStatus() {
        if (isIPv6) {
            printIPv6Status();
        }
        else {
            printIPv4Status();
        }
    }
};
   
class IPAddressChecked : public IPAddress
{
private:
    bool IPv4_check;
    bool IPv6_check;

public:
    IPAddressChecked(int IPv4_1, int IPv4_2, int IPv4_3, int IPv4_4)
        : IPAddress(IPv4_1, IPv4_2, IPv4_3, IPv4_4), IPv4_check(false){
        if (IPv4_1 >= 0 && IPv4_1 <= 255 && IPv4_2 >= 0 && IPv4_2 <= 255 && IPv4_3 >= 0 && IPv4_3 <= 255 && IPv4_4 >= 0 && IPv4_4 <= 255) {
            IPv4_check = true;
        }
    }

    IPAddressChecked(const std::vector<std::string>& IPv6_blocks)
        : IPAddress(IPv6_blocks), IPv6_check(true) {
        if (IPv6_blocks.size() != 8) {
            IPv6_check = false;
        }
        else {
            for (const std::string& block : IPv6_blocks) {
                if (block.size() != 4) {
                    IPv6_check = false;
                    break;
                }
                for (char c : block) {
                    if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
                        IPv6_check = false;
                        break;
                    }
                }
            }
        }
    }

    IPAddressChecked(const IPAddressChecked& other)
        : IPAddress(other), IPv4_check(other.IPv4_check), IPv6_check(other.IPv6_check) {}

    bool isIPv4Valid() {
        return IPv4_check;
    }

    bool isIPv6Valid() {
        return IPv6_check;
    }

    void printStatus() {
        IPAddress::printStatus();
        std::cout << " - " << (isIPv4Valid() || isIPv6Valid() ? "Valid" : "Invalid") << std::endl;
    }
};

int main()
{
    int IPv4_1, IPv4_2, IPv4_3, IPv4_4;
    std::vector<std::string> IPv6_blocks(8);

    std::cout << "Enter the IPv4 address (four integers separated by spaces): ";
    std::cout << std::endl;
    if (!(std::cin >> IPv4_1 >> IPv4_2 >> IPv4_3 >> IPv4_4)) {
        std::cout << std::endl;
        std::cout << "Invalid input for IPv4." << std::endl;
        return 1;
    }

    std::cout << "Enter the IPv6 address (eight blocks separated by spaces): ";
    std::cout << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cin >> IPv6_blocks[i];
    }

    IPAddress* IPv4_address_o1;
    IPv4_address_o1 = new IPAddress(IPv4_1, IPv4_2, IPv4_3, IPv4_4);
    IPAddressChecked* IPv4_address_o2;
    IPv4_address_o2 = new IPAddressChecked(IPv4_1, IPv4_2, IPv4_3, IPv4_4);
    IPAddressChecked IPv4_address_o3(IPv4_1, IPv4_2, IPv4_3, IPv4_4);

    IPAddress* IPv6_address_o1;
    IPv6_address_o1 = new IPAddress(IPv6_blocks);
    IPAddressChecked* IPv6_address_o2;
    IPv6_address_o2 = new IPAddressChecked(IPv6_blocks);
    IPAddressChecked IPv6_address_o3(IPv6_blocks);

    std::cout << std::endl;
    IPv4_address_o1->printStatus();
    std::cout << std::endl;
    IPv4_address_o2->printStatus();
    IPv4_address_o3.printStatus();
    static_cast<IPAddressChecked*>(IPv4_address_o2)->printStatus();

    std::cout << std::endl;
    IPv6_address_o1->printStatus();
    std::cout << std::endl;
    IPv6_address_o2->printStatus();
    IPv6_address_o3.printStatus();
    static_cast<IPAddressChecked*>(IPv6_address_o2)->printStatus();

    delete IPv4_address_o1;
    delete IPv4_address_o2;
    delete IPv6_address_o1;
    delete IPv6_address_o2;
    return 0;
}