#include "includes.h"

//espera um certo numero de frames, retorna 0 enquanto nao completar e 1 apos o fim da espera
int esperar (unsigned short int frames, unsigned short int *aux) {

	if (*aux >= frames) {
		*aux = 0;
		return 1;
	}
	else {
		(*aux)++;
		return 0;
	}

}



//verifica se objeto atingiu limite da plataforma
short int cair (SDL_Rect *objeto) {

	//se o objeto esta na segunda plataforma e esta fora dos limites dela
	if ( (*objeto).y <= RESY - SPRITE_ESCADAY - 16 && (*objeto).y >= RESY - 2*SPRITE_ESCADAY - 16 && (*objeto).x > RESX - LIM_PLAT ) {
		return 1;
	}

	//se o objeto esta na quarta plataforma e esta fora dos limites dela
	else if ( (*objeto).y <= RESY - 3*SPRITE_ESCADAY - 16 && (*objeto).x > RESX - LIM_PLAT ) {
		return 1;
	}	

	//se o objeto esta na terceira plataforma e esta fora dos limites dela
	else if ( (*objeto).y <= RESY - 2*SPRITE_ESCADAY - 16 && (*objeto).y >= RESY - 3*SPRITE_ESCADAY - 16 && (*objeto).x < LIM_PLAT - (*objeto).w ) {
		return 1;
	}
	
	//se objeto nao deve cair
	else{
		return 0;
	}

}



//anima o oficial apos levar hit e determina sua queda
void hit (short int colisao) {

	//se virado para direita 
	if ( (oficial_sprite.x != 15*SPRITE_OFICIALX && (oficial_sprite.y == 0 || oficial_sprite.y == 2*SPRITE_OFICIALY) ) ||
	     (oficial_sprite.y == 4*SPRITE_OFICIALY && oficial_sprite.x < 15*SPRITE_OFICIALX) ) {

		oficial_sprite.x = 15*SPRITE_OFICIALX;
		oficial_sprite.y = 3*SPRITE_OFICIALY;

	}

	//se virado para esquerda
	else if ( oficial_sprite.y == SPRITE_OFICIALY || oficial_sprite.y == 3*SPRITE_OFICIALY ||
		 ( oficial_sprite.y < 3*SPRITE_OFICIALY && oficial_sprite.x == 15*SPRITE_OFICIALX ) ) {

		oficial_sprite.x = 15*SPRITE_OFICIALX;
		oficial_sprite.y = 4*SPRITE_OFICIALY;

	}

	//determina novo chao caso necessario
	if ( status_jogador != 1 && chao < RESY - 16 && modo_jogo == 1 && colisao == 1) {

		chao += SPRITE_ESCADAY;

		//zera a diminuicao de score
		score_div = 1;
		score_pedraspuladas = 0;

	}

	//impede o jogador de se mover
	status_jogador = 0;
	cont_aux = 0;

	//remove colisao do ataque
	ataque.x = 0;
	ataque.y = 0;

	//tira pontos do jogador
	if (colisao == 1) {
		score_print = -1*SCORE_HIT;
		score = (score >= SCORE_HIT)? score+score_print : 0;
		printscore_temp = 0;
		//mostra a pontuacao perdida na tela
		texto_printscore.pos.x = oficial_pos.x + SPRITE_OFICIALX/2;
		texto_printscore.pos.y = oficial_pos.y + SPRITE_OFICIALY/2;
	}

}



