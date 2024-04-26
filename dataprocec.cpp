// dataprocec.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <map>
#include <iostream>
#include <string>
class DataProcessor
{
    std::map<std::string, int> data;
    std::map<std::string, int> tmpdata;
    bool transaction = false;
public:

    int get(std::string key) {
        
        if (data.find(key) != data.end()) {
			return data[key];
		}
		return NULL;
    }

    void put(std::string key, int val) {
        if (transaction) {
            tmpdata[key] = val;
        }
        else {
            throw std::runtime_error("cannot put when no transaction active.");
        }
    }

    void begin_transaction() {
        transaction = true;
    }

    void commit() {
        if (!transaction) {
            std::cout << "AB";
            throw std::runtime_error("cannot commit when no transaction active.");

        }
        for (auto it = tmpdata.begin(); it != tmpdata.end(); it++) {
			data[it->first] = it->second;
		}
        tmpdata.clear();
        transaction = false;
    }

    void rollback() {
        if (!transaction) {
            throw std::runtime_error("cannot rollback when no transaction active.");

        }
        tmpdata.clear();
    }
    DataProcessor() {

    }

};
int main()
{
    DataProcessor d;
    std::cout << d.get("a")<<std::endl;
    //d.put("a", 1);
    d.begin_transaction();
    d.put("a", 5);
    std::cout << d.get("a") << std::endl;
    d.put("a", 6);
    d.commit();
    std::cout << "A";
    std::cout << d.get("a") << std::endl;
    //d.commit();
    //d.rollback();
    std::cout << d.get("B") << std::endl;
    d.begin_transaction();
    d.put("B", 2);
    d.rollback();
    d.commit();
    std::cout<<d.get("B") <<std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
