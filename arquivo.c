#include "includes.h"
#include <stdlib.h>
#define CHARMAX 73 //I
#define asciiMAX 127
#define ESPACO_ESCRITO 24


void criptografa_numero (char *string) {

	short int i, j, valor_aleatorio;
	char aux[4];

	//printf ("\n-----CRIPTOGRAFIA NUMERO-----");

	valor_aleatorio = randomizar(asciiMAX - CHARMAX) + CHARMAX + 1;

	//transforma 0 em characteres aleatorios maiores que J e transforma numeros > 0 em letras de A ate I
	for (i = 0; i < 8; i++) {
		if (string[i] == '0') {
			string[i] = valor_aleatorio;
		}else{
			string[i] += 16;
		}
	}
	//debug
	//printf ("PASSO 1: %s\n", string);

	//aumenta o character em 2*i a partir do character 5
	for (i = 4; i < 8; i++) {
		string[i] += i*2;
	}
	//debug
	//printf ("PASSO 2: %s\n", string);

	//inverte string ate o character 4 na string aux, diminuindo em (i+1)*3 durante o processo
	for (i = 0, j = 3; i < 4; i++, j--) {
		aux [j] = string[i] - (i+1)*3; 
	}
	//joga a string auxiliar de volta na string principal
	for (i = 0; i < 4; i++)
		string[i] = aux[i];
	//debug
	//printf ("FINAL: %s\n", string);

}



void descriptografa_numero (char *string) {

	short int i, j;
	char aux[4];

	//printf ("\n-----DESCRIPTOGRAFIA NUMERO-----");

	//inverte string ate o character 4 na string aux
	for (i = 0, j = 3; i < 4; i++, j--) {
		aux [j] = string [i] + (j+1)*3;
	}
	//joga characteres da string aux de volta na string principal
	for (i = 0; i < 4; i++) {
		string[i] = aux[i];
	}
	//debug
	//printf ("PASSO 1: %s\n", string);

	//diminui o character em 2 a partir do character 5
	for (i = 4; i < 8; i++) {
		string[i] -= i*2;
	}
	//debug
	//printf ("PASSO 2: %s\n", string);

	//transforma todo character > I em 0 e diminui os demais em 16
	for (i = 0; i < 8; i++) {
		if (string[i] > CHARMAX) {
			string[i] = '0';
		}else{
			string[i] -= 16;
		}
	}
	//debug
	//printf ("FINAL: %s\n", string);
	

}


void criptografa_nome (char *string) {

	short int i, j, dim;
	char aux[4];

	//printf ("\n-----CRIPTOGRAFIA NOME-----");

	//determina dimensao da string
	for (dim = 0; string[dim] != '\n'; dim++) {}
	//debug
	//printf ("DIMENSAO: %d\n", dim);

	//aumenta todos os caracteres da string em 16
	for (i = 0; i < dim; i++) {
			string[i] += 16;
	}
	//debug
	//printf ("PASSO 1: %s\n", string);

	//aumenta o character em 2*i a partir da metade
	for (i = dim/2; i < dim; i++) {
		string[i] += i*2;
	}
	//debug
	//printf ("PASSO 2: %s\n", string);

	//inverte string ate o character 4 na string aux, diminuindo em (i+1)*3 durante o processo
	for (i = 0, j = dim/2 - 1; i < dim/2; i++, j--) {
		aux [j] = string[i] - (i+1)*3; 
	}
	//joga a string auxiliar de volta na string principal
	for (i = 0; i < dim/2; i++)
		string[i] = aux[i];
	//debug
	//printf ("FINAL: %s\n", string);

}



