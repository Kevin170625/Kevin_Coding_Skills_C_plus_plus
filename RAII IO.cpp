#include <iostream>
#include <memory>
using namespace std;

class Resource
{
public:
    Resource()
    {
        cout << "Resource acquired" << endl;
    }

    ~Resource()
    {
        cout << "Resource released" << endl;
    }

    void use()
    {
        cout << "Resource is being used" << endl;
    }
};

class MySmartPointer
{
private:
    Resource* ptr;

public:
    MySmartPointer(Resource* p)
    {
        ptr = p;
    }

    ~MySmartPointer()
    {
        delete ptr;
        cout << "Manual smart pointer destroyed" << endl;
    }

    Resource* operator->()
    {
        return ptr;
    }

    MySmartPointer(const MySmartPointer&) = delete;

    MySmartPointer& operator=(const MySmartPointer&) = delete;
};

int main()
{
    int n;

    cout << "Enter number of resources: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid input!" << endl;
        return 0;
    }

    cout << "\n----- Manual RAII Smart Pointer -----" << endl;

    for (int i = 0; i < n; i++)
    {
        MySmartPointer smartPtr(new Resource());
        smartPtr->use();
    }

    cout << "\n----- unique_ptr -----" << endl;

    for (int i = 0; i < n; i++)
    {
        unique_ptr<Resource> uniquePtr = make_unique<Resource>();
        uniquePtr->use();
    }

    cout << "\n----- shared_ptr -----" << endl;

    for (int i = 0; i < n; i++)
    {
        shared_ptr<Resource> sharedPtr1 = make_shared<Resource>();
        shared_ptr<Resource> sharedPtr2 = sharedPtr1;

        sharedPtr1->use();

        cout << "Shared Pointer Count: "
             << sharedPtr1.use_count() << endl;
    }

    cout << "\nProgram completed successfully." << endl;

    return 0;
}