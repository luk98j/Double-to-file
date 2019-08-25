#include <stdio.h>
#include <stdlib.h>
union double_to_char_t
{
    double d;
    char tab[8];
};
int load_double(union double_to_char_t *dtc, const char *filename)
{
    int temp = 0;
    FILE * file;
    if (filename==NULL){
            return 1;
    }
    if (dtc==NULL){
            return 1;
            }

    file = fopen(filename, "rb");
    if (file==NULL) return 2;

    for(int i = 0; i < 8; i++)
    {
        temp += fread((dtc->tab+i),sizeof(char),1,file);

    }
    if(temp != 8)
    {
        fclose(file);
        return 3;
    }
    fclose(file);
    return 0;
}
int save_double(const union double_to_char_t *dtc, const char *filename)
{
    int temp = 0;
     FILE * file;
    if (filename==NULL){
            return 1;
    }
    if (dtc==NULL){
            return 1;
    }
    file = fopen(filename, "wb");
    if (file==NULL) return 2;
    for(int i = 0; i < 8; i++)
    {
        temp += fwrite((dtc->tab+i),sizeof(char),1,file);
    }
    if(temp != 8)
    {
        fclose(file);
        return 3;
    }
    fclose(file);
    return 0;
}
int main()
{
    union double_to_char_t unia;
    char path[40];
    char *ptr_path = path;
    char path1[40];
    char *ptr_path1 = path1;
    int test,test1;
    double result;

    printf("Podaj liczbe: ");
    test = scanf("%lf",&unia.d);
    getchar();
    if(test!=1)
    {
        printf("Incorrect input");
        return 1;
    }

    printf("Podaj nazwe pliku: ");
    scanf("%39s",ptr_path);

    while(getchar()!='\n');

    test = save_double(&unia,ptr_path);
    if(test == 2)
    {
        printf("Couldn't create file");
        return 5;
    }
    else if(test == 3)
    {
        printf("File corrupted");
        return 6;
    }else{
    printf("File saved\n");
    }


    printf("Podaj nazwe pliku: ");
    scanf("%39s",ptr_path1);
    test1 = load_double(&unia,ptr_path1);

    if(test1 == 2)
    {
        printf("Couldn't open file");
        return 4;
    }
    else if(test1 == 3)
    {
        printf("File corrupted");
        return 6;
    }

    result = unia.d;
    printf("%lf",result);
    return 0;
}
