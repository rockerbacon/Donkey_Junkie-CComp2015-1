/*
Controle da janela do programa
*/

#include "includes.h"
#include <stdlib.h>

/*ABRIR JANELA*/
SDL_Surface* iniciar(SDL_Surface *tela) {

	//Erro caso nao seja possivel iniciar o sistema de video
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0 ) {
		printf ( "Nao foi possivel iniciar subsistema:\n%s\n", SDL_GetError() );
		exit(1);
	}

	//criar a janela
	tela = SDL_SetVideoMode(RESX, RESY, 16, SDL_SWSURFACE | SDL_FULLSCREEN);
	
	//erro caso nao consiga criar janela
	if (tela == NULL) {
		printf ( "Nao foi possivel criar janela %dx%d 16bit:\n%s\n", RESX, RESY, SDL_GetError() );
		exit(1);
	}
	
	//inicializa o sistema de audio
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );

	//erro caso nao consiga iniciar o sistema de audio
	if ( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) != 0) {
	      	printf( "Nao foi possivel inicializar o audio:\n%s\n", Mix_GetError() );
   	}

	//Titulo na janela
	SDL_WM_SetCaption ("Donkey Junkie", NULL);
	return tela;


}

/*BLITAR TELA*/
void blit_tela(void) {

		static short int i;

		//background
		if ( SDL_BlitSurface (fundo, NULL, tela, NULL) < 0 ) {
			printf ("Nao foi possivel blitar fundo:\n%s\n", SDL_GetError() );
			exit(1);
		}

		//escadas
		for (i = 0; i < NESCADAS; i++) {
			if ( SDL_BlitSurface (escada, NULL, tela, &escada_pos[i]) < 0 ) {
				printf ("Nao foi possivel blitar escada %d:\n%s\n", i, SDL_GetError() );
				exit(1);
			}
			if ( SDL_BlitSurface (escada_quebrada, NULL, tela, &escada_quebrada_pos[i]) < 0 ) {
				printf ("Nao foi possivel blitar escada quebrada %d:\n%s\n", i, SDL_GetError() );
				exit(1);
			}
		}

		//ultima escada
		if ( SDL_BlitSurface (escadafinal, NULL, tela, &escadafinal_pos) < 0 ) {
			printf ("Nao foi possivel blitar ultima escada:\n%s\n", SDL_GetError() );
			exit(1);
		}

		//crianca
		if ( SDL_BlitSurface (crianca, &crianca_sprite, tela, &crianca_pos) < 0 ) {
			printf ("Nao foi possivel blitar crianca:\n%s\n", SDL_GetError() );
			exit(1);
		}
		//pedras de crack
		for (i = 0; i < NCRACK; i++) {
			if (crack_velo[i] > 0)
				if ( SDL_BlitSurface (crack, &crack_sprite[i], tela, &crack_pos[i]) < 0 ) {
					printf ("Nao foi possivel blitar crack %d:\n%s\n", i, SDL_GetError() );
					exit(1);
				}
		}

		//vidas
		if (modo_jogo == 0) {
			for (i = 0; i < NVIDAS; i++) {
				if ( SDL_BlitSurface (vida, NULL, tela, &vida_pos[i]) < 0 ) {
					printf ("Nao foi possivel blitar vida %d:\n%s\n", i, SDL_GetError() );
					exit(1);
				}
			}
		}

		//pau
		if (pau_pos.y != 0)
			if ( SDL_BlitSurface (pau, NULL, tela, &pau_pos) < 0 ) {
				printf ("Nao foi possivel blitar pau: \n%s\n", SDL_GetError() );
				exit(1);
			}

		//caixa de crack
		if ( SDL_BlitSurface (caixa, NULL, tela, &caixa_pos) < 0 ) {
			printf ("Nao foi possivel blitar caixa:\n%s\n", SDL_GetError() );
			exit(1);
		}

		//beira mar
		if ( SDL_BlitSurface (beira, &beira_sprite, tela, &beira_pos) < 0 ) {
			printf ("Nao foi possivel blitar vilao:\n%s\n", SDL_GetError() );
			exit(1);
		}

		//oficial
		if ( SDL_BlitSurface (oficial, &oficial_sprite, tela, &oficial_pos) < 0 ) {
			printf ("Nao foi possivel blitar oficial:\n%s\n", SDL_GetError() );
			exit(1);
		}

}



