#include "includes.h"
#include <stdlib.h>

//cria um ponteiro com uma imagem otimizada
SDL_Surface* carregar_png (char *arquivo, short int transparencia) {

	//variavel auxiliar que carrega a imagem original na memoria
	SDL_Surface *original,
		    //variavel que carrega a imagem ja otimizada na memoria
		    *otimizada;

	//carrega a imagem original na memoria, verificando possiveis erros durante o processo
	if ( !( original = IMG_Load (arquivo) ) ) {

		printf ("Nao foi possivel carregar %s na memoria:\n%s\n", arquivo, SDL_GetError() );
		return NULL;

	}

	//converte imagem para formato nativo
	if (transparencia == 1) {
		if ( !( otimizada = SDL_DisplayFormatAlpha (original) ) ) {
			printf ("Nao foi possivel converter imagem %s para formato nativo mantendo transparencia:\n%s\n", arquivo, SDL_GetError() );
		}
	}else{
		if ( !( otimizada = SDL_DisplayFormat (original) ) ) {
			printf ("Nao foi possivel converter imagem %s para formato nativo:\n%s\n", arquivo, SDL_GetError() );
		}
	}

	SDL_FreeSurface (original);

	return otimizada;

}



/*VARIAVEIS ESTATICAS*/
void carregar_inicial (void) {

	short int i, j, primeiro;
	char aux[10];
	FILE *ler_arquivo;

	/*IMAGENS*/
	//declara a tela de  aviso anti drogas
	aviso = carregar_png ( "imagens/AVISO.png", 0 );

	//declara as telas de historia
	historia1 = carregar_png ( "imagens/HISTORIA1.png", 0 );
	historia2 = carregar_png ( "imagens/HISTORIA2.png", 0 );

	//declara as telas de abertura iniciais (com a diferença de cor do pressione enter)
	abertura1 = carregar_png ( "imagens/TELA_INICIAL_FINAL_1.png", 0 );
	abertura2 = carregar_png ( "imagens/TELA_INICIAL_FINAL_2.png", 0 );

	//declara a tela dos recordes
	tela_recordes = carregar_png ( "imagens/RECORDES.png", 0 );

	//declara a tela dos creditos
	creditos = carregar_png ( "imagens/CREDITOS_FINAL.png", 0 );

	//declara a tela dos controles
	controles = carregar_png ( "imagens/CONTROLES.png", 0 );

	//declara o menu principal
	menu = carregar_png ( "imagens/MENU_FINAL.png", 0 );

	//teclara tela de selecao de dificuldade
	tela_dificuldade = carregar_png ( "imagens/DIFICULDADE.png", 0);

	//declara a tela de modo de jogo
	tela_mododejogo = carregar_png ( "imagens/MODODEJOGO.png", 0 );

	//declara a tela de gameover
	tela_gameover = carregar_png ( "imagens/GAMEOVER.png", 0 );

	//declara a tela de vitoria
	ganhou = carregar_png ( "imagens/GANHOU.png", 0 );

	//declara a tela de digitar o nome
	digiteonome = carregar_png ( "imagens/DIGITE_O_NOME.png", 0 );

	//declara sprite da escada
	escada = carregar_png ( "sprites/escada.png", 1 );

	//declara sprite da escada quebrada
	escada_quebrada = carregar_png ("sprites/escada_quebrada.png", 1);

	//declara plano de fundo
	fundo = carregar_png ( "sprites/fundo.png", 0 );

	//declara sprite da ultima escada
	escadafinal = carregar_png ( "sprites/escada_men.png", 1 );

	//declara sprite sheet do oficial
	oficial = carregar_png ( "sprites/oficial.png", 1 );

	//declara sprite da pedra de crack
	crack = carregar_png ( "sprites/crack.png", 1 );

	//declara sprite da caixa de crack
	caixa = carregar_png ( "sprites/caixa.png", 1 );

	//declara sprite do beira mar
	beira = carregar_png ( "sprites/vilao.png", 1 );

	//declara sprite da crianca
	crianca = carregar_png ( "sprites/crianca.png", 1 );

	//declara sprite da vida
	vida = carregar_png ( "sprites/vida.png", 1 );

	//declara sprite do pau
	pau = carregar_png ( "sprites/pau.png", 1 );

	/*AUDIO*/
	//declara musica de fundo
	theme = Mix_LoadMUS ( "Audio/Tema.ogg" );

	//declara o som do crack
	som = Mix_LoadWAV ( "Audio/Crack.ogg" );

	//declara o som do menu
	sommenu = Mix_LoadWAV ("Audio/Menu.ogg");

	//declara o som do game over
	somgo = Mix_LoadWAV ("Audio/GameOver.ogg");

	//declara o som de inicio de jogo
	missao = Mix_LoadWAV ("Audio/Missao.ogg");

	//declara o som do ponto
	coin = Mix_LoadWAV ("Audio/Coin.ogg");

	//declara som do hit
	somhit = Mix_LoadWAV ("Audio/Pau.ogg");

	//declara som da vitoria
	somwin = Mix_LoadWAV ("Audio/SomVitoria.ogg");

	/*FONTES*/
	//inicializa a livraria ttf
	if (TTF_Init() < 0)
		printf ("Nao foi possivel inicializar a livraria ttf:\n%s\n", TTF_GetError() );

	//declara fonte e tamanho da fonte do score
	if ( !( texto_score.fonte = TTF_OpenFont("fonte/stocky.ttf", TAMANHO_FONTE_SCORE) ) )
		printf ("Nao foi possivel carregar fonte/stocky.ttf com tamanho %d:\n%s\n", TAMANHO_FONTE_SCORE, TTF_GetError() );

	//declara fonte e tamanho da pontuacao ganha
	if ( !( texto_printscore.fonte = TTF_OpenFont("fonte/froufrou.ttf", TAMANHO_FONTE_PRINTSCORE) ) )
		printf ("Nao foi possivel carregar fonte/froufrou.ttf com tamanho %d:\n%s\n", TAMANHO_FONTE_PRINTSCORE, TTF_GetError() );

	//declara fonte e tamanho do tempo
	if ( !( texto_tempo.fonte = TTF_OpenFont("fonte/froufrou.ttf", TAMANHO_FONTE_SCORE) ) )
		printf ("Nao foi possivel carregar fonte/froufrou.ttf com tamanho %d:\n%s\n", TAMANHO_FONTE_SCORE, TTF_GetError() );

	if ( !( pixel = TTF_OpenFont("fonte/ponderosa.ttf", TAMANHO_FONTE_RECORDES) ) )
		printf ("Nao foi possivel carregar fonte/pixel.ttf com tamanho %d:\n%s\n", TAMANHO_FONTE_RECORDES, TTF_GetError() );

	if ( !( pixel_25 = TTF_OpenFont("fonte/pixel.ttf", TAMANHO_FONTE_MUDARECORDES) ) )
		printf ("Nao foi possivel carregar fonte/pixel.ttf com tamanho %d:\n%s\n", TAMANHO_FONTE_MUDARECORDES, TTF_GetError() );

	/*RECTS*/
	//posicao do score na tela
	texto_score.pos.x = POS_SCOREX;
	texto_score.pos.y = POS_SCOREY;
	texto_score.pos.w = POS_SCOREW;
	texto_score.pos.h = POS_SCOREH;

	//posicao do tempo na tela
	texto_tempo.pos.x = POS_TEMPOX;
	texto_tempo.pos.y = POS_TEMPOY;
	texto_tempo.pos.w = POS_TEMPOW;
	texto_tempo.pos.h = POS_TEMPOH;

	//posicao dos recordes
	for (i = 0; i < NRECORDES; i++) {
		texto_recordes[i].pos.x = 40;
		texto_recordes[i].pos.y = 140+i*55;
		texto_recordes[i].pos.w = 960;
		texto_recordes[i].pos.h = 40;
	}

	//menu inicial
	//botao do inicio
	menu_inicio.x = 420;
	menu_inicio.y = 300;
	menu_inicio.w = 190;
	menu_inicio.h = 90;
	//botao dos creditos
	menu_creditos.x = 420;
	menu_creditos.y = 430;
	menu_creditos.w = 190;
	menu_creditos.h = 90;
	//botao de voltar
	menu_voltar.x = 420;
	menu_voltar.y = 680;
	menu_voltar.w = 230;
	menu_voltar.h = 85;
	//botao dos recordes
	menu_recordes.x = 420;
	menu_recordes.y = 560;
	menu_recordes.w = 190;
	menu_recordes.h = 90;
	//botao de sair
	menu_sair.x = 923;
	menu_sair.y = 733;
	menu_sair.w = 101;
	menu_sair.h = 35;
	//botoes de mudar recordes
	//debil mental
	texto_mudardificuldade[0].pos.x = 50;
	texto_mudardificuldade[0].pos.y = 90;
	texto_mudardificuldade[0].pos.w = 380;
	texto_mudardificuldade[0].pos.h = 45;
	//facil
	texto_mudardificuldade[1].pos.x = 450;
	texto_mudardificuldade[1].pos.y = 90;
	texto_mudardificuldade[1].pos.w = 158;
	texto_mudardificuldade[1].pos.h = 45;
	//huebr
	texto_mudardificuldade[2].pos.x = 800;
	texto_mudardificuldade[2].pos.y = 90;
	texto_mudardificuldade[2].pos.w = 158;
	texto_mudardificuldade[2].pos.h = 45;
	//botao submeter
	botao_submeter.x = 390;
	botao_submeter.y = 375;
	botao_submeter.w = 250;
	botao_submeter.h = 55;
	//botao continuar
	botao_continuar.x = 360;
	botao_continuar.y = 570;
	botao_continuar.w = 310;
	botao_continuar.h = 62;
	//botao tentarnovamente
	botao_tentar_novamente.x = 270;
	botao_tentar_novamente.y = 227;
	botao_tentar_novamente.w = 525;
	botao_tentar_novamente.h = 65;
	//botao troca mododejogo
	botao_troca_mododejogo.x = 405;
	botao_troca_mododejogo.y = 375;
	botao_troca_mododejogo.w = 260;
	botao_troca_mododejogo.h = 65;
	//botao troca dificuldade
	botao_troca_dificuldade.x = 405;
	botao_troca_dificuldade.y = 510;
	botao_troca_dificuldade.w = 260;
	botao_troca_dificuldade.h = 65;
	//botao ir para menu principal
	botao_menu_principal.x = 385;
	botao_menu_principal.y = 645;
	botao_menu_principal.w = 300;
	botao_menu_principal.h = 75;
	//botao modo de jogo classico
	modo_classico.x = 370;
	modo_classico.y = 280;
	modo_classico.w = 295;
	modo_classico.h = 80;
	//botao modo de jogo contraotempo
	modo_contraotempo.x = 310;
	modo_contraotempo.y = 445;
	modo_contraotempo.w = 425;
	modo_contraotempo.h = 75;
	//botao ir para menu principal
	botao_menu_principal.x = 385;
	botao_menu_principal.y = 645;
	botao_menu_principal.w = 300;
	botao_menu_principal.h = 75;
	//botao da dificuldade debil mental
	dificuldade_debil.x = 300;
	dificuldade_debil.y = 325;
	dificuldade_debil.w = 440;
	dificuldade_debil.h = 75;

	//posicao da caixa de crack
	caixa_pos.x = 0;
	caixa_pos.y = RESY - 3*SPRITE_ESCADAY - SPRITE_CAIXAD - 12;
	caixa_pos.w = SPRITE_CAIXAD;
	caixa_pos.h = SPRITE_CAIXAD;

	//posicao do beira mar
	beira_pos.x = SPRITE_CAIXAD + 3;
	beira_pos.y = RESY - 3*SPRITE_ESCADAY - SPRITE_BEIRAY - 16;
	beira_pos.w = SPRITE_BEIRAX;
	beira_pos.h = SPRITE_BEIRAY;
	beira_sprite.x = 0;
	beira_sprite.w = SPRITE_BEIRAX;
	beira_sprite.h = SPRITE_BEIRAY;

	//posicao da ultima escada
	escadafinal_pos.x = SPRITE_CAIXAD + 2*SPRITE_BEIRAX;
	escadafinal_pos.y = RESY - 3*SPRITE_ESCADAY - SPRITE_ESCADAFINALY - 16;
	escadafinal_pos.w = SPRITE_ESCADAFINALX;
	escadafinal_pos.h = SPRITE_ESCADAFINALY;

	escadafinal_col.x = escadafinal_pos.x + SPRITE_ESCADAFINALX/2;
	escadafinal_col.y = escadafinal_pos.y - SPRITE_OFICIALY;
	escadafinal_col.w = escadafinal_pos.w - SPRITE_ESCADAFINALX;
	escadafinal_col.h = escadafinal_pos.h + SPRITE_OFICIALY;

	//posicao da crianca
	crianca_pos.x = escadafinal_pos.x + SPRITE_CRIANCAX + 20;
	crianca_pos.y = escadafinal_pos.y - SPRITE_CRIANCAY + 6;
	crianca_pos.w = SPRITE_CRIANCAX;
	crianca_pos.h = SPRITE_CRIANCAY;
	crianca_sprite.x = 0;
	crianca_sprite.y = 0;
	crianca_sprite.w = SPRITE_CRIANCAX;
	crianca_sprite.h = SPRITE_CRIANCAY;

	//alocacao dinamica dos recordes
	recorde = (struct recordes *)malloc(3*PONTUACOES*sizeof(struct recordes));

	//ler os recordes do arquivo
	//coloca valores do arquivo na matriz, se o arquivo nao existir, coloca os valores padroes na matriz 
	if ( !( ler_arquivo = fopen (ARQUIVO, "r") ) ) {

		for (j = 0; j < 3; j++) {

			primeiro = j*PONTUACOES;

			//escreve os recordes
			for (i = 0; i < PONTUACOES; i++) {
				sprintf (recorde[i+primeiro].nome, "%s\n", NOME_PADRAO);
				recorde[i+primeiro].pontuacao = 0;
			}
		}

	}else{

		for (j = 0; j < 3; j++) {
			
			primeiro = j*PONTUACOES;

			//ler os recordes
			for (i = 0; i < PONTUACOES; i++) {
				//pontuacao
				fgets (aux, NOME_CHAR, ler_arquivo);
				descriptografa_numero (aux);
				sscanf (aux, "%d", &recorde[i+primeiro].pontuacao);
				//nome
				fgets (recorde[i+primeiro].nome, NOME_CHAR, ler_arquivo);
				descriptografa_nome (recorde[i+primeiro].nome);
			}
		}

		fclose (ler_arquivo);

	}

	cont_aux = 0;
	cont_pauaux = 0;

}


