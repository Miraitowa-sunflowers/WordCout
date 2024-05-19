#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int count_characters(FILE *fp)
{
    int count = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        count++;
    }
    rewind(fp); // �����ļ�ָ���Ա����¶�ȡ
    return count;
}

int count_words(FILE *fp)
{
    int count = 0, in_word = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (isspace(ch) || ch == ',')
        {
            if (in_word)
            {
                count++;
                in_word = 0;
            }
        }
        else
        {
            in_word = 1;
        }
    }
    // ����ļ�ĩβ�ǵ��ʣ������Ӽ���
    if (in_word)
    {
        count++;
    }
    rewind(fp); // �����ļ�ָ���Ա����¶�ȡ
    return count;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    if (!fp)
    {
        perror("Error opening file");
        return 1;
    }

    int result;
    if (strcmp(argv[1], "-c") == 0)
    {
        result = count_characters(fp);
        printf("�ַ�����%d\n", result);
    }
    else if (strcmp(argv[1], "-w") == 0)
    {
        result = count_words(fp);
        printf("��������%d\n", result);
    }
    else
    {
        fprintf(stderr, "Invalid parameter: %s\n", argv[1]);
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}
