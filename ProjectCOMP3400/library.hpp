#include <iostream>
#include <unordered_map>
#include <initializer_list>
#include <vector>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

constexpr int num_provinces = 5;
constexpr int num_customers = 100;
constexpr int num_energy_categories = 4;

void getCustomerInfo(std::string &input, std::string &CustomerID, std::string &Fname, std::string &Lname, std::string &PhoneNumber, std::string &Email, double &balance, std::string &Street, std::string &City, std::string &PostalCode, std::string &PName) {
    std::cout << "Enter Customer ID : ";
    std::cin >> CustomerID;
    std::cout << "Enter First Name : ";
    std::cin >> Fname;
    std::cout << "Enter Last Name : ";
    std::cin >> Lname;
    std::cout << "Enter Phone Number : ";
    std::cin >> PhoneNumber;
    std::cout << "Enter Email : ";
    std::cin >> Email;
    std::cout << "Enter balance : ";
    std::cin >> balance;
    std::cin.ignore();
    std::cout << "Enter Street : ";
    getline(std::cin, input);
    std::cout << "Enter City : ";
    std::cin >> City;
    std::cout << "Enter Postal Code : ";
    std::cin >> PostalCode;
    std::cout << "Enter Province Name : ";
    std::cin >> PName;
    return;
}

std::string getFile(std::ifstream &inFile) {
    std::string filename;
    std::regex re{ ".*\.txt" };
    do {
        std::cout << "Enter txt file : ";
        std::cin >> filename;
    } while (!std::regex_match(filename, re));
    inFile.open(filename);
    if (!inFile) {
        throw std::invalid_argument("Not a valid file name! (Or perhaps some other issue...)");
    }
    return filename;
}

std::string getCustomerID(std::string input) {
    std::regex CustomerIDPattern{ "[0-9]{9}" };
    do {
        std::cout << "Enter Customer ID : ";
        std::cin >> input;
    } while (!std::regex_match(input, CustomerIDPattern));
    return input;
}

class Customer {
private:
    std::string CustomerID;
    std::string Fname;
    std::string Lname;
    std::string PhoneNumber;
    std::string Email;
    double balance;
    std::string Street;
    std::string City;
    std::string PostalCode;
    std::string PName;
    bool PaymentOverdue = false;
public:
    Customer() : balance{ 0.0 } {}
    Customer(std::string CustomerID, std::string Fname, std::string Lname, std::string PhoneNumber,
        std::string Email, double balance, std::string Street, std::string City, std::string PostalCode,
        std::string PName) : 
        CustomerID{ CustomerID }, Fname{ Fname }, Lname{ Lname }, 
        PhoneNumber{ PhoneNumber }, Email{ Email }, balance{ balance },
        Street{ Street }, City{ City }, PostalCode{ PostalCode }, PName{ PName } {}
    Customer& printCustomer() {
        std::cout << "----------------------\n";
        std::cout << "CustomerID : " << CustomerID << "\nFname : " << Fname
            << "\nLname : " << Lname << "\nPhone Number : " << PhoneNumber
            << "\nEmail : " << Email << "\nBalance : " << balance
            << "\nStreet : " << Street << "\nCity : " << City << "\nPostal Code : " << PostalCode << "\nProvince Name : " << PName << "\n\n";
        return (*this);
    }
    double balanceGetter() const {
        return balance;
    }
    Customer& makePayment(double payment) {
        if (payment > 0) {
            balance -= payment;
            if (balance >= 0)
                PaymentOverdue = false;
        }
        return (*this);
    }
    bool operator<(const Customer& customer) const {
        return this->CustomerID < customer.CustomerID;
    }
};

class Province {
private:
    std::string ProvinceName;
    std::unordered_map<std::string, Customer> customersMap;
public:
    Province() = default;
    Province(std::string ProvinceName) : ProvinceName{ ProvinceName } {}
    void printProvince() {
        std::cout << "(Province : " << ProvinceName << ')';
        if (customersMap.empty()) {
            std::cout << "->EMPTY\n";
            return;
        }
        std::cout << "\n\n";
        for (auto& customer : customersMap) {
            customer.second.printCustomer();
        }
    }
    void provinceNameSetter(std::string ProvinceName) {
        if (ProvinceName.empty())
            throw std::invalid_argument("Province name must be non-null!!!");
        this->ProvinceName = ProvinceName;
    }
    Customer* __findCustomer(std::string CustomerID) {
        if (customersMap.contains(CustomerID))
            return &customersMap[CustomerID];
        return nullptr;
    }
    std::string provinceNameGetter() const {
        return ProvinceName;
    }
    std::unordered_map<std::string, Customer>& customersMapGetter() {
        return customersMap;
    }
};