/*FASE*/
void carregar_fase (void) {

	short int i;

	//posicao do chao
	chao = RESY - 16;

	//posicao inicial da escada 1
	escada_pos[0].x = RESX - LIM_PLAT - SPRITE_ESCADAX - randomizar (207);
	escada_pos[0].y = chao - SPRITE_ESCADAY;
	escada_pos[0].w = SPRITE_ESCADAX;
	escada_pos[0].h = SPRITE_ESCADAY;

	escada_col[0].x = escada_pos[0].x + SPRITE_ESCADAX/3;
	escada_col[0].y = escada_pos[0].y - SPRITE_OFICIALY;
	escada_col[0].w = escada_pos[0].w - 2*SPRITE_ESCADAX/3;
	escada_col[0].h = escada_pos[0].h + SPRITE_OFICIALY;

	escada_quebrada_pos[0].x = SPRITE_ESCADAX + randomizar (413);
	escada_quebrada_pos[0].y = chao - SPRITE_ESCADAY;
	escada_quebrada_pos[0].w = SPRITE_ESCADAX;
	escada_quebrada_pos[0].h = SPRITE_ESCADAY;

	//tempo para completar a fase (se o modo for por vidas ela sera zerado mais abaixo no codigo)
	seg = 60;

	//determina objetos de acordo com a dificuldade
	if (dificuldade == 0) {

		//numero de vidas
		MAX_VIDAS = 5;

		//numero de pedras de crack
		NCRACK = 10;

		//velodidades minima e maxima das pedras de crack
		MINVELO_CRACK = 5;
		MAXVELO_CRACK = 7;

		//tempos minimo e maximo para lancamento das pedras de crack (em frames)
		MINTEMP_CRACK = 120;
		MAXTEMP_CRACK = 150;

		//tempo com o pau e posicao do pau
		pau_tempo = 300;

	}else if (dificuldade == 1) {

		//numero de vidas
		MAX_VIDAS = 3;

		//numero de pedras de crack
		NCRACK = 10;

		//velodidades minima e maxima das pedras de crack
		MINVELO_CRACK = 6;
		MAXVELO_CRACK = 8;

		//tempos minimo e maximo para lancamento das pedras de crack (em frames)
		MINTEMP_CRACK = 70;
		MAXTEMP_CRACK = 90;

		//tempo com o pau e posicao do pau
		pau_tempo = 500;

	}else {

		//numero de vidas
		MAX_VIDAS = 1;

		//numero de pedras de crack
		NCRACK = 15;

		//velodidades minima e maxima das pedras de crack
		MINVELO_CRACK = 5;
		MAXVELO_CRACK = 12;

		//tempos minimo e maximo para lancamento das pedras de crack (em frames)
		MINTEMP_CRACK = 40;
		MAXTEMP_CRACK = 100;

		//tempo com o pau e posicao do pau
		pau_tempo = 900;

	}

	crack_cont = NCRACK;
	
	//posicao inicial da pontuacao ganha
	texto_printscore.pos.x = 0;
	texto_printscore.pos.y = 0;
	texto_printscore.pos.w = 130;
	texto_printscore.pos.h = 26;

	//se vai jogar modo por vidas
	if (modo_jogo == 0) {

		//zera o tempo
		seg = 0;

		//da o numero maximo de vidas ao jogador
		NVIDAS = MAX_VIDAS;

		//aloca espaco necessario para os sprites da vida na memoria
		if (vida_pos == NULL) {
			if ( !(vida_pos = (SDL_Rect *)malloc( MAX_VIDAS*sizeof(SDL_Rect) ) ) ) {
				printf ("Nao foi possivel alocar espaco na memoria para vida_pos\n");
			}
		}else if ( !(vida_pos = (SDL_Rect *)realloc( vida_pos, MAX_VIDAS*sizeof(SDL_Rect) ) ) ) {
			printf ("Nao foi possivel alocar espaco na memoria para vida_pos\n");
		}

		//randomizar posicao y do pau
		pau_pos.y = chao - ( randomizar(2) + 1 ) * SPRITE_ESCADAY - SPRITE_PAUY;
		//randomizar posicao x do pau de acordo com posicao y
		pau_pos.x = (pau_pos.y == chao - 2*SPRITE_ESCADAY - SPRITE_PAUY) ? LIM_PLAT + randomizar(RESX/2) : RESX - randomizar (RESX/2) - LIM_PLAT;

	}else{
		NVIDAS = 1;
		pau_pos.y = 0;
	}

	pau_pos.w = SPRITE_PAUX;
	pau_pos.h = SPRITE_PAUY;

	/*aloca espaco necessario para as pedras de crack na memoria*/
	//se o espaco ainda nao foi alocado
	if (crack_velo == NULL) {

		//velocidade das pedras
		if ( !( crack_velo = (short int *)malloc( NCRACK * sizeof(short int) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_velo\n");
		//status das pedras
		if ( !( crack_status = (short int *)malloc( NCRACK * sizeof(short int) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_status\n");
		//posicao do chao das pedras
		if ( !( crack_chao = (short int *)malloc( NCRACK * sizeof(short int) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_chao\n");
		//posicao das pedras
		if ( !( crack_pos = (SDL_Rect *)malloc( NCRACK * sizeof(SDL_Rect) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_pos\n");
		//sprite das pedras
		if ( !( crack_sprite = (SDL_Rect *)malloc( NCRACK * sizeof(SDL_Rect) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_sprite\n");
		//colisao das pedras
		if ( !( crack_col = (SDL_Rect *)malloc( NCRACK * sizeof(SDL_Rect) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_col\n");
		//aleatoriedade do lancamento
		if ( !( crack_rnd = (unsigned short int *)malloc( NCRACK * sizeof(unsigned short int) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_rnd\n");

	}

	//se o espaco ja esta alocado alocado
	else {

		//velocidade do crack
		if ( !( crack_velo = (short int *)realloc( crack_velo, NCRACK*sizeof(short int) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_velo\n");
		//status das pedras
		if ( !( crack_status = (short int *)realloc( crack_status, NCRACK*sizeof(short int) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_status\n");
		//posicao do chao das pedras
		if ( !( crack_chao = (short int *)realloc( crack_chao, NCRACK*sizeof(short int) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_velo\n");
		//posicao das pedras
		if ( !( crack_pos = (SDL_Rect *)realloc( crack_pos, NCRACK*sizeof(SDL_Rect) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_pos\n");
		//sprite das pedras
		if ( !( crack_sprite = (SDL_Rect *)realloc( crack_sprite, NCRACK*sizeof(SDL_Rect) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_sprite\n");
		//colisao das pedras
		if ( !( crack_col = (SDL_Rect *)realloc( crack_col, NCRACK*sizeof(SDL_Rect) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_col\n");
		//aleatoriedade do lancamento
		if ( !( crack_rnd = (unsigned short int *)realloc( crack_rnd, NCRACK*sizeof(unsigned short int) ) ) )
			printf ("Nao foi possivel alocar espaco na memoria para crack_rnd\n");

	}

	//posicao da escada 2
	escada_pos[1].x = LIM_PLAT + randomizar (397);
	escada_pos[1].y = chao - 2*SPRITE_ESCADAY;
	escada_pos[1].w = SPRITE_ESCADAX;
	escada_pos[1].h = SPRITE_ESCADAY;

	escada_col[1].x = escada_pos[1].x + SPRITE_ESCADAX/3;
	escada_col[1].y = escada_pos[1].y - SPRITE_OFICIALY;
	escada_col[1].w = escada_pos[1].w - 2*SPRITE_ESCADAX/3;
	escada_col[1].h = escada_pos[1].h + SPRITE_OFICIALY;

	escada_quebrada_pos[1].x = RESX - LIM_PLAT - SPRITE_ESCADAX - randomizar(267);
	escada_quebrada_pos[1].y = chao - 2*SPRITE_ESCADAY;
	escada_quebrada_pos[1].w = SPRITE_ESCADAX;
	escada_quebrada_pos[1].h = SPRITE_ESCADAY;

	//posicao inicial do oficial (includes.h)
	oficial_pos.x = 0;
	oficial_pos.y = chao - SPRITE_OFICIALY;
	oficial_pos.w = SPRITE_OFICIALX;
	oficial_pos.h = SPRITE_OFICIALY;

	oficial_sprite.x = 0;
	oficial_sprite.y = 0;
	oficial_sprite.w = SPRITE_OFICIALX;
	oficial_sprite.h = SPRITE_OFICIALY;

	oficial_col.x = oficial_pos.x;
	oficial_col.y = oficial_pos.y;
	oficial_col.w = SPRITE_OFICIALX/3;
	oficial_col.h = SPRITE_OFICIALY - COMP_OFICIALY;

	//posicao inicial do ataque do oficial
	ataque.x = 0;
	ataque.y = 0;
	ataque.w = ALCANCE_ATAQUE;
	ataque.h = SPRITE_OFICIALY;

	//posicao inicial das pedras de crack
	for (i = 0; i < NCRACK; i++) {

		crack_status[i] = 0;
		crack_velo[i] = 0;
		crack_rnd[i] = 0;
		crack_chao[i] = RESY - 3*SPRITE_ESCADAY - SPRITE_CRACKD - 16;

		crack_pos[i].x = 0;
		crack_pos[i].y = RESY - SPRITE_CRACKD - 3*SPRITE_ESCADAY - 16;
		crack_pos[i].w = SPRITE_CRACKD;
		crack_pos[i].h = SPRITE_CRACKD;

		crack_sprite[i].x = 0;
		crack_sprite[i].y = 0;
		crack_sprite[i].w = SPRITE_CRACKD;
		crack_sprite[i].h = SPRITE_CRACKD;

		crack_col[i].x = crack_pos[i].x;
		crack_col[i].y = crack_pos[i].y;
		crack_col[i].w = SPRITE_CRACKD-10;
		crack_col[i].h = SPRITE_CRACKD;

	}

	//posicao da escada 3
	escada_pos[2].x = RESX - LIM_PLAT - SPRITE_ESCADAX - randomizar (303);
	escada_pos[2].y = chao - 3*SPRITE_ESCADAY;
	escada_pos[2].w = SPRITE_ESCADAX;
	escada_pos[2].h = SPRITE_ESCADAY;

	escada_col[2].x = escada_pos[2].x + SPRITE_ESCADAX/3;
	escada_col[2].y = escada_pos[2].y - SPRITE_OFICIALY;
	escada_col[2].w = escada_pos[2].w - 2*SPRITE_ESCADAX/3;
	escada_col[2].h = escada_pos[2].h + SPRITE_OFICIALY;

	escada_quebrada_pos[2].x = LIM_PLAT + randomizar(283);
	escada_quebrada_pos[2].y = chao - 3*SPRITE_ESCADAY;
	escada_quebrada_pos[2].w = SPRITE_ESCADAX;
	escada_quebrada_pos[2].h = SPRITE_ESCADAY;

	//posicao dos sprites das vidas
	if (modo_jogo == 0) {
		for (i = 0; i < MAX_VIDAS; i++) {

			vida_pos[i].x = i*SPRITE_VIDAX + 5;
			vida_pos[i].y = 5;
			vida_pos[i].w = SPRITE_VIDAX;
			vida_pos[i].h = SPRITE_VIDAY;

		}
	}

	//zera o score
	score = 0;
	score_mult = 1;
	score_div = 1;
	score_pedraspuladas = 0;
	score_tempaux = 0;
	printscore_temp = 0;

	//zerar contagem de tempo
	frame = 0;

	cont_aux = 0;
	cont_pauaux = 0;
	cont_paucool = 0;
	aux_paucool = 0;
	gameover = 0;
	cont_gameover = 0;
	cont_tecla = 0;

	//permitir movimentacao do jogador
	status_jogador = 10;

}
