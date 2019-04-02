#include "stdafx.h"
#include "CustomerFactory.h"

shared_ptr<ACustomer> CustomerFactory::createCustomer( TypeOfCustomers customerType,
                                                       const int32_t id,
                                                       const string name,
                                                       const string phoneNumber,
                                                       int32_t balance,
                                                       int32_t totalCallDuration )
{
    switch (customerType)
    {
        case TypeOfCustomers::PREPAID:
        {
            return make_shared<PrepaidCustomer>(id, name, phoneNumber, balance, totalCallDuration);
        }
        case TypeOfCustomers::POSTPAID:
        {
            return make_shared<PostpaidCustomer>(id, name, phoneNumber, balance, totalCallDuration);
        }
        case TypeOfCustomers::UNKNOWN:
        default:
        {
            throw exception("Unknown customer type error");
        }
    }
}