#include "includes.h"
#include <unistd.h>

//retorna um valor "aleatorio" entre 0 e amostragem-1
short unsigned int randomizar (amostragem) {
	return SDL_GetTicks() % amostragem;
}



//retorna diretorio onde se encontra o programa (somente para Linux)
void selecionar_dir (void) {

	//variaveis para auxiliar link
	char pseudo_dir[32],
	     diretorio[512];
	short int tam_dir;

	//link para pseudo diretorio
	sprintf ( pseudo_dir, "/proc/%d/exe", getpid() );

	//define dimensao da string que contem o diretorio do programa
	tam_dir = readlink ( pseudo_dir, diretorio, 511 );

	//remove nome do programa e adiciona fim de string
	diretorio[tam_dir-13] = '\0';

	//muda o diretorio de trabalho para o diretorio selecionado
	chdir (diretorio);

}




/*FUNCAO PRINCIPAL*/
int main (int argc, char **argv) {

	
	//selecionar diretorio de trabalho (main.c)
	selecionar_dir();

	//variavel para receber input
	unsigned char *tecla;

	//variavel para auxiliar nos loops
	short int i;

	/*VARIAVEIS PARA MENUS*/
	short int menu_loop = 1;
	//variaveis pra captar a posicao do mouse
	short int mousex, mousey;

	char string_pontuacao[17];

	//limpar a tela ao sair do programa (janela.c), chamado em todo exit()
	atexit (sair);

	//Variavel para verificar eventos
	SDL_Event evento;

	//abrir janela (janela.c)
	tela = iniciar(tela);
	
	//cria canais de audio
	Mix_AllocateChannels (10);

	//carrega todos os elementos necessarios
	carregar_inicial();

	/*MENUS*/
	/*INICIAL*/
	//loop de abertura
	do {

		iteracao = SDL_GetTicks();

		//verificar eventos
		SDL_PollEvent(&evento);

		//receber tecla pressionada
		tecla = SDL_GetKeyState(NULL);

		//verifica se deve sair da tela
		if (evento.type == SDL_QUIT)
			exit(0);

		//espera um tempo antes de trocar as imagens
		if ( esperar(FPS/2, &cont_aux) == 1 ) {
			menu_loop = (menu_loop == 1)? 0 : 1;
		}

		//blita as imagens de abertura com o pressione enter "piscando"
		if (menu_loop == 1) {
			if ( SDL_BlitSurface ( abertura1, NULL , tela , NULL ) < 0 )
		    		printf ("Nao foi possivel blitar abertura1:\n%s\n", SDL_GetError() );
		}else{
			if ( SDL_BlitSurface ( abertura2, NULL , tela , NULL ) < 0 )
			    	printf ("Nao foi possivel blitar abertura2:\n%s\n", SDL_GetError() );
		}

		//atualiza tela
		SDL_Flip ( tela );

		//controlar o FPS
		tempo = SDL_GetTicks() - iteracao;
		if ( tempo < 1000/FPS ) {
			SDL_Delay(1000/FPS - tempo);
		}

	} while ( tecla[SDLK_RETURN] != 1 );

	cont_aux = 0;

	//blitando o aviso anti drogas
	SDL_BlitSurface(aviso , NULL , tela , NULL);
	SDL_Flip(tela);
	SDL_Delay(1500);


	//loop da historia
	do {

		iteracao = SDL_GetTicks();

		//verificar eventos
		SDL_PollEvent(&evento);

		//recebe tecla pressionada
		tecla = SDL_GetKeyState(NULL);

		//verifica se deve sair da tela, se nao, conta o tempo para passar para o proximo menu
		if (evento.type == SDL_QUIT)
			exit(0);

		//espera um tempo para trocar imagens
		if ( esperar (FPS/2, &cont_aux) == 1 )
			menu_loop = (menu_loop == 1)? 0 : 1;

		//blitando as img da historia, com o pressione enter "piscando"
		if (menu_loop == 1){
			if ( SDL_BlitSurface ( historia1 , NULL , tela , NULL ) < 0 )
			    	printf ("Nao foi possivel blitar historia1:\n%s\n", SDL_GetError() );

		}else{
			if ( SDL_BlitSurface ( historia2 , NULL , tela , NULL ) < 0 )
				printf ("Nao foi possivel blitar historia2:\n%s\n", SDL_GetError() );
		}

		//atualiza tela
		SDL_Flip ( tela );

		//controlar o FPS
		tempo = SDL_GetTicks() - iteracao;
		if ( tempo < 1000/FPS ) {
			SDL_Delay(1000/FPS - tempo);
		}

	} while ( tecla[SDLK_RETURN] != 1 && tecla[SDLK_ESCAPE] != 1 );

	menu_loop = 1;


	/*MENU PRINCIPAL*/
	menu_principal:
	cont_aux = 0;

	if (menu_loop != 0 ) {
		Mix_PlayChannel ( 3, sommenu, -1 );
		Mix_Volume (3, 30);
	}
		
	while(menu_loop != 0) {
		
		//iteracao = SDL_GetTicks();

		tecla = SDL_GetKeyState(NULL);

		//verifica os eventos se necessario
		if (evento.type != SDL_MOUSEBUTTONUP)
			SDL_PollEvent(&evento);
		else
			evento.type = 0;

		//verifica se deve sair do jogo
		if (evento.type == SDL_QUIT)
			exit(0);

		//tela principal
		if(menu_loop == 1) {
			if ( SDL_BlitSurface( menu , NULL , tela , NULL) < 0 )
				printf ("Nao foi possivel blitar menu:\n%s\n", SDL_GetError() );
			SDL_Flip(tela);
				
			//verificando as açoes do mouse dentro do menu
			if (evento.type == SDL_MOUSEBUTTONUP && evento.button.button == SDL_BUTTON_LEFT) {
				mousex = evento.button.x;
				mousey = evento.button.y;

				//verificar se apertou o botao para iniciar o jogo, se sim troca a variavel
				//pra 0 para sair do loop do menu
				if(mousex > menu_inicio.x && mousex < menu_inicio.x+menu_inicio.w &&
				   mousey > menu_inicio.y && mousey < menu_inicio.y+menu_inicio.h) {
						menu_loop = 5; // 5 para ir para a tela de selecao de modo
				}

				//verifica se apertou em cima dos creditos, se sim troca a variavel pra 2
				//e fica blitando a img dos creditos ate voltar ao menu
				else if(mousex > menu_creditos.x && mousex < menu_creditos.x+menu_creditos.w &&
					mousey > menu_creditos.y && mousey < menu_creditos.y+menu_creditos.h) {
						menu_loop = 2;
				}

				//verifica se apertou em cima dos recordes, se sim troca a variavel pra 3
				//e fica blitando a img dos recordes ate voltar ao menu
				else if(mousex > menu_recordes.x && mousex < menu_recordes.x+menu_recordes.w &&
					mousey > menu_recordes.y && mousey < menu_recordes.y+menu_recordes.h) {
						menu_loop = 3;
				}

				//botao de sair
				else if(mousex > menu_sair.x && mousex < menu_sair.x+menu_sair.w &&
					mousey > menu_sair.y && mousey < menu_sair.y+menu_sair.h ) {
						exit(0);
				}
			}

		}//chave que fecha o switch da vericacao do mouse no menu


		//blita a tela de creditos se a variavel for 2(quando aperta o botao creditos ela troca pra 2)
		else if(menu_loop == 2) {
			if ( SDL_BlitSurface( creditos , NULL , tela , NULL) < 0 )
				printf ("Nao foi possivel blitar creditos:\n%s\n", SDL_GetError() );
			SDL_Flip(tela);

			if ( evento.type == SDL_MOUSEBUTTONUP && evento.button.button == SDL_BUTTON_LEFT ) {
				mousex = evento.button.x;
				mousey = evento.button.y;

				//verificar se apertou o botao para voltar a tela menu.
				if(mousex > menu_voltar.x && mousex < menu_voltar.x+menu_voltar.w &&
				   mousey > menu_voltar.y && mousey < menu_voltar.y+menu_voltar.h) {
						menu_loop = 1;
							
				}
			}//chave que fecha o switch da vericacao do mouse na tela creditos

			//voltar para menu principal ao apertar esc
			else if ( tecla[SDLK_ESCAPE] == 1)
				menu_loop = 1;
					
		}//chave que fecha o if de de blit dos creditos.

		//blita a tela dos recordes se a variavel for 3(quando aperta os recordes ela muda pra 3)
		else if(menu_loop == 3) {

			if (cont_aux == 0) {
				//declara o valor dos surfaces
				mostrar_pontuacao(dificuldade);
				cont_aux = 1;

				//declara as surfaces das dificuldades
				if ( !( texto_mudardificuldade[0].surface = (0 == dificuldade)? TTF_RenderText_Solid (pixel_25, "Debil Mental", VERDE) :
												TTF_RenderText_Solid (pixel_25, "Debil Mental", BRANCO) ) ) {
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );
				}
				if ( !( texto_mudardificuldade[1].surface = (1 == dificuldade)? TTF_RenderText_Solid (pixel_25, "Facil", VERDE) :
												TTF_RenderText_Solid (pixel_25, "Facil", BRANCO) ) ) {
						printf ( "Nao foi possivel declarar texto_mudardificuldade[1]:\n%s\n", TTF_GetError() );
				}
				if ( !( texto_mudardificuldade[2].surface = (2 == dificuldade)? TTF_RenderText_Solid (pixel_25, "HueBR", VERDE) :
												TTF_RenderText_Solid (pixel_25, "HueBR", BRANCO) ) ) {
						printf ( "Nao foi possivel declarar texto_mudardificuldade[2]:\n%s\n", TTF_GetError() );
				}

				//blita o fundo
				if ( SDL_BlitSurface( tela_recordes , NULL , tela , NULL) < 0 )
					printf ("Nao foi possivel blitar recordes:\n%s\n", SDL_GetError() );

				//blita os botoes de troca de recorde
				for (i = 0; i < 3; i++) {
					if ( SDL_BlitSurface( texto_mudardificuldade[i].surface , NULL , tela , &texto_mudardificuldade[i].pos) < 0 )
						printf ("Nao foi possivel blitar tela_recordes:\n%s\n", SDL_GetError() );
				}

				//blita os recordes
				for (i = 0; i < PONTUACOES; i++) {
					if ( SDL_BlitSurface( texto_recordes[i].surface , NULL , tela , &texto_recordes[i].pos) < 0 )
						printf ("Nao foi possivel blitar recordes:\n%s\n", SDL_GetError() );
				}

				SDL_Flip(tela);

				//limpar memoria para evitar vazamentos
				for (i = 0; i < PONTUACOES; i++) {
					SDL_FreeSurface(texto_recordes[i].surface);
					if (i < 3)
						SDL_FreeSurface(texto_mudardificuldade[i].surface);
				}

			}

			//evento para verificar os botoes dentro da tela de recordes
			if ( evento.type == SDL_MOUSEBUTTONUP && evento.button.button == SDL_BUTTON_LEFT ) {
				mousex = evento.button.x;
				mousey = evento.button.y;

				//VERIFICA SE APERTOU EM CIMA DO DEBIL E FAZ A TABELA MUDAR
				if(mousex >= texto_mudardificuldade[0].pos.x && mousex <= texto_mudardificuldade[0].pos.x+texto_mudardificuldade[0].pos.w &&
				   mousey >= texto_mudardificuldade[0].pos.y && mousey <= texto_mudardificuldade[0].pos.y+texto_mudardificuldade[0].pos.h) {

					//declara o valor dos surfaces
					mostrar_pontuacao(0);

					//declara as surfaces das dificuldades
					if ( !( texto_mudardificuldade[0].surface = TTF_RenderText_Solid (pixel_25, "Debil Mental", VERDE) ) )
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );

					if ( !( texto_mudardificuldade[1].surface = TTF_RenderText_Solid (pixel_25, "Facil", BRANCO) ) )
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );

					if ( !( texto_mudardificuldade[2].surface = TTF_RenderText_Solid (pixel_25, "HueBR", BRANCO) ) )
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );

					//blita o fundo
					if ( SDL_BlitSurface( tela_recordes , NULL , tela , NULL) < 0 )
						printf ("Nao foi possivel blitar recordes:\n%s\n", SDL_GetError() );

					//blita os botoes de troca de recorde
					for (i = 0; i < 3; i++) {
						if ( SDL_BlitSurface( texto_mudardificuldade[i].surface , NULL , tela , &texto_mudardificuldade[i].pos) < 0)
							printf ("Nao foi possivel blitar tela_recordes:\n%s\n", SDL_GetError() );
					}

					//blita os recordes
					for (i = 0; i < PONTUACOES; i++) {
						if ( SDL_BlitSurface( texto_recordes[i].surface , NULL , tela , &texto_recordes[i].pos) < 0 )
							printf ("Nao foi possivel blitar recordes:\n%s\n", SDL_GetError() );
					}

					SDL_Flip(tela);

					//limpar memoria para evitar vazamentos
					for (i = 0; i < PONTUACOES; i++) {
						SDL_FreeSurface(texto_recordes[i].surface);
						if (i < 3)
							SDL_FreeSurface(texto_mudardificuldade[i].surface);
					}
				}

				//VERIFICA SE APERTOU EM CIMA DO FACIL E FAZ A TABELA MUDAR
				else if(mousex >= texto_mudardificuldade[1].pos.x &&
					mousex <= texto_mudardificuldade[1].pos.x+texto_mudardificuldade[1].pos.w &&
					mousey >= texto_mudardificuldade[1].pos.y &&
					mousey <= texto_mudardificuldade[1].pos.y+texto_mudardificuldade[1].pos.h) {
							
					//declara o valor dos surfaces
					mostrar_pontuacao(1);

					//declara as surfaces das dificuldades
					if ( !( texto_mudardificuldade[0].surface = TTF_RenderText_Solid (pixel_25, "Debil Mental", BRANCO) ) )
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );

					if ( !( texto_mudardificuldade[1].surface = TTF_RenderText_Solid (pixel_25, "Facil", VERDE) ) )
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );

					if ( !( texto_mudardificuldade[2].surface = TTF_RenderText_Solid (pixel_25, "HueBR", BRANCO) ) )
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );

					//blita o fundo
					if ( SDL_BlitSurface( tela_recordes , NULL , tela , NULL) < 0 )
						printf ("Nao foi possivel blitar tela_recordes:\n%s\n", SDL_GetError() );

					//blita os botoes de troca de recorde
					for (i = 0; i < 3; i++) {
						if ( SDL_BlitSurface( texto_mudardificuldade[i].surface , NULL , tela , &texto_mudardificuldade[i].pos) < 0)
							printf ("Nao foi possivel blitar recordes:\n%s\n", SDL_GetError() );
					}

					//blita os recordes
					for (i = 0; i < PONTUACOES; i++) {
						if ( SDL_BlitSurface( texto_recordes[i].surface , NULL , tela , &texto_recordes[i].pos) < 0 )
							printf ("Nao foi possivel blitar recordes:\n%s\n", SDL_GetError() );
					}

					SDL_Flip(tela);

					//limpar memoria para evitar vazamentos
					for (i = 0; i < PONTUACOES; i++) {
						SDL_FreeSurface(texto_recordes[i].surface);
						if (i < 3)
							SDL_FreeSurface(texto_mudardificuldade[i].surface);
					}
				}


				//VERIFICA SE APERTOU EM CIMA DO HUEBR E FAZ A TABELA MUDAR
				else if(mousex >= texto_mudardificuldade[2].pos.x &&
					mousex <= texto_mudardificuldade[2].pos.x+texto_mudardificuldade[1].pos.w &&
					mousey >= texto_mudardificuldade[2].pos.y &&
					mousey <= texto_mudardificuldade[2].pos.y+texto_mudardificuldade[1].pos.h) {
									
					//declara o valor dos surfaces
					mostrar_pontuacao(2);

					//declara as surfaces das dificuldades
					if ( !( texto_mudardificuldade[0].surface = TTF_RenderText_Solid (pixel_25, "Debil Mental", BRANCO) ) )
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );

					if ( !( texto_mudardificuldade[1].surface = TTF_RenderText_Solid (pixel_25, "Facil", BRANCO) ) )
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );

					if ( !( texto_mudardificuldade[2].surface = TTF_RenderText_Solid (pixel_25, "HueBR", VERDE) ) )
						printf ( "Nao foi possivel declarar texto_mudardificuldade[0]:\n%s\n", TTF_GetError() );

					//blita o fundo
					if ( SDL_BlitSurface( tela_recordes , NULL , tela , NULL) < 0 )
						printf ("Nao foi possivel blitar tela_recordes:\n%s\n", SDL_GetError() );

					//blita os botoes de troca de recorde
					for (i = 0; i < 3; i++) {
						if ( SDL_BlitSurface( texto_mudardificuldade[i].surface , NULL , tela , &texto_mudardificuldade[i].pos) < 0)
							printf ("Nao foi possivel blitar recordes:\n%s\n", SDL_GetError() );
					}

					//blita os recordes
					for (i = 0; i < PONTUACOES; i++) {
						if ( SDL_BlitSurface( texto_recordes[i].surface , NULL , tela , &texto_recordes[i].pos) < 0 )
							printf ("Nao foi possivel blitar recordes:\n%s\n", SDL_GetError() );
					}

					SDL_Flip(tela);

					//limpar memoria para evitar vazamentos
					for (i = 0; i < PONTUACOES; i++) {
						SDL_FreeSurface(texto_recordes[i].surface);
						if (i < 3)
							SDL_FreeSurface(texto_mudardificuldade[i].surface);
					}

				}

				//verificar se apertou o botao para voltar a tela menu.
				else if(mousex > menu_voltar.x && mousex < menu_voltar.x+menu_voltar.w &&
					mousey > menu_voltar.y && mousey < menu_voltar.y+menu_voltar.h) {
						menu_loop = 1;
						cont_aux = 0;
				}
			}//chave que fecha o switch da vericacao do mouse na tela recordes

			//voltar para menu principal ao apertar esc
			else if ( tecla[SDLK_ESCAPE] == 1)
				menu_loop = 1;

		}//chave que fecha o if de de blit dos recordes

		//blita a tela para escolha da dificuldade quando a variavel for 4
		else if (menu_loop == 4) {
			if ( SDL_BlitSurface( tela_dificuldade , NULL , tela , NULL ) < 0 )
				printf ("Nao foi possivel blitar tela_dificuldade:\n%s\n", SDL_GetError() );
			SDL_Flip(tela);

			//evento para verificar o botao voltar dentro da tela de creditos
			if ( evento.type == SDL_MOUSEBUTTONUP && evento.button.button == SDL_BUTTON_LEFT ) {
				SDL_PollEvent(&evento);
				mousex = evento.button.x;
				mousey = evento.button.y;

				//se apertou em cima da dificuldade debil
				//troca parametros e termina o loop do menu
				if(mousex > dificuldade_debil.x && mousex < dificuldade_debil.x+dificuldade_debil.w &&
				   mousey > dificuldade_debil.y && mousey < dificuldade_debil.y+dificuldade_debil.h) {

						//determina a dificuldade
						dificuldade = 0;

						menu_loop = 0; //para sair do loop de menu
				}

				//se apertou em cima da dificuldade facil
				//troca parametros e termina o loop do menu
				else if(mousex > menu_creditos.x && mousex < menu_creditos.x+menu_creditos.w &&
					mousey > menu_creditos.y && mousey < menu_creditos.y+menu_creditos.h) {
						//determina a dificuldade
						dificuldade = 1;
						menu_loop = 0; //para sair do loop de menu
				}

				//se apertou em cima da dificuldade huebr
				//troca parametros e termina o loop do menu
				else if(mousex > menu_recordes.x && mousex < menu_recordes.x+menu_recordes.w &&
					mousey > menu_recordes.y && mousey < menu_recordes.y+menu_recordes.h) {

						//determina a dificuldade
						dificuldade = 2;

						menu_loop = 0; //para sair do loop de menu
				}

				//verificar se apertou o botao para voltar a tela menu e retornar a ela.
				else if(mousex > menu_voltar.x && mousex < menu_voltar.x+menu_voltar.w &&
					mousey > menu_voltar.y && mousey < menu_voltar.y+menu_voltar.h) {
						menu_loop = 5; //para voltar para menu de selecao de modo
				}
			}//chave que fecha o switch da vericacao do mouse na tela dificuldade

			//voltar para menu de selecao de modo ao apertar esc
			else if ( tecla[SDLK_ESCAPE] == 1)
				menu_loop = 5;

		}//chave que fecha o if de de blit dos dificuldade

		//LOOP PARA ESCOLHER O MODO DE JOGO
		else if(menu_loop == 5) {
			if ( SDL_BlitSurface( tela_mododejogo , NULL , tela , NULL) < 0 )
				printf ("Nao foi possivel blitar tela_mododejogo:\n%s\n", SDL_GetError() );
			SDL_Flip(tela);

			if ( evento.type == SDL_MOUSEBUTTONUP && evento.button.button == SDL_BUTTON_LEFT ) {
				mousex = evento.button.x;
				mousey = evento.button.y;

				//se apertou em cima do classico
				//muda o parametro e vai pra tela pra mudar a dificuldade
				if (mousex > modo_classico.x && mousex < modo_classico.x+modo_classico.w &&
					mousey > modo_classico.y && mousey < modo_classico.y+modo_classico.h) {
						modo_jogo = 0;
						menu_loop = 4;
				}
				//se apertou em cima do contra o tempo
				//muda o parametro e vai pra tela pra mudar a dificuldade
				else if (mousex > modo_contraotempo.x && mousex < modo_contraotempo.x+modo_contraotempo.w &&
						 mousey > modo_contraotempo.y && mousey < modo_contraotempo.y+modo_contraotempo.h) {
							modo_jogo = 1;
							menu_loop = 4;
				}

				//verificar se apertou o botao para voltar a tela menu.
				else if(mousex > menu_voltar.x && mousex < menu_voltar.x+menu_voltar.w &&
						mousey > menu_voltar.y && mousey < menu_voltar.y+menu_voltar.h) {
							menu_loop = 1;
				}
			}
			
			//voltar para menu principal ao apertar esc
			else if ( tecla[SDLK_ESCAPE] == 1)
				menu_loop = 1;
			
		}//chave que fecha o switch da vericacao do mouse na tela de modo de jogo
		
		/*
		//controlar o FPS
		tempo = SDL_GetTicks() - iteracao;
		if ( tempo < 1000/FPS ) {
			SDL_Delay(1000/FPS - tempo);
		}
		*/
		
	}//chave que fecha o while do loop do menu

	//Para a musica do menu gradativamente
	Mix_FadeOutChannel (3, 100);
	SDL_Delay (50);

	//Toca o som antes de iniciar a partida
	Mix_PlayChannel (5, missao, 0);
	//define o volume do som antes da partida começar
	Mix_Volume (5, 50);
	
	//BLITANDO TELA DE CONTROLES ANTES DO INICIO DO JOGO
	SDL_Delay ( 500 ); 
	SDL_BlitSurface (controles , NULL , tela , NULL);
	SDL_Flip ( tela );
	SDL_Delay ( 4500 );
	



	/*FASE*/
	fase:
	//determinar valor das variaveis necessarias para inicio da fase (carregar.c)
	carregar_fase();

	if (Mix_PlayingMusic() == 0) {
		//poe musica de fundo pra tocar
		Mix_PlayMusic (theme, -1);
		//define o volume da musica de fundo
		Mix_VolumeMusic (30);
	}else{
		Mix_ResumeMusic();
	}



	/*LOOP PRINCIPAL*/
	do {

		//iniciar contagem de frames
		iteracao = SDL_GetTicks();

		//efetuar contagem de tempo
		if (frame < FPS) {
			frame++;
		}else{
			frame = 0;

			//verifica se o jogador ainda nao terminou a fase
			if (oficial_pos.y > escadafinal_col.y) {

				//contagem progressiva se no modo de jogo por vidas
				if (modo_jogo == 0 && NVIDAS > 0) {
						seg++;
				//contagem regressiva se no modo de jogo por tempo
				}else if (seg > 0){
						seg--;
				}

			}

		}

		//verificar eventos
		SDL_PollEvent(&evento);

		//receber input
		tecla = SDL_GetKeyState(NULL);

		//verificar input (input.c) e status do jogador
		if ( input(tecla) == 0 && ( status_jogador == 2 || status_jogador > 5) ) {
			//retorna o sprite para idle se o jogador nao esta apertando nada
			oficial_sprite.x = 0;
		}


		//se o jogador chegou ao final da fase mas ainda nao subiu a ultima plataforma
		if ( colisao(&oficial_col, &escadafinal_col) == 1 && oficial_pos.y > escadafinal_col.y && NVIDAS > 0 ) {

			subir_descer(1, &escadafinal_col);
			status_jogador = 1;

		}			

		//coloca oficial em idle se ja subiu a plataforma e termina o jogo apos um tempo
		else if (oficial_pos.y == escadafinal_col.y) {
			oficial_sprite.x = 0;
			oficial_sprite.y = 0;
			if (esperar(60, &cont_gameover) == 1) {
				//termina o jogo
				Mix_PlayChannel (9, somwin, 0);
				Mix_Volume (9, 128);
				gameover = 1;
			}
		}

		//impede o movimento do jogador e termina o jogo apos um tempo
		else if ( modo_jogo == 0 && NVIDAS < 1 || modo_jogo == 1 && seg == 0) {
			hit(0);
			if (esperar(60, &cont_gameover) == 1) {
				//toca o som do gameover
				Mix_PlayChannel (6, somgo, 0);
				Mix_Volume (6, 50);
				gameover = 2;
			}
		}

		//verifica se alguma pedra esta na fila
		else if (crack_cont == NCRACK) {

			//determina proxima na fila
			for (i = 0; i < NCRACK; i++) {
				if ( crack_velo[i] == 0 ) {
					crack_cont = i;
					break;
				}
			}

		}else{

			//determina valor a ser esperado
			if ( crack_rnd[crack_cont] == 0 ) {
				crack_rnd[crack_cont] = randomizar(MAXTEMP_CRACK + 1 - MINTEMP_CRACK) + MINTEMP_CRACK;
			}

			//da nova velocidade a pedra apos passado o tempo
			if ( esperar ( crack_rnd[crack_cont], &cont_aux ) == 1 ) {

				//posiciona pedra a frente do beira
				crack_pos[crack_cont].x = beira_pos.x + beira_pos.w;

				//randomiza velocidade da pedra
				crack_velo[crack_cont] = randomizar(MAXVELO_CRACK + 1 - MINVELO_CRACK) + MINVELO_CRACK;

				//libera espaco na fila
				crack_rnd[crack_cont] = 0;
				crack_cont = NCRACK;

			}

		}

		//mover pedra de crack (eventos.c)
		for (i = 0; i < NCRACK; i++) {
			mover_crack (&crack_pos[i], &crack_sprite[i], &crack_velo[i], &crack_status[i], &crack_chao[i]);
		}

		//atualiza posicao das colisoes
		//oficial
		oficial_col.y = oficial_pos.y + COMP_OFICIALY;
		oficial_col.x = oficial_pos.x + SPRITE_OFICIALX/3;
		//pedra de crack
		for (i = 0; i < NCRACK; i++) {
			crack_col[i].x = crack_pos[i].x+5;
			crack_col[i].y = crack_pos[i].y;
		}


		//verifica colisoes do oficial ou de seu ataque (eventos.c)
		verificar_col ();

		//verifica quando jogador deve cair (eventos.c)
		if ( cair(&oficial_col) == 1 && status_jogador != 4 && status_jogador != 0 ) {

			//determina novo chao e inicia queda
			chao += SPRITE_ESCADAY;
			status_jogador = 4;

			//zera a diminuicao de score
			score_div = 1;
			score_pedraspuladas = 0;

		}

		//verificar se jogador esta pulando/caindo e chamar funcao em caso positivo (input.c)
		else if ( status_jogador == 3 || status_jogador == 4 || status_jogador == 0 ) {
			pular_bater(0);
		}

		//verificar se o jogador esta batendo com o pau (input.c)
		else if (status_jogador == 5) {
			pular_bater(1);
		}

		//verificar se o jogador esta com o pau na mao (eventos.c)
		if ( status_jogador == 2 || status_jogador == 5 ) {

			//tirar o pau apos passado o tempo (eventos.c)
			if ( esperar (pau_tempo, &cont_pauaux) == 1 ) {

				//garante que a funcao sera executada apos passado o tempo
				cont_pauaux = pau_tempo;

				if (status_jogador != 5) {

					//volta ao status normal
					status_jogador = 10;

					//remove a colisao com o ataque da tela
					ataque.x = 0;
					ataque.y = 0;

					//determina sprite do oficial
					//se oficial esta virado para a direita
					if ( oficial_sprite.y == 2*SPRITE_OFICIALY ||
					     oficial_sprite.y == 4*SPRITE_OFICIALY && oficial_sprite.x <= 3*SPRITE_OFICIALX) {

						oficial_sprite.y = 0;

					}
					//se o oficial esta virado para a esquerda
					else {
						oficial_sprite.y = SPRITE_OFICIALY;
					}

					//permite o inicio de nova contagem
					cont_pauaux = 0;

				}

			}

			//cooldown do ataque
			aux_paucool = (aux_paucool == 1 && status_jogador == 2) ? !( esperar (ATAQUE_COOLDOWN, &cont_paucool) ) : 0;

		}

		//reseta multiplicador de score e remove pontuacao ganha da tela se necessario
		if ( score_mult > 1 ) {
			if ( esperar (INTERVALO_COMBO, &score_tempaux) == 1 ) {

				//reseta multiplicador
				score_mult = 1;

			}
		}

		if ( texto_printscore.pos.y != 0 && esperar( 28, &printscore_temp ) == 1 ) {

				//remove pontuacao ganha da tela
				texto_printscore.pos.x = 0;
				texto_printscore.pos.y = 0;

		}

		//animacao do beira mar
		beira_sprite = selecionar_sprite (beira_sprite, 'x', 0, 0, 12, VELOANIM_BEIRA);

		//animacao da crianca
		crianca_sprite = selecionar_sprite (crianca_sprite, 'x', 0, 0, 3, VELOANIM_CRIANCA);

		//blitar elementos na tela (janela.c)
		blit_tela();

		//blitar texto na tela (janela.c)
		blit_texto();

		SDL_Flip (tela);

		//controlar o FPS
		tempo = SDL_GetTicks() - iteracao;
		if ( tempo < 1000/FPS ) {
			SDL_Delay(1000/FPS - tempo);
		}
		// printf ("Tempo do loop: %d\n", tempo);	//debug

	} while ( gameover == 0 && evento.type != SDL_QUIT);

	//para musica
	Mix_PauseMusic();
	Mix_RewindMusic();

	/*FIM DE JOGO*/
	//jogador ganhou
	if (gameover == 1) {

		//ajusta posicao do texto na tela
		for (i = 2; i < 7; i += 2) {
			texto_recordes[i].pos.x += 310;
		}
		texto_recordes[4].pos.x -= 10;

		//blita tela
		if ( SDL_BlitSurface (ganhou, NULL, tela, NULL) < 0 )
			printf ("Nao foi possivel blitar ganhou:\n%s\n", SDL_GetError() );

		//joga score na string
		sprintf (string_pontuacao, "PONTOS: %8d", score);

		//cria surface com o score
		if ( !( texto_score.surface = TTF_RenderText_Solid (pixel_25, string_pontuacao, VERDE) ) )
			printf ("Nao foi possivel declarar texto_tempo.surface:\n%s\n", TTF_GetError() );

		//blita score
		if ( SDL_BlitSurface (texto_score.surface, NULL, tela, &texto_recordes[2].pos) < 0 )
			printf ("Nao foi possivel blitar texto_score.surface:\n%s\n", SDL_GetError() );

		//limpa memoria
		SDL_FreeSurface (texto_score.surface);

		//se jogou modo de jogo por tempo
		if (modo_jogo == 1) {

			//joga bonus de tempo na string
			sprintf (string_pontuacao, "%+02ds %+12d", seg, seg*SCORE_TEMPBONUS);

			//aumenta o score de acordo com o bonus de tempo
			score = (score + seg*SCORE_TEMPBONUS < MAX_SCORE) ? score + seg*SCORE_TEMPBONUS : MAX_SCORE;

		}else{

			//coloca bonus das vidas em uma variavel auxiliar
			cont_aux = 5500*NVIDAS/MAX_VIDAS;

			//joga bonus de tempo na string
			if (NVIDAS > 1)
				sprintf (string_pontuacao, "%+d VIDAS: %+7d", NVIDAS, cont_aux);
			else
				sprintf (string_pontuacao, "+1 VIDA: %+8d", cont_aux);

			//aumenta o score de acordo com o bonus de tempo
			score = (score + cont_aux < MAX_SCORE) ? score + cont_aux : MAX_SCORE;

		}

		//cria surface com o bonus de tempo
		if ( !( texto_tempo.surface = TTF_RenderText_Solid (pixel_25, string_pontuacao, VERDE) ) )
			printf ("Nao foi possivel declarar texto_tempo.surface:\n%s\n", TTF_GetError() );
	
		//joga o score com o bonus na string
		sprintf (string_pontuacao, "FINAL: %9d", score);

		//cria surface com o score + bonus
		if ( !( texto_score.surface = TTF_RenderText_Solid (pixel_25, string_pontuacao, VERDE) ) )
			printf ("Nao foi possivel declarar texto_tempo.surface:\n%s\n", TTF_GetError() );

		//blita bonus
		if ( SDL_BlitSurface (texto_tempo.surface, NULL, tela, &texto_recordes[4].pos) < 0 )
			printf ("Nao foi possivel blitar texto_tempo.surface:\n%s\n", SDL_GetError() );

		//blita score final
		if ( SDL_BlitSurface (texto_score.surface, NULL, tela, &texto_recordes[6].pos) < 0 )
			printf ("Nao foi possivel blitar texto_score.surface:\n%s\n", SDL_GetError() );

		//limpa memoria
		SDL_FreeSurface (texto_score.surface);
		SDL_FreeSurface (texto_tempo.surface);

		//atualiza a tela
		SDL_Flip(tela);

		//desfaz ajuste de texto
		for (i = 2; i < 7; i += 2) {
			texto_recordes[i].pos.x -= 310;
		}
		texto_recordes[4].pos.x += 10;

		//aguarda input do jogador
		do {
			
			// iteracao = SDL_GetTicks();

			//recebe input
			tecla = SDL_GetKeyState(NULL);

			//verifica os eventos se necessario
			if (evento.type != SDL_MOUSEBUTTONUP)
				SDL_PollEvent(&evento);
			else
				evento.type = 0;

			//sai ao clicar no botao continuar
			if ( evento.type == SDL_MOUSEBUTTONUP && evento.button.button == SDL_BUTTON_LEFT ) {
				//verifica posicao do mouse
				mousex = evento.button.x;
				mousey = evento.button.y;

				//clica no botao continuar
				if(mousex > botao_continuar.x && mousex < botao_continuar.x+botao_continuar.w && mousey > botao_continuar.y &&
				   mousey < botao_continuar.y+botao_continuar.h) {
					//vai para evento de insercao de nome para pontuacao em (arquivo.c)
					inserir_score(score);
					
					//vai para a tela de recordes
					menu_loop = 3;
					goto menu_principal;
				}
			}
			//sai ao pressionar enter ou escape
			else if ( tecla[SDLK_RETURN] == 1 || tecla[SDLK_ESCAPE] == 1) {
				//vai para evento de insercao de nome para pontuacao em (arquivo.c)
				inserir_score(score);
					
				//vai para a tela de recordes
				menu_loop = 3;
				goto menu_principal;
			}
			else if (evento.type == SDL_QUIT) {
				exit(0);
			}
			
			/*
			//controlar o FPS
			tempo = SDL_GetTicks() - iteracao;
			if ( tempo < 1000/FPS ) {
				SDL_Delay(1000/FPS - tempo);
			}
			*/

		} while (1);

	}

	//jogador perdeu
	else {
		//Desliga o som da colisao com o crack
		Mix_HaltChannel (1);

		//toca o som do gameover
		Mix_PlayChannel (6, somgo, -1);
		Mix_Volume (6, 60);

		//blita bonus de tempo
		if ( SDL_BlitSurface (tela_gameover, NULL, tela, NULL) < 0 )
			printf ("Nao foi possivel blitar tela_gameover:\n%s\n", SDL_GetError() );
		//atualiza tela
		SDL_Flip(tela);

		//aguarda input do jogador
		do {

			//verifica os eventos se necessario
			if (evento.type != SDL_MOUSEBUTTONUP)
				SDL_PollEvent(&evento);
			else
				evento.type = 0;

			if ( evento.type == SDL_MOUSEBUTTONUP && evento.button.button == SDL_BUTTON_LEFT ) {
				//verifica posicao do mouse
				mousex = evento.button.x;
				mousey = evento.button.y;

				//clica no botao de tentar novamente
				if(mousex > botao_tentar_novamente.x && mousex < botao_tentar_novamente.x+botao_tentar_novamente.w &&
				   mousey > botao_tentar_novamente.y && mousey < botao_tentar_novamente.y+botao_tentar_novamente.h) {
					Mix_HaltChannel (6);
					//retorna para carregamento da fase
					goto fase;
				}

				//clica no botao de selecionar modo de jogo
				else if(mousex > botao_troca_mododejogo.x && mousex < botao_troca_mododejogo.x+botao_troca_mododejogo.w &&
					mousey > botao_troca_mododejogo.y && mousey < botao_troca_mododejogo.y+botao_troca_mododejogo.h) {
						Mix_HaltChannel (6);
						//retorna para o menu principal
						menu_loop = 5;
						goto menu_principal;
				}

				//clica no botao de trocar dificuldade
				else if(mousex > botao_troca_dificuldade.x && mousex < botao_troca_dificuldade.x+botao_troca_dificuldade.w &&
					mousey > botao_troca_dificuldade.y && mousey < botao_troca_dificuldade.y+botao_troca_dificuldade.h) {
						Mix_HaltChannel (6);
						//retorna para o menu principal
						menu_loop = 4;
						goto menu_principal;
				}

				//clica no botao de voltar para o menu
				else if(mousex > botao_menu_principal.x && mousex < botao_menu_principal.x+botao_menu_principal.w &&
					mousey > botao_menu_principal.y && mousey < botao_menu_principal.y+botao_menu_principal.h) {
						Mix_HaltChannel (6);
						//retorna para o menu principal
						menu_loop = 1;
						goto menu_principal;
				}
			}

		} while (evento.type != SDL_QUIT);

		Mix_HaltChannel (6);
	}

	exit(0);

}
