
#include <stdio.h>

// 正常版
void demo1(){
// 声明结构体
struct Student {
        char name[20];
        int num;
        float score;
};

// 定义结构体变量
struct Student stu1;
	
}

// 简化版
void demo2 (){
struct Student {
	char name[20];
	int num;
	float score;
}stu1;

}

// 匿名版
void demo3 (){
struct {
	char name[20];
	int num;
	float score;
}stu1;

}

// 结构体嵌套结构体
void demo4(){
struct Brithday{
	int year;
	int month;
	int day;
};

struct Student{
	char name[20];
	int num;
	float scroe;
	struct Brithday brithday;
} stu1;
}


// 结构体变量初始化


void demo5(){
struct Employee{
	char name[3];
	int age;
};
struct Employee employee1, employee2;
employee1.name[0] = 'a';
employee1.name[1] = 'b';
employee1.name[2] = 'c';
employee1.age = 18;

printf("employee1 age:%d, name: %s",employee1.age,employee1.name);
}

void demo6(){
struct Employee{
        char name[20];
        int age;
};
struct Employee employee1 = {"wendell koan",18};

printf("employee1 age:%d, name: %s",employee1.age,employee1.name);
}

void demo7(){
struct Employee{
        char name[20];
        int age;
};
struct Employee employee1 = {.name = "jay", .age = 18};

printf("employee1 age:%d, name: %s",employee1.age,employee1.name);
}

void demo8(){
struct Employee{
        char name[20];
        int age;
};
struct Employee employee1;
struct Employee employee0 = {.name = "jay", .age = 18};


printf("赋值之前employee0 addr:%p\n", &employee0);
printf("赋值之前employee1 addr:%p\n", &employee1);


employee1 = employee0;

printf("赋值之后employee0 addr:%p\n", &employee0);
printf("赋值之后employee1 addr:%p\n", &employee1);


printf("employee1 age:%d, name: %s",employee1.age,employee1.name);
}


int main(){
	demo8();
	return 0;
}

