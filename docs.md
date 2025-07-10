# Mapeamento da Codebase do RPG Terminal

Este documento descreve a estrutura e o funcionamento do jogo RPG de terminal, facilitando a compreensão e a implementação de novas funcionalidades ou modificações.

## 1. Visão Geral do Projeto

O projeto é um jogo RPG baseado em terminal, desenvolvido em C++. Ele apresenta um sistema de batalha simples por turnos entre o jogador e um inimigos, um sistema de criação de personagem e funcionalidade de salvar/carregar o progresso do jogo. A interação com o usuário é feita através de menus e entrada de teclado (setas, espaço, 'q').

## 2. Estrutura de Diretórios

-   `main.cpp`: Contém o loop principal do jogo e a inicialização.
-   `include/`: Contém os arquivos de cabeçalho (`.hpp`) para as classes e funções.
-   `src/`: Contém os arquivos de implementação (`.cpp`) correspondentes aos cabeçalhos.
-   `saves/`: Diretório para armazenar os arquivos de save do jogo.
-   `obj/`: Diretório para arquivos objeto gerados pela compilação.
-   `.vscode/`: Configurações do VS Code.

## 3. Componentes Principais

### 3.1. Gerenciamento de Estado do Jogo

-   **[`GameState.hpp`](include/GameState.hpp)** / **[`GameState.cpp`](src/GameState.cpp)**:
    -   Define o `enum class GameState` que representa os diferentes estados do jogo (e.g., `MAIN_MENU`, `BATTLE_MENU`, `SAVE_MENU`, `EXIT`).
    -   O namespace `Game` gerencia o estado atual (`currentState`), a opção selecionada (`selectedOption`), e outras variáveis globais relacionadas ao estado do jogo, incluindo `activePlayer` que armazena o personagem do jogador atualmente em uso.
    -   As funções `Game::handleInput()` e `Game::render()` são responsáveis por processar a entrada do usuário e renderizar a tela com base no `currentState`.

### 3.2. Entrada do Usuário

-   **[`ArrowKey.hpp`](include/ArrowKey.hpp)** / **[`ArrowKey.cpp`](src/ArrowKey.cpp)**:
    -   Fornece funcionalidades para capturar a entrada do teclado, incluindo teclas de seta, Enter e 'q'.
    -   A função `getArrowKey()` retorna um `Key` enum (Up, Down, Left, Right, Enter, Quit, None).
    -   `initKeyboard()` e `restoreKeyboard()` configuram e restauram o terminal para a captura de teclas.

### 3.3. Personagens e Inimigos

-   **[`Character.hpp`](include/Character.hpp)** / **[`Character.cpp`](src/Character.cpp)**:
    -   Define a classe `Character`, que é a base para o jogador e os inimigos.
    -   Contém atributos como nome, HP, defesa, ataque, magia e equipamento.
    -   Métodos para `dealDamage()`, `takeDamage()`, `cure()`, `defend()` e `action()` (para realizar ações em batalha).
-   **[`Enemy.hpp`](include/Enemy.hpp)** / **[`Enemy.cpp`](src/Enemy.cpp)**:
    -   Deriva da classe `Character`.
    -   Implementa a lógica de `autoAction()` para o inimigo, que decide automaticamente qual ação tomar em batalha (atacar, curar, defender).

### 3.4. Sistema de Batalha

-   **[`Battle.hpp`](include/Battle.hpp)** / **[`Battle.cpp`](src/Battle.cpp)**:
    -   Gerencia a lógica principal de uma batalha entre o `player` e um `enemy`.
    -   Contém métodos para `playerTurn()`, `enemyTurn()` e `checkBattleStatus()`.
    -   A batalha continua em um loop até que `battleOver` seja verdadeiro.
    -   A lógica de exibição da mensagem de vitória/derrota e a atualização visual da barra de HP foram ajustadas no construtor da classe `Battle` para garantir a sincronização visual.
-   **[`BattleMenu.hpp`](include/BattleMenu.hpp)** / **[`BattleMenu.cpp`](src/BattleMenu.cpp)**:
    -   Define as opções do menu de batalha (Atacar, Defender, Curar, Status).
    -   `renderBattleMenu()` exibe o menu de batalha.
    -   `handleBattleMenuInput()` processa a entrada do usuário para navegar no menu de batalha.
    -   `renderBattleStatus()` exibe o HP e outras informações do jogador e inimigo durante a batalha.

### 3.5. Sistema de Salvar/Carregar

-   **[`Save.hpp`](include/Save.hpp)** / **[`Save.cpp`](src/Save.cpp)**:
    -   Define a classe `Save` para gerenciar os dados de save do jogo.
    -   Contém o objeto `Character` do herói e o inventário dos inimigos.
    -   `saveToFile()` e `loadFromFile()` (função global) lidam com a persistência dos dados em arquivos de texto no diretório `saves/`.
    -   `deleteSave()` remove um save existente.
    -   `saveVector` é um vetor global que armazena os objetos `Save` em memória.
-   **[`SaveMenu.hpp`](include/SaveMenu.hpp)** / **[`SaveMenu.cpp`](src/SaveMenu.cpp)**:
    -   Gerencia a interface do menu de saves.
    -   `renderSaveMenu()` exibe os slots de save.
    -   `handleSaveMenuInput()` processa a entrada do usuário para carregar, deletar ou voltar.
    -   `renderSaves()` (em `Save.cpp`) é responsável por renderizar visualmente os slots de save.

### 3.6. Menus e Criação de Personagem

-   **[`MainMenu.hpp`](include/MainMenu.hpp)** / **[`MainMenu.cpp`](src/MainMenu.cpp)**:
    -   Define as opções do menu principal (Novo Jogo, Carregar Jogo, Sair).
    -   `renderMainMenu()` e `handleMainMenuInput()` gerenciam a exibição e a interação.
