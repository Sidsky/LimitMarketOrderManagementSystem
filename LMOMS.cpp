#include "LM_OMS.h"

void LM_OMS::process_order(double& price, int& order_id, int& number_of_shares, string& type, stringstream& out) {  // O(logN)
    map<double, vector<tuple<int, int, bool> >, greater<> > *mp;

    if (type=="S") mp = &ASK;
    else mp = &BID;

    if (mp->contains(price)) {
        (*mp)[price].emplace_back(make_tuple(number_of_shares, order_id, false));
        out<<"New order added at the end of the queue of price HKD" << price<<endl;
    } else {
        vector<tuple<int, int, bool> > v;
        v.emplace_back(number_of_shares, order_id, false);
        mp->insert({price, v});
        out << "New order added for price HKD" << price << endl;
    }
}

void LM_OMS::order_matching(double& price, int& number_of_shares, string& type) { // O(N*S); N = Size of the map, S = Size of the vector.
    map<double, vector<tuple<int, int, bool> >, greater<> > *mp;

    if (type == "S") mp = &BID;
    else mp = &ASK;

    for (it=mp->begin(); it != mp->end() && number_of_shares > 0; ++it)  { // O(N); N = Size of the map.

        if (type == "S" and price <= it->first) {

            for (int i=0; i < it->second.size(); i++) { // O(S);

                int available_shares = get<0>(it -> second[i]); // O(1)

                if (available_shares >= number_of_shares) { // O(1)
                    get<0>(it -> second[i]) -= number_of_shares;
                    cout << number_of_shares << " share(s) sold at " << it->first << " HKD" << endl;
                    number_of_shares = 0;

                } else { // O(1)
                    cout << available_shares << " share(s) sold at " << it->first << " HKD" << endl;
                    number_of_shares -= available_shares;
                    get<0>(it -> second[i]) = 0;
                }
                get<2>(it->second[i]) = true;
            }

            erase_if(it->second,[](tuple<int, int, bool> & x)  { // Linear Time
                return get<0>(x) == 0;});

        } else if (type == "B" && it->first <= price) { // O(1)

            for (int i=0; i < it->second.size(); i++) { // O(S); S = Size of the vector.

                int available_shares = get<0>(it -> second[i]); // O(1)

                if (available_shares >= number_of_shares) { // O(1)
                    get<0>(it -> second[i]) -= number_of_shares;
                    cout << number_of_shares << " share(s) sold at " << it->first << " HKD" << endl;
                    number_of_shares = 0;

                } else { // O(1)
                    cout << available_shares << " share(s) sold at " << it->first << " HKD" << endl;
                    number_of_shares -= available_shares;
                    get<0>(it -> second[i]) = 0;
                }
                get<2>(it->second[i]) = true;
            }
            erase_if(it->second,[](tuple<int, int, bool> & x)  { // Linear Time
                return get<0>(x) == 0;});
        }
    }

    erase_if(*mp,[](pair<const double, vector<tuple<int, int, bool> > >& x)  { // Linear Time
        return x.second.size() == 0;});
}

void LM_OMS::delete_order (double& price, int& order_id, string& type, stringstream& out) {
    map<double, vector<tuple<int, int, bool> >, greater<> > *mp;

    if (type == "S") mp = &ASK;
    else mp = &BID;

    it = mp->find(price); // O(logN)
    int i;

    if (it == mp -> end()) {
        out << "Cannot delete order. It has either been settled or was never placed." << endl;
    } else {
        for (i = 0; i < it -> second.size(); ++i) { // O(N); N = size of the vector;
            if (get<1>(it -> second[i]) == order_id) {
                if (!get<2>(it -> second[i])) {
                    out << "Delete successful. All share(s) returned" << endl;
                } else {
                    out << "Partial ordered has already been fulfilled. Remaining " << get<0>(it->second[i])
                        << " share(s) returned." << endl;
                }
                break;
            }
        }
        it->second.erase((it->second).begin() + i);
    }
    erase_if(*mp,[](pair<const double, vector<tuple<int, int, bool> > >& x)  {
        return x.second.size() == 0;});
}


stringstream LM_OMS::execute_order(const string& order) {
    stringstream out;

    stringstream ss(order);
    string details;
    vector<string> order_details;

    while (!ss.eof()) {
        getline(ss, details, ',');
        order_details.push_back(details);
    }

    double price = stod(order_details[4]);
    int number_of_shares = stoi(order_details[3]);
    string type = order_details[2];
    int order_id = stoi(order_details[1]);

    if (order_details[0] == "A") {
        order_matching(price, number_of_shares, type);
        if (number_of_shares > 0) {
            process_order(price, order_id, number_of_shares, type, out);
        }
    } else if (order_details[0] == "X") {
        delete_order(price, order_id, type, out);
    } else {
        cout << "Invalid Instruction." << endl;
    }
    return out;
}

void LM_OMS::print_order_book(){
    cout<<"=================\nASK"<<endl;

    for_each(ASK.begin(), ASK.end(),
             [](pair<const double, vector<tuple<int, int, bool>>>& x){
                 cout<<x.first<<": ";
                 for_each(x.second.begin(),x.second.end(),[](const tuple<int, int, bool>& elem) { cout<<get<0>(elem)<<" ";} );
                 cout<<endl;
             });

    cout<<"\n------------------\n";

    for_each(BID.begin(), BID.end(),
             [](pair<const double, vector<tuple<int, int, bool>>>& x){
                 cout<<x.first<<": ";
                 for_each(x.second.begin(),x.second.end(),[](const tuple<int, int, bool>& elem) { cout<<get<0>(elem)<<" ";} );
                 cout<<endl;
             });

    cout<<"\nBID\n================="<<endl;
}
