#ifndef CustomerFactory_h__
#define CustomerFactory_h__

#include "stdafx.h"
#include "ACustomer.h"
#include "PostpaidCustomer.h"
#include "PrepaidCustomer.h"


using namespace std;

class CustomerFactory 
{
public:
    enum class TypeOfCustomers
    {
        UNKNOWN,
        PREPAID,
        POSTPAID
    };

    static shared_ptr<ACustomer> createCustomer( TypeOfCustomers customerType,
                                                 const int32_t id,
                                                 const string name,
                                                 const string phoneNumber,
                                                 int32_t balance,
                                                 int32_t totalCallDuration );
};
#endif // CustomerFactory_h__