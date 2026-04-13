#include <iostream>
#include <cmath>


const int N = 6; //num bits in the vector
const int NV = (int) std::pow(2, N); // num different N-bit binary numbers'
const int ny = 3; //num bits in the calculated Hamming weight

int HW_b(int b) {
    int HW = 0;
    for (int i = 0; i < N; i++) {
        HW += (1 & b); //increment if ones digit is 1
        b = b >> 1; //right shift 1
    }
    return HW;
}

void b_v(int b, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        int k = b >> i;
        if (k & 1)
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << " ";
}


int main() {
    int b;
    for (b = 0; b < NV; b++) {
        b_v(b, N);
        b_v(HW_b(b), ny);
        std::cout << " HW(" << b << ") = " << HW_b(b) << std::endl;
    }


}