#include <iostream>

using namespace std;

struct Funcionario//Montando struct encadeada
{
	int prontuario;
	string nome;
	double salario;
	struct Funcionario *prox;
};

Funcionario* init() //Iniciar lista encadeada com valor null
{
	return NULL;
}

Funcionario* insert(Funcionario* lista, int i)//Encadear o num prontuario
{
	Funcionario* novo=new Funcionario;
	novo->prontuario=i;
	novo->prox=lista;
	return novo;
}

Funcionario* remove(Funcionario* lista, int i)//Desencadear um prontuario
{
	Funcionario *ant = NULL;
	Funcionario *aux;
	
	aux = lista;
	while (aux != NULL && aux->prontuario != i)
	{
		ant = aux;
		aux = aux->prox;
	}
	if (aux == NULL)
	{
		return lista;
	}
	if (ant == NULL) // era primeiro
	{
		lista = aux->prox;
	}
	else // estava no meio
	{
		ant->prox = aux->prox;
	}
	free(aux);
	return lista;
}

void print(Funcionario* lista)//Exibir ficha dos funcionarios + salario total
{
	Funcionario* aux;
	aux = lista;
	int salario=0;
	while (aux != NULL)
	{
		cout << "Numero prontuario: " << aux->prontuario <<" - Nome: "<<aux->nome<<" - Salario: R$"<<aux->salario<<endl;
		salario=salario+aux->salario;
		aux = aux->prox;
	}
	cout<<endl<<"Total dos salarios: R$"<<salario<<endl;
}

Funcionario* find(Funcionario* lista, int i)//Procurar prontuario
{
	Funcionario* aux;
	aux = lista;
	while (aux != NULL && aux->prontuario != i)
	{
		aux = aux->prox;
	}
	if (aux == NULL)
	{
		aux = new Funcionario;
		aux->prontuario = -1;
		aux->prox = NULL;
	}
	return aux;
}

void freeList(Funcionario* lista)//Liberar memoria
{
	Funcionario *aux;
	aux = lista;
	while (aux != NULL)
	{
		Funcionario *ant = aux->prox;
		free(aux);
		aux = ant;
	}
}

int main(int argc, char** argv)
{
	bool menu=true;
	int opcao, pront=0, apagar=0, pesquisar=0;
	string nome;
	double salario;
	Funcionario *ficha;
	ficha=init();
	
	cout<<"Bem-vindo ao cadastro de funcionarios!"<<endl;
	while(menu!=false)//Criando um loop para o menu
	{
	cout<<endl<<"Escolha uma opcao:"<<endl;
	cout<<"0 - Sair do programa."<<endl;
	cout<<"1 - Incluir um funcionario."<<endl;
	cout<<"2 - Excluir um funcionario."<<endl;
	cout<<"3 - Pesquisar um funcionario (por prontuario)."<<endl;
	cout<<"4 - Listar todos os funcionarios."<<endl<<endl;
	cout<<"Digite a opcao desejada: ";
	
	cin>>opcao;
	
	while(!cin||opcao<0||opcao>4)
	{
		cin.clear();
		cin.ignore();
		cout<<"Opcao invalida! Digite um numero entre 0 e 4: ";
		cin>>opcao;
	}
	
	switch(opcao)
	{
	case 0://Saindo do loop do menu e finalizando
		cout<<endl<<"Obrigado e volte sempre!"<<endl;
		menu=false;
		break;
	
	case 1://Incluindo um funcionario
		cout<<endl<<"Incluir um funcionario."<<endl;
		pront++;
		ficha=insert(ficha,pront);
		cout<<"Numero do prontuario: "<<pront<<endl;
		cout<<"Digite o nome do funcionario: ";
		cin>>nome;
		ficha->nome=nome;
		cout<<"Digite o salario: R$";
		cin>>salario;
		while(!cin)
		{
			cin.clear();
			cin.ignore();
			cout<<"Opcao invalida! Digite um numero valido: ";
			cin>>opcao;
		}
		ficha->salario=salario;
		cout<<"Funcionario cadastrado!"<<endl;
		break;
	
	case 2://Excluindo um funcionario
		if(pront>0){
		cout<<endl<<"Excluir um funcionario."<<endl;
		cout<<"Insira o numero do prontuario para ser apagado: ";
		cin>>apagar;
		while(!cin||apagar<0||apagar>pront)
		{
			cin.clear();
			cin.ignore();
			cout<<"Opcao invalida! Digite um numero de prontuario valido (entre 1 e "<<pront<<"): ";
			cin>>apagar;
		}
		ficha=remove(ficha,apagar);
		cout<<"Funcionario excluido!"<<endl;
		}
		else{
		cout<<"Necessario cadastrar um funcionario primeiro!"<<endl;	
		}
		break;
	
	case 3://Pesquisando um funcionario
		if(pront>0){
		cout<<endl<<"Pesquisar um funcionario."<<endl;
		cout<<"Digite o numero de prontuario para pesquisar: ";
		cin>>pesquisar;
		while(!cin||pesquisar<0||pesquisar>pront)
		{
			cin.clear();
			cin.ignore();
			cout<<"Opcao invalida! Digite um numero de prontuario valido (entre 1 e "<<pront<<"): ";
			cin>>pesquisar;
		}
		Funcionario *procurado;
		procurado=find(ficha,pesquisar);
		cout<<"Prontuario: "<<procurado->prontuario<<" - Nome: "<<procurado->nome<<" - Salario: R$"<<procurado->salario<<endl;
		}
		else
		{
		cout<<"Necessario cadastrar um funcionario primeiro!"<<endl;	
		}
		break;
	
	case 4://Listando todos os funcionarios
		if(pront>0){
		cout<<endl<<"Lista dos funcionarios ativos."<<endl;
		print(ficha);
		}
		else
		{
		cout<<"Necessario cadastrar um funcionario primeiro!"<<endl;	
		}
		break;
	}	
	}
	
	freeList(ficha);//Liberando memoria
	return 0;
}