#include "stdafx.h"
#include "PrepaidCustomer.h"

PrepaidCustomer::PrepaidCustomer( int32_t id,
                                  string name,
                                  string phoneNumber,
                                  int32_t balance,
                                  int32_t totalCallDuration )
    : ACustomer( id,
                 name,
                 phoneNumber,
                 balance,
                 totalCallDuration )
{
    /*empty*/
}

void PrepaidCustomer::credit(int32_t changeBalance)
{
    m_balance += changeBalance;
}