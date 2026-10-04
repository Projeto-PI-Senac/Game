#include <stdio.h>
#include <stdbool.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

int jogo(void);

int main(void)
{
    al_init();
    al_init_primitives_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_mouse();

   
    // Tamanho da tela e dos botões
    int largura_tela = 1280;
    int altura_tela = 720;

    int largura_botao = 350;
    int altura_botao = 100;

    // Posição dos botões
    int x1 = (largura_tela - largura_botao) / 2;
    int y1 = 500;
    int x2 = x1 + largura_botao;
    int y2 = y1 + altura_botao;

    // Criação da janela
    ALLEGRO_DISPLAY* janela = al_create_display(largura_tela, altura_tela);

    // Como fonts e imgs estão na mesma pasta do projeto
    ALLEGRO_FONT* fonte = al_load_ttf_font(
        "fonts/Arial.ttf",
        50,
        0
    );

    ALLEGRO_BITMAP* background = al_load_bitmap(
        "imgs/fundo_menu.png"
    );

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    ALLEGRO_EVENT_QUEUE* mouse = al_create_event_queue();

    // Verifica se os recursos foram carregados
    if (!janela)
    {
        printf("Erro ao criar a janela!\n");
        return -1;
    }

    if (!fonte)
    {
        printf("Erro ao carregar a fonte: fonts/Arial.ttf\n");

        al_destroy_display(janela);
        return -1;
    }

    if (!background)
    {
        printf("Erro ao carregar a imagem: imgs/fundo_menu.png\n");

        al_destroy_font(fonte);
        al_destroy_display(janela);
        return -1;
    }

    if (!timer || !mouse)
    {
        printf("Erro ao criar timer ou fila de eventos!\n");

        al_destroy_font(fonte);
        al_destroy_bitmap(background);
        al_destroy_display(janela);

        return -1;
    }

    // Eventos do mouse, janela e timer
    al_register_event_source(
        mouse,
        al_get_mouse_event_source()
    );

    al_register_event_source(
        mouse,
        al_get_display_event_source(janela)
    );

    al_register_event_source(
        mouse,
        al_get_timer_event_source(timer)
    );

    al_start_timer(timer);

    bool menu = true;
    bool desenho = true;

    while (menu)
    {
        ALLEGRO_EVENT evento;

        al_wait_for_event(mouse, &evento);

        // Fechar pelo X
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            menu = false;
        }

        // Atualização do desenho
        if (evento.type == ALLEGRO_EVENT_TIMER)
        {
            desenho = true;
        }

        // Desenhar menu
        if (desenho && al_is_event_queue_empty(mouse))
        {
            desenho = false;

            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Fundo
            al_draw_bitmap(background, 0, 0, 0);

            // Botões
            al_draw_filled_rectangle(
                x1, y1,
                x2, y2,
                al_map_rgb(0, 100, 255)
            );

            al_draw_filled_rectangle(
                x1, y1 + 120,
                x2, y2 + 120,
                al_map_rgb(0, 100, 255)
            );

            al_draw_filled_rectangle(
                x1, y1 + 240,
                x2, y2 + 240,
                al_map_rgb(0, 100, 255)
            );

            int texto_x = x1 + (largura_botao / 2);
            int texto_y = y1 + (altura_botao / 2 - 25);

            // Textos
            al_draw_text(
                fonte,
                al_map_rgb(255, 255, 255),
                texto_x,
                texto_y,
                ALLEGRO_ALIGN_CENTER,
                "PLAY"
            );

            al_draw_text(
                fonte,
                al_map_rgb(255, 255, 255),
                texto_x,
                texto_y + 120,
                ALLEGRO_ALIGN_CENTER,
                "TUTORIAL"
            );

            al_draw_text(
                fonte,
                al_map_rgb(255, 255, 255),
                texto_x,
                texto_y + 240,
                ALLEGRO_ALIGN_CENTER,
                "SAIR"
            );

            al_flip_display();
        }

        // Clique do mouse
        if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            int mouse_x = evento.mouse.x;
            int mouse_y = evento.mouse.y;

            // PLAY
            if (
                mouse_x >= x1 &&
                mouse_x <= x2 &&
                mouse_y >= y1 &&
                mouse_y <= y2
                )
            {
                // Libera o menu antes de entrar no jogo
                al_destroy_font(fonte);
                al_destroy_bitmap(background);
                al_destroy_timer(timer);
                al_destroy_event_queue(mouse);
                al_destroy_display(janela);

                // Inicia o jogo
                return jogo();
            }

            // TUTORIAL
            if (
                mouse_x >= x1 &&
                mouse_x <= x2 &&
                mouse_y >= y1 + 120 &&
                mouse_y <= y2 + 120
                )
            {
                printf("TUTORIAL!\n");
            }

            // SAIR
            if (
                mouse_x >= x1 &&
                mouse_x <= x2 &&
                mouse_y >= y1 + 240 &&
                mouse_y <= y2 + 240
                )
            {
                menu = false;
            }
        }
    }

    // Limpeza ao sair pelo menu
    al_destroy_font(fonte);
    al_destroy_bitmap(background);
    al_destroy_timer(timer);
    al_destroy_event_queue(mouse);
    al_destroy_display(janela);

    return 0;
   
}


