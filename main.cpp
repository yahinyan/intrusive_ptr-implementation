#include "intrusive_ptr.hpp"

int main() {
    intrusive_ptr<int> ptr(new int(10));
}