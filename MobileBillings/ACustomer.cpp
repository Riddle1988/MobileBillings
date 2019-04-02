#include "stdafx.h"
#include "ACustomer.h"

ACustomer::ACustomer( const int32_t id,
                      const string name,
                      const string phoneNumber,
                      int32_t balance,
                      int32_t totalCallDuration )
    : m_id(id)
    , m_name(name)
    , m_phoneNumber(phoneNumber)
    , m_balance(balance)
    , m_totalCallDuration(totalCallDuration)
{
    /*empty*/
}

int32_t ACustomer::enquireBalance() const
{
    return m_balance;
}

int32_t ACustomer::enquireCallDuration() const
{
    return m_totalCallDuration;
}

void ACustomer::addCallDuration(int32_t time)
{
    m_totalCallDuration += time;
}

// CustomerCompareNumber implementation
bool ACustomer::CustomerCompareNumber::operator() (const shared_ptr<ACustomer> lhs, string rhs) const
{
    return lhs->m_phoneNumber > rhs;
}

bool ACustomer::CustomerCompareNumber::operator() (string lhs, const shared_ptr<ACustomer> rhs) const
{
    return lhs > rhs->m_phoneNumber;
}

bool ACustomer::CustomerCompareNumber::operator()
                            (const shared_ptr<ACustomer> lhs, const shared_ptr<ACustomer> rhs) const
{
    return lhs->m_phoneNumber > rhs->m_phoneNumber;
}

// CustomerCompareId implementation
bool ACustomer::CustomerCompareId::operator() (const shared_ptr<ACustomer> lhs, int32_t rhs) const
{
    return lhs->m_id > rhs;
}

bool ACustomer::CustomerCompareId::operator() (int32_t lhs, const shared_ptr<ACustomer> rhs) const
{
    return lhs > rhs->m_id;
}

bool ACustomer::CustomerCompareId::operator()
                            (const shared_ptr<ACustomer> lhs, const shared_ptr<ACustomer> rhs) const
{
    return lhs->m_id > rhs->m_id;
}

// CustomerCompareName implementation
bool ACustomer::CustomerCompareName::operator() (const shared_ptr<ACustomer> lhs, string rhs) const
{
    return lhs->m_name > rhs;
}

bool ACustomer::CustomerCompareName::operator() (string lhs, const shared_ptr<ACustomer> rhs) const
{
    return lhs > rhs->m_name;
}

bool ACustomer::CustomerCompareName::operator()
                            (const shared_ptr<ACustomer> lhs, const shared_ptr<ACustomer> rhs) const
{
    return lhs->m_name > rhs->m_name;
}