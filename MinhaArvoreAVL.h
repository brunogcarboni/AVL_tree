#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    ~MinhaArvoreAVL()
    {
        destrutor(this->raiz);
        this->raiz = nullptr;
    }

    virtual void destrutor(Nodo<T>* raiz)
    {
        if (raiz != nullptr)
        {
            destrutor(raiz->filhoEsquerda);
            destrutor(raiz->filhoDireita);  

            delete raiz;   
        }
        
    }

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const
    {
        return (this->raiz == nullptr) ? true : false;
    };

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade() const
    {
        if (!vazia())
        {
            return quantidadeRec(this->raiz);
        }

        return 0;
    };

    virtual int quantidadeRec(Nodo<T> *nodo) const
    {
        if (nodo != nullptr)
        {
            return quantidadeRec(nodo->filhoEsquerda) + quantidadeRec(nodo->filhoDireita) + 1;
        }
        else
        {
            return 0;
        }
    }

    /**
     * @brief procura um nodo a partir do valor da sua chave
     * @param chave chave a ser procurada na arvore
     * @param nodo raiz da arvore/subarvore
     * @return nodo que contem a chave
     */
    virtual Nodo<T> *procuraChave(T chave, Nodo<T> *nodo) const
    {

        if (chave < nodo->chave)
        {
            if (nodo->filhoEsquerda != nullptr)
            {
                return procuraChave(chave, nodo->filhoEsquerda);
            }
            else
            {
                return nullptr;
            }
        }

        if (chave > nodo->chave)
        {
            if (nodo->filhoDireita != nullptr)
            {
                return procuraChave(chave, nodo->filhoDireita);
            }
            else
            {
                return nullptr;
            }
        }

        return nodo;
    }

    /**
     * @brief procura um nodo a partir de seu filho
     * @param filho nodo filho do nodo procurado
     * @param nodo raiz da arvore/subarvore
     * @return nodo pai do nodo @param filho
     */
    virtual Nodo<T> *procuraPai(Nodo<T> *filho)
    {
        if (filho == this->raiz)
        {
            return nullptr;
        }

        Nodo<T> *pai = this->raiz;

        while (pai != nullptr)
        {
            if (filho->chave < pai->chave)
            {
                if (pai->filhoEsquerda == filho)
                {
                    return pai;
                }
                else
                {
                    pai = pai->filhoEsquerda;
                }
            }
            else if (filho->chave >= pai->chave)
            {
                if (pai->filhoDireita == filho)
                {
                    return pai;
                }
                else
                {
                    pai = pai->filhoDireita;
                }
            }
        }

        return nullptr;
    }

    /*  virtual Nodo<T>* procuraPosicao(T chave, Nodo<T>* nodo) const{

         if (chave < nodo->chave)
         {
             if (nodo->filhoEsquerda != nullptr)
             {
                 return procuraPosicao(chave, nodo->filhoEsquerda);
             }
         }

         if (chave > nodo->chave)
         {
             if (nodo->filhoDireita != nullptr)
             {
                 return procuraPosicao(chave, nodo->filhoDireita);
             }
         }

         return nodo;
     } */

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const
    {
        if (!vazia())
        {
            if (procuraChave(chave, this->raiz) != nullptr)
            {
                return true;
            }
        }

        return false;
    };

    /*  virtual bool contemRec(T chave, Nodo<T>* nodo) const{
         if (chave < nodo->chave)
         {
             if (nodo->filhoEsquerda != nullptr)
             {
                 contemRec(nodo->filhoEsquerda);
             } else {
                 return false;
             }
         }

         if (chave > nodo->chave)
         {
             if (nodo->filhoDireita != nullptr)
             {
                 contemRec(nodo->filhoDireita);
             } else {
                 return false;
             }
         }

         return true;


     } */

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const
    {
        if (!vazia())
        {
            Nodo<T> *nodo = procuraChave(chave, this->raiz);
            if (nodo != nullptr)
            {
                return nodo->altura;
            }
            else
            {
                return std::nullopt;
            }
        }

        return std::nullopt;
    };

    /* virtual std::optional<int> alturaRec(T chave, Nodo<T>* nodo) const{
        if (chave < nodo->chave)
        {
            if (nodo->filhoEsquerda =! nullptr)
            {
                alturaRec(chave ,nodo->filhoEsquerda);
            } else {
                return std::nullopt;
            }
        }

        if (chave > nodo->chave)
        {
            if (nodo->filhoDireita =! nullptr)
            {
                alturaRec(chave, nodo->filhoDireita);
            } else {
                return std::nullopt;
            }
        }

        return nodo->altura;
    } */

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave)
    {

        if (!vazia())
        {
            inserirRec(chave, this->raiz);
        }
        else
        {
            this->raiz = new Nodo<T>;
            this->raiz->chave = chave;
        }
    };

    /**
     * @brief procura recursivamente um nodo folha correpondete a uma chave e aloca um novo nodo na folha
     * @param chave chave a ser inserida
     * @param nodo nodo atualmente visitado, inicialmente a raiz da arvore/subarvore
    */
    virtual void inserirRec(T chave, Nodo<T> *nodo)
    {

        if (chave < nodo->chave)
        {
            if (nodo->filhoEsquerda != nullptr)
            {
                inserirRec(chave, nodo->filhoEsquerda);
            }
            else
            {
                Nodo<T> *novo_nodo = new Nodo<T>;
                novo_nodo->chave = chave;
                nodo->filhoEsquerda = novo_nodo;
            }
        }
        else if (chave >= nodo->chave)
        {
            if (nodo->filhoDireita != nullptr)
            {
                inserirRec(chave, nodo->filhoDireita);
            }
            else
            {
                Nodo<T> *novo_nodo = new Nodo<T>;
                novo_nodo->chave = chave;
                nodo->filhoDireita = novo_nodo;
            }
        }

        ajustaAltura(nodo);
        verificaRotacao(nodo);
    }

    /**
     * @brief ajusta a altura de um nodo
     * @param nodo nodo a ter a altura ajustada
    */
    virtual void ajustaAltura(Nodo<T> *nodo)
    {
        if (nodo != nullptr)
        {
            if (nodo->filhoEsquerda && nodo->filhoDireita)
            {

                nodo->altura = std::max(nodo->filhoEsquerda->altura, nodo->filhoDireita->altura) + 1;
            }
            else if (!nodo->filhoEsquerda && nodo->filhoDireita)
            {

                nodo->altura = std::max(nodo->filhoDireita->altura, -1) + 1;
            }
            else if (nodo->filhoEsquerda && !nodo->filhoDireita)
            {

                nodo->altura = std::max(nodo->filhoEsquerda->altura, -1) + 1;
            }
            else
            {

                nodo->altura = 0;
            }
        }
    };

    /**
     * @brief verifica a necessidade de rotacao a partir de um nodo dado
     * @param nodo nodo o qual se baseara a rotacao
    */
    virtual void verificaRotacao(Nodo<T> *nodo)
    {

        if (nodo != nullptr)
        {
            int fb_nodo = fatorDeBalanceamento(nodo);

            if (fb_nodo < -1 || fb_nodo > 1)
            {
                int fb_esquerda = fatorDeBalanceamento(nodo->filhoEsquerda);
                int fb_direita = fatorDeBalanceamento(nodo->filhoDireita);

                if ((fb_direita <= 0) && nodo->filhoDireita)
                {
                    rotacaoSimplesEsquerda(nodo, procuraPai(nodo));
                }
                else if (fb_esquerda >= 0 && nodo->filhoEsquerda)
                {
                    rotacaoSimplesDireita(nodo, procuraPai(nodo));
                }
                else if (fb_esquerda < 0)
                {

                    rotacaoEsquerdaDireita(nodo, procuraPai(nodo));
                }
                else if (fb_direita > 0)
                {

                    rotacaoDireitaEsquerda(nodo, procuraPai(nodo));
                }
            }
        }
    };

    /**
     * @brief verifica o fator de balancamento de um nodo e o retorna
     * @param nodo
     * (fator de balanceamento = altura filho esquerda - altura filho direita)
    */
    virtual int fatorDeBalanceamento(Nodo<T> *nodo)
    {
        if (nodo)
        {
            if (nodo->filhoEsquerda && nodo->filhoDireita)
            {

                return nodo->filhoEsquerda->altura - nodo->filhoDireita->altura;
            }
            else if (!nodo->filhoEsquerda && nodo->filhoDireita)
            {

                return -1 - nodo->filhoDireita->altura;
            }
            else if (nodo->filhoEsquerda && !nodo->filhoDireita)
            {

                return nodo->filhoEsquerda->altura + 1;
            }

            return 0;
        }
        else
        {

            return 0;
        }
    }

    /**
     * @brief retorna o nodo antecessor
     * @param nodo nodo referencia
     * @return nodo antecessor a referenfia
     */
    /* virtual Nodo<T> *getAntecessor(Nodo<T> *nodo)
    {
        if (nodo != nullptr)
        {
            if (nodo->filhoEsquerda != nullptr)
            {
                return getMaisDireita(nodo->filhoEsquerda);
            }
        }

        return nullptr;
    } */

    /**
     * @brief retorna o nodo sucessor
     * @param nodo nodo referencia
     * @return nodo sucessor a referenfia
     */
    /* virtual Nodo<T> *getSucessor(Nodo<T> *nodo)
    {
        if (nodo)
        {
            if (nodo->filhoEsquerda)
            {
                return getMaisEsquerda(nodo->filhoDireita);
            }
        }

        return nullptr;
    } */

    /**
     * @brief procura o nodo mais a direita
     * @param nodo referencia para inicio da busca
     * @return nodo mais a direita
     */
    /* virtual Nodo<T> *getMaisDireita(Nodo<T> *nodo)
    {
        if (nodo->filhoDireita != nullptr)
        {

            return getMaisDireita(nodo->filhoDireita);
        }
        else
        {

            return nodo;
        }
    } */

    /**
     * @brief procura o nodo mais a esquerda
     * @param nodo referencia para inicio da busca
     * @return nodo mais a esquerda
     */
    /* virtual Nodo<T> *getMaisEsquerda(Nodo<T> *nodo)
    {
        if (nodo->filhoEsquerda != nullptr)
        {
            return getMaisEsquerda(nodo->filhoEsquerda);
        }
        else
        {

            return nodo;
        }
    } */

    /**
     * @brief realiza uma rotação simples à direita
     * @param nodo_base nodo desbalanceado
     * @param pai_nodo_base pai do nodo desbalanceado
    */
    virtual void rotacaoSimplesDireita(Nodo<T> *nodo_base, Nodo<T> *pai_nodo_base)
    {

        Nodo<T> *filho_esquerda = nodo_base->filhoEsquerda;

        nodo_base->filhoEsquerda = filho_esquerda->filhoDireita;
        filho_esquerda->filhoDireita = nodo_base;

        if (pai_nodo_base != nullptr)
        {
            if (nodo_base->chave < pai_nodo_base->chave)
            {
                pai_nodo_base->filhoEsquerda = filho_esquerda;
            }
            else
            {

                pai_nodo_base->filhoDireita = filho_esquerda;
            }
        }
        else
        {

            this->raiz = filho_esquerda;
        }

        ajustaAltura(nodo_base);
        ajustaAltura(filho_esquerda);
    };

    /**
     * @brief realiza uma rotação simples à esquerda
     * @param nodo_base nodo desbalanceado
     * @param pai_nodo_base pai do nodo desbalanceado
    */
    virtual void rotacaoSimplesEsquerda(Nodo<T> *nodo_base, Nodo<T> *pai_nodo_base)
    {

        Nodo<T> *filho_direita = nodo_base->filhoDireita;

        nodo_base->filhoDireita = filho_direita->filhoEsquerda;
        filho_direita->filhoEsquerda = nodo_base;

        if (pai_nodo_base != nullptr)
        {
            if (nodo_base->chave < pai_nodo_base->chave)
            {
                pai_nodo_base->filhoEsquerda = filho_direita;
            }
            else
            {

                pai_nodo_base->filhoDireita = filho_direita;
            }
        }
        else
        {
            this->raiz = filho_direita;
        }

        ajustaAltura(nodo_base);
        ajustaAltura(filho_direita);
    };

    /**
     * @brief realiza uma rotação direta-esquerda
     * @param nodo_base nodo desbalanceado
     * @param pai_nodo_base pai do nodo desbalanceado
    */
    virtual void rotacaoDireitaEsquerda(Nodo<T> *nodo_base, Nodo<T> *pai_nodo_base)
    {

        Nodo<T> *direita_esquerda = nodo_base->filhoDireita->filhoEsquerda;

        nodo_base->filhoDireita->filhoEsquerda = direita_esquerda->filhoDireita;
        direita_esquerda->filhoDireita = nodo_base->filhoDireita;
        nodo_base->filhoDireita = direita_esquerda;

        nodo_base->filhoDireita = direita_esquerda->filhoEsquerda;
        direita_esquerda->filhoEsquerda = nodo_base;

        ajustaAltura(nodo_base);
        ajustaAltura(direita_esquerda->filhoDireita);
        ajustaAltura(direita_esquerda);

        if (pai_nodo_base != nullptr)
        {
            if (nodo_base->chave < pai_nodo_base->chave)
            {

                pai_nodo_base->filhoEsquerda = direita_esquerda;
            }
            else
            {

                pai_nodo_base->filhoDireita = direita_esquerda;
            }
        }
        else
        {
            this->raiz = direita_esquerda;
        }
    };

    /**
     * @brief realiza uma rotação esquerda-direita
     * @param nodo_base nodo desbalanceado
     * @param pai_nodo_base pai do nodo desbalanceado
    */
    virtual void rotacaoEsquerdaDireita(Nodo<T> *nodo_base, Nodo<T> *pai_nodo_base)
    {

        Nodo<T> *esquerda_direita = nodo_base->filhoEsquerda->filhoDireita;

        nodo_base->filhoEsquerda->filhoDireita = esquerda_direita->filhoEsquerda;
        esquerda_direita->filhoEsquerda = nodo_base->filhoEsquerda;
        nodo_base->filhoEsquerda = esquerda_direita;

        nodo_base->filhoEsquerda = esquerda_direita->filhoDireita;
        esquerda_direita->filhoDireita = nodo_base;

        ajustaAltura(nodo_base);
        ajustaAltura(esquerda_direita->filhoEsquerda);
        ajustaAltura(esquerda_direita);

        if (pai_nodo_base != nullptr)
        {
            if (nodo_base->chave < pai_nodo_base->chave)
            {

                pai_nodo_base->filhoEsquerda = esquerda_direita;
            }
            else
            {

                pai_nodo_base->filhoDireita = esquerda_direita;
            }
        }
        else
        {
            this->raiz = esquerda_direita;
        }
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a ser removida
     */
    virtual void remover(T chave)
    {

        if (contem(chave))
        {
            removerRec(chave, this->raiz);
        }
    };

    /**
     * @brief procura recursivamente um nodo e entao o remove
     * @param chave chave que o nodo a ser removido possui
     * @param raiz nodo atualmente visitia, inicialmente a raiz da arvore/subarvore
    */
    virtual void removerRec(T chave, Nodo<T> *raiz)
    {
        if (raiz != nullptr)
        {

            if (chave < raiz->chave)
            {
                if (raiz->filhoEsquerda != nullptr)
                {

                    removerRec(chave, raiz->filhoEsquerda);
                }
            }
            else if (chave > raiz->chave)
            {
                if (raiz->filhoDireita != nullptr)
                {

                    removerRec(chave, raiz->filhoDireita); 
                }
            } 
            else 
            {
                return avaliaRemocao(raiz);
                
            }
        }

        ajustaAltura(raiz);
        verificaRotacao(raiz);
    }

    /**
     * @brief define o estado da remoção e realiza a remocao mais adequada
     * @param raiz nodo a ser avaliado e removido
    */
    virtual void avaliaRemocao(Nodo<T>* raiz)
    {
        if (raiz != nullptr)
        {   
            if (raiz->filhoEsquerda != nullptr && raiz->filhoDireita != nullptr)
            {
                if (raiz->filhoDireita->filhoEsquerda == nullptr)
                {

                    if (raiz != this->raiz)
                    {
                        Nodo<T>* pai_raiz = procuraPai(raiz);

                        if (pai_raiz->filhoEsquerda = raiz)
                        {

                            pai_raiz->filhoEsquerda = raiz->filhoDireita;
                        }
                        else
                        {

                            pai_raiz->filhoDireita = raiz->filhoDireita;
                        }

                        raiz->filhoDireita->filhoEsquerda = raiz->filhoEsquerda;

                        ajustaAltura(raiz->filhoEsquerda);
                        ajustaAltura(pai_raiz);

                        delete raiz;

                    } else {
                        
                        raiz->filhoDireita->filhoEsquerda = raiz->filhoEsquerda;

                        ajustaAltura(raiz->filhoDireita);
                        this->raiz = raiz->filhoDireita;

                        delete raiz;
                    }
                }
                else
                {

                    inverteSucessor(raiz);
                }
                
            }
            else if (raiz->filhoEsquerda != nullptr && raiz->filhoDireita == nullptr)
            {
                
                if(raiz != this->raiz)
                {
                    Nodo<T>* pai_raiz = procuraPai(raiz);

                    if (pai_raiz->filhoEsquerda = raiz)
                    {

                        pai_raiz->filhoEsquerda = raiz->filhoEsquerda;
                    }
                    else
                    {

                        pai_raiz->filhoDireita = raiz->filhoEsquerda;
                    }

                    ajustaAltura(pai_raiz);

                    delete raiz;
                }
                else
                {
                    this->raiz = raiz->filhoEsquerda;
                    delete raiz;
                }

                
            }
            else if (raiz->filhoEsquerda == nullptr & raiz->filhoDireita != nullptr)
            {

                if (raiz->filhoDireita->filhoEsquerda == nullptr)
                {
                    
                    if (raiz != this->raiz)
                    {
                        Nodo<T>* pai_raiz = procuraPai(raiz);

                        if (pai_raiz->filhoEsquerda = raiz)
                        {

                            pai_raiz->filhoEsquerda = raiz->filhoDireita;
                        }
                        else
                        {

                            pai_raiz->filhoDireita = raiz->filhoDireita;
                        }

                        raiz->filhoDireita->filhoDireita = raiz->filhoEsquerda;

                        ajustaAltura(raiz->filhoEsquerda);
                        ajustaAltura(pai_raiz);

                        delete raiz;
                    }
                    else
                    {
                        //raiz->filhoDireita->filhoDireita = raiz->filhoEsquerda;

                        ajustaAltura(raiz->filhoEsquerda);
                        this->raiz = raiz->filhoEsquerda;

                        delete raiz;
                    }
                }
                else
                {

                    inverteSucessor(raiz);
                }
            }
            else
            {
                if (raiz != this->raiz)
                {
                    Nodo<T>* pai_raiz = procuraPai(raiz);

                    if (pai_raiz->filhoEsquerda == raiz)
                    {

                        delete raiz;
                        pai_raiz->filhoEsquerda = nullptr;
                    }
                    else
                    {
                        
                        delete raiz;
                        pai_raiz->filhoDireita = nullptr;
                    }

                    ajustaAltura(pai_raiz);
                } else {

                    delete raiz;
                    this->raiz = nullptr;
                    
                }
            }            
        }
    }

    /**
     * @brief inverte a chave de um nodo com seu sucessor e remove o sucessor
     * @param raiz nodo que recebera nova chave
    */
    virtual void inverteSucessor(Nodo<T>* raiz)
    {
        inverteSucessorRec(raiz->filhoDireita, raiz);
    }

    virtual void inverteSucessorRec(Nodo<T>* nodo, Nodo<T>* raiz)
    {
        if (nodo->filhoEsquerda != nullptr)
        {
            inverteSucessorRec(nodo->filhoEsquerda, raiz);
        }
        else
        {
            raiz->chave = nodo->chave;
            return avaliaRemocao(nodo);
        }
        
        ajustaAltura(nodo);
        verificaRotacao(nodo);
    }

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        if (!vazia())
        {
            Nodo<T> *nodo = procuraChave(chave, this->raiz);

            if (nodo != nullptr)
            {
                if (nodo->filhoEsquerda != nullptr)
                {

                    return nodo->filhoEsquerda->chave;
                }
                else
                {

                    return std::nullopt;
                }
            }
        }

        return std::nullopt;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        if (!vazia())
        {
            Nodo<T> *nodo = procuraChave(chave, this->raiz);

            if (nodo != nullptr)
            {

                if (nodo->filhoDireita != nullptr)
                {

                    return nodo->filhoDireita->chave;
                }
            }
        }

        return std::nullopt;
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {

        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;

        if (!vazia())
        {
            return emOrdemRec(this->raiz, lista);
        }

        return lista;
    };

    /**
     * @brief trabalha em conjunto com a função emOrdem()
    */
    virtual ListaEncadeadaAbstrata<T> *emOrdemRec(Nodo<T> *raiz, ListaEncadeadaAbstrata<T> *lista) const
    {

        if (raiz->filhoEsquerda != nullptr)
        {
            lista = emOrdemRec(raiz->filhoEsquerda, lista);
        }

        lista->inserirNoFim(raiz->chave);

        if (raiz->filhoDireita != nullptr)
        {
            lista = emOrdemRec(raiz->filhoDireita, lista);
        }

        return lista;
    }

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {

        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;

        if (!vazia())
        {
            return preOrdemRec(this->raiz, lista);
        }

        return lista;
    };

    /**
     * @brief trabalha em conjunto com a função preOrdem()
    */
    virtual ListaEncadeadaAbstrata<T> *preOrdemRec(Nodo<T> *raiz, ListaEncadeadaAbstrata<T> *lista) const
    {
        lista->inserirNoFim(raiz->chave);

        if (raiz->filhoEsquerda != nullptr)
        {
            lista = preOrdemRec(raiz->filhoEsquerda, lista);
        }

        if (raiz->filhoDireita != nullptr)
        {
            lista = preOrdemRec(raiz->filhoDireita, lista);
        }

        return lista;
    }

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {

        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;

        if (!vazia())
        {
            return posOrdemRec(this->raiz, lista);
        }

        return lista;
    };

    /**
     * @brief trabalha em conjunto com a função posOrdem()
    */
    virtual ListaEncadeadaAbstrata<T> *posOrdemRec(Nodo<T> *raiz, ListaEncadeadaAbstrata<T> *lista) const
    {

        if (raiz->filhoEsquerda != nullptr)
        {
            lista = posOrdemRec(raiz->filhoEsquerda, lista);
        }

        if (raiz->filhoDireita != nullptr)
        {
            lista = posOrdemRec(raiz->filhoDireita, lista);
        }

        lista->inserirNoFim(raiz->chave);

        return lista;
    }
};

#endif