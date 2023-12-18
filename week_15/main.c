#include "main.h"
#include "limits.h"

void my_add(My_int answer, My_int input_1, My_int input_2)
{
    // printf("DEBUG : ");
    // my_number_print(answer);
    // printf("\n");
    // printf("DEBUG input1: ");
    // my_number_print(input_1);
    // printf("\n");
    // printf("DEBUG input2: ");
    // my_number_print(input_2);
    // printf("\n");
    int carry = 0, i;
    for (i = 0; i < MAX; i++)
    {
        int tmp = input_1[i] + input_2[i] + carry;
        carry = tmp / 10;
        tmp = tmp % 10;
        answer[i] = tmp;
    }
    if (carry != 0)
        printf("Overflow!\n");
}
void my_number_print(My_int input)
{
    int i;
    int leading_zero = 1;
    for (i = MAX - 1; i >= 0; i--)
    {
        if (input[i] == 0 && leading_zero)
            continue; // skip leading zero
        else
        {
            leading_zero = 0;
            printf("%d", (int)input[i]);
        }
    }
}

void trans_from_string(My_int res, char *user_input)
{
    int dis_to_zero;
    int index = strlen(user_input);
    int len = strlen(user_input);
    // printf("\n DEBUG : %d\n", index);
    index--;
    while (1)
    {
        if (user_input[index] == '\0')
            return;
        dis_to_zero = user_input[index] - '0';
        if (dis_to_zero < 0 || dis_to_zero > 9)
        {
            printf("Wrong input, try again...\n");
            return;
        }
        res[len - index - 1] = dis_to_zero;
        index--;
    }
}

void clear_my_int(My_int target)
{
    for (int i = 0; i < MAX; i++)
    {
        target[i] = 0;
    }
}

void clear_buffer(char * buffer){
    for(int i =0 ; i< MAX+1; i++){
        buffer[i] = 0;
    }
}

int main(void)
{
    My_int input_1, input_2, adding_result;
    // input_1[0] = 1;
    // input_1[1] = 1;
    // input_1[2] = 1;
    // input_1[3] = 0;

    // input_2[0] = 5;
    // input_2[1] = 5;
    // input_2[2] = 5;
    // input_2[3] = 0;

    // clear_my_int(adding_result);

    // my_add(adding_result, input_1, input_2);
    // my_number_print(adding_result);
    char buffer[MAX + 1] = {0};
    while (1)
    {
        clear_my_int(input_1);
        clear_my_int(input_2);
        clear_my_int(adding_result);
        clear_buffer(buffer);

        printf("\nfirst input : ");
        scanf("%s", buffer);
        trans_from_string(input_1, buffer);
        printf("Second input : ");

        scanf("%s", buffer);
        trans_from_string(input_2, buffer);
        my_add(adding_result, input_1, input_2);
        my_number_print(adding_result);
    }

    return 0;
}