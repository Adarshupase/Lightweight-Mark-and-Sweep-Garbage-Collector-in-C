#include <assert.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h> 
#include <stdbool.h>
#include "./heap.h"


typedef  struct Node Node ;

struct Node {
   char x;
   Node *left;
   Node *right;
};

Node* generate_tree(size_t level_cur, size_t level_max)
{
   if(level_cur < level_max) {
      Node* root = heap_alloc(sizeof(*root));
      assert((char) level_cur - 'a' <= 'z');
      root->x = level_cur + 'a';
      root->left = generate_tree(level_cur + 1,  level_max);
      root->right = generate_tree(level_cur + 1,  level_max);
      return root;

   } else {
      return NULL;
   }
}

void print_tree(Node *root, int space)
{
  if(!root) return;
   space += 5;

   print_tree(root->right,space);

   printf("\n");
   for(int i = 0; i < space; i++){
      printf(" ");
   }
   printf("%c\n",root->x);
   print_tree(root->left, space);
   
}


int main() 
{
   stack_base  = (const uintptr_t *)__builtin_frame_address(0);
   Node* root =   generate_tree(0,3);
   printf("address of the root : %p\n",(void *)root);
   print_tree(root,0);
   printf("\n-----------------------------------\n");
   heap_collect();
   chunk_list_dump(&alloced_chunks,"Allced");
   chunk_list_dump(&freed_chunks, "Freed");
   root = NULL;
   heap_collect();

   printf("\n-----------------------------------\n");
   chunk_list_dump(&alloced_chunks,"Allced");
   chunk_list_dump(&freed_chunks, "Freed");

   
   return 0;
  
 }
