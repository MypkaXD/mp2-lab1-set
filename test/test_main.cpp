#include <gtest.h>
#include "tbitfield.h"

int main(int argc, char** argv) {

    /*TBitField test(100);

    int sum = 0;
    for (int i = 0; i < test.GetLength(); i++)
    {
        sum += test.GetBit(i);
    }

    std::cout << sum;
    */


    //тест на получение мощности множества и длины массива pMem
    /*
        std::cout << "byte = " << sizeof(TELEM) << "\nbit = " << sizeof(TELEM) * 8 << std::endl; // кол-во байт и бит в одном TELEM
        std::cout << "===================================================" << std::endl;
        int arraytest2[6] = {172,128,192,193,129,65 };
        int lenght = sizeof(arraytest2) / sizeof(int);
        std::cout << "Lenght is " << lenght << std::endl;
        for (int count = 0; count < lenght; count++) {
            TBitField test2_1(arraytest2[count]);
            std::cout << test2_1.GetLength() << std::endl;
            std::cout << test2_1.GetMemLen() << std::endl;
            test2_1.printpMem();
            std::cout << "===================================================" << std::endl;
    }
    */
    //тест для получения GetMemIndex;
    /*
        TBitField test_3(172);
        std::cout << test_3.GetMemLen()  * sizeof(TELEM) * 8 - 1 << std::endl;
        std::cout << sizeof(TELEM) * 8 * test_3.GetMemLen() - 1 << std::endl;
        std::cout << test_3.GetLength() - 1 << std::endl;
    */
    //Тест маски
    /*
        TBitField test4(168);
        std::cout << test4.GetMemMasktest(2) << std::endl;
    */
    //тест с set get clr и << >>;
    /*
        const int size1 = 4, size2 = 5;
        TBitField bf1(size1), bf2(size2), expBf(size2);
        // bf1 = 0011
        bf1.SetBit(2);
        bf1.SetBit(3);
        // bf2 = 01010
        bf2.SetBit(1);
        bf2.SetBit(3);

        // expBf = 01110
        expBf.SetBit(1);
        expBf.SetBit(2);
        expBf.SetBit(3);
        expBf.ClrBit(3);
        std::cout << bf1 << "\n=================" << bf2 << "\n================" << expBf << std::endl;
        if (expBf.GetBit(3))
            std::cout << "true";
        else if (!(expBf.GetBit(3)))
            std::cout << "false";
    */

    /*const int size1 = 4, size2 = 5;
    TBitField bf1(size1), bf2(size2), expBf(size2);
    // bf1 = 0011
    bf1.printpMem();
    bf1.SetBit(2);
    bf1.printpMem();
    bf1.SetBit(3);
    bf1.printpMem();
    // bf2 = 01010
    bf2.SetBit(1);
    bf2.SetBit(3);

    // expBf = 01110
    expBf.SetBit(1);
    expBf.SetBit(2);
    expBf.SetBit(3);
    expBf.ClrBit(3);
    std::cout << bf1 << "\n=================" << bf2 << "\n================" << expBf << std::endl;
    if (expBf.GetBit(3))
        std::cout << "true" << std::endl;
    else if (!(expBf.GetBit(3)))
        std::cout << "false" << std::endl;
    bf1.printpMem();
    std::cout << bf1.GetMemLen() << std::endl;
    //expBf = bf1 | bf2;
    std::cout << expBf << std::endl;
    */
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
