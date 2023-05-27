#include "University.h"
using namespace std;

ostream& operator<<(ostream& os, const University& uni)
{
    os << "University name: " << uni.name;
    os << "Location: " << uni.location;
    os << "Rank: " << uni.rank;
    // Output other fields in a similar way

    return os;
}
