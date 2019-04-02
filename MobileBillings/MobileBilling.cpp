#include "stdafx.h"
#include "MobileBilling.h"

MobileBilling::MobileBilling()
    : m_postpaidSortedById()
    , m_postpaidSortedByName()
    , m_postpaidSortedByNumber()
    , m_prepaidSortedById()
    , m_prepaidSortedByName()
    , m_prepaidSortedByNumber()
    , m_numberOfCustomer(0)
{
    /*empty*/
}

void MobileBilling::addCustomer( CustomerFactory::TypeOfCustomers customerType,
                                 const int32_t id,
                                 const string name,
                                 const string phoneNumber,
                                 int32_t balance,
                                 int32_t totalCallDuration )
{
    if (searchByNumber(phoneNumber))
    {
        throw exception("Duplicated number error");
    }

    auto customer = CustomerFactory::createCustomer(customerType,
                                                    id,
                                                    name,
                                                    phoneNumber,
                                                    balance,
                                                    totalCallDuration);

    PairOfCustomers tmp = searchById(id);
    switch (customerType)
    {
        case CustomerFactory::TypeOfCustomers::PREPAID:
        {
            if (tmp.second)
            {
                throw exception("Duplicated id error");
            }
            shared_ptr<PrepaidCustomer> prepaidCustomer =
                        dynamic_pointer_cast<PrepaidCustomer>(customer);

            m_prepaidSortedById.insert(prepaidCustomer);
            m_prepaidSortedByName.insert(prepaidCustomer);
            m_prepaidSortedByNumber.insert(prepaidCustomer);
            break;
        }
        case CustomerFactory::TypeOfCustomers::POSTPAID:
        {
            if (tmp.first)
            {
                throw exception("Duplicated id error");
            }
            shared_ptr<PostpaidCustomer> postpaidCustomer =
                        dynamic_pointer_cast<PostpaidCustomer>(customer);

            m_postpaidSortedById.insert(postpaidCustomer);
            m_postpaidSortedByName.insert(postpaidCustomer);
            m_postpaidSortedByNumber.insert(postpaidCustomer);
            break;
        }
        default:
            break;
    }
    m_numberOfCustomer++;
}

void MobileBilling::deleteCustomer(shared_ptr<ACustomer> customer)
{
    if (auto prepaidCustomer = dynamic_pointer_cast<PrepaidCustomer>(customer))
    {
        m_prepaidSortedById.erase(prepaidCustomer);
        m_prepaidSortedByName.erase(prepaidCustomer);
        m_prepaidSortedByNumber.erase(prepaidCustomer);
        m_numberOfCustomer--;
    }
    else if (auto postpaidCustomer = dynamic_pointer_cast<PostpaidCustomer>(customer))
    {
        m_postpaidSortedById.erase(postpaidCustomer);
        m_postpaidSortedByName.erase(postpaidCustomer);
        m_postpaidSortedByNumber.erase(postpaidCustomer);
        m_numberOfCustomer--;
    }
}

double MobileBilling::getAveragePostPaidCallDuration()
{
    int32_t tmp = 0;
    for (auto customer : m_postpaidSortedByNumber)
    {
        tmp += customer->enquireCallDuration();
    }
    return tmp / m_postpaidSortedByNumber.size();
}

double MobileBilling::getAveragePrePaidBalance()
{
    int32_t tmp = 0;
    for (auto customer : m_prepaidSortedByNumber)
    {
        tmp += customer->enquireBalance();
    }
    return tmp / m_prepaidSortedByNumber.size();
}

list<shared_ptr<PostpaidCustomer>> MobileBilling::queryPostpaidCustomers(int32_t callDuration)
{
    list<shared_ptr<PostpaidCustomer>> result;
    for (auto customer : m_postpaidSortedByNumber)
    {
        if (customer->enquireCallDuration() > callDuration)
        {
            result.push_back(customer);
        }
    }
    return result;
}

list<shared_ptr<PrepaidCustomer>> MobileBilling::queryPrepaidCustomers(int32_t balance)
{
    list<shared_ptr<PrepaidCustomer>> result;
    for (auto customer : m_prepaidSortedByNumber)
    {
        if (customer->enquireBalance() > balance)
        {
            result.push_back(customer);
        }
    }
    return result;
}

PairOfCustomers MobileBilling::searchById(int32_t customerId)
{
    PairOfCustomers result = { nullptr, nullptr };

    auto postpaidCustomer = m_postpaidSortedById.find(customerId);

    if (postpaidCustomer != m_postpaidSortedById.end())
    {
        result.first = *postpaidCustomer;
    }

    auto prepaidCustomer = m_prepaidSortedById.find(customerId);

    if (prepaidCustomer != m_prepaidSortedById.end())
    {
        result.second = *prepaidCustomer;
    }

    return result;
}

list<shared_ptr<ACustomer>> MobileBilling::searchByName(string name)
{
    list<shared_ptr<ACustomer>> result;

    using iteratorPrepaidCustomer 
        = multiset<shared_ptr<PrepaidCustomer>, ACustomer::CustomerCompareName>::iterator;
    using iteratorPostpaidCustomer 
        = multiset<shared_ptr<PostpaidCustomer>, ACustomer::CustomerCompareName>::iterator;

    pair<iteratorPrepaidCustomer, iteratorPrepaidCustomer> resultPrepaid
        = m_prepaidSortedByName.equal_range(name);
    pair<iteratorPostpaidCustomer, iteratorPostpaidCustomer> resultPostpaid
        = m_postpaidSortedByName.equal_range(name);

    for (iteratorPrepaidCustomer it = resultPrepaid.first; it != resultPrepaid.second; it++)
    {
        result.push_back(*it);
    }

    for (iteratorPostpaidCustomer it = resultPostpaid.first; it != resultPostpaid.second; it++)
    {
        result.push_back(*it);
    }

    return result;
}

shared_ptr<ACustomer> MobileBilling::searchByNumber(string number)
{
    shared_ptr<ACustomer> result;

    auto customerPostpaid = m_postpaidSortedByNumber.find(number);
    auto customerPrepaid = m_prepaidSortedByNumber.find(number);

    if (customerPostpaid != m_postpaidSortedByNumber.end())
    {
        result = *customerPostpaid;
    }
    else if(customerPrepaid != m_prepaidSortedByNumber.end())
    {
        result = *customerPrepaid;
    }

    return result;
}

int32_t MobileBilling::getNumberOfCustomer() const
{
    return m_numberOfCustomer;
}