#include <stdio.h>
#define maxKey 100

typedef int Item;
Item ITEMscan(void);
int ITEMeq(Item A, Item B);
int ITEMneq(Item A, Item B);
int ITEMlt(Item A, Item B);
int ITEMgt(Item A, Item B);
void ITEMshow(Item A);
Item ITEMrand(void);

int ITEMeq(Item A, Item B)
{
    return (A == B);
}
int ITEMneq(Item A, Item B)
{
    return (A != B);
}
int ITEMlt(Item A, Item B)
{
    return (A < B);
}
int ITEMgt(Item A, Item B)
{
    return (A > B);
}
Item ITEMscan(void)
{
    Item A;
    printf("item = ");
    scanf("%d", &A);
    return A;
}
void ITEMshow(Item A)
{
    printf("%6d \n", A);
}
