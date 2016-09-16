#include <iostream>
#include <locale.h>

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
        if(fe!=NULL)
            fe->imprime();
        cout << info << endl;
        if(fd!=NULL)
            fd->imprime();
    }
    int getInfo(){return info;}
};





int main()
{
    setlocale(LC_ALL, "Portuguese");


    No *arvore = new No(10);
    arvore->addFilha(5);
    arvore->addFilha(15);
    arvore->addFilha(2);
    arvore->addFilha(7);
    arvore->addFilha(25);
    arvore->imprime();
    delete arvore;

    //cout << "Hello world!" << endl;
    return 0;
}
