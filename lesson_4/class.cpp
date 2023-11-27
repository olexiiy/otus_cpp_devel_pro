#include <iostream>
#include <vector>

struct foo
{
    foo() = delete;
    foo(int value) { }

    virtual ~foo() = default;

    foo & operator=(const foo& rhs) = default;

    virtual void m() = 0;
    virtual void n(int a, double b) {};
};

struct bar : foo
{
    bar() : foo(42) {

    }
    ~bar() = default;

    void m() override {};
    void n(int a, double b) override {};
//    void o() override {}; // only virtual member functions can be marked 'override'
};

namespace one_more {

    struct DoNotCopyMe {
        public:
            DoNotCopyMe() = default;
        private:
            DoNotCopyMe(const DoNotCopyMe&) = delete;

            DoNotCopyMe& operator=(const DoNotCopyMe&) = delete;
    };

    void example() {

        DoNotCopyMe value;
        // DoNotCopyMe value2{ value };

        // Compile time error in case of delete:
        // prog.cc:43:21: error: call to deleted constructor of 'one_more::DoNotCopyMe'
        //         DoNotCopyMe value2{ value };
        //                     ^     ~~~~~~~~~
        // prog.cc:35:13: note: 'DoNotCopyMe' has been explicitly marked deleted here
        //             DoNotCopyMe(const DoNotCopyMe&) = delete;


        // Compile time error in case of private:
        // prog.cc:43:21: error: calling a private constructor of class 'one_more::DoNotCopyMe'
        //         DoNotCopyMe value2{ value };
        //                     ^
        // prog.cc:35:13: note: declared private here
        //             DoNotCopyMe(const DoNotCopyMe&);
    }
}

int main(int, char *[]) {
    bar b;

    return 0;
}