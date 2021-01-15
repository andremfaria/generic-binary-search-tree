#include "Gtree.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


typedef struct SPerson
{
	char *id;
	char *name;
	int age;
}StPerson, *PtrPerson;

int compare(void* a, void* b)
{
	PtrPerson p1= (PtrPerson) a, p2= (PtrPerson) b;
	return atoi(p1->id) - atoi(p2->id);
}

char* get_key_value(void* data)
{
	PtrPerson p = (PtrPerson) data;
	return p->id;
}
char* to_string(void* a)
{
	PtrPerson person = (PtrPerson) a;
	char age[3];
	
	char * personInfo = (char*) malloc(48);
	strcpy(personInfo,"\nID: ");
	strncat(personInfo, person->id,strlen(person->id));
	strcpy(personInfo,"\nName: ");
	strncat(personInfo, person->name,strlen(person->name));
	strcat(personInfo, ", Age: ");
	sprintf(age, "%d", person->age);
	strcat(personInfo,age);
	strcat(personInfo,"\n");

	return personInfo;	
}

char* to_string_only_id(void * a)
{
	PtrPerson person = (PtrPerson) a;

	char * personInfo = (char*) malloc(48);
	strncat(personInfo, person->id,strlen(person->id));
	strcat(personInfo,"-");

	return personInfo;	
}

PtrPerson createPerson(char *id, char * name, int age)
{
	PtrPerson person = (PtrPerson) malloc (sizeof (StPerson));
	
	person->id = id;
	person->name = name;
	person->age=age;

	return person;
}

int main(int argc, char const *argv[])
{
	int retrievedResult=-1;
	PtrPerson test;
	PbinTree tree;

    (void)init_g_tree(&tree,sizeof(StPerson), compare,get_key_value, to_string_only_id);
 
    test = createPerson("15","Test",12);
    (void)insert(tree,test);
    
    test = createPerson("10","Test2",14);
    (void)insert(tree,test);
    
    test = createPerson("20","Test3",15);
    (void)insert(tree,test);

    test = createPerson("5","Test4",15);
    (void)insert(tree,test);

    test = createPerson("12","Test4",15);
    (void)insert(tree,test);

    test = createPerson("16","Test5",15);
    (void)insert(tree,test);

    test = createPerson("25","Test6",15);
    (void)insert(tree,test);
    
    printf("\n###Pre-order###\nExpect: 15-10-5-12-20-16-25\nResult: ");
    list_pre_order(tree);
    printf("\n###Pos-order###\nExpect: 5-12-10-16-25-20-15\nResult: ");
    list_pos_order(tree);
    printf("\n###In-order ###\nExpect: 10-12-15-16-20-25\nResult: ");
    list_in_order(tree);

    PtrPerson retrievedPerson = (PtrPerson) malloc (sizeof(StPerson)), 
    	searchPerson = (PtrPerson) malloc (sizeof(StPerson));
    searchPerson->id="25";

    retrievedResult = get_element(tree, searchPerson, retrievedPerson);
    printf("\nSearch for %s id.Retrieved Person Result -> %d \n", searchPerson->id,retrievedResult);
    if(retrievedResult == 0)	
		printf("\nRetrieved person: %s\n", to_string(retrievedPerson));

	//Remove leaf.
	printf("\nDeleting 25. Delete response: %d \n",delete_element(tree,test));
	printf("[Leaf removing] After remove %s Pre-order: ", test->id);
	list_pre_order(tree);
	
	//Remove non-leaf
	test->id="20";
	printf("\nDeleting 20. Delete response: %d \n",delete_element(tree,test));
	printf("[Non leaf removing] After remove %s Pre-order: ", test->id);
	list_pre_order(tree);

	//Remove root
	test->id="15";
	printf("\nDeleting 15. Delete response: %d \n",delete_element(tree,test));
	printf("[Root] After remove %s Pre-order: ", test->id);
	list_pre_order(tree);

	//Remove non existent element
	printf("\nDeleting 15. Delete response: %d \n",delete_element(tree,test));


	
	return 0;
}	