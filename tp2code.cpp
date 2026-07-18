// -- Trabalho pratico 2 --
// -- Rafael Vagner Pinto da Fonseca Souza --
// -- Programa para ler, modificar e gravar uma imagem no formato PNM --
//
// Autor Base: Andre Gustavo dos Santos			(criado em 16/06/14)
// Rafael Vagner Pinto da Fonseca Souza    (modificado em 16/05/2026)
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

const int MAXALTURA  = 2000;				//tamanho maximo de imagem aceito
const int MAXLARGURA = 2000;

using namespace std;
	unsigned char imagem[MAXALTURA][MAXLARGURA];	    //a matriz para imagem do tipo P2
	unsigned char imagemP3[MAXALTURA][MAXLARGURA][3];   //a matriz para imagem do tipo P3
	int matauxP2[MAXALTURA+2][MAXLARGURA+2];            //matriz auxiliarr pra imagens P2
	int matauxP3[MAXALTURA+2][MAXLARGURA+2][3];         //matriz auxiliar pra imagens P3
int main() {
	int largura, altura;						        //dimensoes da imagem
	char tipo[4];										//tipo da imagem
	ifstream arqentrada;						        //arquivo que contem a imagem original
	ofstream arqsaida;							        //arquivo que contera a imagem modificada
	char comentario[200], c;				            //auxiliares
	int i, j, valor, p;								    //auxiliares

//*** LEITURA DA IMAGEM ***//
	//*** Abertura do arquivo ***//
	
	char nomearq[100];
	cout << "Digite o nome da imagem: ";
	cin >> nomearq;
	arqentrada.open(nomearq,ios::in); //Abre arquivo para leitura
	if (!arqentrada) {
		cout << "Nao consegui abrir arquivo imagem.pnm" << endl;
		return 0;
	}
//===========================================================================//


//*** Leitura do cabecalho ***//
	arqentrada >> tipo;	         //Le o tipo de arquivo
	arqentrada.get();		     //Le e descarta o \n do final da 1a. linha

	if (strcmp(tipo,"P2")==0) {
		cout << "Imagem em tons de cinza\n";
	}
	else if (strcmp(tipo,"P3")==0) {
		cout << "Imagem colorida\n";
	}
	else if (strcmp(tipo,"P1")==0) {
		cout << "Imagem preto e branco\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}
	else if (strcmp(tipo,"P4")==0 || strcmp(tipo,"P5")==0 || strcmp(tipo,"P6")==0) {
		cout << "Imagem no formato RAW\n";
		cout << "Desculpe, nao trabalho com esse tipo de imagem.\n";
		arqentrada.close();
		return 0;
	}

	while((c = arqentrada.get()) == '#')	  //Enquanto for comentario
		arqentrada.getline(comentario,200);	  //Le e descarta a linha "inteira"

	arqentrada.putback(c);	                  //Devolve o caractere lido para a entrada, pois como
											  //nao era comentario, era o primeiro digito da largura

	arqentrada >> largura >> altura;	      //Le as dimensoes da imagem, numero de pixels da horizontal e da vertical
	cout << "Tamanho: " << largura << " x " << altura << endl;
	if (largura > MAXLARGURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXLARGURA << " pixels de largura.\n";
		arqentrada.close();
		return 0;
	}
	if (altura > MAXALTURA) {
		cout << "Desculpe, ainda nao trabalho com imagens com mais de " << MAXALTURA << " pixels de altura.\n";
		arqentrada.close();
		return 0;
	}

	arqentrada >> valor;	//Valor maximo do pixel (temos que ler, mas nao sera usado, assumimos 255)
//===========================================================================//

//*** Leitura dos pixels da imagem ***//

//PARA IMAGEM DO TIPO P2
if(strcmp(tipo,"P2")==0) {
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			arqentrada >> valor;
			imagem[i][j] = (unsigned char)valor;	//guarda no formato unsigned char
		}
}
//PARA IMAGEM DO TIPO P3
else if(strcmp(tipo,"P3")==0) {
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			for(p=0; p<3; p++){
			arqentrada >> valor;
			imagemP3[i][j][p] = (unsigned char)valor;	//guarda no formato unsigned char
			}
		}
}
arqentrada.close();  //Fecha arquivo apos a leitura

//*** Fim da leitura da imagem ***//

//===========================================================================//

//*** Escolha da operação de processamento da imagem ***//

