#ifndef LHFT_LM_OMS_H
#define LHFT_LM_OMS_H

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <sstream>

using namespace std;

//Limit Market Order Management System

class LM_OMS {
private:
    map<double, vector<tuple<int, int, bool> >, greater<> > ASK;
    map<double, vector<tuple<int, int, bool> >, greater<> > BID;
    map<double, vector<tuple<int, int, bool> > > :: iterator it;

    void process_order (double& price, int& order_id, int& number_of_shares, string& type, stringstream& out);

    void order_matching (double& price, int& number_of_shares, string& type);

    void delete_order (double& price, int& order_id, string& type, stringstream& out);

public:
    stringstream execute_order (const string& order);

    void print_order_book();

};
#endif //LHFT_LM_OMS_H
