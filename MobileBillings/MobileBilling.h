#ifndef MobileBilling_h__
#define MobileBilling_h__

#include "stdafx.h"
#include "PostpaidCustomer.h"
#include "PrepaidCustomer.h"
#include "CustomerFactory.h"

using namespace std;
using PairOfCustomers = pair<shared_ptr<PostpaidCustomer>, shared_ptr<PrepaidCustomer>>;

// Class that contains database and handles queries
class MobileBilling
{
public:

    // Constructor should setup "database"
    MobileBilling();
    ~MobileBilling() = default;

    /*
    Method which should add new customers according to this parameters:
      1. unique phone numbers for all customers -> (throw "duplicated number error")
      2. unique id in customer type -> (throw "duplicated id error")
    */
    void addCustomer( CustomerFactory::TypeOfCustomers customerType,
                      const int32_t id,
                      const string name,
                      const string phoneNumber,
                      int32_t balance,
                      int32_t totalCallDuration );

    /*
    Delete customer from database
    */
    void deleteCustomer(shared_ptr<ACustomer> customer);

    /*
    Searches list of prepaid and postpaid customers and if found at least one returns
    pair of customers
    */
    PairOfCustomers searchById(int32_t customerId);

    /*
    Search the database for the customer name, if more than one is the same return the list,
    otherwise return null
    */
    list<shared_ptr<ACustomer>> searchByName(string name);

    /*
    Search the database for the number if found return the number otherwise return null.
    */
    shared_ptr<ACustomer> searchByNumber(string number);

    /*
    Calculate average postpaid duration and return the result if 
    there are no postpaid customers return null.
    */
    double getAveragePostPaidCallDuration();

    /*
    Returns a list of postpaid customers that have higher call duration than specified
    */
    list<shared_ptr<PostpaidCustomer>> queryPostpaidCustomers(int32_t callDuration);

    /*
    Calculate average prepaid balance and return the result if
    there are no prepaid customers return null.
    */
    double getAveragePrePaidBalance();

    /*
    Returns a list of prepaid customers that have higher balance than specified
    */
    list<shared_ptr<PrepaidCustomer>> queryPrepaidCustomers(int32_t balance);

    int32_t getNumberOfCustomer() const;

private:
    /*
    General idea:
    search operation should have O(lon n) -> searchById, searchByName, searchByNumber
    implementation will be done using sets (since I haven't implement patterns like visitor and
    similar patterns I will try to separate set of customers to multiple lists to 
    avoid casting a lot (since this is prototyping anyway)
    Other query's will be implemented in O(n) speed since no sorting will be done
    */

    /* 
       This two lists must contain all customers since number is unique for both types of customer
       for every query we will iterate them 
    */
    set<shared_ptr<PrepaidCustomer>, ACustomer::CustomerCompareNumber> m_prepaidSortedByNumber;
    set<shared_ptr<PostpaidCustomer>, ACustomer::CustomerCompareNumber> m_postpaidSortedByNumber;

    set<shared_ptr<PrepaidCustomer>, ACustomer::CustomerCompareId> m_prepaidSortedById;
    set<shared_ptr<PostpaidCustomer>, ACustomer::CustomerCompareId> m_postpaidSortedById;

    multiset<shared_ptr<PrepaidCustomer>, ACustomer::CustomerCompareName> m_prepaidSortedByName;
    multiset<shared_ptr<PostpaidCustomer>, ACustomer::CustomerCompareName> m_postpaidSortedByName;

    int32_t m_numberOfCustomer;
};
#endif // MobileBilling_h__