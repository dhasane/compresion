
#include <iostream>
#include <map>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <vector>
#include <queue>
#include <bitset>

class nodo_arbol_huffman {
public:
    char valor;
    std::shared_ptr<nodo_arbol_huffman>  hijo_i;
    std::shared_ptr<nodo_arbol_huffman>  hijo_d;
	int tendencia;

    nodo_arbol_huffman(char valor, int tendencia);

    nodo_arbol_huffman(nodo_arbol_huffman &nah1, nodo_arbol_huffman &nah2);

    void prt();

    friend bool operator>(const nodo_arbol_huffman &nah,
                          const nodo_arbol_huffman &nah2) {
        return nah.tendencia > nah2.tendencia;
    }

    friend bool operator<(const nodo_arbol_huffman &nah,
                          const nodo_arbol_huffman &nah2) {
        return nah.tendencia < nah2.tendencia;
    }
};

class Arbol_huffman {

    // nodo inicial del arbol
	std::shared_ptr<nodo_arbol_huffman> raiz;
    std::map<char, std::string> simbolos;

public:
    Arbol_huffman(std::string cadena);

	void conseguirCodigos();

	void _conseguirCodigos(std::shared_ptr<nodo_arbol_huffman> nah, std::string codigo);

	std::string descomprimir(std::string binCodigo);

	char _descomprimir(std::shared_ptr<nodo_arbol_huffman> nah,
					   std::string codigo,
					   int &posicion
		);

	void imprimirPreOrden();

    void _imprimirPreOrden(std::shared_ptr<nodo_arbol_huffman> nah, int depth);

	std::string comprimir(std::string cadena);
};
