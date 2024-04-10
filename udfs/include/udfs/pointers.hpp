#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

void AdvancedSharedPtr();                   // Forward reference
void Basics();                   // Forward reference
void FileExample();                         // Forward reference
void WeakPtrDemo();                         // Forward reference
void MutCond();

class Base {
public:
    virtual void speak() { // Have to make virtual to be able to override
        std::cout << "I am a Base." << std::endl;
    }

    virtual ~Base() {
        std::cout << "Base destroyed." << std::endl;
    }
};

class Derived : public Base {
public:
    void speak() override { // must explicitly override 
        std::cout << "I am a Derived." << std::endl;
    }

    ~Derived() override { // Derived destructor will still call Parent's destructor
        std::cout << "Derived destroyed." << std::endl;
    }
};

void custom_deleter(Base *ptr) {
    std::cout << "Custom deleter called." << std::endl;
    delete ptr;
}

int shared_pointers() 
{
    
    // Basics();
    // AdvancedSharedPtr();
    // FileExample();
    // WeakPtrDemo();
    // MutCond();

    return 0;
}

void Basics()
{
    // Creating a shared_ptr and initializing it with a new object
    std::shared_ptr<Base> sp1 = std::make_shared<Base>();
    sp1->speak(); // since ptr we use -> to access members

    // Creating a shared_ptr with a custom deleter
    std::shared_ptr<Base> sp2(new Derived, custom_deleter);
    sp2->speak();

    // Creating a shared_ptr from another shared_ptr (copying)
    // Increasing Reference count
    std::shared_ptr<Base> sp3 = sp1;
    sp3->speak();

    // Resetting a shared_ptr
    sp3.reset(new Derived);
    sp3->speak();

    // Checking the use_count of a shared_ptr
    std::cout << "sp1 use_count: " << sp1.use_count() << std::endl; // Now 1, still Base, since sp3 has been reset

    // Using shared_ptr in a container
    std::vector<std::shared_ptr<Base>> container;
    container.push_back(sp1);
    container.push_back(sp2);
    container.push_back(sp3);

    for (const auto &item : container) {
        item->speak();
    }
}

void AdvancedSharedPtr() 
{
    // 1. Weak pointers
    std::shared_ptr<Base> sp1 = std::make_shared<Base>();
    std::weak_ptr<Base> wp1 = sp1; // weak_ptr does not contribute to ref count

    if (std::shared_ptr<Base> locked = wp1.lock()) {
        locked->speak(); // I am Base
    }

    sp1.reset(); // Base destroyed

    if (wp1.expired()) {
        std::cout << "The weak_ptr is expired." << std::endl;
    }

    // 2. Aliasing constructor
    std::shared_ptr<Base> sp2 = std::make_shared<Derived>();
    std::shared_ptr<Base> sp2_alias(sp2, sp2.get());
    sp2_alias->speak();
    std::cout << "sp2 use_count: " << sp2.use_count() << std::endl;

    // 3. shared_ptr for arrays
    // pointer to array of objects
    std::shared_ptr<Base[]> sp3(new Base[3]);
    sp3[0].speak(); // indexing sp3[0] gets actual object
    sp3[1].speak();
    sp3[2].speak();

    // // 4. Atomic operations
    std::shared_ptr<Base> sp4 = std::make_shared<Base>();
    std::shared_ptr<Base> sp5;

    std::thread t1([&]() {
        std::atomic_store(&sp5, std::atomic_load(&sp4));
    });

    std::thread t2([&]() {
        std::atomic_store(&sp4, std::shared_ptr<Base>(nullptr));
    });

    t1.join();
    t2.join();

    if (sp5) {
        sp5->speak();
    }
}

//-------------------------------------------------------------------------
// Custom deleter example for FILE objects
//-------------------------------------------------------------------------

void file_deleter(FILE *file) {
    if (file) {
        std::cout << "Closing the file." << std::endl;
        fclose(file);
    }
}

void readFile(const char *filename) {
    // Create a shared_ptr with a custom deleter
    std::shared_ptr<FILE> file(fopen(filename, "r"), file_deleter);

    if (!file) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    // Read the file
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file.get()) != nullptr) {
        std::cout << buffer;
    }

    // The file will be closed automatically by the custom deleter
}

void FileExample()
{
    readFile("main.cpp");
}

//-------------------------------------------------------------------------
// Weak pointer demo
//-------------------------------------------------------------------------

// Weak Pointers are used to check validity of data in shared_ptr
// 
void WeakPtrDemo() 
{
    // Create a shared_ptr and initialize it with a new object
    std::shared_ptr<Base> sp1 = std::make_shared<Derived>();

    // Create a weak_ptr from the shared_ptr
    std::weak_ptr<Base> wp1(sp1);

    // Check if the weak_ptr is valid and lock it to obtain a shared_ptr
    if (auto locked = wp1.lock()) {
        std::cout << "Weak pointer is valid. Locked and obtained shared_ptr." << std::endl;
        locked->speak();
    } else {
        std::cout << "Weak pointer is not valid." << std::endl;
    }

    // Reset the shared_ptr, causing the object to be destroyed
    sp1.reset();

    // Check if the weak_ptr is still valid
    if (wp1.expired()) {
        std::cout << "Weak pointer is now expired." << std::endl;
    } else {
        std::cout << "Weak pointer is still valid." << std::endl;
    }
}

void MutCond() {
    std::mutex mu; //Global variable or place within class
    std::condition_variable condition; //A signal that can be used to communicate between functions

    auto _MyFunction = [&]() { 
        std::unique_lock<std::mutex> lock(mu);
        //Do Stuff
        lock.unlock(); //Unlock the mutex
        condition.notify_one(); //Notify MyOtherFunction that this is done
        };

    auto _MyOtherFunction = [&]() {
        std::unique_lock<std::mutex> lock(mu);
        condition.wait(lock); //Wait for MyFunction to finish, a lambda can be passed also to protects against spurious wake up e.g (lock,[](){return *some condition*})
        lock.unlock(); // might not be needed since unique lock 
    };
}