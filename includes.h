/*
contem todas as livrarias, variaveis globais, constantes e funcoes
*/

#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"


/*CONSTANTES*/

//resolucao x da tela
#define RESX 1024

//resolucao y da tela
#define RESY 768

//posicao x e y do score na tela
#define POS_SCOREX 400
#define POS_SCOREY 10
#define POS_SCOREW 468
#define POS_SCOREH 33

//posicao x e y do tempo na tela
#define POS_TEMPOX 460
#define POS_TEMPOY (POS_SCOREY + 33)
#define POS_TEMPOW 165
#define POS_TEMPOH 33

//cor branco
#define BRANCO (struct SDL_Color) { 255, 255, 255, 255 }

//cor verde
#define VERDE (struct SDL_Color) { 0, 125, 0, 255 }

//cor vermelho
#define VERMELHO (struct SDL_Color) { 255, 0, 0, 255 }

//numero maximo de recordes
#define NRECORDES 10

//tamanho maximo dos nomes dos recordes
#define NOME_CHAR 10

//nome do arquivo com os recordes
#define ARQUIVO "configs.dkj"

//nome padrao quando nao ha recordes na posicao
#define NOME_PADRAO "JOGADOR"

//volume maximo
#define MIX_MAX_VOLUME 128

//limite x de uma plataforma
#define LIM_PLAT 143

//resolucoes x e y do sprite da escada
#define SPRITE_ESCADAX 43
#define SPRITE_ESCADAY 175

//resolucoes x e y da ultima escada
#define SPRITE_ESCADAFINALX 47
#define SPRITE_ESCADAFINALY 128

//resolucoes x e y do sprite do oficial
#define SPRITE_OFICIALX 66
#define SPRITE_OFICIALY 99

//compensacao y do oficial
#define COMP_OFICIALY 8

//resolucao x e y do sprite da pedra de crack
#define SPRITE_CRACKD 32

//resolucao x e y do sprite da caixa de crack
#define SPRITE_CAIXAD 120

//resolucao x e y do sprite da crianca
#define SPRITE_CRIANCAX 58
#define SPRITE_CRIANCAY 64

//resolucao x e y do sprite do vilao
#define SPRITE_BEIRAX 50
#define SPRITE_BEIRAY 119

//resolucao x e y do sprite da vida
#define SPRITE_VIDAX 25
#define SPRITE_VIDAY 40

//resolucao x e y do pau
#define SPRITE_PAUX 46
#define SPRITE_PAUY 50

//altura do pulo do oficial
#define ALT_PULO 64

//velocidade do personagem
#define VELO_OFICIAL 2

//intervalo entre frames das animacoes (em frames)
#define VELOANIM_OFICIAL 4
#define VELOANIM_BEIRA 12
#define VELOANIM_CRIANCA 12
#define VELOANIM_CRACK 8

//alcance do ataque do personagem
#define ALCANCE_ATAQUE 40

//cooldown do ataque do personagem (em frames)
#define ATAQUE_COOLDOWN 8

//numero de escadas na fase
#define NESCADAS 3

//numero da contagem maxima de frames
#define FPS 60

//tamanho da fonte
#define TAMANHO_FONTE_SCORE 25
#define TAMANHO_FONTE_PRINTSCORE 22
#define TAMANHO_FONTE_RECORDES 52
#define TAMANHO_FONTE_MUDARECORDES 30

//pontuacao maxima
#define MAX_SCORE 99999999

//numero de recordes para cada dificuldade
#define PONTUACOES 10

//numero de pedras apos o qual ocorre diminuicao do score
#define DIM_PORPEDRAS 2

//diminuicao do score
#define DIM_SCOREDIV 0.25

//pontuacao pelas acoes
#define SCORE_PULAR 100
#define SCORE_BATER 150
#define SCORE_HIT 250
#define SCORE_TEMPBONUS 200

//intervalo para o combo (em frames)
#define INTERVALO_COMBO 40



/*VARIAVEIS*/
//struct dos recordes
struct recordes {
	char nome[NOME_CHAR];
	int pontuacao;
};

//struct de texto
struct texto {

	SDL_Surface *surface;
	TTF_Font *fonte;
	SDL_Rect pos;

};
struct text_rec {
	SDL_Surface *surface;
	SDL_Rect pos;
};

//musica de fundo
Mix_Music *theme;

//som do crack
Mix_Chunk *som;

//som do menu
Mix_Chunk *sommenu;

//som do game over
Mix_Chunk *somgo;

