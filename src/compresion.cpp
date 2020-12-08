
#include <iostream>
#include <map>
#include <memory>
#include <algorithm>
#include <vector>
#include <queue>
#include <bitset>
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
	int tendencia;

    nodo_arbol_huffman(char valor, int tendencia) {
        this->valor = valor;
		this->tendencia = tendencia;
		this->hijo_i = nullptr;
		this->hijo_d = nullptr;
	}

    nodo_arbol_huffman(nodo_arbol_huffman &nah1, nodo_arbol_huffman &nah2) {
        this->valor = 0;
		this->tendencia = nah1.tendencia + nah2.tendencia;
		this->hijo_i = std::make_shared<nodo_arbol_huffman>(nah1);
		this->hijo_d = std::make_shared<nodo_arbol_huffman>(nah2);
	}

    void prt() {
        std::cout << "'" << this->valor << "' :" << this->tendencia << std::endl;
    }

	friend bool operator>(const nodo_arbol_huffman &nah, const nodo_arbol_huffman &nah2) {
		return nah.tendencia > nah2.tendencia;
	}

	friend bool operator<(const nodo_arbol_huffman &nah, const nodo_arbol_huffman &nah2) {
		return nah.tendencia < nah2.tendencia;
	}
};

class Arbol_huffman {

    // nodo inicial del arbol
	std::shared_ptr<nodo_arbol_huffman> raiz;
    std::map<char, std::string> simbolos;

public:
    Arbol_huffman(std::string cadena) {

        // tendencia de cada caracter
        std::map<char, int> tendencia;


        for (char c : cadena) {
            tendencia[c] ? tendencia[c]++ : tendencia[c] = 1;
        }

		std::priority_queue<
			nodo_arbol_huffman,
			std::vector<nodo_arbol_huffman>,
			std::greater< nodo_arbol_huffman>> cp ;

		for (std::pair<char, int> v : tendencia) {
			cp.push(nodo_arbol_huffman(v.first, v.second));
		}

		while (cp.size() > 1) {
			nodo_arbol_huffman nah = cp.top();
			cp.pop();
			nodo_arbol_huffman nah2 = cp.top();
			cp.pop();
			cp.push(nodo_arbol_huffman(nah, nah2));
		}

		nodo_arbol_huffman nah = cp.top();
		cp.pop();

		this->raiz = std::make_shared<nodo_arbol_huffman>(nah);
    }

	void conseguirCodigos() {
		_conseguirCodigos(this->raiz, "1");

		// for (std::pair<char, std::string> v : this->simbolos) {
		// 	std::cout << v.first << "->" << v.second << std::endl;
		// }

	}

	void _conseguirCodigos(std::shared_ptr<nodo_arbol_huffman> nah, std::string codigo) {
        this->simbolos[nah->valor] = codigo;
        if (nah->hijo_i != NULL) {
			_conseguirCodigos(nah->hijo_i, codigo + "1");
		}
        if (nah->hijo_d != NULL) {
			_conseguirCodigos(nah->hijo_d, codigo + "0");
		}
	}

	std::string descomprimir(std::string binCodigo) {
		std::string codigo = "";
		for (char c : binCodigo)
		{
			std::bitset<8> btc(c);
			codigo += btc.to_string();
		}
		std::string desc = "";
		int posicion = 0;
		while(codigo.length() > posicion && codigo[posicion] != '0')
		{
			posicion ++;
			desc += _descomprimir(
				this->raiz,
				codigo.substr(posicion),
				posicion
				);
		}

		return desc;
	}

	char _descomprimir(std::shared_ptr<nodo_arbol_huffman> nah,
					   std::string codigo,
					   int &posicion
		) {
		char respuesta = 0;

		if (codigo[0] == '1'){
			if (nah->hijo_i != NULL) {
				posicion ++;
				respuesta = _descomprimir(nah->hijo_i, codigo.substr(1), posicion);
			} else {
				respuesta = nah->valor;
			}
		} else {
			if (nah->hijo_d != NULL) {
				posicion ++;
				respuesta = _descomprimir(nah->hijo_d, codigo.substr(1), posicion);
			} else {
				respuesta = nah->valor;
			}
		}

		return respuesta;
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

	std::string comprimir(std::string cadena) {
		this->conseguirCodigos();
		std::string binString = "";
		std::string ret = "";

		for(char c : cadena) {
			binString += this->simbolos[c];
		}

		int faltante = binString.length() % 8;

		for(int a = 0 ; a < faltante ; a++)
		{
			binString += "0";
		}

		for (int a = 0 ; a < binString.length() ; a+=8)
		{
			std::bitset<8> btc(binString.substr(a, a+8));
			ret += (char)btc.to_ulong();
		}
		return ret;
	}
};

using std::cout;

int main() {

	// prueba(); return 0;

	std::string cadenas[] = {
        "hola que hace"
        , "algÈÞesoµ½esto×"
		, "abcdefghijklmnopqrstuvwxyz"
    };

    for (std::string c : cadenas)
    {
        std::cout << c << std::endl;
        Arbol_huffman ah(c);
        // ah.imprimirPreOrden();

		std::string bla = ah.comprimir(c);
		std::cout << bla << std::endl;
		// std::cout << bla.length()% 8 << std::endl;

		std::cout << ">" << ah.descomprimir(bla) << "<" << std::endl;
        // ah.prtTendencia();
        cout << std::endl << std::endl;
    }

    return 0;
}