/*FECHAR JANELA*/
void sair(void) {

	short int i;

	//limpar imagens
	SDL_FreeSurface (tela);
	SDL_FreeSurface (aviso);
	SDL_FreeSurface (abertura1);
	SDL_FreeSurface (abertura2);
	SDL_FreeSurface (controles);
	SDL_FreeSurface (menu);
	SDL_FreeSurface (tela_recordes);
	SDL_FreeSurface (creditos);
	SDL_FreeSurface (historia1);
	SDL_FreeSurface (historia2);
	SDL_FreeSurface (tela_gameover);
	SDL_FreeSurface (tela_dificuldade);
	SDL_FreeSurface (tela_mododejogo);
	SDL_FreeSurface (digiteonome);
	SDL_FreeSurface (ganhou);
	SDL_FreeSurface (fundo);
	SDL_FreeSurface (oficial);
	SDL_FreeSurface (crack);
	SDL_FreeSurface (escada);
	SDL_FreeSurface (escada_quebrada);
	SDL_FreeSurface (escadafinal);
	SDL_FreeSurface (beira);
	SDL_FreeSurface (caixa);
	SDL_FreeSurface (crianca);
	SDL_FreeSurface (vida);
	SDL_FreeSurface (pau);

	//limpar audio
	Mix_FreeChunk (som);
	Mix_FreeChunk (sommenu);
	Mix_FreeChunk (somgo);
	Mix_FreeChunk (missao);
	Mix_FreeChunk (somhit);
	Mix_FreeChunk (coin);
	Mix_FreeChunk (somwin);
	Mix_FreeMusic (theme);

	//limpar fontes
	TTF_CloseFont(texto_score.fonte);
	TTF_CloseFont(texto_printscore.fonte);
	TTF_CloseFont(texto_tempo.fonte);
	TTF_CloseFont(pixel);
	TTF_CloseFont(pixel_25);

	//limpar variaveis alocadas dinamicamente
	if (vida_pos != NULL) {
		free (vida_pos);
		free (crack_velo);
		free (crack_status);
		free (crack_chao);
		free (crack_pos);
		free (crack_col);
		free (crack_sprite);
		free (crack_rnd);
	}
	free(recorde);

	//fechar o SDL
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}



/*SELECIONAR SPRITE*/
/*
considere seu sprite sheet uma matriz com os elementos (sprites) no formato Axy, com x variando entre 0 e n e y variando entre 0 e m.
(0,0) eh a posicao com o primeiro sprite (1,0) o segundo e assim sucessivamente

-struct SDL_Rect sprite: struct do tipo SDL_Rect que possua a posicao e dimensoes atuais do sprite
-char plano: em qual plano devem ser selecionados os sprites, 'x' para plano x e qualquer outra coisa para plano y
-int ponto_x: coordenada x do primeiro elemento a ser verificado
-int ponto_y: coordenada y do primeiro elemento a ser verificado
-int max: ultimo elemento a ser verificado. Digite valor positivo caso o ultimo elemento venha apos o primeiro e valor negativo em caso contrario
-int freq: o intervalo de frames para mudanca de imagem, 1 significa 60 imagens por segundo e 60 significa 1 imagem por segundo
*/

