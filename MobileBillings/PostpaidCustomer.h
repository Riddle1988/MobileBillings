#ifndef PostpaidCustomer_h__
#define PostpaidCustomer_h__

#include "stdafx.h"
#include "ACustomer.h"

using namespace std;

// Class for all postpaid customer which is a child class of a base ACustomer class
class PostpaidCustomer final : public ACustomer
{
public:
    // Delete default constructor so that only one with all init values can be called
    PostpaidCustomer() = delete;

    // Constructor for the PostpaidCustomer
    PostpaidCustomer( int32_t id,
                      string name,
                      string phoneNumber,
                      int32_t balance,
                      int32_t totalCallDuration );

    // Base class method which must be implemented here
    virtual void credit(int32_t changeBalance) override;

    // Destructor
    virtual ~PostpaidCustomer() = default;
};
#endif // PostpaidCustomer_h__