-   **[`CreateMenu.hpp`](include/CreateMenu.hpp)** / **[`CreateMenu.cpp`](src/CreateMenu.cpp)**:
    -   Gerencia o processo de criação de personagem.
    -   Permite ao usuário escolher entre personagens pré-definidos (Tank, Healer, Assassin) ou criar um personagem customizado.
    -   `renderCharacterChoice()` exibe as opções de personagens.
    -   `handleChoiceMenuInput()` processa a seleção do personagem.
    -   `renderCharCreation()` e `handleCharCreation()` lidam com a customização de atributos.
    -   `renderCreateSaveMenu()` e `handleCreateSaveInput()` gerenciam a tela de salvar o personagem recém-criado. Após a criação/seleção, o personagem é atribuído a `Game::activePlayer` e o jogo transiciona para o estado de batalha.

### 3.7. Utilitários e Renderização

-   **[`utils.hpp`](include/utils.hpp)** / **[`utils.cpp`](src/utils.cpp)**:
    -   Contém funções utilitárias para manipulação de strings (`repeat`, `replacePlaceholder`, `formatField`).
    -   Funções para controle do terminal (`getTerminalWidth`, `adjustWindow`, `centralPrint`).
    -   `renderScroll()` é uma função genérica para renderizar menus de rolagem.
-   **[`card_render.hpp`](include/card_render.hpp)** / **[`card_render.cpp`](src/card_render.cpp)**:
    -   Funções para formatar e renderizar visualmente as "cartas" dos personagens, incluindo seus atributos e arte ASCII.
    -   `formatCharacterCard()` formata os dados do personagem em um layout de carta.
    -   `renderCharStats()` e `renderCharCustom()` exibem as estatísticas do personagem.

### 3.8. Itens (Em Desenvolvimento)

-   **[`Item.hpp`](include/Item.hpp)** / **[`Item.cpp`](src/Item.cpp)**:
    -   Define a classe `Item` e o `enum class ItemType`.
    -   Atualmente, parece ser uma estrutura básica para itens, mas a implementação em `Item.cpp` está vazia, indicando que esta funcionalidade ainda está em desenvolvimento ou não totalmente integrada.

## 4. Fluxo do Jogo (main.cpp)

O arquivo [`main.cpp`](main.cpp) é o ponto de entrada do jogo.

1.  **Inicialização:**
    -   Define a cor do texto do terminal.
    -   Chama `initKeyboard()` para configurar a captura de entrada.
    -   Chama `loadFromFile()` para carregar os saves existentes.
2.  **Loop Principal:**
    -   Um loop `while (Game::currentState != GameState::EXIT)` mantém o jogo em execução.
    -   Dentro do loop:
        -   `adjustWindow()`: Ajusta o tamanho da janela do terminal.
        -   `Game::render()`: Renderiza a tela com base no `currentState`.
        -   `Game::handleInput()`: Processa a entrada do usuário e atualiza o `currentState`.
        -   Se `currentState` for `INITIALIZE_BATTLE`, uma nova instância de `Battle` é criada usando `Game::activePlayer` e um inimigo padrão, iniciando o ciclo de batalha. Após a batalha, o jogo retorna ao menu principal.
3.  **Finalização:**
    -   Quando o `currentState` se torna `EXIT`, o loop termina.
    -   `restoreKeyboard()` é chamado para restaurar as configurações do terminal.
    -   A tela é limpa e uma mensagem de saída é exibida.

## 5. Como Implementar Modificações

Para implementar modificações, siga estas diretrizes:

-   **Novas Ações de Batalha:**
    -   Modifique `BattleMenu.hpp` e `BattleMenu.cpp` para adicionar novas opções ao menu de batalha.
    -   Atualize `Character.hpp` e `Character.cpp` com os novos métodos de ação.
    -   Ajuste a lógica em `Battle.cpp` para chamar as novas ações.
-   **Novos Tipos de Inimigos:**
    -   Crie novas classes derivadas de `Enemy` (ou modifique `Enemy.cpp`) para definir comportamentos e atributos específicos.
    -   Integre esses novos inimigos na lógica de inicialização de batalhas em `main.cpp` ou em um sistema de encontro de inimigos.
-   **Sistema de Inventário/Itens:**
    -   Expanda a classe `Item` em `Item.hpp` e `Item.cpp` com mais atributos e funcionalidades.
    -   Adicione um vetor de `Item` à classe `Character` para gerenciar o inventário do jogador.
    -   Crie um novo menu (`InventoryMenu.hpp`/`.cpp`) e integre-o ao `GameState` para permitir que o jogador gerencie seus itens.
    -   Modifique o sistema de save para persistir os dados do inventário.
-   **Novas Telas/Menus:**
    -   Crie novos arquivos `.hpp` e `.cpp` para o novo menu (e.g., `ShopMenu.hpp`/`.cpp`).
    -   Adicione um novo `GameState` ao `enum class GameState` em `GameState.hpp`.
    -   Atualize `Game::handleInput()` e `Game::render()` em `GameState.cpp` para lidar com o novo estado.
    -   Integre o novo menu a outros menus existentes (e.g., um link do `MainMenu` para o `ShopMenu`).
-   **Melhorias na UI/UX:**
    -   Utilize as funções em `utils.hpp` e `card_render.hpp` para formatar a saída de texto e criar elementos visuais.
    -   Experimente com cores e posicionamento para melhorar a experiência do terminal.

Lembre-se de sempre compilar e testar suas modificações para garantir que não introduzam bugs e que se integrem corretamente ao fluxo do jogo.