#ifndef PrepaidCustomer_h__
#define PrepaidCustomer_h__

#include "stdafx.h"
#include "ACustomer.h"

using namespace std;

// Class for all postpaid customer which is a child class of a base ACustomer class
class PrepaidCustomer final : public ACustomer
{
public:
    // Delete default constructor so that only one with all init values can be called
    PrepaidCustomer() = delete;

    // Constructor for the PrepaidCustomer
    PrepaidCustomer( int32_t m_id,
                     string m_name,
                     string m_phoneNumber,
                     int32_t m_balance,
                     int32_t m_totalCallDuration );

    // Base class method which must be implemented here
    virtual void credit(int32_t changeBalance) override;

    // Destructor
    virtual ~PrepaidCustomer() = default;
};
#endif // PrepaidCustomer_h__