void descriptografa_nome (char *string) {

	short int i, j, dim;
	char aux[4];

	//printf ("\n-----DESCRIPTOGRAFIA NOME-----");

	//determina dimensao da string
	for (dim = 0; string[dim] != '\n'; dim++) {}
	//debug
	//printf ("DIMENSAO: %d\n", dim);

	//inverte string ate o character 4 na string aux, aumentando em (j+1)*3 durante o processo
	for (i = 0, j = dim/2 - 1; i < dim/2; i++, j--) {
		aux [j] = string [i] + (j+1)*3;
	}
	//joga characteres da string aux de volta na string principal
	for (i = 0; i < dim/2; i++) {
		string[i] = aux[i];
	}
	//debug
	//printf ("PASSO 1: %s\n", string);

	//diminui o character em 2*i a partir da metade
	for (i = dim/2; i < dim; i++) {
		string[i] -= i*2;
	}
	//debug
	//printf ("PASSO 2: %s\n", string);

	//aumenta todo character em 16
	for (i = 0; i < dim; i++) {
			string[i] -= 16;
	}
	//debug
	//printf ("FINAL: %s\n", string);
	

}



short int achar_menor (struct recordes *valor) {

	short int i, j, pos_menor, primeiro;
	int menor;
	
	primeiro = dificuldade*PONTUACOES;
	//da para o menor o valor do primeiro recorde
	menor = valor[primeiro].pontuacao;
	pos_menor = primeiro;

	//percorre todos os valores
	for (i = primeiro; i < primeiro+PONTUACOES; i++) {
		//se o menor atual eh maior que valor[i]
		if ( menor > valor[i].pontuacao ) {
					//da novo valor ao menor
					menor = valor[i].pontuacao;
					pos_menor = i;
		}

	}

	return pos_menor;	

}



void ordenar (struct recordes *vetor) {

	struct recordes aux;
	short int i, j, primeiro;

	primeiro = dificuldade*PONTUACOES;

	for (i = 0; i < PONTUACOES-1; i++) {
		for (j = i+1; j < PONTUACOES; j++) { 
			if ( vetor[j+primeiro].pontuacao > vetor[i+primeiro].pontuacao ) {

				//troca os recordes de posicao
				aux = vetor[j+primeiro];
				vetor[j+primeiro] = vetor[i+primeiro];
				vetor[i+primeiro] = aux;
				
			}
		}
	}

}



void mostrar_pontuacao (short int dificul) {

	short int nome_dim[PONTUACOES], i, j, primeiro;

	char aux[23],
		 aux_score[9];

	primeiro = dificul*PONTUACOES;

	//determina a dimensao dos recordes
	for (i = 0; i < PONTUACOES; i++) {
		for (j = 0; recorde[i+primeiro].nome[j] != '\n'; j++);
		nome_dim[i] = j;
	}
	for (i = 0; i < PONTUACOES; i++) {

		//adiciona a posicao do jogador a uma variavel auxiliar
		sprintf (aux, "%02d ", i+1);

		//adiciona o nome do jogador sem o fim de linha a uma variavel auxiliar
		for (j = 3; j < nome_dim[i] + 3; j++) {
			aux[j] = recorde[i+primeiro].nome[j-3];
		}

		//adiciona pontos para separar nome e score a uma variavel auxiliar
		for ( ; j < 14; j++)
			aux[j] = '.';

		//adiciona o score a uma variavel auxiliar
		sprintf (aux_score, "%08d", recorde[i+primeiro].pontuacao);
		for ( ; j < 22; j++)
			aux[j] = aux_score[j-14];

		aux[j] = '\0';

		//declarar surface com o nome do jogador e score
		if ( !( texto_recordes[i].surface = TTF_RenderText_Solid (pixel, aux, BRANCO) ) )
			printf ("Nao foi possivel declarar texto_recordes[%d].surface:\n%s\n", i, TTF_GetError() );

	}

}



