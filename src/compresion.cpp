
#include <iostream>
#include <map>
#include <memory>
#include <algorithm>
#include <vector>
#include <queue>
// #include <boost/dynamic_bitset.hpp>

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
    std::shared_ptr<nodo_arbol_huffman>  hijo_i;
    std::shared_ptr<nodo_arbol_huffman>  hijo_d;
	std::string codigo;

    nodo_arbol_huffman() {}

    nodo_arbol_huffman(char valor) {
        this->valor = valor;
    }

    void prt() {
        std::cout << "'" << this->valor << "'";
		std::cout << std::endl;
    }
};

class Arbol_huffman {

    // nodo inicial del arbol
	std::shared_ptr<nodo_arbol_huffman> raiz;

public:
    Arbol_huffman(std::string cadena) {

        // tendencia de cada caracter
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

        std::queue<std::shared_ptr<nodo_arbol_huffman>> pointer_q;

		this->raiz = std::make_shared<nodo_arbol_huffman>();
        pointer_q.push(this->raiz);

		// TODO: agregar los codigos o crear una funcion para que los consiga
        for(std::pair<char, int> p : elems) {

            std::shared_ptr<nodo_arbol_huffman> nah = pointer_q.front();
				// = std::make_shared<nodo_arbol_huffman>();

            *nah = nodo_arbol_huffman(p.first);

			// TODO: esto se deberia crear de otra forma, para evitar que queden datos vacios
            nah->hijo_i = std::make_shared<nodo_arbol_huffman>();
            nah->hijo_d = std::make_shared<nodo_arbol_huffman>();

            pointer_q.push(nah->hijo_i);
            pointer_q.push(nah->hijo_d);
            pointer_q.pop();
        }

		// TODO: de momento se estan limpiando los valores que hayan quedado vacios
		// quitar esto cuando se arregle lo otro
		limpiar();
    }

	void limpiar() {
		_limpiar(this->raiz);
	}

	void _limpiar(std::shared_ptr<nodo_arbol_huffman> nah) {
        if (nah->hijo_i != NULL) {
			if(nah->hijo_i->valor == 0) {
				nah->hijo_i = nullptr;
			} else {
				_limpiar(nah->hijo_i);
			}
		}
        if (nah->hijo_d != NULL) {
			if(nah->hijo_d->valor == 0) {
				nah->hijo_d = nullptr;
			} else {
				_limpiar(nah->hijo_d);
			}
		}
	}

    void imprimirPreOrden() {
        _imprimirPreOrden(std::shared_ptr<nodo_arbol_huffman>(this->raiz), 0);
    }

    void _imprimirPreOrden(std::shared_ptr<nodo_arbol_huffman> nah, int depth) {

		for (int a = 0 ; a < depth ; a++) {
			std::cout << "|  ";
		}
        nah->prt();

        if (nah->hijo_i != NULL)
            _imprimirPreOrden(nah->hijo_i, depth + 1);
        if (nah->hijo_d != NULL)
            _imprimirPreOrden(nah->hijo_d, depth + 1);
    }

	std::vector<bool> comprimir(std::string cadena) {
		std::vector<bool> bits;

		for(char c : cadena) {

		}

		return bits;
	}
};

using std::cout;

void prueba () {

	std::queue<std::shared_ptr<nodo_arbol_huffman>> q;

	std::shared_ptr<nodo_arbol_huffman> raiz = std::make_shared<nodo_arbol_huffman>();

	// raiz = new nodo_arbol_huffman('1');

	q.push(raiz);
	std::shared_ptr<nodo_arbol_huffman> rr = q.front() ;

	*rr = nodo_arbol_huffman('1');

	std::cout << "raiz  \t:" << raiz << std::endl;
	raiz->prt();

}

int main() {

	// prueba(); return 0;

	std::string cadenas[] = {
        "hola que hace"
        // , "algÈÞesoµ½esto×"
    };

    // std::cout << sizeof(char) << std::endl;

	std::cout << sizeof(new nodo_arbol_huffman(0)) << std::endl;

    for (std::string c : cadenas)
    {
		std::cout<< c << std::endl;
        Arbol_huffman ah(c);
        ah.imprimirPreOrden();
        // ah.prtTendencia();
        cout << std::endl << std::endl;
    }

    return 0;
}