//som de inicio de jogo
Mix_Chunk *missao;

//som do hit
Mix_Chunk *somhit;

//som dos pontos
Mix_Chunk *coin;

//som da vitoria
Mix_Chunk *somwin;

//tela
SDL_Surface *tela;

//aviso anti drogas
SDL_Surface *aviso;

//telas de historia
SDL_Surface *historia1;
SDL_Surface *historia2;

//telas de abertura
SDL_Surface *abertura1;
SDL_Surface *abertura2;

//tela controles
SDL_Surface *controles;

//menu
SDL_Surface *menu;

//tela creditos
SDL_Surface *creditos;

//tela de recordes
SDL_Surface *tela_recordes;

//tela ganhou
SDL_Surface *ganhou;

//tela digite o nome
SDL_Surface *digiteonome;

//tela modo de jogo
SDL_Surface *tela_mododejogo;

//tela de selecao de dificuldade
SDL_Surface *tela_dificuldade;

//tela gameover
SDL_Surface *tela_gameover;

//plano de fundo
SDL_Surface *fundo;

//sprite sheet do oficial
SDL_Surface *oficial;

//sprite sheet da pedra de crack
SDL_Surface *crack;

//sprite da escada
SDL_Surface *escada;

//sprite da escada quebrada
SDL_Surface *escada_quebrada;

//sprite da ultima escada;
SDL_Surface *escadafinal;

//sprite da caixa de crack
SDL_Surface *caixa;

//sprite do beira mar
SDL_Surface *beira;

//sprite da crianca
SDL_Surface *crianca;

//sprite das vidas
SDL_Surface *vida;

//sprite do pau
SDL_Surface *pau;

//botao de inicio do jogo
SDL_Rect menu_inicio; //USADA TAMBEM PARA SELECIONAR A DIFICULDADE IZI

//botao dos creditos
SDL_Rect menu_creditos; //USADA TAMBEM PARA SELECIONAR A DIFICULDADE FACIL

//botao de voltar
SDL_Rect menu_voltar;

//botao dos creditos
SDL_Rect menu_recordes; //USADA TAMBEM PARA SELECIONAR A DIFICULDADE HUEBR

//botao de sair
SDL_Rect menu_sair;

//botoes dos recordes
SDL_Rect recorde_debil;
SDL_Rect recorde_facil;
SDL_Rect recorde_huebr;

//botao continuar
SDL_Rect botao_continuar;

//botao submeter
SDL_Rect botao_submeter;

//botao tentarnovamente
SDL_Rect botao_tentar_novamente;

//botao troca modo de jogo
SDL_Rect botao_troca_mododejogo;

//botao modo de jogo classico
SDL_Rect modo_classico;

//botao modo de jogo contra o tempo
SDL_Rect modo_contraotempo;

//botao trocadificuldade
SDL_Rect botao_troca_dificuldade;

//botao ir para menu principal
SDL_Rect botao_menu_principal;

//botao da dificuldade debil mental
SDL_Rect dificuldade_debil;

//coordenadas das escadas
SDL_Rect escada_pos[NESCADAS];

//coordenadas das escadas quebradas
SDL_Rect escada_quebrada_pos[NESCADAS];

//colisao das escadas
SDL_Rect escada_col[NESCADAS];

//coordenadas da ultima escada
SDL_Rect escadafinal_pos;

//colisao da ultima escada
SDL_Rect escadafinal_col;

//coordenadas da pedra de crack
SDL_Rect *crack_pos;

//colisao da pedra de crack
SDL_Rect *crack_col;

//sprite da pedra de crack
SDL_Rect *crack_sprite;

//coordenadas da crianca
SDL_Rect crianca_pos,
	 crianca_sprite;

//coordenadas da caixa
SDL_Rect caixa_pos;

//coordenadas do beira mar
SDL_Rect beira_pos,
	 beira_sprite;

//coordenadas da vida
SDL_Rect *vida_pos;

//coordenadas do pau
SDL_Rect pau_pos;

//coordenadas do ataque do oficial
SDL_Rect ataque;

//texto do score principal
struct texto texto_score;

//texto da pontuacao ganha
struct texto texto_printscore;

//texto do tempo
struct texto texto_tempo;

//texto dos recordes
struct text_rec texto_recordes[NRECORDES];

//texto da dificuldade na tela de recordes
struct text_rec texto_mudardificuldade[3];

//fonte dos recordes
TTF_Font *pixel;

//fonte da troca da dificuldade na tela de recordes
TTF_Font *pixel_25;

