
#include <stdio.h>
#include <string.h>

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

void demo9(){
    struct Student {
        char name[50];
        int age;
    };
    
    struct Student stu[2] = {{"wendell",18},{"wendy",17}};
    
    printf("stu index 0 = %d",stu[1].age);
}

void demo10(){
    struct Student {
        char name[50];
        int age;
    } stu[2];
    
    strcpy(stu[0].name,"koan");
    stu[0].age = 18;
    
    strcpy(stu[1].name,"lucy");
    stu[1].age = 28;
    
    printf("stu index 0 = %d",stu[1].age);
}

void demo11(){
    struct Student {
        char name[50];
        int age;
    };
    
    struct Student stu1 = {"king",18};
    
    struct Student *pstu;
    
    //数组名表示的是数组的首地址，可以直接赋值给数组指针。但结构变量名只是表示整个结构体变量，不表示结构体变量的首地址，所以不能直接赋值给结构指针变量，而应该使用 & 运算符把结构变量的的地址赋值给结构指针变量。即：
    //assigning to 'struct Student *'from incompatible type 'struct Student'; take the address with&
    //pstu = stu1;
    
    pstu = &stu1;
    
    printf("stu name = %s",(*pstu).name);
    printf("stu age = %d",pstu->age);
}

void demo12(){
    struct Student {
        char name[50];
        int age;
        struct Student *stu;
    } stu;
    
    strcpy(stu.name,"hello");
    stu.age = 18;
    struct Student *p = stu.stu;
    printf("p address = %s",p);
//    strcpy(stu.stu->name,"wangmao");
//    stu.stu->age = 1;
//    printf("name = %s",stu.stu->name);
}


int main(){
	demo12();
	return 0;
}