class EnergyProvider {
private:
    std::string CompanyName;
    std::vector<Province> provinces;
    std::set<Customer> OverdueCustomers;
    std::set<std::string> CustomerIDs;
    std::unordered_map<std::string, double> Imports;
    std::unordered_map<std::string, double> Exports;
public:
    // Make some sort of 30 day timer!!
    EnergyProvider(std::string CompanyName, std::initializer_list<std::string> list) : CompanyName{ CompanyName } {
        if (list.size() != num_provinces)
            throw std::invalid_argument("Number of arguments in initializer list must be exactly five!!!");
        provinces.reserve(num_provinces);
        for (auto& ProvinceName : list) {
            Province province(ProvinceName);
            provinces.push_back(province);
        }
        Imports.reserve(num_energy_categories);
        Exports.reserve(num_energy_categories);
        Imports.insert({ {"Crude Oil", 0.0}, {"Solar", 0.0}, {"Nuclear", 0.0}, {"Natural gas", 0.0} });
        Exports.insert({ {"Crude Oil", 0.0}, {"Solar", 0.0}, {"Nuclear", 0.0}, {"Natural gas", 0.0} });
    }
    Customer* findCustomer(std::string CustomerID) {
        for (Province& province : provinces) {
            Customer* customerPtr;
            if ((customerPtr = province.__findCustomer(CustomerID)) != nullptr) {
                return customerPtr;
            }
        }
        return nullptr;
    }
    EnergyProvider &addCustomer(std::string CustomerID, std::string Fname, std::string Lname, std::string PhoneNumber,
        std::string Email, double balance, std::string Street, std::string City, std::string PostalCode,
        std::string PName) {
        bool flag = false;
        if (CustomerIDs.find(CustomerID) != CustomerIDs.end()) {
            std::cout << "Customer ID already exists!\n";
            flag = true;
        }
        else {
            Customer newCustomer(CustomerID, Fname, Lname, PhoneNumber,
                Email, balance, Street, City, PostalCode, PName);
            CustomerIDs.insert(CustomerID);
            int index = 0;
            for (; index < num_provinces; index++) {
                if (provinces[index].provinceNameGetter() == PName)
                    break;
            }
            if (index < num_provinces)
                provinces[index].customersMapGetter().insert({ CustomerID, newCustomer });
            else
                throw std::invalid_argument("Not a valid province!!\n");
        }
        return (*this);
    }
    EnergyProvider& removeCustomer(std::string CustomerID) {
        for (auto &province : provinces) {
            if (province.__findCustomer(CustomerID) != nullptr) {
                province.customersMapGetter().erase(CustomerID);
                break;
            }
        }
        return (*this);
    }
    // Maybe change back to std::vector and use clear function every call to this function
    std::set<Customer>& overdue() {
        for (Province& province : provinces) {
            for (auto& customer : province.customersMapGetter()) {
                if (customer.second.balanceGetter() > 0)
                    OverdueCustomers.insert(customer.second);
            }
        }
        return OverdueCustomers;
    }
    void printOverdue() {
        overdue();
        auto start = OverdueCustomers.begin();
        for (auto i = start; i != OverdueCustomers.end(); i++) {
            // lol
            const_cast<Customer &>(*i).printCustomer();
        }
    }
    EnergyProvider& printCustomers() {
        std::cout << "\nCompany : " << CompanyName << "\n\n";
        for (auto& province : provinces) {
            province.printProvince();
        }
        return (*this);
    }
    // Maybe make some changes to the naming scheme??
    EnergyProvider &printCustomer(std::string CustomerID) {
        if (findCustomer(CustomerID) == nullptr)
            std::cout << "Customer ID does not exist\n";
        else 
            findCustomer(CustomerID)->printCustomer();
        return (*this);
    }
    EnergyProvider &makePayment(std::string CustomerID, double amount) {
        Customer* customerPtr = findCustomer(CustomerID);
        if (customerPtr == nullptr) {
            std::cout << "Customer ID does not exist!\n";
        }
        else {
            customerPtr->makePayment(amount);
        }
        return (*this);
    }
};