int options;
cout << "Oi! O que deseja fazer com a imagem?" << endl;
cout << "1 - Escurecer" << endl;
cout << "2 - Clarear" << endl;
cout << "3 - Gerar o negativo" << endl;
cout << "4 - Espelhar Horizontalmente" << endl;
cout << "5 - Espelhar Verticalmente" << endl;
cout << "6 - Aplicar filtro de sobel" << endl;
cout << "7 - Aplicar filtro de realce (sharpening)" << endl;
cout << "8 - Aplicar filtro de binarizacao" << endl;
cout << "9 - Transformar a imagem colorida em tons de cinza" << endl;

cin >> options;
if(options < 1 || options >9){
	cout << "Opção inválida!" << endl;
	return 0;
}

//===========================================================================//

//*** Escurecer imagem ***//

if(options ==1){
	int fatorE;
	cout << "Qual o fator de escurecimento (0-255)? ";
	cin >> fatorE;
	if(fatorE < 0)
		fatorE = 0;  // proteção

	//IMAGEM TIPO P2 
	if(strcmp(tipo,"P2")==0) {
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			valor = (int)imagem[i][j];			            //pega o valor do pixel
			valor -= fatorE;								//escurece o pixel em certo valor(fatorE)
			if (valor < 0)									//se der negativo iguala a 0 (preto)
				valor = 0;									
			if (valor > 255)								//se o valor for maior que o valor máximo, iguala ao valor máximo
				valor = 255;							
			imagem[i][j] = (unsigned char)valor;	        //modifica o pixel
		}
	}
	//IMAGEM TIPO P3
	else if(strcmp(tipo,"P3")==0) {
			for(i=0;i<altura;i++) 
			  for(j=0;j<largura;j++) {
					for(p=0; p<3; p++){
						valor = (int)imagemP3[i][j][p];			        //pega o valor das bandas de cores dos pixeis
						valor -= fatorE;							    //escurece em certo valor(fatorE)
						if (valor < 0)									//se der negativo iguala a 0
							valor = 0;									
						if (valor > 255)								//se o valor for maior que o valor máximo, iguala ao valor máximo
							valor = 255;								
						imagemP3[i][j][p] = (unsigned char)valor;	    //modifica o pixel
					}
			  }
	}
}
//===========================================================================//

	//*** Clarear a imagem ***//
	
else if(options ==2){
	int fatorC;
	cout << "Qual o fator de clareamento (0-255)? ";
	cin >> fatorC;
	if(fatorC < 0)
		fatorC = 0;  // proteção
	
	//IMAGEM TIPO P2
	if(strcmp(tipo,"P2")==0) {
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			valor = (int)imagem[i][j];			       //pega o valor do pixel
			valor += fatorC;						   //clareia o pixel em certo valor(fatorC)						   
			if (valor > 255)						   //se o valor for maior que o valor máximo, iguala ao valor máximo
				valor = 255;						
			imagem[i][j] = (unsigned char)valor;	   //modifica o pixel
		}
	}
	
	//IMAGEM TIPO P3
	else if(strcmp(tipo,"P3")==0) {
			for(i=0;i<altura;i++)
			  for(j=0;j<largura;j++) {
					for(p=0; p<3; p++){
						valor = (int)imagemP3[i][j][p];			        //pega o valor das bandas de cores dos pixeis
						valor += fatorC;								//clareia o pixel em certo valor(fatorC)							
						if (valor > 255)								//se o valor for maior que o valor máximo, iguala ao valor máximo
							valor = 255;							
						imagemP3[i][j][p] = (unsigned char)valor;		//modifica o pixel
					}
			  }
	}
}

//===========================================================================//

	//*** Gerar o negativo da imagem ***//
	
else if(options ==3){
	
	//IMAGEM TIPO P2
	if(strcmp(tipo,"P2")==0) {
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
			valor = (int)imagem[i][j];			    //pega o valor do pixel
			valor = 255 - valor;				    //inverte o valor do pixel
			imagem[i][j] = (unsigned char)valor;	//modifica o pixel
		}
	}
	
	//IMAGEM TIPO P3 
	else if(strcmp(tipo,"P3")==0) {
			for(i=0;i<altura;i++)
			  for(j=0;j<largura;j++) {
					for(p=0; p<3; p++){
						valor = (int)imagemP3[i][j][p];             //pega o valor das bandas de cores dos pixeis
						valor = 255 - valor;				        //inverte o valor de cada banda de cor do pixel
						imagemP3[i][j][p] = (unsigned char)valor;	//modifica o pixel
					}
			  }
	}
}
//===========================================================================//

	//*** Espelhar a imagem horizontalmente ***//
	
