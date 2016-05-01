#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

int main(int argc, char* argv[])
{
	/* String temporária que lerá os arquivos. */
	char temp;
    std::string TokenStackNOT[100]; // Talvez nem seja Stack, tem mais cara de lista ou vector

	std::string fileName = "test.txt";

	/* Avisa para o usuário que o arquivo será lido.*/
	std::cout << ">>> Preparing to read bet file [" << fileName << "], please wait...\n";

	/* Abre o arquivo como somente leitura. */
	std::ifstream file( fileName );

	/* Retorna falso se o arquivo não for encontrado. */
	if( !file.is_open() ){
        std::cout << "Falha na abertura" << "\n";
    	return EXIT_FAILURE;
    }

    // Converte de char pra int e depois pra string, dá pra melhorar
    // ^ Tá fazendo com essa variável numberCombo e é simplesmente enojante
    // Usando arranjo e i como contador (simplesmente terrível)
	while ( !file.eof() ){
        int tempNumber;
        bool numberCombo = 0;
        int i = 0;
        while ( temp != '\n' and !file.eof() ){
            file >> temp;
            std::cout << "Loop: " << i << "; temp = " << temp << "\n";
            if ( isdigit( temp ) ){ // Operando
                tempNumber *= 10;
                tempNumber += temp - '0'; // ASCII bit fuckery
                numberCombo++;
            }else{
                if ( numberCombo != 0 ){
                    TokenStackNOT[i] = std::to_string( tempNumber );
                    tempNumber = 0;
                    numberCombo = 0;
                    i++;
                }
            }

            if ( temp == '+' or temp == '-' or temp == 'x' ){ // Clássica gambiarra de teste
                TokenStackNOT[i] = temp;
                i++;
            }else{
                // Tratamento de erro vem aqui
            }
        }
	}

	file.close();

    std::cout << "[ ";
    for ( int i = 0; i < 100; ++i )
        if ( TokenStackNOT[i] != "" )
            std::cout << TokenStackNOT[i] << ", ";

    std::cout << "]\n";


    return 0;
}
