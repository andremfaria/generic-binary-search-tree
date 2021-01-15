# generic-binary-search-tree
A generic BST writted in C language, that can be used in any C project.

## Use example
Check Tests.c for a full example.

## Interface
```c
/**
 * @brief      { Prints the binary tree using pre-order algorithm. }
 *
 * @param[in]  pBinTree  { Binary tree control pointer. }
 **/
void list_pre_order(PbinTree);
/**
 * @brief      { Prints the binary tree using pos-order algorithm }
 *
 * @param[in]  pBinTree  { Binary tree control pointer. }
 */
void list_pos_order(PbinTree);
/**
 * @brief      { Prints the binary tree using in-order algorithm }
 *
 * @param[in]  pBinTree  { Binary tree control pointer. }
 */
void list_in_order(PbinTree);
/**
 * @brief      Gets an element in binary tree. It uses the compare function passed while 
 * initiating the structure to get the element. 
 *
 * @param[in]  pBinTree  { Binary tree control pointer. }
 * @param      searchElement  { Void* pointer to element that we want to search. }
 * @param      retrievedElement  { Void* data to the retrieved information. }
 * @return     0 -> Success.
 *             1 -> Not found.
 */
int get_element(PbinTree,void*,void*);
/**
 * @brief      Deletes an element in binary tree. It uses the compare function passed while 
 * initiating the structure to remove the element. 
 *
 * @param[in]  pBinTree  { Binary tree control pointer. }
 * @param      deleteElement  { Void* pointer to element that we want to delete. }
 * @return     0 -> Success.
 *             1 -> Not found.
 */
int delete_element(PbinTree, void*);
/**
 * @brief      { Function that allow us to insert generic data. }
 *
 * @param[in]  pBinTree  { Binary tree control pointer. }
 * @param      insertElement  { Void* pointer to element that we want to insert. }
 *
 * @return     0 -> Success.
 *             1 -> Malloc failed. Probably not enough memory.
 */
int insert(PbinTree ctrl, void* data);
/**
 * @brief      Initializes the generic binary tree.
 *
 * @param      pBinTree  { Binary tree control pointer. }
 * @param[in]  size_t  { Generic data size. (sizeof(StructMyData)) }
 * @param[in]  compare  { Pointer to the compare function. Its used in insert, delete and get element. This function dictates the order in binary tree. }
 * @param      get_key  { Pointer to the get_key function, that allow us to know the unique key. }
 * @param      to_string  { Pointer to the to_string function. It allow us to creating a char* with all the infos that we need.
 * Its used in pre,pos,in order methods }
 *
 * @return     0 -> Success.
 *             1 -> Malloc failed. Probably not enough memory.
 */
int init_g_tree(PbinTree*,size_t, int (*) (void*,void*),char* (*) (void*), char* (*) (void*));
```
## Compilation

```
gcc -c Gtree.c -g -o Gtree.o&& gcc -c Tests.c -g -o Tests.o&& gcc Gtree.o Tests.o -g -o myapp && ./myapp
```


## Testing environment

- MacOS Catalina 10.15.4
- Gcc 11.0.3
