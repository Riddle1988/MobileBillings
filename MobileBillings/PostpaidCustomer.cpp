#include "stdafx.h"
#include "PostpaidCustomer.h"

PostpaidCustomer::PostpaidCustomer( int32_t id,
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

void PostpaidCustomer::credit(int32_t changeBalance)
{
    m_balance -= changeBalance;
}