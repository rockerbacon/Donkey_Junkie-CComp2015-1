/*
Controle de todo input
*/

#include "includes.h"

/*ANDAR*/
void andar (comando) {
	
	//direita
	if (comando == 1) {

		//aumentar x se possivel (includes.h)
		if (oficial_col.x + oficial_col.w < RESX) {
			oficial_pos.x += VELO_OFICIAL;
		}

		//selecionar sprite do oficial somente se nao estiver em outra animacao mais importante (janela.h)
		if ( (oficial_sprite.y != 4*SPRITE_OFICIALY) && (oficial_sprite.x != 15*SPRITE_OFICIALX) ) {

			//animacao sem o pau
			if ( status_jogador != 2)
				oficial_sprite = selecionar_sprite (oficial_sprite, 'x', 1, 0, 14, VELOANIM_OFICIAL);
			//animacao com o pau
			else
				oficial_sprite = selecionar_sprite (oficial_sprite, 'x', 1, 2, 14, VELOANIM_OFICIAL);

		}				

	}

	//esquerda
	else {

		//diminuir x se possivel (includes.h)
		if (oficial_col.x > 0) {
			oficial_pos.x -= VELO_OFICIAL;
		}

		//selecionar sprite do oficial somente se nao estiver em outra animacao mais importante (janela.h)
		if ( (oficial_sprite.y != 4*SPRITE_OFICIALY) && (oficial_sprite.x != 15*SPRITE_OFICIALX) ) {

			//animacao sem o pau
			if ( status_jogador != 2)
				oficial_sprite = selecionar_sprite (oficial_sprite, 'x', 1, 1, 14, VELOANIM_OFICIAL);
			//animacao com o pau
			else
				oficial_sprite = selecionar_sprite (oficial_sprite, 'x', 1, 3, 14, VELOANIM_OFICIAL);

		}				

	}

}



