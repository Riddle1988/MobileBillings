#ifndef ACustomer_h__
#define ACustomer_h__

#include "stdafx.h"

using namespace std;

// Abstract class for all customers
class ACustomer
{
private:
    // Three const on which search will be preformed
    const int32_t m_id;
    const string m_name;
    const string m_phoneNumber;

protected:
    // Variables that are subjected to change
    int32_t m_balance;
    int32_t m_totalCallDuration;

    /* Default constructor, copy constructor and operator= should be protected so that only 
       access from the child class is possible */
    ACustomer() = default;
    ACustomer(const ACustomer&) = default;
    ACustomer& operator= (const ACustomer&) = default;

    // Base constructor that will set initialization values of the members
    ACustomer( const int32_t id,
               const string name,
               const string phoneNumber,
               int32_t balance,
               int32_t totalCallDuration );

public:

    // Postpaid and prepaid customers should have different implementation of this class
    virtual void credit(int32_t changeBalance) = 0;

    // Get current balance status (should be the same for all child classes)
    int32_t enquireBalance() const;

    // Get current call duration
    int32_t enquireCallDuration() const;

    void addCallDuration(int32_t time);

    // Make destructor virtual so that it can be called from outside from proper destroying
    virtual ~ACustomer() = default;

    /*
    Group of different comparer's that will be used to sort set's for faster searching
    */
    struct CustomerCompareNumber
    {
        using is_transparent = std::true_type;
        bool operator()(const shared_ptr<ACustomer> lhs, string rhs) const;
        bool operator()(string lhs, const shared_ptr<ACustomer> rhs) const;
        bool operator()(const shared_ptr<ACustomer> lhs, const shared_ptr<ACustomer> rhs) const;
    };
    struct CustomerCompareId
    {
        using is_transparent = std::true_type;
        bool operator()(const shared_ptr<ACustomer> lhs, int32_t rhs) const;
        bool operator()(int32_t lhs, const shared_ptr<ACustomer> rhs) const;
        bool operator()(const shared_ptr<ACustomer> lhs, const shared_ptr<ACustomer> rhs) const;
    };
    struct CustomerCompareName
    {
        using is_transparent = std::true_type;
        bool operator()(const shared_ptr<ACustomer> lhs, string rhs) const;
        bool operator()(string lhs, const shared_ptr<ACustomer> rhs) const;
        bool operator()(const shared_ptr<ACustomer> lhs, const shared_ptr<ACustomer> rhs) const;
    };

};
#endif // ACustomer_h__
