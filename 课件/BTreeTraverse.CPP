#include "stdio.h"
#include "stdlib.h"
typedef struct BiTNode{
  char data;
  struct BiTNode *lchild,*rchild;	
}BiTNode,*BiTree;
char *cTree="-+a  *b  c  /d  -e  f  ";//按先序顺序组织的二叉树  例6.9
//char *cTree="ABC  DE G  F   ";//按先序顺序组织的二叉树  例6.8 
//char *cTree="-+a  *b  -c  d  /e  f  ";//按先序顺序组织的二叉树  例6.9
//char *cTree="-*a  b  c  ";//按先序顺序组织的二叉树  例6.10
//char *cTree="HDA  C B  GF E   ";//按先序顺序组织的二叉树  例6.12
//char *cTree="ABD G  E H  C FI  J  ";//按先序顺序组织的二叉树  讲稿

void  PreOrderTraverse( BiTree T ) {
   // 算法6.1
   // 采用二叉链表存储结构，Visit是对数据元素操作的应用函数，
   // 先序遍历二叉树T的递归算法，对每个数据元素调用函数Visit。
   // 最简单的Visit函数是：
   //     Status PrintElement( ElemType e ) {  // 输出元素e的值
   //        printf( e );  // 实用时，加上格式串
   //        return OK;
   //     }
   // 调用实例：PreOrderTraverse(T, PrintElement);
   if (T) {
           printf("%c",T->data);
           PreOrderTraverse(T->lchild);
           PreOrderTraverse(T->rchild);
          } 
} // PreOrderTraverse
void  InOrderTraverse( BiTree T ) {
   if (T) {
          InOrderTraverse(T->lchild);
          printf("%c",T->data);
          InOrderTraverse(T->rchild);
          } 
} // InOrderTraverse

void  EndOrderTraverse( BiTree T ) {
   if (T) {
           EndOrderTraverse(T->lchild);
           EndOrderTraverse(T->rchild) ;
           printf("%c",T->data);
          } 
} // EndOrderTraverse


int CreateBiTree(BiTree &T) {  // 算法6.4
  // 按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树，
  // 构造二叉链表表示的二叉树T。
  if (*cTree==' ') {T = NULL;cTree++;}
  else {
    if (!(T = (BiTNode *)malloc(sizeof(BiTNode)))) return -1;
    T->data = *cTree++;             // 生成根结点
    CreateBiTree(T->lchild);   // 构造左子树
    CreateBiTree(T->rchild);   // 构造右子树
  }
  return 1;
} // CreateBiTree

BiTree root;
int main()
{
 CreateBiTree(root);
 printf("先序遍历序列："); 
 PreOrderTraverse(root);
 printf("\n");
 printf("中序遍历序列："); 
 InOrderTraverse(root);
 printf("\n");
 printf("后序遍历序列："); 
 EndOrderTraverse(root);
 printf("\n");
}