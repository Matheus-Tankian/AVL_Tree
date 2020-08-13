#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BECK {
	int id;
	int quantidade;
	float preco;
	char modelo[20];
	char marca[20];
	struct BECK *esq;
	struct BECK *dir;
}BECK;

typedef struct BinaryTree {
	BECK *raiz;
	
}Btree;

BECK* inicializaNo(int id, char modelo[], char marca[], int quantd, float preco) {//inicializa os noss da arvore
	BECK* node = (BECK*) malloc(sizeof(BECK));
	node->id = id; 
	strcpy(node->modelo,modelo);
	strcpy(node->marca,marca);
	node->quantidade = quantd;
	node->preco = preco;
	node->esq = NULL;
	node->dir = NULL;

	return node;
}

Btree* inicializaArvore(int id, char modelo[], char marca[], int quantd, float preco) {//inicializa arvore

	//printf("Inicializando Árvore. Raiz com valor: %d\n",id);
	
	BECK* node = inicializaNo(id,modelo,marca,quantd,preco);
	
	Btree* arv = (Btree*) malloc(sizeof(Btree));
	arv->raiz = node;
	
	
	return arv;
}



void imprimirtab(int n){  //recebe os valores de imprimr e mostra eles tabulados
	for(int i=0;i<n;i++){
		printf("\t");
	}
	
}


void imprimir(BECK* aux, int nivel){ //percorre arvore por nivel pra tabular a sua impresao
	if(aux!=0){
		imprimir(aux->dir,nivel+1);
		imprimirtab(nivel);
		printf("|id:%d |modelo:%s |marca:%s |qtd:%d |preco:%0.2f|\n",aux->id,aux->modelo,aux->marca,aux->quantidade,aux->preco );
		imprimir(aux->esq,nivel+1);
	}
}
	


BECK* rotacaoLL(BECK* raiz){ // raiz == nó que foi desbalanceado
	BECK* node;
	node = raiz->esq; //Nó recebe a esquerda da raiz passada
	
	raiz->esq = node->dir; //Nó esquerdo da raiz recebe a direita do no criado
	node->dir = raiz; //Nó direito do nó criado recebe a raiz
	
	raiz = node;
	return raiz;
}

BECK* rotacaoRR(BECK* raiz){ // raiz == nó que foi desbalanceado

	BECK* node;
	node = raiz->dir; //Nó recebe a direita da raiz passada

	raiz->dir = node->esq; //Nó direito da raiz recebe a esquerda do no criado

	node->esq = raiz; //Nó esquerdo do nó criado recebe a raiz

	raiz = node;

	return raiz;
}


BECK* rotacaoLR(BECK* raiz){ // desbalanceado pra esq
raiz->esq=	rotacaoRR(raiz->esq); //raiz da esq da esq recebe a rotacao simples da direita
	raiz=rotacaoLL(raiz); // no recebe  a rotacao simples da esquerda
	return raiz;
}

//rotação dupla a esquerda
BECK* rotacaoRL(BECK* raiz){ //desbalanceado pra direita
raiz->dir=	rotacaoLL(raiz->dir);// raiz dir da dir recebe rotacaoi da esq
raiz=	rotacaoRR(raiz); //raiz rotacao simple da direta
	return raiz;
}

int altura(BECK* root) {//
   if (root == NULL){ 
      return -1; // altura da árvore vazia
	}else {
      int he = altura (root->esq); //pecorre toda a esquerda e atribui 1 acada no encontrado a esquerda
      int hd = altura (root->dir);//pecorre toda a direita e atribui 1 acada no encontrado a direita
      if (he < hd){
		  return hd + 1;
	  }else{
	  	return he + 1;
	  } 
   }
}
 
int fatorBalanceamento(BECK* node){

	return (altura(node->esq) - altura(node->dir));  //Retorna a diferenca da altura dos nós ESQ e DIR
}


