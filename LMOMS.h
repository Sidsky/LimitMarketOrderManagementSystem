#ifndef LHFT_LMOMS_H
#define LHFT_LMOMS_H

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <tuple>
#include <functional>

class LMOMS {
private:
    std::map<double, std::vector<std::tuple<int, int, bool> >, std::greater<> > ASK;
    std::map<double, std::vector<std::tuple<int, int, bool> >, std::greater<> > BID;
    std::map<double, std::vector<std::tuple<int, int, bool> > > :: iterator it;

    void process_order (double price, int order_id, int number_of_shares, std::string & type, std::stringstream & out);

    void order_matching (double price, int number_of_shares, std::string & type, std::stringstream & out);

    void delete_order (double price, int order_id, std::string & type, std::stringstream & out);

public:
    std::stringstream execute_order (const std::string & order);

    void print_order_book();
};
#endif //LHFT_LMOMS_H