else if(options ==4){
	
	//IMAGEM TIPO P2
	if(strcmp(tipo,"P2")==0) {
	for(i=0;i<altura;i++)
		for(j=0;(j<largura/2);j++){
			unsigned char auxl = imagem[i][j];         //troca o pixel de uma coluna
			imagem[i][j] = imagem[i][largura-1-j];     //pelo pixel da coluna simetrica
			imagem[i][largura-1-j] = auxl;             //na mesma linha(i)
		}
	}
	//IMAGEM TIPO P3
	else if(strcmp(tipo,"P3")==0) {
			for(i=0;i<altura;i++){
			  for(j=0;(j<largura/2);j++){
					for(p=0; p<3; p++){
					unsigned char auxl = imagemP3[i][j][p];             // troca o pixel de uma coluna pelo pixel da coluna simétrica
					imagemP3[i][j][p] = imagemP3[i][largura-1-j][p];    // na mesma linha (i), mantendo os três canais de cor (RGB)
					imagemP3[i][largura-1-j][p] = auxl;                
					}
				
			}
	}
}
}

//===========================================================================//

	//*** Espelhar a imagem verticalmente***//
	
else if(options ==5){
	
	//IMAGEM TIPO P2
	if(strcmp(tipo,"P2")==0) {
	for(i=0;i<altura/2;i++)
		for(j=0;(j<largura);j++){
			unsigned char auxl = imagem[i][j];            //troca o pixel de uma linha
			imagem[i][j] = imagem[altura - 1 - i][j];     //pelo pixel da linha simétrica
			imagem[altura - 1 - i][j] = auxl;             //na mesma coluna(j)
		}
	}
	//IMAGEM TIPO P3
	else if(strcmp(tipo,"P3")==0) {
			for(i=0;i<altura/2;i++){
			  for(j=0;(j<largura);j++){
					for(p=0; p<3; p++){
					unsigned char auxl = imagemP3[i][j][p];           // troca o pixel (RGB) da linha atual com o pixel 
					imagemP3[i][j][p] = imagemP3[altura-1-i][j][p];   // da linha simétrica, na mesma coluna (j),
					imagemP3[altura-1-i][j][p] = auxl;                
					}
			  }
			}
	}
}
//===========================================================================//

//*** Aplicar filtro de sobel ***//

else if(options ==6){
	
		//IMAGEM TIPO P2 
	if(strcmp(tipo,"P2")==0) {
	int matgx[3][3] = {1, 0, -1, 2, 0, -2, 1, 0, -1};  // declara as matrizes do filtro sobel
	int matgy[3][3] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
	for(i=0;i<altura+2;i++)                            // inicializa a matriz auxiliar com 0
		for(j=0;j<largura+2;j++) {
			matauxP2[i][j] = 0;       //matriz auxiliar criada globalmente
		}
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
		    matauxP2[i+1][j+1] = imagem[i][j];  // copia a imagem original para o centro da matriz auxiliar
		}
		
	for(i=0;i<altura;i++){                      // percorre a matriz 'imagem' novamente para aplicar o filtro
		for(j=0;(j<largura);j++){
			int somax = 0;
			int somay = 0;
			int multip;
			for(int t = i;t<i+3; t++){                // percorre os pixels vizinhos e o próprio pixel
				for(int g = j; g<j+3; g++){           
					multip =(matgx[t-i][g-j])*(matauxP2[t][g]);   // calcula o gradiente horizontal (gx)
					somax += multip;
					multip =(matgy[t-i][g-j])*(matauxP2[t][g]);   // calcula o gradiente vertical (gy)
					somay += multip;
				}
			}
		
			int somagp = sqrt((somax*somax)+(somay*somay));       // calcula a magnitude do gradiente
			if(somagp > 255)    // tratamento do caso especial
				somagp = 255;
			imagem[i][j] = somagp;
			somagp = 0;
		}
	}
	}

	//IMAGEM TIPO P3
	else if(strcmp(tipo,"P3")==0) {
	int matgx[3][3] = {1, 0, -1, 2, 0, -2, 1, 0, -1};   // declara as matrizes do filtro sobel
	int matgy[3][3] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
	for(i=0;i<altura+2;i++)                 // inicializa a matriz auxiliar com 0
		for(j=0;j<largura+2;j++) {
			for(p=0; p<3; p++){
			matauxP3[i][j][p] = 0;          //matriz auxiliar criada globalmente
			}
		}
	for(i=0;i<altura;i++){
		for(j=0;j<largura;j++) {
			for(p=0; p<3; p++){
		    matauxP3[i+1][j+1][p] = imagemP3[i][j][p]; // copia a imagem original para o centro da matriz auxiliar
			}
		}
	}
	for(i=0;i<altura;i++){            // percorre a matriz 'imagem' novamente para aplicar o filtro
		for(j=0;(j<largura);j++){
			for(p=0; p<3; p++){
			int somax = 0;
			int somay = 0;
			int multip;
			for(int t = i;t<i+3; t++){        // percorre os pixels vizinhos e o próprio pixel
				for(int g = j; g<j+3; g++){
					multip =(matgx[t-i][g-j])*(matauxP3[t][g][p]);    // calcula o gradiente horizontal (gx)
					somax += multip;
					multip =(matgy[t-i][g-j])*(matauxP3[t][g][p]);    // calcula o gradiente vertical (gy)
					somay += multip;
				}
			}
		
			int somagp = sqrt((somax*somax)+(somay*somay));     // calcula a magnitude do gradiente
			if(somagp > 255)      // tratamento do caso especial
				somagp = 255;
			imagemP3[i][j][p] = somagp;
			somagp = 0;
			}
		}
	}
	}
}

	
//===========================================================================//

	//*** Filtro de realce ***//
