#include <stdio.h>

void demo1(){
    struct BitField {
        unsigned char a:2;
        unsigned char b:4;
        unsigned char c:3;
    };
    /*
     1Byte 1字节 = 8bit 即 8组二进制
     unsigned char = 1 Byte = 8bit
     2bit + 4 bit + 3bit > 8bit(1Byte)
     大于unsigned char的一个字节，所以需要横跨的下一个字节 因此是2Byte
     */
    printf("unsigned char size = %ld \n",sizeof(unsigned char));
    printf("BitField size %ld \n", sizeof(struct BitField));
}

void demo2(){
    struct BitField {
        unsigned char a:2;
        unsigned char b:4;
        unsigned char c:2;
    };
    /*
     1Byte 1字节 = 8bit 即 8组二进制
     unsigned char = 1 Byte = 8bit
     2bit + 4 bit + 2bit = 8bit(1Byte)
     小于等于unsigned char的一个字节， 因此是1Byte
     */
    printf("unsigned char size = %ld \n",sizeof(unsigned char));
    printf("BitField size %ld \n", sizeof(struct BitField));
}

void demo3(){
    struct BitField {
        unsigned char a:2; //2 bit 1Byte
        unsigned char :0;  //宽度为 0 的一个未命名位域强制下一位域对齐到其下一type位域的边界
        unsigned char c:2; // 从下一个unsigned char的边界开始即1Byte
        unsigned char :0;  //宽度为 0 的一个未命名位域强制下一位域对齐到其下一type位域的边界
        unsigned char :1;  // 从下一个unsigned char的边界开始即1Byte
    };
    /*
     宽度为 0 的一个未命名位域强制下一位域对齐到其下一type位域的边界
     */
    printf("unsigned char size = %ld \n",sizeof(unsigned char));
    printf("BitField size %ld \n", sizeof(struct BitField));
}


//void demo4(){
//    struct BitField {
//        int a:33; //int最大4Byte == 32bit 不能超过最大bit，会报错
//    };
//    //width of bit-field 'a' (33 bits) exceeds width of
//
//    printf("int size = %ld \n",sizeof(int));
//    printf("BitField size %ld \n", sizeof(struct BitField));
//}


// 整个位域结构体的总大小为最宽基本类型成员大小的整数倍，这一点与常规结构体类型是一致的，从这里也可看出，位域本质上就是结构体；
void demo5(){
    struct BitField
    {
        int   a: 8;    // 第一个4Byte中的开始8bit
        int   b: 2;    // 由于相邻两个位域的类型相同，总大小10 < 32(int类型大小）
        // 所以这里存储是挨着第一个4Byte，紧接着的2bit
        
        char  c: 6;    // 由于相邻的两个位域类型不同
        // 所以这里是第二个4Byte
        // 总共8Byte
    };
    printf("int size = %ld \n",sizeof(int));
    printf("char size = %ld \n",sizeof(char));
    printf("BitField size %ld \n", sizeof(struct BitField));
}

void demo6(){
    // 假如 BitField_4::a = 0x1,(0001 B); BitField_4::b = 0x08676665
    // 则有：第一个4字节：0000 0001 0000 0000 0000 0000 0000 0000（B）
    // 第二个4字节：0x65 66 67 08（小端模式，高高低低，高字节存放在高地址）
    struct BitField
    {
        int a: 4;   // 第一个4字节
        
        int b: 29;  // 虽然相邻位域类型相同
        // 但是，4 + 29 > 32
        // 因此b位域从第二个4字节开始存储
        // 总共8字节
    };
    
}


void demo7(){
    // 如果相邻位域字段的类型不同，则各编译器的具体实现有差异，VC采取不压缩方式
    // 假如 BitField_5::a = 0x4, (0100 B); BitField_5::b = 0x5, (0101 B), 则有：
    // 第一个4字节：0000 0100 0000 0000 0000 0000 0000 0000（B）
    // 第二个4字节：0000 0101 0000 0000 0000 0000 0000 0000（B）
    struct BitField
    {
        int  a : 4;  // 占据int的4字节中的4个bit
        char b : 4;  // 相邻字段类型不同，就算类型是char，也另起一个4字节
        // 总共8Byte，可见不但没有压缩，还浪费空间
    };
    
    printf("int size = %ld \n",sizeof(int));
    printf("char size = %ld \n",sizeof(char));
    printf("BitField size %ld \n", sizeof(struct BitField));
}

void demo8(){
    // 如果位域字段之间穿插着非位域字段，则不进行压缩
    struct BitField
    {
        int  a : 4; // 4Byte
        int b;      // 4Byte
        int c : 4;  // 4Byte
    };
    
    printf("int size = %ld \n",sizeof(int));
    printf("char size = %ld \n",sizeof(char));
    printf("BitField size %ld \n", sizeof(struct BitField));
}

void demo9(){
    // 如果位域字段之间穿插着非位域字段，则不进行压缩
    struct BitField
    {
        int  a; // 4Byte
        int b : 4;
        int c : 4;
        // b c 之间没有穿插非位移字段，会进行压缩成4Byte
    };
    
    printf("int size = %ld \n",sizeof(int));
    printf("BitField size %ld \n", sizeof(struct BitField));
}


void demo10(){
    struct BitField
    {
        char a : 2;
        char b : 3;
        char c : 3;
    };
    
    struct BitField BF;
    
    // 位域赋值
    BF.a = 0x3;   // 11
    BF.b = 0x5;   // 101
    BF.c = 0x2;   // 010
    
    printf("%d,%d,%d\n", BF.a, BF.b, BF.c);
    //implicit truncation from 'int' to bit-field changes value from 3 to -1
    // OUTPUT:  -1（0xff, 1111 1111）, -3（0xfd, 1111 1101）, 2（0x02, 0000 0110）
    // 可见，当为域的最高位是1的时候，会进行符号扩展，而且这也取决于编译器的实现
    // 因此，为避免此类问题，最好使用无符号类型定义位域
    
    // 如果把BitField_8中的char换成unsigned char就没有问题了，输出是3, 5, 2，
    //从其内存布局可以看出，使用位域的最佳实践是：
    // 第一，位域的类型要使用无符号类型，并且在整个结构体内部要保持一致；
    // 第二，位域的总长度尽量与类型的长度保持一致；
    // 第三，不要在两个位域中间穿插非位域字段；
}



int main (){
    
    
    demo10();
    return 0;
}
