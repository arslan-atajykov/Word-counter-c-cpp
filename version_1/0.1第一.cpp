

#include <iostream>
#include<cstring>

bool GetWord(FILE* fpInput, char* sWord);

typedef struct node
{
    char word[128];
    int num=1;
    
}sqlist[1000],dataElem;


//void swap(dataElem &a,dataElem &b);
//void swap(dataElem &pa,dataElem &pb);
void swap(dataElem &pa,dataElem &pb)
{
    dataElem temp=pa;
    pa=pb;
    pb=temp;
    
}

using namespace std;

int main()
{
   // char szFileInputFileName[128];
    
   // printf("Please input the file name: \n ");
   // scanf("%s", szFileInputFileName);
    sqlist L;
    

    int cl=0;
    
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
            strcpy(L[cl].word,sWord);
            
            
            cl++;
        }
        //strcmp()
    }
 
     int j;
    
    for(int i=0;i<cl;i++)
    {
        
        j=i+1;
        while(j<cl)
        {
            
           
            if(strcmp(L[i].word,L[j].word)==0)
            {
               
                strcpy(L[j].word,L[cl-1].word);
                
                L[i].num++;
                cl--;
                
                j--;
            }
           
            j++;
        }
    }
    
    
    
    ///sortttttt
    for(int i=0;i<cl;i++)
    {
        for(j=0;j<cl-i-1;j++)
        {
            if(L[j].num<L[j+1].num)
            {
                //std::swap(L[j+1],L[j]);
                
                swap(L[j+1],L[j]);
                
                
            }
        }
    }
    
    
    
   // cout<<L[0].word<<endl;
    
    for(int q=0;q<cl;q++)
    {
        ///if(L[i].num<5)
        //  break;
        cout<<L[q].word<<' '<<L[q].num<<endl;
        
       
    }
    
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