else if(options ==7){
	//IMAGEM TIPO P2 
	if(strcmp(tipo,"P2")==0) {
	int matfiltro[3][3] = {0, -1, 0, -1, 5, -1, 0, -1, 0};   // declara a matriz do filtro de realce
	for(i=0;i<altura+2;i++)                                  // inicializa a matriz auxiliar com 0
		for(j=0;j<largura+2;j++) {
			matauxP2[i][j] = 0;           // matriz auxiliar criada globalmente
		}
	for(i=0;i<altura;i++)
		for(j=0;j<largura;j++) {
		    matauxP2[i+1][j+1] = imagem[i][j];   // copia a imagem original para o centro da matriz auxiliar
		}
		
	for(i=0;i<altura;i++){                       // percorre a matriz 'imagem' novamente para aplicar o filtro
		for(j=0;(j<largura);j++){
			int soma = 0;
			int multip;
			for(int t = i;t<i+3; t++){           // percorre os pixels vizinhos e o próprio pixel
				for(int g = j; g<j+3; g++){           
					multip =(matfiltro[t-i][g-j])*(matauxP2[t][g]);   //calcula o filtro para cada pixel
					soma += multip;
				}
			}
			if(soma < 0)            // tratamento dos casos especiais
				soma = 0;
			if(soma > 255)
				soma = 255;
			imagem[i][j] = soma;    //aplica o filtro ao pixel 
			soma = 0;
		}
	}
	}
	//IMAGEM TIPO P3
	else if(strcmp(tipo,"P3")==0) {
	int matfiltro[3][3] = {0, -1, 0, -1, 5, -1, 0, -1, 0};   // declara a matriz do filtro de realce
	for(i=0;i<altura+2;i++){                                 // inicializa a matriz auxiliar com 0
		for(j=0;j<largura+2;j++) {
			for(p=0;p<3;p++){
				matauxP3[i][j][p] = 0;        // matriz auxiliar criada globalmente
			}
		}
	}
	for(i=0;i<altura;i++){
		for(j=0;j<largura;j++) {
			for(p=0;p<3;p++){
			 matauxP3[i+1][j+1][p] = imagemP3[i][j][p];        // copia a imagem original para o centro da matriz auxiliar
			}
		}
	}
	for(i=0;i<altura;i++){              // percorre a matriz 'imagem' novamente para aplicar o filtro
		for(j=0;(j<largura);j++){
			for(p=0;p<3;p++){
			int soma = 0;
			int multip;
				for(int t = i;t<i+3; t++){           // percorre os pixels vizinhos e o próprio pixel
					for(int g = j; g<j+3; g++){           
						multip =(matfiltro[t-i][g-j])*(matauxP3[t][g][p]);    // calcula o valor do filtro para cada pixel
						soma += multip;
					}
				}
				if(soma < 0)        // tratamento dos casos especiais 
					soma = 0;
				if(soma > 255)
					soma = 255;
				imagemP3[i][j][p] = soma;
				soma = 0;
				}
			}
		}
	}
	}
	
//===========================================================================//

	//*** Filtro de Binarização ***//
	
