#include <iostream>
#include <cstdlib>
#include <locale.h>
#include <limits>
#include <math.h>

#define LINUX 1

using namespace std;

class No
{
    No* fe, *fd;
    int info;
public:
    No(int _info)
    {
        fe = NULL;
        fd = NULL;
        info = _info;
    }
    ~No()
    {
        //desaloca filhas
        if(fe!=NULL)
            delete fe;
        if(fd!=NULL)
            delete fd;
    }

    No* getFE()
    {
        return fe;
    }

    No* getFD()
    {
        return fd;
    }

    //deleta nó de informação _info, returna 1 se bem sucedido e -1 se for folha e 0 para não existe
    int deleteNo(int _info)
    {
        //sou o nó a ser deletado
        if(_info==info)
        {
            //se filha fe existir
            if(fe!=NULL)
            {
                No* tmp_fe = fe;
                No* tmp_fd = fd;
                //nó atual passa a ser a filha fe
                info = tmp_fe->getInfo();
                fe = tmp_fe->getFE();
                fd = tmp_fe->getFD();
                //retira as filhas de fe e a deleta
                tmp_fe->fd = NULL;
                tmp_fe->fe = NULL;
                delete tmp_fe;
                //adiciona a filha da direita se existir
                if(tmp_fd!=NULL)
                    addFilha(tmp_fd);
                return 1;
            }
            //se somente a filha fd existir
            else if(fd!=NULL)
            {
                No* tmp_fd = fd;
                //nó atual passa a ser a filha fd
                info = tmp_fd->getInfo();
                fe = tmp_fd->getFE();
                fd = tmp_fd->getFD();
                //retira as filhas de fd e a deleta
                tmp_fd->fd = NULL;
                tmp_fd->fe = NULL;
                delete tmp_fd;
                return 1;
            }
            //Magic!
            else
            {
                delete this;//BOOOOM!!!
                return -1;
            }
        }
        //Alguem da direita vai ser deletado
        else if(_info < info)
        {
            if(fe==NULL)
                return 0;
            int resultado;
            resultado = fe->deleteNo(_info);
            //se fe era uma folha
            if(resultado == -1)
            {
                fe = NULL;
                return 1;
            }
            else
                return resultado;
        }
        //Alguem da esquerda vai ser deletado
        else if(info < _info)
        {
            if(fd == NULL)
                return 0;
            int resultado;
            resultado = fd->deleteNo(_info);
            //se fd era uma folha
            if(resultado == -1)
            {
                fd = NULL;
                return 1;
            }
            else
                return resultado;
        }
        else
            return 0;
    }
    void addFilha(No* filha)
    {
        if(filha == NULL)
            return;
        //esquerda
        if(filha->getInfo() < info)
        {
            if(fe==NULL)
                fe = filha;
            else
                fe->addFilha(filha);
        }
        //direita
        else if(info < filha->getInfo())
        {
            if(fd==NULL)
                fd = filha;
            else
                fd->addFilha(filha);
        }
    }

    int addFilha(int _info)
    {
        //esquerda
        if(_info < info)
        {
            if(fe==NULL)
                fe = new No(_info);
            else
                return fe->addFilha(_info);
        }
        //direita
        else if(info < _info)
        {
            if(fd==NULL)
                fd = new No(_info);
            else
                return fd->addFilha(_info);
        }
        else
        {
            return 0;
        }
        return  1;
    }

    void imprime()
    {
        cout << "Nó: " << this->getInfo();
        this->getFE() != NULL ? (cout << " FE: " << (this->getFE())->getInfo()) : (cout << " FE: -1 ");
        this->getFD() != NULL ? (cout << " FD: " << (this->getFD())->getInfo()) : (cout << " FD: -1 ");
        cout << endl;

        if(fe!=NULL)
            fe->imprime();

        if(fd!=NULL)
            fd->imprime();
    }
    int getInfo()
    {
        return info;
    }
};


int lerEntrada(const char* print)
{
    int input = -1;
    bool valid= false;
    do
    {
        cout << print;
        cin >> input;
        if (cin.good())
        {
            valid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << " Entrada inválida!" << endl;
        }
    }
    while (!valid);
    return (input);
}

//imprime o menu podendo ou não imprimir as opções
void imprimeMenu(bool tudo=true)
{
    if(LINUX)
        system("clear");
    else
        system("cls");
    cout  << "   _____ _                 _        ____  _                          _______            " << endl;
    cout  << "  / ____(_)               | |      |  _ \\(_)                        |__   __|           " << endl;
    cout  << " | (___  _ _ __ ___  _ __ | | ___  | |_) |_ _ __   __ _ _ __ _   _     | |_ __ ___  ___ " << endl;
    cout  << "  \\___ \\| | '_ ` _ \\| '_ \\| |/ _ \\ |  _ <| | '_ \\ / _` | '__| | | |    | | '__/ _ \\/ _ \\" << endl;
    cout  << "  ____) | | | | | | | |_) | |  __/ | |_) | | | | | (_| | |  | |_| |    | | | |  __/  __/" << endl;
    cout  << " |_____/|_|_| |_| |_| .__/|_|\\___| |____/|_|_| |_|\\__,_|_|   \\__, |    |_|_|  \\___|\\___|" << endl;
    cout  << "                    | |                                       __/ |                     " << endl;
    cout  << "                    |_|                                      |___/                      " << endl;
    cout << "========================================================================================" << endl;

    if(tudo)
    {
        cout << " Selecione uma opção:" << endl;
        cout << "   1. Inserir nó" << endl;
        cout << "   2. Remover nó" << endl;
        cout << "   3. Imprime árvore" << endl;
        cout << "   0. Sair" << endl;
        cout << "=========================================================================================" << endl;
        cout << ">>";
    }
}