BECK* verifica_Balanceamento(BECK* raiz){ // recebe a arvore por funcao
	
		BECK* aux = NULL;
//primeiro ele percorre na arvore e mais embaixo ele atribui o fb
	if ( raiz->esq )
	{
		raiz->esq = verifica_Balanceamento ( raiz->esq );
	}
	if (raiz->dir )
	{
		raiz->dir = verifica_Balanceamento (raiz->dir );//percorre toa a esquerda e toda a direta 	
	}
	
	if(fatorBalanceamento(raiz) >= 2){ // logo depois ele chama o fb pra verivicar se a arvore esta balanceada
		if(fatorBalanceamento((raiz)->esq) == -1){
	   	  aux = rotacaoLR(raiz); //rotacao dupla direita fb tem q ser fb >2 e fb ==-1
		}else{
			aux = rotacaoLL(raiz);//rotacao simples esquerda fb >2 efb != -1
		}
	}else{
		if(fatorBalanceamento(raiz) <= -2){
			if(fatorBalanceamento((raiz)->dir) == 1){
				aux=rotacaoRL(raiz);//rotacao dupla desquerda fb<-2 e fb == 1
			}else{ 
				aux = rotacaoRR(raiz);// rotacao simples a direita fb<-2 e fb !=1
		
			}
		}else{
			 aux=raiz;// ta balanceada
		}
	}
	return aux;
 
}

void balancear_tree (Btree* arvore)
{
	BECK* raiz = NULL;

	raiz = verifica_Balanceamento ( arvore->raiz ); // recebe a arvore e verifica seu balanceamento
	if ( raiz != arvore->raiz )
	{
		arvore->raiz = raiz;
	}
}



void inserir(BECK *raiz, BECK *node) {  //insere um valor por vez 

	if (raiz != NULL) {
		if (node->id < raiz->id) {
			if (raiz->esq == NULL) {
				raiz->esq = node;
			} else {
				inserir(raiz->esq, node);
			}
		} else {
			if (raiz->dir == NULL) {
				raiz->dir = node;
			} else {
				inserir(raiz->dir, node);
			}
		}
	} else {
		raiz = node;
	}

}

BECK* buscar(BECK* raiz , int id){ // busca pelo id passado por parametro percorrendo a arvore por recusividade e quando 
	while(raiz!=NULL){  //acha o valor ele pede pra edita o conteudo dele
		if(raiz->id == id){
			printf("Elemento encontrado!\n");
			printf("Digite um novo modelo: ");
			scanf("%s",raiz->modelo);
			printf("Digite uma nova marca: ");
			scanf("%s",raiz->marca);
			printf("Digite uma nova quantidade: ");
			scanf("%d",&raiz->quantidade);
			printf("Digite um novo valor: ");
			scanf("%f",&raiz->preco);
			return raiz;
		}
		if(id < raiz->id){
			if(raiz->esq == NULL){
				return NULL;
			}else {
				raiz = raiz->esq;
			}
		}else{
			if(raiz->dir == NULL){
				return NULL;
			}else{
				raiz = raiz->dir;
			}
		}

	}
	return 0;
}


