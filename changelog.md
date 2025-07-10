# Changelog - RPG Terminal (v1)

Este changelog documenta as modificações realizadas para trazer o jogo RPG Terminal para um estado jogável de "versão 1", com um ciclo completo de criação de personagem e batalha.

## Versão 1.0.0 - Ciclo Básico de Jogo

### Funcionalidades Adicionadas:

-   **Personagem Ativo Global:**
    -   Adicionada uma variável `activePlayer` no namespace `Game` (`include/GameState.hpp` e `src/GameState.cpp`) para armazenar o personagem do jogador atualmente em uso.

-   **Integração da Criação de Personagem com o Jogo:**
    -   Após a criação ou seleção de um personagem no menu de criação (`src/CreateMenu.cpp`), o personagem escolhido é agora atribuído a `Game::activePlayer`.
    -   O jogo transiciona automaticamente para o estado de batalha (`GameState::INITIALIZE_BATTLE`) após a confirmação da criação/seleção do personagem.

-   **Fluxo de Batalha Integrado:**
    -   A batalha agora utiliza o `Game::activePlayer` como o personagem do jogador (`main.cpp`).
    -   A opção "Battle Test" foi removida do menu principal (`src/MainMenu.cpp`) para garantir que a batalha seja iniciada apenas através do fluxo de criação de personagem.
    -   Após a conclusão da batalha (vitória ou derrota), o jogo retorna ao menu principal (`main.cpp`).

### Melhorias e Correções:

-   **Sincronização Visual da Batalha:**
    -   A lógica de exibição da mensagem de vitória/derrota e a atualização visual da barra de HP do inimigo foram ajustadas no construtor da classe `Battle` (`src/Battle.cpp`). Agora, a tela é renderizada com o HP atualizado imediatamente após a condição de vitória/derrota ser detectada, antes de qualquer prompt para o usuário continuar.
    -   Removidas as chamadas `cout` e `pressSpaceToContinue()` de `Battle::checkBattleStatus()` para centralizar a lógica de exibição no construtor da `Battle`.

### Correções de Bugs:

-   **Erro de Compilação em `src/MainMenu.cpp`:**
    -   Corrigido um erro de chave de fechamento (`}`) ausente na função `handleMainMenuInput()` em `src/MainMenu.cpp`, que impedia a compilação do projeto.

## Versão 1.1.0 - Inimigos Sequenciais e Refinamentos do Fluxo

### Funcionalidades Adicionadas:

-   **Inimigos Sequenciais:**
    -   Adicionada a variável `currentEnemyIndex` no namespace `Game` (`include/GameState.hpp` e `src/GameState.cpp`) para controlar o inimigo atual na sequência.
    -   Implementadas as funções `Game::getEnemyByIndex(int index)` e `Game::getTotalEnemies()` em `src/GameState.cpp` para gerenciar uma lista pré-definida de inimigos.
    -   A inicialização da batalha em `main.cpp` agora utiliza o inimigo correspondente ao `Game::currentEnemyIndex`.
    -   `Game::currentEnemyIndex` é incrementado em `src/Battle.cpp` quando o jogador vence uma batalha.

### Melhorias e Correções:

-   **Correção do Construtor de Inimigo:**
    -   Adicionado um novo construtor à classe `Enemy` (`include/Enemy.hpp` e `src/Enemy.cpp`) para permitir a inicialização com nome, defesa, ataque e magia, corrigindo erros de compilação ao criar inimigos.

-   **Correção de Warnings de Comparação:**
    -   Aplicado `static_cast<size_t>` em comparações entre `int` e `size_t` em `src/Battle.cpp` e `src/GameState.cpp` para resolver warnings de compilação relacionados a diferentes tipos de sinalização.

-   **Fluxo de Batalha Aprimorado:**
    -   A lógica de transição de estado após a batalha em `src/Battle.cpp` foi ajustada para que o jogo avance para o próximo inimigo (se houver) ou retorne ao menu principal (se todos os inimigos forem derrotados ou o jogador perder).
    -   Removida a transição incondicional para o menu principal em `main.cpp` após cada batalha, permitindo o fluxo sequencial de inimigos.

-   **Reset do Índice de Inimigo em Novo Jogo:**
    -   `Game::currentEnemyIndex` agora é resetado para `0` em `src/MainMenu.cpp` quando a opção "Novo Jogo" é selecionada, garantindo que o primeiro inimigo seja sempre enfrentado ao iniciar um novo jogo.

## Versão 1.2.0 - Pós-Merge e Correções de Fluxo

### Melhorias e Correções:

-   **Padronização da Variável do Jogador:**
    -   Renomeada a variável global `Game::activePlayer` para `Game::player` em todo o projeto (`GameState.hpp`, `GameState.cpp`, `main.cpp`, `CreateMenu.cpp`) para resolver um erro de linkagem (`undefined reference`) que surgiu após o merge com a branch `main`.

-   **Correção da Lógica de Renderização da Batalha:**
    -   Removida a limpeza de tela (`system(CLEAR_COMMAND)`) da função `pressSpaceToContinue()` em `src/BattleMenu.cpp` para evitar que a tela da batalha desaparecesse durante o turno do inimigo.

-   **Correção de Pausas Duplas na Batalha:**
    -   Removidas chamadas redundantes para `pressSpaceToContinue()` de dentro do loop de batalha em `src/Battle.cpp`, resolvendo o problema de o jogo pausar duas vezes por rodada.

-   **Correção do Incremento Duplo do Inimigo:**
    -   Restaurada a verificação `if (battleOver)` após o turno do jogador em `src/Battle.cpp` para interromper o loop de batalha imediatamente após uma vitória, corrigindo o bug que fazia o jogo pular um inimigo na sequência.