void imprimeArvorePorNiveis(No** raiz)
{
    No* atual;
    bool fim;
    int p;

    if((*raiz)==NULL)
    {
        cout << "Árvore vazia!" << endl;
    }
    else
    {
        cout << "Raiz: " << (*raiz)->getInfo();
        (*raiz)->getFE() != NULL ? (cout << " FE: " << ((*raiz)->getFE())->getInfo()) : (cout << " FE: -1 ");
        (*raiz)->getFD() != NULL ? (cout << " FD: " << ((*raiz)->getFD())->getInfo()) : (cout << " FD: -1 ");
        cout << endl;

        fim = false;

        p = 1;

        while(!fim)
        {
            fim = true;
            for(int i = 0; i < pow(2, p); i++)
            {
                atual = (*raiz);

                for(int j = p - 1; j >= 0; j--)
                {
                    if(((i >> j)&1) == 1)
                    {
                        if(atual->getFD() != NULL)
                        {
                            atual = atual->getFD();
                        }
                        else
                        {
                            atual = NULL;
                            break;
                        }
                    }
                    else
                    {
                        if(atual->getFE() != NULL)
                        {
                            atual = atual->getFE();
                        }
                        else
                        {
                            atual = NULL;
                            break;
                        }
                    }
                }

                if(atual != NULL)
                {
                    fim = false;
                    cout << "Nó: " << atual->getInfo();
                    atual->getFE() != NULL ? (cout << " FE: " << (atual->getFE())->getInfo()) : (cout << " FE: -1 ");
                    atual->getFD() != NULL ? (cout << " FD: " << (atual->getFD())->getInfo()) : (cout << " FD: -1 ");
                    cout << endl;
                }
            }
            p++;
        }
    }
}

int main()
{
    char ent;
    int res, ph;


    if(LINUX)
        setlocale(LC_ALL, "pt_BR_utf8");
    else
        setlocale(LC_ALL, "Portuguese");

    /*
                25
          20            30
      10     23      28     40
    5   15 22  24  27  29 35  43

    Raiz: 25 FE: 20 FD: 30
    Nó 20: FE: 10 FD: 23
    Nó 30: FE: 28 FD: 40
    Nó 10: FE: 5 FD: 15
    Nó 23: FE: -1 FD: -1
    Nó 28: FE: -1 FD: -1
    Nó 40: FE: -1 FD: -1
    Nó 5: FE: -1 FD:-1
    Nó 15: FE: -1 FD: -1

    */
    No *arvore = NULL;
    /*
    arvore->addFilha(20);
    arvore->addFilha(10);
    arvore->addFilha(5);
    arvore->addFilha(15);
    arvore->addFilha(23);
    arvore->addFilha(22);
    arvore->addFilha(24);
    arvore->addFilha(30);
    arvore->addFilha(28);
    arvore->addFilha(27);
    arvore->addFilha(29);
    arvore->addFilha(40);
    arvore->addFilha(35);
    arvore->addFilha(43);
    */

    while(1)
    {
        imprimeMenu();

        cin >> ent;

        switch(ent)
        {
        case '0':
            return 0;
            break;
        /// Inserir nó
        case '1':
            imprimeMenu(false);
            cout << " 1. Adicionar nó" << endl;

            if(arvore ==  NULL)
            {
                arvore = new No(lerEntrada("  Valor: "));
                cout << "  Nó adicionado!" << endl;
            }
            else
            {
                if(arvore->addFilha(lerEntrada("  Valor: ")) == 1)
                    cout << "  Nó adicionado!" << endl;
                else
                    cout << "  Nó não foi adicionado,  nó informado já faz parte da árvore!" << endl;
            }

            if(LINUX)
                system("read -p \"\nPressione enter para sair\" saindo");
            else
                system("pause");
            break;
        /// Remover nó
        case '2':
            imprimeMenu(false);
            cout << " 2. Remover nó" << endl;
            if(arvore ==  NULL)
            {
                cout << "  Árvore vazia!" <<endl;
            }
            else
            {
                res = lerEntrada("  Valor: ");
                res  = arvore->deleteNo(res);
                if(res == 1)
                    cout << "  Nó removido!" << endl;
                else  if(res == 0)
                    cout << "  Nó não foi removido,  nó informado não existe!" <<endl;
                else
                {
                    arvore = NULL;
                }
            }

            if(LINUX)
                system("read -p \"\nPressione enter para sair\" saindo");
            else
                system("pause");
            break;
        /// Imprimir árvore
        case '3':
            imprimeMenu(false);
            imprimeArvorePorNiveis(&arvore);
            if(LINUX)
                system("read -p \"\nPressione enter para sair\" saindo");
            else
                system("pause");
            break;
        /// Entrada inválida
        default:
            break;
        }
    }

    delete arvore;

    return 0;
}
