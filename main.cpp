#include <iostream>
#include <locale.h>
#include <math.h>

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

    void addFilha(int _info)
    {
        //esquerda
        if(_info < info)
        {
            if(fe==NULL)
                fe = new No(_info);
            else
                fe->addFilha(_info);
        }
        //direita
        else if(info < _info)
        {
            if(fd==NULL)
                fd = new No(_info);
            else
                fd->addFilha(_info);
        }
    }

    void imprime()
    {
        cout << "Nó: " << this->getInfo();
        this->getFE() != NULL ? (cout << " FE: " << (this->getFE())->getInfo()) : (cout << " FE: -1 ");
        this->getFD() != NULL ? (cout << " FD: " << (this->getFD())->getInfo()) : (cout << " FD: -1 ");
        cout << endl;

        if(fe!=NULL)
            fe->imprime();
        //cout << info << endl;
        if(fd!=NULL)
            fd->imprime();
    }
    int getInfo()
    {
        return info;
    }
};

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
    No *arvore = new No(25);
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
    arvore->imprime();
    cout << endl;
    imprimeArvorePorNiveis(&arvore);
    delete arvore;

    return 0;
}