//variaveis para armazenar recordes do arquivo
/*
char **recordes,
     **jogadores;
*/
struct recordes *recorde;

//auxiliar para remover texto da pontuacao ganha
unsigned short int printscore_temp;

//velocidade das pedras de crack
short int *crack_velo;

//0 se a pedra de crack deve andar, 1 se ela deve cair e 2 se a pedra foi pulada
short int *crack_status;

//coordenadas do chao da pedra
short int *crack_chao;

//se o jogo acabou. 0 se nao acabou, 1 se o jogador ganhou e 2 se o jogador perdeu
short int gameover;

//variaveis para contagem de tempo
short unsigned int iteracao,
		     tempo,
		     cont_aux,
		     cont_pauaux,
		     cont_paucool,
		     cont_gameover,
		     cont_tecla;

//variaveis para auxiliar na espera do lancamento da pedra de crack
short unsigned int *crack_rnd,
		     crack_cont;

//variavel que determina tempo com o pau (em frames)
short unsigned int pau_tempo;

//coordenadas do oficial
SDL_Rect oficial_pos;

//coordenadas do sprite do oficial
SDL_Rect oficial_sprite;

//colisao do oficial
SDL_Rect oficial_col;	

//status do jogador
/*
0 : nao pode se mover
1 : nao pode mover no eixo x e pode mover no eixo y (na escada)
2 : nao pode pular ou subir escada (pau na mao)
3 : subindo durante pulo
4 : descendo durante pulo
5 : batendo
qualquer outro valor : pode de tudo
*/
short unsigned int status_jogador;

//coordenada y do chao
short int chao;

//contador de frames
short unsigned int frame;

//numero de pedras de crack na fase
short int NCRACK;

//velocidade minima da pedra de crack
short int MINVELO_CRACK;

//velocidade maxima da pedra de crack
short int MAXVELO_CRACK;

//tempo minimo para lancamento da pedra (em frames)
short int MINTEMP_CRACK;

//tempo maximo para lancamento da pedra (em frames)
short int MAXTEMP_CRACK;

//vidas do jogador
short int NVIDAS;

//numero maximo de vidas do jogador
short int MAX_VIDAS;

//modo de jogo, 0 para modo por vidas e 1 para modo por tempo
short int modo_jogo;

//dificuldade do jogo 0 = Debil Mental, 1 = Hard, 2 = Impossivel
short int dificuldade;

//score
int score;

//multiplicador do score
short int score_mult;
float score_div;

//pedras puladas em um andar (reseta ao determinar diminuicao dos pontos)
short int score_pedraspuladas;

//auxiliar para mostrar pontos ganhos
short int score_print;

//variavel para auxiliar no tempo dos combos
short unsigned int score_tempaux;

//variavel auxiliar para cooldown do ataque
short unsigned int aux_paucool;

//variaveis para contagem do tempo de jogo
short int seg;



/*FUNCOES*/

//cria a janela principal (janela.c)
SDL_Surface* iniciar (SDL_Surface *);

//blitar elementos na tela (janela.c)
void blit_tela (void);

//selecionar sprite (janela.c)
SDL_Rect selecionar_sprite (struct SDL_Rect, char, short unsigned int, short unsigned int, short int, short unsigned int);

//encerra o programa (janela.c)
void sair (void);

//espera um certo numero de frames (janela.c)
int esperar (unsigned short int, unsigned short int *);

//verifica colisao entre dois objetos (janela.c)
int colisao (SDL_Rect *, SDL_Rect *);

//carregar variaveis estaticas (carregar.c)
void carregar_inicial (void);

//carregar inicio da fase (carregar.c)
void carregar_fase (void);

//verifica input (input.c)
short int input (unsigned char *);

//funcao do pulo (input.c)
void pular_bater (short int);

//verifica se objeto deve cair (eventos.c)
short int cair (SDL_Rect *);

//verifica colisao de oficial com pedras de crack (eventos.c)
void verificar_col (void);

//animar oficial em colisao (eventos.c)
void hit (short int);

//move as pedras de crack (eventos.c)
void mover_crack (SDL_Rect *, SDL_Rect *, short int *, short int *, short int *);

//da valores aos surfaces dos recordes (arquivo.c)
void mostrar_pontuacao (short int);

//modificar o menor valor do recorde (arquivo.c)
void inserir_score (int);

//funcoes para descriptografar recordes (arquivo.c)
void descriptografa_nome (char *);
void descriptografa_numero (char *);