else if(options ==8){
	
//IMAGEM TIPO P2 
if(strcmp(tipo,"P2")==0) {      
	for(i=0;i<altura;i++){        //Percorre a matriz 'imagem'
		for(j=0;j<largura;j++){
			if(imagem[i][j] < 127)    //Condicional de quando o pixel será 0 ou 255(preto ou branco)
				imagem[i][j] = 0;
			else if(imagem[i][j] >= 127)
				imagem[i][j] = 255;
		}
	}
}
//IMAGEM TIPO P3
else if(strcmp(tipo,"P3")==0) {  
int soma = 0;
int media = 0;    
	for(i=0;i<altura;i++){        //Percorre a matriz 'imagemP3'
		for(j=0;j<largura;j++){
			soma = 0;
			media = 0;
			for(p=0;p<3;p++){
				 soma+= imagemP3[i][j][p];      //Soma as bandas de cores de cada pixel
			}
			media = soma/3;   //Media da soma das bandas de cores dos pixels
			
			for(p=0;p<3;p++){    //percorre as bandas novamente para atualizar elas com o novo valor
			if(media < 127)      //Condicional de quando o pixel será 0 ou 255(preto ou branco)
				imagemP3[i][j][p] = 0;
			else
				imagemP3[i][j][p] = 255;
			}
		}
	}
}
}

//===========================================================================//

//*** Colorida para tons de cinza ***//
else if(options ==9){
	
//Executa apenas para imagens do tipo P3
if(strcmp(tipo,"P3")==0) {   
	for(i=0;i<altura;i++){        //Percorre a matriz 'imagemP3'
		for(j=0;j<largura;j++){
			double cinza = 0.299 * imagemP3[i][j][0] + 0.587 * imagemP3[i][j][1] + 0.114 * imagemP3[i][j][2];     // calcula o tom de cinza usando média ponderada dos canais RGB, com valores preestabelecidos
				imagem[i][j] = (unsigned char)cinza;       // Salva o resultado na matriz P2 
				
		}
	}
	strcpy(tipo, "P2");     //altera a assinatura da imagem para P2
		cout << "A imagem foi convertida para P2 (tons de cinza)!" << endl; 
}
else{ 
	cout << "Erro: a imagem ja esta em tons de cinza.\n";
	return 0;
}
}

//*** FIM DO TRATAMENTO DA IMAGEM ***//

//===========================================================================//

//*** GRAVACAO DA IMAGEM ***//
	//*** Grava a nova imagem ***//
	// TIPO P2  -------- 
	if(strcmp(tipo,"P2")==0) {
		
	char nomesaida[100];
	cout << "Digite o nome do arquivo de saida: ";
	cin >> nomesaida;
	arqsaida.open(nomesaida,ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar novaimagem.pnm\n";
		return 0;
	}

	arqsaida << tipo << endl;			    	//tipo
	arqsaida << "# TP2-INF110, by RV\n";	    //comentario
	arqsaida << largura << " " << altura;	    //dimensoes
	arqsaida << " " << 255 << endl;				//maior valor
	for(i=0;i<altura;i++){
		for(j=0;j<largura;j++){
			arqsaida << (int)imagem[i][j] << " ";   //pixels
		}
		arqsaida << endl;      //Pula a linha
	}
	arqsaida.close();		
	}
	// TIPO P3  -------- 
	if(strcmp(tipo,"P3")==0) {
		
	char nomesaida[100];
	cout << "Digite o nome do arquivo de saida: ";
	cin >> nomesaida;
	arqsaida.open(nomesaida,ios::out);	//Abre arquivo para escrita
	if (!arqsaida) {
		cout << "Nao consegui criar novaimagem.pnm\n";
		return 0;
	}

	arqsaida << tipo << endl;				//tipo
	arqsaida << "# TP2-INF110, by RV\n";	//comentario
	arqsaida << largura << " " << altura;	//dimensoes
	arqsaida << " " << 255 << endl;			//maior valor
	for(i=0;i<altura;i++) {
		for(j=0;j<largura;j++) {
			for(p=0; p<3; p++){
			    arqsaida << (int)imagemP3[i][j][p] << " ";	//espaço em vez de endl
			}
        }
        arqsaida << endl; // pula linha só quando acaba a largura
    }

	arqsaida.close();		
	}                 //fecha o arquivo
	
	//*** FIM DA GRAVACAO DA IMAGEM ***//
	
//===========================================================================//
	return 0;
}