SDL_Rect selecionar_sprite (struct SDL_Rect sprite, char plano, short unsigned int ponto_x, short unsigned int ponto_y, short int max, short unsigned int freq){

	if (frame % freq == 0) {

		//movimentacao no plano x
		if (plano == 'x') {

			sprite.y = ponto_y * sprite.h;

			//movimenta no sentido positivo
			if (max > 0) {

				if ( sprite.x < ponto_x * sprite.w  || sprite.x >= max * sprite.w ) {
					sprite.x = ponto_x * sprite.w;
				}else{
					sprite.x += sprite.w;
				}

			}
			//movimenta no sentido negativo
			else{

				max *= -1;

				if ( sprite.x > ponto_x * sprite.w  || sprite.x <= max * sprite.w ) {
					sprite.x = ponto_x * sprite.w;
				}else{
					sprite.x -= sprite.w;
				}


			}

		}

		//movimenta no plano y
		else{
			sprite.x = ponto_x * sprite.w;

			//movimenta no sentido positivo
			if (max > 0) {

				if ( sprite.y < ponto_y * sprite.h  || sprite.y >= max * sprite.h ) {
					sprite.y = ponto_y * sprite.h;
				}else{
					sprite.y += sprite.h;
				}

			}
			//movimenta no sentido negativo
			else{

				max *= -1;

				if ( sprite.y > ponto_y * sprite.h  || sprite.y <= max * sprite.h ) {
					sprite.y = ponto_y * sprite.h;
				}else{
					sprite.y -= sprite.h;
				}


			}


		}
	
	}

	return sprite;

}



//verificar colisao
/*
-SDL_Rect obj1 : coordenadas do primeiro objeto
-SDL_Rect obj2 : coordenadas do segundo objeto
*/
int colisao (SDL_Rect *obj1, SDL_Rect *obj2) {

	if ( (*obj1).x + (*obj1).w > (*obj2).x &&  (*obj2).x + (*obj2).w > (*obj1).x &&
	     (*obj1).y + (*obj1).h > (*obj2).y &&  (*obj2).y + (*obj2).h > (*obj1).y )

		return 1;

	else

		return 0;

}

void blit_texto () {

	static char aux[15];

	/*SCORE*/
	//define texto a ser mostrado
	sprintf (aux, "SCORE %08d", score);

	//declara a surface com o texto a ser mostrado
	if ( !( texto_score.surface = TTF_RenderText_Solid (texto_score.fonte, aux, BRANCO) ) )
		printf ("Nao foi possivel declarar texto_score.surface:\n%s\n", TTF_GetError() );

	//blita texto na tela
	if ( SDL_BlitSurface (texto_score.surface, NULL, tela, &texto_score.pos) < 0 )
		printf ("Nao foi possivel blitar score:\n%s\n", SDL_GetError() );


	/*TEMPO*/
	sprintf (aux, "%02d:%02d", seg/60, seg%60);

	//declara a surface com o texto a ser mostrado
	if ( !( texto_tempo.surface = TTF_RenderText_Solid (texto_tempo.fonte, aux, BRANCO) ) )
		printf ("Nao foi possivel declarar texto_tempo.surface:\n%s\n", TTF_GetError() );

	//blita texto na tela
	if ( SDL_BlitSurface (texto_tempo.surface, NULL, tela, &texto_tempo.pos) < 0 )
		printf ("Nao foi possivel blitar tempo:\n%s\n", SDL_GetError() );



	/*PONTUACAO GANHA*/
	if ( texto_printscore.pos.x != 0 && texto_printscore.pos.y != 0 ) {

			//define texto a ser mostrado
			sprintf (aux, "%+d", score_print);

			//declara a surface com o texto a ser mostrado
			if ( !( texto_printscore.surface = TTF_RenderText_Solid (texto_printscore.fonte, aux, (score_print>0)?VERDE:VERMELHO ) ) )
				printf ("Nao foi possivel declarar texto_printscore.surface:\n%s\n", TTF_GetError() );

			//blita texto na tela
			if ( SDL_BlitSurface (texto_printscore.surface, NULL, tela, &texto_printscore.pos) < 0 )
				printf ("Nao foi possivel blitar printscore:\n%s\n", SDL_GetError() );

			//limpa memoria para evitar vazamentos
			SDL_FreeSurface(texto_printscore.surface);

	}

	//limpar memoria para evitar vazamentos
	SDL_FreeSurface(texto_score.surface);
	SDL_FreeSurface(texto_tempo.surface);

}