/*PULAR OU BATER*/
void pular_bater (short int comando) {

	//variavel para auxiliar na contagem do tempo
	static unsigned short int cont_aux = 0;

	/*PULAR*/
	if (comando == 0) {
	
		//subida	
		if (status_jogador == 3) {

			//sobe o jogador ate a posicao maxima (includes.h)
			if (oficial_pos.y >= chao - SPRITE_OFICIALY - ALT_PULO) {

				//movimentacao do oficial no eixo y
				oficial_pos.y -= VELO_OFICIAL+2;

				/*ANIMACAO*/

				//determina o primeiro sprite a ser usado caso esteja virado para direita
				if ( (oficial_sprite.y == 0 || oficial_sprite.y == 2*SPRITE_OFICIALY) && oficial_sprite.x != 15*SPRITE_OFICIALX) {
					oficial_sprite.y = 4*SPRITE_OFICIALY;
					oficial_sprite.x = 9*SPRITE_OFICIALX;
				}

				//determina o primeiro sprite a ser usado caso esteja virado para esquerda
				else if ( (oficial_sprite.y == SPRITE_OFICIALY || oficial_sprite.y == 3*SPRITE_OFICIALY) && oficial_sprite.x != 15*SPRITE_OFICIALX) {
					oficial_sprite.y = 0;
					oficial_sprite.x = 15*SPRITE_OFICIALX;
				}

				//determina sprite caso ja esteja pulando e virado para direita
				else if ( oficial_sprite.y == 4*SPRITE_OFICIALY && oficial_sprite.x != 11*SPRITE_OFICIALX) {
	
						//se sprite 9 ou 10
						if ( (oficial_sprite.x == 9*SPRITE_OFICIALX || oficial_sprite.x == 10*SPRITE_OFICIALX) &&
						      esperar(VELOANIM_OFICIAL, &cont_aux) == 1) {
							oficial_sprite.x += SPRITE_OFICIALX;
						}

				}

				//determina sprite caso ja esteja pulando e virado para esquerda
				else if ( oficial_sprite.x == 15*SPRITE_OFICIALX && oficial_sprite.y != 2*SPRITE_OFICIALY) {

						//se sprite 0 ou 1
						if ( (oficial_sprite.y == 0 || oficial_sprite.y == SPRITE_OFICIALY) && esperar(VELOANIM_OFICIAL, &cont_aux) == 1) {
							oficial_sprite.y += SPRITE_OFICIALY;
						}

				}

			}else{

				//altera o status para iniciar a queda
				status_jogador = 4;

			}

		//descida
		}else if (status_jogador == 4 || status_jogador == 0) {

			//desce o jogador enquanto possivel
			if (oficial_pos.y < chao - SPRITE_OFICIALY) {
				oficial_pos.y += VELO_OFICIAL + 1;

				if (status_jogador != 0) {

					/*ANIMACAO*/

					//determina sprite caso esteja pulando
					//se virado para direita
					if ( oficial_sprite.y == 4*SPRITE_OFICIALY && oficial_sprite.x != 9*SPRITE_OFICIALX ) {

							//se sprite 10 ou 11
							if ( (oficial_sprite.x == 10*SPRITE_OFICIALX || oficial_sprite.x == 11*SPRITE_OFICIALX) &&
							      esperar(VELOANIM_OFICIAL, &cont_aux) == 1) {

								oficial_sprite.x -= SPRITE_OFICIALX;

							}

					}

					//se virado para esquerda
					else if ( oficial_sprite.x == 15*SPRITE_OFICIALX) {

							//se sprite 2 ou 1
							if ( (oficial_sprite.y == 2*SPRITE_OFICIALY || oficial_sprite.y == SPRITE_OFICIALY) &&
							      esperar(VELOANIM_OFICIAL, &cont_aux) == 1 ) {

								oficial_sprite.y -= SPRITE_OFICIALY;

							}

					}

					//determina sprite caso nao esteja pulando
					//quando virado para direita
					else if ( oficial_sprite.y == 0 || oficial_sprite.y == 2*SPRITE_OFICIALY ) {
						oficial_sprite.y = 4*SPRITE_OFICIALY;
						oficial_sprite.x = 9*SPRITE_OFICIALX;
					}

					//quando virado para esquerda
					else if ( oficial_sprite.y == SPRITE_OFICIALY || oficial_sprite.y == 3*SPRITE_OFICIALY ) {
						oficial_sprite.y = 0;
						oficial_sprite.x = 15*SPRITE_OFICIALX;
					}

				}

			//finaliza o pulo
			}else{

				//ajusta a posicao final
				oficial_pos.y = chao - SPRITE_OFICIALY;

				//se o jogador pode se mover
				if (status_jogador != 0) {

					//normaliza a movimentacao do jogador
					status_jogador = 10;
				
					//retorna sprite para y normal
					//se virado para direita
					if (oficial_sprite.y > 3*SPRITE_OFICIALY) {
						if ( status_jogador != 2 ) {
							oficial_sprite.y = 0;
						}else{
							oficial_sprite.y = 2*SPRITE_OFICIALY;
						}
					}

					//se virado para esquerda
					else{
						if ( status_jogador != 2 ) {
							oficial_sprite.y = SPRITE_OFICIALY;
						}else{
							oficial_sprite.y = 3*SPRITE_OFICIALY;
						}

						oficial_sprite.x = SPRITE_OFICIALX;

					}

				}

			}
		}
			
		
	}


	/*BATER*/
	else {
		
		//se o oficial esta virado para a direita e ainda nao iniciou a animacao
		if (oficial_sprite.y == 2*SPRITE_OFICIALY) {

			//determina o primeiro sprite
			oficial_sprite.x = 3*SPRITE_OFICIALX;
			oficial_sprite.y = 4*SPRITE_OFICIALY;

		}
		
		//se o oficial esta virado para a esquerda e ainda nao iniciou a animacao
		else if (oficial_sprite.y == 3*SPRITE_OFICIALY) {

			//determina o primeiro sprite
			oficial_sprite.x = 7*SPRITE_OFICIALX;
			oficial_sprite.y = 4*SPRITE_OFICIALY;

		}

		//se virado para a esquerda e no meio da animacao
		else if ( oficial_sprite.x > 4*SPRITE_OFICIALX && esperar (2*VELO_OFICIAL, &cont_aux) == 1 ) {

			//anima o oficial
			oficial_sprite = selecionar_sprite (oficial_sprite, 'x', 7, 4, -4, 1);

			//ajusta posicao x do oficial
			oficial_pos.x -= (oficial_sprite.x == 6*SPRITE_OFICIALX) ? 26 : 0;

			//determina colisao do ataque
			ataque.x = oficial_col.x - oficial_col.w;
			ataque.y = oficial_pos.y;

		}

		//se virado para a esquerda e no ultimo frame da animacao
		else if ( oficial_sprite.x == 4*SPRITE_OFICIALX && esperar(2*VELO_OFICIAL, &cont_aux) == 1 ) {

			//retorna para posicao idle
			oficial_sprite.y = 3*SPRITE_OFICIALY;
			oficial_sprite.x = 0;
			status_jogador = 2;

			//remove colisao do ataque
			ataque.x = 0;
			ataque.y = 0;

			//ajusta a posicao x do oficial
			oficial_pos.x += 26;

			//inicia cooldown do ataque
			aux_paucool = 1;

		}

		//se virado para a direita e no meio da animacao
		else if ( oficial_sprite.x > 0 && oficial_sprite.x < 4*SPRITE_OFICIALX && esperar (2*VELO_OFICIAL, &cont_aux) == 1 ) {

			//anima o oficial
			oficial_sprite = selecionar_sprite (oficial_sprite, 'x', 4, 4, 0, 1);

			//ajusta posicao x do oficial
			oficial_pos.x += (oficial_sprite.x == 2*SPRITE_OFICIALX) ? 26 : 0;

			//determina colisao do ataque
			ataque.x = oficial_col.x + oficial_col.w;
			ataque.y = oficial_pos.y;

		}

		//se virado para direita e no fim da animacao
		else if ( oficial_sprite.x == 0 && esperar(2*VELO_OFICIAL, &cont_aux) == 1 ) {
			
			//retorna para posicao idle
			oficial_sprite.y = 2*SPRITE_OFICIALY;
			oficial_sprite.x = 0;
			status_jogador = 2;

			//remove colisao do ataque
			ataque.x = 0;
			ataque.y = 0;

			//ajusta a posicao x do oficial
			oficial_pos.x -= 26;

			//inicia cooldown do ataque
			aux_paucool = 1;

		}

	}
	
			
}



