# Fragmentation Of Dictatorship

Este repositório contém as instruções para configurar o ambiente e compilar o jogo tanto via **GCC (MSYS2)** quanto pelo **Visual Studio 2022**.

---

## Compilação via Terminal (MSYS2 + GCC)

### Pré-requisito
1. Baixe e instale o [MSYS2](https://www.msys2.org/).
2. Abra o terminal **MSYS2 UCRT64** para executar os comandos a seguir.

### Instalação do GCC
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

### Verificação da instalação do GCC
```bash
gcc --version
```

### Instalação do pkgconf
```bash
pacman -S mingw-w64-ucrt-x86_64-pkgconf
```

### Verificação da instalação do pkgconf
```bash
pkg-config --version
```

### Instalação do Allegro
```bash
pacman -S mingw-w64-ucrt-x86_64-allegro
```

### Verificação da instalação do Allegro
```bash
pkg-config --modversion allegro-5 allegro_main-5
```

### Criação do arquivo .exe 
```bash
gcc main.c jogo.c -o jogo -lallegro -lallegro_main -lallegro_primitives -lallegro_audio -lallegro_image -lallegro_font -lallegro_ttf
```

### Execução do jogo
```bash
./jogo.exe
```

---

## Compilação via Visual Studio 2022

### Pré-requisitos
1. Baixe e instale o **Visual Studio 2022 Community**.
2. No instalador do Visual Studio, selecione a carga de trabalho **Desenvolvimento para Desktop com C++**.

### Configuração do Allegro 5 no Projeto
1. Abra a solução ou o projeto do jogo no Visual Studio.
2. No painel **Gerenciador de Soluções**, clique com o botão direito sobre o nome do projeto e selecione **Gerenciar Pacotes NuGet...**
3. Acesse a aba **Procurar**, pesquise por `Allegro` e clique em **Instalar** no pacote oficial do Allegro.
4. Pesquise também por `AllegroDeps` e faça a instalação do pacote de dependências.

### Como Executar
1. Verifique se a arquitetura no topo da janela do Visual Studio está definida corretamente (por exemplo, `x64` ou `x86`).
2. Pressione a tecla **F5** (ou clique no botão verde **Iniciar**) para compilar e executar o jogo.

**Nota**: Certifique-se de que os arquivos de mídia (imagens, sons, fontes) estejam na mesma pasta do arquivo de solução/executável.
