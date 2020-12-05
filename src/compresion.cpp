
#include <iostream>
#include <map>
#include <memory>
#include <algorithm>
#include <vector>
#include <queue>

/*
Begin
   define a node with character, frequency, left and right child of the node for Huffman tree.
   create a list ‘freq’ to store frequency of each character, initially, all are 0
   for each character c in the string do
      increase the frequency for character ch in freq list.
   done

   for all type of character ch do
      if the frequency of ch is non zero then
         add ch and its frequency as a node of priority queue Q.
   done

   while Q is not empty do
      remove item from Q and assign it to left child of node
      remove item from Q and assign to the right child of node
      traverse the node to find the assigned code
   done
End
*/

struct nodo_arbol_huffman {
    char valor;
    std::shared_ptr<nodo_arbol_huffman>  hijo_i;
    std::shared_ptr<nodo_arbol_huffman>  hijo_d;

    nodo_arbol_huffman(char valor) {
        this->valor = valor;
        this->hijo_i = NULL;
        this->hijo_d = NULL;
    }

    void prt() {
        std::cout << "'" << this->valor << "'";
        if (this->hijo_i == NULL)
        {
            std::cout << "  i:" << this->hijo_i;
        }
        if (this->hijo_i == NULL)
        {
            std::cout << ", d:" << this->hijo_d;
        }
        std::cout << std::endl;
    }
};

class Arbol_huffman {

    // nodo inicial del arbol
    std::shared_ptr<nodo_arbol_huffman> raiz;

public:
    Arbol_huffman(std::string cadena) {

        this->raiz = NULL;

        // tendencia de cada carater
        std::map<char, int> tendencia;

        std::cout << cadena << std::endl;

        for (char c : cadena) {
            tendencia[c] ? tendencia[c]++ : tendencia[c] = 1;
        }

        std::vector<std::pair<char, int>> elems(tendencia.begin(), tendencia.end());

        std::sort(elems.begin(), elems.end(),
                  [](std::pair<char, int> elem1,
                     std::pair<char, int> elem2) {
                    return elem1.second > elem2.second;
                  }
            );

        // std::queue<nodo_arbol_huffman*>

        // TODO: los apuntadores dentro del queue no estan apuntando a los elementos originales fuera del queue
        std::queue<std::shared_ptr<nodo_arbol_huffman>>
            pointer_q;

        pointer_q.push(this->raiz);

        std::cout << &this->raiz << std::endl;

        for(std::pair<char, int> p : elems) {
            std::shared_ptr<nodo_arbol_huffman> nah = pointer_q.front();
            nodo_arbol_huffman nn(p.first);
            nah = std::make_shared<nodo_arbol_huffman>(nn);

            pointer_q.push(nah->hijo_i);
            pointer_q.push(nah->hijo_d);
            pointer_q.pop();
        }
    }

    void recorrerPre() {
        std::cout<< this->raiz->valor << std::endl;
        _recorrerPre(this->raiz);
    }

    void _recorrerPre(std::shared_ptr<nodo_arbol_huffman> nah) {
        nah->prt();

        if (nah->hijo_i != NULL)
            _recorrerPre(nah->hijo_i);
        if (nah->hijo_d != NULL)
            _recorrerPre(nah->hijo_d);
    }

    // void prtTendencia () {
    //     for (std::pair<char, int> p : tendencia) {
    //         std::cout << "'" << p.first << "' " << p.second << std::endl;
    //     }
    // }

};

using std::cout;

int main() {
    std::string cadenas[] = {
        "hola que hace",
        // "algÈÞesoµ½esto×"
    };

    // std::cout << sizeof(char) << std::endl;

    for (std::string c : cadenas)
    {
        Arbol_huffman ah(c);
        ah.recorrerPre();
        // ah.prtTendencia();
        cout << std::endl << std::endl;
    }

    return 0;
}