/*SUBIR OU DESCER ESCADA*/
void subir_descer (short int comando, SDL_Rect *escada) {

	static short unsigned int min_anim;
	static short int max_anim;

	//subir
	if (comando == 1) {

		//sobe o jogador caso possivel
		if ( oficial_pos.y > (*escada).y) {

			oficial_pos.y -= VELO_OFICIAL;

			//animacao
			//determina primeiro sprite da animacao
			if ( !(oficial_sprite.x >= 12*SPRITE_OFICIALX && oficial_sprite.x <= 14*SPRITE_OFICIALX && oficial_sprite.y == 4*SPRITE_OFICIALY) ) {

				oficial_sprite.x = 12*SPRITE_OFICIALX;
				oficial_sprite.y = 4*SPRITE_OFICIALY;

				min_anim = 12;
				max_anim = 14;

			}
			//determina max_anim e min_anim para percorrer o eixo x de forma crescente
			else if ( oficial_sprite.x == 14*SPRITE_OFICIALX ) {
				min_anim = 14;
				max_anim = -12;
			}
			//determina max_anim e min_anim para percorrer o eixo x de forma decrescente
			else if ( oficial_sprite.x == 12*SPRITE_OFICIALX ) {
				min_anim = 12;
				max_anim = 14;
			}

			//determina proximo sprite (janela.c)
			oficial_sprite = selecionar_sprite (oficial_sprite, 'x', min_anim, 4, max_anim, 2*VELOANIM_OFICIAL);

		}

		//se nao for possivel, parar a subida
		else {

			//determina nova posicao do chao
			chao = (*escada).y + SPRITE_OFICIALY;

			//completa a subida
			oficial_pos.y = chao - SPRITE_OFICIALY;

			//zera a diminuicao de score
			score_div = 1;
			score_pedraspuladas = 0;

			//seleciona sprite final
			//virado para a esquerda
			if ( colisao (&oficial_col, &escada_col[0]) == 1 || colisao (&oficial_col, &escada_col[2]) == 1 ) {
				oficial_sprite.y = SPRITE_OFICIALY;
				oficial_sprite.x = 0;
			}
			//virado para a direita
			else{
				oficial_sprite.y = 0;
				oficial_sprite.x = 0;
			}

			//permite movimentacao normal do jogador
			status_jogador = 10;


		}

	}

	//descer
	else {

		//determina a nova posicao do chao
		chao = (*escada).y + (*escada).h;

		//desce o jogador caso possivel
		if ( oficial_pos.y < chao - SPRITE_OFICIALY ) {

			oficial_pos.y += VELO_OFICIAL;

			//animacao
			//determina primeiro sprite da animacao
			if ( oficial_sprite.y < 2*SPRITE_OFICIALY ) {

				oficial_sprite.x = 12*SPRITE_OFICIALX;
				oficial_sprite.y = 4*SPRITE_OFICIALY;

				max_anim = -12;
				min_anim = 14;

			}
			//determina max_anim e min_anim para percorrer o eixo x de forma crescente
			else if ( oficial_sprite.x == 12*SPRITE_OFICIALX ) {
				max_anim = 14;
				min_anim = 12;
			}
			//determina max_anim e min_anim para percorrer o eixo x de forma decrescente
			else if ( oficial_sprite.x == 14*SPRITE_OFICIALX ) {
				max_anim = -12;
				min_anim = 14;
			}

			//determina proximo sprite (janela.c)
			oficial_sprite = selecionar_sprite (oficial_sprite, 'x', min_anim, 4, max_anim, 2*VELOANIM_OFICIAL);

		}

		//se nao for possivel, parar a descida
		else {

			//coloca o jogador no chao
			oficial_pos.y = chao - SPRITE_OFICIALY;

			//zera a diminuicao de score
			score_div = 1;
			score_pedraspuladas = 0;

			//seleciona sprite final
			//virado para esquerda
			if ( colisao (&oficial_col, &escada_col[0]) == 1 || colisao (&oficial_col, &escada_col[2]) ) {

				oficial_sprite.y = SPRITE_OFICIALY;
				oficial_sprite.x = 0;

			//virado para direita
			}else{
				oficial_sprite.y = 0;
				oficial_sprite.x = 0;
			}

			//permite a movimentacao do jogador
			status_jogador = 10;

		}

	}

}



