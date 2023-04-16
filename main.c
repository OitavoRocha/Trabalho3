// OTAVIO ROCHA - M2 - 21104191
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int bool;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct TreeNode * Node;

Node create( int value ); // função para criar nodos/arvore
bool leafSimilar( struct TreeNode * root1, struct TreeNode * root2 ); // função em questão
int * getLeafs( struct TreeNode * root, int * counter, int * leafs ); // função que retorna um vetor com os valores de 
//todas as folhas, da esquerda pra direita
int numberOfLeafs( struct TreeNode * root, int n ); // função que retorna a quantidade de folhas da arvore
void clear( Node root ); // função para limpar a arvore

int main() {
/*        DIFERENTES
        1            1
       / \          / \
      2   3        3   2  */
    Node root1 = create( 1 );
    Node root2 = create( 1 );

    root1->left = create( 2 );
    root1->right = create( 3 );

    root2->left = create( 3 );
    root2->right = create( 2 );

/*          SIMILARES
        5                 0
       / \             /    \
      1   3           1      3 
     /   /             \    / 
    9   0               2  0
   /                   /
  4                   4
    Node root1 = create( 5 );
    Node root2 = create( 0 );

    // criação da arvore 1
    root1->left = create( 1 );
    root1->left->left = create( 9 );
    root1->left->left->left = create( 4 );
    root1->right = create( 3 );
    root1->right->left = create( 0 );

    //criação da arvore 2
    root2->left = create( 1 );
    root2->left->right = create( 2 );
    root2->left->right->left = create( 4 );
    root2->right = create( 3 );
    root2->right->left = create( 0 );
*/
    if ( leafSimilar( root1, root2 ) ) 
        printf("\nFolhas Similares\n");
    else
        printf("\nFolhas Diferentes\n");

    clear( root1 );
    clear( root2 );
    return 0;
}

Node create( int value ) {
    Node newNode = (Node)malloc( sizeof( struct TreeNode ) );

    if ( !newNode ) {
        printf("Impossivel alocar espaço para o no\n");
        return NULL;
    }

    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

bool leafSimilar( struct TreeNode * root1, struct TreeNode * root2 ) {
    int counter = 0;
    int size = numberOfLeafs( root1, 0 );

    if (size != numberOfLeafs( root2, 0 ))
        return FALSE;       // tamanhos diferentes, conjunto de folhas diferentes

    int * leafsRoot1 = ( int * )malloc( sizeof( int ) * size );
    int * leafsRoot2 = ( int * )malloc( sizeof( int ) * size );

    leafsRoot1 = getLeafs( root1 , &counter , leafsRoot1 );
    counter = 0;
    leafsRoot2 = getLeafs( root2 , &counter, leafsRoot2 );

    // compara dois vetores de inteiros que contem o conjunto de folhas de cada arvore, se forem iguais, retorna verdadeiro
    for( int i = 0 ; i < size ; i++ ) 
        if( ! (*(leafsRoot1 + sizeof( int )*i ) == *(leafsRoot2 + sizeof(int)*i ) ) ){
            free( leafsRoot1 );
            free( leafsRoot2 );
            return FALSE;
        }

    free( leafsRoot1 );
    free( leafsRoot2 );
    return TRUE;
}

int *getLeafs( struct TreeNode * root, int * counter, int * leafs ) {
    if( root == NULL )
        return leafs;

    if ( root->left == NULL && root->right == NULL ) {
        *(leafs + ( sizeof( int ) * (*counter) ) ) = root->val;
        (*counter)++;
        return leafs;
    }

    getLeafs( root->left, counter, leafs );
    getLeafs( root->right, counter, leafs );
    return leafs;
}

int numberOfLeafs( struct TreeNode * root, int n ) {
    if( root == NULL )
        return n;

    if ( root->left == NULL && root->right == NULL )
        return n + 1;

    n = numberOfLeafs( root->left, n );
    n = numberOfLeafs( root->right, n );
    return n;
}

void clear( Node root ) {
    if ( root == NULL )
        return;
    
    clear( root->left );
    clear( root->right );

    free( root );
}
