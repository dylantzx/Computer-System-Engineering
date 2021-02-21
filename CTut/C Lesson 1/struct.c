#include "cclass.h"
int main(int argc, char** argv){
  // defining struct
   struct Vector_Int{
       int x;
       int y;
       int z;
       char name[64];
   };

   // structure variable declaration, empty member values
   struct Vector_Int v1;

   // manual member initialization
   v1.x = 2;
   v1.y = 3;
   v1.z = 10;
   // sprintf sends formatted output to a string pointed to, by str
   sprintf(v1.name, "Vector 1");

   // structure variable auto member initialization
   struct Vector_Int v2 = {3,5,11, "Vector 2"};

   printf("Values of v1 is x:%d y:%d z:%d name: %s\n", v1.x, v1.y, v1.z, v1.name);
   printf("Values of v2 is x:%d y:%d z:%d name: %s\n", v2.x, v2.y, v2.z, v2.name);

    // Struct within struct
    struct address
    {
        char area_name[32];
        int house_no;
        char district[32];
    };

    struct Info
    {
        char name[32];
        int age;
        struct address address; //now this is a member
    };

    struct Info my_Info = {"Alice", 25, "Somapah Road", 8, "Upper Changi"};

    printf("Name: %s, age %d, area name %s, house number %d, district %s\n", my_Info.name, my_Info.age, my_Info.address.area_name, my_Info.address.house_no, my_Info.address.district);

    struct address my_Addrs = {"Another Road", 15, "Lower Changi"};
    printf("Another address %s %d %s \n", my_Addrs.area_name, my_Addrs.house_no, my_Addrs.district);

    // Byte size of structs are rougly the sum of size of its members
    struct Vector_Int vector_sample;

    printf("Size of Vector_Int struct is %d bytes\n", sizeof(struct Vector_Int));
    printf("Size of its members are x %d bytes, y %d bytes, z %d bytes, and name %d bytes\n", sizeof(vector_sample.x), sizeof(vector_sample.y), sizeof(vector_sample.z), sizeof(vector_sample.name));

    // Array of structs
    // Use typedef for neater code
    typedef struct Info InfoData;
    InfoData many_info[3] = {{"Alice", 25, "Somapah Road", 8, "Upper Changi"},
                               {"Bob", 22, "Somapah Road", 19, "Upper Changi"},
                               {"Michael", 30, "Another Road", 25, "East Changi"}};

   for (int i = 0; i < 3; i++)
   {
       printf("Name: %s, age %d, area name %s, house number %d, district %s\n", many_info[i].name, many_info[i].age, many_info[i].address.area_name, many_info[i].address.house_no, many_info[i].address.district);
   }

    // More on struct size
    struct structure1
    {
        int id1;
        int id2;
        char name;
        char c;
        float percentage;
    };
    struct structure2
    {
        int id1;
        char name;
        int id2;
        char c;
        float percentage;                     
    };
    struct structure1 a;
    struct structure2 b;
    printf("size of structure1 in bytes : %d\n",
            sizeof(a));
    printf ( "\n   Address of id1        = 0x%llx", &a.id1 );
    printf ( "\n   Address of id2        = 0x%llx", &a.id2 );
    printf ( "\n   Address of name       = 0x%llx", &a.name );
    printf ( "\n   Address of c          = 0x%llx", &a.c );
    printf ( "\n   Address of percentage = 0x%llx",
                    &a.percentage );

    printf("   \n\nsize of structure2 in bytes : %d\n",
                    sizeof(b));
    printf ( "\n   Address of id1        = 0x%llx", &b.id1 );
    printf ( "\n   Address of name       = 0x%llx", &b.name );
    printf ( "\n   Address of id2        = 0x%llx", &b.id2 );
    printf ( "\n   Address of c          = 0x%llx", &b.c );
    printf ( "\n   Address of percentage = 0x%llx\n",
                    &b.percentage );

}

