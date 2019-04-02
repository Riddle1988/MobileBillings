// Main.cpp : Defines the entry point for the console application.
// Used to test the application

#include "stdafx.h"
#include "MobileBilling.h"
#include "CustomerFactory.h"

int main()
{
    MobileBilling* database = new MobileBilling();



    // Add a new customer test
    database->addCustomer
                    ( CustomerFactory::TypeOfCustomers::POSTPAID
                    , 5000
                    , "John D."
                    , "0176555222"
                    , 0
                    , 0);
    assert(database->getNumberOfCustomer() == 1);



    // Try to add the same customer test
    try
    {
        database->addCustomer
                    ( CustomerFactory::TypeOfCustomers::POSTPAID
                    , 5000
                    , "John D."
                    , "0176555222"
                    , 0
                    , 0);
    }
    catch(exception ex)
    {
        string text = ex.what();
        assert(text == "Duplicated number error");
    }



    // Try to add customer with the same id
    try
    {
        database->addCustomer
                    (CustomerFactory::TypeOfCustomers::POSTPAID
                    , 5000
                    , "John D."
                    , "0175555"
                    , 0
                    , 0);
    }
    catch (exception ex)
    {
        string text = ex.what();
        assert(text == "Duplicated id error");
    }



    // try to add customer with different type but same number
    try
    {
        database->addCustomer
        (CustomerFactory::TypeOfCustomers::PREPAID
            , 5000
            , "John D."
            , "0176555222"
            , 0
            , 0);
    }
    catch (exception ex)
    {
        string text = ex.what();
        assert(text == "Duplicated number error");
    }


    // try to add customer with the same id but different type
    try
    {
        database->addCustomer
        (CustomerFactory::TypeOfCustomers::PREPAID
            , 5000
            , "John D."
            , "0175555"
            , 0
            , 0);
        assert(database->getNumberOfCustomer() == 2);
    }
    catch (exception ex)
    {
        assert(database->getNumberOfCustomer() == 2);
    }

    // Add another customer
    try
    {
        database->addCustomer
        (CustomerFactory::TypeOfCustomers::PREPAID
            , 5005
            , "Mike"
            , "5"
            , 10
            , 15);
        assert(database->getNumberOfCustomer() == 3);
    }
    catch (exception ex)
    {
        assert(database->getNumberOfCustomer() == 3);
    }

    // Add another customer
    try
    {
        database->addCustomer
        (CustomerFactory::TypeOfCustomers::PREPAID
            , 5006
            , "Luke"
            , "555"
            , 42
            , 24);
        assert(database->getNumberOfCustomer() == 4);
    }
    catch (exception ex)
    {
        assert(database->getNumberOfCustomer() == 4);
    }

    // Add another customer
    try
    {
        database->addCustomer
        (CustomerFactory::TypeOfCustomers::PREPAID
            , 1025
            , "Silvio"
            , "84"
            , 28
            , 35);
        assert(database->getNumberOfCustomer() == 5);
    }
    catch (exception ex)
    {
        assert(database->getNumberOfCustomer() == 5);
    }

    // Check calculation
    assert(database->getAveragePrePaidBalance() > 0);
    assert(database->getAveragePostPaidCallDuration() == 0);

    // try to add the same customer test
    try
    {
        database->addCustomer
        (CustomerFactory::TypeOfCustomers::POSTPAID
            , 66666
            , "Karlo"
            , "88888"
            , 20
            , 20);
    }
    catch (exception ex)
    {
        /*empty*/
    }
    // check average call duration calculation
    assert(database->getAveragePostPaidCallDuration() == 10);

    // check can we find customer with search by number
    auto customer = database->searchByNumber("0176555222");
    assert(customer != nullptr);


    customer->addCallDuration(10);

    int32_t num = database->getAveragePostPaidCallDuration();

    // can we change customer that we found
    assert(database->getAveragePostPaidCallDuration() == 15);

    // check what happens when we search customer that does not exist
    customer = database->searchByNumber("00001111");
    assert(customer == nullptr);

    // check can we retrieve second time
    customer = database->searchByNumber("0176555222");
    assert(customer != nullptr);

    // check can we delete
    database->deleteCustomer(customer);
    assert(database->getNumberOfCustomer() == 5);

    // Check that we cannot access it again
    customer = nullptr;
    customer = database->searchByNumber("0176555222");
    assert(customer == nullptr);

    // check can we add the same customer again
    try
    {
        database->addCustomer
        (CustomerFactory::TypeOfCustomers::POSTPAID
            , 5000
            , "John D."
            , "0176555222"
            , 0
            , 0);
        assert(database->getNumberOfCustomer() == 6);
    }
    catch (exception ex)
    {
        /*empty*/
    }

    // Check if method returns both values
    auto somePair = database->searchById(5000);
    assert(somePair.first != nullptr);
    assert(somePair.second != nullptr);

    // Check if search returns if only one value is present
    somePair = database->searchById(66666);
    assert(somePair.first != nullptr);
    assert(somePair.second == nullptr);

    // Check search by name
    auto searchByName = database->searchByName("John D.");
    assert(searchByName.size() != 0);

    // Search by false name
    searchByName = database->searchByName("IdoNotExist");
    assert(searchByName.size() == 0);

    // Check that we have a list of customers with a value more that 5
    auto morethan5 = database->queryPostpaidCustomers(5);
    assert(morethan5.size() > 0);

    // Check that we do not get any because number is to high
    auto morethan100000 = database->queryPostpaidCustomers(100000);
    assert(morethan100000.size() == 0);

    // Check prepaid customers
    auto morethan2 = database->queryPrepaidCustomers(2);
    assert(morethan2.size() > 0);

    auto morethan8000000 = database->queryPrepaidCustomers(8000000);
    assert(morethan8000000.size() == 0);

    return 0;
}

