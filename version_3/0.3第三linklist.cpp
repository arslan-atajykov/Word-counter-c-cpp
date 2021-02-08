

#include <iostream>
#include<cstring>





typedef struct {
    char word[32];        //单词名称
    int count;                //单词出现次数
} el;


typedef struct LNode
{
    el data;       //结点的数据域
    struct LNode * next; //结点的指针域
} LNode;
typedef LNode * LinkList; // 将LNode * 类型 用 LinkList 这个 别名 来使用

bool SingleLinkListInit(LinkList &L);
bool ListDestroy(LinkList &L);
void swap(struct LNode *a, struct LNode *b);

void bubble_sort(LinkList L);

void count_remove(LinkList L);

void printlist(FILE *,LinkList L);
bool GetWord(FILE* fpInput, char* sWord);
using namespace std;

int main()
{
    
    
    
    LinkList L;
    
    
    
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
    
    int cl=0;
    
    
    LinkList temp,p;
    
    
    
    if(SingleLinkListInit(L))
    {
        temp=L;
        while(!feof(fpInput))
        {
            
            char sWord[128];
            
            if (GetWord(fpInput,sWord ))
            {
                
                
                
                p=(LinkList)new(LNode);
                strcpy( p->data.word,sWord);
                p->data.count=1;
                temp->next=p;
                temp=p;
                cl++;
            }
            
        }
        temp->next=NULL;
    }
   
    count_remove(L);
    
    
    bubble_sort(L);
    
    
    
    printlist(fpOutput,L);
   
    
    fclose(fpInput);
    fclose(fpOutput);
    
    ListDestroy(L);
    return 1;
    
}


bool SingleLinkListInit(LinkList &L)
{
    //初始化一个带有头结点的单链表，这样L指向一个结点
    //用下面的代码把L指向的结点创建出来，用new方法
    L = new LNode;
    L -> data.count = 0;
    L->data.word[0] = '\0';
    L -> next = NULL;
    
    
    
    return true;
}

void count_remove(LinkList L)
{
    LinkList ptr,p2,temp;
    ptr=L->next;
    while( ptr->next!=NULL&&ptr!=NULL)
    {
        p2=ptr;
        while(p2->next!=NULL)
        {
            if(strcmp(ptr->data.word,p2->next->data.word)==0)
            {
                
               
                temp=p2->next;
                p2->next=p2->next->next;
                delete(temp);
                ptr->data.count++;
                
            }
            else
                p2=p2->next;
        }
        ptr=ptr->next;
    }
}


void bubble_sort(LinkList L)
{
    LinkList  lptr=NULL;
    LinkList ptr ;
    int swapped;
    do
    {
        swapped=0;
        ptr=L->next;
        
        while(ptr->next!=lptr)
        {
            if(ptr->data.count<ptr->next->data.count)
            {
                swap(ptr,ptr->next);
                swapped=1;
            }
            ptr=ptr->next;
        }
        lptr=ptr;
    }
    while(swapped);

}


void swap(struct LNode *a, struct LNode *b)
{
    el temp = a->data;
    a->data = b->data;
    b->data = temp;
}



void printlist(FILE *fpOutput,LinkList L)
{
    LinkList ptr;
    ptr=L->next;
    while(ptr!=NULL)
    {
        // if(ptr->data.count<5)
        //     break;
        cout<<ptr->data.word<<" "<<ptr->data.count<<endl;
        fprintf(fpOutput,"%s  %d\n",ptr->data.word,ptr->data.count);
        ptr=ptr->next;
    }
}



bool ListDestroy(LinkList &L)
{
    if(!L)
    {
        return false;
    }
    
    
    int i = 0;
    while(L)
    {
        LinkList pTemp;
        pTemp = L;
        
        L = L -> next;
        /*
        if( i == 0)
        {
            printf("\n在销毁链表时，释放头结点 : data = 0x%08x; \n", pTemp->data);
        }
        else
        {
            printf("在销毁链表时，释放第%i个结点：data = 0x%08x;\n", i, pTemp->data);
        }
         */
        delete pTemp;
        
        pTemp = L;
        i++;
    }
    L = NULL;
    return true;
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

