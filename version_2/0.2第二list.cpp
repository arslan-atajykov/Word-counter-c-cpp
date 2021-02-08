#include <iostream>
#include<cstring>
#define MAX 1000
bool GetWord(FILE* fpInput, char* sWord);


typedef struct
{
    char word[32];
    int num;
}El,dataElem;


typedef struct list{
    El *elem;
    unsigned int length;
    unsigned int max;
}*ptr;

bool Inlist(list &l);
bool DestroyList(list &L);



//void swap(dataElem *a,dataElem *b);
void swap(dataElem &pa,dataElem &pb);


 void swap(dataElem &pa,dataElem &pb)
 {
 dataElem temp=pa;
 pa=pb;
 pb=temp;
 
 }
 
using namespace std;

int main()
{
    
    
    
    list L;
    Inlist(L);
    
    
    
    FILE* fpInput;
    fpInput = fopen("//Users/macbookpro/Desktop/aa.txt", "r");
    if (!fpInput)        //fnInput==NULL
    {
        printf("cannot open the file, quit.");
        return -1;
    }
    
    FILE* fpOutput;
    fpOutput = fopen("/Users/macbookpro/Desktop/sample.txt", "w");
    if (!fpOutput)
    {
        printf("cannot open the file..., quit.");
        fclose(fpInput);
        return -1;
    }
    
    
    while(!feof(fpInput))
    {
        
        char sWord[128];
        if (GetWord(fpInput,sWord ))
        {
            int i=0;
            for(i=0;i<L.length;i++)
            {
                if(strcmp(L.elem[i].word,sWord)==0)
                {
                    L.elem[i].num++;
                    break;
                }
            
                
                
                
            }
            if(i==L.length)
            {
                if(L.length<L.max)
                {
                    strcpy(L.elem[L.length].word,sWord);
                    L.elem[L.length].num=1;
                    L.length++;
                }
            }
        }
    }
    
    int j;
    
    
     ///sortttttt
     for(int i=0;i<L.length;i++)
     {
     for(j=0;j<L.length-i-1;j++)
     {
     if(L.elem[j].num<L.elem[j+1].num)
     {
     //std::swap(L[j+1],L[j]);
     
     swap(L.elem[j+1],L.elem[j]);
     
     
     }
     }
     }
     
    
    
    
    
    for(int q=0;q<L.length;q++)
    {
        ///if(L[i].num<5)
        //  break;
        cout<<L.elem[q].word<<' '<<L.elem[q].num<<endl;
        fprintf(fpOutput, "%s %d\n", L.elem[q].word,L.elem[q].num);
        
        
    }
    
    DestroyList(L);
    
    
    fclose(fpInput);
    fclose(fpOutput);
    return 1;
    
}

bool GetWord(FILE* fpInput, char* sWord)
{
    char cTemp;
    
    int i = 0;
    
    while (!feof(fpInput))
    {
        //从文件中读入一个字符
        cTemp = fgetc(fpInput);
        
        if ((cTemp >= 'A') && (cTemp <= 'Z'))
        {
            //是大写字符，转换为小写字符
            cTemp = cTemp + 32;
            sWord[i] = cTemp;
            i++;
        }
        else if (((cTemp >= 'a') && (cTemp <= 'z'))
                 || ((cTemp >= '0') && (cTemp <= '9'))
                 || (cTemp == '-'))
        {
            //是小写字符、数字或 -，有效字符
            sWord[i] = cTemp;
            i++;
        }
        else
        {
            //其他字符，表示找到了一个单词
            sWord[i] = '\0';// 0;
            break;
        }
        
    }
    
    //检查是否全部是数字字符
    bool isdigitall = true;
    for (int j = 0; j < i; j++)
    {
        if (!((sWord[j] >= '0') && (sWord[j] <= '9')))
        {
            isdigitall = false;
            break;
        }
    }
    
    if (isdigitall)
    {
        //如果全部都是数字，单词内容清空
        sWord[0] = '\0';
        return false;
    }
    else if (sWord[0] == '\0')
    {
        //如果单词长度为0，即连续都是符号、空格等，返回false
        return false;
    }
    else
    {
        return true;
    }
}
bool Inlist(list &l)
{
    l.elem=new El[ 1000];
    if(!l.elem)
    {
        return false;
    }
    l.length=0;
    l.max=MAX;
    return true;
}

bool DestroyList(list &L)
{
    if(L.elem)
    {
        free(L.elem);
        return true;
    }
    else
        return false;
}