/*VERIFICAR INPUT*/
short int input (unsigned char *tecla) {

	short int pressiona = 0;

	static short int i;

	//suicidio
	if (tecla[SDLK_ESCAPE] == 1) {
		if (esperar(60, &cont_tecla) == 1) {
			if (modo_jogo == 0)
				NVIDAS = 0;
			else
				seg = 0;
			hit(0);
		}
	}else{
		cont_tecla = 0;
	}

	//se o jogador pode se mover
	if ( status_jogador != 0 ) {

		//subir escada (janela.c)
		if ( tecla[SDLK_UP] == 1 && status_jogador != 2 && status_jogador != 5 ) {

			//sobe escada
			for (i = 0; i < NESCADAS; i++) {
				if ( colisao (&oficial_col, &escada_col[i]) == 1 && chao > escada_pos[i].y ) {

					//impede o jogador de se mover no eixo x
					status_jogador = 1;

					//sobe o jogador
					subir_descer(1, &escada_col[i]);
					pressiona = 1;

				}
			}

		}


		//descer escada (janela.c)
		else if ( tecla[SDLK_DOWN] == 1 && status_jogador != 2 && status_jogador != 5 ) {

			//desce escada
			for (i = 0; i < NESCADAS; i++) {
				if ( colisao (&oficial_col, &escada_col[i]) == 1 && (oficial_pos.y == escada_col[i].y || status_jogador == 1)  ) {

					//impede o jogador de se mover no eixo x
					status_jogador = 1;

					//sobe o jogador
					subir_descer(0, &escada_col[i]);
					pressiona = 1;

				}
			}

		}

		//mover para direita
		else if ( tecla[SDLK_RIGHT] == 1 && status_jogador > 1 && status_jogador != 5 ) {
			andar(1);
			pressiona = 1;
		}

		//mover para esquerda	
		else if ( tecla[SDLK_LEFT] == 1 && status_jogador > 1 && status_jogador != 5 ) {
			andar(0);
			pressiona = 1;
		}

		/*DEBUG*/
		/*
		//altera modo de jogo
		if ( tecla[SDLK_e] == 1) {

			if (modo_jogo == 0) {
				modo_jogo = 1;
				seg = 0;
				min = 2;
			}else{
				modo_jogo = 0;
				seg = 0;
				min = 0;
			}
			NVIDAS = MAX_VIDAS;

		}
		*/

		// pular se status diferente de 2 ou bater se status igual a 2
		if ( tecla[SDLK_SPACE] == 1 ) {
			if (status_jogador > 5) {

				//funcao do pulo chamada em main.c
				status_jogador = 3;
				pressiona = 1;

			}

			else if (status_jogador == 2) {

				if (aux_paucool == 0) {

					//funcao de bater chamada em main.c
					status_jogador = 5;
					pressiona = 1;
					Mix_PlayChannel (6, somhit, 0);
					Mix_Volume (6, 25);

				}

			}

		}

	}

	/*DEBUG*/
	/*
	//descongelar jogador quando pressionar tecla F
	else if ( tecla[SDLK_f] == 1 ) {
		status_jogador = 10;
		NVIDAS = MAX_VIDAS;
	}
	*/

	return pressiona;

}