BECK *MaiorDireita(BECK **no){
    if((*no)->dir != NULL) 
       return MaiorDireita(&(*no)->dir);
    else{
       BECK *aux = *no;
       if((*no)->esq != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da esquerda!
          *no = (*no)->esq;
       else
          *no = NULL;
       return aux;
       }
}

//remover 

void remover(BECK **pRaiz, int numero){//** pra nao perder conteudo da arvore
    if(*pRaiz == NULL){   // esta verificacao serve para caso o numero nao exista na arvore.
       printf("ID nao existe na arvore!");
       getchar();
       return;
    }
    if(numero < (*pRaiz)->id)//buscar o numero
       remover(&(*pRaiz)->esq, numero);
    else 
       if(numero > (*pRaiz)->id)//bucar o numero
          remover(&(*pRaiz)->dir, numero);
       else{    // se nao eh menor nem maior, logo, eh o numero que estou procurando! :)
          BECK *pAux = *pRaiz;     
          if (((*pRaiz)->esq == NULL) && ((*pRaiz)->dir == NULL)){         // se nao houver filhos flha
                free(pAux);
                (*pRaiz) = NULL; 
               }
          else{     // so tem o filho da direita no
             if ((*pRaiz)->esq == NULL){
                (*pRaiz) = (*pRaiz)->dir;
                pAux->dir = NULL;
                free(pAux); 
				pAux = NULL;
                }
             else{            //so tem filho da esquerda no
                if ((*pRaiz)->dir == NULL){
                    (*pRaiz) = (*pRaiz)->esq;
                    pAux->esq = NULL;
                    free(pAux); 
					pAux = NULL;
                    }
                else{      
                   pAux = MaiorDireita(&(*pRaiz)->esq); //no com dois filhos  
                   pAux->esq = (*pRaiz)->esq;         
                   pAux->dir = (*pRaiz)->dir;
                   (*pRaiz)->esq = (*pRaiz)->dir = NULL;
                   free((*pRaiz));  
				   *pRaiz = pAux;  
				   pAux = NULL;   
                   }
                }
             }
          }
}


void menu(){
	printf("|=============================================|\n");
	printf("| BECK intrumentos                            |\n");
	printf("|=============================================|\n");
	printf("| 1-Inserir instrumento                       |\n");
	printf("| 2-Mostrar instrumento                       |\n");
	printf("| 3-Atualizar dados                           |\n");
	printf("| 4-remover                                   |\n");
	printf("| 0-Exit                                      |\n");
	printf("|=============================================|\n");
}

int main(void){
		int rem;
		static int mais=100;
		int id1 = 10,qtd1 = 10;
		float preco1=10;
		char modelo1[20]={"batata"},marca1[20]={"batata"};
		//printf("Raiz");
	//	printf("Digite um id, modelo, marca, quantidade e preco: ");
		//scanf("%d%s%s%d%f",&id1,modelo1,marca1,&qtd1,&preco1);
    	Btree* arvore = inicializaArvore(id1,modelo1,marca1,qtd1,preco1); 
 		int id=10,qtd=0;
		float preco=0;
		char modelo[20],marca[20];
    	BECK *res;
	int op=0;
	
	do{
		system("cls");
		menu();
		scanf("%d",&op);
		puts("|============================================|");
		switch(op)
		{
		case 1://, marca, quantidade e preco:
			id=mais;
			mais=mais+10;
			
			printf("Insesrir\n");
			puts("|============================================|");
 	 	 	    printf("Digite um modelo: ");
				scanf("%s",modelo);
				printf("Digite uma marca: ");
				scanf("%s",marca);
				printf("Digite uma quantidade: ");
				scanf("%d",&qtd);
				printf("Digite um preco: ");
				scanf("%f",&preco);
				inserir(arvore->raiz,inicializaNo(id,modelo,marca,qtd,preco));	
		   	   	balancear_tree(arvore);
		   	   	remover(&arvore->raiz,id1);
			break;
		case 2:
			printf("imprimmir\n");
			puts("|============================================|");
			imprimir(arvore->raiz,0);
			system("pause");
			break;
		case 3:
			printf("Atualizar dados\n");
			puts("|============================================|");
			printf("Digite o ID: ");
			scanf("%d",&id);
			res = buscar(arvore->raiz,id);
			if(res != 0){
				printf("id encontrado %d\n",res->id);
				system("pause");
			}else{
				printf("Nao encontrado\n");
				system("pause");
			}   	   	

			break;
		case 4:
			printf("Remover\n");
			puts("|============================================|");
			printf("Digite um elemento para remover : \n");
			scanf("%d",&rem);
			remover(&arvore->raiz,rem);
			balancear_tree(arvore);
			
			break;
		case 0:
			break;
		default:
			printf("Opcao invalida\n");
			break;
		}
	}while(op!=0);
	
		free(arvore);
	return 0;
}