//verificar colisao do oficial com pedras de crack
void verificar_col (void) {

	//variavel para auxiliar nos loops
	static short int i;
	//variavel para auxiliar na contagem de tempo
	static unsigned short int cont_aux = 0;

	//colisao com pedras
	for (i = 0; i < NCRACK; i++) {

		//colisao com o ataque do oficial
		if ( colisao ( &ataque, &crack_col[i] ) == 1) {

			//move o crack na colisao
			crack_pos[i].x = 0;
			crack_pos[i].y = RESY - SPRITE_CRACKD - 3*SPRITE_ESCADAY - 16;
			crack_velo[i] = 0;
			crack_status[i] = 0;

			//da pontuacao para o jogador
			score_print = (score_mult > 1) ? score_print + score_mult * SCORE_BATER : score_mult * SCORE_BATER;

			score = (score < MAX_SCORE - score_mult*SCORE_BATER) ? score + score_mult * SCORE_BATER : MAX_SCORE;
			score_mult++;
			score_tempaux = 0;
			printscore_temp = 0;

			//mostra a pontuacao ganha na tela
			texto_printscore.pos.x = ataque.x;
			texto_printscore.pos.y = ataque.y + SPRITE_OFICIALY/2;

		}

		//colisao com o oficial
		else if ( colisao ( &oficial_col, &crack_col[i] ) == 1 && status_jogador != 0 ) {

			//move o crack na colisao
			crack_pos[i].x = 0;
			crack_pos[i].y = RESY - SPRITE_CRACKD - 3*SPRITE_ESCADAY - 16;
			crack_velo[i] = 0;
			crack_status[i] = 0;

			//toca o som da colisao com o crack
			Mix_PlayChannel (1, som, 0);
			//define o volume do canal 1
			Mix_Volume (1, 25);

			//tira vida do jogador
			if (modo_jogo == 0)
				NVIDAS--;

			//animacao do oficial (eventos.c)
			hit (1);

		}

		//verificar se o jogador pulou a pedra
		else if ( oficial_col.x >= crack_col[i].x && oficial_col.x <= crack_col[i].x + crack_col[i].w && 
			   oficial_col.y < crack_col[i].y && crack_col[i].y < chao && (status_jogador == 3 || status_jogador == 4) && crack_status[i] == 0 ) {

			//toca o som da pontuação ganha
			Mix_PlayChannel (7, coin, 0);
			//define o volume do canal 7
			Mix_Volume (7, 40);

			//da pontuacao para o jogador
			score_print = (score_mult > 1) ? score_print + (int)(score_mult * SCORE_PULAR * score_div) : (int)(score_mult * SCORE_PULAR * score_div);

			score = (score < MAX_SCORE - SCORE_PULAR) ? (int)(score + score_mult * SCORE_PULAR * score_div) : MAX_SCORE;
			score_pedraspuladas += (score_mult == 1)? 1 : 0;
			score_mult++;
			if (score_pedraspuladas == DIM_PORPEDRAS) {
				score_div-= (score_div > DIM_SCOREDIV) ? DIM_SCOREDIV : 0;
				score_pedraspuladas = 0;
			}
			score_tempaux = 0;
			printscore_temp = 0;
			crack_status[i] = 2;

			//mostra a pontuacao ganha na tela
			texto_printscore.pos.x = oficial_col.x;
			texto_printscore.pos.y = oficial_pos.y + SPRITE_OFICIALY;

		}

	}

	//verifica se o oficial esta usando crack
	if ( (oficial_sprite.x == 15*SPRITE_OFICIALX) &&
	     (oficial_sprite.y == 3*SPRITE_OFICIALY || oficial_sprite.y == 4*SPRITE_OFICIALY) &&
	     (status_jogador == 0) ) {

		//espera 0.5s
		if ( esperar (FPS/2, &cont_aux) == 1 && oficial_pos.y == chao - SPRITE_OFICIALY) {

			if (NVIDAS > 0 || modo_jogo == 1) {

				//permite a movimentacao do jogador
				status_jogador = 10;

				//retorna o sprite para idle
				oficial_sprite.x = 0;
				oficial_sprite.y = (oficial_sprite.y == 4*SPRITE_OFICIALY) ? 1*SPRITE_OFICIALY : 0*SPRITE_OFICIALY;

			}

		}

	}

	//verificar colisao com o pau
	else if ( colisao (&oficial_col, &pau_pos) == 1 && status_jogador > 5 ) {

		//determina novo status e remove o pau da tela
		status_jogador = 2;
		pau_pos.y = 0;
		pau_pos.x = 0;

		//determina nova linha a ser usada pelos sprites
		oficial_sprite.y = (oficial_sprite.y == 0) ? 2*SPRITE_OFICIALY : 3*SPRITE_OFICIALY;

	}

}



//movimentar pedras de crack
void mover_crack (SDL_Rect *crack, SDL_Rect *sprite, short int *velo, short int *status, short int *plat) {

	//se a pedra nao deve cair (evento.c)
	if ( cair(crack) == 0 && *status != 1 ) {

		//verifica em qual direcao deve rolar
		//se esta na segunda ou quarta plataforma
		if ( (*crack).y == RESY - SPRITE_ESCADAY - 16 - SPRITE_CRACKD || (*crack).y == RESY - 3*SPRITE_ESCADAY - 16 - SPRITE_CRACKD ) {

			//animacao
			if (*velo > 0)
				*sprite = selecionar_sprite (*sprite, 'x', 0, 0, 5, VELOANIM_CRACK);

			//anda no eixo x
			(*crack).x += *velo;

		}

		//se esta na primeira ou terceira plataforma
		else {

			//animacao
			*sprite = selecionar_sprite (*sprite, 'x', 5, 0, 0, VELOANIM_CRACK);

			//se chegou ao fim da fase
			if ( (*crack).y == RESY - 16 - SPRITE_CRACKD && (*crack).x < 5 ) {

				//reseta posicao
				(*crack).x = 0;
				(*crack).y = RESY - SPRITE_CRACKD - 3*SPRITE_ESCADAY - 16;

				//zera velocidade
				*velo = 0;

			}else{

				//anda no eixo x
				(*crack).x -= *velo;

			}

		}

	}

	//se a pedra de crack deve cair
	else if ( *status != 1 ) {

		//altera o status da pedra
		*status = 1;

		//se esta na quarta plataforma
		if ( (*crack).y == RESY - 3*SPRITE_ESCADAY - SPRITE_CRACKD - 16 ) {
			*plat = RESY - 2*SPRITE_ESCADAY - SPRITE_CRACKD - 16;
		}

		//se esta na terceira plataforma
		else if ( (*crack).y == RESY - 2*SPRITE_ESCADAY - SPRITE_CRACKD - 16 ) {
			*plat = RESY - SPRITE_ESCADAY - SPRITE_CRACKD - 16;
		}

		//se esta na segunda plataforma
		else {
			*plat = RESY - SPRITE_CRACKD - 16;
		}

	}

	//se a pedra deve cair
	else {

		//desce a pedra enquanto necessario
		if ( (*crack).y < *plat ) {
			(*crack).y += 5;

			//se cai na terceira ou primeira plataforma
			if ( *plat == RESY - 2*SPRITE_ESCADAY - 16 - SPRITE_CRACKD || *plat == RESY - 16 - SPRITE_CRACKD ) {
				(*crack).x += 3;
			}
			//se esta na terceira plataforma
			else {
				(*crack).x -= 3;
			}

		}

		//para a descida
		else {
			(*crack).y = *plat;
			*status = 0;
		}

	}


}
