// Customer.cpp
#include <sstream>
#include <vector>
#include "Customer.h"

using std::ostringstream;
using std::vector;

double Customer::amountFor( const Rental& aRental ) const
{
  return aRental.getCharge();
}

std::string Customer::statement() {
  vector< Rental >::iterator iter = _rentals.begin();
  vector< Rental >::iterator iter_end = _rentals.end();
  ostringstream result;
  result << "Rental Record for " << getName() << "\n";
  for ( ; iter != iter_end; ++iter ) {
    Rental each = *iter;

    // show figures for this rental
    result << "\t" << each.getMovie().getTitle() << "\t"
           << each.getCharge() << "\n";
  }
  // add footer lines
  result << "Amount owed is " << getTotalCharge() << "\n";
  result << "You earned " << getTotalFrequentRenterPoints()
         << " frequent renter points";
  return result.str();
}

double Customer::getTotalCharge()
{
  double result = 0;
  vector< Rental >::iterator iter = _rentals.begin();
  vector< Rental >::iterator iter_end = _rentals.end();
  for ( ; iter != iter_end; ++iter ) {
    Rental each = *iter;
    result += each.getCharge();
  }
  return result;
}

int Customer::getTotalFrequentRenterPoints()
{
  int result = 0;
  vector< Rental >::iterator iter = _rentals.begin();
  vector< Rental >::iterator iter_end = _rentals.end();
  for ( ; iter != iter_end; ++iter ) {
    Rental each = *iter;
    result += each.getFrequentRenterPoints();
  }
  return result;
}

std::string Customer::htmlStatement()
{
  vector< Rental >::iterator iter = _rentals.begin();
  vector< Rental >::iterator iter_end = _rentals.end();
  ostringstream result;
  result << "<H1>Rentals for <EM>" << getName() << "</EM></H1><P>\n";
  for ( ; iter != iter_end; ++iter ) {
    Rental each = *iter;
    // show figures for each rental
    result << each.getMovie().getTitle() << ": "
           << each.getCharge() << "<BR>\n";
  }
  // add footer lines
  result << "<P>You owe <EM>" << getTotalCharge() << "</EM><P>\n";
  result << "On this rental you earned <EM>"
         << getTotalFrequentRenterPoints()
         << "</EM> frequent renter points<P>";
  return result.str();
}
