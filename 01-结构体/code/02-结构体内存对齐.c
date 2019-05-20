//
//  main.m
//  02-结构体的内存
//
//  Created by wenjie on 5/11/19.
//  Copyright © 2019 wenjie. All rights reserved.
//

/*

1）概念：

有效对齐值：是 #pragma pack指定值 和 结构体中最长数据类型长度 中较小的那个。有效对齐值也叫对齐单位。

注意：VS、VC 默认是#pragma pack(8)，而 gcc 默认是#pragma pack(4)，并且gcc只支持1，2，4对齐。

2）规则：

结构体变量的首地址是有效对齐值（对齐单位）的整数倍。

结构体第一个成员的偏移量（offset）为0，以后每个成员相对于结构体首地址的 offset 都是该成员大小与有效对齐值中较小那个的整数倍，如有需要编译器会在成员之间加上填充字节。

结构体的总大小为 有效对齐值 的整数倍，如有需要编译器会在最末一个成员之后加上填充字节。

结构体内类型相同的连续元素将在连续的空间内，和数组一样。
*/

#include <stdio.h>

// 此方法设置模数的值
//#pragma pack(1)

void demo1(){
    
    struct A {
        int a; //4 < 模数8,offset=0 0%1=0, 起始位置为0至3
        char b; //1 < 模数8,offset=4 4%1=0, 起始位置4
        short c; //2 < 模数8, offset=5 5%2=1, 非整数倍，需要补位1，即6%2=0，起始位置6
    };
    struct A str1 = {10,'a','b'};

    
    printf("size of A = %ld \n",sizeof(struct A));
    /*
     模数是8，最长数据类型4，取最小值，所以整体对齐系数是4
     4B+1B+(补位)1B+2B = 8B
     8B是整体对齐系数4的倍数，因此内存大小是8B
     */
}

void demo2(){
	struct A {
  	short a; // 按2字节对齐，存放区间：0-1
  	double b; // 按8字节对齐，存放区间：8-15
  	int c; // 按4字节对齐，存放区间：16-19
  	char d; // 按1字节对齐，存放区间：20
  };

  printf("size of A = %ld \n",sizeof(struct A));
}

void demo3(){

	struct A { 
		                 //长度        对齐      偏移     区间
	    char   a;       //1  < 8     1         0      [0]     
	    double b;       //8  = 8     8         8      [8,  15]
	    int    c;       //4  < 8     4         16     [16, 19]
	    short  d;       //2  < 8     2         20     [20, 21]
	} a1;

	printf("size of A = %ld \n",sizeof(struct A));
	/* 
	模数是8，最大类型double长度是8所以整体对齐数是8
	1B+(补全)7B+8B+4B+2B = 22B
	总长度必须满足是整体对齐数的倍数，所以24B
	*/
}


void demo4(){
    struct A {
        char a[3];
        char b[4];
        int c;
    } a1;
    
    printf("size of A = %ld \n",sizeof(struct A));
    /*
     模数是8，最大类型int4，取最小值所以整体对齐数是4
     3B + 4B + （补位）1B + 4B = 12B;
     总长度必须满足是整体对齐数的倍数，所以12B
     */
}


int main(int argc, const char * argv[]) {
    printf("size of int : %ld \n", sizeof(int));
    printf("size of char : %ld \n", sizeof(char));
    printf("size of short : %ld \n", sizeof(short));
    printf("size of double : %ld \n", sizeof(double));
    printf("size of long double : %ld \n", sizeof(long double));
    demo4();
	return 0;
}