void inserir_score (int score) {

	FILE *escrever_arquivo;
	short int menor_recorde,
		   i,
		   j,
		   nome_dim[PONTUACOES],
		   primeiro,
		   cont_aux,
		   mousex,
		   mousey;

	char nome[NOME_CHAR] = {'\0'},
	     numero[9];

	SDL_Event evento;
	SDL_Surface *nome_surface;

	//verificar qual a posicao do menor recorde no vetor
	menor_recorde = achar_menor(recorde);

	//verificar quebra de recorde
	if ( score > recorde[menor_recorde].pontuacao) {

		i = 0;
		nome[0] = 124;
		texto_recordes[3].pos.x += 230;
		SDL_EnableUNICODE(SDL_ENABLE);
		while(1) {

			//blita fundo
			if ( SDL_BlitSurface (digiteonome, NULL, tela, NULL) < 0 )
				printf ("Nao foi possivel blitar digiteonome:\n%s\n", SDL_GetError() );

			//verifica input do jogador
			while (SDL_PollEvent(&evento)) {

				if (evento.type == SDL_QUIT)
					exit(0);
				//se aperta enter e ja digitou alguma coisa termina o loop
				else if(evento.key.keysym.sym == SDLK_RETURN && i > 0) {
					//sai do loop
					goto encerra_input;
				}
				//se apertou alguma tecla
				else if (evento.type == SDL_KEYDOWN) {
					//backspace
					if (evento.key.keysym.sym == SDLK_BACKSPACE && i > 0) {
						//se possivel retorna o cursor e apaga o ultimo caracter do nome
							nome[i] = '\0';
							i--;
							nome[i] = 124;
					}
					else if (i < NOME_CHAR - 2 && evento.key.keysym.unicode >= 32 && evento.key.keysym.unicode <= 126 &&
						( i != 0 || evento.key.keysym.unicode != 32 ) ) {

						//coloca caracter no nome e muda a posicao do cursor
						nome[i] = (char)evento.key.keysym.unicode;
						i++;
						nome[i] = 124;

					}
 
				}
				//se clicou no botao de submeter
				else if (evento.type == SDL_MOUSEBUTTONUP && evento.button.button == SDL_BUTTON_LEFT && i > 0) {
					//atualiza posicao do mouse
					mousex = evento.button.x;
					mousey = evento.button.y;

					if (mousex > botao_submeter.x && mousex < botao_submeter.x+botao_submeter.w && mousey > botao_submeter.y &&
					    mousey < botao_submeter.y+botao_submeter.h) {
						goto encerra_input;
					}

				}
			}

			//determina surface com o nome
			if ( !(nome_surface = TTF_RenderText_Solid (pixel, nome, BRANCO) ) )
				printf ("Nao foi possivel declarar nome_surface:\n%s\n", TTF_GetError() );
			//blita o nome na tela
			if ( SDL_BlitSurface (nome_surface, NULL, tela, &texto_recordes[3].pos) < 0 )
				printf ("Nao foi possivel blitar nome_surface:\n%s\n", SDL_GetError() );
			//limpa memoria para evitar vazamentos
			SDL_FreeSurface(nome_surface);


			SDL_Flip(tela);

		}

		//saida do loop
		encerra_input:
		//completa a string do nome
		nome[i] = '\n';
		nome[i+1] = '\0';
		texto_recordes[3].pos.x -= 230;
		SDL_EnableUNICODE(SDL_DISABLE);

		//printf ("%s", nome);

		//substitui o menor recorde pelo novo recorde
		sprintf (recorde[menor_recorde].nome, "%s", nome);
		recorde[menor_recorde].pontuacao = score;

		//ordena os recordes
		ordenar (recorde);

		//abre arquivo para escrita
		if ( !( escrever_arquivo = fopen (ARQUIVO, "w") ) ) {
			//erro em caso de falha
			printf ("Nao foi possivel abrir %s\n", ARQUIVO);

			exit(1);
		}

		//insere os recordes no arquivo
		for (j = 0; j < 3; j++) { 

			primeiro = j*PONTUACOES;

			for (i = 0; i < PONTUACOES; i++) {
				//pontuacao
				sprintf (numero, "%08d", recorde[i+primeiro].pontuacao);
				criptografa_numero(numero);
				fprintf (escrever_arquivo, "%s\n", numero);
				//nome
				criptografa_nome(recorde[i+primeiro].nome);
				fprintf (escrever_arquivo, "%s", recorde[i+primeiro].nome);
				descriptografa_nome(recorde[i+primeiro].nome);
			}

		}

		fclose (escrever_arquivo);

	}

}
