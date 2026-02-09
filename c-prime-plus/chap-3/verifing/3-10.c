/* escape.c -- uses escape characters */
#include <stdio.h>

int main(void)
{
    float salary;

    printf("\aEnter your desired monthly salary:");
    printf("$_______\b\b\b\b\b\b\b");
    // 因为\b，光标被移动到下划线开始的字符，然后由scanf输入的字符替换掉了
    // 所以如果输入的字符不够，后面的下划线还会留在CLI中
    scanf("%f", &salary);

    return 0;

}