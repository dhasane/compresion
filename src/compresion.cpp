
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

class nodo_arbol_huffman {


public:
    char valor;
    nodo_arbol_huffman* hijo_i;
    nodo_arbol_huffman* hijo_d;
    nodo_arbol_huffman(char valor) {
        this->valor = valor;
        this->hijo_i = NULL;
        this->hijo_d = NULL;
    }
};

class Arbol_huffman {

    // arbol
    nodo_arbol_huffman* raiz;

    // tendencia de cada carater
    std::map<char, int> tendencia;

public:
    Arbol_huffman(std::string cadena) {

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

        // crear el primer nodo del arbol
        this->raiz= new nodo_arbol_huffman(elems.begin()->first);

        elems.erase(elems.begin());

        std::queue<nodo_arbol_huffman*> ptrs;

        ptrs.push(this->raiz->hijo_i);
        ptrs.push(this->raiz->hijo_d);

        std::cout << &this->raiz << std::endl;

        for (std::pair<char, int> p : elems) {
            std::cout << p.first << " " << p.second << std::endl;
            // aqui agregar los valores de manera organizada al arbol
            nodo_arbol_huffman nah(p.first);
            ptrs.front();
            std::cout << &nah << " -> " << &nah.hijo_i << " " << &nah.hijo_d << std::endl;
            ptrs.push(nah.hijo_i);
            ptrs.push(nah.hijo_d);

            nodo_arbol_huffman* pnah = ptrs.front();
            std::cout<< &ptrs.front() << std::endl;
            std::cout<< &pnah << std::endl;
            pnah = &nah;
            ptrs.pop();
        }
    }

    void recorrerPre() {
        std::cout<< this->raiz->valor << std::endl;
        _recorrerPre(this->raiz);
    }

    void _recorrerPre(nodo_arbol_huffman* nah) {
        std::cout<< nah->valor << std::endl;

        if (nah->hijo_i != NULL)
            _recorrerPre(nah->hijo_i);
        if (nah->hijo_d != NULL)
            _recorrerPre(nah->hijo_d);
    }

    void prtTendencia () {
        for (std::pair<char, int> p : tendencia) {
            std::cout << "'" << p.first << "' " << p.second << std::endl;
        }
    }

};

using std::cout;

int main() {
    std::string cadenas[] = {
        "hola que hace",
        "algÈÞesoµ½esto×"

    };

    for (std::string c : cadenas)
    {
        Arbol_huffman ah(c);
        ah.recorrerPre();
        // ah.prtTendencia();
        cout << std::endl << std::endl;
    }

    return 0;
}
