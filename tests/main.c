#include <stdio.h>

#include "library.h"
#include "Args.h"
#include "Struct.h"


int main(int argc, char** argv)
{
    if (isOdd(15)) printf("15 is odd\n");
    if (isEven(22)) printf("22 is even\n");
    int size = 5;
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int odds = countOddNumbers(values, size);
    int evens = countEvenNumbers(values, size);
    printf("%d odds, %d evens\n", odds, evens);
    struct HashMap* hm = MyLib.Hashmap.new(5);
    MyLib.Hashmap.put(hm, "Foo", 3);
    MyLib.Hashmap.display(hm);
    MyLib.Hashmap.free(hm);
    struct Link* list = MyLib.List.new(values, 10);
    MyLib.List.display(list);
    MyLib.List.free(list);
    return 0;
}
