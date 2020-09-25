#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define max(a,b) (a > b) ? a : b

struct Data {
    int value, height;
    struct Data *left, *right;
} *root = NULL;

struct Data* createNode(int value) {
    struct Data* newNode = (struct Data*)malloc(sizeof(struct Data));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Data *minValueNode(struct Data *node) {
  	struct Data *current = node;
  	while (current->left != NULL)
    	current = current->left;
  	return current;
}

	char route[100];

int getHeight(struct Data *curr) {
	if (curr == NULL)
		return 0;
	return curr->height;
}

struct Data* updateHeight(struct Data* curr) {
	curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
	return curr;
}

struct Data* rightRotate(struct Data* root) {
	struct Data* temp = root->left;
	struct Data* subChild = temp->right;
	
	root->left = subChild;
	temp->right = root;
	
	root = updateHeight(root);
	temp = updateHeight(temp);
	return temp;
}

struct Data* leftRotate(struct Data* root) {
	struct Data* temp = root->right;
	struct Data* subChild = temp->left;
	
	root->right = subChild;
	temp->left = root;
	
	temp = updateHeight(temp);
	root = updateHeight(root);
	return temp;
}

struct Data* insert(struct Data *root, int value) {
	if (root == NULL)
        return createNode(value);
    else if (root->value < value) 
    	root->right = insert(root->right, value);
	else if (root->value > value)
    	root->left = insert(root->left, value);
	else 
		return root;
	
	root = updateHeight(root);
    int bf = getHeight(root->left) - getHeight(root->right);

    if (bf > 1 && root->left->value < value) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if(bf > 1 && root->left->value > value) {
    	return rightRotate(root);
	} else if(bf < -1 && root->right->value < value) {
		return leftRotate(root);
	} else if(bf < -1 && root->right->value > value) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Data *deleteNode(struct Data *root, int value) {
  	if (root == NULL)
    	return root;
  	if (value < root->value)
    	root->left = deleteNode(root->left, value);
  	else if (value > root->value)
    	root->right = deleteNode(root->right, value);
  	else {
    if ((root->left == NULL) || (root->right == NULL)) {
      	struct Data *temp = root->left ? root->left : root->right;
      	if (temp == NULL) {
        	temp = root;
        	root = NULL;
      	} else
        	*root = *temp;
      		free(temp);
    	} else {
      		struct Data *temp = minValueNode(root->right);
      		root->value = temp->value;
      		root->right = deleteNode(root->right, temp->value);
    	}
  	}
  	if (root == NULL)
    	return root;

  	root->height = 1 + max(getHeight(root->left),
               		getHeight(root->right));
  	int bf = getHeight(root->left) - getHeight(root->right);
  	if (bf > 1) {
    	if (getHeight(root->left) >= 0) {
      		return rightRotate(root);
    	} else {
      		root->left = leftRotate(root->left);
    		return rightRotate(root);
    	}
  	}
  	if (bf < -1) {
    	if (getHeight(root->right) <= 0) {
      		return leftRotate(root);
    	} else {
      		root->right = rightRotate(root->right);
      		return leftRotate(root);
    	}
  	}
  	return root;
}




void freeAll(struct Data* curr) {
    if (curr!=NULL) {
		freeAll(curr->left);
		freeAll(curr->right);
		free(curr);
	}
}

void printPreOrder(struct Data *root) {
  if (root != NULL) {
    printf("%d ", root->value);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
  
}

int getLevelUtil(struct Data *node, int key, int level) 
{ 
    if (node == NULL) 
        return 0; 
  
    if (node->value == key) 
        return level; 
  
    int downlevel = getLevelUtil(node->left, key, level+1); 
    if (downlevel != 0) {
    strcat(route,"L");
    	return downlevel; 
    	
	}
    	
        
  
    downlevel = getLevelUtil(node->right, key, level+1); 
   	strcat(route,"R");
    return downlevel;
} 
  
/* Returns level of given data value */
int getLevel(struct Data *node, int key) 
{ 
    return getLevelUtil(node,key,1); 
} 

int main() {
	
	int amount = 4;
	
  struct Data *root = NULL;
	root = insert(root, 702);
	root = insert(root, 107);
	root = insert(root, 745);
	root = insert(root, 570);


  while(1){
  	printf("Data List : ");
  	printPreOrder(root);
  	
	int choice;
	printf("\n1.Add\n2.Search\n3.Exit\n>>");
	scanf("%d",&choice);
	


	if(choice==1){
			
			int inputan;
			do{	
				printf("Input the new receipt number [3 digits]: ");
				scanf("%d",&inputan);
			}while(inputan<=100 or inputan>999);
			root = insert(root, inputan);
			printf("Receipt number %d inserted!\n\n",inputan);
			amount++;
		
		} else if (choice==2){
		int inputan;
		 if(root==NULL){
                printf("There is no receipt in the database. Please add new receipt with the first menu!\n");
                getchar();
             	continue;   
            }
			do{	
				printf("Input the receipt number to be searched: ");
				scanf("%d",&inputan);
			}while(inputan<=100 or inputan>999);
			
			int lvl = getLevel(root, inputan);
			printf("Value : %d\nLevel : %d\nRoute : %s\n",inputan,lvl,route);
			strcpy(route,"");
		
		
		}else if(choice==2){
		return 0;		
		}
  	
  	
  	
  
  	
  }
    return 0;
}


