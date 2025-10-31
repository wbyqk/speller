// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 936  //前8个单词，考虑了权重

//我定义了一个全局变量来统计单词数量
unsigned int wordcount=0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //把word小写
    char lowerword[LENGTH+1];
    int l=strlen(word);
    for(int i=0;i<l;i++){
        lowerword[i]=tolower(word[i]);
    }
    // 确保字符串以空字符终止(ps:这是我写完代码后询问ai我的代码准确性后ai给我提出的修改建议，平时我自己的代码编写过程中没有这个习惯)
    lowerword[l] = '\0'; 

    unsigned int nowindex1=hash(lowerword);
    //找到头节点
    node*words=table[nowindex1];
    
    //开始遍历链表
    while(words!=NULL){
        if(strcmp(words->word,lowerword)==0){
            return true;
        }
       words=words->next; 
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int value=0;
    for(int i=0;word[i]!='\0';i++){
        //大小写不敏感，进行转换
        char singleword=tolower(word[i]);
        //通过权重保证单词的顺序影响，不能*i,因为这意味着所有以相同字符开头的单词在哈希值上受第一个字符的影响为零
        value+=(int)singleword*(i+1);
    }
    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //初始化hash指针数组
    for(int i=0;i<N;i++){
        table[i]=NULL;
    }
    FILE*file=fopen(dictionary,"r");
    //这步是我在代码完成后让ai帮我检查时ai给的修改建议（load 函数	内存分配检查	缺少对 malloc 返回值（newnode）的 NULL 检查。内存分配失败会导致程序崩溃。）
    if(file==NULL){
        return false;
    }
    
    char wordbuffer[LENGTH+1];
    while(fscanf(file,"%s",wordbuffer)!=EOF){
        //想要读取新word，需要给word分配内存
        node*newnode=(node*)malloc(sizeof(node));
        if(newnode==NULL){
        fclose(file);
        return false;
    }
        // 将单词复制到新节点中
        strcpy(newnode->word,wordbuffer);
        unsigned int index=hash(newnode->word);
        //执行插入操作
        newnode->next=table[index];
        table[index]=newnode;
        wordcount++;
    }
    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i=0;i<N;i++){
        node *nowindex2=table[i];
        while(nowindex2!=NULL){
            //保存下一个节点的地址
            node*temp=nowindex2->next;
            free(nowindex2);
            nowindex2=temp;
        }
    }
    wordcount=0;
    return true;
}
