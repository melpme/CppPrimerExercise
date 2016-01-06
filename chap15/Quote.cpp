#include "Quote.hpp"
#include <iostream>
using std::ostream; using std::endl;

#include <cstddef>
using std::size_t;

// calculate and print the price for the given numbers of copies, applying any discounts
double print_total(ostream &os,
                   const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold : " << n << " total due: " << ret << endl;
    return ret;
}

// Bulk_item::net_price
double Bulk_item::net_price(size_t cnt) const {
    if (cnt >= min_qty) {
        return cnt * (1-discount) * price;
    } else {
        return cnt * price;
    }
}

//Bulk_quote::net_price
double Bulk_quote::net_price(size_t cnt) const {
    if (cnt >= min_qty) {
        return cnt * (1-discount) * price;
    } else {
        return cnt * price;
    }
}