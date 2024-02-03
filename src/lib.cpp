#include <iostream>
#include <cstdint>
#include <array>
using namespace std;

int square(int value) {
    return value*value;
}

// function arg doesn't have to have a name
double sqr(double){
    return 2;
};

void f(const int& x) {
  int& y = const_cast<int&>(x);
  y+=1;
  std::cout << "Number after adding 1 with const_cast: " << y << std::endl;
}

void addOne(int &num) {
    num += 1;
}

void addOne(int* numPtr) {
    // Check if the pointer is valid (not nullptr)
    if (numPtr != nullptr) {
        // Increment the value at the memory location pointed to by numPtr
        (*numPtr) += 1;
    }
}

#include <vector>

void modifyVector(const std::vector<int>& vec) {
    // Using const_cast to remove the const qualifier temporarily
    std::vector<int> &mutableVec = const_cast<std::vector<int> &>(vec);

    // Now you can modify mutableVec safely
    for (int &element : mutableVec) {
        element += 1;
    }

    std::cout << "Vector after adding 1 to each element:";
    for (const int &element : mutableVec) {
        std::cout << " " << element;
    }
    std::cout << std::endl;
}


int count_x(const char* p, char x)
// count the number of occurrences of x in p[]
// p is assumed to point to a zero-terminated array of char (or to nothing)
{
    if (p==nullptr)
        return 0;
    int count = 0;
    while (*p) { //similar to for (; ∗p!=0; ++p)
        if (*p==x)
            ++count;
        ++p; // pointer arithmetics
        }
    return count;
}



void playground() {
    // Pointer Просто хранит какой-то адрес
    char c = 'A';
    void* addr =  &c;
    cout <<"ref to c: "<< &c << endl;
    cout <<"pointer to c: "<< addr << endl;
    // Если указатель никуда не ссылается,
    // надо использовать nullptr
    void* invalid = nullptr;
    // Pointer vs ref
    //https://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable
    // In declarations, [ ] means ‘‘array of’’ and ∗ means ‘‘pointer to.’’
    //In an expression ∗ means ‘‘contents of’’ and prefix unary & means ‘‘address of.’’
    //In a declaration, the unary suffix & means ‘‘reference to.’’

    // Размер указателя, например, 4 - это количество
    // байт необходимых для размещения адреса
    size_t size = sizeof(addr); // size == 4/8 (64bit is 8)
    cout << "Size of pointer: " << size<< endl;
    cout << "Size of a char: " << sizeof(c) << endl; //size of a char is 1
    // sizeof(int) = 4

    
    // Теперь мы говорим компилятору как
    // интерпретировать то, на что указывет
    // указатель
    char* charPtr = (char*) &c;
    cout << "charPtr: "<< charPtr << endl;

    // Разыменование - получение значения, находящегося
    // по указанному адресу
    char cc = *charPtr; // c == 1
    cout << "c: " << cc << endl;

    // & - взятие адреса, теперь в charPtrPtr находится
    // адрес charPtr
    char** charPtrPtr = &charPtr;

    int* intPtr = (int*) addr; // addr as int pointer
    int i = *intPtr; //deref addr (as int pointer)
    cout << "addr as int, i: " << i<< endl;

    // Pointer arithmetics
    int* i1 = intPtr;
    int* i2 = i1 + 2; //adding two times the size of int
    ptrdiff_t d1 = i2 - i1; // d1 == 2
    cout << "d1: " << d1 << endl;

    short* c1 = (short*) i1;
    char c11 = *c1;
    char c111 = *i1;
    int i111 = *i1;
    cout << "c111 : " << c111 << endl;
    cout << "i111 : " << i111 << endl; // same as i

    short* c2 = (short*) i2;
    char x = *c2;
    cout << "What is this? " << x << endl;

    ptrdiff_t d2 = c2 - c1; // d2 == 8 - we added 2*int = 8bytes = 8 chars
                            // if c1/c2 is short* then 8bytes = 8/2=4 shorts 
    cout << "d2: " << d2 << endl;

    //free(&x);
    // size of an array must be constexpr
    // this is on heap: https://stackoverflow.com/questions/1598397/creating-array-of-objects-on-the-stack-and-heap
    int dt[10] = {5,2,3,4}; // dt is a pointer to the first element of the array
    cout << "dt: " << *dt << endl; // Note
    int z = dt[9];
    cout << "y: " << z << endl;
    
    // this is on stack (because of int*)
    int* data = new int[10]; // new keyword allocates on heap - and you MUST call delete
    int ii = data[15]; // Undefined behaviour?
    cout << "ii: " << ii << endl;


    int ar[20] = { 1, 2, 3 };
    int* j = ar;
    using array = int*; //array is just whenever we type int*
    array k = (array) j;
    cout << "k: " << *k << endl;

    i1 = ar;
    cout << "at i1 now: " << *i1 << endl;
    i1 = i1 + 2 ;//adding two times size of int
    cout << "at i1 now: " << *i1 << endl;
    // Capacity(size) of the array
    cout << "size of ar: " << sizeof(ar) / sizeof(ar[0]) << endl;

    int q = 100;
    int32_t* m = new int[q]; // heap - m is a pointer
    cout << "m: " << *m << endl;
    cout << "at: " << *ar << endl;

    std::array<int, 3> abc = {1,2,3};//#include array
    //abc.front();
    cout << "abc back: " << abc.back() << endl;
}

void mut_ref() {
  // https://stackoverflow.com/questions/37247695/const-cast-doesnt-change-the-value#:~:text=As%20for%20why%20it%20doesn,instead%20of%20reading%20the%20variable.
    int zz = 100;
    f(zz); // Note: if zz was const, since int, and const in f, i get's copied into x in f
    cout << "zz post f: " << zz << endl;
    addOne(zz);
    cout << "zz post addOne ref: " << zz << endl;
    addOne(&zz);
    cout << "zz post addOne ptr: " << zz << endl;  

    std::vector<int> originalVector = {1, 2, 3, 4, 5};

    std::cout << "Original vector:";
    for (const int &element : originalVector) {
        std::cout << " " << element;
    }
    std::cout << std::endl;

    modifyVector(originalVector);

    // originalVector is modified
    std::cout << "Original vector after modifyVector:";
    for (const int &element : originalVector) {
        std::cout << " " << element;
    }
    std::cout << std::endl;  
}